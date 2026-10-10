//
//  Liste der Datenbank - Tabellen
//
// $Header:   P:/marille/clinicum/restool/rev/dbtblst.cpv   1.12   26 Apr 1999 18:11:14   Wolfgang  $
// $Log:   P:/marille/clinicum/restool/rev/dbtblst.cpv  $
// 
//    Rev 1.12   26 Apr 1999 18:11:14   Wolfgang
// 1.) Sanduhr-Cursor auch wieder zuruecksetzen.
// 
//    Rev 1.11   28 Aug 1997 15:48:18   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.10   19 Feb 1997 12:12:26   Hannes
// Parent in den Tabellendefinition (Scriptfunktionen neu)
// 
//    Rev 1.9   29 Nov 1996 07:56:14   HANNES
// Verbesserte Vergleiche beim Listenoeffnen
// 
//    Rev 1.8   26 Nov 1996 08:10:40   HANNES
// Automatischer Update
// 
//    Rev 1.7   21 Oct 1996 18:57:38   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.6   20 Jun 1996 18:55:58   HANNES
// Ungereimtheiten im Restool ausgeraeumt
// 
//    Rev 1.5   18 Jun 1996 15:35:00   HANNES
// wenigstens Syntaxfehler-frei gemacht
// 
//    Rev 1.4   02 Feb 1996 10:50:42   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   23 May 1995 11:51:56   GERHOLD
// SearchStringInList ... Suchen nach Namen in der Tabelle
// 
//    Rev 1.2   26 Apr 1995 15:26:18   HANNES
// 
//    Rev 1.1   16 Feb 1995 12:33:08   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.0   24 Jan 1995 11:00:42   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "font.hpp"
#include "printer.hpp"
#define NODDSDATA
#include "dds.hpp"
#include "sc2d.hpp"
#include "paint.hpp"
#include "cfield.hpp"
#include "multl.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "drdrop.hpp"

#include "fldlst.hpp"

class FAR DbTbList : public FldList {
 public :
  DbTbList (LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { }

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
  virtual void   OnCommand (WORD wP);

  virtual LPSTR  GetMenuName();
  virtual LPSTR  ProfBase();
  virtual int    GetColWidth(int Column);
  virtual void   OnDblClk(LPFLDLINE line,int column);
  virtual void   SearchInList (WORD wP);
  virtual BOOL   SearchStringInList (LPSTR prefix,LPSTR SearchStr,BOOL doOpen);
  virtual int    GetDropType (int DownColumn);
  };

class FAR IntTbList : public DbTbList {
 public :
  IntTbList (LPVOID Cntx,LPSTR cptn) : DbTbList (Cntx,cptn)
     { }

  virtual LPVOID GetFirstContext();
  virtual LPVOID GetNextContext(LPVOID oldConext);
  virtual void   OnCommand (WORD wP);
  virtual int    GetDropType (int DownColumn);
  virtual void   OnDblClk(LPFLDLINE line,int column);
  };

class FAR GlobTbList : public DbTbList {
 public :
  GlobTbList (LPVOID Cntx,LPSTR cptn) : DbTbList (Cntx,cptn)
     { }

  virtual LPVOID GetFirstContext();
  virtual LPVOID GetNextContext(LPVOID oldConext);
  virtual void   OnCommand (WORD wP);
  virtual int    GetDropType (int DownColumn);
  virtual void   OnDblClk(LPFLDLINE line,int column);
  };

/*--< Implementierung der virtuellen Funktionen fuer Feldbearbeitung >--*/
int DbTbList::AnzColumns()
  {
  return 1;
  }
int DbTbList::GetX0()
  {
  return 0 ;
  }

DWORD DbTbList::GetColMode (int Column)
  {
  return FM_OUTLINEONLY ;
  }

LPSTR DbTbList::GetFieldString (LPVOID Context,int Column)
  {
  LPCONTENTRY ent = LPCONTENTRY (Context);
  return ent->TableName;
  }

LPSTR DbTbList::GetHdString (int Column)
  {
  return "\\m1Tabelle" ;
  }

int DbTbList::GetFormat()
  {
  return 2 ;
  }

LPVOID DbTbList::GetFirstContext()
  {
  LPCONTENTRY ent = GetTableAdmin()->GetDDContent()->First();
  for ( ; ((ent != NULL) && (ent->tRef.TableNr >= GLOBALTBIDMIN)) ; 
                ent = GetTableAdmin()->GetDDContent()->Next(ent)) ;
  return ent;
  }

LPVOID IntTbList::GetFirstContext()
  {
  LPCONTENTRY ent = GetTableAdmin()->GetDDContent()->First();
  for ( ; ((ent != NULL) && ((ent->tRef.TableNr > INTERNTBIDMAX) || (ent->tRef.TableNr < INTERNTBIDMIN))) ; 
                ent = GetTableAdmin()->GetDDContent()->Next(ent)) ;
  return ent;
  }

LPVOID GlobTbList::GetFirstContext()
  {
  LPCONTENTRY ent = GetTableAdmin()->GetDDContent()->First();
  for ( ; ((ent != NULL) && ((ent->tRef.TableNr > GLOBALTBIDMAX) || (ent->tRef.TableNr < GLOBALTBIDMIN))) ; 
                ent = GetTableAdmin()->GetDDContent()->Next(ent)) ;
  return ent;
  }

LPVOID DbTbList::GetNextContext(LPVOID oldContext)
  {
  LPCONTENTRY ent = LPCONTENTRY(oldContext);
  for (ent = GetTableAdmin()->GetDDContent()->Next(ent) ;
          ((ent != NULL) && (ent->tRef.TableNr >= GLOBALTBIDMIN)) ; 
                ent = GetTableAdmin()->GetDDContent()->Next(ent)) ;
  return ent;
  }

LPVOID IntTbList::GetNextContext(LPVOID oldContext)
  {
  LPCONTENTRY ent = LPCONTENTRY(oldContext);
  for (ent = GetTableAdmin()->GetDDContent()->Next(ent) ;
          ((ent != NULL) && ((ent->tRef.TableNr > INTERNTBIDMAX) || (ent->tRef.TableNr < INTERNTBIDMIN))) ; 
                ent = GetTableAdmin()->GetDDContent()->Next(ent)) ;
  return ent;
  }

LPVOID GlobTbList::GetNextContext(LPVOID oldContext)
  {
  LPCONTENTRY ent = LPCONTENTRY(oldContext);
  for (ent = GetTableAdmin()->GetDDContent()->Next(ent) ;
          ((ent != NULL) && ((ent->tRef.TableNr > GLOBALTBIDMAX) || (ent->tRef.TableNr < GLOBALTBIDMIN))) ; 
                ent = GetTableAdmin()->GetDDContent()->Next(ent)) ;
  return ent;
  }

BOOL DbTbList::EnableNewContext()
  {
  return FALSE ;
  }

LPSTR DbTbList::GetMenuName()
  {
  return "DBTBMENU";
  }

static HWND DbTbOpenWnd,IntTbOpenWnd,GlobTbOpenWnd;
void DbTbList::OnDestroy()
  {
  if (hWnd == DbTbOpenWnd)
    DbTbOpenWnd = 0 ;
  else if (hWnd == IntTbOpenWnd)
    IntTbOpenWnd = 0 ;
  else
    GlobTbOpenWnd = 0 ;
  }

LPSTR DbTbList::ProfBase()
  {
  return "TLST";
  }

LPSTR DbTbList::GetResource (int Column)
  {
  static char res[2];
  res[0] = res[1] = '\0';
  return res;
  }

BOOL DbTbList::EnableInput ()
  {
  return FALSE ;
  }

int DbTbList::GetColWidth(int Column)
  {
  if (ColWidth == NULL) {
    ColWidth = (int FAR *) GetGlobMem (sizeof(int) * AnzColumns());
    for (int i = 0 ; i < AnzColumns() ; i++)
      ColWidth[i] = -1;
    }
  if (ColWidth[Column] == -1) {
    char wstring[32];
    wsprintf (wstring,"Width%d",Column);
    ColWidth[Column] = GetProfInt (wstring,3000);
    }
  return ColWidth[Column];
  }

extern void WorkOnTable (LPSTR TableName);
extern void WorkOnIntTable (LPSTR TableName,HWND hWParent);
extern void CreateNewTableDef ();
extern void CreateNewIntTableDef (HWND hWParent);
void DbTbList::OnDblClk(LPFLDLINE line,int column)
  {
  GLOBALHANDLE hGtmp;
  *(line->GetField(0)) >> hGtmp;
  LPSTR res = (LPSTR)GlobalLock (hGtmp);
  WorkOnTable (res);
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  }

void IntTbList::OnDblClk(LPFLDLINE line,int column)
  {
  GLOBALHANDLE hGtmp;
  *(line->GetField(0)) >> hGtmp;
  LPSTR res = (LPSTR)GlobalLock (hGtmp);
  WorkOnIntTable (res,hWnd);
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  }

extern void WorkOnGlobTable (LPSTR TableName);
void GlobTbList::OnDblClk(LPFLDLINE line,int column)
  {
  GLOBALHANDLE hGtmp;
  *(line->GetField(0)) >> hGtmp;
  LPSTR res = (LPSTR)GlobalLock (hGtmp);
  WorkOnGlobTable (res);
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);
  }

void DbTbList::OnCommand (WORD wP)
  {
  switch (wP) {
    case 100 :
      if (ActiveLine != NULL)
        OnDblClk(ActiveLine,ActiveCol);
      break ;
    case 102 :
      CreateNewTableDef ();
      break ;
    case 101 :
      {
      char Name[64];
      if ((ActiveLine != NULL) && (GetFieldContent (Name,ActiveLine,0))) {
        char outstring[128];
        wsprintf (outstring,"Sind Sie sicher, daß Sie die Tabelle %s löschen wollen",LPSTR(Name));
        if (MessageBox (hWnd,outstring,"Löschen",MB_ICONQUESTION | MB_YESNO) == IDYES) {
          SetCursor (LoadCursor (NULL,IDC_WAIT));
          if (GetTableAdmin()->DelTableDef (Name)) {
            OnKillFocus ();
            ActiveLine = RemoveLine (ActiveLine);
            OnSetFocus ();
            }
          }
        }
      }
      break ;
    }
  }

void IntTbList::OnCommand (WORD wP)
  {
  switch (wP) {
    case 102 :
      CreateNewIntTableDef (hWnd);
      break ;
    default :
      DbTbList::OnCommand (wP);
      break ;
    }
  }

extern void CreateNewGlobTable ();
void GlobTbList::OnCommand (WORD wP)
  {
  switch (wP) {
    case 102 :
      CreateNewGlobTable ();
      break ;
    default :
      DbTbList::OnCommand (wP);
      break ;
    }
  }

int DbTbList::GetDropType (int DownColumn)
  {
  return DDTYPE_TABLE ;
  }

int IntTbList::GetDropType (int DownColumn)
  {
  return DDTYPE_INTTABLE ;
  }

int GlobTbList::GetDropType (int DownColumn)
  {
  return 0 ;
  }

static BOOL mystrcmpnum (LPSTR ltxt, LPSTR stxt,int FAR *fault)
  {
  for ( ; ((*ltxt) && (*stxt) && 
#ifdef WIN32
            ((char) (DWORD) CharUpper (LPSTR(*stxt)) == 
             (char) (DWORD) CharUpper (LPSTR(*ltxt)))) ; stxt ++ , ltxt ++ ) ;
#else
            ((char) (DWORD) AnsiUpper (LPSTR(MAKELP(0,*stxt))) == 
             (char) (DWORD) AnsiUpper (LPSTR(MAKELP(0,*ltxt))))) ; stxt ++ , ltxt ++ ) ;
#endif
  *fault = int (*ltxt);
  if (*fault < 0) *fault = - *fault ;
  return ((*stxt == '\0') || (*stxt == '.')) ;
  }

BOOL DbTbList::SearchStringInList (LPSTR prefix,LPSTR SearchStr,BOOL doOpen)
  {
  char szTmp[128];
  LPFLDLINE f = NULL ;
  int anzFound = 0 ;
  BOOL res ;
  int oldfault = 32000 ;
  char t1[256],t2[256];
  lstrcpy (t1,SearchStr);
  GetVersionFrom(t1);
  if (prefix != NULL) {
    GetPrefix(t2,prefix);
    lstrcat (t2,t1);
    }
  else
    *t2 = '\0' ;
  for (LPFLDLINE h = ActiveLine ; h != NULL ; ) {
    GLOBALHANDLE hGtmp;
    *(h->GetField(0)) >> hGtmp;
    LPSTR res = (LPSTR)GlobalLock (hGtmp);
    lstrcpy (szTmp, res);
    GlobalUnlock(hGtmp);
    GlobalFree(hGtmp);

    int fault1,fault2,fault;
    BOOL d1,d2;
    if ((d1 = mystrcmpnum(szTmp, t1,&fault1)) ||
        ((*t2) && (d2 = mystrcmpnum(szTmp, t2,&fault2)))) {
      if (d1) fault = fault1 ;
      else    fault = fault2 ;
      if ((f == NULL) || (fault < oldfault)) f = h , oldfault = fault ;
      anzFound ++ ;
      }
    LPFLDLINE next = GetNextLine (h);
    if (next == ActiveLine) break ;
    h = next ;
    }

  if ((anzFound >= 1) && (doOpen) && (oldfault == 0)) {
    OnDblClk (f,0);
    res = TRUE ;
    }
  else {
    res = FALSE ;
    if (f != NULL) {
      OnKillFocus ();
      ActiveLine = f;
      OnSetFocus ();
      }
    }

  return res;  
  }

static char searchString [32];
void resetSearchString ()
  {
  searchString[0] = '\0';
  }

void DbTbList::SearchInList (WORD wP)
  {
  int l = lstrlen (searchString) ;
  if ((wP == '\b') || (wP == 255)) {
    if (l > 0)
      searchString[l - 1] = '\0';
    }
  else {
    if (l < sizeof(searchString) - 2) {
      searchString[l] = char(wP);
      searchString[l+1] = '\0';
      }
    }

  SearchStringInList (NULL,searchString,FALSE);
  }

//
//    Anzeigen der Tabellen
//
void OpenDBList (LPSTR SearchStr)
  {
  if (!IsWindow (DbTbOpenWnd)) {
    resetSearchString ();
    DbTbList FAR *lst = new DbTbList (NULL,"TABLES");
    lst->Create (0);
    lst->Show ();
    BOOL doDestroy ;
    if (SearchStr != NULL)
      doDestroy = lst->SearchStringInList (NULL,SearchStr,TRUE);
    else
      doDestroy = FALSE ;
    if (doDestroy)
      DestroyWindow (lst->hWnd);
    else
      DbTbOpenWnd = lst->hWnd ;
    }
  }

HWND GetDBTableWnd ()
  {
  return DbTbOpenWnd;
  }

void TestTable (LPSTR Name,WORD Id,WORD Version)
  {
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
  if ((!GetTableAdmin()->CheckDataDictContent (Name,Id,Version,0,0)) &&
                    (IsWindow (DbTbOpenWnd))) {
    DbTbList FAR *lst = (DbTbList FAR *) (GetWindowLong (DbTbOpenWnd,GWL_FLDLIST));
    lst->ActiveLine = lst->Enlarge (NULL);
    *(lst->ActiveLine->GetField(0)) = Name;
    }
  SetCursor (oldCursor);
  }

void TestIntTable (LPSTR Name,WORD Id)
  {
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
  if ((!GetTableAdmin()->CheckDataDictContent (Name,Id,0,0,0)) &&
                    (IsWindow (IntTbOpenWnd))) {
    IntTbList FAR *lst = (IntTbList FAR *) (GetWindowLong (IntTbOpenWnd,GWL_FLDLIST));
    lst->ActiveLine = lst->Enlarge (NULL);
    *(lst->ActiveLine->GetField(0)) = Name;
    }
  SetCursor (oldCursor);
  }

void TestGTable (LPSTR Name,WORD Id,WORD ParentID,WORD ParentVersion)
  {
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
  if ((!GetTableAdmin()->CheckDataDictContent (Name,Id,0,ParentID,ParentVersion)) &&
                    (IsWindow (GlobTbOpenWnd))) {
    GlobTbList FAR *lst = (GlobTbList FAR *) (GetWindowLong (GlobTbOpenWnd,GWL_FLDLIST));
    lst->ActiveLine = lst->Enlarge (NULL);
    *(lst->ActiveLine->GetField(0)) = Name;
    }
  SetCursor (oldCursor);
  }

void OpenIntList (LPSTR prefix,LPSTR SearchStr)
  {
  if (!IsWindow (IntTbOpenWnd)) {
    resetSearchString ();
    IntTbList FAR *lst = new IntTbList (NULL,"VIEW");
    lst->Create (0);
    lst->Show ();
    BOOL doDestroy ;
    if (SearchStr != NULL)
      doDestroy = lst->SearchStringInList (prefix,SearchStr,TRUE);
    else
      doDestroy = FALSE ;
    if (doDestroy)
      DestroyWindow (lst->hWnd);
    else
      IntTbOpenWnd = lst->hWnd ;
    }
  }

void OpenGlobList (LPSTR prefix,LPSTR SearchStr)
  {
  if (!IsWindow (GlobTbOpenWnd)) {
    resetSearchString ();
    GlobTbList FAR *lst = new GlobTbList (NULL,"STRUCT");
    lst->Create (0);
    lst->Show ();
    BOOL doDestroy ;
    if (SearchStr != NULL)
      doDestroy = lst->SearchStringInList (prefix,SearchStr,TRUE);
    else
      doDestroy = FALSE ;
    if (doDestroy)
      DestroyWindow (lst->hWnd);
    else
      GlobTbOpenWnd = lst->hWnd ;
    }
  }

HWND GetGTableWnd ()
  {
  return GlobTbOpenWnd;
  }

void DestroyTables ()
  {
  GetTableAdmin()->OnExit();
  GetDLLAdmin()->ResetDLLAdmin();
  }

extern DLLExport LPSTR _export FAR PASCAL makeIni (LPSTR name);
LPSTR IniFile() 
  { 
  return makeIni("restool.ini") ; 
  }

