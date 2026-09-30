/*------------------------------------*/
/*  Bearbeiten der internen Tabellen  */
/*------------------------------------*/
// $Header:   P:/marille/clinicum/restool/rev/intlst.cpv   1.11   26 Apr 1999 18:11:32   Wolfgang  $
// $Log:   P:/marille/clinicum/restool/rev/intlst.cpv  $
// 
//    Rev 1.11   26 Apr 1999 18:11:32   Wolfgang
// 1.) Sanduhr-Cursor auch wieder zuruecksetzen.
// 
//    Rev 1.10   05 Oct 1998 11:27:08   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.9   05 Nov 1997 09:02:46   Gerhold
// 32 Bit
// 
//    Rev 1.8   28 Aug 1997 15:52:34   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.7   26 Nov 1996 08:10:12   HANNES
// Automatischer Update
// 
//    Rev 1.6   21 Oct 1996 18:57:56   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.5   17 Jun 1996 16:53:52   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.4   02 Feb 1996 10:50:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   27 Aug 1995 13:15:14   HANNES
// Caption setzten beim Speichern
// 
//    Rev 1.2   26 Apr 1995 15:26:38   HANNES
// 
//    Rev 1.1   24 Apr 1995 11:34:32   HANNES
//  
// 
//    Rev 1.0   16 Feb 1995 12:41:10   HANNES
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
#include "srved.hpp"
#include "tblst.hpp"
#include "restool.hpp"
#include "hash.hpp"
#include "riwnd.hpp"
#include "jlst.hpp"
#include "blandmdi.hpp"

static char oldstr[256];
static char *yes = "yes" ;
static char *no = "no" ;

BOOL IntFldList::IsNameAllowed (LPSTR Name,LPFLDLINE l)
  {
  char inword [64];
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((GetFieldSent (inword,h,1)) && (lstrcmp (inword,"*") == 0)) continue;
    if (h == l) break ;
    if ((GetFieldContent (inword,h,3)) && (lstrcmp (inword,Name) == 0)) return FALSE;
    }
  return TRUE ;
  }

BOOL IntFldList::IsAllSelected (int nr,LPSTR prefix)
  {
  char inword[20];
  int tnr;
  if (prefix != NULL) *prefix = '\0';
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((GetFieldWord (inword,h,0,TRUE)) && (sscanf (inword,"%d",&tnr)) &&
        (tnr == nr)) {
      if ((GetFieldRes (inword,h,2,TRUE)) && (lstrcmp (inword,yes) == 0)) {
        if (prefix != NULL) GetFieldContent (prefix,h,3);
        return TRUE ;
        }
      else
        return FALSE ;
      }
    }
  return FALSE ;
  }

BOOL IntFldList::AllowChange(LPFLDLINE h,int Column)
  {
  if ((Column == 0) || (Column == 1)) return FALSE ;
  if (Column == 3) {
    char selection[32];
    if ((GetFieldRes(selection,h,2,TRUE)) && (lstrcmp (selection,yes) == 0))
      GetFieldContent (oldstr,h,Column);
    else
      return FALSE ;
    }
  if (Column == 2) {
    char inword[64];
    WORD tnr;
    if ((GetFieldWord (inword,h,0,TRUE)) && (sscanf (inword,"%d",&tnr))) {
      if ((GetFieldSent (inword,h,1)) && (lstrcmp (inword,"*") == 0))
        return TRUE ;
      else if (IsAllSelected (tnr)) 
        return FALSE ;
      }
    else
      return TRUE ;
    }
  return TRUE;
  }

LPSTR IntFldList::GetAliasName (LPSTR str,LPFLDLINE line)
  {
  GetFieldContent (str,line,3);  return str;
  }

void IntFldList::AllAliasChanged (LPFLDLINE h)
  {
  char str1[64],str2[64],str3[64],prefix[32];
  int t0,tnr;
  GetFieldContent (prefix,h,3);
  GetFieldWord (str1,h,0,TRUE);  sscanf (str1,"%d",&t0);
  for (h = h->Next ; h != NULL ; h = h->Next) {
    if ((GetFieldWord (str3,h,0,TRUE)) && (sscanf (str3,"%d",&tnr)) &&
        (tnr == t0)) {
      GetFieldContent (str1,h,3);
      GetFieldContent (str3,h,1);
      char postfix[2];
      postfix[0] = postfix[1] = '\0';
      for (int i = 0 ; ; i++) {
        lstrcpy (str2,prefix); if (*str2)   lstrcat (str2,"_"); lstrcat (str2,str3);
        if (i > 0) postfix[0] = '1' + i - 1;
        lstrcat (str2,postfix);
        if (IsNameAllowed (str2,h)) break ;
        }
      ModifyContent (h,3,str2);
      jlst->AliasChanged (str1,str2);
      }
    }
  }

void IntFldList::DelAllAlias (LPFLDLINE line,int t0)
  {
  int tnr;
  char str[64];
  for (LPFLDLINE h = line->Next ; h != NULL ; h = h->Next) {
    if ((GetFieldWord (str,h,0,TRUE)) && (sscanf (str,"%d",&tnr)) &&
                (tnr == t0))
      ModifyContent (h,3,"");
    else
      break ;
    }
  }

void IntFldList::GetNameWithPrefix (LPSTR str,LPFLDLINE h)
  {
  char str2[64],prefix[5];
  int tnr;
  GetFieldWord (str2,h,0,TRUE); sscanf (str2,"%d",&tnr);
  IsAllSelected (tnr,prefix);
  GetFieldContent (str2,h,1);
  char postfix[2];
  postfix[0] = postfix[1] = '\0';
  for (int i = 0 ; ; i++) {
    lstrcpy (str,prefix); if (*str) lstrcat (str,"_"); lstrcat (str,str2);
    if (i > 0) postfix[0] = '1' + i - 1;
    lstrcat (str,postfix);
    if (IsNameAllowed (str,h)) break ;
    }
  }

void IntFldList::AliasChanged (LPFLDLINE h)
  {
  char str1[64];
  BOOL doModify = FALSE ;
  if (!GetFieldContent (str1,h,3)) {
    GetNameWithPrefix (str1,h);
    doModify = TRUE ;
    }
  if (doModify)
    ModifyContent (h,3,str1);
  jlst->AliasChanged (oldstr,str1);
  }

void IntFldList::Save (LPFLDLINE line,int column)
  {
  char str[256];
  if (column == 3) {
    if ((GetFieldSent (str,line,1)) && (lstrcmp (str,"*") == 0))
      AllAliasChanged (line);
    else
      AliasChanged (line);
    }
  if (column == 2) {
    if ((GetFieldSent (str,line,1)) && (lstrcmp (str,"*") == 0)) {
      if ((GetFieldRes (str,line,2,TRUE)) && (lstrcmp (str,yes) == 0)) {
        int tnr,t0;
        GetFieldWord (str,line,0,TRUE);
        sscanf (str,"%d",&t0);
        for (LPFLDLINE h = line->Next ; h != NULL ; h = h->Next) {
          if ((GetFieldWord (str,h,0,TRUE)) && (sscanf (str,"%d",&tnr)) &&
                      (tnr == t0))
            ModifyContent (h,2,no);
          else
            break ;
          }
        AllAliasChanged (line);
        }
      else {
        int t0;
        GetFieldWord (str,line,0,TRUE);
        sscanf (str,"%d",&t0);
        DelAllAlias (line,t0);
        }
      }
    else {
      if ((GetFieldRes (str,line,2,TRUE)) && (lstrcmp (str,no) == 0))
        ModifyContent (line,3,"");
      else {
        if (!GetFieldSent (str,line,3)) {
          GetNameWithPrefix (str,line);
          ModifyContent (line,3,str);
          }
        }
      }
    jlst->CheckJoins ();
    }
  }

int IntFldList::AnzColumns()
  {
  return 4;
  }
DWORD IntFldList::GetColMode(int Column)
  {
  switch (Column) {
    case 2 :
      return FM_LSELECTION | FM_NOSELECTION ; // yes/no
    case 3 :
      return FM_SINGLELINE | FM_NOSELECTION ;  // alias - Name
    }
  return FM_OUTLINEONLY ;
  }
int IntFldList::GetX0()
  {
  return 400 ;
  }
int IntFldList::GetFormat()
  {
  return 2 ;
  }
LPSTR IntFldList::GetHdString (int Column)
  {
  switch (Column) {
    case 0 :
      return "\\m1T.Nr";
    case 1 :
      return "\\m1Name";
    case 2 :
      return "\\m1Sel.";
    case 3 :
      return "\\m1Alias (optional)";
    }
  return "";
  }
struct IntFldListContext {
  LPTABLEDEF td;
  LPINTTABLE ti;
  WORD TableNr;
  int VarNr;
  };
static struct IntFldListContext ifl;
WORD IntFldList::SearchVarID()
  {
  for (int i = 0 ; i < ifl.td->GetAnzVars() ; i++) {
    ReqElem e;
    ifl.ti->GetReqElem (&e,i);
    if ((e.TableNumber == int(ifl.TableNr)) && (e.VarID == WORD(ifl.VarNr))) return i ;
    }
  return 0 ;
  }

WORD IntFldList::GetFirstVarForTable()
  {
  for (int i = 0 ; i < ifl.td->GetAnzVars() ; i++) {
    ReqElem e;
    ifl.ti->GetReqElem (&e,i);
    if (e.TableNumber == int(ifl.TableNr)) return i;
    }
  return 0 ;
  }

LPSTR IntFldList::GetFieldString (LPVOID Context,int Column)
  {
  IntFldListContext FAR *c = (IntFldListContext FAR *) Context;
  static char res[64];
  static char *nothing = "" ;
  switch (Column) {
    case 0 :
      wsprintf (res,"%d",c->TableNr);
      return res;
      break ;
    case 1 :
      if (c->VarNr == -1)
        return "*" ;
      else {
        LPPTABLE p = c->ti->GetTableByNum(c->TableNr);
        LPTABLEDEF td = GetTableAdmin()->GetTableDef (p->tRef.TableNr,p->tRef.Version);
        LPSTR r = td->GetVarDef(c->VarNr)->GetName();
        GetTableAdmin()->FreeTable (p->tRef.TableNr,p->tRef.Version);
        return r;
        }
      break ;
    case 2 :
      {
      LPPTABLE p = c->ti->GetTableByNum(c->TableNr);
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (p->tRef.TableNr,p->tRef.Version);
      LPSTR r;
      if (c->VarNr == -1) {
        r = (td->GetAnzVars() == int(p->AnzVars)) ? yes : no ;
        }
      else {
        if (td->GetAnzVars() == int(p->AnzVars))
          r = no ;
        else {
          r = no ;
          for (WORD i = 0 ; i < p->AnzVars ; i++) {
            if (p->VarID[i] == WORD(c->VarNr)) r = yes ;
            }
          }
        }
      GetTableAdmin()->FreeTable (p->tRef.TableNr,p->tRef.Version);
      return r;
      }
      break ;
    case 3 :
      {
      LPPTABLE p = c->ti->GetTableByNum(c->TableNr);
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (p->tRef.TableNr,p->tRef.Version);
      LPSTR r = nothing;
      if (c->VarNr == -1) {
        if (td->GetAnzVars() == int(p->AnzVars)) {
          // Suchen des generellen Prefix
          LPSTR n = c->td->GetVarDef(GetFirstVarForTable())->GetName();
          r = res ;
          BOOL found = FALSE ;
          for (LPSTR h = n ; ((*h) && (!found)) ; h++) {
            if (*h != '_') 
              *r ++ = *h ;
            else {
              *r = '\0';
              found = TRUE ;
              }
            }
          if (found)
            r = res ;
          else
            r =  nothing ;
          }
        }
      else {
        // Es handelt sich um einen Ausschnitt
        for (WORD i = 0 ; i < p->AnzVars ; i++) {
          if (p->VarID[i] == WORD(c->VarNr))
            r = c->td->GetVarDef(SearchVarID())->GetName();
          }
        }
      GetTableAdmin()->FreeTable (p->tRef.TableNr,p->tRef.Version);
      return r;
      }
      break ;
    }
  return nothing ;
  }
BOOL IntFldList::EnableNewContext()
  {
  return FALSE ;
  }
void IntFldList::OnDestroy()
  {
  if (jlst != NULL) DestroyWindow (jlst->hWnd);
  if (jWnd != NULL) DestroyWindow (jWnd->hWnd);
  if (FileName != NULL) FreeGlobMem (FileName);
  MyProfFlush ();
  }
LPSTR IntFldList::GetResource (int Column)
  {
  return "no\0yes\0\0";
  }
BOOL IntFldList::EnableInput ()
  {
  return TRUE ;
  }
LPVOID IntFldList::GetFirstContext()
  {
  if (BaseContext != NULL) {
    ifl.td = LPTABLEDEF (BaseContext);
    ifl.ti = LPINTTABLE (ifl.td->GetDLLDef());
    ifl.TableNr = 0;
    ifl.VarNr = -1;
    if (ifl.TableNr < ifl.ti->AnzTables) 
      return &ifl ;
    else {
      GetTableAdmin()->FreeTable (ifl.td->GetTableID(),ifl.td->GetVersion());
      return NULL ;
      }
    }
  return NULL ;
  }
LPVOID IntFldList::GetNextContext(LPVOID oldConext)
  {
  ifl.VarNr ++ ;
  LPVOID res = &ifl;
  LPPTABLE p = ifl.ti->GetTableByNum(ifl.TableNr);
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (p->tRef.TableNr,p->tRef.Version);
  if (ifl.VarNr >= td->GetAnzVars()) {
    ifl.TableNr ++ ;
    ifl.VarNr = -1 ;
    if (ifl.TableNr >= ifl.ti->AnzTables) res = NULL ;
    }
  GetTableAdmin()->FreeTable (p->tRef.TableNr,p->tRef.Version);
  if (res == NULL)
    GetTableAdmin()->FreeTable (ifl.td->GetTableID(),ifl.td->GetVersion());
  return res;
  }
LPSTR IntFldList::GetMenuName()
  {
  return "IFLMENU" ;
  }
LPSTR IntFldList::ProfBase()
  {
  return "ILST" ;
  }
int IntFldList::GetColWidth(int Column)
  {
  if (ColWidth == NULL) {
    ColWidth = (int FAR *) GetGlobMem (sizeof(int) * AnzColumns());
    for (int i = 0 ; i < AnzColumns() ; i++)
      ColWidth[i] = -1;
    }
  if (ColWidth[Column] == -1) {
    char wstring[32];
    wsprintf (wstring,"Width%d",Column);
    int def = 1000;
    switch (Column) {
      case 0 :
        def = 800 ;
        break ;
      case 1 :
        def = 3000 ;
        break ;
      case 2 :
        def = 800 ;
        break ;
      case 3 :
        def = 3000 ;
        break ;
      }
    ColWidth[Column] = GetProfInt (wstring,def);
    }
  return ColWidth[Column];
  }
void IntFldList::OnCommand (WORD wP)
  {
  switch (wP) {
    case 100 :
      jlst->Show ();
      break ;
    case 111 :
      Attribute ();
      break ;
    case 110 :
      Store ();
      break ;
    }
  }

int IntFldList::GetTableNr (LPSTR Alias)
  {
  char actname[64];
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((GetFieldContent (actname,h,3)) && (lstrcmp (actname,Alias) == 0)) {
      int tnr = -1;
      GetFieldWord (actname,h,0,TRUE);
      sscanf (actname,"%d",&tnr);
      return tnr;
      }
    }
  return -1;
  }

LPFLDLINE IntFldList::GetVarLine (int tnr,WORD VarID,BOOL FAR *allSelected,LPSTR prefix)
  {
  *allSelected = FALSE ;
  char instr[32];
  int VarFromTable = -1,tx ;
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((GetFieldWord (instr,h,0,TRUE)) && (sscanf (instr,"%d",&tx)) &&
        (tx == tnr)) {
      if (VarFromTable == -1) {
        if (*allSelected = ((GetFieldRes (instr,h,2,TRUE)) && (lstrcmp (instr,yes) == 0)))
          GetFieldContent (prefix,h,3);
        }
      else {
        if (VarFromTable == int(VarID)) return h;
        }
      VarFromTable ++ ;
      }
    }
  return NULL;
  }

LPSTR IntFldList::GetRealVarName (int tnr,WORD VarID,LPSTR res)
  {
  BOOL allSelected;
  char instring[32];
  LPFLDLINE h = GetVarLine (tnr,VarID,&allSelected,instring);
  GetAliasName (res,h);
  return res;
  }

BOOL IntFldList::AllVarsHere (int tnr,int AnzVars,WORD FAR *VarIDs)
  {
  BOOL res = TRUE ;
  BOOL allSelected;
  char instr[32];
  for (int i = 0 ; ((i < AnzVars) && (res)) ; i++) {
    LPFLDLINE h = GetVarLine (tnr,VarIDs[i],&allSelected,instr);
    res = ((allSelected) || ((GetFieldRes (instr,h,2,TRUE)) && (lstrcmp (instr,yes) == 0)));
    }
  return res;
  }
void IntFldList::AddTable (int TableNum,LPSTR TableName)
  {
  BOOL found;
  WORD Version;
  WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
  LPTABLEDEF td = GetTableAdmin()->GetTableDef (TableID,Version);
  LPFLDLINE firstNew = NULL;
  for (int i = -1 ; i < td->GetAnzVars() ; i++) {
    LPFLDLINE h = Enlarge (NULL);
    if (firstNew == NULL) firstNew = h;
    ActiveLine = h;
    char str[32];
    wsprintf (str,"%d",TableNum);
    ModifyContent (h,0,str);
    if (i == -1) {
      ModifyContent (h,1,"*");
      ModifyContent (h,2,yes);
      }
    else {
      ModifyContent (h,1,td->GetVarDef(i)->GetName());
      ModifyContent (h,2,no);
      }
    }
  AllAliasChanged (firstNew);
  if (TableNum > 0) {
    jlst->AddTable (TableNum,TableName);
    }
  GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
  }

IntFldList FAR *_actIntDlgLst;
extern LPSTR GetEdText (HWND hWnd,WORD Id,LPSTR old);
DLLExport BOOL _export FAR PASCAL IntAttribProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  switch (msg) {
    case WM_INITDIALOG :
      SetDlgItemText (hWnd,101,_actIntDlgLst->Caption);
      SetDlgItemText (hWnd,104,_actIntDlgLst->FileName);
      return TRUE ;
      break ;
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          {
          _actIntDlgLst->Caption = GetEdText (hWnd,101,_actIntDlgLst->Caption);
          _actIntDlgLst->FileName = GetEdText (hWnd,104,_actIntDlgLst->FileName);
          if ((_actIntDlgLst->Caption != NULL) && (_actIntDlgLst->FileName != NULL)) {
            EndDialog (hWnd,TRUE);
            }
          return TRUE ;
          }
          break ;
        case IDCANCEL :
          EndDialog (hWnd,FALSE);
          return TRUE ;
          break ;
        }
      break ;
    }
  return FALSE ;
  }

extern HINSTANCE MyInstance;
void IntFldList::Attribute()
  {
  _actIntDlgLst = this ;
  DLGPROC dlgproc = DLGPROC (MakeProcInstance (FARPROC(IntAttribProc),MyInstance));
  DialogBox (MyInstance,"ATTRIBUTE",hWnd,dlgproc);
  FreeProcInstance (dlgproc);
  }

void IntFldList::DelTable(int TableNum)
  {
  BOOL found = FALSE;
  char instring[32];
  int tnr;
  for (LPFLDLINE h = FirstLine ; h != NULL ; ) {
    LPFLDLINE n = h->Next ;
    if ((GetFieldWord (instring,h,0,TRUE)) && (sscanf (instring,"%d",&tnr)) && (tnr == TableNum)) {
      ActiveLine = RemoveLine (h);
      found = TRUE ;
      }
    else {
      if (found) {
        if ((GetFieldWord (instring,h,0,TRUE)) && (sscanf (instring,"%d",&tnr))) {
          wsprintf (instring,"%d",tnr-1);
          ModifyContent (h,0,instring);
          }
        }
      }
    h = n ;
    }
  jlst->DelTable (TableNum);
  }

extern int GetVarsforRI(LPCLRIDEF ri,WORD FAR *rivars);
LPFLDLINE IntFldList::CheckPrimary ()
  {
  char instr[64];
  int tnr,oldtnr = -1;
  BOOL SkipTable ;
  WORD rivars[32],VarNr;
  int AnzVarsToCheck;
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((GetFieldWord (instr,h,0,TRUE)) && (sscanf (instr,"%d",&tnr)) &&
              (tnr != oldtnr)) {
      if ((GetFieldRes (instr,h,2,TRUE)) && (lstrcmp (instr,yes) == 0))
        SkipTable = TRUE ;
      else {
        BOOL found;
        WORD Version;
        WORD TableID = GetTableAdmin()->GetTableID (NULL,jWnd->GetTableName (tnr),&found,&Version);
        LPTABLEDEF td = GetTableAdmin()->GetTableDef (TableID,Version);
        if (td->GetAnzRIDefs () > 0) {
          WORD rivars[32];
          AnzVarsToCheck = GetVarsforRI (td->GetRIDef (0),rivars);
          }
        else
          AnzVarsToCheck = 0 ;
        GetTableAdmin()->FreeTable (TableID,Version);
        SkipTable = FALSE ;
        VarNr = 0 ;
        }
      oldtnr = tnr;
      }
    else {
      if (!SkipTable) {
        BOOL found = FALSE ;
        for (int i = 0 ; i < AnzVarsToCheck ; i++)
          if (VarNr == rivars[i]) found = TRUE ;
        if (found) {
          if ((!GetFieldRes (instr,h,2,TRUE)) || (lstrcmp (instr,yes) != 0))
            return h;
          }
        VarNr ++ ;
        }
      }
    }
  return NULL;
  }

LPFLDLINE IntFldList::CheckDuplicate ()
  {
  char instr[64];
  int tnr,oldtnr = -1;
  BOOL CheckWhole;
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((GetFieldWord (instr,h,0,TRUE)) && (sscanf (instr,"%d",&tnr)) && (tnr != oldtnr)) {
      CheckWhole = ((GetFieldRes (instr,h,2,TRUE)) && (lstrcmp (instr,yes) == 0));
      oldtnr = tnr;
      }
    else {
      if ((CheckWhole) || ((GetFieldRes (instr,h,2,TRUE)) && (lstrcmp (instr,yes) == 0))) {
        GetFieldContent (instr,h,3);
        if (!IsNameAllowed (instr,h)) return h;
        }
      }
    }
  return NULL;
  }

static char *IDDEXT = "IDD";
void IntFldList::GetOutFileName (LPSTR fName)
  {
  lstrcpy (fName,FileName);
  for (LPSTR h = fName ; *h ; h++) {
    if (*h == '.') {
      lstrcpy (h+1,IDDEXT);
      break ;
      }
    }
  if (*h == '\0') {
    *h = '.' ;
    lstrcpy (h+1,IDDEXT);
    }
  }

extern BOOL GenIntScript (HWND hWnd,LPSTR fname);
extern void GetPrePostParts (LPSTR Caption,LPSTR fName,GLOBALHANDLE FAR *PreText,GLOBALHANDLE FAR *PostText);
extern void TestIntTable (LPSTR Caption,WORD Id);
void WriteToFile (HFILE fm,GLOBALHANDLE hGtxt)
  {
  LPSTR res =(LPSTR)GlobalLock (hGtxt);
  _lwrite (fm,res + 2 * sizeof(WORD),*((WORD FAR *) res)-2*sizeof(WORD));
  GlobalUnlock (hGtxt);
  }

BOOL IntFldList::Store ()
  {
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
  if ((FileName != NULL) && (Caption != NULL)) {
    // Einige Syntax - Checks
    char instring[256],str1[64];
    FldList FAR *eList;
    LPFLDLINE eLine = CheckPrimary ();
    if (eLine == NULL) {
      eLine = CheckDuplicate ();
      if (eLine == NULL) {
        eLine = jlst->CheckWholeJoins ();
        if (eLine != NULL)
          lstrcpy (str1,"Join nicht definiert") , eList = jlst;
        }
      else
        lstrcpy (str1,"Name schon verwendet") , eList = this;
      }
    else
      lstrcpy (str1,"Primärschlüsselsegment fehlt") , eList = this;
    if (eLine != NULL) {
      Fehler (str1);
      eList->ActiveLine = eLine;
      eList->ActiveCol = 0;
      eList->Show();
      SetFocus (eList->hWnd);
      SetCursor (oldCursor);
      return FALSE ;
      }

    int oldtnr = -1,tnr;
    GLOBALHANDLE hGtxt = InitializeHandleForPush ();
    wsprintf (instring,"View %s = {\r\n",Caption);
    PushDataToHandle (instring,lstrlen(instring),&hGtxt);
    BOOL SkipTable ;
    for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
      if ((GetFieldWord (instring,h,0,TRUE)) && (sscanf (instring,"%d",&tnr)) &&
                (tnr != oldtnr)) {
        if ((oldtnr >= 0) && (!SkipTable)) {
          lstrcpy (instring,"    };\r\n");
          PushDataToHandle (instring,lstrlen(instring),&hGtxt);
          }
        wsprintf (instring,"  table %s",jWnd->GetTableName (tnr));
        PushDataToHandle (instring,lstrlen(instring),&hGtxt);
        if (tnr > 0) {
          *instring = ' ';
          jlst->GetJoinText (instring+1,tnr);
          PushDataToHandle (instring,lstrlen(instring),&hGtxt);
          }
        if ((GetFieldRes (instring,h,2,TRUE)) && (lstrcmp (instring,yes) == 0)) {
          SkipTable = TRUE ;
          if (GetFieldContent (str1,h,3))
            wsprintf (instring," select all alias %s;\r\n",LPSTR(str1));
          else
            lstrcpy (instring," select all;\r\n");
          }
        else {
          lstrcpy (instring," {\r\n");
          SkipTable = FALSE ;
          }
        PushDataToHandle (instring,lstrlen(instring),&hGtxt);
        oldtnr = tnr;
        }
      else {
        if (!SkipTable) {
          if ((GetFieldRes (instring,h,2,TRUE)) && (lstrcmp (instring,yes) == 0)) {
            lstrcpy (instring,"    ");
            PushDataToHandle (instring,lstrlen(instring),&hGtxt);
            GetFieldContent (instring,h,1);
            PushDataToHandle (instring,lstrlen(instring),&hGtxt);
            if (GetFieldContent (str1,h,3)) {
              wsprintf (instring," = %s",LPSTR(str1));
              PushDataToHandle (instring,lstrlen(instring),&hGtxt);
              }
            lstrcpy (instring,";\r\n");
            PushDataToHandle (instring,lstrlen(instring),&hGtxt);
            }
          }
        }
      }
    if (!SkipTable) {
      lstrcpy (instring,"    };\r\n");
      PushDataToHandle (instring,lstrlen(instring),&hGtxt);
      }
    lstrcpy (instring,"  }");
    PushDataToHandle (instring,lstrlen(instring),&hGtxt);
    OFSTRUCT Of;
    char fName[128];
    GetOutFileName (fName);
    GLOBALHANDLE PreText = 0,PostText = 0;
    GetPrePostParts (Caption,fName,&PreText,&PostText);
    HFILE fm = OpenFile (fName,&Of,OF_CREATE);
    if ((PreText == 0) && (PostText == 0)) {
      lstrcpy (instring,"\r\nend");
      PushDataToHandle (instring,lstrlen(instring),&hGtxt);
      }
    if (fm > 0) {
      if (PreText)
        WriteToFile (fm,PreText);
      WriteToFile (fm,hGtxt);
      if (PostText)
        WriteToFile (fm,PostText);
      _lclose (fm);
      }
    else
      Fehler ("Ausgabedatei kann nicht geöffnet werden");
      
    if (PreText)
      GlobalFree (PreText);
    GlobalFree (hGtxt);
    if (PostText)
      GlobalFree (PostText);

    if (fm) {
      GenIntScript (hWnd,fName);
      }
    SendMessage (hWnd,WM_SETTEXT,0,LPARAM(Caption));

    SetCursor (oldCursor);
    return TRUE ;
    }
  else {
    Fehler ("Name der Ausgabedatei nicht bekannt");
    SetCursor (oldCursor);
    return FALSE ;
    }
  SetCursor (oldCursor);
  }

// Aufbau der internen Tabelle
extern HMENU GetTbLstMenu ();
HMENU GetIntLstMenu ()
  {
  return GetTbLstMenu();
  }
void WorkOnIntTable (LPSTR TableName,HWND hWParent)
  {
  WndDef wd[3];
  wd[0].x0 = wd[1].x0 = 400 ;
  wd[2].x0 = 0 ;
  wd[0].x1 = wd[1].x1 = 1000 ;
  wd[2].x1 = 400 ;
  wd[0].y0 = 300 ;  wd[0].y1 = 1000 ;
  wd[1].y0 = 0   ;  wd[1].y1 = 300 ;
  wd[2].y0 = 0   ;  wd[2].y1 = 1000 ;

  if (CreateChildWindowsInMDI (TableName,3, wd, 0L, GetIntLstMenu())) {
    HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
    BOOL found;
    WORD Version;
    WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
    if (found) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (TableID,Version);
      IntFldList FAR *lst = new IntFldList (hWParent,td,td->GetName());
      LPSTR FName = td->GetFileName();
      if (FName != NULL) {
        lst->FileName = LPSTR(GetGlobMem (lstrlen(FName)+1));
        lstrcpy (lst->FileName,FName);
        }
      lst->Create (wd[0].hWnd);

      lst->jlst = new JoinList (lst->hWnd,td,td->GetName());
      lst->jlst->Create (wd[1].hWnd);
      lst->jlst->Show ();

      LPINTTABLE ti = LPINTTABLE (td->GetDLLDef());
      lst->jWnd = new jShow (lst);
      lst->jWnd->Create (wd[2].hWnd);
      lst->jWnd->Show ();
      int x = 1000 ; 
      for (int i = 0 ; i < int(ti->AnzTables) ; i++) {
        LPPTABLE p = ti->GetTableByNum(i);
        LPTABLEDEF tp = GetTableAdmin()->GetTableDef (p->tRef.TableNr,p->tRef.Version);
        lst->jWnd->NewTable (tp->GetName(),x,1000,0,0);
        x += 2500 ;
        GetTableAdmin()->FreeTable (p->tRef.TableNr,p->tRef.Version);
        }
      lst->jWnd->CheckRI ();
      lst->Show ();
      }
    SetCursor (oldCursor);
    }
  }

void CreateNewIntTableDef (HWND hWParent)
  {
  WndDef wd[3];
  wd[0].x0 = wd[1].x0 = 400 ;
  wd[2].x0 = 0 ;
  wd[0].x1 = wd[1].x1 = 1000 ;
  wd[2].x1 = 400 ;
  wd[0].y0 = 300 ;  wd[0].y1 = 1000 ;
  wd[1].y0 = 0   ;  wd[1].y1 = 300 ;
  wd[2].y0 = 0   ;  wd[2].y1 = 1000 ;

  if (CreateChildWindowsInMDI ("<unbekannt>",3, wd, 0L,GetIntLstMenu())) {
    HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
    IntFldList FAR *lst = new IntFldList (hWParent,NULL,"<unbekannt>");
    lst->Create (wd[0].hWnd);

    lst->jlst = new JoinList (lst->hWnd,NULL,"<unbekannt>");
    lst->jlst->Create (wd[1].hWnd);
    lst->jlst->Show ();

    lst->jWnd = new jShow (lst);
    lst->jWnd->Create (wd[2].hWnd);
    lst->jWnd->Show ();

    lst->Show ();
    SetCursor (oldCursor);
    }
  }

