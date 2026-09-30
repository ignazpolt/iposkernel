///////////////////////////////////////////////////////////////////////
//
//  Darstellung von Terminobjekten
//
///////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/frmobj6.hpv   1.6   12 Sep 1997 08:12:58   Gerhold  $
//  $Log:   P:/marille/clinicum/include/rev/frmobj6.hpv  $
// 
//    Rev 1.6   12 Sep 1997 08:12:58   Gerhold
// OnL...-Funktionen WORD -> WPARAM
// 
//    Rev 1.5   22 Apr 1997 12:07:56   Hannes
// Korrektur des Clippings der einzelnen Felder
// 
//    Rev 1.4   17 Dec 1996 19:46:14   HANNES
// 
//    Rev 1.3   24 Mar 1996 12:15:48   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.2   02 Feb 1996 10:59:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   26 Jul 1995 14:46:38   HANNES
// SetProcectCallBack
// 
//    Rev 1.0   20 Mar 1995 12:17:04   HANNES
// Initial revision.

// Definition der Parameter der Einzelnen Objekte
#pragma pack(1)
struct FAR prText {
  DWORD xoffs;
  DWORD yoffs;
  DWORD Text;
  DWORD with;
  DWORD AnzLines;
  DWORD Format;
  };
struct FAR ProjectPoint_param {
  FrmObjPar_Header hd;
  DWORD ptorg;
  DWORD xwith;
  DWORD yheight;
  DWORD triangwith;
  DWORD callBackProc;
  DWORD inactPen;
  DWORD inactBrush;
  DWORD actPen;
  DWORD actBrush;
  DWORD doActivate;
  DWORD ymin,ymax;
  prText t[1];
  int AnzTexts ()
    {
    return (hd.par_Size - (sizeof(*this) - sizeof(t[0]))) / sizeof(t[0]);
    }
  };
#pragma pack()

#define MAX_FLDS  10
DLLExport void _export WINAPI SetProjectCallBack(DWORD proc,DWORD x,DWORD y);

class FAR ProjectPoint : public FrmObject {
 public :
  POINT pt[4];
  int AnzPoints;    // 3 ... Dreick, 4 ... Rechteck
  cField FAR *flds[MAX_FLDS];
  int AnzFields;
  DWORD inactivePenColor;
  DWORD inactiveBrushColor;
  DWORD activePenColor;
  DWORD activeBrushColor;
  BOOL doActivate;
  int xMoveStart,yMoveStart,dxMove,dyMove;
  DWORD tMoveStart;
  BOOL isMoveing;
  void DrawMoving (PaintContext *pc);

  cField FAR *GetField (prText FAR *p,int x0,int y0,int ymin,int ymax);

  ProjectPoint_param FAR *Par()
    { return (ProjectPoint_param FAR *) ScriptParam ; }
  DLLExport _export WINAPI ProjectPoint (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI Load ();             // Laden der Daten
  virtual DLLExport void _export WINAPI Update ();           // Irgenwelche Daten haben sich

  virtual DLLExport void _export WINAPI SetConnection();           // Aufsetzen der Verbindung
  virtual DLLExport void _export WINAPI Reset(BOOL);               // Verbindung zur Datenbank
  virtual DLLExport void _export WINAPI Paint (PaintContext *, int Seite);    // Zeichnen
  virtual DLLExport void _export WINAPI Reformat (BOOL forPrinter = FALSE); // Neu Formatieren
  virtual DLLExport void _export WINAPI GetMinMax ();              // Berechnen des rcLogRects
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
 private:
  virtual DLLExport void _export WINAPI SetActive (int Seite, BOOL);          // Objekt aktivieren setzen
  virtual DLLExport void _export WINAPI SetInActive (int Seite);            // Objekt deaktivieren
 public:
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);   // Bearbeiten der Mousenachrichten
  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk (WPARAM,int,int,int); // -..-

  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);          // Bearbeiten der Tastaturnachr.

  virtual DLLExport void _export WINAPI OnMapChange (double,int,int,int,int,int);
  virtual DLLExport void _export WINAPI StartExternPaint ();
  virtual DLLExport void _export WINAPI EndExternPaint ();
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);
  };
