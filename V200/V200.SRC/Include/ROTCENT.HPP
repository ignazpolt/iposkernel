// $Header:   P:/marille/clinicum/include/rev/rotcent.hpv   1.7   11 Sep 1997 19:00:12   HANNES  $
// $Log:   P:/marille/clinicum/include/rev/rotcent.hpv  $
// 
//    Rev 1.7   11 Sep 1997 19:00:12   HANNES
// Prototyp der Mousefunktionen
// 
//    Rev 1.6   18 Aug 1997 18:01:50   Martin
// VTO Formular-faehig
// 
//    Rev 1.5   10 Apr 1997 11:13:54   Martin
// 32-bit-isiert
// 
//    Rev 1.4   24 Mar 1996 12:15:50   HANNES
// UmStellung auf mehrseitige cFields
// 
//    Rev 1.3   02 Feb 1996 11:00:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   20 Mar 1995 12:16:44   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.1   24 Jun 1994 19:18:32   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   03 Mar 1993 15:44:28   MARTIN
// Initial revision.
//


#pragma pack(1)
struct Vto_DefRotCent_param {
  FrmObjPar_Header hd;
  // zusaetzliche Parameter Daten
  WORD ptR, ptI;        // Referenz auf den Ort
  WORD scR, scI;        // world to screen Matrix
  DWORD rcolor;          // Farbe
  };
#pragma pack()


#define RCENT_WIDTH 57
#define ROT_LEVER_LEN 1134

class FAR RotCentObj : public FrmObject {
 public:
  Vto_DefRotCent_param FAR *Par() { return (Vto_DefRotCent_param FAR *)ScriptParam; }
  LONG color;
  int px, py;     // aktuelle Koordinaten
  ftr2 wtos;      // world to screen Matrix
  DLLExport _export WINAPI RotCentObj(LPVOID p, mdiChild *c);
  virtual DLLExport void _export WINAPI GetMinMax();
  virtual DLLExport void _export WINAPI Load();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Reset(BOOL);
  virtual DLLExport void _export WINAPI Paint(PaintContext *, int);
  virtual DLLExport void _export WINAPI PaintSel(PaintContext *, int);
  virtual DLLExport void _export WINAPI PaintTrans(PaintContext *, int, tr2 FAR *);

  virtual DLLExport BOOL _export WINAPI OnLButtonDblClk(WPARAM wP, int x, int y, int Seite);  // Rotationszentrum setzen
  };

