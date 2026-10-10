// 
// Prototypen der Funktionen, die zur Digitalisierung verwendet werden
// koennen
//
// $Header:   P:/marille/clinicum/include/rev/digitize.hpv   1.4   05 Oct 1998 11:24:48   Gerhold  $
// $Log:   P:/marille/clinicum/include/rev/digitize.hpv  $
// 
//    Rev 1.4   05 Oct 1998 11:24:48   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.3   02 Feb 1996 11:00:20   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   20 Nov 1994 18:16:36   HANNES
// Digitizer wieder reaktiviert
// 
//    Rev 1.1   24 Jun 1994 19:19:06   MARTIN
// Frmobject in DLL
// 
//    Rev 1.2   16 Nov 1993 04:24:36   HANNES
// Einbau der Mouseskalierung
// 
//    Rev 1.1   23 Aug 1993 19:46:36   HANNES
// ...
// 
//    Rev 1.0   02 Dec 1992 15:56:04   HANNES
// Initial revision.

#ifndef DIGITIZE_INCLUDED
#define DIGITIZE_INCLUDED
// Struktur in der Konfigurationsdatei
struct FAR DIGICNF {
  WORD Size;
  char LibName[13];
  char CnfStr[14];
  };

struct FAR MAPINFO {
  float scale;
  int x0,y0,xp,yp ;
  BOOL scdefined;
  tr2 sc;
  };

DLLExport HINSTANCE _export WINAPI GetDigLib (LPSTR Name);
/*-----< DDL Laden .... >-----*/
DLLExport void _export WINAPI InitDigLib (void);
DLLExport void _export WINAPI ExitDigLib (void);
DLLExport void _export WINAPI InitDigMse (void);
DLLExport void _export WINAPI ExitDigMse (void);
/*-----< Bedienung des Digitizers >-----*/
DLLExport void _export WINAPI SetupForPoint (HWND hWnd,BOOL state = TRUE);
DLLExport void _export WINAPI SetupForCont (HWND hWnd,BOOL state = TRUE);
DLLExport LONG _export WINAPI DigiMsg (HWND,UINT,WPARAM,LPARAM,BOOL FAR *,struct MAPINFO FAR *);

/*-----< Funktionen der DLL >-------*/
typedef void (WINAPI * GETDIGNAME) (char FAR *Name,int nSize);
typedef void (WINAPI * SETUPFNC) (HWND,char FAR *,BOOL state);
typedef LONG (WINAPI * MSGCHECK) (HWND,UINT,WPARAM,LPARAM,BOOL FAR *,struct MAPINFO FAR *);


DLLExport void _export WINAPI SetDigCnf (DIGICNF FAR *cnf);
DLLExport HWND _export WINAPI GetDigWindow (void);

#endif
