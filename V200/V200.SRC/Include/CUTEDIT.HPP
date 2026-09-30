////////////////////////////////////
//  Deklarationen fuer Chirurgie  //
////////////////////////////////////
// $Header:   P:/marille/clinicum/include/rev/cutedit.hpv   1.7   11 Sep 1997 19:00:10   HANNES  $
// $Log:   P:/marille/clinicum/include/rev/cutedit.hpv  $
// 
//    Rev 1.7   11 Sep 1997 19:00:10   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.6   10 Apr 1997 11:13:54   Martin
// 32-bit-isiert
// 
//    Rev 1.5   24 Mar 1996 12:12:32   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:59:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   05 Apr 1995 16:49:46   HANNES
// 
//    Rev 1.2   27 Jun 1994 10:56:02   HANNES
// Exportierte Funktionen nicht mehr als Inline
// 
//    Rev 1.1   24 Jun 1994 19:19:04   MARTIN
// Frmobject in DLL
// 
//    Rev 1.1   22 Apr 1993 21:04:24   MARTIN
// Erste brauchbare Version
// 
//    Rev 1.0   19 Apr 1993 01:31:20   MARTIN
// Initial revision.
// 


// weitere Definitionen fuer boneside (zur Definition im Script):
#define BS_INSIDE    3
#define BS_OUTSIDE   4
#define BS_SAMESIDE  5
#define BS_OTHERSIDE 6


typedef struct cutpoint FAR *LPCUTPOINT;
typedef struct cont_pt_list FAR *LPCONTPTLIST;
typedef struct cont_piece_list FAR *LPCONTPIECELIST;
typedef struct cont_part_list FAR *LPCONTPARTLIST;
typedef struct cont_link_list FAR *LPCONTLINKLIST;
typedef struct contlist FAR *LPCONTLIST;

struct cont_pt_list {
  LPCONTPTLIST prev, next;
  fpt pt;
  int ind;
  };

// Definitionen fuer cont_piece_list.cut_dir:
#define CD_UNKNOWN 0
#define CD_RIGHT   1
#define CD_LEFT    2

// Definitionen fuer cont_piece_list.part_mark und cutpoint.part_left:
#define P_UNKNOWN 0
#define P_OLD     1
#define P_NEW     2
#define P_INVERS(x) (((x) == P_OLD) ? P_NEW : P_OLD)

struct cont_piece_list {
  LPCONTPIECELIST prev, next;
  LPCONTPTLIST pt_from, pt_to;  // erster und letzter Punkt des Stueckes
  // nur gueltig waehrend Durchfuehrung des Schnittes:
  LPCUTPOINT parted_by[2];   // welche(r) Schnittpunkt(e) teil(t/en) Stueck ?
  LPCONTPTLIST ins_after[2]; // nach welchem Punkt vom Stueck teilen ?
  int cut_dir[2];            // in welche Richtung geht Schnitt ?
  int part_mark;             // gehoert zu altem oder neuem Teil ?
  LPCUTPOINT cut_before;     // Schnittlinie (vor dem Stueck einzufuegen)
  LPCUTPOINT cut_after;      // Schnittlinie (nach dem Stueck einzufuegen)
  LPCONTLINKLIST link_before;// Link (vor dem Stueck)
  LPCONTLINKLIST link_after; // Link (nach dem Stueck)
  };

struct cont_part_list {
  LPCONTPARTLIST next;
  short part_num;
  short bone_side;  // siehe Konstanten BS_* aus cutcont.hpp
  LPCONTPIECELIST piecehead, piecetail;
  };

struct cont_link_list {
  LPCONTLINKLIST next;
  short part_from, part_to;
  LPCONTPTLIST pt_from, pt_to;
  };

struct contlist {         // eine Kontur der Konturgruppe
  LPCONTLIST next;
  int num_org_pts;
//  BOOL ptindvalid;        // sind pts->ind gueltig ?
  LPCONTPARTLIST parthead, parttail;
  LPCONTLINKLIST linkhead, linktail;
  LPCONTPTLIST pthead, pttail;
  // nur gueltig waehrend Durchfuehrung des Schnittes:
  LPCUTPOINT parted_by[2];  // welche(r) Schnittpunkt(e) teil(t/en) Kontur ?
  BOOL already_parted;      // Aufteilung durchgefuehrt ?
  };


// Definitionen fuer cutpoint.type:
#define CT_CUTBEGIN 0x00 // Beginn eines (Teil-)Schnittes
#define CT_CUTMID   0x01 // Pkt. des Schnittverlaufes, liegt NICHT auf Kontur
#define CT_CUTEND   0x02 // Ende eines Schnittes, liegt auf Kontur
#define CT_CUTCALC  0x03 // berechneter Schnittpunkt (nicht waehrend Eingabe)

struct cutpoint {          // ein Punkt eines Schnittverlaufes
  LPCUTPOINT prev, next;
  fpt pt;           // Koordinaten des Schnittpunktes
  int type;         // Typ des Schnittpunktes
  // nur waehrend Durchfuehrung des Schnittes gueltig
  short part_num;   // schneidet welche Teilnummer ?
  int part_left;    // welcher Teil liegt links vom Schnitt ?
  };


class FAR CutCnt {
 public:
  LPCUTPOINT cphead, cptail;
  LPCONTLIST cnts;
  short act_part_num;   // aktuelle Teilnummer, -1 wenn kein bestimmter Teil
  DLLExport LPVOID _export WINAPI operator new(size_t size);
  DLLExport void _export WINAPI operator delete(LPVOID ptr);
  DLLExport _export WINAPI CutCnt();
  DLLExport _export WINAPI ~CutCnt();
  DLLExport void _export WINAPI Free();              // gibt belegten Speicherplatz frei
  DLLExport void _export WINAPI FreeCp();            // die Schnittpunkt-Liste
  DLLExport void _export WINAPI FreeCnts();          // die (geschnittenen) Konturen
  DLLExport BOOL _export WINAPI PtsEqual(fpt FAR *pt1, fpt FAR *pt2); // sind zwei Punkte gleich ?

  // in den folgenden beiden Funktionen beschreiben part, piece und pt
  // eine Konturlinie (geht von pt nach pt->next); in cp ist der
  // neue Schnittpunkt (liegt zw. pt und pt->next) zu uebergeben !
  DLLExport fpt _export WINAPI GetPrevPt(fpt cp, LPCONTPARTLIST part, LPCONTPIECELIST piece, LPCONTPTLIST pt, BOOL try_next = TRUE);
  DLLExport fpt _export WINAPI GetNextPt(fpt cp, LPCONTPARTLIST part, LPCONTPIECELIST piece, LPCONTPTLIST pt, BOOL try_prev = TRUE);
  DLLExport void _export WINAPI GetSCos(double FAR *dres, double dx, double dy);  // Hilfsfunktiuon fuer CalcBoneSide

  // in der folgenden Funktion muss sichergestellt sein, dass die Vektoren
  // cntA->cntB, cntB->cntC und cntB->cpD eine Laenge > 0 haben !
  DLLExport short _export WINAPI CalcBoneSide(fpt cntA, fpt cntB, fpt cntC, fpt cpD);
  DLLExport void _export WINAPI GetNearestContPt(float FAR *res, fpt FAR *p, short one_part = -1); // Abst. zu Kontur
  DLLExport void _export WINAPI GetCntPts(LPCONTLIST cnt, fpt FAR *pts, int PtCount);  // Punkte
  DLLExport void _export WINAPI GetCntPP(LPCONTLIST cnt, LPCONTPART cp, int np);  // Teile
  DLLExport void _export WINAPI GetCntLinks(LPCONTLIST cnt, LPCONTLINK cl, int nl);  // Links
  DLLExport LPCONTLIST _export WINAPI UnpackCnt(fpt FAR *cnt);  // Datenbankkontur -> Speicherkontur
  DLLExport void _export WINAPI CalcPtInds(LPCONTLIST cnt);  // berechnet die Punktindizes
  DLLExport int _export WINAPI CntSize(LPCONTLIST cnt);  // Speicherbedarf fuer die Datenbankstruktur
  DLLExport void _export WINAPI PackCnt(fpt FAR *dcnt, LPCONTLIST scnt);  // Speicher -> Datenbank
  DLLExport short _export WINAPI GetFreePartNum();   // ermittle freie Teilnummer fuer neuen Schnitt
  DLLExport void _export WINAPI CleanCutPoints();    // entfernt alle berechneten Schnittpunkte
  DLLExport BOOL _export WINAPI CalcCutPoints();     // berechnet Schnittpunkte mit allen Konturen
  DLLExport BOOL _export WINAPI IsCutLineBegin(LPCUTPOINT cp);
  DLLExport BOOL _export WINAPI IsCutLineEnd(LPCUTPOINT cp);
  DLLExport int _export WINAPI AssignCutPoints();    // weist den Pieces die Schnittpunkte zu
  DLLExport void _export WINAPI MarkCutLine(LPCUTPOINT cp, int part_left);
  DLLExport BOOL _export WINAPI DividePieces(short part_num); // Ergebnis: neue Aufteilung gefunden ?
  DLLExport LPCONTPIECELIST _export WINAPI CutLineToPieces(LPCONTLIST cnt, LPCUTPOINT cp, BOOL reverse);
  DLLExport BOOL _export WINAPI DividePart(short part_num, short new_part_num1, short new_part_num2);
  DLLExport fpt _export WINAPI CalcPartSchwer(short part_num, LPCONTLIST onecnt = NULL);
  DLLExport void _export WINAPI PartRest(short part_num, short new_part_num1, short new_part_num2);
  DLLExport void _export WINAPI AddLinks();   // neue Links in die Konturen einfuegen
  DLLExport void _export WINAPI AssignLinks();  // Links den richtigen Teilen zuweisen
  DLLExport BOOL _export WINAPI PartClosed(short part_num);  // Teil geschlossen ?
// Rueckgabewerte fuer ApplyCut:
#define AC_CUTOK     0    // Schnitt konnte durchgefuehrt werden
#define AC_MULTIPART 1    // Schnitt geht ueber verschiedene Teile
#define AC_TOOFEW    2    // nur ein Schnitt bei geschlossener Kontur
#define AC_TOOMANY   3    // mehr als 2 Schnitte bei einem Konturteil
#define AC_NOCUT     4    // noch kein Schnitt eingegeben
#define AC_NOTBONE   5    // Schnitt geht nicht Richtung Knochen
#define AC_NOTCONN   6    // Teilschnitte haengen nicht zusammen
  DLLExport int _export WINAPI ApplyCut();         // versucht den Schnitt durchzufuehren
  };

typedef CutCnt FAR *LPCUTCNT;


// Schnitteditierobjekt

#pragma pack(1)
struct DefCutEdit_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  DWORD rcolor;        // Farbe der Schnittlinien
  DWORD rMoveColor;    // Farbe fuer XOR-Modus + Dicke fuer Kontur
  WORD scR, scI;      // Referenz auf die world to screen Matrix
  struct {
    WORD R, I;        // Referenz(en) auf zugehoerige(n) Originalkontur(en)
    } CntRef[1];
  };
#pragma pack()

// Definitionen fuer CutEditObj.ed_state:
#define ED_INIT   0   // noch kein Schnittpunkt eingegeben
#define ED_ADD    1   // Anhaengen eines neuen Schnittendpunktes
#define ED_INIMOV 2   // Verschieben eines Schnittpunktes
#define ED_ADDMOV 3

class FAR CutEditObj : public FrmObject {
 public:
  DefCutEdit_param FAR *Par() { return (DefCutEdit_param FAR *)ScriptParam; }
  ftr2 wtos;             // world to screen Matrix
  ftr2 stow;             // inverse
  LPCUTCNT cc;           // Schnitt
  LPCUTPOINT actcp;      // aktueller Schnittpunkt
  int ed_state;          // Editierstatus
  BOOL clear_old;        // Schnitt XOR am Bildschirm ?
  DWORD color,MoveColor;
  DLLExport _export WINAPI CutEditObj(LPVOID p, mdiChild *c);
  virtual DLLExport _export WINAPI ~CutEditObj();
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *, int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *, int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);
  virtual DLLExport BOOL _export WINAPI OnLButtonDown(WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk(WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove(WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp(WPARAM,int,int,int);
  DLLExport void _export WINAPI DrawMark(PaintContext *pc, int Seite, int px, int py);
  DLLExport void _export WINAPI DrawLine(PaintContext *pc, int Seite, int px1, int py1, int px2, int py2);
  DLLExport BOOL _export WINAPI NearPt(int x, int y, fpt FAR *p);
  DLLExport BOOL _export WINAPI NearCont(int x, int y, fpt FAR *p);  // in Naehe von Konturstueck ?
  DLLExport void _export WINAPI MovePt(int x, int y);
  DLLExport void _export WINAPI DrawMove(int Seite);
  DLLExport void _export WINAPI DoMove(int Seite);
  };

