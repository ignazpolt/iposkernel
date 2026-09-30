/////////////////////////////////////////////////////////////////////
//  Templates fuer Dialog- und Formulareditor
////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/template.hpv   1.20   28 Aug 1997 15:54:10   gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/template.hpv  $
// 
//    Rev 1.20   28 Aug 1997 15:54:10   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.19   04 Nov 1996 15:12:26   HANNES
// 
//    Rev 1.18   02 Jul 1996 16:56:48   GERHOLD
// GetCommand
// 
//    Rev 1.17   28 May 1996 14:46:10   GERHOLD
// #pragma pack
// 
//    Rev 1.16   02 Feb 1996 11:12:14   gerhold
// GetCommand (StartParam, EndParam)
// 
//    Rev 1.15   27 Aug 1995 13:00:52   HANNES
// 
//    Rev 1.14   10 Jul 1995 19:58:30   GERHOLD
// ColorRect
// 
//    Rev 1.13   17 May 1995 15:56:28   HANNES
// Direktes Aendern von Texten in Ausgabefeldern
// 
//    Rev 1.12   27 Mar 1995 10:42:00   GERHOLD
// 
//    Rev 1.11   20 Mar 1995 08:45:32   HANNES
//  
// 
//    Rev 1.10   17 Oct 1994 14:53:42   HANNES
// Tracing eingebaut
// 
//    Rev 1.9   05 Oct 1994 08:48:30   HANNES
// Header in den Listen
// 
//    Rev 1.8   05 Sep 1994 18:55:46   GERHOLD
// die drei neuen Listen werden jetzt angezeigt
// 
//    Rev 1.7   05 Sep 1994 11:41:40   GERHOLD
// UpDown Control
// 
//    Rev 1.6   26 Aug 1994 12:28:04   GERHOLD
// ToolTime, ToolShortInt
// 
//    Rev 1.5   10 Aug 1994 12:09:20   GERHOLD
// Hotkeys in RESTOOL
// 
//    Rev 1.4   05 Aug 1994 20:54:42   HANNES
// DefFrmTime
// 
//    Rev 1.3   05 Aug 1994 11:58:14   GERHOLD
// XYFromRect, BmpTextPushButton
// 
//    Rev 1.2   25 Jul 1994 17:15:02   HANNES
// 
//    Rev 1.1   12 Jul 1994 18:16:18   HANNES
// 
//    Rev 1.0   12 Jul 1994 14:47:16   HANNES
// Initial revision.
//

inline BOOL mystrcmp (LPSTR ltxt,LPSTR stxt)
  {
  for ( ; ((*ltxt) && (*stxt) && (*stxt == *ltxt)) ; stxt ++ , ltxt ++ ) ;
  return (*stxt == '\0');
  }

#define EDTYPE_NONE     0
#define EDTYPE_DIALOG   1
#define EDTYPE_FORM     2

#define FORMTYPE_NONE     0
#define FORMTYPE_FORM     1
#define FORMTYPE_TRACING  2

class _EdTemplate ;
class FAR DialogElem {
 public :
  DialogElem FAR *Next;
  _EdTemplate *templ;
  LPVOID parblock;
  BOOL  IsDeleted;

  HWND hExtWnd;
  LPLINE sLine;   WORD sPos;
  LPLINE eLine;   WORD ePos;

  WORD AnzParams;
  LPSTR FAR *Param;
  void GetParCopy (WORD _AnzParams,LPSTR FAR *_Param);

  void MarkEnd (LPLINE h,WORD e);
  void AddToList ();
  void PushParToParList (LPSTR t);
  LPSTR PushPar (LPSTR t,LPLINE FAR *h,LPLINE last);
  void UpdatePar (WORD Id,LPSTR text);
  LPSTR GetCommand ();
  LPSTR GetCommand (WORD StartParam, WORD EndParam, BOOL bFirstLine);
  LPSTR GetText ();
  void FreeLines (LPLINE FAR *lSelected,LPLINE FAR *last);
  LPLINE SetCommand (LPSTR Text,LPLINE ActLine,LPTEXTBLOCK bl);

  void OnChar (char ch);
  void GetRect (HWND hWnd,LPRECT r);
  void Invalidate (HWND hWnd,BOOL erase = FALSE);
  BOOL MoveAllowed ();
  BOOL P1Allowed ();
  BOOL P2Allowed ();
  BOOL Hit (LPPOINT pt);
  BOOL ChangeHeightAllowed();
  BOOL ChangeWidthAllowed();
  BOOL HeightHit(LPPOINT pt);
  BOOL WidthHit(LPPOINT pt);
  BOOL P1Hit (LPPOINT pt);
  BOOL P2Hit (LPPOINT pt);
  void InitializeMove (int FAR *xold,int FAR *yold,int FAR *x1old,int FAR *y1old);
  void InitializeP1 (int FAR *xold,int FAR *yold);
  void InitializeP2 (int FAR *xold,int FAR *yold);
  void InitializeHeight (int FAR *h);
  void InitializeWidth (int FAR *w);
  void Move (int x,int y,int x1,int y1);
  void SetP1 (int x,int y);
  void SetP2 (int x,int y);
  void SetWidth (int x);
  void SetHeight (int y);
  void PaintSelected (HWND hWnd,HDC hDC);
  LPSTR GetObjectName();
  BOOL IsCreateScreen();

  DialogElem (_EdTemplate *t,LPLINE l,WORD s)
    {
    templ = t;
    AddToList ();
    sLine    = l;
    sPos     = s;
    }
  LPVOID GetIntMem ();
  void   Reconnect (LPVOID);
  void DelMem ();
  ~DialogElem ();

  LPVOID operator new (size_t size)
    { 
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };
typedef DialogElem FAR *LPDIALOGELEM;

class FAR ShowObject {
 public :
  ShowObject FAR *Next;
  LPDIALOGELEM elem;
  BOOL  IsDeleted;

  LPLINE sLine;   WORD sPos;
  LPLINE eLine;   WORD ePos;

  WORD AnzParams;
  LPSTR FAR *Param;

  void SetElem ();

  LPSTR GetCommand ();
  LPLINE SetCommand (LPSTR Text,LPLINE ActLine,LPTEXTBLOCK bl);
  void FreeLines (LPLINE FAR *lSelected,LPLINE FAR *last);
  LPSTR GetText ();

  void AddToList ();
  void MarkEnd (LPLINE h,WORD e);
  void PushParToParList (LPSTR t);
  LPSTR PushPar (LPSTR t,LPLINE FAR *h,LPLINE last);
  ShowObject (LPLINE l,WORD s)
    {
    AddToList ();
    sLine    = l;
    sPos     = s;
    }

  LPVOID operator new (size_t size)
    { 
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  };
typedef ShowObject FAR *LPSHOWOBJECT ;

#pragma pack(1)
struct ParamTemplate {
  WORD AnzPars;
  WORD p[1];
  };
#pragma pack()

typedef ParamTemplate FAR *LPPARTEMPLATE ;
class _EdTemplate {
 public :
  _EdTemplate   *Next;
  LPSTR         TemplateName;
  LPPARTEMPLATE pt;

  void GetParTemplate ();
  LPVOID CreateParBlock (WORD pcount,LPSTR FAR *par);
  void GetParName (LPSTR outtxt,int i);
  BOOL IsOpt (LPSTR t);
  BOOL IsVar (LPSTR t);
  BOOL DoUpdateImmediate (WORD wP);
  BOOL ShowButton (WORD wP,WORD FAR *dType);
  void DoAction (WORD wP);

  LPVOID GetIntMem (LPVOID parblock);
  void   Reconnect (LPVOID parblock,LPVOID old);

  DialogElem FAR *GetElem (LPLINE l,WORD sPos)
    { return new DialogElem (this,l,sPos); }

  BOOL CheckName (LPSTR h)
    { return mystrcmp (h,TemplateName); }
  virtual void DoEdit (LPDIALOGELEM h,WORD mode);
  BOOL IsThere (WORD Type);
  BOOL MoveAllowed (BOOL FAR *isPoint = NULL);
  BOOL P1Allowed ();
  BOOL P2Allowed ();
  void GetOrigin (LPDIALOGELEM e,int FAR *x,int FAR *y);
  void InitializeMove (LPDIALOGELEM e,LPVOID parblock,int FAR *x,int FAR *y,int FAR *x1,int FAR *y1);
#ifdef WIN32
  void GetPointPar (LPDIALOGELEM e,WORD Type,long FAR *x,long FAR *y);
#else
  void GetPointPar (LPDIALOGELEM e,WORD Type,int FAR *x,int FAR *y);
#endif
  void InitializeP1 (LPDIALOGELEM e,LPVOID parblock,int FAR *x,int FAR *y);
  void InitializeP2 (LPDIALOGELEM e,LPVOID parblock,int FAR *x,int FAR *y);
  void InitializeHeight (LPDIALOGELEM e,int FAR *h);
  void InitializeWidth (LPDIALOGELEM e,int FAR *w);
  BOOL WidthAllowed ();
  BOOL HeightAllowed ();
  void SetIntPar (WORD Type,LONG val,LPVOID parblock,LPSTR FAR *Param);
  void GetIntParWithNum (LPDIALOGELEM e,int Num,int FAR *x);

#ifdef WIN32
  void GetIntPar (LPDIALOGELEM e,WORD Type,long FAR *x);
#else
  void GetIntPar (LPDIALOGELEM e,WORD Type,int FAR *x);
#endif

  void SetPointPar (WORD Type,int x,int y,LPVOID parblock,LPSTR FAR *Param);
  virtual void ToLogKoords (int FAR *dx,int FAR *dy);
  virtual void ToAbsLogKoords (int FAR *x,int FAR *y);
  virtual void ToPointKoords (int x,int y,double FAR *xf,double FAR *yf)
    {
    *xf = double(x);
    *yf = double(y);
    }
  virtual void TransformPoint (fpt FAR *p) { } 

#ifdef WIN32
  virtual void ToAbsDevKoords (long FAR *x,long FAR *y);
#else
  virtual void ToAbsDevKoords (int FAR *x,int FAR *y);
#endif

  virtual BOOL TestParam (LPDIALOGELEM c,int i,int x,int y);
  void Move (LPDIALOGELEM e,int x,int y,int x1,int y1);
  void SetP1 (LPDIALOGELEM e,int x,int y);
  void SetP2 (LPDIALOGELEM e,int x,int y);
  void OnChar (LPDIALOGELEM e,char ch);

  virtual int GetIdOffs()
    { return 0 ; }
  virtual WORD GetToolType ()
    { return 0 ; }
  virtual WORD GetPrivSize ()
    { return 4 ; }
  virtual BOOL InsertAllowed ()
    { return TRUE ; }
  virtual void AnalyseExtraInfo (LPSTR FAR *_Param);
  virtual BOOL WorkExtern ()
    { return FALSE ; }
  BOOL IsImplemented ()
    { return ((pt != NULL) && (pt->AnzPars > 0)) ; }
  virtual LPSTR GetObjectName (LPSTR FAR *Param)
    { return Param[0] ; }
  virtual WORD GetEdType ()
    { return EDTYPE_DIALOG ; }

  int GetDscID()
    {
    return GetIdOffs() + IDDSC_BASE ;
    }
  int GetParID()
    {
    return GetIdOffs() + IDPAR_BASE ;
    }
  int GetToolID()
    {
    return GetIdOffs() + IDPIC_BASE ;
    }

  int GetHelpIndex()
    {
    return GetIdOffs() + IDHLP_BASE ;
    }

  void InsertNewElem (int x,int y);
  void InsertNewElem ();
  void DuplicateElem (LPDIALOGELEM e);

  void DelExtraData ()
    {
    if (pt != NULL) FreeGlobMem (pt) ;
    pt = NULL;
    }

  // Snapping
  virtual BOOL AvoidSnap ()
    { return FALSE ; }
  virtual int SnapXOffs (LPDIALOGELEM e)
    { return 0 ; }
  virtual int SnapYOffs (LPDIALOGELEM e)
    { return 0 ; }
  virtual int SnapX1Offs (LPDIALOGELEM e)
    { return 0 ; }
  virtual int SnapY1Offs (LPDIALOGELEM e)
    { return 0 ; }

  virtual BOOL ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2)
    { return TRUE ; }
  // Sortierung
  int SortNum (LPDIALOGELEM h);
  };

#pragma pack(1)
struct CreateScreen_param {
  WORD  fncID;
  WORD  parSize;
  DWORD ScreenId;
  DWORD ParentScreen;
  LONG  ScreenNmbr;
  DWORD Caption;
  DWORD PosRef;
  LONG  w,h;
  LONG  ModalScreen;
  };
#pragma pack()

#define DOEXTERN_SHOWLIST         300
#define DOEXTERN_SHOWPERMLIST     567
#define DOEXTERN_SHOWSTRINGLIST   568
#define DOEXTERN_SHOWCOLUMNLIST    58
#define DOEXTERN_SHOWOBJECTLIST    32
#define DOEXTERN_SHOWMPOBJECTLIST  46

#define DOEXTERN_DBCALL_STRINGLIST  307
#define DOEXTERN_DBCALL_COLUMNLIST  313
#define DOEXTERN_DBCALL_OBJLIST     314
#define DOEXTERN_DBCALL_MPOBJLIST   319

#define ID_CREATESCREEN         274
#define DOEXTERN_DOCUMENT       596
class _PushButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_PushButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_PUSHBUTTON ; }
  };
class _CheckButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_CheckButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_CHECKBUTTON ; }
  };
class _TextPushButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_TextPushButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_TEXTPUSHBUTTON ; }
  };
class _TextCheckButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_TextCheckButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_TEXTCHECKBUTTON ; }
  virtual int SnapYOffs (LPDIALOGELEM e);
  };
class _TextRadioButton : public _TextCheckButton {
 public :
  virtual int GetIdOffs()
    { return dsc_TextRadioButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_TEXTRADIOBUTTON ; }
  };
class _ComboButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ComboButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_COMBOBUTTON ; }
  virtual BOOL TestParam (LPDIALOGELEM c,int i,int x,int y);
  virtual BOOL ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2);
  };
class _UpDown : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_UpDown ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_UPDOWN ; }
  virtual BOOL TestParam (LPDIALOGELEM c,int i,int x,int y);
  virtual BOOL ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2);
  };
class _ToolEdit : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolEdit ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_EDIT ; }
  virtual int SnapYOffs (LPDIALOGELEM e);
  };
class _ToolZoom : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolZoom ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_ZOOM ; }
  };
class _ToolPage : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolPage ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_PAGE ; }
  };
class _ToolDate : public _ToolEdit {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolDate ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_DATE ; }
  };
class _ToolFloat : public _ToolEdit {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolFloat ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_FLOAT ; }
  };
class _GroupBox : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_GroupBox ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_GROUPBOX ; }
  };
class _StaticTool : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_StaticTool ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_STATIC ; }
  virtual int SnapYOffs (LPDIALOGELEM e);
  };
class _lShowList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_lShowList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_SHOWLIST ; }
  };
class _StaticBitmap : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_StaticBitmap ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_STATICBITMAP ; }
  };
class _Line3D : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_Line3D ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_3DLINE ; }
  };
class _ColorLine : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ColorLine ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_COLORLINE ; }
  };
class _ColorRect : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ColorRect ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_COLORRECT ; }
  };
class _ActionBox : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ActionBox ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_ACTIONRECT ; }
  };
class _FlapMap : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_FlapMap ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_FLAPMAP ; }
  };
class _ToolPwd : public _ToolEdit {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolPwd ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_PASSWORD ; }
  };
class _PushCheckButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_PushCheckButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_PUSHCHECKBUTTON ; }
  };
class _TransparentBitmap : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_TransparentBitmap ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_TRANSPARENTBITMAP ; }
  };
class _AnimationBitmap : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_AnimationBitmap ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_ANIMATIONBITMAP ; }
  };
class _ToolBEdit : public _ToolEdit {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolBEdit ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_BEDIT ; }
  };
class _BmpFloat : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_BmpFloat ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_BMPFLOAT ; }
  };
class _ShowPermList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ShowPermList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_SHOWPERMLIST ; }
  };
class _ShowStringList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ShowStringList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_SHOWSTRINGLIST ; }
  };
class _ShowColumnList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ShowColumnList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_SHOWCOLUMNLIST ; }
  };
class _ShowObjectList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ShowObjectList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_SHOWOBJECTLIST ; }
  };
class _ShowMPObjectList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ShowPMObjectList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_SHOWMPOBJECTLIST ; }
  };
class _ExternDocument : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ExternDocument ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_DOCUMENT ; }
  };
class _XYFromRect : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_XYFromRect ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_XYFROMRECT ; }
  };

class _BmpTextPushButton : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_BmpTextPushButton ; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_BMPTEXTPUSHBUTTON ; }
  };

class _ToolTime : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolTime; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_TIME; }
  };

class _ToolShortInt : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolShortInt; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_SHORTINT; }
  };

class _ToolLongInt : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolLongInt; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_LONGINT; }
  };

class _ToolMoney : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_ToolMoney; }
  virtual WORD GetToolType ()
    { return TOOLTYPE_MONEY; }
  };

class _CreateScreen : public _EdTemplate {
 public :
  virtual void DoEdit (LPDIALOGELEM h,WORD mode);
  virtual int GetIdOffs()
    { return dsc_CreateScreen ; }
  virtual WORD GetToolType ()
    { return ID_CREATESCREEN ; }
  virtual WORD GetPrivSize ()
    { return 0 ; }
  virtual BOOL InsertAllowed ()
    { return FALSE ; }
  virtual void AnalyseExtraInfo (LPSTR FAR *_Param);
  virtual BOOL WorkExtern ()
    { return TRUE ; }
  virtual LPSTR GetObjectName (LPSTR FAR *Param)
    { return NULL ; }
  };

#define ID_STDHEADER  565   // aus FDEF.TXT
#define GWL_EXTTOOLPTR  0
#define GWL_HEADERPTR   4
#define GWL_BOTTOMPTR   8
#define GWL_BUTTONPTR   12
#define GWL_OUTLISTPTR  16
class _PaintStdHeader : public _EdTemplate {
 public :
  virtual void DoEdit (LPDIALOGELEM h,WORD mode);
  virtual int GetIdOffs()
    { return dsc_StdHeader ; }
  virtual WORD GetToolType ()
    { return ID_STDHEADER ; }
  virtual WORD GetPrivSize ()
    { return 0 ; }
  virtual BOOL InsertAllowed ()
    { return FALSE ; }
  virtual void AnalyseExtraInfo (LPSTR FAR *_Param)
    { } 
  virtual BOOL WorkExtern ()
    { return FALSE ; }
  virtual LPSTR GetObjectName (LPSTR FAR *Param)
    { return NULL ; }
  BOOL ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2);
  };

#define ID_FULLHEADER  50   // aus FDEF.TXT
#define ID_STDBUTTON   60
#define ID_FULLBUTTON  59
#define ID_SETBUTTONS  572
#define ID_SETLIST     109
class _PaintFullHeader : public _PaintStdHeader {
 public :
  virtual int GetIdOffs()
    { return dsc_FullHeader ; }
  virtual WORD GetToolType ()
    { return ID_FULLHEADER ; }
  };
class _PaintStdButton : public _EdTemplate {
  virtual void DoEdit (LPDIALOGELEM h,WORD mode);
  virtual int GetIdOffs()
    { return dsc_StdButton ; }
  virtual WORD GetToolType ()
    { return ID_STDBUTTON ; }
  virtual WORD GetPrivSize ()
    { return 0 ; }
  virtual BOOL InsertAllowed ()
    { return FALSE ; }
  virtual void AnalyseExtraInfo (LPSTR FAR *_Param)
    { } 
  virtual BOOL WorkExtern ()
    { return FALSE ; }
  virtual LPSTR GetObjectName (LPSTR FAR *Param)
    { return NULL ; }
  int WndId()
    { return GWL_BOTTOMPTR ; }
  virtual int GetParNr()
    { return 0; }
  BOOL ExChangeAllowed (LPDIALOGELEM x1,LPDIALOGELEM x2);
  };
class _PaintFullButton : public _PaintStdButton {
  virtual int GetIdOffs()
    { return dsc_FullButton; }
  virtual int GetParNr()
    { return 0; }
  virtual WORD GetToolType ()
    { return ID_FULLBUTTON ; }
  int WndId()
    { return GWL_BOTTOMPTR ; }
  };
class _SetButtons : public _PaintStdButton {
  virtual int GetIdOffs()
    { return dsc_SetButtons; }
  virtual int GetParNr()
    { return 0; }
  virtual WORD GetToolType ()
    { return ID_SETBUTTONS ; }
  int WndId()
    { return GWL_BUTTONPTR ; }
  };
class _BindInnerListToOutList : public _PaintStdButton {
  virtual int GetIdOffs()
    { return dsc_BindInnerListToOutList; }
  virtual int GetParNr()
    { return 1; }
  virtual WORD GetToolType ()
    { return ID_SETLIST ; }
  int WndId()
    { return GWL_OUTLISTPTR ; }
  };
class _DBCallStringList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_DBCall_StringList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_DBCALL_STRINGLIST ; }
  };
class _DBCallColumnList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_DBCall_ColumnList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_DBCALL_COLUMNLIST ; }
  };
class _DBCallObjList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_DBCall_ObjList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_DBCALL_OBJLIST ; }
  };
class _DBCallMPObjList : public _EdTemplate {
 public :
  virtual int GetIdOffs()
    { return dsc_DBCall_MPObjList ; }
  virtual WORD GetToolType ()
    { return DOEXTERN_DBCALL_MPOBJLIST ; }
  };


// Indizess der Objektfunktionen
#define ID_DefFrmField                  155
#define ID_DefFrmDate                   156
#define ID_DefFrmDec                    157
#define ID_DefFrmShort                  627
#define ID_DefFrmLong                   628
#define ID_DefFrmMoney                  629
#define ID_DefFrmSLDec                  158
#define ID_DefFrmStrList                159
#define ID_DefFrmLine                   162
#define ID_DefFrmImage                  163
#define ID_Trc_DefCont                  149
#define ID_Trc_DefPattern               152
#define ID_Trc_DefmPattern              153
#define ID_Trc_DefLine                  168
#define ID_DefFrmSozNr                  178
#define ID_DefFrmDevDec                 180
#define ID_DefCheckBox                  182
#define ID_DefFrmShortStrList           188
#define ID_Trc_DefArc                   192
#define ID_DefPattern                   195
#define ID_DefFrmTab                    200
#define ID_DefFrmTabField               201
#define ID_DefTabDecField               202
#define ID_DefFrmTabShortStrList        203
#define ID_DefTabFlagField              204
#define ID_DefCheckField                209
#define ID_DefTabCheckField             210
#define ID_DefFrmStrDivList             214
#define ID_DefTabDate                   218
#define ID_DefFrmTabStrList             220
#define ID_DefTabColDec                 225
#define ID_DefFrmSlantField             236
#define ID_DefFrmSlantDec               238
#define ID_DefFrmSlantSLDec             239
#define ID_DefMovePattern               246
#define ID_DefFrmDefDec                 247
#define ID_DefFrmMultiField             248
#define ID_DefTrcImage                  279
#define ID_DefFrmStaticBitmap           444
#define ID_DefActivationRegion          461
#define ID_DefFrmBField                 469
#define ID_Trc_DefRectangle             540
#define ID_DefFrmTime                   29

class _FrmObj : public _EdTemplate {
  virtual void DoEdit (LPDIALOGELEM h,WORD mode);
  virtual WORD GetEdType ()
    { return EDTYPE_FORM ; }
  virtual LPVOID GetObject (LPDIALOGELEM h)
    { return NULL ; }
  virtual void ToLogKoords (int FAR *dx,int FAR *dy);
  virtual void ToAbsLogKoords (int FAR *x,int FAR *y);
  virtual void ToAbsDevKoords (int FAR *x,int FAR *y);
  virtual void ToPointKoords (int x,int y,double FAR *xf,double FAR *yf);
  virtual void TransformPoint (fpt FAR *p);
  };

class _DefFrmField : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmField ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  virtual int SnapYOffs (LPDIALOGELEM e);
  };
class _DefFrmDate : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmDate ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmDate ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmTime : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmTime ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmTime ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmDec : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmDec ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmShort : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmShort ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmShort ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmLong : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmLong ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmLong ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmMoney : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmMoney ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmMoney ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmSLDec : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmSLDec ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmSLDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmStrList : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmStrList ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmStrList ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmLine : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmLine ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmLine ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmImage : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmImage ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmImage ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _Trc_DefCont : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_Trc_DefCont ; }
  virtual WORD GetToolType ()
    { return ID_Trc_DefCont ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _Trc_DefPattern : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_Trc_DefPattern ; }
  virtual WORD GetToolType ()
    { return ID_Trc_DefPattern ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _Trc_DefmPattern : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_Trc_DefmPattern ; }
  virtual WORD GetToolType ()
    { return ID_Trc_DefmPattern ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _Trc_DefLine : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_Trc_DefLine ; }
  virtual WORD GetToolType ()
    { return ID_Trc_DefLine ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmSozNr : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmSozNr ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmSozNr ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmDevDec : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmDevDec ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmDevDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefCheckBox : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefCheckBox ; }
  virtual WORD GetToolType ()
    { return ID_DefCheckBox ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  virtual int SnapYOffs (LPDIALOGELEM e);
  };
class _DefFrmShortStrList : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmShortStrList ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmShortStrList ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _Trc_DefArc : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_Trc_DefArc ; }
  virtual WORD GetToolType ()
    { return ID_Trc_DefArc ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefPattern : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefPattern ; }
  virtual WORD GetToolType ()
    { return ID_DefPattern ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmTab : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmTab ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmTab ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmTabField : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmTabField ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmTabField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefTabDecField : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefTabDecField ; }
  virtual WORD GetToolType ()
    { return ID_DefTabDecField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmTabShortStrList : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmTabShortStrList ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmTabShortStrList ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefTabFlagField : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefTabFlagField ; }
  virtual WORD GetToolType ()
    { return ID_DefTabFlagField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefCheckField : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefCheckField ; }
  virtual WORD GetToolType ()
    { return ID_DefCheckField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefTabCheckField : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefTabCheckField ; }
  virtual WORD GetToolType ()
    { return ID_DefTabCheckField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmStrDivList : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmStrDivList ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmStrDivList ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefTabDate  : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefTabDate ; }
  virtual WORD GetToolType ()
    { return ID_DefTabDate ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmTabStrList : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmTabStrList ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmTabStrList ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefTabColDec : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefTabColDec ; }
  virtual WORD GetToolType ()
    { return ID_DefTabColDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmSlantField : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmSlantField ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmSlantField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmSlantDec : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmSlantDec ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmSlantDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmSlantSLDec : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmSlantSLDec ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmSlantSLDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefMovePattern : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefMovePattern ; }
  virtual WORD GetToolType ()
    { return ID_DefMovePattern ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmDefDec : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmDefDec ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmDefDec ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmMultiField : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmMultiField ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmMultiField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefTrcImage : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefTrcImage ; }
  virtual WORD GetToolType ()
    { return ID_DefTrcImage ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmStaticBitmap  : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefFrmStaticBitmap ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmStaticBitmap ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefActivationRegion : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_DefActivationRegion ; }
  virtual WORD GetToolType ()
    { return ID_DefActivationRegion ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _DefFrmBField        : public _DefFrmField {
  virtual int GetIdOffs()
    { return dsc_DefFrmBField ; }
  virtual WORD GetToolType ()
    { return ID_DefFrmBField ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };
class _Trc_DefRectangle    : public _FrmObj {
  virtual int GetIdOffs()
    { return dsc_Trc_DefRectangle ; }
  virtual WORD GetToolType ()
    { return ID_Trc_DefRectangle ; }
  virtual LPVOID GetObject (LPDIALOGELEM h);
  };


LPSTR NextParDsc (LPSTR h);
LPPARTEMPLATE PushToParTemplate (LPPARTEMPLATE pt,WORD Type);
WORD GetParType (LPSTR Name);
LPSTR ScanString (LPSTR str,BOOL FAR *isConst = NULL,BOOL checkDefs = TRUE);
DWORD ScanInt (LPSTR h);
float FAR *ScanDecVar (LPSTR txt);
LPSTR ScipEndingDigits (LPSTR txt);
void DestroyFrmWindow ();
LPVOID MyGetData (LPDIALOGELEM h,WORD Id);
VOID MySetData (LPDIALOGELEM h,WORD Id,LPVOID Data,int size,LPVOID Cmd);
fpt FAR * ScanPoint (LPSTR txt);
DWORD FAR *ScanIntVar (LPSTR txt);
int DoEditCallBack (LPDIALOGELEM h,HWND hWnd,WORD Command,LPEDCMEM m);
void GetDevRect (LPDIALOGELEM h,LPRECT r);
void ScrollPTStart (int dx,int dy);
LPSTR PushToCommand (LPSTR c,LPSTR cp);
LPSTR FindEndPar (LPSTR t,LPSTR FAR *res,LPLINE FAR *h,LPLINE last);
LPSHOWOBJECT GetShowElem (LPSTR t,LPLINE l,WORD sPos);
void SetElemPtrs ();
void DeleteShows();
int GetShownNmbr(LPDIALOGELEM elem);
void NewShow(LPSTR objName);
LPDIALOGELEM GetShownElemByNmbr(int Nmbr);
BOOL ExChangeShow (LPDIALOGELEM x1,LPDIALOGELEM x2);

