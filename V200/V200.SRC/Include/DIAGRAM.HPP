/*-------------------------------------------------------------
**
**      Diagramme
**      ---------
**
**-----------------------------------------------------------*/
// $Header:   P:/marille/clinicum/include/rev/diagram.hpv   1.2   02 Feb 1996 10:59:46   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/diagram.hpv  $
// 
//    Rev 1.2   02 Feb 1996 10:59:46   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Mar 1995 12:16:18   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.0   24 Jun 1994 17:01:12   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   23 Feb 1994 18:04:12   HANNES
// Abspeichern der Position der Gauss - Kurve
// 
//    Rev 1.0   02 Dec 1992 15:55:36   HANNES
// Initial revision.

// Mode - Variable
#define DS_XVALUES      0x00000001
#define DS_YVALUES      0x00000002
#define DS_XGRID        0x00000004
#define DS_YGRID        0x00000008
#define DS_XPARTUP      0x00000010
#define DS_XPARTDOWN    0x00000020
#define DS_YPARTRIGHT   0x00000040
#define DS_YPARTLEFT    0x00000080
#define DS_TIPRIGHT     0x00000100
#define DS_TIPLEFT      0x00000200
#define DS_TIPUP        0x00000400
#define DS_TIPDOWN      0x00000800
#define DS_XVALUP       0x00001000
#define DS_YVALRIGHT    0x00002000
#define DS_XAXIS        0x40000000
#define DS_YAXIS        0x80000000
#define DS_SCFORMAT(A)  ((DWORD (A) & 0x001F) << 14)
#define DS_LMFORMAT(A)  ((DWORD (A) & 0x001F) << 19)
#define DS_XSCALE(A)    ((DWORD (A) & 0x0003) << 24)
#define DS_YSCALE(A)    ((DWORD (A) & 0x0003) << 26)
#define DS_CTYPE(A)     ((DWORD (A) & 0x0003) << 28)

#define DS_GETSCFORMAT(A) (((A) >> 14) & 0x0000001F)
#define DS_GETLMFORMAT(A) (((A) >> 19) & 0x0000001F)
#define DS_GETXSCALE(A)   (((A) >> 24) & 0x00000003)
#define DS_GETYSCALE(A)   (((A) >> 26) & 0x00000003)
#define DS_GETCTYPE(A)    (((A) >> 28) & 0x00000003)

// moegliche Callback - Funktionen
typedef double (* LINEFUNC) (double,GLOBALHANDLE,int);
typedef void (* POINTFUNC)  (double *,double *,int,GLOBALHANDLE);
typedef void (* HISTOFUNC)  (double *,double *,double *,int,GLOBALHANDLE);
typedef void (* CURSORFUNC) (double *,double *,GLOBALHANDLE,int);

// Basisklasse der Diagramme, kann als MDI - Dokument verwendet werden
struct ValuePos {
  float val;
  };

class FAR Diagram : public mdiChild {
 public :

  // Beschreibung der Achsen
  DWORD mode;           
  void SetDiagramMode (DWORD);

  // Callbackfunktionen, die beim Zeichnen aufgerufen werden
  LINEFUNC linefunc;
  POINTFUNC pointfunc;
  HISTOFUNC histofunc;
  CURSORFUNC cursorfunc;
  void SetLineFunc (LINEFUNC);
  void SetPointFunc (POINTFUNC);
  void SetHistoFunc (HISTOFUNC);
  void SetCursorFunc (CURSORFUNC);
  GLOBALHANDLE PaintParam;              // Parameterblock (wird von Diagramm
                                        // freigegeben !!!!)
  void SetPaintParam (GLOBALHANDLE);
  
  // Labels
  WORD XLOffs,YLOffs;
  void SetLabel (char FAR *XLabel,char FAR *YLabel);
  
  // Extremwerte, Nullpunkt
  double xmin,ymin,xmax,ymax,xc,yc;
  void SetAxValues (double,double,double,double,double,double);

  // Steuerung
  BOOL Initialized;                     // Skalierungen wurden durchgefuehrt
  void InvalidateWindow (void);         // Zwingen zum Neuzeichnen ohne
                                        // Berechnung der Scalierung
  void Rescale (void);                  // Zwingen, die Skalierung neu
                                        // zu berechnen

  Diagram () : mdiChild (NULL) { }
  virtual ~Diagram () ;

  // Diverse Hilfsfunktionen
  GLOBALHANDLE hDmem;
  fRECT rWork;
  int nXVals,nYVals;
  WORD hXValPos,hYValPos;
  void SetUpWData (void);
  virtual LONG Paint(PaintContext *);
  };

// Eigenstaendige Klasse, kann als Overlapped Window verwendet werden
class sDiag : public Diagram {
 public :
  HWND Notify;          // Fenster, an das die Kommandos gesendet werden
                        // koennen
  DWORD style;
  BOOL ActivateHandling;
  WORD ListID;          // Anzeige der Knoepfchens ...
  sDiag (HWND,WORD,
           DWORD st = WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_VISIBLE,
           BOOL ah = FALSE);
  void Create (char *);         // Kreation des (OVERLAPPED) - Windows,
  virtual LONG WINAPI SpcFnc (HWND,UINT,WPARAM,LPARAM,BOOL *);
  virtual void StoreWPos (WORD wP = 0);
  virtual ~sDiag ();
  };

// Fensterfunktion zum Behandeln der Kommentarfunktion
DLLExport LONG _export FAR PASCAL sDiagWndProc (HWND,UINT,WPARAM,LPARAM);

extern int GetValues (ValuePos *,int,int,int,double,double);

