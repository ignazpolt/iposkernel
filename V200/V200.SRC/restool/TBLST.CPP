/*----------------------------------*/
/*  Bearbeiten der echten Tabellen  */
/*----------------------------------*/
// $Header:   P:/marille/clinicum/restool/rev/tblst.cpv   1.13   26 Apr 1999 18:11:50   Wolfgang  $
// $Log:   P:/marille/clinicum/restool/rev/tblst.cpv  $
// 
//    Rev 1.13   26 Apr 1999 18:11:50   Wolfgang
// 1.) Sanduhr-Cursor auch wieder zuruecksetzen.
// 
//    Rev 1.12   05 Oct 1998 11:28:16   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.11   16 Feb 1998 14:48:50   Gerhold
// VC++5.x ... kleine Aenderungen
// 
//    Rev 1.10   28 Aug 1997 15:53:00   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.9   26 Nov 1996 08:09:38   HANNES
// Automatischer Update
// 
//    Rev 1.8   21 Oct 1996 18:57:56   HANNES
// Fehlerkorrekturen Editor
// 
//    Rev 1.7   17 Jun 1996 16:54:08   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.6   24 Mar 1996 12:16:46   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.5   02 Feb 1996 10:50:30   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   27 Aug 1995 13:15:12   HANNES
// Caption setzten beim Speichern
// 
//    Rev 1.3   26 Apr 1995 15:26:54   HANNES
// 
//    Rev 1.2   16 Feb 1995 12:34:08   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.1   29 Jan 1995 11:48:20   HANNES
// 
//    Rev 1.0   24 Jan 1995 11:00:42   HANNES
// Initial revision.

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

#include "BlandMDI.hpp"

class FAR TbFldList : public FldList {
 public :
  TbFldList (LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { }

  KeyList FAR *KList;
  FKList FAR *ForeignList;
  SrvEd FAR *ServerInfo;
  LPSTR FileName;
  FldName FAR *lpFldList;
  FldCheck FAR *VarNames;

  BOOL Store();
  void GetServerIncName (LPSTR IncName,LPSTR DLLName);
  void GetOutFileName (LPSTR fName);
  void WriteServerInfo (GLOBALHANDLE hGTxt,LPSTR DLLName,LPSTR IncName);
  BOOL WriteHeader (HFILE fm,LPSTR TableName);
  BOOL WriteField (HFILE fm,LPFLDLINE h);
  BOOL WriteFieldEnd (HFILE fm);
  void Attribute();

  virtual void  Save (LPFLDLINE line,int column);
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

  virtual LPSTR  GetMenuName();
  virtual LPSTR  ProfBase();
  virtual int    GetColWidth(int Column);
  virtual void   OnCommand (WORD wP);
  virtual int     GetDropType (int DownColumn)
    {
    if (DownColumn == 0)
      return DDTYPE_VARNAME ;
    else
      return 0 ;
    }
  virtual BOOL   AllowChange(LPFLDLINE h,int Column);
  };

/*--< Implementierung der virtuellen Funktionen fuer Feldbearbeitung >--*/
int TbFldList::AnzColumns()
  {
  return 5;
  }
int TbFldList::GetX0()
  {
  return 400 ;
  }

DWORD TbFldList::GetColMode (int Column)
  {
  static int XFldColMode[] = {
    FM_SINGLELINE | FM_NOSELECTION ,  // Name
    FM_LSELECTION | FM_NOSELECTION ,  // Typ
    FM_SINGLELINE | FM_DECIMAL | FM_NOSELECTION , // Groesse
    FM_SINGLELINE | FM_DECIMAL | FM_NOSELECTION , // VarID
    FM_LSELECTION | FM_NOSELECTION 
    } ;
  return XFldColMode[Column];
  }

LPSTR TbFldList::GetFieldString (LPVOID Context,int Column)
  {
  static char res[256];
  LPVARDEF v = LPVARDEF (Context);
  switch (Column) {
    case 0 :    // Feldname
      return v->GetName();
      break ;
    case 1 :    // Datentyp
      return GetMTypeName(v->mType);
      break ;
    case 2 :    // Laenge
      if (v->VarSize != 0xFFFF)
        wsprintf (res,"%d",v->VarSize);
      else
        *res = '\0';
      return res;
      break ;
    case 3 :    // VarID
      if (v->VarID != 0xFFFF)
        wsprintf (res,"%d",v->VarID);
      else
        *res = '\0';
      return res;
      break ;
    case 4 :
      if (v->Property & VPROP_NOTNULL)
        lstrcpy (res,"no");
      else
        lstrcpy (res,"yes");
      return res ;
      break ;
    }
  return NULL;
  }

LPSTR TbFldList::GetHdString (int Column)
  {
  switch (Column) {
    case 0 :
      return "\\m1Name" ;
    case 1 :
      return "\\m1Typ" ;
    case 2 :
      return "\\m1Size" ;
    case 3 :
      return "\\m1VarID" ;
    case 4 :
      return "\\m1null" ;
    }
  return NULL;
  }

int GetTypeSize (LPSTR typName)
  {
  if ((lstrcmp (typName,"strfield") == 0) ||
          (lstrcmp (typName,"short") == 0)) return 2 ;
  if ((lstrcmp (typName,"dec") == 0) ||
          (lstrcmp (typName,"long") == 0) ||
          (lstrcmp (typName,"date") == 0) ||
          (lstrcmp (typName,"time") == 0)) return 4 ;
  if (lstrcmp (typName,"point") == 0) return 8 ;
  return -1 ;
  }
void TbFldList::Save (LPFLDLINE line,int column)
  {
  cField FAR *f1 = NULL;
  RECT rold;
  if (column == 3) {    // Id eingegeben -> Groesse wegnehmen
    char tid[32];
    if (GetFieldContent (tid,line,3)) {
      f1 = line->GetField (2);
      f1->GetFieldRect (&rold, 0);
      *f1 = "" ;
      }
    else {
      char typ[32];
      int Size;
      f1 = line->GetField (2);
      if (GetFieldRes (typ,line,1,TRUE)) Size = GetTypeSize(typ);
      else                               Size = 32 ;
      char str[32];
      wsprintf (str,"%d",Size);
      f1->GetFieldRect (&rold, 0);
      *f1 = str;
      }
    }
  else if (column == 1) { // typ
    char typ[32],tid[32];
    int Size;
    if (GetFieldRes (typ,line,1,TRUE)) Size = GetTypeSize(typ);
    if ((Size > 0) && (!GetFieldContent (tid,line,3))) {
      f1 = line->GetField (2);
      char str[32];
      wsprintf (str,"%d",Size);
      f1->GetFieldRect (&rold, 0);
      *f1 = str;
      }
    }
  if (f1 != NULL) {
    RECT r;
    f1->GetFieldRect (&r, 0) ;
    Invalidate (line,&rold,TRUE);
    Invalidate (line,&r,TRUE);
    }
  }

int TbFldList::GetFormat()
  {
  return 2 ;
  }

LPVOID TbFldList::GetFirstContext()
  {
  if (BaseContext != NULL) {
    LPTABLEDEF t = LPTABLEDEF (BaseContext);
    if (t->GetAnzVars() > 0)
      return t->GetVarDef(0);
    }
  return NULL;
  }

LPVOID TbFldList::GetNextContext(LPVOID oldContext)
  {
  LPTABLEDEF t = LPTABLEDEF (BaseContext);
  int AnzVars = t->GetAnzVars();
  for (int i = 0 ; i < AnzVars ; i++) {
    LPVARDEF v = t->GetVarDef(i);
    if (v == LPVARDEF(oldContext)) {
      return (i < AnzVars - 1) ? t->GetVarDef(i+1) : NULL ;
      }
    }
  return NULL;
  }

BOOL TbFldList::EnableNewContext()
  {
  return TRUE ;
  }

LPSTR TbFldList::GetMenuName()
  {
  return "FLDLSTMENU";
  }

extern HWND GetDBTableWnd ();
void TbFldList::OnDestroy()
  {
  LPTABLEDEF td = LPTABLEDEF (BaseContext);
  if (td != NULL)
    GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
  if (IsWindow (KList->hWnd))
    DestroyWindow (KList->hWnd);
  if (IsWindow (ForeignList->hWnd))
    DestroyWindow (ForeignList->hWnd);
  if (ServerInfo != NULL)
    delete ServerInfo;
  if (FileName != NULL) FreeGlobMem (FileName);
  MyProfFlush ();
  }

LPSTR TbFldList::ProfBase()
  {
  return "FLST";
  }

#define ID_TYPELIST   40000
extern HINSTANCE MyInstance;
LPSTR TbFldList::GetResource (int Column)
  {
  static char res[256];
  static char *yesno = "yes\0no\0" ;
  res[0] = res[1] = '\0';

  switch (Column) {
    case 1 :
      {
      LoadString (MyInstance,ID_TYPELIST,res,sizeof(res));
      for (LPSTR h = res ; *h ; h++)
        if (*h == '_') *h = '\0';
      return res;
      }
    case 4 :
      {
      return yesno ;
      }
    break ;
    }

  return NULL ;
  }

BOOL TbFldList::EnableInput ()
  {
  return TRUE ;
  }

int TbFldList::GetColWidth(int Column)
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
        def = 1200 ;
        break ;
      case 2 :
        def = 600 ;
        break ;
      case 3 :
        def = 600 ;
        break ;
      case 4 :
        def = 600 ;
        break ;
      }
    ColWidth[Column] = GetProfInt (wstring,def);
    }
  return ColWidth[Column];
  }

TbFldList FAR *_actDlgLst;
LPSTR GetEdText (HWND hWnd,WORD Id,LPSTR old)
  {
  char Text[128];
  GetDlgItemText (hWnd,Id,Text,sizeof(Text));
  for (LPSTR h = Text ; *h ; h++) {
    if (*h == ' ') *h = '\0';
    }
  if (lstrlen(Text) == 0) {
    MessageBeep (0);
    return NULL ;
    }
  if (old != NULL) FreeGlobMem (old);
  old = LPSTR(GetGlobMem (lstrlen(Text)+1));
  lstrcpy (old,Text);
  return old;
  }

DLLExport BOOL _export FAR PASCAL AttribProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  switch (msg) {
    case WM_INITDIALOG :
      SetDlgItemText (hWnd,101,_actDlgLst->Caption);
      SetDlgItemText (hWnd,104,_actDlgLst->FileName);
      return TRUE ;
      break ;
    case WM_COMMAND :
      switch (wP) {
        case IDOK :
          {
          _actDlgLst->Caption = GetEdText (hWnd,101,_actDlgLst->Caption);
          _actDlgLst->FileName = GetEdText (hWnd,104,_actDlgLst->FileName);
          if ((_actDlgLst->Caption != NULL) && (_actDlgLst->FileName != NULL)) {
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

void TbFldList::Attribute()
  {
  _actDlgLst = this ;
  DLGPROC dlgproc = DLGPROC (MakeProcInstance (FARPROC(AttribProc),MyInstance));
  DialogBox (MyInstance,"ATTRIBUTE",hWnd,dlgproc);
  FreeProcInstance (dlgproc);
  }

void TbFldList::OnCommand (WORD wP)
  {
  switch (wP) {
    case 100 :
      KList->Show();
      break ;
    case 101 :
      if (ServerInfo != NULL)
        ServerInfo->Show();
      break ;
    case 102 :
      ForeignList->Show();
      break ;
    case 110 :
      Store();
      break ;
    case 111 :
      Attribute();
      break ;
    }
  }

static HMENU TbLstMenu ;
HMENU GetTbLstMenu ()
  {
  if (TbLstMenu == 0) {
    TbLstMenu = LoadMenu (MyInstance,"FLDLSTMENU");
    }
  return TbLstMenu ;
  }
void WorkOnTable (LPSTR TableName)
  {
  WndDef wd[3];
  wd[0].x0 = wd[1].x0 = wd[2].x0 = 0 ;
  wd[0].x1 = wd[1].x1 = wd[2].x1 = 1000 ;
  wd[0].y0 = 400 ;  wd[0].y1 = 1000 ;
  wd[1].y0 = 200 ;  wd[1].y1 = 400 ;
  wd[2].y0 = 0   ;  wd[2].y1 = 200 ;

  if (CreateChildWindowsInMDI (TableName,3, wd, 0L,GetTbLstMenu ())) {
    HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
    BOOL found;
    WORD Version;
    WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
    TbFldList FAR *lst;
    if (found) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (TableID,Version);
      lst = new TbFldList (td,td->GetName());
      LPSTR FName = td->GetFileName();
      if (FName != NULL) {
        lst->FileName = LPSTR(GetGlobMem (lstrlen(FName)+1));
        lstrcpy (lst->FileName,FName);
        }
      lst->Create (wd[0].hWnd);
      lst->KList = WorkOnKeyList (wd[1].hWnd,wd[0].hWnd,td);
      lst->ForeignList = WorkOnFKList (wd[2].hWnd,wd[0].hWnd,td);

      lst->Show ();
      }
    SetCursor (oldCursor);
    }
  }

GLOBALHANDLE GetEmptySrvTxt ()
  {
  LPSTR EmptyText = "access\r\n\r\nend";
  GLOBALHANDLE res = GlobalAlloc (GHND,lstrlen(EmptyText)+1);
  lstrcpy (LPSTR(GlobalLock (res)),EmptyText);
  GlobalUnlock (res);
  return res;
  }

void CreateNewTableDef ()
  {
  WndDef wd[3];
  wd[0].x0 = wd[1].x0 = wd[2].x0 = 0 ;
  wd[0].x1 = wd[1].x1 = wd[2].x1 = 1000 ;
  wd[0].y0 = 400 ;  wd[0].y1 = 1000 ;
  wd[1].y0 = 200 ;  wd[1].y1 = 400 ;
  wd[2].y0 = 0   ;  wd[2].y1 = 200 ;

  if (CreateChildWindowsInMDI ("<unbekannt>",3, wd, 0L,GetTbLstMenu ())) {
    TbFldList FAR *lst = new TbFldList (NULL,"<unbekannt>");
    lst->Create (wd[0].hWnd);
    lst->KList = WorkOnKeyList (wd[1].hWnd,wd[0].hWnd,NULL);
    lst->ForeignList = WorkOnFKList (wd[2].hWnd,wd[0].hWnd,NULL);

    lst->Show ();
    }
  }

extern LPSTR IniFile();
void TbFldList::GetServerIncName (LPSTR IncName,LPSTR DLLName)
  {
  char ext[10];
  GetPrivateProfileString ("ServerExtension",DLLName,"",ext,sizeof(ext),IniFile());
  lstrcpy (IncName,FileName);
  for (LPSTR h = IncName ; *h ; h++) {
    if (*h == '.') {
      lstrcpy (h+1,ext);
      break ;
      }
    }
  if (*h == '\0') {
    *h = '.' ;
    lstrcpy (h+1,ext);
    }
  }

void TbFldList::WriteServerInfo (GLOBALHANDLE hGTxt,LPSTR DLLName,LPSTR IncName)
  {
  GetServerIncName (IncName,DLLName);

  OFSTRUCT Of;
  int fi = OpenFile (IncName,&Of,OF_CREATE);
  if (fi > 0) {
    LPSTR src = (LPSTR)GlobalLock (hGTxt);
    int size = lstrlen(src);
    static char *srvhd = "#include \"tabledef.inc\"\r\n";
    _lwrite (fi,srvhd,lstrlen(srvhd));
    _lwrite (fi,src,size);
    _lwrite (fi,"\r\n",2);
    _lclose (fi);
    GlobalUnlock (hGTxt);
    }
  }

static char *DDDEXT = "DDD";
void TbFldList::GetOutFileName (LPSTR fName)
  {
  lstrcpy (fName,FileName);
  for (LPSTR h = fName ; *h ; h++) {
    if (*h == '.') {
      lstrcpy (h+1,DDDEXT);
      break ;
      }
    }
  if (*h == '\0') {
    *h = '.' ;
    lstrcpy (h+1,DDDEXT);
    }
  }

BOOL TbFldList::WriteHeader (HFILE fm,LPSTR TableName)
  {
  char outstring[128];
  wsprintf (outstring,"Table %s = {\r\n  fields = {\r\n",TableName);
  _lwrite (fm,outstring,lstrlen(outstring));
  return TRUE ;
  }

BOOL TbFldList::WriteField (HFILE fm,LPFLDLINE h)
  {
  char t1[128],t2[40],t3[40],t4[40],t5[10];
  
  BOOL SizeDone = GetFieldWord (t3,h,2,TRUE);
  BOOL IdDone = GetFieldWord (t4,h,3,TRUE);
  BOOL null = GetFieldRes(t5,h,4,TRUE);
  BOOL res = ((GetFieldContent (t1,h,0)) &&
              (GetFieldRes (t2,h,1,TRUE)) && 
              ((SizeDone && !IdDone) || (!SizeDone && IdDone)) &&
              (VarNames->CheckName (t1)));
  if (res) {
    char outstring[256];
    if (SizeDone) {
      if (lstrcmp (t5,"no") == 0)
        wsprintf (outstring,"    %s %s[%s] not null;\r\n",LPSTR(t2),LPSTR(t1),LPSTR(t3));
      else
        wsprintf (outstring,"    %s %s[%s];\r\n",LPSTR(t2),LPSTR(t1),LPSTR(t3));
      }
    else
      wsprintf (outstring,"    %s %s _Id = %s;\r\n",LPSTR(t2),LPSTR(t1),LPSTR(t4));
    _lwrite (fm,outstring,lstrlen(outstring));
    }
  return res ;
  }

BOOL TbFldList::WriteFieldEnd (HFILE fm)
  {
  _lwrite (fm,"    };\r\n",8);
  return TRUE ;
  }

extern BOOL GenTbScript (HWND hWnd,LPSTR fname);
extern void FreeRITableDefs (LPSTR Name);
extern void UpdateRITableDef (LPSTR Name);
extern LPSTR GetFName(LPVOID IncName);
BOOL TbFldList::Store()
  {
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
  if (FileName != NULL) {
    // Hauptfile aufmachen
    //--------------------------
    char fName[128];
    GetOutFileName (fName);
    OFSTRUCT Of;
    HFILE fm = OpenFile (fName,&Of,OF_CREATE);
    if (fm > 0) {
      // Header
      WriteHeader (fm,Caption);
      VarNames = new FldCheck();
      BOOL correct = TRUE ;
      for (LPFLDLINE h = FirstLine ; ((h != NULL) && (correct)) ; h = h->Next) {
        correct = WriteField (fm,h);
        if (!correct) {
          Fehler ("Definitionsfehler");
          if (GetFocus() == hWnd) {
            OnKillFocus ();
            }
          ActiveLine = h;
          ActiveCol = 0;
          if (GetFocus() == hWnd) {
            OnSetFocus ();
            }
          else
            SetFocus (hWnd);
          }
        }
      if (correct)
        WriteFieldEnd (fm);

      // Schreiben der Schluesselinfo
      if (correct) {
        LPFLDLINE ErrorLine = KList->Store (fm,VarNames);
        if (ErrorLine != NULL) {
          Fehler ("Definitionsfehler");
          KList->ActiveLine = ErrorLine;
          KList->ActiveCol = 0;
          KList->Show();
          SetFocus (KList->hWnd);
          correct = FALSE ;
          }
        }

      // Schreiben der ForeignKeys
      if (correct) {
        LPFLDLINE ErrorLine = ForeignList->Store (fm,VarNames);
        if (ErrorLine != NULL) {
          Fehler ("Definitionsfehler");
          ForeignList->ActiveLine = ErrorLine;
          ForeignList->ActiveCol = 0;
          ForeignList->Show();
          SetFocus (ForeignList->hWnd);
          correct = FALSE ;
          }
        }

      // Schreiben der Serverreferenz
      if (correct) {
        char outtxt[32];
        wsprintf (outtxt,"  }\r\n");
        _lwrite (fm,outtxt,lstrlen(outtxt));
        }

      // fertig exportiert
      _lclose (fm);
      if (VarNames != NULL) delete VarNames , VarNames = NULL;

      if (correct)
        correct = GenTbScript (hWnd,fName);

      if (correct) {
        FreeRITableDefs (Caption);
        LPTABLEDEF td = LPTABLEDEF (BaseContext);
        if (td != NULL) {
          GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
          BaseContext = NULL;
          }
        UpdateRITableDef (Caption);
        }

      SetCursor (oldCursor);
      return correct ;
      }
    else {
      Fehler ("Kann Ausgabedatei nicht öffnen");
      }
    SendMessage (hWnd,WM_SETTEXT,0,LPARAM(Caption));
    }
  else {
    Fehler ("Name der Ausgabedatei nicht bekannt");
    }
  SetCursor (oldCursor);
  return FALSE ;
  }

BOOL IsConstSize (LPSTR typName)
  {
  return (GetTypeSize (typName) > 0) ;
  }
BOOL TbFldList::AllowChange(LPFLDLINE h,int Column)
  {
  if (Column == 2) {
    char t2[32];
    if ((GetFieldRes (t2,h,1,TRUE)) && (IsConstSize (t2))) return FALSE ;
    else                                                   return TRUE ;
    }
  else
    return TRUE ;
  }

