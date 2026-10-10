// $Header:   P:/marille/clinicum/include/rev/btrieve.hpv   1.1   02 Feb 1996 11:00:22   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/btrieve.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:00   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.14   09 Dec 1993 16:01:30   MARTIN
// DOS_VERSION ....
// 
//    Rev 1.13   13 Oct 1993 12:20:06   HANNES
// convbase.hpp raus
// 
//    Rev 1.12   22 Sep 1993 09:22:02   HANNES
// Version nach St. Poelten
// 
//    Rev 1.11   02 Jun 1993 19:38:36   HANNES
// Verschiedene Konstanten zur verbesserten Schluesseldef.
// 
//    Rev 1.10   24 May 1993 14:02:20   HANNES
// Prototyp von DoUseNetware
// 
//    Rev 1.9   10 May 1993 12:50:42   HANNES
// ??
// 
//    Rev 1.8   06 May 1993 21:32:10   HANNES
// WriteHugeBlock, ReadHugeBlock, Open_Create
// 
//    Rev 1.7   02 Apr 1993 17:52:52   HANNES
// Strukturbereinigung
// 
//    Rev 1.6   17 Mar 1993 18:01:10   HANNES
// Reset
// 
//    Rev 1.5   02 Mar 1993 22:32:06   HANNES
// Filename in der Btrieve
// 
//    Rev 1.4   22 Feb 1993 17:19:14   HANNES
// GetRecCount
// 
//    Rev 1.3   08 Feb 1993 10:42:10   HANNES
// Umbau aller Files auf btrFiles
// 
//    Rev 1.2   05 Feb 1993 19:40:42   HANNES
// Definition der Klasse btrFile
// 
//    Rev 1.1   02 Feb 1993 19:16:48   HANNES
// Neue Datei: Orte.swk
// 
//    Rev 1.0   02 Dec 1992 15:50:52   HANNES
// Initial revision.

/*----< Btrieve Operation Codes >------*/
#define MODE_NORMAL             0
#define MODE_ACCELERATED        -1
#define REQNOTFOUND             4
#define ENDOFFILE               9
#define BRFILENOTFOUND          12

#define B_DELETE                4
#define B_CLOSE                 1
#define B_OPEN                  0
#define B_GETEQ                 5
#define B_GETKEYEQ              55
#define B_GETKEYGT              58
#define B_GETKEYGTE             59
#define B_GETKEYLE              61
#define B_GETKEYL               60
#define B_GETGT                 8
#define B_INSERT                2
#define B_UPDATE                3
#define B_GETPOS                22
#define B_GETDIRECT             23
#define B_GETNEXTKEY            56
#define B_GETPREVKEY            57
#define B_RESET                 28
#define B_CREATE                14
#define B_GETNEXTEXTENDED       36
#define B_GETPREVEXTENDED       37

#define B_GETNEXT               6
#define B_GETPREV               7
#define B_GETFIRST              12
#define B_GETLAST               13
#define B_GETGTE                9
#define B_GETL                  10
#define B_GETLE                 11

#define B_STATUS                15

#define BUFFER_SIZE     0x7FFF          // 32 kByte Buffer
typedef char POSBLOCK[128];

#ifdef DOS_VERSION
#define EXPORT
#else
#define EXPORT _export
#endif

#ifdef DOS_VERSION

// Teil aus windows.h
/******* Common definitions and typedefs ***********************************/

#define VOID                void

#define FAR                 _far
#define NEAR                _near
#define PASCAL              _pascal
#define CDECL               _cdecl

/****** Simple types & common helper macros *********************************/

typedef int                 BOOL;
#define FALSE               0
#define TRUE                1

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned long       DWORD;

typedef unsigned int        UINT;

typedef signed long         LONG;

#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((UINT)(w) >> 8) & 0xFF))

#define LOWORD(l)           ((WORD)(DWORD)(l))
#define HIWORD(l)           ((WORD)((((DWORD)(l)) >> 16) & 0xFFFF))

#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))

/****** Common pointer types ************************************************/

#ifndef NULL
#define NULL                0
#endif

typedef char NEAR*          PSTR;
typedef char NEAR*          NPSTR;

typedef char FAR*           LPSTR;
typedef const char FAR*     LPCSTR;

typedef BYTE NEAR*          PBYTE;
typedef BYTE FAR*           LPBYTE;

typedef int NEAR*           PINT;
typedef int FAR*            LPINT;

typedef WORD NEAR*          PWORD;
typedef WORD FAR*           LPWORD;

typedef long NEAR*          PLONG;
typedef long FAR*           LPLONG;

typedef DWORD NEAR*         PDWORD;
typedef DWORD FAR*          LPDWORD;

typedef void FAR*           LPVOID;

typedef UINT                HANDLE;
typedef HANDLE              GLOBALHANDLE;

#define lmemcpy memcpy
#define lmemset memset
#define lstrcpy strcpy
#define lstrncpy strncpy
#define lstrlen strlen
#define lstrcat strcat

#define MYINI "swdos.ini"

#else

#define BASEIDENT  0
#define MAINIDENT  1
#define PROGIDENT  2
#define CNFIDENT   3
#define KLIDENT    4
#define ORTIDENT   5

#define MAX_FILES       7
extern int OpenFile (int);

#endif // DOS_VERSION

#define STACKDEPTH  5

DLLExport void EXPORT btrReset(void);

struct brekey {
  WORD Laufende_Nummer;
  WORD PrimKey;
  } ;
struct BREntry_Header {
  brekey key ;
  DWORD DataSize;
  DWORD HeaderSize;
  };

struct BTRKEYSPEC {
  WORD keypos;
  WORD keylen;
  WORD keyflags;
  DWORD reserved1;
  BYTE keytype;
  BYTE nullval;
  DWORD reserved2;
  };

#define BTRKEY_BINARY    14
#define BTRKEY_LSTRING   10

#define BTRKEY_SEGMENTED 16
#define BTRKEY_DUPLICATE 1
#define BTRKEY_MODIFY    2
#define BTRKEY_EXTENDED  0x100

typedef BTRKEYSPEC FAR *LPBTRKEYSPEC;

class FAR btrFile {
 protected :
  BOOL IsOpen;
  POSBLOCK pb;
  int StackPtr;

  int KeyNumber[STACKDEPTH];
  int KeySize  [STACKDEPTH];
  int KeyOffset[STACKDEPTH];

  LPSTR GetDataFileName (LPSTR,LPSTR,LPSTR);
  int BufferSize;
  LPSTR Buffer;
  GLOBALHANDLE hGBuffer;

  void InitializeFileBuffer ();
  void SetBufferSize(int Size)
    { BufferSize = Size ; InitializeFileBuffer () ; }

 public :
  BOOL IsFileOpen ()
    { return IsOpen ; }
  char FileName[128];
  DLLExport LPVOID EXPORT operator new (size_t size);
  DLLExport void EXPORT operator delete (LPVOID);
  DLLExport BOOL EXPORT Open (LPSTR,LPSTR);
  DLLExport void EXPORT InitializeKey (int,int,int);

  DLLExport EXPORT btrFile (LPSTR,LPSTR,int,BOOL doOpen = TRUE);

  DLLExport void EXPORT PushKeyInfo ();
  DLLExport void EXPORT PopKeyInfo ();
  DLLExport LPVOID EXPORT GetFirst (unsigned FAR *);
  DLLExport LPVOID EXPORT GetLast (unsigned FAR *);
  DLLExport LPVOID EXPORT GetNext (unsigned FAR *);
  DLLExport LPVOID EXPORT GetPrev (unsigned FAR *);
  DLLExport LPVOID EXPORT GetGreaterEqual (LPSTR,unsigned FAR *);
  DLLExport LPVOID EXPORT GetGreater (LPSTR,unsigned FAR *);
  DLLExport LPVOID EXPORT GetLessEqual (LPSTR,unsigned FAR *);
  DLLExport LPVOID EXPORT GetLess (LPSTR,unsigned FAR *);
  DLLExport BOOL   EXPORT GetKeyGreaterEqual (LPSTR);
  DLLExport BOOL   EXPORT GetKeyLessEqual (LPSTR);
  DLLExport BOOL   EXPORT GetKeyLess (LPSTR);
  DLLExport DWORD  EXPORT GetPos ();
  DLLExport LPVOID EXPORT GetDirect (DWORD,unsigned FAR *);

  DLLExport int    EXPORT GetNextExtended (LPVOID,LPVOID,unsigned FAR *);
  DLLExport int    EXPORT GetPrevExtended (LPVOID,LPVOID,unsigned FAR *);

  DLLExport LPVOID EXPORT Get(LPSTR,unsigned FAR *);
  DLLExport BOOL EXPORT Insert (LPSTR,unsigned);
  DLLExport BOOL EXPORT Update (LPSTR,unsigned);

  // folgende Funktion NICHT fuer segmentierte Keys !
  DLLExport BOOL EXPORT Put (LPSTR,unsigned);

#ifndef DOS_VERSION
  DLLExport GLOBALHANDLE EXPORT ReadHugeBlock (WORD PrimKey);
  DLLExport BOOL EXPORT WriteHugeBlock (GLOBALHANDLE hGmem);
#endif

  DLLExport BOOL EXPORT Delete (LPSTR);

  DLLExport DWORD EXPORT GetRecCount ();

  DLLExport EXPORT ~btrFile ();

  LPSTR Get(LPSTR);    // ????????????????

#ifndef DOS_VERSION
  void InitializeFileSpec (int RecSize,int NumKeys,unsigned FAR *bfsize);
  DLLExport BOOL EXPORT btrFile::Open_Create (LPSTR pathItem,LPSTR name,
              WORD recLength,int KeyNums,LPBTRKEYSPEC keys,int keydefnum);
#endif
  };

#ifndef DOS_VERSION

DLLExport DWORD EXPORT WINAPI SetStationSemaphor (LPSTR);
DLLExport BOOL EXPORT WINAPI CheckStationSemaphor(LPSTR);
DLLExport void EXPORT WINAPI ClearStationSemaphor (DWORD);
DLLExport void EXPORT WINAPI GetNWAddress (LPSTR,int);
DLLExport BOOL EXPORT WINAPI DoUseNetware (void);
extern BOOL Login (void);
extern void Logout (void);
extern BOOL IsPatReferenced (WORD FAR *);
extern BOOL LockPatient (WORD FAR *,BOOL ShowMsg = TRUE);
void ReleasePatient (WORD FAR *);
extern BOOL UseMultiUserVersion ();
extern void GetPStr (LPSTR,int,LPSTR);
extern BOOL IsLockDetected (WORD FAR *,WORD RecType,WORD FNr);
extern void GetCommentListEntry (LPSTR Buffer,LPSTR res,int rSize);
extern void GetRecFlags (LPSTR Buffer,BOOL FAR *IsVTO,BOOL FAR *IsFixed,BOOL FAR *IsCopyied);
extern BOOL InquireLogin (BOOL relog);


#ifdef BTRV_MAIN
btrFile FAR *Patient;
btrFile FAR *Orte;
btrFile FAR *Station;
btrFile FAR *Platz;
btrFile FAR *Benutzer;
btrFile FAR *Klinik;
btrFile FAR *Config;
btrFile FAR *Prog;
btrFile FAR *MainData;
#else
extern btrFile FAR *Patient;
extern btrFile FAR *Orte;
extern btrFile FAR *Station;
extern btrFile FAR *Platz;
extern btrFile FAR *Benutzer;
extern btrFile FAR *Klinik;
extern btrFile FAR *Config;
extern btrFile FAR *Prog;
extern btrFile FAR *MainData;
#endif

#endif // not DOS_VERSION

#ifdef DOS_VERSION

extern "C" {
  extern int cdecl BTRV(int            operation,
                        struct BT_POS_BLOCK *posBlock,
                        void                *dataBuf,
                        unsigned short int  *dataLen,
                        void                *keyBuf,
                        short int            keyNum);
  }

#define BTRCALL(OP,PB,DB,DL,KB,KL,KN) BTRV((OP),(struct BT_POS_BLOCK *)(PB),(DB),(unsigned short int *)(DL),(KB),(KN))

#endif

