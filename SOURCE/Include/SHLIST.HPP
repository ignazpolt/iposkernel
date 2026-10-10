//  
//  $Header:   P:/marille/clinicum/include/rev/shlist.hpv   1.1   02 Feb 1996 10:59:06   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/shlist.hpv  $
// 
//    Rev 1.1   02 Feb 1996 10:59:06   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:02:02   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.4   17 Jun 1993 09:29:52   HANNES
// Vorlaufige Implementation der Multiselektionslisten
// 
//    Rev 1.3   09 May 1993 17:48:06   HANNES
// Uebernahme des ausgewaehlten Items
// 
//    Rev 1.2   09 May 1993 15:57:22   HANNES
// Datenelement fuer GetColoredText (dFormat)
// 
//    Rev 1.1   07 May 1993 09:46:16   HANNES
// ifdef ..._INCLUDED eingefuegt
// 
//    Rev 1.0   06 May 1993 21:35:26   HANNES
// Initial revision.
//
#ifndef SHLIST_INCLUDED
#define SHLIST_INCLUDED
struct FAR BemStrEntry {
  DWORD Benutzer;
  char Text[1];

  struct BemStrEntry FAR *GetNext(int FAR *size = NULL);
  };
typedef BemStrEntry FAR *LPBEMENT;

struct FAR BemCodeEntry {
  WORD CodeLen;
  BYTE Code[1];

  struct BemCodeEntry FAR *GetNext(int FAR *size = NULL);
  };
typedef BemCodeEntry FAR *LPBEMCENT;

struct FAR SHEntry {
  WORD EntrySize;
  WORD Flags;
  WORD IntNum;
  int AnzKuerzel;
  BemStrEntry Kuerzel[1];
  int AnzLangText;
  BemStrEntry LangText[1];
  int AnzCodes;
  BemCodeEntry Code[1];

  LPBEMENT GetKuerzel(int Num);
  LPBEMENT GetKuerzel(DWORD Benutzer,int Num);
  LPBEMENT GetFirstLangText (int FAR &AnzLangText);
  LPBEMENT GetLangText (int Num);
  LPBEMENT GetLangText(DWORD Benutzer,int Num,int FAR *Index = NULL);

  int GetAnzLangText();
  SHEntry FAR *AddKuerzel(DWORD Benutzer,LPSTR Text);
  SHEntry FAR *AddLangText(DWORD Benutzer,LPSTR Text);
  SHEntry FAR *ChangeKuerzel(int Num,DWORD Benutzer,LPSTR Text);
  SHEntry FAR *ChangeLangText(int Num,DWORD Benutzer,LPSTR Text);

  GLOBALHANDLE SHEntry::Export (int FAR &size);
  };

typedef SHEntry FAR *LPSHENT ;

LPSHENT GetEmptySHEnt (WORD IntNum);

#define SHLIST_VERSION0  0x01
struct SHEntry_Header {
  BREntry_Header brh;
  DWORD Version;
  };            
typedef SHEntry_Header FAR *LPSHENTHD;

#define HIDIMENSION  237
class FAR SHList {
 protected :
  WORD PrimKey;
  DictList FAR *dl;
#ifdef HASH_INCLUDED
  hash FAR *hi;
#else
  LPVOID FAR *hi;
#endif
  int RedFormat;
  int dFormat;

  LPSHENT act;      // aktuell bearbeiteter Eintrag
  int SHKNum;       // aktuell bearbeitetes Kuerzel
  int SHLNum;       // aktuell bearbeiteter Langtext

  GLOBALHANDLE hGData;
  LPSTR Base;
  BOOL dataChanged;

  int TranslateFormat (LPVOID entry,int FFormat);
  int TranslateModify (LPVOID entry,int FModify);
  WORD ResIndex (LPVOID entry);
  LPSTR ResString (LPVOID entry);

  void FillActSHList (HWND hDlg,int sel);
  void FillMainList (HWND hDlg);
  void ShowNostrMessage (HWND hDlg);
  BOOL TestString (HWND hDlg,WORD wP);
  void GetActCopy (HWND hDlg);
  void UpdateEntry (HWND hDlg,int kchecked = -1,int lchecked = -1);
  DWORD GetActUser ()
    { return 1 ; } // !!!!

  GLOBALHANDLE GetEmptyHeader ();
  BOOL BuildDict_Hash ();
  BOOL ChangeEnt (LPSHENT NewEntry);

  BOOL GetExpFileName (HWND hDlg,LPSTR filename);
  BOOL GetImpFileName (HWND hDlg,LPSTR filename);
  void Export (HWND hDlg);
  void Import (HWND hDlg);
  void Options (HWND hDlg);

  LPTWI SearchText;
  int twiformat,twimod;

 public :
  DLLExport LPVOID _export operator new (size_t size);
  DLLExport void _export operator delete (LPVOID obj);

  DLLExport _export SHList (WORD Id);
  virtual DLLExport _export ~SHList ();

  WORD GetNewIntNum();

  DLLExport BOOL _export GetEnt (LPTWI t,int FFormat,int FModify);
  DLLExport BOOL _export GetWord (LPTWI t,int FFormat,int FModify);
  DLLExport void _export WorkOn (int DefFormat,int RedFormat,HWND hWndOwner,LPTWI t,int trformat,int trmod);

  DLLExport void _export Load ();
  virtual DLLExport void _export Save ();

  friend DLLExport BOOL _export WINAPI SHDlgProc (HWND hDlg,unsigned msg,WORD wP,LONG lP);
  friend DLLExport BOOL _export WINAPI OptDlgProc (HWND hDlg,unsigned msg,WORD wP,LONG lP);
  friend void GetColoredLangText (LPSTR res,LPSTR LangText,LPSTR selstr);
  virtual BOOL doChange() { return TRUE ; }
  };

class SHSList : public SHList {
 protected :
  GLOBALHANDLE hGEntMem;
 public :
  DLLExport _export SHSList (WORD pk);
  virtual DLLExport _export ~SHSList ()
    { if (hGEntMem != 0) GlobalFree (hGEntMem); }
  virtual BOOL doChange() { return FALSE ; }
  BOOL TestIntNum (WORD i);
  LPSHENT GetSHEnt (LPSTR sh,LPSTR la,int num);
  void AddSHEnt (LPSHENT h);
  virtual DLLExport void _export Save ();
  };

DLLExport SHList FAR *_export GetSHList (WORD PrimKey);
DLLExport void _export DestroyLists();
DLLExport void _export AddToList (WORD PrimKey,LPSTR sh,LPSTR lang,int num);

#ifdef SHLIST_MAIN
static SHList FAR *ActSHList;
#endif

#endif
