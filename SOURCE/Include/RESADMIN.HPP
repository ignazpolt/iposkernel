////////////////////////////////////////////////////////////////////////
//  Verwaltung der Resourcen
////////////////////////////////////////////////////////////////////////
//  $Header:   F:/marille/clinicum/include/rev/resadmin.hpv   1.4   01 May 2000 13:33:46   Hannes  $
//  $Log:   F:/marille/clinicum/include/rev/resadmin.hpv  $
// 
//    Rev 1.4   01 May 2000 13:33:46   Hannes
// Auch 800x600 in den Bitmaps unterstuetzt
// 
//    Rev 1.3   04 Mar 1996 21:13:48   GERHOLD
// pragma pack
// 
//    Rev 1.2   02 Feb 1996 11:00:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   11 Jul 1994 21:30:16   HANNES
// GetWMFID
// 
//    Rev 1.0   24 Jun 1994 17:01:30   HANNES
// Neuuebernahme clinicum
//

//  Exportierte Funktionen
////////////////////////////////////////////
#define RESTYPE_CONT        0
#define RESTYPE_BITMAP      1
#define RESTYPE_WMF         2
#define RESTYPE_BITMAP8_6   3      

#ifndef NOFUNCTION
DLLExport BOOL _export WINAPI StoreBitmap (LPSTR Bmp,LPSTR fname,int xd,int yd,int type);
DLLExport BOOL _export WINAPI StoreWMF (LPSTR Wmf,LPSTR fname);
DLLExport void _export WINAPI CreateResContent ();
DLLExport void _export WINAPI ReadResContent ();
DLLExport void _export WINAPI UnloadResContent ();
DLLExport void _export WINAPI FillResDlg (HWND hDlg,WORD Id);
DLLExport GLOBALHANDLE _export WINAPI GetResource (DWORD Id,WORD FAR *Type,DWORD FAR *DataSize);
DLLExport void _export WINAPI GetResourceInfo (int Sel,LPSTR TypeName,LPSTR RsName,DWORD FAR *Id);
#endif

#pragma pack(1)
struct FAR Res_CEntry {
  DWORD ResID;
  WORD  Type;
  char  name[1];

  Res_CEntry FAR *Next()
    { return (Res_CEntry FAR *) (LPSTR(this) + sizeof(*this) + lstrlen(name)) ; }
  LPSTR GetName()
    { return name ; }
  LPSTR GetEntType(LPSTR buffer)
    { wsprintf (buffer,"%s",(Type == RESTYPE_BITMAP) ? LPSTR("BITMAP") : LPSTR("WMF")) ; return buffer ; }
  LPSTR GetResID(LPSTR buffer)
    { wsprintf (buffer,"%ld",ResID) ; return buffer ; }
  };
struct FAR Res_CHead {
  WORD AnzEntrys;
  };

typedef Res_CEntry FAR *LPRESCENT;

DLLExport DWORD _export WINAPI TransformResID (DWORD ID,short resX);

DLLExport LPRESCENT _export WINAPI GetFirstResourceInfo();
DLLExport LPRESCENT _export WINAPI GetNextResourceInfo(LPRESCENT h,WORD Nr);
DLLExport DWORD _export WINAPI GetBitmapID (LPSTR Name);
DLLExport DWORD _export WINAPI GetWMFID (LPSTR Name);
DLLExport DWORD _export WINAPI GetBitmap8x6ID (LPSTR Name);
#pragma pack()
