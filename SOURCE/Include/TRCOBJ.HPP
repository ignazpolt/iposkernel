// $Header:   P:/marille/clinicum/include/rev/trcobj.hpv   1.21   28 Apr 1999 19:01:42   Martin  $
// $Log:   P:/marille/clinicum/include/rev/trcobj.hpv  $
// 
//    Rev 1.21   28 Apr 1999 19:01:42   Martin
// Marker: optionaler Parameter Skalierungsfaktor
// 
//    Rev 1.20   05 Oct 1998 11:24:24   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.19   25 May 1998 13:38:20   Hannes
// 
//    Rev 1.18   07 May 1998 15:16:50   Hannes
// Kreuzchen im Contain - Object
// 
//    Rev 1.17   27 Apr 1998 12:51:20   Hannes
// 
//    Rev 1.16   21 Apr 1998 19:31:54   Hannes
// Erweiterung um den Containerbausteines
// 
//    Rev 1.15   02 Mar 1998 19:13:26   Hannes
// Trc_DefEllipse
// 
//    Rev 1.14   08 Sep 1997 11:07:36   Gerhold
// WORD-Parameter in WPARAM-Parameter umgewandelt
// 
//    Rev 1.13   18 Aug 1997 18:01:38   Martin
// VTO Formular-faehig
// 
//    Rev 1.12   05 May 1997 17:24:26   Hannes
// 
//    Rev 1.11   17 Mar 1997 16:40:42   Martin
// Trc_RectImage erweitert (2.Punkt)
// 
//    Rev 1.10   25 Jul 1996 20:03:10   GERHOLD
// #pragma pack(1)
// 
//    Rev 1.9   22 Mar 1996 12:14:56   HANNES
// Aenderungen Hannes
// 
//    Rev 1.8   02 Feb 1996 11:00:24   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.7   27 Aug 1995 13:06:02   MARTIN
// 
//    Rev 1.6   14 Aug 1995 08:23:06   HANNES
// TrcFilledCont::Reset bzw. SetConnection
// 
//    Rev 1.5   21 Mar 1995 16:21:30   HANNES
// 
//    Rev 1.4   20 Mar 1995 12:16:44   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.3   20 Sep 1994 11:31:30   HANNES
// Trc_DefFilledCont
// 
//    Rev 1.2   27 Jun 1994 11:11:26   MARTIN
// exportierte virtuelle Funktionen nicht mehr inline
// 
//    Rev 1.1   24 Jun 1994 19:19:12   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.17   13 Apr 1994 14:38:30   HANNES
// Update von Fraben im MovePattern
// 
//    Rev 1.16   20 Jan 1994 23:59:06   HANNES
// OnSetCursor bei MovePatterns
// 
//    Rev 1.15   05 Jul 1993 14:44:24   MARTIN
// InvalidOnUpdate() fuer DefMovePattern
// 
//    Rev 1.14   07 Jun 1993 15:11:22   MARTIN
// neues Objekt DefMovePattern
// 
//    Rev 1.13   24 May 1993 14:20:32   HANNES
// ??
// 
//    Rev 1.12   22 Apr 1993 21:06:40   MARTIN
// Erweiterungen des TrcContObj, LINELISTs
// 
//    Rev 1.11   19 Apr 1993 01:32:46   MARTIN
// Aenderungen in TrcContObj fuer geschnittene Konturen
// 
//    Rev 1.10   16 Apr 1993 19:44:26   MARTIN
// Bunte Patterns
// 
//    Rev 1.9   02 Apr 1993 18:05:02   HANNES
// ?
// 
//    Rev 1.8   17 Mar 1993 18:06:12   HANNES
// 32 bit Umstellung..
// 
//    Rev 1.7   10 Mar 1993 21:20:44   MARTIN
// Objekt DefPattern
// 
//    Rev 1.6   02 Mar 1993 19:41:00   MARTIN
// neues Objekt TrcArcObj
// 
//    Rev 1.5   24 Feb 1993 21:35:12   MARTIN
// Verwendung von Bitmaps zur schnelleren Ausgabe von
// Metafile-Objekten (TrcPattern)
// 
//    Rev 1.4   17 Feb 1993 15:26:56   MARTIN
// Umbau auf FrmObjects
// 
//    Rev 1.3   02 Feb 1993 12:03:48   MARTIN
// Trc_LineObj
// 
//    Rev 1.2   29 Jan 1993 21:17:52   MARTIN
// Entwicklung
// 
//    Rev 1.1   21 Jan 1993 23:49:10   MARTIN
// TrcContObj und TrcPatternObj definiert
// 
//    Rev 1.0   20 Jan 1993 15:53:36   MARTIN
// Initial revision.
// 
// to be included first: "frmobj.hpp"

struct LogPt {
  int x, y;
  };

#pragma pack(1)
// Script - Parameter - Strukturen
#define MARK_SQUARE   0
struct Trc_DefMark_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD ptR, ptI;        // Referenz auf den Ort
  DWORD rtype;          // Typ des Markers
  WORD colR, colI;      // Referenz auf die Farbe
  DWORD ScaleFact;      // optional: Skalierungsfaktor
  };

struct Trc_DefLine_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD pt1R, pt1I;      // Referenz auf den 1. Punkt
  WORD pt2R, pt2I;      // Referenz auf den 2. Punkt
  WORD colR, colI;      // Referenz auf die Farbe
  };
struct Trc_DefGrid_param {
  Trc_DefLine_param l;
  // zusaetzliche Parameter Daten
  DWORD dx,dy;
  };

struct Trc_DefRectangle_param {
  Trc_DefLine_param l;
  // zusaetzliche Parameter Daten fuers Rechteck
  DWORD rbrushStyle;      // Brush - Typ
  DWORD rbrushColor;      // Farbe zum Fuellen
  DWORD rbrushHatch;      // Fuer Hatch - Brush
  };

struct Trc_DefArc_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD mR, mI;          // Referenz auf den Mittelpunkt
  WORD pt1R, pt1I;      // Referenz auf den 1. Punkt
  WORD pt2R, pt2I;      // Referenz auf den 2. Punkt
  WORD colR, colI;      // Referenz auf die Farbe
  };

struct Trc_DefPattern_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD pt1R, pt1I;      // Referenz auf den ersten Punkt
  WORD pt2R, pt2I;      // Referenz auf den zweiten Punkt
  DWORD rx1, ry1;          // Koordinaten des ersten Punktes im Metafile
  DWORD rx2, ry2;          // Koordinaten des zweiten Punktes im Metafile
  WORD picR, picI;      // Referenz auf das Metafile
  WORD colR, colI;      // Referenz auf die Farbe
  };

struct DefPattern_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD picR, picI;      // Referenz auf das Metafile
  WORD ptR, ptI;        // Referenz auf Mittelpunkt
  DWORD _xfact, _yfact;   // x- und y-Skalierungsfaktor
  DWORD _ang;            // Winkel in Grad
  WORD colR, colI;      // Referenz auf die Farbe (free !)
  };

// Definitionen fuer DefMovePattern_param.move_mode
#define MP_SHOWHORIZ 0x01   // horizontale Verschiebung Anzeigen
#define MP_SHOWVERT  0x02   // vertikale Verschiebung anzeigen
#define MP_EDITHORIZ 0x04   // horizontale Verschiebung mit Maus editierbar
#define MP_EDITVERT  0x08   // vertikale Verschiebung mit Maus editierbar

struct DefMovePattern_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD picR, picI;      // Referenz auf das Metafile
  WORD ptR, ptI;        // Referenz auf Mittelpunkt
  float xfact, yfact;   // x- und y-Skalierungsfaktor
  float ang;            // Winkel in Grad
  WORD modeR, modeI;    // Flags fuer das Verschieben (siehe Konstanten MP_*)
  DWORD rmove_color;     // Farbe zum Verschieben in XOR
  WORD hminR, hminI;    // minimaler horizontaler Verschiebungswert
  WORD hmaxR, hmaxI;    // maximaler horizontaler Verschiebungswert
  WORD hvalR, hvalI;    // aktueller horizontaler Verschiebungswert
  WORD hfacR, hfacI;    // horizontaler Skalierungsfaktor
  WORD vminR, vminI;    // minimaler vertikaler Verschiebungswert
  WORD vmaxR, vmaxI;    // maximaler vertikaler Verschiebungswert
  WORD vvalR, vvalI;    // aktueller vertikaler Verschiebungswert
  WORD vfacR, vfacI;    // vertikaler Skalierungsfaktor
  WORD colR, colI;      // Referenz auf die Farbe (free !)
  };

struct Trc_DefCont_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD cntR, cntI;      // Referenz auf die Kontur
  WORD colR, colI;      // Referenz auf die Farbe
  };

struct Trc_DefContain_param {
  Trc_DefCont_param cnt;
  // zusaetzliche Parameter Daten
  DWORD Kennung;        // Kenn - Nummer im BLOB
  DWORD pt1,pt2;        // Clip - Rechteck
  DWORD a,b;            // Skalierung Y - Achse
  DWORD dscale;         // Skalierung X - Achse
  };

struct Trc_DefContain2_param {
  Trc_DefContain_param dc;
  DWORD b2;
  };

struct Trc_DefFilledCont_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD cntR, cntI;      // Referenz auf die Kontur
  WORD colR, colI;      // Referenz auf die Farbe
  DWORD rbrushStyle;      // Brush - Typ
  DWORD rbrushColor;      // Farbe zum Fuellen
  DWORD rbrushHatch;      // Fuer Hatch - Brush
  };

struct Trc_DefRectImage_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  DWORD FileName;       // Name des Bildes (mit Pfad)
  DWORD pt;             // Punkt
  DWORD scx;            // optional: X-Skalierungsfaktor
  DWORD scy;            // optional: Y-Skalierungsfaktor
  DWORD ang;            // optional, nur fuer WMF: Rotationswinkel
  DWORD pt2;            // optional: 2. Punkt
  DWORD flags;          // optional: flags fuer Optionen (siehe RI_*)
  DWORD ratio;          // optional, Ausgabeparameter: Breite zu Hoehe
  };
// flags fuer Trc_DefRectImage_param->flags (nur wenn 2. Punkt angegeben):
#define RI_LINKS 1L
#define RI_RECHTS 2L
#define RI_OBEN 4L
#define RI_UNTEN 8L
// es muessen die Seiten angegeben werden, an denen das Bild anliegen soll
// wenn nichts angegeben -> zentriert
// wenn LINKS und RECHTS und OBEN und UNTEN angegeben -> Stretching
// Beispiel fuer drei angegebene Seiten:
// LINKS, OBEN, UNTEN angegeben -> das Bild kann eventuell rechts oder
// links der rechten Begrenzung enden
// wenn zwei gegenueberliegende Seiten angegeben sind, wird das Bild
// so skaliert, dass es genau zwischen die beiden Seiten passt.
// Dabei wird das Seitenverhaeltnis beibehalten.

#pragma pack()

// Trace - Objekte als von FrmObject abgeleitete Klassen

class FAR TrcMarkObj : public FrmObject {
 public:
  Trc_DefMark_param FAR *Par() { return (Trc_DefMark_param FAR *)ScriptParam; }
  LONG color;
  int type;
  int px, py;     // aktuelle Koordinaten
  float sf;       // Skalierungsfaktor
  DLLExport _export WINAPI TrcMarkObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int,tr2 FAR *);
  };


class FAR TrcLineObj : public FrmObject {
 public:
  Trc_DefLine_param FAR *Par() { return (Trc_DefLine_param FAR *)ScriptParam; }
  LONG color;
  int p1x, p1y, p2x, p2y;    // aktuelle Koordinaten
  DLLExport _export WINAPI TrcLineObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);
  };

class FAR TrcGridObj : public TrcLineObj {
 public:
  float dx,dy;
  Trc_DefGrid_param FAR *Par() { return (Trc_DefGrid_param FAR *)ScriptParam; }
  DLLExport _export WINAPI TrcGridObj (LPVOID p,mdiChild *);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *pc, int Seite, tr2 FAR *sc);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  };

class FAR TrcArcObj : public FrmObject {
 public:
  Trc_DefArc_param FAR *Par() { return (Trc_DefArc_param FAR *)ScriptParam; }
  LONG color;
  int r, mx, my, p1x, p1y, p2x, p2y;    // aktuelle Koordinaten
  DLLExport _export WINAPI TrcArcObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);
  DLLExport void _export WINAPI GetSCos(double FAR *dres, double dx, double dy);
  DLLExport BOOL _export WINAPI VectInside(double cc, double c1, double c2);
  };


// fuer ratiomode:
#define COS_POS 0x0000
#define COS_NEG 0x0001
#define SIN_POS 0x0000
#define SIN_NEG 0x0002
#define MOD_TAN 0x0004
#define MOD_COT 0x0008
#define QUADRANT(x) ((x) & 0x0003)
#define TANORCOT(x) ((x) & 0x000C)

class FAR PatternBaseClass : public FrmObject {
 public:
  LONG color;
  BOOL trans_color;     // Farbe angegeben ?
  ftr2 scale;           // Skalierungsmatrix
  fRECT rmf;            // Extremwerte des Metafiles
  HMETAFILE hmf;        // Handle des Meta - Files 
  HBITMAP hBitmap;      // Handle des Bitmaps, wenn vorhanden
  int bmx, bmy;         // linke obere Ecke in MM_TEXT-Koordinaten
  int bmdx, bmdy;       // Breite und Hoehe in MM_TEXT-Koordinaten
  float oldratio;       // Verhaeltnis scale.A[0][0] zu scale.A[0][1]
  int oldratiomode;     // tan oder cotan, Quadrant
  DWORD oldpenstyle;    // die obersten 8 Bit von actdiPen
  DLLExport _export WINAPI PatternBaseClass(LPVOID p, mdiChild *c);
  // virtuelle Funktionen fuer Basisklasse:
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);
  // virtuelle Funtionen fuer abgeleitete Klassen:
  virtual DLLExport BOOL _export WINAPI GetPicRef(WORD FAR *picR, WORD FAR *picI);
  virtual DLLExport void _export WINAPI GetColRef(WORD FAR *colR, WORD FAR *colI);
  virtual DLLExport BOOL _export WINAPI OtherUpdate();        // zusaetzliche Updates und
  virtual DLLExport void _export WINAPI OtherSetConn();       // zusaetzliche Connections
  virtual DLLExport void _export WINAPI OtherClearConn();     // der abgeleiteten Klassen
  // andere Funktionen:
  DLLExport void _export WINAPI GetBitMap(PaintContext *pc, tr2 FAR *sc);
  DLLExport void _export WINAPI FreeBitMap();
  DLLExport void _export WINAPI GetMinMaxInt(tr2 FAR *sc, RECT FAR *r, DWORD col);
  };


class FAR TrcPatternObj : public PatternBaseClass {
 public:
  Trc_DefPattern_param FAR *Par() { return (Trc_DefPattern_param FAR *)ScriptParam; }
  int p1x, p1y, p2x, p2y;  // Koordinaten der alten Punkte
  BOOL doInvert;        // Muss invertiert werden ? 
  DLLExport _export WINAPI TrcPatternObj(LPVOID p, mdiChild *c, BOOL doInv);
  virtual DLLExport BOOL _export WINAPI GetPicRef(WORD FAR *picR, WORD FAR *picI);
  virtual DLLExport void _export WINAPI GetColRef(WORD FAR *colR, WORD FAR *colI);
  virtual DLLExport BOOL _export WINAPI OtherUpdate();
  virtual DLLExport void _export WINAPI OtherSetConn();
  virtual DLLExport void _export WINAPI OtherClearConn();
  DLLExport void _export WINAPI CalcPatScale();
  };


class FAR PatternObj : public PatternBaseClass {
 public:
  DefPattern_param FAR *Par() { return (DefPattern_param FAR *)ScriptParam; }
  int px, py;           // Koordinaten des alten Punktes
  BOOL first_call;      // erster Aufruf von CalcPatScale
  ftr2 fix_sc;          // unveraenderlicher Teil der Skalierungsmatrix
  DLLExport _export WINAPI PatternObj(LPVOID p, mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetPicRef(WORD FAR *picR, WORD FAR *picI);
  virtual DLLExport void _export WINAPI GetColRef(WORD FAR *colR, WORD FAR *colI);
  virtual DLLExport BOOL _export WINAPI OtherUpdate();
  virtual DLLExport void _export WINAPI OtherSetConn();
  virtual DLLExport void _export WINAPI OtherClearConn();
  DLLExport void _export WINAPI CalcPatScale();

  // virtuelle Funktionen fuer den Editor
  DLLExport void _export WINAPI GetNScFact (LPVOID);
  };


class FAR MovePatternObj : public PatternObj {
 public:
  DefMovePattern_param FAR *Par() { return (DefMovePattern_param FAR *)ScriptParam; }
  int dx, dy;                    // aktuelle Verschiebungswerte
  DWORD move_mode;               // aktuelle Modusflags
  DWORD move_color;
  float hmin, hmax, hval, hfac;  // horizontal: Schranken / Wert / Faktor
  float vmin, vmax, vval, vfac;  // vertikal: Schranken / Wert / Faktor
  int moving;                    // Editierstatus
  BOOL clear_old;                // Zahn XOR am Bildschirm ?
  int old_mx, old_my;            // Koordinaten der Maus bei LButtonDown
  int act_dx, act_dy;            // aktuelle Verschiebung (nur wenn moving)
  BOOL from_load;                // OtherUpdate von Load aufgerufen ?
  DLLExport _export WINAPI MovePatternObj(LPVOID p, mdiChild *c);
  virtual DLLExport BOOL _export WINAPI GetPicRef(WORD FAR *picR, WORD FAR *picI);
  virtual DLLExport void _export WINAPI GetColRef(WORD FAR *colR, WORD FAR *colI);
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport BOOL _export WINAPI OtherUpdate();
  virtual DLLExport BOOL _export WINAPI InvalidOnUpdate();
  virtual DLLExport void _export WINAPI OtherSetConn();
  virtual DLLExport void _export WINAPI OtherClearConn();
  DLLExport void _export WINAPI CalcPatScale();
  DLLExport void _export WINAPI DrawMove();              // Pattern in XOR zeichnen
  DLLExport void _export WINAPI CalcMove(int x, int y);  // act_dx und act_dy berechnen
  // kein Formulareditor:
  virtual DLLExport BOOL _export WINAPI AnalysePar (LPSTR,LPVOID FAR *);

  DLLExport BOOL _export WINAPI HitTest(int x, int y);
  DLLExport HCURSOR _export WINAPI MoveCursor ();

  // virtuelle Funktionen fuer die Verschiebung
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnSetCursor (int x,int y,int mode);
  };

class FAR ClickPatternObj : public MovePatternObj {
 public:
  void WriteVal ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  DLLExport _export WINAPI ClickPatternObj(LPVOID p, mdiChild *c);
  };

// interne Struktur fuer zeichnen von geschnittenen Konturen

typedef struct line_list FAR *LPLINELIST;

struct line_list {
  LPLINELIST next;
  int x1, y1, x2, y2;  // logische Koordinaten der Linie
  };

DLLExport void _export WINAPI FreeLineList(LPLINELIST l);

class FAR TrcContObj : public FrmObject {
 public:
  Trc_DefCont_param FAR *Par() { return (Trc_DefCont_param FAR *)ScriptParam; }
  LONG color;           // na was wohl ?
  WORD PtCount;         // Anzahl Punkte
  LogPt FAR *cnt;       // Kontur in logischen Koordinaten
  BOOL cut;             // ist Kontur geschnitten ?
  LPCUTCONT cc;         // Header der geschnittenen Kontur
  short act_part;       // aktuelle Teilnummer (-1 = ganze Kontur)
  int lastx, lasty;     // Koordinaten des letzten Punktes
  LPLINELIST FAR *linehead; // Liste mit gezeichneten Linien (temporaer)
  DLLExport _export WINAPI TrcContObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport BOOL _export WINAPI GetPtToObjVect (int Ptx, int Pty,
                 int FAR *Vectx, int FAR *Vecty);  // Vektor Pt->Obj
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);
  virtual DLLExport BOOL _export WINAPI IsCont();    // ist Objekt eine Kontur ?
  DLLExport void _export WINAPI SelectPart(short part_num);
  DLLExport void _export WINAPI UseLineList(LPLINELIST FAR *lines);
  DLLExport void _export WINAPI LineFrom(PaintContext *pc, int x, int y); // Linie ziehen mit Check
  DLLExport void _export WINAPI LineTo(PaintContext *pc, short ptind, int x, int y);
// Definitionen fuer parameter mode von PaintTransInt:
#define PTI_NORMAL 0   // Aufruf durch Paint()
#define PTI_SEL    1   // Aufruf durch PaintSel()
#define PTI_TRANS  2   // Aufruf durch PaintTrans()
  DLLExport void _export WINAPI PaintTransInt(PaintContext *, tr2 FAR *, int mode);
  };

class FAR TrcContainObj : public TrcContObj {
 public :
  Trc_DefContain_param FAR *Par() { return (Trc_DefContain_param FAR *)ScriptParam; }
  DLLExport _export WINAPI TrcContainObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI GetMinMax();
  fpt ptClip1,ptClip2;
  };

class FAR TrcContain2Obj : public TrcContainObj {
 private :
  void PaintBar (PaintContext *pc, LogPt FAR *lp);
 public :
  int xc0,yc0,xc1,yc1;
  Trc_DefContain_param FAR *Par() { return (Trc_DefContain_param FAR *)ScriptParam; }
  Trc_DefContain2_param FAR *CPar() { return (Trc_DefContain2_param FAR *)ScriptParam; }
  DLLExport _export WINAPI TrcContain2Obj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  };

class FAR TrcFilledContObj : public TrcContObj {
 public:
  Trc_DefFilledCont_param FAR *Par() { return (Trc_DefFilledCont_param FAR *)ScriptParam; }

  UINT brushStyle;
  DWORD brushColor;
  int brushHatch;
  virtual DLLExport void _export WINAPI Update();
  DLLExport _export WINAPI TrcFilledContObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  };

class FAR TrcRectangleObj : public TrcLineObj {
 public:
  Trc_DefRectangle_param FAR *Par() { return (Trc_DefRectangle_param FAR *)ScriptParam; }
  UINT brushStyle;
  DWORD brushColor;
  int brushHatch;
  DLLExport _export WINAPI TrcRectangleObj(LPVOID p, mdiChild *c);

  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *,int,tr2 FAR *sc);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *,int);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI PaintIt(HDC hDC,int x1,int y1,int x2,int y2);
  };

class FAR TrcEllipseObj : public TrcRectangleObj {
 public:
  DLLExport _export WINAPI TrcEllipseObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI PaintIt(HDC hDC,int x1,int y1,int x2,int y2);
  };

class MoveRect : public TrcRectangleObj {
  MoveObj mo;
 public :
  DLLExport _export WINAPI MoveRect (LPVOID p,mdiChild *c);
  virtual DLLExport LPMOVEOBJ _export WINAPI moptr();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);
  virtual DLLExport void _export WINAPI Paint(PaintContext *pc,int);
  };

class FAR TrcRectImageObj : public FrmObject {
 public:
  Trc_DefRectImage_param FAR *Par() { return (Trc_DefRectImage_param FAR *)ScriptParam; }
  float dx, dy, scalex, scaley;  // aktuelle Koordinaten (in logical units)
  BOOL SecondPoint;              // 2. Punkt angegeben ?
  float dx2, dy2;                // Koordinaten des 2. Punktes
  DWORD flags;                   // flags fuer Optionen (RI_*)
  fRECT ImageRect;               // Rechteck des Bildes
  float ang;                     // aktueller Rotationswinkel (nur WMF)
  ftr2 scale;                    // Skalierungsmatrix fuer WMFs
  BOOL FromLoad;                 // Aufruf Update() vom Load
  BOOL IsWMF;                    // Metafile oder Rasterbild ?
  HMETAFILE hImage;              // ImageMan - Handle
  DLLExport _export WINAPI TrcRectImageObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *,int);
  };

class MoveRectImage : public TrcRectImageObj {
  MoveObj mo;
 public :
  DLLExport _export WINAPI MoveRectImage (LPVOID p,mdiChild *c);
  virtual DLLExport LPMOVEOBJ _export WINAPI moptr();
  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL);
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnChar (WORD,int);
  virtual DLLExport BOOL _export WINAPI OnKeyUp (WORD,int);
  virtual DLLExport void _export WINAPI Paint(PaintContext *pc,int);
  };

#pragma pack(1)
#ifndef SCDT_DEFINED
struct SCDT_res {
  double a ;
  double b ;
  };
#define SCDT_DEFINED
#endif
#pragma pack()
#ifdef HASH_INCLUDED
DLLExport void _export WINAPI SortContainHash (hash FAR *h);
#endif

