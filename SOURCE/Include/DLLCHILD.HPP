///////////////////////////////////////////////////////////////
//  Klasse dllChild: Callbackfunktionen fuer mdiChild
///////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/dllchild.hpv   1.12   13 Oct 1998 12:54:02   Gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/dllchild.hpv  $
// 
//    Rev 1.12   13 Oct 1998 12:54:02   Gerhold
// 
// Aenderung wegen VC6. Type Casts (HWND), (HPEN)
// 
//    Rev 1.11   15 Dec 1997 17:35:42   Hannes
// Zusammenspiel Debugger / Formulargenerierung
// 
//    Rev 1.10   11 Jul 1997 10:14:16   Hannes
// 
//    Rev 1.9   02 Feb 1996 10:59:48   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   11 Jun 1995 10:00:18   HANNES
// GetClock..
// 
//    Rev 1.7   04 Apr 1995 12:09:38   HANNES
// 
//    Rev 1.6   21 Mar 1995 16:21:30   HANNES
// 
//    Rev 1.5   20 Mar 1995 12:16:18   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.4   09 Jan 1995 12:11:50   HANNES
// Debugger eingebaut
// 
//    Rev 1.3   05 Dec 1994 17:37:08   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.2   06 Oct 1994 19:28:54   HANNES
// Funktioneserweiterungen
// 
//    Rev 1.1   20 Sep 1994 11:30:10   HANNES
// Erweiterung auf MultiProc
// 
//    Rev 1.0   24 Jun 1994 19:19:42   MARTIN
// Initial revision.
//

// Nomenklatur: DC heisst DLLCHILD, CB heisst CALLBACK

struct FAR dllChild ;

typedef void (WINAPI * DCCB_VOID_VOID) (dllChild FAR *);
typedef WORD (WINAPI * DCCB_WORD_VOID) (dllChild FAR *);
typedef LPVOID (WINAPI * DCCB_LPVOID_VOID) (dllChild FAR *);
typedef HANDLE (WINAPI * DCCB_HANDLE_VOID) (dllChild FAR *);
typedef void (WINAPI * DCCB_VOID_LPVOID) (dllChild FAR *, LPVOID);
typedef int (WINAPI * DCCB_INT_VOID) (dllChild FAR *);
typedef DWORD (WINAPI * DCCB_DWORD_VOID) (dllChild FAR *);
typedef void (WINAPI * DCCB_VOID_INT_DWORD_LPVOID) (dllChild FAR *, int, DWORD, LPVOID);
typedef int (WINAPI * DCCB_INT_FLOAT) (dllChild FAR *, float);
typedef void (WINAPI * DCCB_VOID_LPVOID_INT) (dllChild FAR *, LPVOID, int);
typedef int (WINAPI * DCCB_INT_DWORD) (dllChild FAR *, DWORD);
typedef void (WINAPI * DCCB_VOID_HANDLE) (dllChild FAR *, HANDLE);
typedef void (WINAPI * DCCB_VOID_INT) (dllChild FAR *, int);
typedef void (WINAPI * DCCB_VOID_DWORD_WORD) (dllChild FAR *, DWORD, WORD);
typedef BOOL (WINAPI * DCCB_BOOL_WORD_INT) (dllChild FAR *, WORD, int);
typedef BOOL (WINAPI * DCCB_BOOL_WORD) (dllChild FAR *, WORD);
typedef LPVOID (WINAPI * DCCB_LPVOID_WORD_LPVOID) (dllChild FAR *, WORD, LPVOID);
typedef void (WINAPI * DCCB_VOID_WORD_LPVOID_INT) (dllChild FAR *, WORD, LPVOID, int);
typedef void (WINAPI * DCCB_VOID_WORD) (dllChild FAR *, WORD);
typedef void (WINAPI * DCCB_SHOWGAUSS) (dllChild FAR *, LPVOID, LPVOID, LPVOID, int, LPVOID);
typedef HANDLE (WINAPI * DCCB_GETGAUSSPAR) (dllChild FAR *, LPVOID, LPVOID, LPVOID, int);
typedef LPVOID (WINAPI * DCCB_READLDATA) (dllChild FAR *, DWORD);
typedef void (WINAPI * DCCB_WRITELDATA) (dllChild FAR *, DWORD, LPVOID, int, LPVOID, BOOL);
#ifdef UNICODE
typedef void (WINAPI * DCCB_WRITELSTRDATA) (dllChild FAR *, DWORD, LPTSTR, int, LPVOID, BOOL);
#endif
typedef void (WINAPI * DCCB_LCONNECTION) (dllChild FAR *, DWORD, LPVOID);
typedef void (WINAPI * DCCB_LOTHERCONNECTION) (dllChild FAR *, DWORD, LPVOID);
typedef void (WINAPI * DCCB_DELLDATA) (dllChild FAR *, DWORD, LPVOID, BOOL);
typedef BOOL (WINAPI * DCCB_ISUPDATEFROMELE) (dllChild FAR *, DWORD);
typedef int (WINAPI * DCCB_INT_LPVOID) (dllChild FAR *, LPVOID);
typedef LPVOID (WINAPI * DCCB_LPVOID_LPVOID) (dllChild FAR *, LPVOID);
typedef LPTABLEDEF (WINAPI * DCCB_LPTABLEDEF_) (dllChild FAR *,LPSTR,WORD FAR *);
typedef LPDBRECORD (WINAPI * DCCB_LPDBRECORD_) (dllChild FAR *,LPDBRECORD,WORD);
typedef void (WINAPI * DCCB_VOID_LPTABLEDEF) (dllChild FAR *,LPTABLEDEF);
typedef int (WINAPI * DCCB_INT_GETVARSIZE) (dllChild FAR *, DWORD);
typedef int (WINAPI * DCCB_GETCONSTINT) (dllChild FAR *, DWORD);
typedef LONG (WINAPI * DCCB_GETCONSTLONG) (dllChild FAR *, DWORD);
typedef void (WINAPI * DCCB_GETCONSTFLOAT) (dllChild FAR *, DWORD,float FAR *);
typedef void (WINAPI * DCCB_BRINGTOTAIL) (dllChild FAR *, LPVOID);
typedef LONG (WINAPI * DCCB_GETCLOCK) (dllChild FAR *);
typedef WORD (WINAPI * DCCB_WORD_GETDATATYPE) (dllChild FAR *,DWORD);


#define DCFUNC_SCHD                               0
#define DCFUNC_MYHANDLE                           1
#define DCFUNC_GET_SCALE                          2
#define DCFUNC_XP                                 3
#define DCFUNC_YP                                 4
#define DCFUNC_X0                                 5
#define DCFUNC_Y0                                 6
#define DCFUNC_ANZSIDES                           7
#define DCFUNC_ACTSIDE                            8
#define DCFUNC_SELCOLOR                           9
#define DCFUNC_HACTIVEPEN                        10
#define DCFUNC_HINACTIVEPEN                      11
#define DCFUNC_GETDOCINFO                        12
#define DCFUNC_RESCALE                           13
#define DCFUNC_WORLDTOLOG                        14
#define DCFUNC_GET_LOGTOWORLD                    15
#define DCFUNC_HALFPENWIDTH                      16
#define DCFUNC_PR                                17
#define DCFUNC_TABX                              18
#define DCFUNC_GET_SLI_RES                       19
#define DCFUNC_GET_SLI_IND                       20
#define DCFUNC_GET_SLI_ACTTXT                    21
#define DCFUNC_SET_SLI_RES                       22
#define DCFUNC_SET_SLI_IND                       23
#define DCFUNC_SET_SLI_ACTTXT                    24
#define DCFUNC_ACTSCANPTR                        25
#define DCFUNC_SET_ACTSCANPTR                    26
#define DCFUNC_EXCUTEPROC                        27
#define DCFUNC_ISDOCLOCKED                       28
#define DCFUNC_GETEXTRADATA                      29
#define DCFUNC_PUTEXTRADATA                      30
#define DCFUNC_REMOVEEXTRADATA                   31
#define DCFUNC_NEXTFIELD                         32
#define DCFUNC_PREVFIELD                         33
#define DCFUNC_CREATEGAUSSWIN                    34
#define DCFUNC_SHOWGAUSS                         35
#define DCFUNC_GETGAUSSPAR                       36
#define DCFUNC_CLOSEGAUSS                        37
#define DCFUNC_READLDATA                         38
#define DCFUNC_WRITELDATA                        39
#define DCFUNC_SETLCONNECTION                    40
#define DCFUNC_SETLOTHERCONNECTION               41
#define DCFUNC_CLEARLCONNECTION                  42
#define DCFUNC_CLEARLOTHERCONNECTION             43
#define DCFUNC_DELLDATA                          44
#define DCFUNC_ISUPDATEFROMELE                   45
#define DCFUNC_DESTROYSCHIEBELEHRE               46
#define DCFUNC_SETUPSCHIEBELEHRE                 47
#define DCFUNC_GETOBJSIDE                        48
#define DCFUNC_ACT_OBJ                           49
#define DCFUNC_SETACTIVEEXPLICIT                 50
#define DCFUNC_GETOBJECTFROMPAR                  51
#define DCFUNC_UPDATEELECOUNT                    52
#define DCFUNC_EMPTYUPDATELIST                   53
#define DCFUNC_SETCARETSHOWN                     54
#define DCFUNC_SETNOCARET                        55
#define DCFUNC_SETSTATUS                         56
#define DCFUNC_GETTABLEDEF                       57
#define DCFUNC_DOCUMENTID                        58
#define DCFUNC_SETRECORD                         59
#define DCFUNC_FREETABLEDEF                      60
#define DCFUNC_FREETABLEDEF                      60
#define DCFUNC_GETVARSIZE                        61
#define DCFUNC_GETCONSTINT                       62
#define DCFUNC_GETCONSTFLOAT                     63
#define DCFUNC_GETCONSTLONG                      64
#define DCFUNC_BRINGTOTAIL                       65
#define DCFUNC_GETCLOCK                          66
#define DCFUNC_GETMTYPE                          67

#ifdef UNICODE

#define DCFUNC_WRITELSTRDATA                     68
#define ANZ_DC_FUNCS                             69

#else

#define ANZ_DC_FUNCS                             68

#endif

#ifdef DLLCHILD_MAIN
DCCB_VOID_VOID dcfunc[ANZ_DC_FUNCS];
#else
extern DCCB_VOID_VOID dcfunc[ANZ_DC_FUNCS];
#endif

class FrmObject;

struct FAR dllChild {
 public :
  mdiChild *PrivData;
  LPCONNEXTRAINFO Extra;
  LPSCRIPTCONTENT schd()
    { return LPSCRIPTCONTENT((*(DCCB_LPVOID_VOID)dcfunc[DCFUNC_SCHD])(this)); }
  HWND MyHandle()
    { return (HWND)(*(DCCB_HANDLE_VOID)dcfunc[DCFUNC_MYHANDLE])(this); }
  void Get_scale(float FAR *sc)
    { (*(DCCB_VOID_LPVOID)dcfunc[DCFUNC_GET_SCALE])(this, sc); }
  int xp()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_XP])(this); }
  int yp()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_YP])(this); }
  int x0()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_X0])(this); }
  int y0()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_Y0])(this); }
  int AnzSides()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_ANZSIDES])(this); }
  int ActSide()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_ACTSIDE])(this); }
  DWORD SelColor()
    { return (*(DCCB_DWORD_VOID)dcfunc[DCFUNC_SELCOLOR])(this); }
  HPEN hActivePen()
    { return (HPEN)(*(DCCB_HANDLE_VOID)dcfunc[DCFUNC_HACTIVEPEN])(this); }
  HPEN hInactivePen()
    { return (HPEN)(*(DCCB_HANDLE_VOID)dcfunc[DCFUNC_HINACTIVEPEN])(this); }
  void GetDocInfo (int Cmd,DWORD fldId,LPVOID Buffer)
    { (*(DCCB_VOID_INT_DWORD_LPVOID)dcfunc[DCFUNC_GETDOCINFO])(this, Cmd, fldId, Buffer); }
  void Rescale (LPRECT rect)
    { (*(DCCB_VOID_LPVOID)dcfunc[DCFUNC_RESCALE])(this, rect); }
  int WorldToLog (float val)
    { return (*(DCCB_INT_FLOAT)dcfunc[DCFUNC_WORLDTOLOG])(this, val); }
  void Get_LogToWorld (float FAR *ltw, int val)
    { (*(DCCB_VOID_LPVOID_INT)dcfunc[DCFUNC_GET_LOGTOWORLD])(this, ltw, val); }
#define SCRIPT_NULL_PEN  429497295L
  int HalfPenWidth (DWORD color)
    { 
    if (color >= SCRIPT_NULL_PEN)
      return 1;
    else
      return (*(DCCB_INT_DWORD)dcfunc[DCFUNC_HALFPENWIDTH])(this, color); 
    }
  Printer FAR *Pr()
    { return (Printer FAR *)((*(DCCB_LPVOID_VOID)dcfunc[DCFUNC_PR])(this)); }
  int tabx()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_TABX])(this); }
  GLOBALHANDLE Get_sli_res()
    { return (*(DCCB_HANDLE_VOID)dcfunc[DCFUNC_GET_SLI_RES])(this); }
  int Get_sli_Ind()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_GET_SLI_IND])(this); }
  LPSTR Get_sli_actTxt()
    { return LPSTR((*(DCCB_LPVOID_VOID)dcfunc[DCFUNC_GET_SLI_ACTTXT])(this)); }
  void Set_sli_res(GLOBALHANDLE res)
    { (*(DCCB_VOID_HANDLE)dcfunc[DCFUNC_SET_SLI_RES])(this, res); }
  void Set_sli_Ind(int Ind)
    { (*(DCCB_VOID_INT)dcfunc[DCFUNC_SET_SLI_IND])(this, Ind); }
  void Set_sli_actTxt(LPSTR actTxt)
    { (*(DCCB_VOID_LPVOID)dcfunc[DCFUNC_SET_SLI_ACTTXT])(this, actTxt); }
  LPVOID ActScanPtr()
    { return (*(DCCB_LPVOID_VOID)dcfunc[DCFUNC_ACTSCANPTR])(this); }
  void Set_ActScanPtr(LPVOID ActScanPtr)
    { (*(DCCB_VOID_LPVOID)dcfunc[DCFUNC_SET_ACTSCANPTR])(this, ActScanPtr); }
  void ExCuteProc(DWORD Offset, WORD mode)
    { (*(DCCB_VOID_DWORD_WORD)dcfunc[DCFUNC_EXCUTEPROC])(this, Offset, mode); }
  BOOL IsDocLocked (WORD RecType)
    { return (*(DCCB_BOOL_WORD)dcfunc[DCFUNC_ISDOCLOCKED])(this, RecType); }
  LPVOID GetExtraData (WORD Code,int FAR *size = NULL)
    { return (*(DCCB_LPVOID_WORD_LPVOID)dcfunc[DCFUNC_GETEXTRADATA])(this, Code, size); }
  void PutExtraData (WORD Type,LPVOID Data,int size)
    { (*(DCCB_VOID_WORD_LPVOID_INT)dcfunc[DCFUNC_PUTEXTRADATA])(this, Type, Data, size); }
  void RemoveExtraData (WORD Type)
    { (*(DCCB_VOID_WORD)dcfunc[DCFUNC_REMOVEEXTRADATA])(this, Type); }
  void NextField ()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_NEXTFIELD])(this); }
  void PrevField ()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_PREVFIELD])(this); }
  void CreateGaussWin()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_CREATEGAUSSWIN])(this); }
  void ShowGauss (double FAR *val,double FAR *norm,double FAR *dev,
                            int AnzRec,LPSTR caption
                 )
    { (*(DCCB_SHOWGAUSS)dcfunc[DCFUNC_SHOWGAUSS])(this, val, norm, dev, AnzRec, caption); }
  GLOBALHANDLE GetGaussPar (double FAR *val,double FAR *norm,
                                  double FAR *dev,int AnzRun)
    { return (*(DCCB_GETGAUSSPAR)dcfunc[DCFUNC_GETGAUSSPAR])(this, val, norm, dev, AnzRun); }
  void CloseGauss ()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_CLOSEGAUSS])(this); }
  LPVOID ReadlData (DWORD DataRef)
    { return (*(DCCB_READLDATA)dcfunc[DCFUNC_READLDATA])(this, DataRef); }
  int GetConstInt (DWORD DataRef)
    { return (*(DCCB_GETCONSTINT)dcfunc[DCFUNC_GETCONSTINT])(this, DataRef); }
  LONG GetConstLong (DWORD DataRef)
    { return (*(DCCB_GETCONSTLONG)dcfunc[DCFUNC_GETCONSTLONG])(this, DataRef); }
  float GetConstFloat (DWORD DataRef)
    {
    float res;
    (*(DCCB_GETCONSTFLOAT)dcfunc[DCFUNC_GETCONSTFLOAT])(this, DataRef,&res); 
    return res ;
    }
  LPVOID ReadData (WORD RecType,WORD Ident)
    {
    return ReadlData (MAKELONG(RecType,Ident));
    }
  void WritelData (DWORD DataRef,LPVOID data,int size,
                      LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON
                 )
    { (*(DCCB_WRITELDATA)dcfunc[DCFUNC_WRITELDATA])(this, DataRef, data, size, Cmd, UpdateSystem); }
#ifdef UNICODE
  void WritelStrData (DWORD DataRef,LPTSTR data,int size,
                      LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON
                 )
    { (*(DCCB_WRITELSTRDATA)dcfunc[DCFUNC_WRITELSTRDATA])(this, DataRef, data, size, Cmd, UpdateSystem); }
#endif
  void WriteData (WORD RecType,WORD Ident,LPVOID data,int size,
                      LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON
                 )
    {
    WritelData (MAKELONG(RecType,Ident),data,size,Cmd,UpdateSystem);
    }
  void SetlConnection (DWORD DataRef,LPVOID Cmd)
    { (*(DCCB_LCONNECTION)dcfunc[DCFUNC_SETLCONNECTION])(this, DataRef, Cmd); }
  void SetConnection (WORD RecType,WORD Ident,LPVOID Cmd)
    {
    SetlConnection (MAKELONG(RecType,Ident),Cmd);
    }
  void SetlOtherConnection (DWORD DataRef,LPVOID Cmd)
    { (*(DCCB_LOTHERCONNECTION)dcfunc[DCFUNC_SETLOTHERCONNECTION])(this, DataRef, Cmd); }
  void ClearlConnection (DWORD DataRef,LPVOID Cmd)
    { (*(DCCB_LCONNECTION)dcfunc[DCFUNC_CLEARLCONNECTION])(this, DataRef, Cmd); }
  void ClearConnection (WORD RecType,WORD Ident,LPVOID Cmd)
    {
    ClearlConnection (MAKELONG(RecType,Ident),Cmd);
    }
  void ClearlOtherConnection (DWORD DataRef,LPVOID Cmd)
    { (*(DCCB_LOTHERCONNECTION)dcfunc[DCFUNC_CLEARLOTHERCONNECTION])(this, DataRef, Cmd); }
  void DellData (DWORD DataRef,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
    { (*(DCCB_DELLDATA)dcfunc[DCFUNC_DELLDATA])(this, DataRef, Cmd, UpdateSystem); }
  void DelData (WORD RecType,WORD Ident,LPVOID Cmd,BOOL UpdateSystem = UPDATE_ASYNCHRON)
    {
    DellData(MAKELONG(RecType,Ident),Cmd,UpdateSystem);
    }
  BOOL IsUpdatelFromEle (DWORD DataRef)
    { return (*(DCCB_ISUPDATEFROMELE)dcfunc[DCFUNC_ISUPDATEFROMELE])(this, DataRef); }
  BOOL IsUpdateFromEle (WORD RecType,WORD Ident)
    {
    return IsUpdatelFromEle(MAKELONG(RecType,Ident));
    }

// aus Form:
  void DestroySchiebeLehre (void)
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_DESTROYSCHIEBELEHRE])(this); }
  void SetUpSchiebeLehre (void)
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_SETUPSCHIEBELEHRE])(this); }

// eigentlich unabhaengig von mdiChild:
  int GetObjSide (FrmObject FAR *obj)
    { return (*(DCCB_INT_LPVOID)dcfunc[DCFUNC_GETOBJSIDE])(this, obj); }
  FrmObject FAR *act_obj()
    { return (FrmObject FAR *)((*(DCCB_LPVOID_VOID)dcfunc[DCFUNC_ACT_OBJ])(this)); }
  void SetActiveExplicit (FrmObject FAR *obj)
    { (*(DCCB_VOID_LPVOID)dcfunc[DCFUNC_SETACTIVEEXPLICIT])(this, obj); }
  FrmObject FAR *GetObjectFromPar(LPVOID param)
    { return (FrmObject FAR *)((*(DCCB_LPVOID_LPVOID)dcfunc[DCFUNC_GETOBJECTFROMPAR])(this, param)); }
  int UpdateEleCount()
    { return (*(DCCB_INT_VOID)dcfunc[DCFUNC_UPDATEELECOUNT])(this); }
  void EmptyUpdateList()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_EMPTYUPDATELIST])(this); }
  void SetCaretShown()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_SETCARETSHOWN])(this); }
  void SetNoCaret()
    { (*(DCCB_VOID_VOID)dcfunc[DCFUNC_SETNOCARET])(this); }
  void SetStatus(LPSTR hlp)
    { (*(DCCB_VOID_LPVOID)dcfunc[DCFUNC_SETSTATUS])(this, hlp); }
  LPTABLEDEF GetTableDef(LPSTR TableName,WORD FAR *TableInd)
    { return (*(DCCB_LPTABLEDEF_)dcfunc[DCFUNC_GETTABLEDEF])(this,TableName,TableInd); }
  DWORD DocumentID()
    { return (*(DCCB_DWORD_VOID)dcfunc[DCFUNC_DOCUMENTID])(this); }
  LPDBRECORD SetRecord (LPDBRECORD r,WORD TableInd)
    { return (*(DCCB_LPDBRECORD_)dcfunc[DCFUNC_SETRECORD])(this,r,TableInd); }
  void FreeTableDef (LPTABLEDEF tb)
    { (*(DCCB_VOID_LPTABLEDEF)dcfunc[DCFUNC_FREETABLEDEF])(this,tb); }
  int GetVarSize (DWORD VarId)
    { return (*(DCCB_INT_GETVARSIZE)dcfunc[DCFUNC_GETVARSIZE])(this,VarId); }
  void BringToTail (LPVOID obj)
    { (*(DCCB_BRINGTOTAIL)dcfunc[DCFUNC_BRINGTOTAIL])(this,obj); }
  LONG GetClock (void)
    { return (*(DCCB_GETCLOCK)dcfunc[DCFUNC_GETCLOCK])(this); }
  WORD GetMType (DWORD Id)
    { 
    return (*(DCCB_WORD_GETDATATYPE)dcfunc[DCFUNC_GETMTYPE])(this,Id); 
    }
  };

static float __float__;
#define m_scale() (m.Get_scale(&__float__),__float__)
#define m_LogToWorld(val) (m.Get_LogToWorld (&__float__,(int)val),__float__)
#define m__scale() (m->Get_scale(&__float__),__float__)
#define m__LogToWorld(val) (m->Get_LogToWorld (&__float__,(int)val),__float__)

