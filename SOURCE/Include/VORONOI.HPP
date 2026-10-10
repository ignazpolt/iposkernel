//////////////////////////////////////////////////////////////////
// Bilden von Dreiecken in einem Punkthaufen
//////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/voronoi.hpv   1.4   23 Mar 1998 23:13:24   Martin  $
//  $Log:   P:/marille/clinicum/include/rev/voronoi.hpv  $
// 
//    Rev 1.4   23 Mar 1998 23:13:24   Martin
// uGetVGrid_param: anz int -> WORD (wegen 32 BIT !!!!)
// 
//    Rev 1.3   10 Jun 1996 10:16:08   GERHOLD
// pragma pack
// 
//    Rev 1.2   02 Feb 1996 10:59:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Mar 1995 12:16:46   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.0   24 Jun 1994 17:01:20   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   29 Nov 1993 08:40:14   HANNES
// 
//    Rev 1.3   15 Nov 1993 14:03:32   HANNES
// 
//    Rev 1.2   03 Nov 1993 17:46:50   HANNES
// Zwischenversion
// 
//    Rev 1.1   02 Nov 1993 11:08:34   HANNES
// Zwischenversion
// 
//    Rev 1.0   28 Oct 1993 08:49:56   HANNES
// Initial revision.
//
#define MAXTRIANGS    50
class FAR Triang {
 public :
  int p1,p2,p3;     // Punkte im pts Array der Klasse Voronoi,
                    // Punkte prinzipiell aufsteigend sortiert
  float ax,bx,cx,   // Flaechengleichnung (z = a*x + b*y + c)
        ay,by,cy;   // jeweils fuer beide Komponenten der Vektoren

  Triang (int i1,int i2,int i3);

  BOOL IsLine(int i1,int i2);  // Untersuchung, ob diese Linie im
                               // Dreieck vorkommt.
  int ThirdPt(int i1,int i2);  // Den Dritten Punkt der Dreiecks
  BOOL IsPoint(int i);         // Untersuchung, ob Punkt vorkommt
  int SecondPoint(int i);      // Anderen Punkt des Dreieckes

  void OrderDirection ();
  BOOL IsTriangEmpty ();
  void GetPlane (float z1,float z2,float z3,
                           float FAR &a,float FAR &b,float FAR &c);
  BOOL IsPtInside (fpt FAR *p);

  BOOL IsTriangInSect (double xmin,double xmax,double ymin,double ymax);
  BOOL IsRectPartInside (double xmin,double xmax,double ymin,double ymax);
  BOOL HLineCross (double y,double xmin,double xmax,int i1,int i2);
  BOOL VLineCross (double x,double ymin,double ymax,int i1,int i2);
  BOOL HLineCross (double y,double xmin,double xmax);
  BOOL VLineCross (double x,double ymin,double ymax);
  BOOL TestSection (double xmin,double xmax,double ymin,double ymax);
  };
typedef Triang FAR *LPTRIANG;
#define PTTYPE_UNKNOWN  0
#define PTTYPE_CONVEX   0
#define PTTYPE_INNER    1

#define ANZSEGS         10

#pragma pack(1)
struct ConvexPt {
  int pi;               // Index des Punktes
  ConvexPt FAR *Next;   // Naechster Punkt im Uhrzeigersinn
  ConvexPt FAR *Prev;
  };
#pragma pack()
typedef ConvexPt FAR *LPCPT;

struct FAR tag_ffpt {
  float x ;
  float y ;
  } ;

class FAR ExtRange {
 public :
  int i1,i2;        // Punkte der Linie, die untersucht wird
                    // (Koennen auch zusammen fallen)
  tag_ffpt p1,p2;   // Vektoren, zur Untersuchung
  tag_ffpt pcross;  // Schnittpunkt der obigen Vektoren
  ExtRange FAR *Next;

  LPVOID operator new (size_t size);
  void operator delete (LPVOID obj);

  ExtRange () { }
  ~ExtRange () { }

  BOOL IsDeadEnd (int i,int ip,int in);
  void GetSymmetrie (int i,int ip,int in,tag_ffpt FAR &res,double lfact,int FAR &state);
  void GetDeadEndSide (int i,int ip,tag_ffpt FAR &r1);
  void GetDeadEnd (int i,int ip,tag_ffpt FAR &r1,tag_ffpt FAR &r2,int FAR &state);

  void Cross (tag_ffpt FAR *p11,tag_ffpt FAR *p12,tag_ffpt FAR *p21,tag_ffpt FAR *p22,double FAR &res);
  void Cross (tag_ffpt FAR *p11,tag_ffpt FAR *p12,tag_ffpt FAR *p21,tag_ffpt FAR *p22,tag_ffpt FAR *res);
  void ProPt (fpt FAR *p,fpt FAR *p1,fpt FAR *p2,double FAR &t);
  BOOL TestRight (fpt FAR *p,tag_ffpt FAR *p1,tag_ffpt FAR *p2);
  LPCPT NextLine (LPCPT c,int FAR &state);

  BOOL Test (fpt FAR *p);
  void Interpolate (fpt FAR *p,fpt FAR *v);
  };

class FAR Voronoi {
 public :
  fpt FAR *pts;                 // Originalpunkte
  int AnzPts;                   // Anzahl Punkte, die zu untersuchen sind
  int AnzOrgPts;

  fpt FAR *vects;               // Wachstumsvektoren
  DLLExport void _export WINAPI SetVects(fpt FAR *v,int Anz);   // Setzen der Vektoren

  LONG trmemSize;                // Speicher fuer die Dreiecksliste
  GLOBALHANDLE hGTriangMem ;
  LPINT FAR *TriangsfromPt;
  LPINT FAR *TriangsfromSection;
  void PushTriangToSection (int tr,int xs,int ys);
  void BuildSectionList ();

  int AnzTriangs;               // Dreiecksliste
  Triang FAR *lpTriangs;
  void EnlargeTriangMem ();
  BOOL IsTriangSet (int i1,int i2,int i3);
  void PushTriangToPt (int trnum,int pt);
  void PushTriang (int i1,int i2,int i3);

  LPINT pind;                   // Indizess zum Umsortieren der Punkte...
  LPINT rvpind;                 // Umkehrung dieses Wertes
  void GetRevInd ();
  void GetRevInd (int i);
  void QuickSort (int Low,int High);
  BOOL IsToEleminate (int i,int j);
  void Eleminate (int i);
  void EleminateSingular ();
  int SearchConvexClockwise(int ind,int tind,BOOL FAR &ptOnLine);
                                // pt[pind[res]] ist der naechste Punkt auf
                                // der Konvexen Huelle (im Uhrzeigersinn, relativ
                                // zum Punkt pt[pind[ind]]

  int l0,l1;                      // Informationen zur gerade untersuchten
  double dxl,dyl;                 // Linie
  double xmin,xmax,ymin,ymax;     // Bereich der gesuchten Loesung
  double xsw,ysw;                 // xmin,xsw bzw. y... wird fuer
                                  // Dreieckssuche benoetigt

  void SetActiveLine (int i0,int i1);  // Linie aktiv setzen

  BOOL TestPtRight (int i,int i0,int i1);
  BOOL TestPtRightOnLine (int i,int i0,int i1);
  BOOL TestPtOnLine (int i,int i0,int i1);
  BOOL TestPtRightOrg (int i);
  BOOL TestPtRightOrgPositive (int i);
  BOOL TestPtRight (int i);     // Untersuchung, ob Punkt recht von
                                // der aktive Linie ist

  double xsbeg,xswidth,         // Segmente
         xsend;
  LPINT segstart ;              // Indizess der einzelnen Regionen
  void SetSegStart ();
  void GetBorders (double c);   // Untersuchen der Region, die fuer eine
                                // Loesung in Frage kommt
  int GetSegInd (double x);
  void LineCross (int i,double FAR &abst,double FAR &c); // Untersuchung des Dreieckes l0,l1,i
  int SearchTriangle ();        // Suchen, obs schon ein gewuenschtes
                                // Dreick gibt
  int FindInd (int j);          // Umsetzung Orginalindex zu Index in pind

  int TriangBuffer[MAXTRIANGS];
  int TriangBufferCount;
  void PushToTB (int t);
  int lstart;
  BOOL InTriangBuffer(int i);
  int NextLine ();              // Suchen des naechsten Dreieckes
  int NextStartLine (int start);

  // Hauptprogramm
  DLLExport void _export WINAPI Analyse ();
  DLLExport void _export WINAPI Paint (HDC hDC,tr2 FAR *sc);
  DLLExport void _export WINAPI PaintVect (HDC hDC,fpt FAR *p,fpt FAR *v);
  DLLExport void _export WINAPI PaintAllVects (HDC hDC);
  DLLExport void _export WINAPI PaintConvexList (HDC hDC);

  /*----- Konvexe Liste ------*/
  LPCPT clist ;
  LPCPT AtomicConvex (int min,int max);
  LPCPT UnionConvex (LPCPT c1,LPCPT c2);
  LPCPT GetConvexList (int min,int max);
  void CompleteConvex (LPCPT start);

  /*----- Interpolationsarbeiten --------*/
  void StartCalculations ();
  void EndCalculations ();
  void ChgTriang (Triang FAR *t1,Triang FAR *t2);
  DLLExport void _export WINAPI PrepareTriangs ();
  LPTRIANG SearchTriang (fpt FAR *p);
  DLLExport void _export WINAPI Interpolate (fpt FAR *p,fpt FAR *v);
  ExtRange FAR *GetExtRange ();
  ExtRange FAR *SearchExtRange (fpt FAR *p);
  ExtRange FAR *exr;

  /*----- Konstruktor - Destruktor ------*/
  DLLExport _export WINAPI Voronoi (fpt FAR *p,int Anz);
  DLLExport _export WINAPI ~Voronoi ();
  DLLExport void _export WINAPI RemoveAnalyseMem ();

  /*----- Speicherverwaltung ------*/
  DLLExport LPVOID _export WINAPI operator new (size_t size);
  DLLExport void _export WINAPI operator delete (LPVOID obj);
  };

#pragma pack(1)
struct FAR uGetVGrid_param {
  WORD parSize;
  Voronoi FAR *v;
  fpt     FAR *pts;
  BOOL    FAR *lpdone;
  fpt     FAR *vects;
  WORD    anz;
#ifdef CB_SELECTIONNAME
  DBRecord FAR *rrec;
#else
  LPVOID   rrec;
#endif
  DWORD   res;
  DWORD   pt[1];
  int AnzPts()
    { return (parSize - sizeof(*this)) / sizeof(DWORD) + 1; }
  };
#pragma pack()

#define VORONOI_INCLUDED

