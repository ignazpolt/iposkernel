/*----------------------------------*/
/*  Bearbeiten der Schluesselliste  */
/*----------------------------------*/
//
// $Header:   P:/marille/clinicum/restool/rev/keylst.cpv   1.5   24 Mar 1996 12:16:36   HANNES  $
// $Log:   P:/marille/clinicum/restool/rev/keylst.cpv  $
// 
//    Rev 1.5   24 Mar 1996 12:16:36   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:50:58   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   26 Apr 1995 15:27:04   HANNES
// 
//    Rev 1.2   16 Feb 1995 12:40:18   HANNES
// Erweiterte DB-Funktionalitaet
// 
//    Rev 1.1   29 Jan 1995 11:48:00   HANNES
// 
//    Rev 1.0   24 Jan 1995 11:00:42   HANNES
// Initial revision.
// 
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
#include "tblst.hpp"

/*--< Implementierung der virtuellen Funktionen fuer Feldbearbeitung >--*/
int KeyList::AnzColumns()
  {
  return 6;
  }
int KeyList::GetX0()
  {
  return 400 ;
  }

DWORD KeyList::GetColMode (int Column)
  {
  static int XFldColMode[] = {
    FM_SINGLELINE | FM_NOSELECTION ,  // SchluesselName
    FM_SINGLELINE | FM_NOSELECTION ,  // Feldname
    FM_LSELECTION | FM_NOSELECTION ,  // Autoinc
    FM_LSELECTION | FM_NOSELECTION ,  // Unique
    FM_LSELECTION | FM_NOSELECTION ,  // Modify
    FM_LSELECTION | FM_NOSELECTION    // NULL
    } ;
  return XFldColMode[Column];
  }

struct FAR KeyListContext {
  LPTABLEDEF td;
  int KeySeg;
  };

LPSTR KeyList::GetFieldString (LPVOID Context,int Column)
  {
  static char *nothing = "";
  static char *yes = "yes";
  static char *no = "no";
  KeyListContext FAR *c = (KeyListContext FAR *) Context;
  LPCLKEYDEF k = c->td->GetKeyDef(c->KeySeg);
  BOOL firstSegKey;
  if (c->KeySeg == 0) firstSegKey = TRUE ;
  else {
    LPCLKEYDEF old = c->td->GetKeyDef(c->KeySeg-1);
    firstSegKey = (k->KeyNmbr == old->KeyNmbr) ? FALSE : TRUE ;
    }
  switch (Column) {
    case 0 :    // Schluesselname
      if (firstSegKey)
        return k->name;
      else 
        return nothing;
      break ;
    case 1 :    // Feldname
      if (k->VarID != 0xFFFF) {
        LPVARDEF v = c->td->GetVarDef (k->VarID);
        return v->GetName();
        }
      else
        return nothing;
      break ;
    case 2 :    // Autoinc
      if (firstSegKey) {
        if (k->Attribute & CLKD_AUTOINC)
          return yes;
        else
          return no;
        }
      else
        return nothing;
      break ;
    case 3 :    // Unique
      if (firstSegKey) {
        if (k->Attribute & CLKD_UNIQUE)
          return yes;
        else
          return no;
        }
      else
        return nothing;
      break ;
    case 4 :    // Modify
      if (firstSegKey) {
        if (k->Attribute & CLKD_MODIFYABLE)
          return yes;
        else
          return no;
        }
      else
        return nothing;
      break ;
    case 5 :    // Null
      if (firstSegKey) {
        if (k->Attribute & CLKD_NULL)
          return yes;
        else
          return no;
        }
      else
        return nothing;
      break ;
    }
  return NULL;
  }

LPSTR KeyList::GetHdString (int Column)
  {
  switch (Column) {
    case 0 :
      return "\\m1Schlüssel" ;
    case 1 :
      return "\\m1Name" ;
    case 2 :
      return "\\m1AUTOINC" ;
    case 3 :
      return "\\m1UNIQUE" ;
    case 4 :
      return "\\m1MOD" ;
    case 5 :
      return "\\m1NULL" ;
    }
  return NULL;
  }

void KeyList::Save (LPFLDLINE line,int column)
  {
  }

int KeyList::GetFormat()
  {
  return 2 ;
  }

struct FAR KeyListContext kc;
LPVOID KeyList::GetFirstContext()
  {
  LPTABLEDEF t = LPTABLEDEF (BaseContext);
  if (t == NULL) return NULL;
  kc.td = t;
  kc.KeySeg = 0;
  if (kc.KeySeg < t->GetAnzKeySegs()) return &kc;
  else                                return NULL;
  }

LPVOID KeyList::GetNextContext(LPVOID oldContext)
  {
  kc.KeySeg ++;
  if (kc.KeySeg < kc.td->GetAnzKeySegs()) return &kc;
  else                                    return NULL;
  }

BOOL KeyList::EnableNewContext()
  {
  return TRUE ;
  }

LPSTR KeyList::GetMenuName()
  {
  return "KEYLSTMENU";
  }

void KeyList::OnDestroy()
  {
  }

LPSTR KeyList::ProfBase()
  {
  return "KLST";
  }

static char *yesno = "yes\0no\0\0";
LPSTR KeyList::GetResource (int Column)
  {
  return yesno;
  }

BOOL KeyList::EnableInput ()
  {
  return TRUE ;
  }

int KeyList::GetColWidth(int Column)
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
        def = 3000 ;
        break ;
      case 1 :
        def = 3000 ;
        break ;
      default :
        def = 600 ;
        break ;
      }
    ColWidth[Column] = GetProfInt (wstring,def);
    }
  return ColWidth[Column];
  }

BOOL KeyList::AllowClose()
  {
  SetFocus (hWndParent);
  Hide ();
  return FALSE ;
  }

/*------< Speichern der Info >------*/
BOOL KeyList::WriteHeader (HFILE fm)
  {
  _lwrite (fm,"  keys = {\r\n",12);
  return TRUE ;
  }

BOOL KeyList::WriteLine (HFILE fm,LPFLDLINE h,FldCheck FAR *c)
  {
  char t1[128],t2[128],t3[20],t4[20],t5[20],t6[20];
  BOOL KeyGiven = ((GetFieldContent(t1,h,0)) && (kNames->CheckName (t1)));
  BOOL VarGiven = ((GetFieldContent(t2,h,1)) && (c->FieldExist(t2)));
  BOOL AGiven  = GetFieldRes(t3,h,2,TRUE);
  BOOL UGiven  = GetFieldRes(t4,h,3,TRUE);
  BOOL MGiven  = GetFieldRes(t5,h,4,TRUE);
  BOOL NGiven  = GetFieldRes(t6,h,5,TRUE);
  if ((VarGiven) && ((KeyGiven && AGiven && UGiven && MGiven && NGiven) ||
                    (!KeyGiven && !AGiven && !UGiven && !MGiven && !NGiven))) {
    if ((h == FirstLine) && (!KeyGiven)) return FALSE ;
    if (h != FirstLine) {
      // Letzte Zeile abschliessen
      if (KeyGiven) _lwrite (fm,";\r\n",3);
      else          _lwrite (fm,",",1);
      }
    if (KeyGiven) {
      char outtxt[256];
      wsprintf (outtxt,"    %s (autoinc=%s,unique=%s,modify=%s,null=%s) = ",
                    LPSTR(t1),LPSTR(t3),LPSTR(t4),LPSTR(t5),LPSTR(t6));
      _lwrite (fm,outtxt,lstrlen(outtxt));
      }
    _lwrite (fm,t2,lstrlen(t2));
    return TRUE ;
    }
  else
    return FALSE ;
  }

BOOL KeyList::WriteEnd (HFILE fm)
  {
  if (FirstLine != NULL)
    _lwrite (fm,";",1);
  _lwrite (fm,"\r\n    };\r\n",10);
  return TRUE ;
  }

LPFLDLINE KeyList::Store (HFILE fm,FldCheck FAR *c)
  {
  // Schreiben des Headers
  WriteHeader (fm);
  kNames = new FldCheck();
  BOOL somethingDone = FALSE ;
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if (!WriteLine (fm,h,c)) {
      delete kNames ;
      kNames = NULL ;
      return h;
      }
    else
      somethingDone = TRUE ;
    }
  delete kNames ;
  kNames = NULL ;
  WriteEnd (fm);
  return (somethingDone) ? NULL : FirstLine ;
  }

KeyList FAR * WorkOnKeyList (HWND hW,HWND hWMain,LPTABLEDEF td)
  {
  LPSTR Caption = (td != NULL) ? td->GetName () : "<unknown>";
  KeyList FAR *lst = new KeyList (hWMain,td,Caption);
  lst->Create (hW);
  return lst;
  }

void KeyList::DoDrop (int x,int y,LPVOID Data,WORD Type)
  {
  int col;
  LPFLDLINE l;
  cField FAR *hit = GetFieldFromPos (&col,&l,x,y);
  if ((hit != NULL) && (col == 1) && (Type == DDTYPE_VARNAME)) {
    RECT r1,r2;
    hit->GetFieldRect (&r1, 0);
    *hit = LPSTR(Data);
    hit->GetFieldRect (&r2, 0) ;
    Invalidate (l,&r1,TRUE);
    Invalidate (l,&r2,TRUE);
    }
  else
    MessageBeep (0);
  }

