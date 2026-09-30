///////////////////////////////////////////////////////////////
//  Klasse mdiChild: FAR und in der DLL
///////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/include/rev/mdichild.hpv   1.60   03 Apr 2000 20:56:44   Hannes  $
//  $Log:   F:/marille/clinicum/include/rev/mdichild.hpv  $
// 
//    Rev 1.60   03 Apr 2000 20:56:44   Hannes
// TryToReadExtra
// 
//    Rev 1.59   23 Nov 1999 17:22:40   Hannes
// Div. Erweiterungen
// 
//    Rev 1.58   12 Aug 1999 08:27:20   Hannes
// SetVeryBestWith (mode...)
// 
//    Rev 1.57   04 Jun 1999 01:28:02   Hannes
// SetDocVeryBestWidth
// 
//    Rev 1.56   11 Jan 1999 08:18:56   Hannes
// Austausch Records im Aufrufer-> Kontextaustauch in Kindern
// 
//    Rev 1.55   29 Jun 1998 18:58:24   Hannes
// GetRecExtraData
// 
//    Rev 1.54   17 May 1998 18:20:20   Hannes
// No Autoscroll
// 
//    Rev 1.53   27 Apr 1998 12:51:20   Hannes
// 
//    Rev 1.52   17 Mar 1998 19:04:04   Hannes
// Prototyp von SetDocBestSize
// 
//    Rev 1.51   07 Jan 1998 13:03:02   Hannes
// 
//    Rev 1.50   05 Jan 1998 07:48:22   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.49   10 Nov 1997 15:22:58   Hannes
// 
//    Rev 1.48   24 Oct 1997 08:37:48   Hannes
// Umstellung von mdiChild zwecks Speichersparmassnahmen
// 
//    Rev 1.47   18 Aug 1997 18:01:48   Martin
// VTO Formular-faehig
// 
//    Rev 1.46   09 Jun 1997 13:10:26   Hannes
// 
//    Rev 1.45   12 May 1997 08:40:24   Hannes
// mdiChild friend to SetExtraData
// 
//    Rev 1.44   05 May 1997 10:46:52   Hannes
// GlobalUnlock - Count korrigiert
// 
//    Rev 1.43   28 Apr 1997 14:48:02   Hannes
// 
//    Rev 1.42   21 Apr 1997 20:45:52   Hannes
// Verschiedene Aenderungen an Virtuellen Funktionen
// 
//    Rev 1.41   11 Apr 1997 11:40:34   Gerhold
// Statuszeile jetzt mit Vorder- und Hintergrundfarbe
// 
//    Rev 1.40   10 Apr 1997 11:39:48   Hannes
// PreparelistFunction -> Ausgabeeigenschaften auch wirklich im Ausgabekontext
// setzen
// 
//    Rev 1.39   28 Feb 1997 14:37:42   Hannes
// FehlerKoorektur in GetVarSize fuer lokale Datensaetze
// 
//    Rev 1.38   19 Feb 1997 12:02:00   Hannes
// Scriptfunktionen
// 
//    Rev 1.37   08 Jan 1997 16:00:20   HANNES
// 
//    Rev 1.36   12 Dec 1996 12:20:22   HANNES
// Call auch in Multiproc's
// 
//    Rev 1.35   03 Dec 1996 16:41:24   HANNES
// 
//    Rev 1.34   31 Oct 1996 16:08:42   HANNES
// Connection auf Liste: Eigene OwnerID
// 
//    Rev 1.33   30 Oct 1996 08:42:36   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.32   03 Sep 1996 10:04:38   HANNES
// Fehlerkorrektur in GetCmdOffset
// 
//    Rev 1.31   10 Jun 1996 10:15:28   GERHOLD
// pragma pack
// 
//    Rev 1.30   02 Feb 1996 11:00:02   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.29   25 Oct 1995 13:53:24   HANNES
// Aenderungen Hannes
// 
//    Rev 1.28   14 Sep 1995 10:00:06   HANNES
// 
//    Rev 1.27   04 Sep 1995 08:56:34   HANNES
// Extchild erweitert
// 
//    Rev 1.26   14 Aug 1995 08:22:46   HANNES
// GetVarElem
// 
//    Rev 1.25   10 Aug 1995 09:19:12   HANNES
// Weiteren Konstruktor fuer SetExtraInfo ...
// 
//    Rev 1.24   11 Jul 1995 12:37:08   HANNES
// InBlock fuer Expressions
// 
//    Rev 1.23   11 Jun 1995 10:02:18   HANNES
// TryToReadExtraData
// 
//    Rev 1.22   09 Jun 1995 00:32:32   HANNES
// CSYSRECS
// 
//    Rev 1.21   04 May 1995 18:40:22   HANNES
// 
//    Rev 1.20   31 Mar 1995 13:11:58   HANNES
//  
// 
//    Rev 1.19   20 Mar 1995 12:16:24   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.18   08 Mar 1995 09:15:38   HANNES
// Forschleifen u.a.
// 
//    Rev 1.17   03 Mar 1995 18:12:04   HANNES
// 
//    Rev 1.16   24 Feb 1995 11:16:42   HANNES
//  
// 
//    Rev 1.15   29 Jan 1995 11:47:00   HANNES
// 
//    Rev 1.14   13 Jan 1995 16:56:14   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.13   09 Jan 1995 12:11:54   HANNES
// Debugger eingebaut
// 
//    Rev 1.12   08 Dec 1994 22:03:28   HANNES
// Fehlerkorrektur in Restorelistfnc
// 
//    Rev 1.11   05 Dec 1994 17:37:06   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.10   16 Nov 1994 18:38:40   GERHOLD
// GetDocBestWidth
// 
//    Rev 1.9   10 Nov 1994 14:29:06   HANNES
// Listenzeilen nicht eingebbar
// 
//    Rev 1.8   08 Nov 1994 12:43:12   HANNES
// AvoidInput
// 
//    Rev 1.7   07 Nov 1994 11:30:22   GERHOLD
// Statusbar
// 
//    Rev 1.6   17 Oct 1994 15:08:18   HANNES
// zoomChild eingebaut
// 
//    Rev 1.5   11 Oct 1994 09:43:02   HANNES
// Einbau der Zoomrect - Funktionen
// 
//    Rev 1.4   20 Sep 1994 11:31:14   HANNES
// MultiProc Handling verbessert
// 
//    Rev 1.3   24 Aug 1994 19:39:36   HANNES
// WriteData: GetCommandAddress
// 
//    Rev 1.2   05 Aug 1994 17:16:48   HANNES
// Aenderungen im Zusammenhang mit ShowObjectList
// 
//    Rev 1.1   13 Jul 1994 21:16:48   HANNES
// Prototyp von DBRecord::Set, DBRecord::Del, VarElem::Update
// 
//    Rev 1.0   24 Jun 1994 17:01:48   HANNES
// Neuuebernahme clinicum
//

#define NO_UPDATE         0
#define UPDATE_ASYNCHRON  1
#define UPDATE_SYNCHRON   2

#define CHWND_TRACING   1
#define CHWND_NUMANA    2
#define CHWND_VERBANA   3
#define CHWND_GRANA     4
#define CHWND_ENTER     5
#define CHWND_GRSTAT    6
#define CHWND_IMAGE     7
#define CHWND_FORM      8
#define CHWND_DIAGRAM   9
#define CHWND_VTO       10
#define CHWND_LAYOUT    11
#define CHWND_LISTDOC   1000

#define EXPTABLEBASE      0xEF00

struct FAR ExpressionPtr;
typedef ExpressionPtr FAR *LPEXPPTR;
struct FAR ExpressionPtr {
  LPEXPPTR Next;
  VarElem v;   // fuer die verschiedenen RunNmbrs
  LPEXPPTR FAR *ptrToThis;
  BYTE callDone;
  };

/*-------------< GetDocInfo >-------------*/
#define GETDRAWINGWINDOW         0
#define GETSCALE                 1
#define GETVIEWPORTORIGIN        2
#define GETCHARHANDLE            3
#define GETPRINTERHANDLE         4
#define ISDRAWINGALLOWED         5
#define NEEDSCROLL               6
#define VSIZECHANGE              7
#define ACTIVEFIELDCHANGE        8
#define GETLISTITEMS             9
#define INFORMABOUTFORMAT       10
#define INFORMABOUTUPDATE       11
#define SETLISTITEM             12
#define GETFLDMEM               13
#define FORMATFORSCREEN         14
#define TRYTOUPDATE             15
#define GETTABPOS               16
#define GETMAPTYPE              17
#define GETWINDOWORG            18
#define GETSELSTR               19

#define PS_GAUSSWIN             2

#define GWL_HWINFO              0

#pragma pack(1)
struct FAR DocExtraData {
  WORD Type;
  DocExtraData FAR *Next;
  int size;
  BYTE Data[1];
  };
#pragma pack()

#pragma pack(1)
struct WindowPosDef {
  int x,y,w,h;
  WORD magic;
  float scale;
  };

struct storeprefpospar {
  HWND hWnd;
  float scale;
  };

struct FAR TrackWndData {
  BOOL IsCaptured;
  BOOL IsTimerSet;
  };
#pragma pack()

typedef TrackWndData FAR *LPTRACKWNDDATA ;
BOOL TrackWndProc (HWND,UINT,WPARAM,LPARAM,LPTRACKWNDDATA);

#pragma pack(1)
struct FAR StrListInfo {
  DWORD Id;             // Identifier des Feldes, das Info haben will
  GLOBALHANDLE res;     // Buffer mit den Strings
  int Ind;              // Resultat der Selektion
  LPSTR actTxt;         // Aktueller Text
  };
#pragma pack()

struct GaussLinePar {
  double x0,dev22,xact;
  };

struct GaussPar {
  int AnzLines;
  double xmin,xmax ;
  GaussLinePar gp[1] ;
  };


struct FAR tableptrdsc {
  WORD TableInd;
  LPDBRECORD r;
  } ;
struct FAR ConnectionExtraInfo {
  DWORD cOffs;      // Korrekturoffset zur Berechnung von Expressionzeiger
  DWORD fOffs;      // Korrekturoffset zur Berechnung von Datentypen in Funktionen
  LPSTR cmdBase;    // Basisadresse einer Multiproc
  union {
    tableptrdsc t[1]; // case EXTRATYPE_REC ;
    LPVOID keyData;   // case EXTRATYPE_LIST ;
    } i ;
  int AnzTables ()
    {
    return (GetBlockSize (this) - (sizeof(*this) - sizeof(i.t[1]))) / sizeof(i.t[1]) ;
    }
  };
typedef ConnectionExtraInfo FAR *LPCONNEXTRAINFO;
struct oldRecBuffer {
  int AnzRecsSaved;
  tableptrdsc t[8];
  };
typedef oldRecBuffer SAVEREC;

class FAR MDIWndList {
 public:
  HWND hWndChild;
  MDIWndList FAR* Prev;
  MDIWndList FAR* Next;

  MDIWndList::MDIWndList (HWND hWnd);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };
typedef MDIWndList FAR* LPMDIWNDLIST;

extern LPMDIWNDLIST FirstChild, LastChild;

//----------------------------------------------------------------------------
// Beschreibung MDICHILD
//----------------------------------------------------------------------------
struct FAR UseDialogDocument_param;
struct FAR ExtChild_param;
#define FORNEXT_NORMAL  0
#define CONTINUE_DONE   1
#define BREAK_DONE      2
struct FAR VirtFunctionCall;
struct _OutData {
  HWND _MyHandle;
  LPVOID _ObjectList;
  float  _scale;
  int    _xp,_yp,_x0,_y0,_xm,_ym;
  fRECT  rcLogRect;
  int    _AnzSides,_ActSide;
  DWORD  _SelColor;
  HPEN   hActivePen,hInactivePen;

  /*------< Drucken >------*/
  #ifdef PRINTER_INCLUDED
  Printer FAR *Pr;
  #else
  LPVOID Pr;
  #endif

  BOOL    IsPrinting;

  /*----< Scrollbar >-----*/
  BOOL    scale_set;
  int     _xunit,_yunit;
  int     hmin,hmax,hpos;
  int     vmin,vmax,vpos;

  /*----< Hilfsvariablen >-----*/
  int          tabx;
  StrListInfo  sli;
  LPVOID       ActScanPtr;
  BOOL         CheckMapChanged;
  int          xpold,ypold;
  float        oldscale;
  BOOL         maximized,veryBestIsDone,veryBestWidthIsDone;
  HWND         hMax;
  TrackWndData twd;

  // Erweiterungen
  BOOL noAutoScroll;
  };
typedef _OutData FAR *LPOUTDATA;
class FAR mdiChild {
 private :
  BOOL CheckCond (LPSTR cnd,DWORD *Len,WORD mode);
  BOOL ExCuteBlock (DWORD Offset,WORD mode);
  WORD MyDocumentNumber;

  LPCONNEXTRAINFO _ExtraData;
  WORD _ExtraType;
  int _ExtraSize;

  BOOL InListFunction;
  LPVOID ConnectionAddress;
  DWORD ConnectionOwnerID;
  inline LPVOID GetConnectionAddress (LPVOID cAddr)
    {
    return (InListFunction) ? ConnectionAddress : cAddr ; 
    }
  inline DWORD OwnerID ()
    {
    return (InListFunction) ? ConnectionOwnerID : 0L ; 
    }
  void SetCount (LPCMDCOUNT cmd)
    {
    FreeGlobMem (_ccount);
    _ccount = cmd->Copy ();
    }
  void ResetCount ()
    {
    FreeGlobMem (_ccount);
    if (_ccount_base != NULL)
      _ccount = _ccount_base->Copy();
    else
      _ccount = GetCount (MyDocumentNumber);
    }

  LPSTR base;
#ifdef DYNALINK_INCLUDED
  dynalink FAR *ExtPrg;
#else
  LPVOID ExtPrg;
#endif

  int fornext_result;     // PREFIX_BREAK,PREFIX_CONTINUE

 public :
  BOOL LoadDone;
  mdiChild *CallerContext;
  void InitializeForResult()
    {
    fornext_result = FORNEXT_NORMAL ;
    }
  int GetForResult ()
    {
    return fornext_result ;
    }
  void SetForResult (int fr)
    {
    fornext_result = fr;
    }

  BOOL ExCuteBlock (LPSTR base,DWORD Offset,WORD mode);

  /*---< Datensaetze >------*/
  LPRECROOT rr;
  DocExtraData FAR *_ed;
  LPSTR GetCmdBase() { return base; }
  union {
    UseDialogDocument_param FAR *use;
    ExtChild_param FAR *ext;
    } cp;

  LPCONNEXTRAINFO _GetRecExtra ()
    { return ((_ExtraData != NULL) && (_ExtraType == EXTRATYPE_REC)) ?
               _ExtraData : NULL ; }
  void _SetRecExtra (LPCONNEXTRAINFO ex)
    { _ExtraData = ex ; }
  void SetRecsForUpdate (SAVEREC &s,LPCONNEXTRAINFO h)
    {
    int AnzTables = h->AnzTables () ;
    for (int i = 0 ; i < AnzTables ; i++) {
      s.t[i].TableInd = h->i.t[i].TableInd ;
      s.t[i].r = rr->GetRecord (s.t[i].TableInd);
      rr->SetRecord (s.t[i].TableInd,h->i.t[i].r);
      }
    s.AnzRecsSaved = AnzTables ;
    }
  void RestoreRecs (SAVEREC &s)
    {
    for (int i = 0 ; i < s.AnzRecsSaved ; i++) {
      rr->SetRecord (s.t[i].TableInd,s.t[i].r);
      }
    }
  LPEXPPTR FAR *GetExpPtr (DWORD Id);

  /*---< Ausfuehrungszustand >------*/
  LPCMDCOUNT      _ccount;
  LPCMDCOUNT      _ccount_base;
  LPSCRIPTCONTENT schd;

  /*---< Ausfuehrungskontext >----*/
  BOOL IsInListFunction ()
    { return InListFunction ; }

  /*---< Ausgabe des Statusstrings >------*/
  WORD            StatusStrId;

  /*---< Ausgabe >------*/
  mdiChild FAR *outContext;
  mdiChild FAR *erzContext;
  LPOUTDATA _outData;
  void   ChangeDocSide (int dside);

  LPOUTDATA GetOutData ()
    {
    if (_outData != NULL)
      return _outData;
    else {
      _outData = LPOUTDATA (GetGlobMem (sizeof (*_outData)));
      return _outData;
      }
    }

  mdiChild *GetErzContext()
    {
    return (erzContext != NULL) ? erzContext : this;
    }

  LPVOID OutList()
    { return (outContext != NULL) ? outContext->GetOutData ()->_ObjectList : GetOutData ()->_ObjectList ; }
  HWND OutWnd()
    { return (outContext != NULL) ? outContext->GetOutData ()->_MyHandle : GetOutData ()->_MyHandle ; }
  float OutScale()
    { return (outContext != NULL) ? outContext->GetOutData ()->_scale : GetOutData ()->_scale ; }
  int OutXp()
    { return (outContext != NULL) ? outContext->GetOutData ()->_xp : GetOutData ()->_xp ; }
  int OutYp()
    { return (outContext != NULL) ? outContext->GetOutData ()->_yp : GetOutData ()->_yp ; }
  int OutX0()
    { return (outContext != NULL) ? outContext->GetOutData ()->_x0 : GetOutData ()->_x0 ; }
  int OutY0()
    { return (outContext != NULL) ? outContext->GetOutData ()->_y0 : GetOutData ()->_y0 ; }
  mdiChild *DrawContext()
    { return (outContext != NULL) ? outContext : this ; }
  int anzSides()
    { return (outContext != NULL) ? outContext->GetOutData ()->_AnzSides : GetOutData ()->_AnzSides ; }
  int actSide()
    { return (outContext != NULL) ? outContext->GetOutData ()->_ActSide : GetOutData ()->_ActSide ; }
  DWORD selColor()
    { return (outContext != NULL) ? outContext->GetOutData ()->_SelColor : GetOutData ()->_SelColor ; }

  virtual LONG ToScreen (HWND hWnd);
  virtual void StartExternPaint (void);
  virtual void EndExternPaint (void);
  virtual LONG Paint(PaintContext *pc);
  virtual void GetDocInfo (int Cmd,DWORD fldId,LPVOID Buffer);
  virtual void Rescale (LPRECT) { }   // Neue Skalierung anfordern
  virtual int WorldToLog (float val)  // Umrechnen von Objekt - Koordinaten
    { return int (val); }             // in Windows - log. Koordinaten
  virtual float LogToWorld (int val)
    { return float (val); }
  virtual int HalfPenWidth (DWORD color) 
    { int w = int ((color & 0x0F000000) >> 24) * 10; return (w) ? w : 1 ; }

  virtual void SetPrintSideOpt(BOOL autoscale,double sc);
  virtual BOOL IsSidePrinted();
  virtual LONG ToPrinter (Printer *,BOOL,WORD);
  BOOL    BestScaling ();

  /*-----< Scrollbalkenverwaltung >------*/
  void    InitializeBars (BOOL doErase = TRUE);
  virtual void MapChanged(void);
  virtual void SizeChanged(void);
  virtual void GetMinMax (BOOL forScreen = TRUE);
  virtual void RecalcScale () { }
  virtual void HScBar (int FAR *mn,int FAR *mx,int FAR *pos);
  virtual void VScBar (int FAR *mn,int FAR *mx,int FAR *pos);
  virtual void ScrollVertikal(int dy);
  virtual void ScrollHorizontal(int dx);
  virtual void ToggleScale ();
  virtual void NewScale (double sc);
  virtual void CalcScale (void);
  void ToggleSize ();

  int XUnit() { return (outContext != NULL) ? outContext->GetOutData ()->_xunit : GetOutData ()->_xunit ; }
  int YUnit() { return (outContext != NULL) ? outContext->GetOutData ()->_yunit : GetOutData ()->_yunit ; }

  /*----< Hilfsvariablen >-----*/
  BOOL         closed;

  /*---< Skriptausfuehrung >-----*/
  void ExCute (WORD mode);
  void ExCuteif (char FAR *blockbeg,WORD mode);
  void ExCuteelse (char FAR *blockbeg,WORD mode);
  void ExCuteProc(DWORD Offset, WORD mode);

  /*------< Allgemeines >--------*/
  mdiChild (LPSCRIPTCONTENT scent,BOOL getCommandCopy = TRUE);
  virtual ~mdiChild ();
  virtual void Create (LPSTR Name);
  virtual BOOL IsSmallDoc()
    { return FALSE ; }
  virtual BOOL IsListDoc()
    { return FALSE ; }
  virtual LONG WINAPI SpcFnc(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done);
  BOOL dontUpdateDocument;
  BOOL    IsDocLocked (WORD RecType)
    { return (outContext != NULL) ? outContext->dontUpdateDocument : dontUpdateDocument ; }
  void    Store (void);
  BOOL    CheckDocExit (BOOL doExCute);
  BOOL    CallOnClose ();
  BOOL    CheckOnClose (BOOL doAsk,BOOL doClose);
  FARPROC DefaultHandler_base;
  LONG    ChildProc (HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done);
  void    SetCreationFlag (BOOL);
  virtual void LoadData (void);
  virtual void ZoomRect (int,int,int,int);    // Rechteck in logischen Koords
  virtual void Reset (void);
  virtual void CloseChilds (void);

  /*------------< Kommandoverwaltun >-------------*/
  void CallCommand (LPVOID Cmd,WORD mode);
  void CallExpression (LPVOID cmd,WORD mode);
  GLOBALHANDLE commands;
  GLOBALHANDLE hGConstMem;
  void         FreeExpNodes();
  LPEXPPTR     ExpNodes;

  /*-----------< Extradatenverwaltung >-----------------*/
  LPVOID GetDocumentExtraData (WORD Code,int FAR *size = NULL);
  void   PutDocumentExtraData (WORD Type,LPVOID Data,int size);
  void   RemoveDocumentExtraData (WORD Type);
  void   DeleteDocumentExtraData ();

  void  WriteScaleRef (DWORD scaleRef);
  DWORD FAR *GetScaleRef (void);

  /*-----------< Oberflaeche >------------------------*/
  void NextField ();
  void PrevField ();

  /*----------< Spezialfunktionen >--------------*/
  void CreateGaussWin();
  void ShowGauss (double FAR *val,double FAR *norm,double FAR *dev,
                            int AnzRec,LPSTR caption
                 );
  GLOBALHANDLE GetGaussPar (double FAR *val,double FAR *norm,
                                  double FAR *dev,int AnzRun);
  void CloseGauss ();

  /*------------< Datenbankzugriffe >--------------------*/
  LPVOID GetExpression     (DWORD Id);
  LPTSTR GetStrExpression  (DWORD Id);
  WORD   GetExpressionType (DWORD Id);
  LPVOID GetExtraData      (DWORD Id);
  LPTSTR GetStrExtraData   (DWORD Id);
  WORD   GetExtraDataType  (DWORD Id);
  void   SetExpression     (DWORD Id,LPVOID data,WORD size,LPVOID Cmd,BOOL UpdateSystem);
  void   DelExpression     (DWORD Id,LPVOID Cmd,BOOL UpdateSystem);
  void   ConnectExpression (DWORD Id,DWORD DocumentID,LPVOID Cmd,LPCMDCOUNT cnt);
  void   ClearExpression   (DWORD Id,DWORD DocumentID,LPVOID Cmd,LPCMDCOUNT cnt);
  BOOL   IsUpdateFromExpression (DWORD Id);

  LPVOID ReadData (WORD RecType,WORD Ident)
    {
    if (RecType < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,RecType,Ident))
#endif
      return rr->Get(MAKELONG(RecType,Ident));
#ifdef DEBUG
      else return NULL;
#endif
      }
    else
      return GetExtraData (MAKELONG(RecType,Ident));
    }
  void WriteData (WORD RecType,WORD Ident,LPVOID data,int size,
                      LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON
                 )
    {
    if (RecType < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,RecType,Ident))
#endif
        rr->Set(MAKELONG(RecType,Ident),data,size,GetConnectionAddress (Cmd),UpdateSystem,_ExtraType,_ExtraData,_ExtraSize);
#ifdef DEBUG
      AfterWrite (this,RecType,Ident);
#endif
      }
    else
      SetExpression (MAKELONG(RecType,Ident),data,size,GetConnectionAddress (Cmd),UpdateSystem);
    }
  void SetConnection (WORD RecType,WORD Ident,LPVOID Cmd)
    {
    if (RecType < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,RecType,Ident))
#endif
      rr->SetConnection (OwnerID(),MAKELONG(RecType,Ident),DocumentID(),GetConnectionAddress (Cmd),_ccount,_ExtraType,_ExtraData,_ExtraSize);
      }
    else
      ConnectExpression (MAKELONG(RecType,Ident),DocumentID(),GetConnectionAddress (Cmd),_ccount);
    }
  void ClearConnection (WORD RecType,WORD Ident,LPVOID Cmd)
    {
    if (RecType < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,RecType,Ident))
#endif
      rr->ClearConnection (OwnerID(),MAKELONG(RecType,Ident),DocumentID(),GetConnectionAddress (Cmd),_ExtraType,_ExtraData,_ExtraSize);
      }
    else
      ClearExpression (MAKELONG(RecType,Ident),DocumentID(),GetConnectionAddress (Cmd),_ccount);
    }
  BOOL IsConst (DWORD DataRef)
    {
    return (LOWORD(DataRef) == 2); 
    }
  LPVOID ReadlData (DWORD DataRef)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      return rr->Get(DataRef);
#ifdef DEBUG
      else return NULL;
#endif
      }
    else
      return GetExtraData (DataRef);
    }
  LPTSTR ReadlStrData (DWORD DataRef)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      return rr->GetStr(DataRef);
#ifdef DEBUG
      else return NULL;
#endif
      }
    else
      return GetStrExtraData (DataRef);
    }
  LPVOID TryToReadExtraData (DWORD Id,BOOL FAR *done = NULL);
  LPVOID TryToReadData (DWORD DataRef,BOOL FAR *done = NULL)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
      if (done != NULL) *done = TRUE ;
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      return rr->Get(DataRef);
#ifdef DEBUG
      else return NULL;
#endif
      }
    else
      return TryToReadExtraData (DataRef,done);
    }
  DBINT ReadConstInt (DWORD DataRef)
    {
    return *((DBINT FAR *) ReadlData (DataRef));
    }
  LONG ReadConstLong (DWORD DataRef)
    {
    return *((LONG FAR *) ReadlData (DataRef));
    }
  float ReadConstFloat (DWORD DataRef)
    {
    return *((float FAR *) ReadlData (DataRef));
    }
  WORD GetDataType (DWORD DataRef)
    {
    if ((LOWORD(DataRef) < EXPTABLEBASE) && (LOWORD(DataRef) >= CSYSRECS)) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      return rr->GetDataType(DataRef);
#ifdef DEBUG
      else return 0xFFFF;
#endif
      }
    else
      return GetExtraDataType (DataRef);
    }
  void WritelData (DWORD DataRef,LPVOID data,int size,
                      LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON
                 )
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
        rr->Set(DataRef,data,size,GetConnectionAddress (Cmd),UpdateSystem,_ExtraType,_ExtraData,_ExtraSize);
#ifdef DEBUG
      AfterWrite (this,LOWORD(DataRef),HIWORD(DataRef));
#endif
      }
    else
      SetExpression (DataRef,data,size,GetConnectionAddress (Cmd),UpdateSystem);
    }
#ifdef UNICODE
  void WritelStrData (DWORD DataRef,LPTSTR data,int size,
                      LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON
                 )
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef),Cmd))
#endif
        rr->SetStr(DataRef,data,size,GetConnectionAddress (Cmd),UpdateSystem,_ExtraType,_ExtraData,_ExtraSize);
#ifdef DEBUG
      AfterWrite (this,LOWORD(DataRef),HIWORD(DataRef),Cmd);
#endif
      }
    else
      SetStrExpression (DataRef,data,size,GetConnectionAddress (Cmd),UpdateSystem);
    }
#endif
  void SetlConnection (DWORD DataRef,LPVOID Cmd)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      rr->SetConnection (OwnerID(),DataRef,DocumentID(),GetConnectionAddress (Cmd),_ccount,_ExtraType,_ExtraData,_ExtraSize);
      }
    else
      ConnectExpression (DataRef,DocumentID(),GetConnectionAddress (Cmd),_ccount);
    }
  void ClearlConnection (DWORD DataRef,LPVOID Cmd)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      rr->ClearConnection (OwnerID(),DataRef,DocumentID(),GetConnectionAddress (Cmd),_ExtraType,_ExtraData,_ExtraSize);
      }
    else
      ClearExpression (DataRef,DocumentID(),GetConnectionAddress (Cmd),_ccount);
    }
  void ClearlOtherConnection (DWORD DataRef,LPVOID Cmd)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      rr->ClearConnection (OwnerID(),DataRef,DocumentID(),GetConnectionAddress (Cmd),_ExtraType,_ExtraData,_ExtraSize);
      }
    else
      ClearExpression (DataRef,DocumentID(),GetConnectionAddress (Cmd),_ccount);
    }
  void DelData (WORD RecType,WORD Ident,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
    {
    if (RecType < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,RecType,Ident))
#endif
        rr->Del(MAKELONG(RecType,Ident),GetConnectionAddress (Cmd),UpdateSystem,_ExtraType,_ExtraData,_ExtraSize);
#ifdef DEBUG
      AfterWrite (this,RecType,Ident);
#endif
      }
    else
      DelExpression(MAKELONG(RecType,Ident),GetConnectionAddress (Cmd),UpdateSystem);
    }
  void DellData (DWORD DataRef,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
        rr->Del(DataRef,GetConnectionAddress (Cmd),UpdateSystem,_ExtraType,_ExtraData,_ExtraSize);
#ifdef DEBUG
      AfterWrite (this,LOWORD(DataRef),HIWORD(DataRef));
#endif
      }
    else
      DelExpression(DataRef,GetConnectionAddress (Cmd),UpdateSystem);
    }
  LPVARELEM GetExtraVarElem (DWORD DataRef);
  LPVARELEM GetVarElem (DWORD DataRef)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
        return rr->GetRecord(LOWORD(DataRef))->GetVarElem(HIWORD(DataRef));
#ifdef DEBUG
      else return NULL ;
#endif
      }
    else
      return GetExtraVarElem (DataRef);
    }
  BOOL IsUpdateFromEle (WORD RecType,WORD Ident)
    {
    if (RecType < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,RecType,Ident))
#endif
      return rr->IsUpdateFromEle(MAKELONG(RecType,Ident));
#ifdef DEBUG
      else return TRUE;
#endif
      }
    else
      return IsUpdateFromExpression(MAKELONG(RecType,Ident));
    }
  BOOL IsUpdatelFromEle (DWORD DataRef)
    {
    if (LOWORD(DataRef) < EXPTABLEBASE) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      return rr->IsUpdateFromEle(DataRef);
#ifdef DEBUG
      else return TRUE;
#endif
      }
    else
      return IsUpdateFromExpression(DataRef);
    }
  int GetVarSize (DWORD DataRef)
    {
    if ((LOWORD(DataRef) < EXPTABLEBASE) && (LOWORD(DataRef) >= CSYSRECS)) {
#ifdef DEBUG
      if (BeforeWrite (this,LOWORD(DataRef),HIWORD(DataRef)))
#endif
      return rr->GetRecord(LOWORD(DataRef))->GetVarSize(HIWORD(DataRef));
#ifdef DEBUG
      else return -1;
#endif
      }
    else
      return -1 ;
    }

  void CallScriptDestruktor ();

  friend class FAR SetExtraInfo;

  DWORD GetCmdOffset (LPVOID cmd) {
    if (_ExtraData != NULL) 
      return ((char _huge *) cmd - (char _huge *) (_ExtraData->cmdBase) + _ExtraData->cOffs);
    else
      // return ((char _huge *) cmd - (char _huge *) GlobalLock (commands));
      return ((char _huge *) cmd - (char _huge *) base);
    }
  char huge * DoFunctionCall (char huge *h,WORD mode);
  // char huge * DoExpFunctionCall (char huge *h,WORD mode);
  void UpdateVirtFunction (VirtFunctionCall FAR *fc,SetExtraInfo FAR *extra,WORD FAR *olddest);
  char huge * DoVirtFunctionCall (char huge *h,WORD mode);
  void SetContextRecords (mdiChild *source,int AnzRecords,LPWORD destInd,LPWORD sourceInd);
  void DelContextRecords (int AnzRecords,LPWORD destInd);

  LPVOID operator new (size_t size)
    { return GetGlobMem (size) ; }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }

  DWORD DocumentID()
    { return DWORD(this); }

  friend BOOL CallExternProc (mdiChild *c,LPVOID param,WORD mode);
  friend void CallProc (mdiChild *c,DWORD Offset,WORD mode,int Nr);
  friend BOOL uVarCall (mdiChild *c,void FAR *param,WORD mode);
  friend BOOL CallOnUpdate (mdiChild *c,LPVOID param,WORD mode);

  friend class RestoreListFnc;
  friend class PrepareListFunction;
  friend class MultiProc;
  friend class FAR ForParam;
  friend char huge *DoFor (mdiChild *c,char huge *h,WORD mode);
  friend char huge *DoWith (mdiChild *c,char huge *h,WORD mode);
  friend char huge *DoInsert (mdiChild *c,char huge *h,WORD mode);
  friend char huge *DoRemove (mdiChild *c,char huge *h,WORD mode);
  friend void ExCuteWith (mdiChild *c,MultiProc FAR *mp,LPVOID par,WORD TableInd,WORD mode,LPDBRECORD r,char huge *IfBeg,char huge *ElseBeg,BOOL doLoad);
  friend void SetRecordToLastExtraInfo (LPDBRECORD r,WORD TableInd);
  friend void RestoreLastExtra ();
  friend void SetLastExtra ();
  friend struct FAR DoWithList;
  friend void CallFunction (DWORD FuncAddr,mdiChild *c,LPSCRIPTCONTENT scchild,LPWORD destInd,int AnzPars,LPVOID FAR *vals,int AnzValsRet,LPVOID FAR *ValsRet);
  friend LPVOID ParseExpression (mdiChild *c,LPVOID par,WORD mode,WORD FAR *error,WORD FAR *rType);
  };
typedef mdiChild FAR *LPMDICHILD;
void ActivateStatBar (mdiChild *c,BOOL state,COLORREF foreColor = 0xFFFFFFFF,
                      COLORREF backColor = 0xFFFFFFFF);

class FAR SetExtraInfo {
 private :
  mdiChild *whereisset;
  LPCONNEXTRAINFO ci;
  LPCONNEXTRAINFO oldci;
  WORD oldType;
  WORD oldSize;
 public :
  SetExtraInfo (mdiChild *c,WORD TableInd,LPDBRECORD r,DWORD cOffs);
  SetExtraInfo (mdiChild *c,LPCONNEXTRAINFO extra);
  SetExtraInfo (mdiChild *c,WORD TableInd,LPDBRECORD r,DWORD cOffs,BOOL replace);
  SetExtraInfo (mdiChild *c,LPPRIMKEY k,DWORD cOffs);
  SetExtraInfo (mdiChild *c,LPVOID keyData,DWORD cOffs);
  SetExtraInfo (mdiChild *c,DWORD cOffs);
  SetExtraInfo (mdiChild *c,DWORD cOffs,DWORD fOffs);
  void SetCmdBase (LPSTR cmdBase);
  ~SetExtraInfo ();
  friend void SetRecordToLastExtraInfo (LPDBRECORD r,WORD TableInd);
  friend void RestoreLastExtra ();
  friend void SetLastExtra ();
  friend class mdiChild;
  friend char huge * DoInsert (mdiChild *c,char huge *h,WORD mode);

  LPCONNEXTRAINFO actci () 
    {
    return ci;
    }
  };

class RestoreListFnc {
 private :
  LPSTR oldcmdBase;
  DWORD oldcOffs;
  mdiChild *whereisset;
 public :
  RestoreListFnc (mdiChild *c)
    {
    if (c->_ExtraData != NULL) {
      oldcmdBase  = c->_ExtraData->cmdBase;
      oldcOffs = c->_ExtraData->cOffs;
      c->_ExtraData->cmdBase = c->base ;
      c->_ExtraData->cOffs = 0;
      whereisset = c;
      }
    else
      oldcmdBase = NULL ;
    }
  ~RestoreListFnc ()
    {
    if (oldcmdBase != NULL) {
      whereisset->_ExtraData->cmdBase = oldcmdBase ;
      whereisset->_ExtraData->cOffs = oldcOffs ;
      }
    }
  };

class PrepareListFunction {
 private :
  mdiChild *whereisset;
  HWND oldHandle;
  int oldXP,oldYP;
  float oldscale ;
  BOOL old_dontUpdateDocument ;
 public :
  PrepareListFunction (DWORD OwnerID,mdiChild *c,LPVOID ConnectionAddress,HWND hWnd,int x,int y,double sc)
    { 
    (whereisset = c)->InListFunction = TRUE ; 
    c->ConnectionAddress = ConnectionAddress ; 
    c->ConnectionOwnerID = OwnerID ;
    oldHandle = c->DrawContext()->GetOutData ()->_MyHandle ;
    oldXP = c->DrawContext()->GetOutData ()->_xp;
    oldYP = c->DrawContext()->GetOutData ()->_yp;
    oldscale = c->DrawContext()->GetOutData ()->_scale;
    old_dontUpdateDocument = c->dontUpdateDocument ;
    c->DrawContext()->GetOutData ()->_MyHandle = hWnd;
    c->DrawContext()->GetOutData ()->_xp = x;
    c->DrawContext()->GetOutData ()->_yp = y;
    c->DrawContext()->GetOutData ()->_scale = float(sc);
    c->dontUpdateDocument = TRUE ;
    }
  ~PrepareListFunction ()
    { 
    whereisset->InListFunction = FALSE ; 
    whereisset->ConnectionAddress = NULL ; 
    whereisset->ConnectionOwnerID = 0L ;
    whereisset->DrawContext()->GetOutData ()->_MyHandle = oldHandle ;
    whereisset->DrawContext()->GetOutData ()->_xp = oldXP ;
    whereisset->DrawContext()->GetOutData ()->_yp = oldYP ;
    whereisset->DrawContext()->GetOutData ()->_scale = oldscale ;
    whereisset->dontUpdateDocument = old_dontUpdateDocument ;
    }
  };

/* ----------------------- fuer VTO --------------------------- */
class FrmObject;
typedef FrmObject FAR *LPFRMOBJ;

struct FAR ftr2 {
  float A[2][2];
  float B[2];
  };

struct FAR ffpt {
  float x,y;
  };

#pragma pack(1)
struct Vto_Init_param {
  WORD ParSize;         // Groesse des Parameterblockes
  // Parameterdaten     // alle folgenden Variablen haben freien RecordType
  WORD vtomodeR, vtomodeI;  // long vtomode (allgemein verwendbar)
  WORD dxR, dxI;        // dec dx (fuer UpdateProcs)
  WORD dyR, dyI;        // dec dy (fuer UpdateProcs)
  WORD phiR, phiI;      // dec phi (fuer UpdateProcs)
  WORD rotptR, rotptI;  // point rcent (fuer UpdateProcs)
  WORD modeR, modeI;    // long updmode (fuer UpdateProcs + allgemein)
  WORD gnR, gnI;        // long grpnum (fuer UpdateProcs + allgemein)
  WORD pnR, pnI;        // long partnum (fuer UpdateProcs + allgemein)
  DWORD _MoveColor;      // Farbe zum Zeichnen im XOR Modus
  DWORD CopyProcOffs[1];
  };
#pragma pack()

#pragma pack(1)
struct Vto_DefineGroup_param {
  WORD ParSize;         // Groesse des Parameterblockes
  LPSTR partypes;       // zum merken der Parametertypen
  // Parameterdaten
  WORD grpR, grpI;      // Referenz auf die Gruppenvariable
  DWORD grpid;          // Gruppenid-Nummer
  DWORD _modeflags;      // was darf mit der Gruppe gemacht werden ?
  DWORD UpdateProc;     // Offset der Update Prozedur
  WORD selmodeR;        // Referenz auf die SelMode-Variable
  WORD selmodeI;
  DWORD _SelColor;       // Farbe, wenn selektiert
  WORD scfactR;         // Skalierungsfaktor fuer dx/dy - Ausgabe
  WORD scfactI;
  // variable Laenge
  struct {
    WORD R, I;
    } Ref[1];           // Liste mit Objekten und Matritzen
  };
#pragma pack()

typedef struct Vto_MoveList FAR *LPVTOMOVELIST;
typedef struct Vto_SelSort FAR *LPVTOSELSORT;
typedef struct Vto_IdList FAR *LPVTOIDLIST;
typedef struct Vto_ObjList FAR *LPVTOOBJLIST;
typedef struct Vto_OtherObjList FAR *LPVTOOTHERLIST;
typedef class Vto_Group FAR *LPVTOGRP;

struct Vto_MoveList {
  LPVTOMOVELIST next;
  DWORD grpid;          // Gruppenid-Nummer
  DWORD MoveProc;     // Offset der Update Prozedur
  };

struct Vto_SelSort {
  LPVTOSELSORT next;
  LPVTOSELSORT prev;
  LPVTOGRP grp;
  float dist;
  };

struct Vto_IdList {
  LPVTOIDLIST next;   // verkettete Liste
  DWORD grpid;        // Gruppenid-Nummer
  };

struct Vto_ObjList {
  LPVTOOBJLIST next;  // verkettete Liste
  LPFRMOBJ obj;       // Zeiger auf Objekt
  WORD objId;         // Ident der Objektvariable
  };

struct Vto_OtherObjList {
  LPVTOOTHERLIST next;  // verkettete Liste
  ftr2 sc;              // zugehoerige Transformationsmatrix
  int sc_parnum;        // Parameternummer der Matrix fuer spaeteren Update
  ffpt refpt;           // Referenzpunkt fuer Rotation
  LPFRMOBJ obj;         // Zeiger auf Objekt
  WORD objId;           // Ident der Objektvariable
  };

class FAR Vto_Group {
 public:
  LPVTOGRP next;        // verkettete Liste (wenn part: father)
  DWORD grpid;          // Gruppenid-Nummer
  DWORD modeflags;      // was darf mit der Gruppe gemacht werden ?
  DWORD UpdateProc;     // Offset der Update Prozedur
  WORD selmodeR, selmodeI;   // Referenz auf die mode-Variable
  LPFRMOBJ RotObj;      // Gruppenrotationszentrum
  LPFRMOBJ SoftObj;     // Weichteileditierobjekt
  LPFRMOBJ CutObj;      // Schnitteditierobjekt
  DWORD SelColor;       // Farbe, wenn selektiert
  float scfact;         // Skalierungsfaktor fuer dx/dy - Ausgabe
  LPVTOIDLIST idlist;   // Liste der zugehoerigen Gruppen
  LPVTOOBJLIST objlist; // Liste der zugehoerigen Objekte
  LPVTOOTHERLIST otherlist;  // Liste der Objekte mit 'SCALE_FOLLOWING'
  LPVTOGRP parts;       // Liste der Konturteile, wenn geschnitten
  ftr2 s_to_w;          // screentoworld Transformationsmatrix
  int Vsumx, Vsumy;     // Vektorsumme Maus->Schwerpunkt
  fRECT grpLogRect;     // Extremwerte der Gruppe
  BOOL selected;

  mdiChild *myinst;
  LPDBRECORD xRec;
  WORD xTableInd;

  Vto_Group(Vto_DefineGroup_param FAR *par,mdiChild *c);
  ~Vto_Group();
  LPVOID operator new (size_t size);
  void operator delete (LPVOID obj);
  LPVTOGRP GetGroup(DWORD id);
  void CalcSelInfo(int ptx, int pty);   // Informationen fuer Selektion
 private:
  void CalcSelInt(LPVTOGRP grp, int ptx, int pty);
 public:   // CalcSchwerSum: in first Listenanfang uebergeben !
  void CalcSchwerSum(LPVTOGRP first, fpt FAR *pt, int FAR *anz_pts);
  };
/* ----------------------- Ende VTO --------------------------- */

class FAR Form : public mdiChild {
 public :
  BOOL UseSchiebeLehre;
  BOOL SchiebeEntryExist;
  int xPrinterOffs ;
  int yPrinterOffs ;
  /*----< Allgemeines >------*/
  Form (LPSCRIPTCONTENT scent);
  virtual ~Form ();
  virtual void LoadData (void);
  virtual void Reset (void);
  virtual void GetDocInfo (int Cmd,DWORD fldId,LPVOID Buffer);
  virtual LONG WINAPI SpcFnc(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done);

  /*---< Scroll - Verwaltung >-----*/
  virtual void HScBar (int FAR *mn,int FAR *mx,int FAR *pos);
  virtual void VScBar (int FAR *mn,int FAR *mx,int FAR *pos);
  virtual void SizeChanged(void);
  virtual void GetBestSize (int xmin = -1,int ymin = -1,int xmax = -1,int ymax = -1);
  virtual void GetBestWidth ();
  virtual void GetMinMax (BOOL forScreen = TRUE);
  virtual void Rescale (LPRECT rcnr);
  virtual void ScrollVertikal(int dy);
  virtual void ScrollHorizontal(int dx);
  void    GetVeryBestSize();
  void    GetVeryBestWidth(int mode = TRUE);

  /*-----< Ausgabe >-------*/
  virtual LONG ToScreen (HWND hWnd);
  virtual LONG Paint(PaintContext *pc);

  /*-----< Drucken >-------*/
  virtual LONG ToPrinter (Printer *pr,BOOL firstPart,WORD partNo);
  virtual BOOL IsSidePrinted();
  virtual void SetPrintSideOpt(BOOL autoscale,double sc);

  /*-----< Formularspezifische Hilfsfunktionen >-------*/
  void GetActivePos (LPPOINT pt);
  void DestroySchiebeLehre (void);
  void SetUpSchiebeLehre (void);

  /* --------------- fuer VTO: ---------------- */
 public :
  DWORD MoveColor;
  Vto_Init_param FAR *vip;  // Zeiger auf Parameterblock von Vto_Init
  mdiChild *VtoContext;     // Script, das fuer die VTO verantwortlich ist
  LPVTOGRP group;           // Liste aller definierten Gruppen
  LPVTOSELSORT sellist;     // sortierte Liste der waehlbaren Objekte
  LPVTOSELSORT actsel;      // aktueller Eintrag in der sellist
  LPVTOMOVELIST movelist;   // Liste mit Scriptprozeduren zum Verschieben
  WORD mode;                // Modus: INACTIVE / MOVE / SOFT / CUT / ....
  WORD state;               // Status je nach Modus (z.B. MOVING)
  LONG old_lP;              // zum Merken der aktuellen Mausposition
  WORD old_wP;              // zum Merken der aktuellen Maustasten
  int oldmousex, oldmousey; // Mauskoordinaten bei Beginn der Transformation
  float oldphi;             // Winkel bei Beginn der Rotation
  int act_dx, act_dy;       // aktueller Verschiebungsvektor )-> in logischen
  float act_phi;            // aktueller Rotationswinkel     )   Koordinaten
  BOOL clear_old;           // ist Gruppe XOR am Bildschirm ?
  BOOL skip_next_char;      // nach Tab: naechste WM_CHAR ignorieren
  tr2 grp_sc;               // Transformationsmatrix des aktuellen Moves
  WORD sc_state;            // state bei Berechnung des aktuellen Moves
  void MouseToLog(LONG mouse, int FAR *ptx, int FAR *pty);  // Maus- in logische Koords.
  void CalcTransMat(LONG mouse);  // Verschiebungsmatrix aus Mauskoords.
  void CalcRotMat(LONG mouse);    // Rotationsmatrix aus Mauskoords.
  BOOL NearRotCent(LONG mouse);   // Maus in der Naehe des Rot.-Zentrums ?
  BOOL MouseInGrpRect(LONG mouse, LPVTOGRP grp); // Maus im umgebenden rect.
  void CalcRotCent(LONG mouse);   // Rotationszentrum aus Mauskoords.
 private:
  void SelectGrpInt(LPVTOGRP grp);  // rekursiver Teil von SelectGrp()
  void DeselectGrpInt(LPVTOGRP grp);  // rekursiver Teil von DeselectGrp()
 public:
  void SelectGrp();          // selektiert die aktuelle Gruppe
  void DeselectGrp();        // deselektiert wenn noetig aktuelle Gruppe
  void GenSelList(LONG mouse);  // generiert die sortierte select-Liste
  void DelSelList();         // loescht die sortierte select-Liste
 private:
  void TextDxDy(PaintContext *pc);  // act_dx, act_dy als Text ausgeben
  void TextPhi(PaintContext *pc);   // act_phi als Text ausgeben
  void DrawGrpMoveInt(LPVTOGRP grp, PaintContext *pc); // rekursiver Teil
 public:
  void DrawGrpMove();        // zeichnet die Transformation in XOR
 private:
  void DoGrpMoveInt(LPVTOGRP grp, DWORD updmode);  // rekursiver Teil
  void WriteScriptVars();    // fuer GrpMove-Script Variable
 public:
  void DoGrpMove();          // fuehrt die Transformation aus
  void DoRotCentMove();      // verschiebt das aktuelle Rotationszentrum
  };

#ifdef UEBERLEGT
class FAR Tracing : public mdiChild {
 public :

  Tracing (LPSCRIPTCONTENT scent);
  virtual ~Tracing ();
  virtual void LoadData (void);
  virtual void Reset (void);
  virtual LONG WINAPI SpcFnc(HWND hWnd,UINT msg,WPARAM wP,LPARAM lP,BOOL *done);
  virtual void GetDocInfo (int Cmd,DWORD fldId,LPVOID Buffer);

  /*-----< Scrollbarverwaltung >-------*/
  virtual void HScBar (int FAR *mn,int FAR *mx,int FAR *pos);
  virtual void VScBar (int FAR *mn,int FAR *mx,int FAR *pos);
  virtual void ScrollVertikal(int dy);
  virtual void ScrollHorizontal(int dx);
  virtual void NewScale (double sc);
  virtual void GetMinMax (BOOL forScreen = TRUE);
  virtual void RecalcScale ();
  virtual void CalcScale (void);
  virtual void Rescale (LPRECT rcnr);

  /*-----< Ausgabe >-------*/
  virtual LONG ToScreen (HWND hWnd);
  virtual LONG Paint(PaintContext *pc);

  /*-----< Drucken >-------*/
  virtual LONG ToPrinter (Printer *pr,BOOL firstPart,WORD partNo);
  virtual BOOL IsSidePrinted();
  virtual void SetPrintSideOpt(BOOL autoscale,double sc);

  virtual int WorldToLog (float val) 
    { return int (val * 25.0); }
  virtual float LogToWorld (int val)
    { return float (val) / float (25.0); }
  virtual int HalfPenWidth (DWORD color) 
    { int w = int (((color & 0x0F000000) >> 24) * 9 + 1) / 4; 
      return (w) ? w : 1 ; }
  };
#endif

class FAR ExpChild : public mdiChild {
 public :
  ExpChild (LPSCRIPTCONTENT scent) : mdiChild (scent,FALSE) { }
  virtual ~ExpChild ();
  };

/*-----------< Generelle Hilfsfunktionen >------------*/
LPSTR GetControlName();
LPMDICHILD GetWindowInst(HWND hWnd);
  
// Extradaten fuer den Rechteck-Zoom-Modus
struct ZoomInfo {
  HCURSOR ZoomCursor;
  HCURSOR OldCursor;
  DWORD ZoomButton;
  int state;
  int newx1, newy1, newx2, newy2;
  int oldx1, oldy1, oldx2, oldy2;
  mdiChild *zoomChild;
  };

// Extradatenhandling Ein / Aus
#ifdef MDICHILD_MAIN
BOOL BlockIsActive;
#else
extern BOOL BlockIsActive;
#endif
class ActiveBlock
  {
 public :
  BOOL oldStatus;
  ActiveBlock()
    {
    oldStatus = BlockIsActive ;
    BlockIsActive = TRUE ;
    }
  ~ActiveBlock()
    {
    BlockIsActive = oldStatus;
    }
  };
#define ZI_STATE_CAPTURED 1
#define ZI_STATE_DRAWBOX  2
#define ZI_STATE_ZOOMDONE 3
#define ZI_STATE_BUTTONUP 4
