// $Header:   P:/marille/clinicum/include/rev/paint.hpv   1.6   05 Oct 1998 11:24:16   Gerhold  $
// $Log:   P:/marille/clinicum/include/rev/paint.hpv  $
// 
//    Rev 1.6   05 Oct 1998 11:24:16   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.5   01 Sep 1998 23:47:22   Hannes
// MyLPtoDP
// 
//    Rev 1.4   02 Feb 1996 11:00:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   27 Jun 1994 10:42:20   HANNES
// Inline Funktionen nicht mehr exportieren
// 
//    Rev 1.2   24 Jun 1994 20:07:18   MARTIN
// export ....
// 
//    Rev 1.1   24 Jun 1994 19:18:30   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.8   14 Feb 1994 19:48:50   HANNES
// No change.
// 
//    Rev 1.7   24 Sep 1993 22:44:22   HANNES
// Neuer Modus: DO_EXTDC
// 
//    Rev 1.6   12 Jul 1993 07:59:28   HANNES
// Initialize mit HDC..
// 
//    Rev 1.5   03 May 1993 15:47:20   HANNES
// Vorlaufiges Clipboard - Handlings
// 
//    Rev 1.4   02 Apr 1993 18:01:08   HANNES
// Strukturbereinigung
// 
//    Rev 1.3   24 Feb 1993 21:33:36   MARTIN
// Erweiterungen zum Erzeugen eines Memory-Kontextes
// 
//    Rev 1.2   16 Feb 1993 13:48:52   HANNES
// Verbesserte Linientypen
// 
//    Rev 1.1   14 Feb 1993 15:55:56   HANNES
// Neues Member: MapType
// 
//    Rev 1.0   02 Dec 1992 16:02:54   HANNES
// Initial revision.

#ifndef fPOINT_DEFINED
#define fPOINT_DEFINED
typedef struct FAR tagfPOINT
{
    int x;
    int y;
} fPOINT;
#endif

typedef struct FAR tagfPAINTSTRUCT
{
    HDC 	hdc;
    BOOL	fErase;
    RECT	rcPaint;
    BOOL	fRestore;
    BOOL	fIncUpdate;
    BYTE	rgbReserved[16];
} fPAINTSTRUCT;

/*------< Ausgabeobjekte >--------------*/
class FAR Line {
 public :
  fPOINT pt0,pt1;
  Line(int x0,int y0,int x1,int y1) 
    { pt0.x = x0 , pt0.y = y0 , pt1.x = x1 , pt1.y = y1 ; }
  Line(POINT p0,POINT p1)
    { pt0 = *((fPOINT *)&p0) , pt1 = *((fPOINT *)&p1) ; }
  };

class FAR Bitmap {
 public :
  HBITMAP hBitmap;
  fPOINT pt;
  int width,height;
  Bitmap(HBITMAP hb,int x0 = 0 ,int y0 = 0,int w = 0,int h = 0)
    { hBitmap = hb , pt.x = x0 , pt.y = y0 , width = w , height = h ; }
  Bitmap(HBITMAP hb,POINT p,int w = 0, int h = 0)
    { hBitmap = hb , pt = *((fPOINT *)&p) , width = w , height = h ; }
  };

class FAR PosStr {
 public :
  char *str;
  int x0,y0 ;
  DWORD fgc ;
  DWORD fgb ;
  DLLExport _export WINAPI PosStr(char *,int x,int y,DWORD c = 0xFFFFFFFF,WORD b = 0xFFFF);
  };

class FAR GrayStr {
 public :
  char *str;
  int x0,y0 ;
  WORD bgb ;
  DLLExport _export WINAPI GrayStr(char *,int x,int y,WORD b = 0xFFFF);
  };

class FAR ExtPosStr {
 public :
  char FAR *str;
  int len ;
  int x0,y0 ;
  DWORD fgc,bgc ;
  WORD Align ;
  WORD FontIdent ;
  DLLExport _export WINAPI ExtPosStr(char FAR *,int,WORD,int,int,DWORD,DWORD,WORD);
  };

#define META_FILE	0
#define META_RSC	1
#define META_DIRECT	2
class FAR MetaDesc {
 public :
  union FAR {
    char *str;
    HMETAFILE hMeta;
    } x ;
  int mode;
  MetaDesc (char *szname,int m = META_FILE) { x.str = szname, mode = m ; }
  MetaDesc (HMETAFILE m) { x.hMeta = m, mode = META_DIRECT ; }
  };

/*------< Kreation eines Stiftes >------*/
class FAR PENDATA {
 public :
  DWORD color;
  int width;
  WORD style;
  DLLExport _export WINAPI PENDATA(DWORD c,int w = 1,WORD s = PS_SOLID);
  DLLExport _export WINAPI PENDATA(WORD);
  };

/*------< Kreation eines Fonts >-----*/
#define SELECT_FONT 	0
#define ADD_TOLIST	1
#define DO_DELETE	2
#define GET_SIZE        4
#define DELETE_FONT	5
#define GET_MODE	6
#define GET_DATA	7
#define FI_BOLD         0x0001
#define FI_UNDERLINE    0x0002
#define FI_STRIKEOUT    0x0004
#define FI_ITALIC       0x0008

/*------< PaintContext >-------*/
#define DO_PAINT	0	// hDC wird durch BeginPaint erhalten
#define DO_WORK		1	// hDC wird durch GetDC erhalten
#define DO_PRINT	2	// hDC vom Drucker
#define NO_MODE   4
#define DO_MEMORY 8 // memory - hDC
#define DO_EXTERN 16
#define DO_EXTDC  32

#define TRANSLATE_NOTHING  0x0000
#define TRANSLATE_PEN      0x0001
#define TRANSLATE_BRUSH    0x0002

// Umrechnung Logigal Twips <-> mm 
inline int MMtoLT(float x) { return (int) (x * 1440.0 / 25.454) ; }
inline float LTtoMM(int x) { return (float) (double (x) * 25.454 / 1440.0) ; }

#define MAPTYPE_TEXT          0     // 1 log. Einheit = 1 Pixel
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll

class FAR PaintContext {
 public :
  HBRUSH hOldBrush ;     // Alter Brush
  HPEN   hOldPen ;       // Alter Pen
  HPEN   hPen ;		 // Neu kreierter Pen
  int x0,y0 ;		 // Ursprung des Koordinatensystems
  Printer *ActPrt;
  int xvp,yvp;
  int mode;		 // Art, wie der Device - Kontext geholt wurde
  int orientation;
  /****** Private Hilfsfunktionen *******/
  DLLExport void _export WINAPI OldAttribs(void);
  DLLExport void _export WINAPI Initialize(HWND hw);
  DLLExport void _export WINAPI Initialize(PaintContext *pc);
  HFONT  hOldFont;	 // Alter Font
  HFONT  hFont;          // Aktueller Font
  fRECT  cr ;     	 // Abmessungen der Client Area
  HWND   hWnd ;		 // Ausgabefenster
  fPAINTSTRUCT ps ;  // siehe windows.h
  HDC hDC ;              // Windows Device Context
  /****** Konstruktoren ********/
  DLLExport void _export WINAPI SetOrientation (int);
  DLLExport int _export WINAPI GetOrientation (void);
  DLLExport _export WINAPI PaintContext(HWND,WORD penident = 0xFFFF,WORD brushident = 0xFFFF,int mode = DO_PAINT);
  DLLExport _export WINAPI PaintContext(HWND,PENDATA,WORD brushident = 0xFFFF,int mode = DO_PAINT);
  DLLExport _export WINAPI PaintContext(PaintContext *pc, WORD penident = 0xFFFF, WORD brushident = 0xFFFF);
  DLLExport _export WINAPI PaintContext(Printer *);
  DLLExport _export WINAPI PaintContext(void);        // Void Construktor
  DLLExport void _export WINAPI GetContext(HWND,WORD penident = 0xFFFF,WORD brushident = 0xFFFF,int mode = DO_PAINT);
  DLLExport void _export WINAPI GetContext(HWND,PENDATA,WORD brushident = 0xFFFF,int mode = DO_PAINT);
  DLLExport void _export WINAPI GetContext(PaintContext *pc, WORD penident = 0xFFFF, WORD brushident = 0xFFFF);
  DLLExport void _export WINAPI GetContext(Printer *);
  DLLExport void _export WINAPI SetDC(HDC hExtDC);
  /****** Destruktor ***********/
  DLLExport void _export WINAPI ReleaseContext(void);
  DLLExport _export WINAPI ~PaintContext(void);   	// Destruktor: Beendet Paint Sitzung 
  /****** Mapping **************/
  int MapType;
  float logicalunits_per_halfpoint;
  DLLExport void _export WINAPI ResetMap (void);
  DLLExport void _export WINAPI Map(double,int x0 = 0,int y0 = 0,int xp = 0,int yp = 0);
  DLLExport void _export WINAPI LogicalTwips(int xp = 0,int yp = 0,float fact = 1.0);
  DLLExport double _export WINAPI GetLogStretch (void);
  /****** Attribute ************/
  DLLExport void _export WINAPI Attrib(WORD penident = 0xFFFF,WORD brushident = 0xFFFF);
  DLLExport void _export WINAPI Attrib(PENDATA,WORD brushident = 0xFFFF);
  DLLExport int _export WINAPI PenStyle(DWORD);
  DLLExport int _export WINAPI PenWidth(DWORD);
  DLLExport int _export WINAPI PenPhysWidth(DWORD);
  DLLExport void _export WINAPI GetPenInfo(DWORD dipen, WORD FAR *style, WORD FAR *width, DWORD FAR *color);
  DLLExport void _export WINAPI diPen(DWORD);
  /****** Fonts *******/
  DLLExport void _export WINAPI InsertFormat(WORD,FontInfo *);
  DLLExport void _export WINAPI DeleteFormat(WORD);
  DLLExport void _export WINAPI SelectFont(WORD,int Modify = -1);
  DLLExport void _export WINAPI GetFontExtraInfo (WORD,FontExtraInfo FAR *);
  DLLExport BOOL _export WINAPI GetFormatFaceName(WORD,LPSTR,int);
  DLLExport BOOL _export WINAPI GetFormatName(WORD,LPSTR,int);
  DLLExport DWORD _export WINAPI GetFormatColor (WORD);
  DLLExport DWORD _export WINAPI GetFormatIvColor (WORD);
  friend DLLExport void _export WINAPI DeleteFonts(void);
  /****** Hilfsfunktionen ******/
  DLLExport int _export WINAPI XLOGtoPHYS(int);
  DLLExport int _export WINAPI YLOGtoPHYS(int);
  DLLExport int _export WINAPI XPHYStoLOG(int);
  DLLExport int _export WINAPI YPHYStoLOG(int);
  DLLExport void _export WINAPI LogRecttoPhys (RECT FAR *,RECT FAR *);
  DLLExport void _export WINAPI Scroll(int,int);
  DLLExport int _export WINAPI XScroll(int);
  DLLExport int _export WINAPI YScroll(int);
  /****** Ausgabeoperator*******/
  DLLExport PaintContext& _export WINAPI operator << (RECT);
  DLLExport PaintContext& _export WINAPI operator << (Line);
  DLLExport PaintContext& _export WINAPI operator << (Bitmap);
  DLLExport PaintContext& _export WINAPI operator << (PosStr);
  DLLExport PaintContext& _export WINAPI operator << (GrayStr);
  DLLExport PaintContext& _export WINAPI operator << (ExtPosStr);
  DLLExport PaintContext& _export WINAPI operator << (MetaDesc);
  /****** Metafile - Bearbeitung *******/
  DLLExport void _export WINAPI GetMaxInfo (HMETAFILE,RECT FAR *);
  DLLExport void _export WINAPI ScaledMetaOut (HMETAFILE,tr2 FAR *,WORD translatemode = 0,DWORD PenType = 0,DWORD BrushType = 0);
  DLLExport void _export WINAPI ExtMetaOut (HMETAFILE,int FAR *);
  DLLExport int _export WINAPI GetPolyCount (HMETAFILE);
  DLLExport void _export WINAPI GetPolyRect (HMETAFILE,RECT *,int FAR *);
  /******* Extended Move *******/
  double lold;
  DWORD actdiPen;
  int xold,yold;
  int state;
  DLLExport void _export WINAPI PolyMoveTo (int,int);
  DLLExport void _export WINAPI PolyLineTo (int,int);
  /****** Bitmap lese bzw. Schreiben *****/
  DLLExport HBITMAP _export WINAPI ReadBitmap (RECT FAR *);
  DLLExport void _export WINAPI DrawBitmap (HBITMAP,RECT FAR *);
  };

DLLExport HANDLE _export WINAPI LoadMetaFile (char FAR *fname);
DLLExport void _export WINAPI ReadFI (void);
// Funktionen, die auf die Formatliste zugreifen
DLLExport UINT _export WINAPI GetFormatFlags (FontInfo FAR *);
DLLExport UINT _export WINAPI GetFormatFlags (LPFORMATINFO);
DLLExport UINT _export WINAPI GetFormatFlags (int);
DLLExport int _export WINAPI ModifyOutFormat (int Format,int OutFormat);

DLLExport void _export WINAPI MyLPtoDP (HDC hDC,LPPOINT pt,int cnt);

#define LPtoDP MyLPtoDP


