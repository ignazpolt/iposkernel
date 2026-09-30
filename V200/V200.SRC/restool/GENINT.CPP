	///////////////////////////////////////////////////////////////////
//  Erzeugen von internen Tabellen mit dem Tool
///////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/restool/rev/genint.cpv   1.5   05 Oct 1998 11:26:28   Gerhold  $
//  $Log:   P:/marille/clinicum/restool/rev/genint.cpv  $
// 
//    Rev 1.5   05 Oct 1998 11:26:28   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.4   28 Aug 1997 15:49:26   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.3   02 Feb 1996 10:50:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   10 Jan 1995 17:32:08   HANNES
// Syntaxkorrektur fuer 8er Compiler
// 
//    Rev 1.1   02 Jan 1995 09:30:24   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.0   24 Jun 1994 16:54:46   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
#define MODULENUM 102
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"

//#include "subclass.hpp"

extern HINSTANCE MyInstance;

struct FAR VarList {
  VarList FAR *   Next;
  LPTABLEDEF      Ref;
  WORD            TableNr;
  WORD            VarNum;
  BOOL            doSel;
  };
typedef VarList FAR *LPVARLIST;
TableEntry FAR *aList;
VarList FAR *vList;
LPSTR TableName;
LPSTR VarPrefix;
LPSTR _fName;

#define _OUT _lwrite (fi,outtxt,lstrlen(outtxt));

char GetPostInd (LPVARLIST x)
  {
  WORD SameName = 0;
  LPSTR Name = x->Ref->GetVarDef(x->VarNum)->GetName();
  for (LPVARLIST h = vList ; h != NULL ; h = h->Next) {
    if (h->doSel) {
      if (h == x) break;
      LPSTR oName = h->Ref->GetVarDef(h->VarNum)->GetName();
      if ((h->Ref != x->Ref) && (lstrcmp (Name,oName) == 0))
        SameName ++;
      }
    }
  if (SameName != 0) return 'a' + char(SameName) - 1;
  else               return '\0';
  }

void WriteFile (HWND hDlg)
  {
  if (_fName != NULL) {
    char Tablename[128];
    GetDlgItemText (hDlg,ID_TABLENAME,Tablename,sizeof(Tablename));
    if (lstrlen(Tablename) < 1) {
      MessageBeep (0); return;
      }
    char Varprefix[128];
    GetDlgItemText (hDlg,ID_VARPREFIX,Varprefix,sizeof(Varprefix));
    if (lstrlen(Varprefix) < 1) {
      MessageBeep (0); return;
      }
    OFSTRUCT Of;
    int fi = OpenFile (_fName,&Of,OF_WRITE | OF_CREATE);
    if (fi >= 0) {
      char outtxt[256];
      // Header 
      wsprintf (outtxt,"intern table %s {\r\n",LPSTR(Tablename));
      _OUT ;
      // Sortierung
      wsprintf (outtxt,"  sort ");
      _OUT ;
      BOOL firstDone = FALSE ;
      for (TableEntry FAR *te = aList ; te != NULL ; te = te->Next) {
        if (te->SelCount > 0) {
          if (firstDone) wsprintf (outtxt,",%s",te->td->GetName());
          else           wsprintf (outtxt,"%s",te->td->GetName()) , firstDone = TRUE;
          _OUT ;
          }
        }
      wsprintf (outtxt,";\r\n");
      _OUT ;
      LPTABLEDEF l = NULL ;
      WORD oNr = 0;
      // Die Zeilen im einzelnen
      firstDone = FALSE ;
      for (LPVARLIST h = vList ; h != NULL ; h = h->Next) {
        if (h->doSel) {
          char VarPostInd[2];
          VarPostInd[0] = GetPostInd (h);
          VarPostInd[1] = '\0';
          LPDLLENTRY e = GetDLLAdmin()->GetDLLEntry(h->Ref->GetDLLHandle());
          WORD mType = e->DataDict_GetMType (h->Ref->GetVarDef(h->VarNum)->GetDLLData());
          if ((h->Ref != l) || (h->TableNr != oNr)) {
            // Naechste Tabelle
            wsprintf (outtxt,"  NewTable ;\r\n");
            _OUT ;
            }
          if (!firstDone) {
            wsprintf (outtxt,"  %s %s_%s%s = %s as primary from %s ;\r\n",
                        GetRealMTypeName(mType),
                        LPSTR(Varprefix),
                        h->Ref->GetVarDef(h->VarNum)->GetName(),
                        LPSTR(VarPostInd),
                        h->Ref->GetVarDef(h->VarNum)->GetName(),
                        h->Ref->GetName()
                     );
            firstDone = TRUE ;
            }        
          else {
            if (h->TableNr > 0)
              wsprintf (outtxt,"  %s %s_%s%s%d = %s from %s ;\r\n",
                        GetRealMTypeName(mType),
                        LPSTR(Varprefix),
                        h->Ref->GetVarDef(h->VarNum)->GetName(),
                        LPSTR(VarPostInd),
                        h->TableNr,
                        h->Ref->GetVarDef(h->VarNum)->GetName(),
                        h->Ref->GetName()
                       );
            else
              wsprintf (outtxt,"  %s %s_%s%s = %s from %s ;\r\n",
                        GetRealMTypeName(mType),
                        LPSTR(Varprefix),
                        h->Ref->GetVarDef(h->VarNum)->GetName(),
                        LPSTR(VarPostInd),
                        h->Ref->GetVarDef(h->VarNum)->GetName(),
                        h->Ref->GetName()
                       );
            }
          _OUT ;
          l = h->Ref;
          oNr = h->TableNr;
          }
        }
      wsprintf (outtxt,"  };\r\n\r\nend\r\n");
      _OUT ;
      _lclose (fi);
      }
    else 
      MessageBeep (0); return;
    }
  else
    MessageBeep (0);
  }

DLLExport BOOL FAR PASCAL _export MWriteDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
//      SubClassElements (hDlg,MyInstance);
      if (TableName != NULL)
        SetDlgItemText (hDlg,ID_TABLENAME,TableName);
      if (VarPrefix != NULL)
        SetDlgItemText (hDlg,ID_VARPREFIX,VarPrefix);
      RetVal = TRUE ;
      break ;
/*
    case WM_CTLCOLOR :
      {
      LONG lres = GetCtlColor (hDlg,wP,lP,RetVal);
      if (RetVal)
        return BOOL (lres);   // ??? !!!! ???
      }
*/
    case WM_COMMAND :
      switch (wP) {
        case IDCANCEL :
          EndDialog (hDlg,TRUE);
          break ;
        case IDOK :
          WriteFile (hDlg);
          EndDialog (hDlg,TRUE);
          break ;
        }
      break ;
    }
  return RetVal;
  }

void FillVarList (HWND hDlg)
  {
  for (VarList FAR *h = vList ; h != NULL ; h = h->Next) {
    LPDLLENTRY e = GetDLLAdmin()->GetDLLEntry(h->Ref->GetDLLHandle());
    WORD mType = e->DataDict_GetMType (h->Ref->GetVarDef(h->VarNum)->GetDLLData());
    char outtxt[128];
    wsprintf (outtxt,"%s\t%s\t%d\t%s",GetMTypeName(mType),
                                 h->Ref->GetVarDef(h->VarNum)->GetName(),
                                 h->TableNr,
                                 h->Ref->GetName()
             );
    SendDlgItemMessage (hDlg,ID_LIST,LB_ADDSTRING,0,LONG(LPSTR(outtxt)));
    }
  }

LPVARLIST GetHead (LPVARLIST act,LPVARLIST FAR *p)
  {
  *p = NULL;
  if (vList == NULL) return NULL;
  if (act   == NULL) return vList;
  WORD       oldNr  = act->TableNr;
  LPTABLEDEF oldRef = act->Ref;
  for ( *p = act , act = act->Next ; act != NULL ; *p = act , act = act->Next) {
    if ((act->TableNr != oldNr) || (act->Ref != oldRef))
      break ;
    }
  return act;
  }

void AddTableToVarList (LPTABLEDEF r,WORD Nr,LPVARLIST a,LPVARLIST p)
  {
  for (WORD i = 0 ; i < WORD(r->GetAnzVars()) ; i++) {
    if (r->GetVarDef(i) != NULL) {
      LPVARLIST n = LPVARLIST (GetGlobMem (sizeof(*n)));
      n->Next = a;
      if (p != NULL) p->Next = n;
      else           vList   = n;
      n->Ref     = r;
      n->VarNum  = i;
      n->TableNr = Nr;
      p = n;
      }
    }
  }

void RemoveTableFromVarList (LPVARLIST a,LPVARLIST p)
  {
  LPTABLEDEF r = a->Ref;
  WORD Nr = 0;
  for ( ; a != NULL ; ) {
    if ((a->Ref != r) || (a->TableNr != Nr)) break;
    if (p != NULL) p->Next = a->Next;
    else           vList   = a->Next;
    LPVARLIST n = a->Next;
    FreeGlobMem (a);
    a = n;
    }
  }

void AddTableToVarList (LPTABLEDEF r,WORD Nr,LPTABLEDEF pt,WORD ptCount)
  {
  if (vList == NULL)
    AddTableToVarList (r,Nr,vList,NULL);
  else {
    if (Nr >= 1) {
      // Suchen, ob diese schon mal drinnen ist
      LPVARLIST a = NULL,p = NULL;
      for ( a = GetHead(a,&p) ; ; a = GetHead(a,&p)) {
        if ((a->Ref == r) && (a->TableNr == Nr - 1)) {
          // Dahinter bitte einfuegen
          a = GetHead (a,&p);
          AddTableToVarList (r,Nr,a,p);
          return ;
          }
        }
      WIN_ASSERT (FALSE);
      }
    else if (pt == NULL) {
      AddTableToVarList (r,Nr,vList,NULL);
      }
    else {
      // Die letzte von pt suchen
      LPVARLIST a = NULL,p = NULL;
      for ( a = GetHead(a,&p) ; ; a = GetHead(a,&p)) {
        if ((a->Ref == pt) && (a->TableNr == ptCount - 1)) {
          // Der naechste ist es
          a = GetHead (a,&p);
          AddTableToVarList (r,Nr,a,p);
          return ;
          }
        }
      WIN_ASSERT(FALSE);
      }
    }
  }

void RemoveTableFromVarList (LPTABLEDEF r,WORD Nr)
  {
  LPVARLIST a = NULL,p = NULL;
  for ( a = GetHead(a,&p) ; a != NULL ; a = GetHead(a,&p)) {
    if ((a->Ref == r) && (a->TableNr == Nr)) {
      RemoveTableFromVarList (a,p);
      return ;
      }
    }
  }

void FreeVarList ()
  {
  for ( ; vList != NULL ; ) {
    VarList FAR *n = vList->Next ; 
    FreeGlobMem (vList);
    vList = n;
    }
  }

void SyncronizeVarSels (HWND hDlg)
  {
  WORD i = 0;
  for (VarList FAR *h = vList ; h != NULL ; h = h->Next , i++) {
    BOOL state = BOOL(SendDlgItemMessage (hDlg,ID_LIST,LB_GETSEL,i,0L));
    h->doSel = state;
    }
  }

void InitializeVarSelStates (HWND hDlg)
  {
  WORD i = 0;
  for (VarList FAR *h = vList ; h != NULL ; h = h->Next , i++) {
    if (h->doSel)
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETSEL,TRUE,MAKELPARAM(i,0));
    }
  }

void SelectAll (HWND hDlg)
  {
  int count = int (SendDlgItemMessage (hDlg,ID_LIST,LB_GETCOUNT,0,0L));
  for (int i = 0 ; i < count ; i++)
    SendDlgItemMessage (hDlg,ID_LIST,LB_SETSEL,TRUE,MAKELPARAM(i,0));
  }

DLLExport BOOL FAR PASCAL _export MVarDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  static int tbstops[] = { 51 , 172 , 204 } ;
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETTABSTOPS,2,LONG(LPINT(tbstops)));
//      SubClassElements (hDlg,MyInstance);
      RetVal = TRUE ;
      FillVarList (hDlg);
      InitializeVarSelStates (hDlg);
      break ;
/*
    case WM_CTLCOLOR :
      {
      LONG lres = GetCtlColor (hDlg,wP,lP,RetVal);
      if (RetVal)
        return BOOL (lres);   // ??? !!!! ???
      }
*/
    case WM_COMMAND :
      switch (wP) {
        case IDCANCEL :
          EndDialog (hDlg,TRUE);
          break ;
        case ID_WRITEINT :
          {
          DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(MWriteDialog),MyInstance));
          DialogBox (MyInstance,"WRITEINT",hDlg,dlgProc);
          FreeProcInstance (dlgProc);
          EndDialog (hDlg,TRUE);
          }
          break ;
        case ID_SELECTALL :
          SelectAll (hDlg);
          SyncronizeVarSels (hDlg);
          break;
        case ID_LIST :
          if (HIWORD(lP) == LBN_SELCHANGE)
            SyncronizeVarSels (hDlg);
          break ;
        }
      break ;
    }
  return RetVal;
  }

void FillTableList (HWND hDlg)
  {
  LPDLLADMIN dlladmin = GetDLLAdmin();
  for ( TableEntry FAR *h = aList ; h != NULL ; h = h->Next ) {
    char outtxt[128];
    wsprintf (outtxt,"%s\t%u\t%s\t%d",h->td->GetName(),h->td->GetTableID(),
                        dlladmin->GetDLLEntry(h->td->GetDLLHandle())->GetDLLName(),
                        h->td->GetAnzVars()
             );
    SendDlgItemMessage (hDlg,ID_LIST,LB_ADDSTRING,0,LONG(LPSTR(outtxt)));
    }
  }

void SetTableSels (HWND hDlg)
  {
  WORD i = 0;
  for ( TableEntry FAR *h = aList ; h != NULL ; h = h->Next , i++) {
    if (h->SelCount > 0)
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETSEL,TRUE,MAKELPARAM(i,0));
    }
  }

void SyncronizeSelStates (HWND hDlg)
  {
  WORD i = 0;
  TableEntry FAR *p = NULL ;
  for ( TableEntry FAR *h = aList ; h != NULL ; h = h->Next , i ++) {
    BOOL state = BOOL (SendDlgItemMessage (hDlg,ID_LIST,LB_GETSEL,i,0L));
    if (state) {
      if (h->SelCount == 0) {
        AddTableToVarList (h->td,0,
                    (p != NULL) ? p->td : NULL,
                    (p != NULL) ? p->SelCount : NULL
                          );
        h->SelCount = 1;
        }
      p = h;
      }
    else if (h->SelCount != 0) {
      for (int j = int (h->SelCount-1) ; j >= 0 ; j--)
        RemoveTableFromVarList (h->td,j);
      h->SelCount = 0;
      }
    }
  }

void ShowSelCount (HWND hDlg)
  {
  WORD j = WORD(SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
  WORD i = 0;
  for ( TableEntry FAR *h = aList ; h != NULL ; h = h->Next , i ++ ) {
    if (i == j) {
      char outtxt[20];
      wsprintf (outtxt,"%d",h->SelCount);
      SetDlgItemText (hDlg,ID_TBLCOUNT,outtxt);
      break ;
      }
    }
  }

void IncSelCount (HWND hDlg)
  {
  WORD j = WORD(SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
  BOOL state = BOOL (SendDlgItemMessage (hDlg,ID_LIST,LB_GETSEL,j,0L));
  if (!state) {
    MessageBeep(0);
    return ;
    }
  WORD i = 0;
  for ( TableEntry FAR *h = aList ; h != NULL ; h = h->Next , i ++ ) {
    if (i == j) {
      AddTableToVarList (h->td,h->SelCount,h->td,0);
      h->SelCount ++ ;
      }
    }
  ShowSelCount (hDlg);
  }

void DecSelCount (HWND hDlg)
  {
  WORD j = WORD(SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
  BOOL state = BOOL (SendDlgItemMessage (hDlg,ID_LIST,LB_GETSEL,j,0L));
  if (!state) {
    MessageBeep(0);
    return ;
    }
  WORD i = 0;
  for ( TableEntry FAR *h = aList ; h != NULL ; h = h->Next , i ++ ) {
    if (i == j) {
      if (h->SelCount > 1) {
        h->SelCount -- ;
        RemoveTableFromVarList (h->td,h->SelCount);
        }
      else {
        MessageBeep(0);
        return ;
        }
      }
    }
  ShowSelCount (hDlg);
  }

void FocusToTable (HWND hDlg)
  {
  SetFocus (GetDlgItem (hDlg,ID_LIST));
  }

void NewSort (HWND hDlg)
  {
  // 1. Ueberpruefen, ob das ueberhaupt moeglich ist
  for (TableEntry FAR *h = aList ; h != NULL ; h = h->Next) {
    if (h->SelCount > 0) break ;
    }
  if (h == NULL) {
    int Sel = int (SendDlgItemMessage (hDlg,ID_LIST,LB_GETCURSEL,0,0L));
    int i = 0;
    TableEntry FAR *p  = NULL;
    TableEntry FAR *pp = NULL;
    for (h = aList ; ((h != NULL) && (i < Sel)) ; pp = p , p = h , h = h->Next , i++) ;
    if ((h != NULL) && (p != NULL)) {
      // h und p vertauschen
      if (pp != NULL) {
        pp->Next = h ;
        p->Next  = h->Next ;
        h->Next  = p ;
        }
      else {
        aList = h ;
        p->Next = h->Next ;
        h->Next = p ;
        }
      SendDlgItemMessage (hDlg,ID_LIST,LB_RESETCONTENT,0,0L);
      FillTableList (hDlg);
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETCURSEL,Sel-1,0L);
      }
    }
  else
    MessageBeep (0);
  SetFocus (GetDlgItem (hDlg,ID_LIST));
  }

DLLExport BOOL FAR PASCAL _export MTableDialog (HWND hDlg, UINT msg, WORD wP, LONG lP)
  {
  static int tbstops[] = { 99 , 126 , 171 } ;
  BOOL RetVal = FALSE ;
  switch (msg) {
    case WM_INITDIALOG :
      SendDlgItemMessage (hDlg,ID_LIST,LB_SETTABSTOPS,3,LONG(LPINT(tbstops)));
//      SubClassElements (hDlg,MyInstance);
      RetVal = TRUE ;
      FillTableList (hDlg);
      SetTableSels (hDlg);
      FocusToTable (hDlg);
      ShowSelCount (hDlg);
      break ;
/*
    case WM_CTLCOLOR :
      {
      LONG lres = GetCtlColor (hDlg,wP,lP,RetVal);
      if (RetVal)
        return BOOL (lres);   // ??? !!!! ???
      }
*/
    case WM_COMMAND :
      switch (wP) {
        case IDCANCEL :
          GetTableAdmin()->DestroyTableList (aList);
          aList = NULL;
          FreeVarList ();
          EndDialog (hDlg,TRUE);
          break ;
        case ID_INC :
          IncSelCount (hDlg);   
          FocusToTable (hDlg);
          break;
        case ID_DEC :
          DecSelCount (hDlg);
          FocusToTable (hDlg);
          break;
        case ID_COLUMN :
          {
          DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(MVarDialog),MyInstance));
          DialogBox (MyInstance,"GENINTVAR",hDlg,dlgProc);
          FreeProcInstance (dlgProc);
          GetTableAdmin()->DestroyTableList (aList);
          aList = NULL;
          FreeVarList ();
          EndDialog (hDlg,TRUE);
          }
          break ;
        case ID_LIST :
          if (HIWORD(lP) == LBN_SELCHANGE) {
            SyncronizeSelStates (hDlg);
            ShowSelCount (hDlg);
            }
          break ;
        case ID_INSERTBEFORE :
          NewSort (hDlg);
          break ;
        }
      break ;
    }
  return RetVal;
  }

// Analyse einer bereits existierenden Tabelle
////////////////////////////////////////////////
static TableEntry FAR *Prev;
void AnalyseInternTableName (LPSTR Name)
  {
  TableName = LPSTR(GetGlobMem (lstrlen(Name)+1));
  lstrcpy (TableName,Name);
  Prev = NULL;
  }

static BOOL AnalyseNextVar;
void AnalyseNextTable ()
  {
  AnalyseNextVar = TRUE ;
  }

void AnalyseInternVarName (LPSTR Name)
  {
  if (VarPrefix == NULL) {
    for (LPSTR h = Name ; ((*h) && (*h != '_')) ; h ++);
    if (*h)
      VarPrefix = LPSTR(GetGlobMem (h - Name + 1));
    lmemcpy (VarPrefix,Name,h-Name);
    }
  }

static char extname[128];
void AnalyseExternVarName (LPSTR Name)
  {
  lstrcpy (extname,Name);
  }

void AnalyseAddInternVar (LPSTR Name)
  {
  // Suchen der Tabelle
  TableEntry FAR *p = NULL;
  for (TableEntry FAR *h = aList ; h != NULL ; h = h->Next) {
    if (lstrcmp(h->td->GetName(),Name) == NULL) {
      if (AnalyseNextVar) {
        AddTableToVarList (h->td,h->SelCount,
                              (p != NULL) ? p->td : NULL ,
                              (p != NULL) ? p->SelCount : 0
                          );
        h->SelCount++;
        }
      break ;
      }
    if (h->SelCount > 0) p = h;
    }
  // Selektieren der Variable
  if (h != NULL) {
    for (LPVARLIST v = vList ; v != NULL ; v = v->Next) {
      if ((v->Ref == h->td) && (v->TableNr == h->SelCount - 1) &&
             (lstrcmp(extname,v->Ref->GetVarDef(v->VarNum)->GetName()) == 0)) {
        v->doSel = TRUE ;
        break ;
        }
      }
    }
  AnalyseNextVar = FALSE ;
  }

void AnalyseInsertTableBehind (LPSTR Name)
  {
  TableEntry FAR *p = NULL;
  for (TableEntry FAR *h = aList ; h != NULL ; ) {
    if (lstrcmp (h->td->GetName(),Name) == 0) {
      // Gefunden -> Rausnehmen und neu einfuegen
      if (p != NULL) p->Next = h->Next;
      else           aList   = h->Next;
      if (Prev != NULL) {
        h->Next    = Prev->Next;
        Prev->Next = h;
        }
      else {
        h->Next = aList ;
        aList   = h;
        }
      Prev = h ;
      break ;
      }
    else {
      p = h;
      h = h->Next;
      }
    }
  }

void GenIntTables (HWND hWnd,LPSTR fName)
  {
  _fName = fName;
  aList = GetTableAdmin()->CreateTableList ();
  AnalyseIntTable (hWnd,fName);
  DLGPROC dlgProc = DLGPROC (MakeProcInstance (FARPROC(MTableDialog),MyInstance));
  DialogBox (MyInstance,"GENINTTBL",hWnd,dlgProc);
  FreeProcInstance (dlgProc);
  if (TableName != NULL) FreeGlobMem (TableName) , TableName = NULL;
  if (VarPrefix != NULL) FreeGlobMem (VarPrefix) , VarPrefix = NULL;
  }

