/////////////////////////////////////////////////////////////////
//  Anzeigen von Listen - Klassen, Strukturen, Defines
/////////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/include/rev/list.hpv   1.9   06 Mar 2000 07:09:40   Hannes  $
//  $Log:   F:/marille/clinicum/include/rev/list.hpv  $
// 
//    Rev 1.9   06 Mar 2000 07:09:40   Hannes
// Neuer Prototyp UpdateElem
// 
//    Rev 1.8   20 Oct 1999 07:49:26   Hannes
// 
//    Rev 1.7   27 Apr 1999 01:48:24   Hannes
// Multiselektionsmodus
// 
//    Rev 1.6   05 Mar 1999 10:55:52   Hannes
// Diverse Verbesserunge Combo - Liste
// 
//    Rev 1.5   26 Nov 1998 08:22:14   Hannes
// SetLineObject ohne Objekte
// 
//    Rev 1.4   27 Jul 1998 15:14:46   Hannes
// lSetUpCallBack
// 
//    Rev 1.3   16 Mar 1998 09:04:32   Hannes
// SetListClickProc ... Position wird zurueckgeliefert
// 
//    Rev 1.2   13 Mar 1998 18:55:40   Hannes
// Listenklickprozedur
// 
//    Rev 1.1   23 Feb 1998 20:01:26   Hannes
// TestRecord: RestoreListFnc
// 
//    Rev 1.0   31 Jan 1998 22:23:04   Martin
// Initial revision.
// 

#define HEADER_RATIO  12 / 10

#define MODE_MULTISELECTION     0x0001   // wird in der Funktion "mode(mdiChild c)" maskiert
#define MODE_DRAWMULTISELRECT   0x0010   // wird in der Funktion "DrawMultiSelRect(mdiChild c)" maskiert
#define MODE_NORMALSIZE         8192     // Darstellung ohne Vergroesserung


struct FAR ExtraData {
  DWORD AnzExtra;
  DWORD Extra[1];
  };
typedef ExtraData FAR *LPEXTRADATA;

#pragma pack(1)
struct FAR SetLineObjects_param {
  WORD parSize ;
  DWORD lst;
  DWORD flds[1];
  int AnzFlds()
    { return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; } 
  };
#pragma pack()

#pragma pack(1)
struct FAR NonRepeativeObjects_param {
  WORD parSize;
  DWORD lst;
  DWORD flds[1];
  int AnzFlds()
    { return (parSize - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; } 
  BOOL InList (DWORD Ref)
    {
    int af = AnzFlds() ;
    for (int i = 0 ; i < af ; i++)
      if (Ref == flds[i]) return TRUE ;
    return FALSE ;
    }
  };
#pragma pack()

struct FAR ShowData {
  DWORD Format;
  DWORD AnzDataToShow;
  struct FAR {
    DWORD ref;
    DWORD width;
    } v[1];
  };
typedef ShowData FAR *LPSHOWDATA;

struct FAR ObjectData {
  DWORD ProcToCall;
  DWORD _AnzObjects;
  DWORD ref[1];
  int AnzObjects (mdiChild *c)
    {
    DBWIN_ASSERT (c->IsConst (_AnzObjects));
    return *((DBINT FAR *) c->ReadlData (_AnzObjects));
    }
  };
typedef ObjectData FAR *LPOBJECTDATA;

#define REMOVE_FIRST    TRUE

#pragma pack(1)
struct FAR lShowList_param {
  tool_header hd;
  // weitere Abmessungen und aehnliches
  DWORD Disable;
  LONG  w,h;
  DWORD Access;         // Zugriff
  DWORD RecsToGet; 
  DWORD RecsToCache;
  DWORD TableName;      // Tabelle
  DWORD pntcmd;         // Zeicenscript 
  DWORD mode ;          // Multi - Selektion / Single - Selektion
  DWORD Help;
  DWORD AnzSelParams;   // Parameter fuer die Selektion
  DWORD Param[1] ;
  };
#pragma pack()

#pragma pack(1)
struct FAR lShowList_extparam {
  tool_header hd;
  // weitere Abmessungen und aehnliches
  DWORD Disable;
  LONG  w,h;
  DWORD Access;         // Zugriff
  DWORD Order;          // Sortierung
  DWORD TableName;      // Tabelle
  DWORD mode ;          // Multi - Selektion / Single - Selektion
  DWORD Help;
  DWORD AnzSelParams;   // Parameter fuer die Selektion
  DWORD Param[1] ;
  // Dahinter je nach Typ DShow() oder DObj()
  };
#pragma pack()

struct ShowDBCallList_param;
class FAR lShowParDesc {
 protected :
  LPVOID ParData;
  DBINT asp;
  DBINT mval;
  BOOL mread;
 public :
  lShowParDesc (LPVOID p,mdiChild *c)
    { 
    ParData = p ; 
    if (c != NULL) {
      if (((lShowList_param FAR *)ParData)->AnzSelParams < 0xFFFFFFFE) {
        DBWIN_ASSERT (c->IsConst (((lShowList_param FAR *)ParData)->AnzSelParams));
        asp = *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->AnzSelParams)); 
        }
      else {
        asp = 0;
        }
      }
    }
  int AnzSelParams ()
    {
    return asp;
    }
  virtual LPEXTRADATA Extra() 
    { 
    return (AnzSelParams() > 0) ? LPEXTRADATA (LPSTR(ParData) + sizeof(lShowList_param) + ((AnzSelParams() - 1) * sizeof(DWORD))) : 
                                  LPEXTRADATA (LPSTR(ParData) + sizeof(lShowList_param) - sizeof(DWORD)) ; 
    }
  virtual int AnzExtra (mdiChild *c)
    { 
    LPEXTRADATA x = Extra() ;
    if (x->AnzExtra >= 0xFFFFFFFE) return 0 ;
    else {
      DBWIN_ASSERT(c->IsConst(x->AnzExtra));
      return *((DBINT FAR *) c->ReadlData (x->AnzExtra)) ; 
      }
    }
  virtual DWORD FAR *ExtraData()
    { return Extra()->Extra ; }
  // Nur fuer die Stringliste
  virtual LPSHOWDATA DShow(mdiChild *c)
    { LPEXTRADATA x = Extra(); return LPSHOWDATA (LPSTR(x) + sizeof(DWORD) + AnzExtra(c) * sizeof(DWORD)) ; }
  // Nur fuer die Objektliste
  virtual LPOBJECTDATA DObj(mdiChild *c)
    { LPEXTRADATA x = Extra(); return LPOBJECTDATA (LPSTR(x) + sizeof(DWORD) + AnzExtra(c) * sizeof(DWORD)) ; }
  virtual DWORD Access()
    { return ((lShowList_param FAR *)ParData)->Access; }
  virtual int RecsToGet(mdiChild *c)
    { 
    if (((lShowList_param FAR *)ParData)->RecsToGet != 0xFFFFFFFF) {
      DBWIN_ASSERT (c->IsConst (((lShowList_param FAR *)ParData)->RecsToGet));
      return *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->RecsToGet)); 
      }
    else
      return - 1;
    }
  virtual int RecsToCache(mdiChild *c)
    { 
    if (((lShowList_param FAR *)ParData)->RecsToCache != 0xFFFFFFFF) {
      DBWIN_ASSERT (c->IsConst (((lShowList_param FAR *)ParData)->RecsToCache));
      return *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->RecsToCache)); 
      }
    else
      return -1;
    }
  virtual DWORD pntcmd()
    { return ((lShowList_param FAR *)ParData)->pntcmd; }
  virtual void SetMode(DWORD m)
    { ((lShowList_param FAR *)ParData)->mode = m; mread = FALSE; }
  virtual int mode(mdiChild *c)
    {
    if (((lShowList_param FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0x000F); 
      }
    else if (((lShowList_param FAR *)ParData)->mode <= 0xFFFFFFFE)
      return 1 ;
    else
      return 0 ;
    }
  virtual int withNormalSize(mdiChild *c)
    {
    if (((lShowList_param FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 8192); 
      }
    else
      return 0 ;
    }
  virtual DWORD ModePar ()
    {
    return ((lShowList_param FAR *)ParData)->mode ;
    }
  virtual int backward(mdiChild *c)
    {
    if (((lShowList_param FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0xFF00); 
      }
    else
      return FALSE ;
    }
  virtual BOOL SubSelFollows(mdiChild *c)
    {
    if (((lShowList_param FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0xF000); 
      }
    else
      return FALSE ;
    }
  virtual int DrawMultiSelRect(mdiChild *c)
    {
    if (((lShowList_param FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_param FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0x00F0); 
      }
    else
      return FALSE ;
    }
  virtual DWORD FAR *Param()
    { return ((lShowList_param FAR *)ParData)->Param; }
  virtual DWORD TableName()
    { return ((lShowList_param FAR *)ParData)->TableName; }
  virtual DWORD Help()
    { return ((lShowList_param FAR *)ParData)->Help; }
  virtual BOOL DoSetOrder()
    { return FALSE ; }
  virtual DWORD Order()
    { return 0L; }

  LPVOID ConnectionAddress()
    { return ParData; }

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj) ; }

  virtual LPSTR GetDlgSel (LPSTR dlgText,BOOL withSet);
  virtual BOOL UseDlgParams (mdiChild *c,ShowDBCallList_param FAR *par);
  };
class FAR lShowParExtDesc : public lShowParDesc {
 public :
  lShowParExtDesc (LPVOID p,mdiChild *c) : lShowParDesc (p,NULL)
    {
    if (c != NULL) {
      if (((lShowList_extparam FAR *)ParData)->AnzSelParams < 0xFFFFFFFE) {
        DBWIN_ASSERT (c->IsConst (((lShowList_extparam FAR *)ParData)->AnzSelParams));
        asp = *((DBINT FAR *) c->ReadlData (((lShowList_extparam FAR *)ParData)->AnzSelParams)); 
        }
      else
        asp = 0 ;
      }
    }
  virtual LPEXTRADATA Extra() 
    { 
    return NULL ;
    }
  virtual int AnzExtra (mdiChild *c)
    { return 0 ; }
  virtual DWORD FAR *ExtraData()
    { return NULL ; }
  virtual DWORD FAR *Param()
    { return ((lShowList_extparam FAR *)ParData)->Param; }
  // Nur fuer die Stringliste
  virtual LPSHOWDATA DShow(mdiChild *c)
    { DWORD FAR *p = Param(); return LPSHOWDATA (p + AnzSelParams()) ; }
  // Nur fuer die Objektliste
  virtual LPOBJECTDATA DObj(mdiChild *c)
    { DWORD FAR *p = Param(); return LPOBJECTDATA (p + AnzSelParams()) ; }
  virtual DWORD Access()
    { return ((lShowList_extparam FAR *)ParData)->Access; }
  virtual int RecsToGet(mdiChild *c)
    { return 50 ; }
  virtual int RecsToCache(mdiChild *c)
    { return 300 ; }
  virtual DWORD pntcmd()
    { return 0L ; }
  virtual void SetMode(DWORD m)
    { ((lShowList_extparam FAR *)ParData)->mode = m; mread = FALSE; }
  virtual int mode(mdiChild *c)
    {
    if (((lShowList_extparam FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_extparam FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0x000F); 
      }
    if (((lShowList_extparam FAR *)ParData)->mode < 0xFFFFFFFF)
      return 1 ;
    else
      return FALSE ;
    }
  virtual int withNormalSize(mdiChild *c)
    {
    if (((lShowList_extparam FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_extparam FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 8192); 
      }
    else
      return FALSE ;
    }
  virtual int backward(mdiChild *c)
    {
    if (((lShowList_extparam FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_extparam FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0x0F00); 
      }
    else
      return FALSE ;
    }
  virtual BOOL SubSelFollows(mdiChild *c)
    {
    if (((lShowList_extparam FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_extparam FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0xF000); 
      }
    else
      return FALSE ;
    }
  virtual int DrawMultiSelRect(mdiChild *c)
    {
    if (((lShowList_extparam FAR *)ParData)->mode < 0xFFFFFFFE) {
      if (!mread) {
        mval = *((DBINT FAR *) c->ReadlData (((lShowList_extparam FAR *)ParData)->mode));
        mread = TRUE;
        }
      return (mval & 0x00F0); 
      }
    else
      return FALSE ;
    }
  virtual DWORD ModePar ()
    {
    return ((lShowList_extparam FAR *)ParData)->mode ;
    }
  virtual DWORD Help()
    { return ((lShowList_extparam FAR *)ParData)->Help; }
  virtual DWORD TableName()
    { return ((lShowList_extparam FAR *)ParData)->TableName; }
  virtual BOOL DoSetOrder()
    { return TRUE ; }
  virtual DWORD Order()
    { return ((lShowList_extparam FAR *)ParData)->Order; }

  virtual LPSTR GetDlgSel (LPSTR dlgText,BOOL withSet);
  virtual BOOL UseDlgParams (mdiChild *c,ShowDBCallList_param FAR *par);
  };

#pragma pack(1)
struct FAR lPrint_param {
  WORD  parSize;
  DWORD lRef;
  DWORD DriverName;
  DWORD doPortrait;
  DWORD doLandscape;
  DWORD defaultsource;
  DWORD papersize;
  DWORD AnzCopys;
  DWORD xLeft,yTop,xRight,yBottom;
  DWORD printProc;
  // Dahinter steht lpobjectdata fuer den Header, die Zeile und den Bottom
  LPOBJECTDATA DObjHeader(mdiChild *c)
    { return LPOBJECTDATA (this + 1) ; }
  LPOBJECTDATA DObjLine(mdiChild *c)
    { LPOBJECTDATA h = DObjHeader(c); return LPOBJECTDATA(LPSTR (h + 1) + (h->AnzObjects(c) - 1) * sizeof(DWORD)) ; }
  LPOBJECTDATA DObjBottom(mdiChild *c)
    { LPOBJECTDATA l = DObjLine(c); return LPOBJECTDATA(LPSTR (l + 1) + (l->AnzObjects(c) - 1) * sizeof(DWORD)) ; }
  BOOL LastEndPageFlagGiven(mdiChild *c)
    {
    LPOBJECTDATA b = DObjBottom(c);
    return ((int)parSize >= ((LPSTR (b + 1) + (b->AnzObjects(c)) * sizeof(DWORD)) - LPSTR(this)));
    }
  DWORD LastEndPageFlagRef(mdiChild *c)
    {
    LPOBJECTDATA b = DObjBottom(c);
    return *LPDWORD((LPSTR (b + 1) + (b->AnzObjects(c) - 1) * sizeof(DWORD))) ;
    }
  };
#pragma pack()

// class FAR ScListEntry;
#define MAXSCCOUNT    3
struct FAR Column_def {
  DWORD Text;
  DWORD Width;
  };
// class FAR ObjectEntry;
struct SelectSubLines_Data {
  int ObjNmbr;
  int LineNmbr;
  };

#define MAXINDEX  30
#pragma pack(1)
struct FAR PaintFullHeader_param {
  WORD parSize;
  DWORD lRef;
  DWORD Format;
  Column_def cd[1];

  int AnzColumns ()
    { return (parSize - (sizeof(*this) - sizeof(cd[0]))) / sizeof(cd[0]) ; }
  };
#pragma pack()

class FAR ListObj : public wobj {
 public :
  lShowParDesc FAR *par;
  mdiChild *c;

  // Hilfsdaten in dem Parameterblock
  LPOBJECTDATA objd;
  LPSHOWDATA sdata;

  LPCONNEXTRAINFO ExtraDataAtCreation ;

  DDSList    FAR *MyList;
  RecordList FAR *dblist;
  DWORD      lptr;
  BOOL       updateDone;
  BOOL       DelayUpdates;
  BOOL       DelayDone;
  int        DelayTime;
  LPTABLEDEF td;
  LPSTR      AliasName;
  BOOL       IsActivated;

  MultiProc FAR *mpp;
  void DoPrint (lPrint_param FAR *par);
  BOOL AllowMultiSel;

  ListObj (mdiChild *doc)
    {
    c = doc ;
    }

  int scount;
  LPPRIMKEY FAR *k;
  LPPRIMKEY DefSel;
  DWORD SetStateProc;
  DWORD ClearStateProc;
  int AnzSelections ()
    { return scount ; }
  void DoSelCallBack (BOOL state,LPPRIMKEY kc);
  BOOL IsKeySelected (LPPRIMKEY kn);
  void AddSelKey (LPPRIMKEY kn);
  void RemoveSelKey (LPPRIMKEY kn);
  void ResetSelection ();
  void _ToggleSelKey (LPPRIMKEY kn);
  void ToggleSelKey (LPDBRECORD rec,OutParam FAR *op);
  void _ForceSelection (LPPRIMKEY kn);
  void ForceSelection (LPDBRECORD rec,OutParam FAR *op);
  void _SetSingleSelKey (LPPRIMKEY kn);
  void SetSingleSelKey (LPDBRECORD r,OutParam FAR *op);
  void SetSelCallBack (DWORD SetProc,DWORD ClearProc)
    { SetStateProc = SetProc ; ClearStateProc = ClearProc ; }
  void _SetDefSel (LPPRIMKEY k,BOOL forceIt);
  void SetDefSel (LPDBRECORD rec,OutParam FAR *op,BOOL forceIt);
  void DelDefSel ();
  DWORD FocusFunction;
  void DoFocusFunction ();
  void SetSelMode (DWORD mode);

  void SetDelay ();
  void DoUpdate ();
  BOOL IsUpdateToDo ();

  WORD TableInd;

  // Callback - Funktionen
  DRAWITEM DrawItem ;
  GETELEMEX Initialize ;
  UPDATEELEM Update ;
  GETELEM GetNext ;
  GETELEM GetPrev ;
  GETSCROLLPOS GetScrollPos ;
  SETSCROLLPOS SetScrollPos ;
  ISSELECTED IsSelected ;
  COMPAREDATA CompareData ;
  GETFIRST GetFirst ;
  GETFIRST GetLast ;
  PROCESSMSG Processmsg ;
  DDSLISTNOTIFY Notify ;
  PRINTPAGE drawheadline;
  PRINTPAGE drawbottomline;
  PRINTPAGE startpage;
  PRINTENDPAGE endpage;
  GETHEADER GetHeader;
  DRAWITEM  PaintHeader;
  DRAWITEM  PaintBottom;
  SELECTSUBLINES SelectSubLines ;
  BOOL useSimpleList;
  int AnzahlHdZeilen;

  DWORD SelectProc;   // Nur in Verwendung mit CreateDlgList 
  DWORD SelChangeCallback;
  DWORD DeleteCallBack;
  void SetSelChangeCallback (DWORD procPtr)
    {
    SelChangeCallback = procPtr;
    }
  void SetDelCallBack (DWORD procPtr)
    {
    DeleteCallBack = procPtr;
    }
  DWORD DblClkCallback;
  DWORD UpClkCallback;
  void SetDblCallBack (DWORD procPtr)
    {
    DblClkCallback = procPtr;
    }
  void SetUpCallBack (DWORD procPtr)
    {
    UpClkCallback = procPtr;
    }
  void DoDblClk (LPDBRECORD rec,OutParam FAR *h);
  void DoUpClk (LPDBRECORD rec,OutParam FAR *h);

  DWORD HeaderClkCallback[MAXINDEX];
  void SetHeaderClkCallBack (DWORD procPtr, short Index)
    {
    DBWIN_ASSERT (Index < MAXINDEX);
    HeaderClkCallback[Index] = procPtr;
    }
  void DoHeaderClk (LPPOINT lppt);

  LPDBRECORD oldSelRecord;
  void SetNewSelection (LPDBRECORD rec,OutParam FAR *op);
  void ResetOldSelection ();
  void ResetOldSelection (LPDBRECORD recToDel);

  int MaxSels;
  int SelMode;
  int LogHeight;
  void SetMaxSelCount (int mSels,int sm)
    {
    MaxSels = mSels ;
    SelMode = sm;
    }
  void GetCallBacks ();
  void ReleaseCallBacks ();
  void CreateList (HWND hWndParent,int x,int y,int w,int h);
  BOOL CreateDlgList (HWND hwParent,LPRECT fRect,LPRECT cRect,BOOL doShowDelButton,int w,int h,LPSTR sel,LPVOID StartData,DWORD startProc,DWORD selCallBack,DWORD delCallBack,BOOL doCheckAnzSels);
  GETHEADER GetHeaderCB();
  GETHEADER ObjGetHeaderCB();
  DRAWITEM PaintHeaderCB();
  DRAWITEM ObjPaintHeaderCB();
  DRAWITEM PaintBottomCB();
  DRAWITEM ObjPaintBottomCB();
  PaintFullHeader_param FAR *HdPar;
  void SetHdPar(PaintFullHeader_param FAR *p)
    { HdPar = p ; }

  void SetConnections ();
  void ClearConnections ();

  virtual BOOL ConnectEntrys ()
    { return FALSE ; }
  virtual void DoInit ()
    { }

  void SetOutParam (OutParam FAR *op);
  virtual LPVOID UseRecord (LPDBRECORD h,OutParam FAR *op,HDC hDC,int FAR *height,lPrint_param FAR *prParam);
  DWORD TestProc;
  DWORD TestRes;
  SetLineObjects_param FAR *slo_p ;
  NonRepeativeObjects_param FAR *nro_p;
  void SetLineObjects (SetLineObjects_param FAR *p)
    {
    slo_p = p ;
    if (p != NULL) {
      MyList->DoSelectSubLines (SelectSubLines,sizeof(SelectSubLines_Data));
      MyList->Adjust();
      }
    else {
      MyList->DoSelectSubLines (NULL,0);
      MyList->Adjust();
      }
    }
  
  void NonRepeativeObjects (NonRepeativeObjects_param FAR *p)
    {
    nro_p = p ;
    MyList->SetNonRepeativePaint ();
    }
  void SetTestProc (DWORD proc,DWORD res)
    {
    TestProc = proc ;
    TestRes = res ;
    }
  DWORD ClickProc,ClickPos;
  void SetClickProc (DWORD proc,DWORD pt)
    {
    ClickProc = proc ;
    ClickPos = pt ;
    }
  void doClk (LPDBRECORD rec,OutParam FAR *op,int x,int y);

  LPSTR GetAccessName()
    { return LPSTR(c->ReadlData (par->Access())); }
  int GetAnzRecsToGet()
    { return par->RecsToGet(c); }
  int GetAnzRecsToCache()
    { return par->RecsToCache(c); }
  LPPARAM GetLPParams(LPPARAM p);
  LPTABLEDEF GetTableDef();
  void FreeTableDef ();

  BOOL IsOuterSet;
  LPVOID fparam;
  void SetOuterList (RecordList FAR *l,LPVOID fp)
    { IsOuterSet = TRUE ; dblist = l; fparam = fp; }

  virtual BOOL IsStringList()
    { return FALSE ; }
  virtual BOOL IsObjectList()
    { return FALSE ; }
  virtual BOOL IsMPObjectList()
    { return FALSE ; }

  void SelRange (WORD mode);

  virtual ~ListObj ();

  DWORD afterStart;
  void AfterStart ()
    {
    if (afterStart != 0L) {
      c->ExCuteProc (afterStart,EM_LOAD);
      c->ExCuteProc (afterStart,EM_RESET);
      }
    }
  BOOL TestRecord (LPDBRECORD r,OutParam FAR *op,DWORD procToTest = 0L,DWORD testFlag = 0L);
  };
typedef ListObj FAR *LPLISTOBJ;
typedef ExternTool FAR *LPEXTTOOL;

