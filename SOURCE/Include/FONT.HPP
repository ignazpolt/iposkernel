////////////////////////////////////////////////////////////////////
//
//  Handling der Font's
//
////////////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/include/rev/font.hpv   1.7   16 Aug 1999 18:38:02   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/font.hpv  $
// 
//    Rev 1.7   16 Aug 1999 18:38:02   Hannes
// Verbesserungen SlantFields
// 
//    Rev 1.6   02 Feb 1996 11:05:36   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   05 Jan 1996 19:59:28   HANNES
// Fehlerkorrektur Formatierung
// 
//    Rev 1.3   11 Jun 1995 10:00:48   HANNES
// MyGetExtent, Buchstabenabmessen bei der Font Kreation
// 
//    Rev 1.2   11 Oct 1994 09:00:12   HANNES
// 
//    Rev 1.1   24 Jun 1994 21:16:00   MARTIN
// 
//    Rev 1.0   24 Jun 1994 17:01:40   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.2   14 Feb 1994 19:46:16   HANNES
// Fontverwaltung: Fensterspezifisch...
// 
//    Rev 1.1   24 May 1993 14:20:04   HANNES
// Slantfonts
// 
//    Rev 1.0   02 Apr 1993 17:59:48   HANNES
// Initial revision.
//

#ifndef FONT_INCLUDED
#define FONT_INCLUDED
#include <commdlg.h>

struct FAR _HandleWidth {
  short modify;
  HFONT HFont;
  LPINT bWidth;
  _HandleWidth FAR *Next;
  } ;
class FAR HandleList {
  _HandleWidth FAR *w;
 public :
  _HandleWidth FAR *operator [] (int modify);
  void ResetHandles ();
  };
struct FAR FHandle {
  HandleList HFont[2];
  };

struct FAR FontExtraInfo {
  int LineWidth;        // Zeilenabstand
  WORD FormatMode;      // Art der Formatierung (Zentriert..)
  int xLeft;            // linker Einzug
  int xRight;           // rechter Einzug
  char Reserved[16];    // Fuer Erweiterungen
  };

#define FDSCLEN 64
struct FAR FontInfo {
  WORD Ident;           // Ident - Nummer
  int DefFormat;        // Default Handle
  FHandle fh;
#ifdef HASH_INCLUDED
  hash FAR *HandleUsed;
#else
  LPVOID HandleUsed;
#endif
  FontExtraInfo fei;    // Extra - Info
  char FormatName[32];  // Name des Formates
  CHOOSEFONT cf;        // ChooseFont - Structure
  LOGFONT lf;           // LogFont - Structure zur Erzeugung von HFont
  char FormatDesc[FDSCLEN];  // Formatbeschreibung
  };

struct FAR FormatMetric {
  int yHeight;          // Gesamthoehe der Zeichen
  int yBaseHeight;      // Hoehe der Zeichen ueber der Basislinie
  int yExtraHeight;     // Zeilenabstand
  int xLeft;            // Platz, der links gelassen werden soll
  int xRight;           // Platz, der rechts gelassen werden soll
  int xAveWidth;        // Durchschnittliche Breite eines Zeichens
  int OutFormat;        // Typ des Formates
  };
typedef FormatMetric FAR *LPFORMATMETRIC;

struct FAR FontSlantHandle {
  int ang;
  int refcount;
  int maptype,modify;
  HFONT hfnt;
  FontSlantHandle FAR *Next;
  DWORD Kennung;

  void Create (FontInfo FAR *fi,double a,int m,int Modify,DWORD K);
  BOOL Delete ();
  void Destroy ();
  BOOL Check (double a,int m,int modify);
  };
typedef FontSlantHandle FAR *LPFSLANT;

struct FAR FormatInfo {
  FontInfo fi;
  BOOL MetricInitialized;
  FormatMetric fm[2]; // Fuer beide Mapping Types
  FontSlantHandle FAR *slh;
  FormatInfo FAR *Next;

  HFONT GetSlantHandle (double ang,int m,int Modify,DWORD Kennung,BOOL doCreate = FALSE);
  void DelSlantHandle (DWORD Kennung);
  };

typedef FormatInfo FAR *LPFORMATINFO;

DLLExport LPFORMATINFO _export WINAPI GetFormatFirst ();
DLLExport LPFORMATINFO _export WINAPI GetFormatNext (LPFORMATINFO);

DLLExport void _export WINAPI fntInsertFormat (WORD Ident,FontInfo FAR *fi);
DLLExport void _export WINAPI fntDeleteFormat (WORD Ident);
DLLExport void _export WINAPI fntDeleteAllFormats ();
DLLExport void _export WINAPI ResetHandles (LPFORMATINFO lpf);
DLLExport void _export WINAPI ResetWindowHandles (LPFORMATINFO lpf,HWND hWnd);
DLLExport void _export WINAPI ResetWindowHandles (HWND hWnd);

typedef HDC (* HDCCALLBACK) (HDC dcToRelease,LPVOID CallBackdata);
DLLExport HFONT _export WINAPI GetFontHandle (HWND hWnd,int MapType,int Format,int Modify,int Orientation = 0,HDCCALLBACK GenPrDC = NULL,LPVOID CallBackData = NULL);
DLLExport LPFORMATMETRIC _export WINAPI GetFormatMetrics (HWND hWnd,int MapType,int Format);
DLLExport void _export WINAPI RebuildList (void);
DLLExport LPFORMATINFO _export WINAPI GetFormatInfo (WORD Ident);
DLLExport void _export WINAPI fntGetFontExtraInfo (WORD Format,FontExtraInfo FAR *fei);
DLLExport BOOL _export WINAPI fntGetFormatFaceName(WORD Format,LPSTR FaceName,int size);
DLLExport BOOL _export WINAPI fntGetFormatName(WORD Format,LPSTR Name,int size);
DLLExport DWORD _export WINAPI fntGetFormatColor (WORD Format);
DLLExport DWORD _export WINAPI fntGetFormatIvColor (WORD Format);

DLLExport int _export WINAPI fntModifyOutFormat (int Format,int OutFormat);
DLLExport int _export WINAPI fntGetMaxFormatId ();

// Nur vom cword aus zugaenglich
int MyGetTextExtent (HDC hDC,LPSTR str,int count,int FAR *FAR *chars = NULL);

#ifdef FONT_MAIN
hash FAR *fListHash;
LPFORMATINFO fifirst;
#endif

#ifndef MAPTYPE_GEOMETRIC
#define MAPTYPE_GEOMETRIC     1     // 1 log. Einheit = 0.04 mm
#define MAPTYPE_TYPOGRAPHIC   2     // 1 log. Einheit = 1/1440 Zoll
#endif

#define FI_BOLD         0x0001
#define FI_UNDERLINE    0x0002
#define FI_STRIKEOUT    0x0004
#define FI_ITALIC       0x0008
#define FI_HIGH         0x0010
#define FI_LOW          0x0020

#define FR_LEFT            0
#define FR_CENTERED        1
#define FR_RIGHT           2
#define FR_BLOCK           3

#endif
extern DLLExport BOOL _export WINAPI GetBestScaling (HWND hWnd,int MapType,float FAR *sc,HDC hPrDC);


