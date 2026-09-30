///////////////////////////////////////////////////////////////////////////
//
//      Funktionen zur Handhabung der TIFF-Files
//
//      Implementiert in tiffimg.dll
//
///////////////////////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/include/rev/image.hpv   1.14   17 Aug 1999 11:16:26   Martin  $
// $Log:   P:/marille/clinicum/include/rev/image.hpv  $
// 
//    Rev 1.14   17 Aug 1999 11:16:26   Martin
// Print raus
// 
//    Rev 1.13   03 Mar 1998 20:06:38   Martin
// True Color
// 
//    Rev 1.12   15 Sep 1997 20:58:40   Hannes
// Bilder mit Blobs
// 
//    Rev 1.11   14 Jul 1997 12:43:56   Martin
// FrmgetImgInfo, FrmLoad/SaveDIB
// 
//    Rev 1.10   25 Apr 1997 12:30:50   Martin
// Bildkomrimierung
// 
//    Rev 1.9   04 Feb 1996 18:36:54   HANNES
// 
//    Rev 1.8   04 Feb 1996 17:35:40   HANNES
// 
//    Rev 1.7   02 Feb 1996 10:59:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.6   14 Aug 1995 08:22:24   HANNES
// CreateGrayPalette erweitert
// 
//    Rev 1.5   02 Mar 1995 15:38:42   HANNES
// 
//    Rev 1.4   15 Dec 1994 22:14:26   HANNES
// 
//    Rev 1.3   09 Dec 1994 16:02:56   GERHOLD
// viele Deklarationen mit _export erweitert!
// 
//    Rev 1.2   15 Nov 1994 12:12:24   MARTIN
// PutImage geaendert
// 
//    Rev 1.1   17 Oct 1994 15:07:46   HANNES
// Funktionen im Zusammenhang mit SetContrast
// 
//    Rev 1.0   24 Jun 1994 17:01:46   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.27   13 Apr 1994 20:47:18   MARTIN
// einiges aus mimage.cpp jetzt in image.hpp
// 
//    Rev 1.26   10 Mar 1994 11:22:06   MARTIN
// Weichteil in Bild malen
// 
//    Rev 1.25   02 Mar 1994 20:58:08   MARTIN
// farbige Bilder
// 
//    Rev 1.24   09 Feb 1994 19:12:10   MARTIN
// Lampstate
// 
//    Rev 1.23   07 Feb 1994 15:40:38   HANNES
// 
//    Rev 1.22   07 Feb 1994 14:56:16   HANNES
// new,delete auf FAR PASCAL umgeaendert
// 
//    Rev 1.21   04 Feb 1994 16:47:00   MARTIN
// TWAIN sauberer
// 
//    Rev 1.20   07 Jan 1994 12:14:02   HANNES
// Waitwin in die DLL verlegt
// 
//    Rev 1.19   29 Nov 1993 09:01:00   MARTIN
// Eleminieren des DIB - Managers
// 
//    Rev 1.18   08 Oct 1993 14:29:10   MARTIN
// RemoveDIBListElem
// 
//    Rev 1.17   06 Oct 1993 09:47:02   MARTIN
// Bilder verschiedener Art, GetFullDIBName exportiert
// 
//    Rev 1.16   05 Sep 1993 22:20:02   HANNES
// Alterscheiss
// 
//    Rev 1.15   25 Aug 1993 15:57:46   MARTIN
// Prototyp von SetDIB
// 
//    Rev 1.14   23 Aug 1993 18:46:02   MARTIN
// Image-Umstellung (Native-Mode, DIBs)
// 
//    Rev 1.13   29 Jul 1993 18:35:06   MARTIN
// jetzt wieder mit LocalContrast
// 
//    Rev 1.12   29 Jul 1993 18:21:38   MARTIN
// wegen cvpack-fatal error nochmal ohne LocalContrast
// 
//    Rev 1.11   29 Jul 1993 17:44:36   MARTIN
// LocalContrast
// 
//    Rev 1.10   28 Jul 1993 20:59:58   MARTIN
// nocheinmal Prototyp von OnPaletteChanged
// 
//    Rev 1.9   28 Jul 1993 13:13:58   MARTIN
// Prototyp von OnPaletteChanged
// 
//    Rev 1.8   10 Jun 1993 18:48:32   HANNES
// MYINI
// 
//    Rev 1.7   17 Mar 1993 18:05:48   HANNES
// Verbesserungen..
// 
//    Rev 1.6   20 Feb 1993 18:28:28   HANNES
// rcDIBVisible als public umgestellt
// 
//    Rev 1.5   29 Jan 1993 10:21:22   HANNES
// Neuer Identifier: SCSTART_FILE
// 
//    Rev 1.4   11 Dec 1992 13:45:30   HANNES
// Funktionsprototyp fur GetImgStatistic
// 
//    Rev 1.3   11 Dec 1992 13:37:24   HANNES
// Statistik eingefuehrt
// 
//    Rev 1.2   10 Dec 1992 13:32:20   HANNES
// Returnwerte der Meldung WMU_SCANSTART definiert
// 
//    Rev 1.1   07 Dec 1992 14:22:26   HANNES
// Neue Methoden fuer mImage: RotDIB,InitializeNewTiff,RotateDIB,WriteDIB
// 
//    Rev 1.0   02 Dec 1992 15:58:44   HANNES
// Initial revision.
//


#ifdef MIMAGE_CLASS

inline LONG ByteWidth (LONG w, WORD BitCount)
  { return (((w * (DWORD)BitCount) + 31) & ~31) >> 3; }
inline LONG ByteWidthNoPad (LONG w, WORD BitCount)
  { return ((w * (DWORD)BitCount) + 7) >> 3; }
// LONG ByteWidth (LONG w)
//   { return ((w % 4) == 0) ? w : ((w / 4 + 1) * 4) ; }
inline int DPItoMRes (LONG r)
  { return int (double (r) * 39.95) ; }


// Definitionen fuer die Berechnung der Palette eines Farbbildes
#define RBITS 5
#define GBITS 5
#define BBITS 4
#define RLOWPART(x) ((x) >> 2)
#define GLOWPART(x) ((x) >> 2)
#define BLOWPART(x) (x)
#define TOTALCOLORS (1 << (RBITS + GBITS + BBITS))
inline BYTE RPART(unsigned index)
  {
  unsigned rp = ((index) >> (GBITS + BBITS));
  return (rp << (8 - RBITS)) | RLOWPART(rp);
  }
inline BYTE GPART(unsigned index)
  {
  unsigned gp = (((index) >> BBITS) & (~((unsigned)0xFFFF << GBITS)));
  return (gp << (8 - GBITS)) | GLOWPART(gp);
  }
inline BYTE BPART(unsigned index)
  {
  unsigned bp = ((index) & (~((unsigned)0xFFFF << BBITS)));
  return (bp << (8 - BBITS)) | BLOWPART(bp);
  }
inline unsigned RGBIND(BYTE r, BYTE g, BYTE b) 
  {
  return ((((((r) >> (8 - RBITS)) << GBITS) | ((g) >> (8 - GBITS))) << BBITS) | ((b) >> (8 - BBITS)));
  }

DLLExport WORD _export WINAPI DibNumColors (VOID FAR *pv);
#endif

/*--------------------------------------------------------------*/
/*              Klasse mImage:                                  */
/*      Aus Kompitibilitaetsgruenden wird die Klasse gleich     */
/*      wie die Klasse des Imageman uebernommen                 */
/*--------------------------------------------------------------*/
struct Filter {
  int a[3][3] ;
  int fct;
  };

struct SCALEIMAGEINFO {
  BOOL rotDone;
  HANDLE hPal;
  RECT LogRect;
  };
typedef SCALEIMAGEINFO FAR *LPSCALEIMAGEINFO;

//
// Klasse PartBitmap:
// Lesen eines Teilbitmaps aus dem grossen Bild, Umwandeln in die fuer
// den Bildschirm optimale Form
///////////////////////////////////////////////////////////////////////
struct SCBITMAP {
  int xo,yo;            // xview = (xworld - xo) * num / denum + xv;
  int xv,yv;            // (reine Integer - Operationen)
  int num;
  int denum;
  };
typedef SCBITMAP FAR *LPSCBITMAP;

inline int xview(int xworld,LPSCBITMAP sc)
  { return int (LONG(xworld - sc->xo) * LONG(sc->num) / LONG(sc->denum))
                + sc->xv ; }
inline int yview(int yworld,LPSCBITMAP sc)
  { return int (LONG(yworld - sc->yo) * LONG(sc->num) / LONG(sc->denum))
                + sc->yv ; }
inline int xworld(int xview,LPSCBITMAP sc)
  { return int (LONG(xview - sc->xv) * LONG(sc->denum) / LONG(sc->num))
                + sc->xo; }
inline int yworld(int yview,LPSCBITMAP sc)
  { return int (LONG(yview - sc->yv) * LONG(sc->denum) / LONG(sc->num))
                + sc->yo; }

class FAR farObj {
 public :
  DLLExport void FAR * _export WINAPI operator new (size_t);
  DLLExport void _export WINAPI operator delete (void FAR *);
  };

GLOBALHANDLE GetTinyDIB (char huge *bits,int left,int top,int width,int height,LONG orgwidth,WORD BitCount);
class FAR PartBitmap : public farObj {
 public :
  HBITMAP hBitmap;      // Bitmap mit den Daten (voll fuer den Bildschirm
                        // aufbereitet
  RECT rcDest;          // Rechteck im Zeichenfenster des Bitmaps
                        // (ungeklippt)
  RECT rcSource;        // zu lesendes Rechteck im DIB
  POINT ptleftupper;    // Linke obere Position relativ zu rcDest des
                        // Bitmaps 
  int width,height;     // Groesse des Bitmaps
  PartBitmap (void);
  virtual ~PartBitmap ();

  void SetWndRect (LPRECT lprc) 
    { lmemcpy (&rcDest,lprc,sizeof(RECT)); }
  void SetDIBRect (LPRECT lprc) 
    { lmemcpy (&rcSource,lprc,sizeof(RECT)); }
  void GetBitmap (HDC hdc,LPRECT lprcView,LPRECT lprcDIB,char huge * lpBits,LPBITMAPINFO lpbi,HPALETTE hDibPal);
  void Move (int dx,int dy);
  void Paint (HDC hDC,HDC hmemDC);
  };

#define MAXBITMAPS      36

class FAR BitmapCollection : public farObj {
 private :
  int VertDim,HorDim;           // Anzahl der Teilbitmaps
  int xbmplen,ybmplen;
  int xdiblen,ydiblen;
  PartBitmap FAR *bmps[MAXBITMAPS];
  RECT rcWnd;                   // Ausgabefenster
  RECT rcDIB;                   // DIB in den Ausgabefenster Koordinaten
  HPALETTE hDibPal;             // zu verwendende Palette
 public :
  RECT rcDIBvisible;            // Darzustellender Bereich des DIB
  BitmapCollection (HPALETTE hPal,int vd = 6,int hd = 6) ;
  ~BitmapCollection ();
  void SetWndRect    (LPRECT lprcWnd)
    { lmemcpy (&rcWnd,lprcWnd,sizeof(RECT)); }
  void SetDIBRect    (LPRECT lprcDIB)
    { lmemcpy (&rcDIB,lprcDIB,sizeof(RECT)); }
  void SetVisibleDIBRect (LPRECT lprcDIBvisible)
    { lmemcpy (&rcDIBvisible,lprcDIBvisible,sizeof(RECT)); }
  void IniParts           (void);
  void Divide             (int,int,int FAR *,int FAR *,int);
  void SetBitmapRects     (void);
  void GetBitmaps (HDC hdc,LPRECT lprcView,LPRECT lprcDIB,char huge *lpbits,LPBITMAPINFO lpbi);
  void Prepare (HDC hdc,LPRECT lprcWnd,LPRECT lprcDIB,LPRECT lprcfullDIB,LPRECT lprcDIBvisible,char huge *lpbits,LPBITMAPINFO lpbi);
  void Paint (HDC hDC);
  void CheckScroll (HDC hdc,LPRECT lprcWnd,LPRECT lprcDIB,LPRECT lprcfullDIB,LPRECT lprcDIBvisible,char huge *lpbits,LPBITMAPINFO lpbi);
  void ScrollLeft (int dx,HDC hdc,LPRECT lprcWnd,LPRECT lprcDIB,LPRECT lprcfullDIB,LPRECT lprcDIBvisible,char huge *lpbits,LPBITMAPINFO lpbi);
  void ScrollRight (int dx,HDC hdc,LPRECT lprcWnd,LPRECT lprcDIB,LPRECT lprcfullDIB,LPRECT lprcDIBvisible,char huge *lpbits,LPBITMAPINFO lpbi);
  void ScrollUp (int dy,HDC hdc,LPRECT lprcWnd,LPRECT lprcDIB,LPRECT lprcfullDIB,LPRECT lprcDIBvisible,char huge *lpbits,LPBITMAPINFO lpbi);
  void ScrollDown (int dy,HDC hdc,LPRECT lprcWnd,LPRECT lprcDIB,LPRECT lprcfullDIB,LPRECT lprcDIBvisible,char huge *lpbits,LPBITMAPINFO lpbi);

  friend class mImage ;
  };

class FAR mImage : public farObj {
 private :
  int DivFact;
  RECT LogRect;
 protected :
  char fileName[128];
  BitmapCollection FAR *bmc;
 public :
  void SetDivFact (int fact) { DivFact = fact ; }

  DLLExport _export WINAPI mImage ();
  GLOBALHANDLE hBMHeader;
  GLOBALHANDLE hDIB;
  GLOBALHANDLE hwholeDIB;
  GLOBALHANDLE hColorHisto;
  HPALETTE hDibPal;
  BOOL IsGray;

  DLLExport _export WINAPI ~mImage() ;

  DLLExport void _export WINAPI SetDIB (GLOBALHANDLE newDIB, LPSTR FileName = NULL);
  DLLExport void         _export WINAPI GetDIBRect     (LPRECT);
  DLLExport GLOBALHANDLE _export WINAPI ReadPart       (GLOBALHANDLE,GLOBALHANDLE,int,int,int,int);
  DLLExport void         _export WINAPI ResetBMPs      ();
  void         WINAPI WriteDIB       ();    // DIB wieder rausschreiben
  void         WINAPI RotDIB         ();    // DIB um 270 Grad drehen
  DLLExport void _export WINAPI RotatePicture  ();

  DLLExport UINT _export WINAPI OnPaletteChanged(HWND hWnd, BOOL ontop);

  DLLExport void _export WINAPI Paint     (HDC hDC,LPRECT rcWnd,LPRECT rcLogWnd,LPRECT rcDIB,BOOL doPrint = FALSE);
  DLLExport void _export WINAPI MapChange (HDC hDC,LPRECT rcWnd,LPRECT rcLogWnd,LPRECT rcDIB);

  DLLExport void _export WINAPI GetHisto  (DWORD FAR *,LPSTR);
  DLLExport void _export WINAPI lutTrans  (BYTE FAR *,LPSTR);
  DLLExport void _export WINAPI linFlt    (Filter FAR *,LPSTR);
  DLLExport void _export WINAPI MedianFlt (LPSTR);
  DLLExport void _export WINAPI SobelFlt  (LPSTR);
  DLLExport void _export WINAPI LocalContrast (LPSTR);
  void SetLogRect(LPRECT lprc)
    { CopyRect (&LogRect,lprc); }

  DLLExport void _export WINAPI InitializeScale (LPSCALEIMAGEINFO,double);
  void WINAPI PaintScaledImage (HDC,LPSCALEIMAGEINFO,BOOL);

  void SplitDIB(void);        // teilt hwholeDIB in hBMHeader und hDIB auf
  void CalcColorHisto(void);  // ermittelt die Haeufigkeiten der Farben
  DLLExport void _export WINAPI AddColorHisto(GLOBALHANDLE hsumcolors); // sumcolors += eigenes Histo
  DLLExport void _export WINAPI SetPal(HPALETTE pal, GLOBALHANDLE hPalInd, BOOL doMorph);
  DLLExport void _export WINAPI WriteBMP(LPSTR FileName);
  DLLExport void _export WINAPI GetPelsPerMeter(LPLONG x, LPLONG y);
  DLLExport void _export WINAPI SetPelsPerMeter(LONG x, LONG y);
  DLLExport LONG _export WINAPI GetImgWidth(void);
  DLLExport LONG _export WINAPI GetImgHeight(void);
  DLLExport void _export WINAPI DrawContDirect(float FAR *cnt, int PtCount, DWORD color);
  DLLExport void _export WINAPI MorphImage(LPVOID FAR *EdgeList, int ymax, GLOBALHANDLE hPalInd);
  DLLExport void _export WINAPI CheckSecondDIB(BOOL);  // ev. hDIB erzeugen
  };


// Konstanten fuer IMAGEFILEHEADER.CompressMode
#define CM_UNCOMPRESSED 0
#define CM_RUNLENGTH    1
#define CM_IM_JPEG      2
#define CM_IM_GIF       3
#define CM_IM_TIF       4
#define CM_LEAD         5


#pragma pack(1)
struct IMAGEFILEHEADER {
  WORD HeaderSize;           // Offset des DIBs im File
  WORD Version;              // Version des Programmes beim Speichern
  WORD CompressMode;         // siehe Konstanten oben
  // gefolgt von beliebig vielen Eintraegen ADDLIMAGEINFO
  };

struct ADDLIMAGEINFO {
  WORD Id;                   // Typ der Zusatzinformation
  WORD Len;                  // Laenge der Info
  char data[1];              // gefolgt von Len Bytes irgendwas
  };
#pragma pack()

typedef IMAGEFILEHEADER FAR *LPIMAGEFILEHEADER;

DLLExport BOOL _export WINAPI StartScan (LPSTR source,
                                  float FAR *left,
                                  float FAR *top,
                                  float FAR *right,
                                  float FAR *bottom,
                                  float FAR *Resolution,
                                  LPWORD Orientation,
                                  LPWORD Pixeltype,
                                  LPWORD Lampstate,
                                  BOOL UserInterface);
DLLExport GLOBALHANDLE _export WINAPI RotateImage(GLOBALHANDLE hDIB);  // um 270 Grad
DLLExport GLOBALHANDLE _export WINAPI GetScannedImage();           // von TWAIN
DLLExport GLOBALHANDLE _export WINAPI GetImage(LPSTR FileName);    // von File
DLLExport GLOBALHANDLE _export WINAPI GetImage(DWORD Size,GLOBALHANDLE hGMem);    // von Blob
DLLExport GLOBALHANDLE _export WINAPI ImportImage(LPSTR FileName); // Import von File
void DLLExport WINAPI _export PutImage(HFILE fhand, GLOBALHANDLE hnewDIB,
                    LPVOID AddlInfo, int Len, WORD CompressMode);  // Bild speichern
DLLExport void _export WINAPI PutImage(GLOBALHANDLE FAR *hGres,DWORD FAR *rSize, 
        GLOBALHANDLE hnewDIB, LPVOID AddlInfo, int Len, WORD CompressMode);  // Bild auf Blob speichern
DLLExport BOOL _export WINAPI ImageExist(LPSTR FileName);          // Bild vorhanden ?
DLLExport int  _export WINAPI TI_GetVersion(void);                 // DLL - Version
DLLExport void _export WINAPI GetImageFileName(LPSTR FileName, LPVOID lpkey);
DLLExport LPSTR _export WINAPI GetFullDIBName(LPSTR FileName);
DLLExport BOOL _export WINAPI GetImageInfo(LPSTR FileName, LPBITMAPINFOHEADER lpbi,
                                           LPWORD CompressMode, LPWORD Version,
                                           LPHANDLE AddlInfo, int FAR *Len);
DLLExport BOOL _export WINAPI GetAddlInfoById(LPVOID AddlInfoBlock, int AddlInfoLen,
                                              WORD Id, LPVOID FAR *Data, LPWORD Len);

#define TIFFIMGSECTION  "Image"
#define INDEXFILE       "Indexfile"
#define INDEXFILEDEF    "imgind.btv"
#define CACHEPATH       "imgtemp"
#define CACHEPATHDEF    ".\\"
#define CACHENUM        "imgtocache"
#define CACHENUMDEF     "7"
#define IMGDEFDRIVE     "PrimaryPath"
#define IMGDEFDRIVEDEF  ".\\"
#define IMGSECDRIVE     "SecondaryPath"
#define IMGSECDRIVEDEF  "a:\\"
#define IMGDEFNAME      "PrimaryName"
#define IMGDEFNAMEDEF   "imagestr.dat"
#define COLORDEPTH      "ColorDepth"
#define COLORDEPTHDEF   "7"

extern LPSTR WINAPI GetIniName ();
#ifndef MYINI
  #define MYINI           GetIniName ()
#endif

#define  IDS_DSMNAME                    11000

#define  IDS_SCANVERSION                10020
#define  IDS_SCANMANUFACTURER           10021
#define  IDS_PRODUCTFAMILY              10022
#define  IDS_PRODUCTNAME                10023

#define E_CLOSEDSM          "Error Closing DSM.  "
#define E_CLOSEDS           "Error Closing DS.  "
#define E_USERSELECT        "Error Accessing DS.  "
#define E_SETUPMEMXFER      "Error Setting up memory transfer.  "
#define E_DISABLEDS         "Error Disabling DS.  "
#define E_ENABLEDS          "Error Enabling DS.  "
#define E_GETFIRST          "Error Getting first Data Source.  "
#define E_GETNEXT           "Error Getting Next Data Source.  "
#define E_CAPPIXELGET       "Error Getting Cap Pixel Type.  "
#define E_CAPPIXELSET       "Error Setting Cap Pixel Type.  "

DLLExport void _export WINAPI CalcDIBKoords (LPRECT rcView,LPRECT rcLog,LPRECT rcPhys);

DLLExport BOOL _export WINAPI ScanConfigure (VOID);
DLLExport VOID _export WINAPI DCInitialize (HWND);
DLLExport VOID _export WINAPI DCExit (VOID);
DLLExport BOOL _export WINAPI ProcessDCMessage(LPMSG);
DLLExport BOOL _export WINAPI GetTWAINSources (LPSTR res);

DLLExport GLOBALHANDLE _export WINAPI GetEmptyColorHisto(VOID);
DLLExport HPALETTE _export WINAPI CalcBestPalette(GLOBALHANDLE hcolhist, GLOBALHANDLE FAR *hPalInd);
DLLExport HPALETTE _export WINAPI CreateGrayPalette(HPALETTE oldPal = 0);
DLLExport void _export WINAPI SetContrast(HPALETTE hGrayPalette, HDC hDC,
                            float contrast, float brightness);

DLLExport void _export WINAPI AddEdge(LPVOID FAR *EdgeList, int ymax,
                        fpt FAR *p1, fpt FAR *p2,
                        fpt FAR *v1, fpt FAR *v2);

DLLExport GLOBALHANDLE _export WINAPI DIBToDeltaHuffman(GLOBALHANDLE hMem);
DLLExport GLOBALHANDLE _export WINAPI DeltaHuffmanToDIB(GLOBALHANDLE hMem);

