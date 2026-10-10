/*------------------------------------*/
/*  Bearbeiten der globalen Tabellen  */
/*------------------------------------*/
// $Header:   P:/marille/clinicum/restool/rev/globlst.cpv   1.10   05 Oct 1998 11:26:58   Gerhold  $
// $Log:   P:/marille/clinicum/restool/rev/globlst.cpv  $
// 
//    Rev 1.10   05 Oct 1998 11:26:58   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.9   16 Feb 1998 14:48:40   Gerhold
// VC++5.x ... kleine Aenderungen
// 
//    Rev 1.8   05 Nov 1997 09:03:06   Gerhold
// 32 Bit
// 
//    Rev 1.7   28 Aug 1997 15:52:28   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.6   26 Nov 1996 08:10:24   HANNES
// Automatischer Update
// 
//    Rev 1.5   17 Jun 1996 16:53:48   HANNES
// Eifuehrung von BLOBS
// 
//    Rev 1.4   02 Feb 1996 10:50:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   27 Aug 1995 13:15:14   HANNES
// Caption setzten beim Speichern
// 
//    Rev 1.2   26 Apr 1995 15:26:36   HANNES
// 
//    Rev 1.1   03 Mar 1995 11:05:20   HANNES
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
#include "hash.hpp"
#include "restool.hpp"
#include "blandmdi.hpp"


class FAR GlobFldList : public FldList {
 public :
  GlobFldList (LPVOID Cntx,LPSTR cptn) : FldList (Cntx,cptn)
     { }

  LPSTR FileName;
  FldCheck FAR *VarNames;

  BOOL Store();
  void GetOutFileName (LPSTR fName);
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

  BOOL WriteHeader (GLOBALHANDLE FAR *hGtxt,LPSTR TableName);
  BOOL WriteField (GLOBALHANDLE FAR *hGtxt,LPFLDLINE h);
  BOOL WriteFieldEnd (GLOBALHANDLE FAR *hGtxt);
  virtual int     GetDropType (int DownColumn)
    {
    if (DownColumn == 0)
      return DDTYPE_VARNAME ;
    else
      return 0 ;
    }
  };

/*--< Implementierung der virtuellen Funktionen fuer Feldbearbeitung >--*/
int GlobFldList::AnzColumns()
  {
  return 2;
  }
int GlobFldList::GetX0()
  {
  return 400 ;
  }

DWORD GlobFldList::GetColMode (int Column)
  {
  static int XFldColMode[] = {
    FM_SINGLELINE | FM_NOSELECTION ,  // Name
    FM_LSELECTION | FM_NOSELECTION    // Typ
    } ;
  return XFldColMode[Column];
  }

static char *typeres = "dec\0string\0point\0cont\0strfield\0flag\0scale\0date\0time\0long\0obj\0";
static char *typenames[] = 
  {
  /* VAR_LONG     */ "long" ,
  /* VAR_DEC      */ "dec" ,
  /* VAR_STR      */ "string" ,
  /* VAR_POINT    */ "point" ,
  /* VAR_CONT     */ "cont" ,
  /* VAR_STRARR   */ "strfield" ,
  /* VAR_FLAG     */ "flag" ,
  /* VAR_SCALE    */ "scale" ,
  /* VAR_PICTURE  */ "" ,
  /* VAR_DATE     */ "date" ,
  /* VAR_PROC     */ "" ,
  /* VAR_IMAGE    */ "" ,
  /* VAR_DWORD    */ "long" ,
  /* VAR_OBJ      */ "obj" ,
  /* VAR_BITMAP   */ "" ,
  /* VAR_TIME     */ "time"
  };
LPSTR GlobFldList::GetFieldString (LPVOID Context,int Column)
  {
  static char res[256];
  LPVARDEF v = LPVARDEF (Context);
  switch (Column) {
    case 0 :    // Feldname
      return v->GetName();
      break ;
    case 1 :    // Datentyp
      return typenames[v->mType];
      break ;
    }
  return NULL;
  }

LPSTR GlobFldList::GetHdString (int Column)
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
    }
  return NULL;
  }

void GlobFldList::Save (LPFLDLINE line,int column)
  {
  }

int GlobFldList::GetFormat()
  {
  return 2 ;
  }

LPVOID GlobFldList::GetFirstContext()
  {
  if (BaseContext != NULL) {
    LPTABLEDEF t = LPTABLEDEF (BaseContext);
    if (t->GetAnzVars() > 0)
      return t->GetVarDef(0);
    else {
      GetTableAdmin()->FreeTable(t->GetTableID(),t->GetVersion());
      BaseContext = NULL;
      }
    }
  return NULL;
  }

LPVOID GlobFldList::GetNextContext(LPVOID oldContext)
  {
  LPTABLEDEF t = LPTABLEDEF (BaseContext);
  int AnzVars = t->GetAnzVars();
  for (int i = 0 ; i < AnzVars ; i++) {
    LPVARDEF v = t->GetVarDef(i);
    if (v == LPVARDEF(oldContext)) {
      if (i < AnzVars - 1) return t->GetVarDef(i+1) ;
      else {
        GetTableAdmin()->FreeTable(t->GetTableID(),t->GetVersion());
        BaseContext = NULL;
        return NULL ;
        }
      }
    }
  return NULL;
  }

BOOL GlobFldList::EnableNewContext()
  {
  return TRUE ;
  }

LPSTR GlobFldList::GetMenuName()
  {
  return "GLSTMENU";
  }

extern HWND GetGTableWnd ();
void GlobFldList::OnDestroy()
  {
  LPTABLEDEF td = LPTABLEDEF (BaseContext);
  if (td != NULL)
    GetTableAdmin()->FreeTable (td->GetTableID(),td->GetVersion());
  if (FileName != NULL) FreeGlobMem (FileName);
  MyProfFlush ();
  }

LPSTR GlobFldList::ProfBase()
  {
  return "FLST";
  }

#define ID_TYPELIST   40000
extern HINSTANCE MyInstance;
LPSTR GlobFldList::GetResource (int Column)
  {
  static char res[256];
  res[0] = res[1] = '\0';

  switch (Column) {
    case 1 :
      return typeres;
    break ;
    }

  return res;
  }

BOOL GlobFldList::EnableInput ()
  {
  return TRUE ;
  }

int GlobFldList::GetColWidth(int Column)
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
      }
    ColWidth[Column] = GetProfInt (wstring,def);
    }
  return ColWidth[Column];
  }

GlobFldList FAR *_actGLst;
extern LPSTR GetEdText (HWND hWnd,WORD Id,LPSTR old);

DLLExport BOOL _export FAR PASCAL GAttribProc (HWND hWnd,unsigned msg,WPARAM wP,LONG lP)
  {
  switch (msg) {
    case WM_INITDIALOG :
      SetDlgItemText (hWnd,101,_actGLst->Caption);
      SetDlgItemText (hWnd,104,_actGLst->FileName);
      return TRUE ;
      break ;
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDOK :
          {
          _actGLst->Caption = GetEdText (hWnd,101,_actGLst->Caption);
          _actGLst->FileName = GetEdText (hWnd,104,_actGLst->FileName);
          if ((_actGLst->Caption != NULL) && (_actGLst->FileName != NULL)) {
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

void GlobFldList::Attribute()
  {
  _actGLst = this ;
  DLGPROC dlgproc = DLGPROC (MakeProcInstance (FARPROC(GAttribProc),MyInstance));
  DialogBox (MyInstance,"ATTRIBUTE",hWnd,dlgproc);
  FreeProcInstance (dlgproc);
  }

void GlobFldList::OnCommand (WORD wP)
  {
  switch (wP) {
    case 110 :
      Store();
      break ;
    case 111 :
      Attribute();
      break ;
    }
  }

extern HMENU GetTbLstMenu ();
HMENU GetGlobLstMenu ()
  {
  return GetTbLstMenu();
  }
void WorkOnGlobTable (LPSTR TableName)
  {
  WndDef wd[1];
  wd[0].x0 = 0 ;    wd[0].x1 = 1000 ;
  wd[0].y0 = 0 ;    wd[0].y1 = 1000 ;
  if (CreateChildWindowsInMDI (TableName,1, wd, 0L,GetGlobLstMenu ())) {
    BOOL found;
    WORD Version;
    WORD TableID = GetTableAdmin()->GetTableID (NULL,TableName,&found,&Version);
    GlobFldList FAR *lst;
    if (found) {
      LPTABLEDEF td = GetTableAdmin()->GetTableDef (TableID,Version);
      lst = new GlobFldList (td,td->GetName());
      LPSTR FName = td->GetFileName();
      if (FName != NULL) {
        lst->FileName = LPSTR(GetGlobMem (lstrlen(FName)+1));
        lstrcpy (lst->FileName,FName);
        }
      lst->Create (wd[0].hWnd);
      lst->Show ();
      }
    }
  }

void CreateNewGlobTable ()
  {
  WndDef wd[1];
  wd[0].x0 = 0 ;    wd[0].x1 = 1000 ;
  wd[0].y0 = 0 ;    wd[0].y1 = 1000 ;
  if (CreateChildWindowsInMDI ("<unbekannt>",1, wd, 0L,GetGlobLstMenu ())) {
    GlobFldList FAR *lst = new GlobFldList (NULL,"<unbekannt>");
    lst->Create (wd[0].hWnd);
    lst->Show ();
    }
  }

static char *GDDEXT = "GDD";
void GlobFldList::GetOutFileName (LPSTR fName)
  {
  lstrcpy (fName,FileName);
  for (LPSTR h = fName ; *h ; h++) {
    if (*h == '.') {
      lstrcpy (h+1,GDDEXT);
      break ;
      }
    }
  if (*h == '\0') {
    *h = '.' ;
    lstrcpy (h+1,GDDEXT);
    }
  }

BOOL GlobFldList::WriteHeader (GLOBALHANDLE FAR *hGtxt,LPSTR TableName)
  {
  char outstring[128];
  wsprintf (outstring,"struct %s {\r\n",TableName);
  PushDataToHandle (outstring,lstrlen(outstring),hGtxt);
  return TRUE ;
  }

BOOL GlobFldList::WriteField (GLOBALHANDLE FAR *hGtxt,LPFLDLINE h)
  {
  char t1[128],t2[40];
  char outstring[256];
  BOOL res = ((GetFieldContent (t1,h,0)) &&
              (GetFieldRes (t2,h,1,TRUE)) && 
              (VarNames->CheckName (t1)));
  wsprintf (outstring,"  %s %s;\r\n",LPSTR(t2),LPSTR(t1));
  PushDataToHandle (outstring,lstrlen(outstring),hGtxt);
  return TRUE ;
  }

BOOL GlobFldList::WriteFieldEnd (GLOBALHANDLE FAR *hGtxt)
  {
  char outstring[32];
  lstrcpy (outstring,"  };");
  PushDataToHandle (outstring,lstrlen(outstring),hGtxt);
  return TRUE ;
  }

extern BOOL GenGScript (HWND hWnd,LPSTR fname);
extern void GetPrePostGlobParts (LPSTR Caption,LPSTR fName,GLOBALHANDLE FAR *PreText,GLOBALHANDLE FAR *PostText);
extern void WriteToFile (HFILE fm,GLOBALHANDLE hGtxt);
BOOL GlobFldList::Store()
  {
  HCURSOR oldCursor = SetCursor (LoadCursor (NULL,IDC_WAIT));
  if ((FileName != NULL) && (Caption != NULL)) {

    GLOBALHANDLE hGtxt = InitializeHandleForPush ();
    BOOL correct = WriteHeader (&hGtxt,Caption);
    VarNames = new FldCheck();
    for (LPFLDLINE h = FirstLine ; ((h != NULL) && (correct)) ; h = h->Next) {
      correct = WriteField (&hGtxt,h);
      }
    if (correct)
      WriteFieldEnd (&hGtxt);
    else {
      Fehler ("Definitionsfehler");
      ActiveLine = h;
      ActiveCol = 0;
      Show();
      SetFocus (hWnd);
      }
    GLOBALHANDLE PreText = 0,PostText = 0;
    if (correct) {
      OFSTRUCT Of;
      char fName[128];
      GetOutFileName (fName);
      GetPrePostGlobParts (Caption,fName,&PreText,&PostText);
      HFILE fm = OpenFile (fName,&Of,OF_CREATE);
      if ((PreText == 0) && (PostText == 0)) {
        char instring[32];
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
      
      if (fm) {
        GenGScript (hWnd,fName);
        }
      }
    if (VarNames != NULL) delete VarNames , VarNames = NULL;
    if (PreText)
      GlobalFree (PreText);
    GlobalFree (hGtxt);
    if (PreText)
      GlobalFree (PostText);
    SendMessage (hWnd,WM_SETTEXT,0,LPARAM(Caption));

    SetCursor (oldCursor);
    return TRUE ;
    }
  else {
    Fehler ("Name der Ausgabedatei nicht bekannt");
    SetCursor (oldCursor);
    return FALSE ;
    }
  }
