//
//  Bearbeiten der Zugriffe fuer Joins in internen Tabellen
//  
// $Header:   P:/marille/clinicum/restool/rev/jlst.cpv   1.6   26 Nov 1996 08:10:12   HANNES  $
// $Log:   P:/marille/clinicum/restool/rev/jlst.cpv  $
// 
//    Rev 1.6   26 Nov 1996 08:10:12   HANNES
// Automatischer Update
// 
//    Rev 1.5   21 Oct 1996 18:57:12   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.4   24 Mar 1996 12:16:36   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.3   02 Feb 1996 10:50:34   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   26 Apr 1995 15:27:06   HANNES
// 
//    Rev 1.1   24 Apr 1995 11:34:34   HANNES
//  
// 
//    Rev 1.0   16 Feb 1995 12:41:12   HANNES
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
#include "riwnd.hpp"
#include "jlst.hpp"

void JoinList::Save (LPFLDLINE line,int column)
  {
  IntFldList FAR *lst = (IntFldList FAR *) GetWindowLong (hWndParent,GWL_FLDLIST);
  lst->jWnd->DelLineDefs();
  lst->jWnd->CheckRI();
  }
int JoinList::AnzColumns()
  {
  return 5;
  }
DWORD JoinList::GetColMode(int Column)
  {
  switch (Column) {
    case 1 :
      return FM_LSELECTION | FM_NOSELECTION ;  // ri
    case 2 :
      return FM_LSELECTION | FM_NOSELECTION ;  // inner / outer
    case 3 :
      return FM_SINGLELINE | FM_NOSELECTION ;  // Kommando
    case 4 :
      return FM_SINGLELINE | FM_NOSELECTION ;  // Parameter
    }
  return FM_OUTLINEONLY ;
  }
int JoinList::GetX0()
  {
  return 400 ;
  }
int JoinList::GetFormat()
  {
  return 2 ;
  }
LPSTR JoinList::GetHdString (int Column)
  {
  switch (Column) {
    case 0 :
      return "\\m1T.Nr";
    case 1 :
      return "\\m1Typ";
    case 2 :
      return "\\m1Verb.";
    case 3 :
      return "\\m1Command";
    case 4 :
      return "\\m1Parameter";
    }
  return "";
  }
struct JoinListContext {
  LPTABLEDEF td;
  int TableNr;
  };
static char *ri = "aus RI" ;
static char *extra = "extra" ;
BOOL IsNullAllowed (LPTABLEDEF ti,LPCLRIDEF r)
  {
  JoinDef FAR *jr = r->GetJDef();
  for (WORD i = 0 ; i < r->AnzSegs ; i++)
    if ((ti->GetVarDef(jr->VarID[i])->Property & VPROP_NOTNULL) == 0) return TRUE ; 
  return FALSE ;
  }
LPSTR JoinList::GetFieldString (LPVOID Context,int Column)
  {
  JoinListContext FAR *c = (JoinListContext FAR *) Context;
  static char res[64];
  static char *nothing = "" ;
  static char *inner = "inner" ;
  static char *outer = "outer" ;
  switch (Column) {
    case 0 :
      wsprintf (res,"%d",c->TableNr);
      return res;
      break ;
    case 1 :
      {
      LPCLRIDEF r = c->td->GetRIDef (c->TableNr-1);
      switch (r->Type) {
        case CLJR_RIEXTENDED :
        case CLJR_RISTANDARD :
          return ri ;
          break ;
        case CLJR_NEW :
          return extra ;
          break ;
        }
      return nothing ;
      }
      break ;
    case 2 :
      {
      LPCLRIDEF r = c->td->GetRIDef (c->TableNr-1);
      switch (r->TypeOfJoin) {
        case CLJT_USEDEFAULT   :
          if ((r->Type == CLJR_RISTANDARD) || (r->Type == CLJR_NEW))
            return (IsNullAllowed (c->td,r)) ? outer : inner ;
          else
            return outer ;
          break ;
        case CLJT_USEOUTERJOIN :
          return outer ;
          break ;
        case CLJT_USEINNERJOIN :
          return inner ;
          break ;
        }
      }
      break ;
    case 3 :
      {
      LPCLRIDEF r = c->td->GetRIDef (c->TableNr-1);
      switch (r->Type) {
        case CLJR_RIEXTENDED :
          wsprintf (res,"call %s",r->name);
          return res;
          break ;
        case CLJR_RISTANDARD :
        case CLJR_NEW :
          return r->name;
        }
      return nothing ;
      }
      break ;
    case 4 :
      {
      LPCLRIDEF r = c->td->GetRIDef (c->TableNr-1);
      *res = '\0';
      JoinDef FAR *jr = r->GetJDef();
      for (WORD i = 0 ; i < r->AnzSegs ; i++) {
        lstrcat (res,c->td->GetVarDef(jr->VarID[i])->GetName());
        if (i < r->AnzSegs - 1) lstrcat (res,",");
        }
      return res;
      }
      break ;
    }
  return nothing ;
  }
BOOL JoinList::EnableNewContext()
  {
  return FALSE ;
  }
void JoinList::OnDestroy()
  {
  MyProfFlush ();
  }
LPSTR JoinList::GetResource (int Column)
  {
  if (Column == 1)
    return "aus RI\0extra\0";
  else
    return "inner\0outer\0" ;
  }
BOOL JoinList::EnableInput ()
  {
  return TRUE ;
  }
static struct JoinListContext ifl;
LPVOID JoinList::GetFirstContext()
  {
  if (BaseContext != NULL) {
    ifl.td = LPTABLEDEF (BaseContext);
    ifl.TableNr = 1;
    LPINTTABLE ti = LPINTTABLE (ifl.td->GetDLLDef());
    if (int(ti->AnzTables) > ifl.TableNr)
      return &ifl;
    else
      return NULL ;
    }
  return NULL ;
  }
LPVOID JoinList::GetNextContext(LPVOID oldConext)
  {
  ifl.TableNr ++ ;
  LPINTTABLE ti = LPINTTABLE (ifl.td->GetDLLDef());
  if (int(ti->AnzTables) > ifl.TableNr)
    return &ifl;
  else
    return NULL ;
  }
LPSTR JoinList::GetMenuName()
  {
  return "JMENU" ;
  }
LPSTR JoinList::ProfBase()
  {
  return "JLST" ;
  }
int JoinList::GetColWidth(int Column)
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
        def = 1200 ;
        break ;
      case 2 :
        def = 800 ;
        break ;
      case 3 :
        def = 2000 ;
        break ;
      case 4 :
        def = 3000 ;
        break ;
      }
    ColWidth[Column] = GetProfInt (wstring,def);
    }
  return ColWidth[Column];
  }
void JoinList::OnCommand (WORD wP)
  {
  }

BOOL JoinList::AllowClose()
  {
  SetFocus (hWndParent);
  Hide ();
  return FALSE ;
  }

BOOL JoinList::AllowChange (LPFLDLINE h,int Column)
  {
  if (Column == 0) return FALSE ;
  if (Column > 2) {
    char selection[32];
    if ((GetFieldRes (selection,h,1,TRUE)) && (lstrcmp (selection,ri) == 0)) 
      return FALSE ;
    }
  return TRUE ;
  }

/*----< Implementierung der Spezialfunktionen >--------*/
int GetParams (LPSTR str,LPSTR FAR *allstrs)
  {
  int j = 0 ;
  for (LPSTR h = str ; *h ; h++) {
    if (h == str) allstrs[j++] = h ;
    if (*h == ',') *h = '\0', str = h + 1 ;
    }
  for (int i = 0 ; i < j ; i++) {
    for ( ; ((!IsCharAlpha(*(allstrs[i]))) && (*(allstrs[i]) != '_')) ; allstrs[i] ++ ) ;
    for (LPSTR h = allstrs[i] + lstrlen(allstrs[i]) ; 
                            ((h >= allstrs[i]) && (!IsCharAlphaNumeric(*h)) && (*(allstrs[i]) != '_')) ; h--)
      *h = '\0' ;
    }
  return j ;
  }

void JoinList::AliasChanged (LPSTR old,LPSTR nw)
  {
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    char str[256],nstr[256];
    GetFieldSent (str,h,4);
    LPSTR allstrs[32];
    int AnzStrs = GetParams (str,allstrs);
    BOOL found = FALSE ;
    for (int i = 0 ; i < AnzStrs ; i++) {
      if (lstrcmp (allstrs[i],old) == 0) allstrs[i] = nw , found = TRUE ;
      }
    if (found) {
      cField FAR *f = h->GetField(4);
      *nstr = '\0';
      for (int i = 0 ; i < AnzStrs ; i++) {
        lstrcat (nstr,allstrs[i]);
        if (i < AnzStrs - 1) lstrcat (nstr,",");
        }
      RECT r1,r2;
      f->GetFieldRect (&r1, 0);
      *f = nstr;
      f->GetFieldRect (&r2, 0);
      Invalidate (h,&r1,TRUE);
      Invalidate (h,&r2,TRUE);
      }
    }
  }

int JoinList::GetSourceTableNr (LPFLDLINE h)
  {
  char str[256];
  GetFieldSent (str,h,4);
  LPSTR allstrs[32];
  int AnzStrs = GetParams (str,allstrs);
  if (AnzStrs > 0) {
    IntFldList FAR *lst = (IntFldList FAR *) GetWindowLong (hWndParent,GWL_FLDLIST);
    return lst->GetTableNr (allstrs[0]);
    }
  else return -1;
  }

int JoinList::GetDestTableNr (LPFLDLINE h)
  {
  int tnr;
  char inword[20];
  if ((GetFieldWord (inword,h,0,TRUE)) && (sscanf (inword,"%d",&tnr)))
    return tnr;
  else
    return -1;
  }

void PushRIDef (LPCLRIDEF r,LPCLRIDEF FAR *rid,int FAR *anz)
  {
  rid[*anz] = r ;
  *anz ++ ;
  }

BOOL IsRIDoneUntil (LPCLRIDEF r,LPCLRIDEF FAR *rid,int anz)
  {
  for (int i = 0 ; i < anz ; i++) {
    if (rid[i] == r) return TRUE ;
    }
  return FALSE ;
  }

int GetVarsforRI(LPCLRIDEF ri,WORD FAR *rivars)
  {
  if (ri->Type == CLKR_EXTENDED) {
    ExtendedRI FAR *ei = ri->GetERI();
    WORD FAR *v = ei->GetVarIDList();
    for (int i = 0 ; i < int(ri->AnzSegs) ; i++) {
      rivars[i] = v[i];
      }
    }
  else {
    StandardRI FAR *si = ri->GetSRI();
    for (int i = 0 ; i < int(ri->AnzSegs) ; i++) {
      rivars[i] = si->VarID;
      si = si->GetNextSRI();
      }
    }
  return ri->AnzSegs;
  }

void JoinList::SetRIDef (LPFLDLINE h,int tnr,LPCLRIDEF rid,LPTABLEDEF tsource)
  {
  char command[256];
  switch (rid->Type) {
    case CLKR_EXTENDED :
      wsprintf (command,"call %s",rid->GetERI()->AccessName);
      break ;
    case CLKR_STANDARD :
      {
      BOOL doinner = TRUE ;
      JoinDef FAR *jr = rid->GetJDef();
      for (int i = 0 ; i < int(rid->AnzSegs) ; i++)
        if ((tsource->GetVarDef(jr->VarID[i])->Property & VPROP_NOTNULL) == 0) doinner = FALSE ; 
      if (doinner)
        ModifyContent (h,2,"inner");
      else
        ModifyContent (h,2,"outer");
      *command = '\0';
      StandardRI FAR *sri = rid->GetSRI();
      for (i = 0 ; i < int(rid->AnzSegs) ; i++) {
        char hlp[43];
        wsprintf (hlp,"%s = %%%d",sri->ForeignField,i+1);
        sri = sri->GetNextSRI();
        lstrcat (command,hlp);
        if (i < int(rid->AnzSegs) - 1) lstrcat (command," && ");
        }
      }
      break ;
    }
  ModifyContent (h,3,command);
  WORD rivars[32];
  int AnzVars = GetVarsforRI(rid,rivars);
  IntFldList FAR *lst = (IntFldList FAR *) GetWindowLong (hWndParent,GWL_FLDLIST);
  *command = '\0';
  for (int i = 0 ; i < AnzVars ; i++) {
    char str[64];
    lstrcat (command,lst->GetRealVarName (tnr,rivars[i],str));
    if (i < AnzVars - 1) lstrcat (command,",");
    }
  ModifyContent (h,4,command);
  }

void JoinList::CheckJoins ()
  {
  char inword[30],selection[30];
  LPCLRIDEF usedrid[32];
  int anzridused = 0;
  WORD rivars[32];
  IntFldList FAR *lst = (IntFldList FAR *) GetWindowLong (hWndParent,GWL_FLDLIST);
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    BOOL RIfound = FALSE ;
    if ((GetFieldRes (inword,h,1,TRUE)) && (lstrcmp (inword,ri) == 0)) {
      int tnr;
      GetFieldWord (inword,h,0,TRUE); sscanf (inword,"%d",&tnr);
      if ((GetFieldRes (selection,h,1,TRUE)) && (lstrcmp (selection,ri) == 0)) {
        LPSTR DestTable = lst->jWnd->GetTableName (tnr);
        for (int i = 0 ; i < tnr ; i++) {
          LPSTR SourceTable = lst->jWnd->GetTableName (i);
          BOOL found;
          WORD Version;
          WORD TableID = GetTableAdmin()->GetTableID (NULL,SourceTable,&found,&Version);
          LPTABLEDEF td = GetTableAdmin()->GetTableDef (TableID,Version);
          for (int j = 0 ; j < td->GetAnzRIDefs() ; j++) {
            LPCLRIDEF rid = td->GetRIDef(j);
            if ((lstrcmp (rid->name,DestTable) == 0) && (!IsRIDoneUntil (rid,usedrid,anzridused)) &&
                (lst->AllVarsHere(i,GetVarsforRI(rid,rivars),rivars))) {
              SetRIDef (h,i,rid,td);
              PushRIDef (rid,usedrid,&anzridused);
              RIfound = TRUE ;
              break ;
              }
            }
          GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
          }
        }
      }
    else
      RIfound = TRUE ;
    if (!RIfound) {
      ModifyContent (h,2,"");
      ModifyContent (h,3,"");
      ModifyContent (h,4,"");
      }
    }
  lst->jWnd->DelLineDefs();
  lst->jWnd->CheckRI();
  }

void JoinList::AddTable (int TableNum,LPSTR TableName)
  {
  LPFLDLINE h = Enlarge (NULL);
  ActiveLine = h;
  char str[32];
  wsprintf (str,"%d",TableNum);
  ModifyContent (h,0,str);
  ModifyContent (h,1,ri);
  CheckJoins ();
  }

void JoinList::DelTable(int TableNum)
  {
  BOOL found = (TableNum == 0);
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
  CheckJoins ();
  }

LPSTR JoinList::GetJoinText (LPSTR buffer,int tnr)
  {
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    int nr;
    char instr[32];
    if ((GetFieldWord (instr,h,0,TRUE)) && (sscanf (instr,"%d",&nr)) && (nr == tnr)) {
      if ((GetFieldRes (buffer,h,1,TRUE)) && (lstrcmp (buffer,extra) == 0)) {
        GetFieldRes (buffer,h,2,TRUE);
        if (lstrcmp (buffer,"inner") == 0)
          lstrcpy (buffer,"join inner with \"");
        else
          lstrcpy (buffer,"join outer with \"");
        LPSTR s = buffer + lstrlen(buffer);
        GetFieldSent (s,h,3);
        s = s + lstrlen(s);
        lstrcpy (s,"\" (");
        s = s + lstrlen(s);
        GetFieldSent (s,h,4);
        s = s + lstrlen(s);
        lstrcpy (s,")");
        }
      else {
        GetFieldRes (buffer,h,2,TRUE);
        if (lstrcmp (buffer,"inner") == 0)
          lstrcpy (buffer,"join inner with \"");
        else
          lstrcpy (buffer,"join outer with \"");
        }
      }
    }
  return buffer;
  }

LPFLDLINE JoinList::CheckWholeJoins ()
  {
  char instr[256];
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if ((!GetFieldSent (instr,h,3)) || (!GetFieldSent (instr,h,4))) return h;
    }
  return NULL;
  }

