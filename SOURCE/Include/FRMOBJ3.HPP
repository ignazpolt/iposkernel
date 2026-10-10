////////////////////////////////////////////////////////////////////////
//
//  Image - Objekte  (ehemals in frmobj.hpp)
//
///////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/frmobj3.hpv   1.17   25 May 1999 18:43:28   Martin  $
//  $Log:   P:/marille/clinicum/include/rev/frmobj3.hpv  $
// 
//    Rev 1.17   25 May 1999 18:43:28   Martin
// Reduktionsfaktor (optional) bei FrmStoreImage
// 
//    Rev 1.16   14 Apr 1998 20:15:44   Martin
// DefFrmRectImage erweitert
// 
//    Rev 1.15   18 Feb 1998 10:25:56   Hannes
// LPIMGBG ... Mit Seite
// 
//    Rev 1.14   15 Sep 1997 20:58:38   Hannes
// Bilder mit Blobs
// 
//    Rev 1.13   25 Apr 1997 12:30:48   Martin
// Bildkomrimierung
// 
//    Rev 1.12   18 Mar 1997 12:38:50   Martin
// FrmScanImage: optionaler Parameter AlteVersion (flag)
// 
//    Rev 1.11   10 Jun 1996 10:15:14   GERHOLD
// pragma pack
// 
//    Rev 1.10   22 Mar 1996 12:14:54   HANNES
// Aenderungen Hannes
// 
//    Rev 1.9   02 Feb 1996 10:59:16   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   14 Aug 1995 08:22:08   HANNES
// 
//    Rev 1.7   20 Mar 1995 12:16:22   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.6   15 Nov 1994 22:48:38   MARTIN
// Scanner...
// 
//    Rev 1.5   11 Nov 1994 17:31:08   MARTIN
// FrmRectImage
// 
//    Rev 1.4   17 Oct 1994 15:07:26   HANNES
// SetContrast_par
// 
//    Rev 1.3   27 Jun 1994 10:47:32   HANNES
// Virtuelle Funktionen nicht mehr als inline
// 
//    Rev 1.2   24 Jun 1994 20:43:18   MARTIN
// 
//    Rev 1.1   24 Jun 1994 19:18:26   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   29 Apr 1994 14:42:52   MARTIN
// FrmGetImageFileName
// 
//    Rev 1.0   13 Apr 1994 20:58:20   MARTIN
// Initial revision.
// 

// Image
/////////////
#pragma pack(1)
struct Frm_DefImage {
  FrmObjPar_Header hd;
  // zus. Daten vom Script
  WORD ImgRec,ImgId;      // Image - Referenz
  WORD PtRec,PtId;        // li. oberer Punkt des Images
  WORD wRec,wId;          // Weite des Bildes
  DWORD flags;            // optional bei RectImage, analog zu trcobj.hpp
  };                      // Hoehe wird selber berechnet
#pragma pack()
typedef Frm_DefImage FAR *LPDEFIMAGE;

#pragma pack(1)
struct BestPalette_par {
  WORD par_Size;
  DWORD img[1];       // Bildobjekte
  };
#pragma pack()

#pragma pack(1)
struct FrmScanImage_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Welches Objekt soll gescannt werden
  WORD rdyRec,rdyId;          // flag: TRUE, wenn Image fertig gescannt
  DWORD source;               // Name der TWAIN Source
  DWORD left,top,right,bottom;// Scan - Koordinaten
  DWORD Resolution;           // Scanner Aufloesung
  DWORD Orientation;          // Bild drehen ? ....
  DWORD Pixeltype;            // Farbe / SW / Graustufen
  DWORD Lampstate;            // Durchleuchteinheit ein / aus
  DWORD UserInterface;        // UI ein / aus
  DWORD AlteVersion;          // flag: soll die eigene TWAIN-Anbindung
  };                          // (ohne LeadTools) aktiviert werden ?
#pragma pack()

#pragma pack(1)
struct FrmImportImage_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // in welches Objekt soll importiert werden
  WORD nameR,nameI;           // String: Filename
  DWORD fact;                 // optional: Reduktionsfaktor
  };
#pragma pack()

#pragma pack(1)
struct FrmSetImage_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // in welches Objekt soll importiert werden
  WORD ImgR,ImgI;             // DIB - Handle
  };
#pragma pack()

#pragma pack(1)
struct FrmWriteBMP_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // welches Objekt soll geschrieben werden
  WORD nameR,nameI;           // String: Filename
  };
#pragma pack()

#pragma pack(1)
struct FrmGetPixPerMeter_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Objekt
  WORD xR,xI;                 // XPelsPerMeter
  WORD yR,yI;                 // YPelsPerMeter
  };
#pragma pack()

#pragma pack(1)
struct FrmSetPixPerMeter_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Objekt
  WORD xR,xI;                 // XPelsPerMeter
  WORD yR,yI;                 // YPelsPerMeter
  };
#pragma pack()

#pragma pack(1)
struct FrmGetImgWidth_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Objekt
  WORD wR,wI;                 // Breite in Pixel
  };
#pragma pack()

#pragma pack(1)
struct FrmDrawContDirect_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Objekt
  WORD cntR,cntI;             // Kontur
  WORD colR,colI;             // Farbe
  };
#pragma pack()

#pragma pack(1)
struct FrmStoreImage_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // welches Objekt soll gespeichert werden
  WORD nameR,nameI;           // String: Imagename
  WORD keyR,keyI;             // Info zum Bilden des Filenamens
  WORD comprR,comprI;         // Index: Kompressionstyp
  struct {                    // beliebige Anzahl:
    DWORD rtype;              // Typ
    WORD R, I;                // Referenz
    } Ref[1];                 // zusaetzliche Infos zum Bild
  };
#pragma pack()

#pragma pack(1)
struct FrmGetImageFileName_par {
  WORD par_Size;
  WORD nameR,nameI;           // String: Imagename
  WORD keyR,keyI;             // Info zum Bilden des Filenamens
  };
#pragma pack()

#pragma pack(1)
struct ImgUserFlt_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Welches Objekt soll gefiltert werden ?
  DWORD rWFuncFlag;             // soll Wartefenster angezeigt werden ?
  DWORD ra00 ;
  DWORD ra01 ;
  DWORD ra02 ;
  DWORD ra10 ;
  DWORD ra11 ;
  DWORD ra12 ;
  DWORD ra20 ;
  DWORD ra21 ;
  DWORD ra22 ;
  DWORD rfact ;
  DWORD WaitWinName;
  };
#pragma pack()

#pragma pack(1)
struct ImgFixFlt_par {
  WORD par_Size;
  WORD ObjRec,ObjId;          // Welches Objekt soll gefiltert werden ?
  DWORD rWFuncFlag;             // soll Wartefenster angezeigt werden ?
  };
#pragma pack()

#pragma pack(1)
struct GetImagePhysScalePar {
  WORD parSize;
  WORD ObjRec, ObjId;
  WORD scRec, scId;
  };
#pragma pack()

#pragma pack(1)
struct CreateEdgeTable_par {
  WORD par_Size;
  DWORD EdgeTab;              // struct EdgeTable
  DWORD ImgObj;               // zu bearbeitendes Bild (fuer y-Clipping)
  };
#pragma pack()

#pragma pack(1)
struct FillInEdges_par {
  WORD par_Size;
  DWORD EdgeTab;              // struct EdgeTable
  struct {
    DWORD p1,p2;              // Koordinaten der Punkte
    DWORD v1,v2;              // zugehoerige Veraenderungsvektoren
    } Edge[1];
  };
#pragma pack()

#pragma pack(1)
struct FrmMorphImage_par {
  WORD par_Size;
  DWORD ImgObj;               // zu bearbeitendes Bild
  DWORD EdgeTab;              // struct EdgeTable
  };
#pragma pack()

#pragma pack(1)
struct FrmGetImageScaleFact_par {
  WORD par_Size;
  DWORD Obj;                  // Objekt
  DWORD sf;                   // Skalierungsfaktor
  };
#pragma pack()


// Objekt - Klassen:

#pragma pack(1)
struct ImgBackgnd {
  WORD Id;
  RECT r;
  short Seite;
  };
#pragma pack()
typedef ImgBackgnd FAR *LPIMGBG;

struct BlobDesc;
class FrmImage : public FrmObject {
 protected :
  LPDEFIMAGE Par() { return LPDEFIMAGE (ScriptParam); }
  char lastStoredFileName[64];
  GLOBALHANDLE LastStorehGMem;
 public :

  mImage FAR *img;
  fRECT ImgRect;
  DLLExport _export WINAPI FrmImage (LPVOID p,mdiChild *c);

  virtual DLLExport void _export WINAPI GetImgRect ();

  WORD rdyR, rdyI;          // zum merken der Flag-Referenz
  mdiChild *rdyC;           // Kontext fuer Flag-Referenz
  DLLExport BOOL _export WINAPI OnStartScan (LPSTR source,
                    float FAR *left,
                    float FAR *top,
                    float FAR *right,
                    float FAR *bottom,
                    float FAR *Resolution,
                    LPWORD Orientation,
                    LPWORD Pixeltype,
                    LPWORD Lampstate,
                    BOOL UserInterface,
                    WORD rdyRec,WORD rdyId,mdiChild *rdyMC);
  DLLExport void _export WINAPI OnScanReady ();
  DLLExport void _export WINAPI ImportFile (LPSTR FileName);
  DLLExport void _export WINAPI SetImage (GLOBALHANDLE hDIB);
  DLLExport void _export WINAPI WriteBMP (LPSTR FileName);
  DLLExport void _export WINAPI StoreImage (LPVOID key, DWORD fRef, LPVOID AddlInfo, int InfoSize, WORD CompressMode);
  DLLExport void _export WINAPI StoreImage (LPVOID key, BlobDesc FAR *bd, LPVOID AddlInfo, int InfoSize, WORD CompressMode);

  DLLExport void _export WINAPI SetImgBg ();
  DLLExport void _export WINAPI RemoveImgBg ();

  virtual DLLExport void _export WINAPI GetMinMax ();
  virtual DLLExport void _export WINAPI SetConnection();
  virtual DLLExport void _export WINAPI Load ();
  virtual DLLExport void _export WINAPI Update();
  virtual DLLExport void _export WINAPI Paint (PaintContext *,int);
  virtual DLLExport void _export WINAPI Reformat (BOOL forPrinter = FALSE);
  virtual DLLExport void _export WINAPI Reset (BOOL);
  virtual DLLExport void _export WINAPI OnMapChange (double,int,int,int,int,int);

  virtual DLLExport BOOL _export WINAPI ForceToBackground ();
  };

class TrcImage : public FrmImage {
 public :
  DLLExport _export WINAPI TrcImage (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI GetImgRect ();
  };

class FrmRectImage : public FrmImage {
 public :
  DLLExport _export WINAPI FrmRectImage (LPVOID p,mdiChild *c);
  virtual DLLExport void _export WINAPI GetImgRect ();
  };

#pragma pack(1)
struct PalInfo {
  HPALETTE actpal;
  GLOBALHANDLE palind;
  BOOL gray;
  BOOL doDelete;
  };
#pragma pack()
typedef PalInfo FAR *LPPALINFO;

#pragma pack(1)
struct EdgeTable {
  int ymax;
  GLOBALHANDLE hET;
  };
#pragma pack()

#pragma pack(1)
struct SetContrast_par {
  WORD par_Size;
  DWORD contrast;
  DWORD brightness;
  DWORD ref[1];  // Objekte, auf die zusaetzl. ein FIXCONNECTION gesetzt wird
  };
#pragma pack()


