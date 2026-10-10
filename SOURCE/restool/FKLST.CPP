/*---------------------------------*/
/*  Bearbeiten der Foreign - Keys  */
/*---------------------------------*/
//
// $Header:   P:/marille/clinicum/restool/rev/fklst.cpv   1.4   24 Mar 1996 12:16:22   HANNES  $
// $Log:   P:/marille/clinicum/restool/rev/fklst.cpv  $
// 
//    Rev 1.4   24 Mar 1996 12:16:22   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.3   02 Feb 1996 10:50:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   26 Apr 1995 15:26:20   HANNES
// 
//    Rev 1.1   16 Feb 1995 12:33:10   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.0   29 Jan 1995 11:47:38   HANNES
// Initial revision.
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
int FKList::AnzColumns()
  {
  return 4;
  }
int FKList::GetX0()
  {
  return 400 ;
  }

DWORD FKList::GetColMode (int Column)
  {
  static int XFldColMode[] = {
    FM_SINGLELINE | FM_NOSELECTION ,  // SchluesselName
    FM_LSELECTION | FM_NOSELECTION ,  // Typ
    FM_SINGLELINE | FM_NOSELECTION ,  // FremdFeldname
    FM_SINGLELINE | FM_NOSELECTION ,  // Feldname
    } ;
  return XFldColMode[Column];
  }

struct FAR FKListContext {
  LPTABLEDEF td;
  int KeyNmbr;
  int KeySeg;
  };

LPSTR FKList::GetFieldString (LPVOID Context,int Column)
  {
  static char *nothing = "";
  static char *Standard = "Standard";
  static char *Extended = "Extended";
  FKListContext FAR *c = (FKListContext FAR *) Context;
  LPCLRIDEF r = c->td->GetRIDef (c->KeyNmbr);
  switch (Column) {
    case 0 :    // Tabellenname
      if (c->KeySeg == 0) {
        return r->name;
        }
      else
        return nothing ;
      break ;
    case 1 :    // Typ
      if (c->KeySeg == 0) {
        return (r->Type == CLKR_STANDARD) ? Standard : Extended ;
        }
      else
        return nothing ;
      break ;
    case 2 :  // Fremdfeld, Zugriff
      if ((r->Type == CLKR_EXTENDED) && (c->KeySeg == 0)) {
        ExtendedRI FAR *ei = r->GetERI();
        return ei->AccessName;
        }
      else if (r->Type == CLKR_STANDARD) {
        int j = 0;
        for (StandardRI FAR *si = r->GetSRI(); j < c->KeySeg ; j++ , si = si->GetNextSRI()) ;
        return si->ForeignField;
        }
      else
        return nothing;
      break ;
    case 3 :    // Eigened Feld
      {
      WORD VarID ;
      if (r->Type == CLKR_EXTENDED) {
        ExtendedRI FAR *ei = r->GetERI();
        VarID = (ei->GetVarIDList())[c->KeySeg];
        }
      else {
        int j = 0;
        for (StandardRI FAR *si = r->GetSRI(); j < c->KeySeg ; j++ , si = si->GetNextSRI()) ;
        VarID = si->VarID;
        }
      if (VarID != 0xFFFF)
        return c->td->GetVarDef(VarID)->GetName();
      else
        return nothing;
      }
      break ;
    }
  return nothing;
  }

LPSTR FKList::GetHdString (int Column)
  {
  switch (Column) {
    case 0 :
      return "\\m1Fremdtabelle" ;
    case 1 :
      return "\\m1Typ" ;
    case 2 :
      return "\\m1Fremdfeld/Zugriff" ;
    case 3 :
      return "\\m1Feld" ;
    }
  return NULL;
  }

void FKList::Save (LPFLDLINE line,int column)
  {
  }

int FKList::GetFormat()
  {
  return 2 ;
  }

struct FAR FKListContext kc;
LPVOID FKList::GetFirstContext()
  {
  LPTABLEDEF t = LPTABLEDEF (BaseContext);
  if (t == NULL) return NULL ;
  kc.td = t ;
  kc.KeyNmbr = 0;
  kc.KeySeg = 0;
  if (kc.KeyNmbr < t->GetAnzRIDefs()) return &kc;
  else                                return NULL;
  }

LPVOID FKList::GetNextContext(LPVOID oldContext)
  {
  LPCLRIDEF r = kc.td->GetRIDef (kc.KeyNmbr);
  kc.KeySeg ++ ;
  if (kc.KeySeg >= int(r->AnzSegs)) {
    kc.KeySeg = 0 ;
    kc.KeyNmbr ++ ;
    }
  if (kc.KeyNmbr < kc.td->GetAnzRIDefs()) return &kc;
  else                                    return NULL;
  }

BOOL FKList::EnableNewContext()
  {
  return TRUE ;
  }

LPSTR FKList::GetMenuName()
  {
  return "FKLSTMENU";
  }

void FKList::OnDestroy()
  {
  }

LPSTR FKList::ProfBase()
  {
  return "FKLST";
  }

static char *StandardExtended = "Standard\0Extended\0\0";
LPSTR FKList::GetResource (int Column)
  {
  return StandardExtended;
  }

BOOL FKList::EnableInput ()
  {
  return TRUE ;
  }

int FKList::GetColWidth(int Column)
  {
  if (ColWidth == NULL) {
    ColWidth = (int FAR *) GetGlobMem (sizeof(int) * AnzColumns());
    for (int i = 0 ; i < AnzColumns() ; i++)
      ColWidth[i] = -1;
    }
  if (ColWidth[Column] == -1) {
    char wstring[32];
    wsprintf (wstring,"Width%d",Column);
    int def = 1000 ;
    switch (Column) {
      case 0 :
        def = 3000 ;
        break ;
      case 1 :
        def = 1200 ;
        break ;
      case 2 :
        def = 3000 ;
        break ;
      case 3 :
        def = 3000 ;
        break ;
      }
    ColWidth[Column] = GetProfInt (wstring,def);
    }
  return ColWidth[Column];
  }

BOOL FKList::AllowClose()
  {
  SetFocus (hWndParent);
  Hide ();
  return FALSE ;
  }

/*-----< Speichern der Info >-------*/
BOOL FKList::WriteHeader (HFILE fm)
  {
  static char *hdstr = "  ForeignDefinition = {\r\n";
  _lwrite (fm,hdstr,lstrlen(hdstr));
  return TRUE ;
  }

BOOL FKList::WriteLine (HFILE fm,LPFLDLINE h,BOOL FAR &IsExtended,FldCheck FAR *c)
  {
  char t1[128],t2[30],t3[128],t4[128];
  BOOL TableGiven = GetFieldContent (t1,h,0);
  BOOL TypGiven = GetFieldRes (t2,h,1,TRUE);
  BOOL ExtGiven = GetFieldContent (t3,h,2);
  BOOL VarGiven = GetFieldContent (t4,h,3);
  BOOL res = ((VarGiven) && (c->FieldExist(t4))) ;
  if (!res) return FALSE ;
  char outtxt[256];
  if (TableGiven) {
    if (h != FirstLine) 
      _lwrite (fm,";\r\n",3);
    if ((!TypGiven) || (!ExtGiven)) return FALSE ;
    IsExtended = (lstrcmp (t2,"Extended") == 0);
    if (IsExtended)
      wsprintf (outtxt,"    _%s %s (%s) %s",LPSTR(t2),LPSTR(t1),LPSTR(t3),LPSTR(t4));
    else
      wsprintf (outtxt,"    _%s %s %s = %s",LPSTR(t2),LPSTR(t1),LPSTR(t3),LPSTR(t4));
    }
  else {
    if (h == FirstLine) return FALSE ;
    if (TypGiven) return FALSE ;
    if ((IsExtended) && (ExtGiven)) return FALSE ;
    if ((!IsExtended) && (!ExtGiven)) return FALSE ;
    if (IsExtended)
      wsprintf (outtxt,",%s",LPSTR(t4));
    else
      wsprintf (outtxt,",%s = %s",LPSTR(t3),LPSTR(t4));
    }
  _lwrite (fm,outtxt,lstrlen(outtxt));
  return TRUE ;
  }

BOOL FKList::WriteEnd (HFILE fm)
  {
  static char *endstr = "\r\n    };\r\n";
  if (FirstLine != NULL)
    _lwrite (fm,";",1);
  _lwrite (fm,endstr,lstrlen(endstr));
  return TRUE ;
  }

LPFLDLINE FKList::Store (HFILE fm,FldCheck FAR *c)
  {
  // Schreiben des Headers
  WriteHeader (fm);
  BOOL IsExtended;
  for (LPFLDLINE h = FirstLine ; h != NULL ; h = h->Next) {
    if (!WriteLine (fm,h,IsExtended,c)) return h;
    }
  WriteEnd (fm);
  return NULL;
  }

FKList FAR *WorkOnFKList (HWND hW,HWND hWMain,LPTABLEDEF td)
  {
  LPSTR Caption = (td != NULL) ? td->GetName () : "<unknown>";
  FKList FAR *lst = new FKList (hWMain,td,Caption);
  lst->Create (hW);
  return lst;
  }

void FKList::DoDrop (int x,int y,LPVOID Data,WORD Type)
  {
  int col;
  LPFLDLINE l;
  cField FAR *hit = GetFieldFromPos (&col,&l,x,y);
  if (hit != NULL) {
    char t2[30];
    BOOL TypGiven = GetFieldRes (t2,l,1,TRUE);
    BOOL IsExtended = (lstrcmp (t2,"Extended") == 0);
    if (((col == 0) && (Type == DDTYPE_TABLE)) ||
        (((col == 2) || (col == 3)) && (Type == DDTYPE_VARNAME))) {
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
  else
    MessageBeep (0);
  }

