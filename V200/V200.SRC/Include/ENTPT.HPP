class FAR DefEnt;
#define INPUTMODE_SEQ       0
#define INPUTMODE_CORRECT   1

#pragma pack(1)
struct DefEnt_param {
  WORD parSize;
  DefEnt FAR *obj;// Private Daten: Zeiger auf das Definitionsobjektes
  DWORD EntDef;   // Zeiger, wo die Namen hin geschrieben werden
  DWORD scdtos;		// Skalierungsmatrix, um von den Weltkoordinaten
            			// zu den den (logischen) Bildschirmkoordinaten zu 
            			// kommen
  DWORD scetod;		// Skalierungsmatirix, um von den eingegeben
            			// Koordinaten (Beim Digitizer sind dies die
            			// Digitizerkoordinaten, Bei der Mouseingabe sind dies
            			// die logischen Bildschirmkoordinaten)
  DWORD SeqInd;		// Index, der beim Aktivieren eines Punktes
            			// geschrieben werden muss (damit die Punktliste
            			// wieder richtig selektiert werden kann)
  DWORD AllNames; // Alle Namen
  DWORD modeRef;  // Zeiger auf den Eingabemodus (nur Sinnvoll bei
                  //   Imageeingabe)
  DWORD picRef;   // Referenz des Bildes, das bei der Eingabe angegeben 
                  // werden kann
  DWORD ImageRef; // Referenz auf ein Roentgenbild, das fuer intellegenteres
                  // Invalidieren verwendet werden kann
  DWORD MouseName;// Soll Name bei der Mouse angezeigt werden
  DWORD PosRef;   // Aktuelle Groesse des Fensters
  DWORD nColorOwn;
  DWORD aColorOwn;
  DWORD nColorExtern;
  DWORD aColorExtern;
  DWORD SoundFlag;// sollen Punkte ueber Lautsprecher angezeigt werden ?
  DWORD WavePath; // Pfad fuer die .wav Dateien
  };
#pragma pack()

struct FAR EntPtCnt_param;
struct SeqGr {
  SeqGr FAR *Next;
  EntPtCnt_param FAR *p;
  };

class DefEnt : public FrmFarObject {
  WORD FNr;
 public :
  DefEnt_param FAR *par;
  dllChild m;
  DLLExport _export WINAPI DefEnt (DefEnt_param FAR *p,mdiChild *x);

  ////////////////////////////////////////////////////
  //  Verwaltung der Graphik
  ////////////////////////////////////////////////////
  HWND hWnd;                  // Fenster mit der Extra - Graphik
  HMETAFILE hmf;              // Extragraphik - hoechstpersoenlich
  float ymin,ymax,xmin,xmax;  // Extremwerte der Graphik
  int x0,y0,xp,yp;            // Mittelpunkt in log. und Device Koordinaten
  float scale;
  EntPtCnt_param FAR *act;
  SeqGr FAR *Root;            // Liste aller Extra - Graphiken
  ftr2  etod,dtos;            // Eingegeben Daten in Speicherdaten
                              // Speicherdaten in Bildschirmkoordinaten
  int  InputMode;             // Siehe modeRef...
  BOOL ShowNameAtMouse;       // Anzeige des Namens bei der Mouse ?
  BOOL SayName;               // Ansage des naechsten Eingabepunktes ?
  DWORD WavePath;             // Referenz des Pfades fuer .wav Dateien
  DLLExport void _export WINAPI GetScaleMat ();
  DLLExport void _export WINAPI SetName ();

  FrmObject FAR *ImageObject; // Dem sein rcLogRect wird fuer
                              // intellegenteres Invalidieren herangezoge

  DLLExport void _export WINAPI ShowEnterMark (PaintContext *pc,int x,int y);
  DLLExport void _export WINAPI ShowEnterCont (PaintContext *pc,int FAR *cnts);
  DLLExport void _export WINAPI InvalidateEnterMark (PaintContext *pc,int x,int y);
  DLLExport void _export WINAPI InvalidateEnterCont (PaintContext *pc,int FAR *cnts);
  DLLExport void _export WINAPI ShowActMark (PaintContext *pc,int x,int y);
  DLLExport void _export WINAPI ShowActCont (PaintContext *pc,int FAR *cnts);
  DLLExport void _export WINAPI InvalidateActMark (PaintContext *pc,int x,int y);
  DLLExport void _export WINAPI InvalidateActCont (PaintContext *pc,int FAR *cnts);
  DLLExport void _export WINAPI ShowNormal   (PaintContext *pc,SeqGr FAR *s);
  DLLExport void _export WINAPI ShowSelected (PaintContext *pc,SeqGr FAR *s);
  DLLExport void _export WINAPI PaintSeq (PaintContext *pc);
  DLLExport void _export WINAPI Invalidate (EntPtCnt_param FAR *p);

  DLLExport void _export WINAPI WriteWndPos ();
  DLLExport void _export WINAPI CalcScale ();
  DLLExport void _export WINAPI Create ();

  DLLExport void _export WINAPI PaintExtraGr(EntPtCnt_param FAR *par,BOOL state);
  DLLExport void _export WINAPI InsertGr(EntPtCnt_param FAR *par,BOOL doInvalidate,BOOL showWnd);
  DLLExport void _export WINAPI RemoveGr (EntPtCnt_param FAR *par,BOOL doInvalidate);

  DLLExport int _export WINAPI GetSeqNum (EntPtCnt_param FAR *par);
  DLLExport void _export WINAPI ActivateName (EntPtCnt_param FAR *par);
  DLLExport void _export WINAPI DeActivateName ();
  DLLExport void _export WINAPI WriteNameList ();
#ifdef UEBERLEGT
  DLLExport void _export WINAPI InsertName (EntPtCnt_param FAR *par);
  DLLExport void _export WINAPI RemoveName (EntPtCnt_param FAR *par);
#endif

  DLLExport FrmObject FAR * _export WINAPI GetInputObj (int i);
  DLLExport void _export WINAPI OnIndChange ();
  };

typedef DefEnt FAR *LPDEFENT;

#define INPUT_NOTDEFINED	0
#define INPUT_DIGITIZER		1
#define INPUT_SCANNER		  2

#define ET_NONE     0
#define ET_POINT    1
#define ET_CONT     2
class FAR InputObj;

#pragma pack(1)
struct FAR EntPtCnt_param {
  WORD parSize;
  LPVOID objlist; // Private Daten

  DWORD ObjId;     // Objekt des Eingabe - Wertes
  DWORD Cntpt;		 // Punkt / Kontur Variable
  DWORD SetOnStore;  // Flag, das beim speichern gesetzt werden muss
  LONG  KontextNr; // Index in der Hilfe
  DWORD EntDef;    // Zeiger auf das Definitionsobjekt

  DWORD mode;		  // Art der Eingabe (siehe obiges define)
  DWORD NameRef;  // Name des Eingabe - Punktes (muss nicht angegeben
			            // sein, kann auch aus der Programm - Datei ermittelt
			            // werden - ist aber ineffizienter.)
  union {
    struct {
      DWORD X,Y;
      } pt;            // Graphik - Definition fuer den Digitizer (Punkt)
    DWORD cntdef[1];   // -''- (Kontur)
    } dgrDef;

  DLLExport DWORD FAR * _export WINAPI SoundNames(int Type,dllChild m); // Array von Stringreferenzen
  DLLExport int _export WINAPI SoundCount(int Type,dllChild m);        // Anzahl der angegebenen Strings

  DLLExport LPSTR _export WINAPI Name (dllChild m);
  };
#pragma pack()

class FAR InputObj : public FrmObject {
 public :
  EntPtCnt_param FAR *Par() { return (EntPtCnt_param FAR *) ScriptParam ; }
  DLLExport _export WINAPI InputObj (LPVOID p,mdiChild *c);

  LPDEFENT Def;
  BOOL OwnData;
  int  mode;
  HCURSOR nCursor,cCursor,iCursor;
  fRECT oldRect;

  BOOL IsDigitizer ()
    { return (mode == INPUT_DIGITIZER) ; }
  BOOL IsImage ()
    { return (mode == INPUT_SCANNER) ; }

  DLLExport void _export WINAPI MyLoad (BOOL doInsert);
  DLLExport void _export WINAPI ShowHelp ();

  // Allgemeine FrmObj - Funktionen
  virtual DLLExport BOOL _export WINAPI IsToActivate ();
  virtual DLLExport void _export WINAPI SetActive (int,BOOL); 
  virtual DLLExport void _export WINAPI SetInActive (int);
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Update ();
  virtual DLLExport BOOL _export WINAPI IsInputObj ();

  // Spezielle Eingabe Funktionen
  virtual DLLExport int  _export WINAPI GetType ();
  virtual DLLExport void _export WINAPI ArmHardware (BOOL state);
  virtual DLLExport void _export WINAPI SetData (LPVOID data);   // Speichern der internen Daten
  virtual DLLExport void _export WINAPI ResetData ();
  virtual DLLExport void _export WINAPI DelMyData ();

  virtual DLLExport void _export WINAPI OnDigitized(UINT msg,GLOBALHANDLE hGmem);

  DLLExport void _export WINAPI InflateMinMax (LPRECT rcLogRect);
  DLLExport int _export WINAPI TestCursor (int xc,int yc,int x,int y,HCURSOR hc);
  DLLExport BOOL _export WINAPI IsAct ();
  DLLExport void _export WINAPI PaintRect (PaintContext *pc,int x,int y);

  DLLExport void _export WINAPI SetName ();
  };

class EnterPoint : public InputObj {
 public :
  int x,y;
  DLLExport _export WINAPI EnterPoint (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI ArmHardware (BOOL state);
  virtual DLLExport int  _export WINAPI GetType ();
  virtual DLLExport void _export WINAPI SetData (LPVOID data);
  virtual DLLExport void _export WINAPI ResetData ();
  virtual DLLExport void _export WINAPI DelMyData ();

  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);    // Zeichnen
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);   // Bearbeiten der Mousenachrichten
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);     // -"-
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);

  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  };

class EnterCont : public InputObj {
 public :
  WORD PtCount;         // Anzahl Punkte
  LogPt FAR *cnt;       // Kontur in logischen Koordinaten
  LogPt FAR *zcnt;      // Zwischen - Kontur
  DLLExport _export WINAPI EnterCont (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI ArmHardware (BOOL state);
  virtual DLLExport int  _export WINAPI GetType ();
  virtual DLLExport void _export WINAPI SetData (LPVOID data);
  virtual DLLExport void _export WINAPI ResetData ();
  virtual DLLExport void _export WINAPI DelMyData ();

  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);    // Zeichnen
  DLLExport void _export WINAPI GetZCont ();
  DLLExport void _export WINAPI EnlargeCont (int id);
  virtual DLLExport BOOL _export WINAPI OnLButtonDown (WPARAM,int,int,int);
  virtual DLLExport BOOL _export WINAPI OnLButtonUp (WPARAM,int,int,int);  
  virtual DLLExport int _export WINAPI OnSetCursor (int,int,int);
  virtual DLLExport BOOL _export WINAPI OnMouseMove (WPARAM,int,int,int);

  virtual DLLExport BOOL _export WINAPI OnKeyDown (WORD,int);
  };

DLLExport void _export WINAPI ShowName ();
DLLExport void _export WINAPI ClearName ();
DLLExport void _export WINAPI HideName ();
DLLExport void _export WINAPI ReadPTB (PaintContext *pc,HWND MyHandle,float scale,int xp,int yp);
DLLExport void _export WINAPI RestorePTB (PaintContext *pc);

