/////////////////////////////////////////////////////////
//  Deklarationen fuer kubisch interpolierte Konturen  //
/////////////////////////////////////////////////////////
// $Header:   P:/marille/clinicum/include/rev/cubspl.hpv   1.7   11 Sep 1997 19:00:10   HANNES  $
// $Log:   P:/marille/clinicum/include/rev/cubspl.hpv  $
// 
//    Rev 1.7   11 Sep 1997 19:00:10   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.6   10 Jun 1996 10:14:48   GERHOLD
// pragma pack
// 
//    Rev 1.5   24 Mar 1996 12:12:32   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.4   02 Feb 1996 10:59:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   20 Mar 1995 12:16:00   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.2   27 Jun 1994 10:50:26   HANNES
// Inline Funktionen nicht exportieren
// 
//    Rev 1.1   24 Jun 1994 19:19:02   MARTIN
// Frmobject in DLL
// 
//    Rev 1.5   27 Jun 1993 12:27:06   MARTIN
// uCalcSoftVect
// 
//    Rev 1.4   16 Jun 1993 16:54:48   MARTIN
// WriteCubSpl
// 
//    Rev 1.3   15 Jun 1993 23:25:14   MARTIN
// ChangeCubSplPt
// 
//    Rev 1.2   19 May 1993 19:01:48   MARTIN
// uCubSpl
// 
//    Rev 1.1   09 Mar 1993 22:56:28   MARTIN
// erste funktionsfaehige Version
// 
//    Rev 1.0   03 Mar 1993 15:43:38   MARTIN
// Initial revision.
//


// Definitionen fuer Modus basepoint.m:
#define BP_P_EDITABLE  0x0001L  // Punkt editierbar
#define BP_WP_EDITABLE 0x0002L  // Winkel in Richtung prev editierbar
#define BP_WN_EDITABLE 0x0004L  // Winkel in Richtung next editierbar
#define BP_LP_EDITABLE 0x0008L  // Laenge in Richtung prev editierbar
#define BP_LN_EDITABLE 0x0010L  // Laenge in Richtung next editierbar
#define BP_W_DEPENDENT 0x0020L  // Winkel absolut abhaengig (w1-w2 konstant)
#define BP_L_DEPENDENT 0x0040L  // Laengen absolut abhaengig (l1/l2 konstant)
#define BP_WP_FOLLOW_N 0x0080L  // Winkel dem prev Nachbarpunkt nachfuehren
#define BP_WN_FOLLOW_N 0x0100L  // Winkel dem next Nachbarpunkt nachfuehren
#define BP_LP_FOLLOW_N 0x0200L  // Laenge dem prev Nachbarpunkt nachfuehren
#define BP_LN_FOLLOW_N 0x0400L  // Laenge dem next Nachbarpunkt nachfuehren
// noch nicht implementiert:
#define BP_W_CALC_N    0x0800L  // Winkel immer aus Nachbarpunkten berechnen

// minimale Distanz zwischen zwei Stuetzpunkten:
#define MIN_DISTANCE 1.0E-3


typedef struct basepoint FAR *LPBASEPOINT;

#pragma pack(1)
struct basepoint {
  LPBASEPOINT prev, next;
  // Daten aus der Datenbank
  DWORD m;    // Modus
  fpt p;      // Stuetzpunkt
  float wp;   // rel. Winkel in Richtung prev
  float wn;   // rel. W. in R. next oder absolute Winkeldifferenz zu wp
  float lp;   // rel. Laenge in Richtung prev
  float ln;   // rel. L. in R. next oder Faktor f mit ln = lp * f (absolut !)
  // temporaere Daten zum Editieren des Stuetzpunktes
  fpt dp, dn;        // Steigungsvektor in Richtung prev/next (Laenge tend !)
  float tend;        // Laenge des Vektors zum naechsten Punkt
  // temporaere Daten zum Berechnen des Splines
  float ax, bx, cx, dx;      // Koeffizienten der Polynome in Richtung next
  float ay, by, cy, dy;      // (fuer jede Koordinate getrennt)
  };
#pragma pack()


class FAR CubSpl {
 public:
  LPBASEPOINT head, tail;
  float tmax;
  DLLExport LPVOID _export WINAPI operator new(size_t size);
  DLLExport void _export WINAPI operator delete(LPVOID ptr);
  DLLExport _export WINAPI CubSpl();
  DLLExport void _export WINAPI AddPt(DWORD m, fpt FAR *p, float wp, float wn, float lp, float ln);
  DLLExport void _export WINAPI Free();
  DLLExport void _export WINAPI GetLN(float FAR *res, LPBASEPOINT pt);
  DLLExport void _export WINAPI CalcDpDn(LPBASEPOINT pt); // Berechnet dp/dn aus Winkeln und Laengen
  DLLExport void _export WINAPI CalcAllDpDn();            // selbiges fuer alle Punkte
  // die folgenden Funktionen ergeben TRUE, wenn die Aenderung moeglich war
  // und aendern dem Modus entsprechend alle davon abhaengenden Daten;
  // durch eine solche Aenderung koennen sich auch andere Punkte mitaendern !
  DLLExport BOOL _export WINAPI ChangePt(LPBASEPOINT pt, fpt FAR *p);   // der Stuetzpunkt selbst
  DLLExport BOOL _export WINAPI ChangeDp(LPBASEPOINT pt, fpt FAR *dp);  // Steigung in Richtung prev
  DLLExport BOOL _export WINAPI ChangeDn(LPBASEPOINT pt, fpt FAR *dp);  // Steigung in Richtung next
 private:
  void InitCalc();
  void EvalFunc(float t, fpt FAR *res);
 public:
  DLLExport void _export WINAPI CalcCont(fpt FAR *cnt, int numpts);
  DLLExport _export WINAPI ~CubSpl();
  };

typedef CubSpl FAR *LPCUBSPL;


// Weichteileditierobjekt

#pragma pack(1)
struct Referenz {
  WORD R, I;
  };
#pragma pack()

#pragma pack(1)
struct DefSoftEdit_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  DWORD rcolor;           // Farbe der Hebel
  DWORD rMoveColor;       // Farbe fuer XOR-Modus + Dicke fuer Kontur
  WORD cntR, cntI;        // Referenz auf die zugehoerige Originalkontur
  DWORD rPtCount;         // Anzahl der Punkte zum Generieren der Kontur
  WORD scR, scI;          // Referenz auf die world to screen Matrix
  DWORD rdispfact;        // Faktor fuer Anzeige der Steigungshebel
  union {                 // free_part:  m p w l { l w m p w l } l w m p
    DWORD rm;              // Modus
    Referenz p;           // Punkt
    Referenz w;           // Winkel
    Referenz l;           // Laenge
    } fp[8];              // mindestens Anfangs- und Endpunkt angeben !
  };
#pragma pack()

// Definitionen fuer SoftEditObj.ed_state:
#define ED_NOTHING 0      // nicht im Editiermodus
#define ED_POINT   1      // Verschieben des Stuetzpunktes
#define ED_LEFT    2      // Veraendern des linken Steigungshebels
#define ED_RIGHT   3      // Veraendern des rechten Steigungshebels

class FAR SoftEditObj : public FrmObject {
 public:
  DefSoftEdit_param FAR *Par() { return (DefSoftEdit_param FAR *)ScriptParam; }
  ftr2 wtos;             // world to screen Matrix
  ftr2 stow;             // inverse
  LPCUBSPL cs;           // kubischer Spline
  int ed_state;          // Editierstatus
  BOOL clear_old;        // Spline XOR am Bildschirm ?
  int ptCount;
  float dispfact;
  LONG color;
  LONG MoveColor;
  LPBASEPOINT actpt;     // aktueller Stuetzpunkt (waehrend Editieren)
  DLLExport _export WINAPI SoftEditObj(LPVOID p, mdiChild *c);
  virtual DLLExport _export WINAPI ~SoftEditObj();
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *, int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *, int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);
  virtual DLLExport BOOL _export WINAPI OnLButtonDown(WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove(WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp(WPARAM,int,int,int);
  DLLExport void _export WINAPI DrawMark(PaintContext *pc, int Seite, int px, int py);
  DLLExport void _export WINAPI DrawLine(PaintContext *pc, int Seite, int px1, int py1, int px2, int py2);
  DLLExport BOOL _export WINAPI NearPt(int x, int y, fpt FAR *p);
  DLLExport void _export WINAPI MovePt(int x, int y);
  DLLExport void _export WINAPI DrawMove(int Seite);
  DLLExport void _export WINAPI DoMove(int Seite);
  };

typedef SoftEditObj FAR *LPSOFTEDITOBJ;

#pragma pack(1)
struct uCubSpl_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  WORD cntR, cntI;        // Referenz auf Ergebniskontur
  DWORD rPtCount;         // Anzahl der Punkte zum Generieren der Kontur
  union {                 // free_part:  m p w l { l w m p w l } l w m p
    DWORD rm;             // Modus
    Referenz p;           // Punkt
    Referenz w;           // Winkel
    Referenz l;           // Laenge
    } fp[8];              // mindestens Anfangs- und Endpunkt angeben !
  };
#pragma pack()

#pragma pack(1)
struct ChangeCubSplPt_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  WORD objR, objI;        // Referenz auf SoftEditObject
  WORD optR, optI;        // Referenz auf au veraendernden Stuetzpunkt
  WORD nptR, nptI;        // neue Koordinaten des Stuetzpunktes
  DWORD rUpdateMode;      // 0 = nichts, 1 = Variable, 2 = Kontur schreiben
  };
#pragma pack()

#pragma pack(1)
struct WriteCubSpl_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  WORD objR, objI;        // Referenz auf SoftEditObject
  DWORD rWriteCont;       // flag: soll Kontur geschrieben werden ?
  };
#pragma pack()

#pragma pack(1)
struct uCalcSoftVect_param {
  WORD ParSize;
  // zusaetzliche Parameter Daten
  WORD dstR, dstI;        // Ergebnis
  struct {
    WORD refR, refI;      // Referenzlinie
    WORD scR, scI;        // Skalierungsfaktoren
    WORD srcR, srcI;      // Ausgangsvektor
    } t[1];               // variable Anzahl
  };
#pragma pack()

