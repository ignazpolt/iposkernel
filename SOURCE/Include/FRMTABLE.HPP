////////////////////////////////////////////////////////////
//  Tabelle in einem Formular
////////////////////////////////////////////////////////////

#define TXSPACING  20
#define TYSPACING  10
// Paramterblock
///////////////////////////////
struct FAR AccessDef {
  DWORD SelectionName;
  DWORD TableName;
  DWORD AnalyseProc;
  DWORD rAnzParams;
  DWORD Par[1];
  LPVOID NextStruct (dllChild FAR *m)
    { return (LPSTR(this + 1) - sizeof(DWORD) + m->GetConstInt (rAnzParams) * sizeof(DWORD)) ; }
  };
typedef AccessDef FAR *LPACCESSDEF;

struct FAR CellKeyDef {
  DWORD rAnzKeySegs;
  DWORD Key[1];
  LPVOID NextStruct (dllChild FAR *m)
    { return (LPSTR(this + 1) - sizeof(DWORD) + m->GetConstInt (rAnzKeySegs) * sizeof(DWORD)) ; }
  };
typedef CellKeyDef FAR *LPCELLKEYDEF;

#define GTID_ALLSAMELINES     0

#define ANZSUPPORTEDGRIDTYPES   1
#ifdef FRMTABLE_MAIN
static BYTE MustAnzColors[] = { 
  1       // GTID_ALLSAMELINES
  } ;
#endif

struct FAR GridDef {
  DWORD rGridType;
  DWORD rAnzColors;
  DWORD ColRef[1];    // Farben der einzelnen Linien
#ifdef FRMTABLE_MAIN
  BOOL CheckGridType (dllChild *m)
    { 
    int GridType = m->GetConstInt (rGridType);
    int AnzColors = m->GetConstInt (rAnzColors);
    return ((GridType < ANZSUPPORTEDGRIDTYPES) && 
              (BYTE(AnzColors) == MustAnzColors[GridType])) ; 
    }
#endif
  LPVOID NextStruct (dllChild FAR *m)
    { return (LPSTR(this + 1) - sizeof(DWORD) + m->GetConstInt(rAnzColors) * sizeof(DWORD)) ; }
  };
typedef GridDef FAR *LPGRIDDEF;

struct FAR FrmTable_Param {
  FrmObjPar_Header hd;  // Standard - Object Header
  // Position
  DWORD ptOrg;          // Ursprung der Tabelle
  DWORD rx0,ry0;          // Offset dazu
  // Uebergabe - Parameter (Werden zum Lesen der Prozedur - Variablen
  //                        benoetigt)
  DWORD Text;           // Text
  DWORD TextFormat;     // Textformat
  DWORD TextType;       // Texttyp (0 ... Normal, 1 ... Invertiert)
  DWORD TextColor;      // Texttyp (Farbe...)
  DWORD Width;          // Spaltenbreite (wird nur in den 
                        // Spaltenueberschriften gelesen)
  // Layout
  DWORD rw0;             // Breite der ersten Spalten (= Namens - Spalte)
  GridDef gd;		        // Beschreibung des Spaltenlayouts (Strichdicken...)

  // Dahinter 
  // AccessDef ... Zugriffe fuer die Spaltenueberschriften
  // AccessDef ... Zugriffe fuer die Zeilennamen
  // AccessDef ... Zugriffe fuer die Zelleninhalte
  // KeyDef ... Beschreibung der Spaltenschluessel
  // KeyDef ... Beschreibung der Zeilenschluessel

  BOOL AnalyseStruct (dllChild FAR *m,LPACCESSDEF FAR &spa,LPACCESSDEF FAR &za,LPACCESSDEF FAR &zellena,
                      LPCELLKEYDEF FAR &spk,LPCELLKEYDEF FAR &zk);
  };
typedef FrmTable_Param FAR *LPFRMTABLEPAR;

// Beschreibung einer Zeile innerhalb einer Zelle
class FAR CLineDef : public FrmFarObject {
 private :
  CLineDef FAR *Next;

 protected :
  LPSTR Text;
  WORD  Format;
  DWORD Color;
  WORD  Type;

  cField FAR *fld;

  void StartExternPaint ();
  void EndExternPaint ();
  void OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0);
  void Paint (PaintContext *);
  int Height(dllChild FAR *m);
  int LineHeight();

 public :
  CLineDef (LPSTR t,WORD f,DWORD c,WORD ty,int w,int AnzLines,dllChild FAR *m);
  ~CLineDef ();

  friend class CellDef;
  friend class FrmTable;
  };
typedef CLineDef FAR *LPCLINEDEF;

// Beschreibung einer Zelle
class FAR CellDef : public FrmFarObject {
 private :
  CellDef FAR *Up,FAR *Down,FAR *Right,FAR *Left;
  BOOL IsOuterCell;
  union FAR {
    struct FAR { CellDef FAR *FirstOfLine,FAR *FirstOfColumn; } InnerCell;
    struct FAR { LPPRIMKEY k; } OuterCell;
    } more ;

 protected :
  LPCLINEDEF cd;
  int x,y,h,w;
  int  Height ();
  void SetPos (int px,int py,int ph);
  void StartExternPaint ();
  void EndExternPaint ();
  void OnMapChange (double scale,int MapType,int xp,int yp,int x0,int y0);
  void Paint (PaintContext *);
  void CellUnionRect (LPRECT r,BOOL FAR *first);

 public :
  CellDef () { }
  virtual ~CellDef () ;

  friend class FrmTable ;
  };
typedef CellDef FAR *LPCELLDEF;

// Die Klasse, die die Tabelle Representiert
class FAR FrmTable : public FrmObject {
 private :
  LPPARAM GetLPParams(LPACCESSDEF a,LPPARAM p);
  DBList FAR *GetList (LPACCESSDEF a,WORD FAR *TableInd,LPTABLEDEF FAR *tb);
  LPPRIMKEY LeseSpaltenSchluessel (LPCELLKEYDEF k);

 protected :
  LPCELLDEF LeftUpper,RightUpper,LeftLower;

  void InitializeLeftUpper (int w);
  void HaengeSpalteAn (LPPRIMKEY k,LPSTR Text,WORD Format,DWORD Color,WORD Type,int Width);
  void HaengeZeileAn (LPPRIMKEY k,LPSTR Text,WORD Format,DWORD Color,WORD Type);
  void HaengeEintragAnZelle (LPPRIMKEY ks,LPPRIMKEY kz,LPSTR Text,WORD Format,DWORD Color,WORD Type);
  void CreateEmptyCells ();

  LPSTR ReadText ();
  WORD ReadFormat ();
  WORD ReadType ();
  DWORD ReadColor ();
  int ReadWidth ();
  void GetOrg (LPPOINT pt);
  void SetPos (LPPOINT pt);

  void Destroy ();
 public :
  
  LPFRMTABLEPAR Par() { return LPFRMTABLEPAR(ScriptParam) ; }
  DLLExport _export WINAPI FrmTable (LPVOID p,mdiChild *mc);
  virtual DLLExport _export WINAPI ~FrmTable ();

  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *, int);
  virtual DLLExport void _export WINAPI StartExternPaint ();
  virtual DLLExport void _export WINAPI EndExternPaint ();
  virtual DLLExport void _export WINAPI OnMapChange (double,int,int,int,int,int);
  };

