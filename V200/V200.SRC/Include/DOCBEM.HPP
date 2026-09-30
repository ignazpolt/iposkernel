////////////////////////////////////////////////////////////////////////
//  Bemerkungen zum einem Dokument
////////////////////////////////////////////////////////////////////////
// Header in dem Segment
//////////////////////////////
struct BemHeader {
  DWORD dwActSize;
  DWORD AnzBem;
  };
typedef BemHeader FAR *LPBEMHEADER;

// Record, wie er in dem Segment steht
///////////////////////////////////////
struct BemRecord {
  char prgName[13];
  WORD FallNummer;
  LONG EnterTime;
  DWORD User;
  int StrLen;
  char Txt[1];
  };
typedef BemRecord FAR *LPBEMREC;

// Callbackfunktion zu
#define PATBEM_GETTEXT      0     // Ermitteln des Textes aus dem Record
#define PATBEM_FILLSTRUCT   1     // Eintragen des Benutzers
typedef void (WINAPI * BEMCALLBACK) (int Command,LPBEMREC rec,LPSTR txt,int size,LPVOID CallbackMem);

// Anzeigen der Bemerkungen: 
// Resultat: Benutzer will neue Bemerkung speichern
////////////////////////////////////////////////////////
DLLExport BOOL _export WINAPI ShowBemerkungen (HWND hWnd,
                                         GLOBALHANDLE FAR &hGtxt,
                                         BEMCALLBACK cfb,
                                         LPVOID cbm,
                                         BOOL doEdit,     // mit Editbox
                                         BOOL FAR &doChange,   // letzten Eintrag veraendern
                                         LPSTR prgName,
                                         WORD FallNummer);

DLLExport BOOL _export WINAPI CheckBemSeg (GLOBALHANDLE hGBemSeg,LPSTR prgName,WORD FallNumm);
DLLExport BOOL _export WINAPI GetLastBemerkung (GLOBALHANDLE hGBemSeg,LPSTR prgName,WORD FallNummer,LPSTR rTxt,int rSize);

