//  Lesen eines Versionsverwalteten Files - Strukturen
// $Header:   P:/marille/clinicum/include/rev/get_put.hpv   1.3   25 Feb 1998 17:48:28   Hannes  $
// $Log:   P:/marille/clinicum/include/rev/get_put.hpv  $
// 
//    Rev 1.3   25 Feb 1998 17:48:28   Hannes
// #pragma pack(1) wieder rein
// 
//    Rev 1.2   23 Feb 1998 09:17:58   Hannes
// 
//    Rev 1.1   19 Nov 1997 19:14:24   Hannes
// 
//    Rev 1.0   26 Nov 1996 08:09:04   HANNES
// Initial revision.
// Aufruf:
//   1) Get filename: Liest die aktuellste Version
//   2) Get -nnn -l filename: Liest die angegebene Version
//--------------------------------------------------------
#ifndef WINVER
#define FAR
typedef FILE *HFILE ;
typedef char *LPSTR ;

#define GetGlobMem(Size) malloc (Size)
#define FreeGlobMem(Obj) free (Obj)
typedef int OFSTRUCT;
#define OF_READ 	        0x0000
#define OF_WRITE	        0x0001
#define OF_READWRITE	    0x0002
#define OF_CREATE	        0x1000
#define OF_DELETE	        0x0200
#define FALSE 0
#define TRUE  1
typedef unsigned int UINT;
#include <errno.h>
#include <dos.h>
inline HFILE OpenFile(LPSTR fName,OFSTRUCT FAR *of,UINT flags) 
  {
  if (flags & OF_CREATE) {
    HFILE newfile = fopen (fName,"w+b");
    int a = errno;
    int b = _doserrno;
    _DOSERROR de;
    _dosexterr(&de);
    return newfile;
    }
  else if (flags & OF_READWRITE) return fopen (fName,"r+b");
  else if (flags & OF_DELETE)    { remove (fName) ; return NULL ; }
  else                           return fopen (fName,"rb");
  }
#define _lread(A,B,C) fread (B,1,C,A)
#define _lwrite(A,B,C) fwrite (B,1,C,A)
#define _lclose(F) fclose (F)
#define IsValidFile(A)  (A != NULL)
inline void GetEnvironment (LPSTR name,void *res,int size)
  {
  LPSTR x = getenv (name);
  if (x != NULL)
    strcpy (LPSTR(res),x);
  else
    *((char *) res) = '\0';
  }
#define wsprintf sprintf
typedef int BOOL;
inline long _llseek(HFILE A,long B,int C) 
  {
  if (fseek(A,B,C) == 0) 
    return ftell (A);
  else
    return 0L;
  }
#define lstrcpy strcpy
#define lstrcat strcat
#define lstrlen strlen
#define lstrcmp strcmp
#define lmemset memset
#define lmemcpy memcpy
#else
#define IsValidFile(A)  (A > NULL)
#endif
#define REV_EXTENSION   ".rvh"
#define COMMENT_END     "$-+-\r\n"

#define CB_LOCKEDBY 32
#define FIRSTVERSION  1
#pragma pack(1)
struct GetPut_Hd {
  long  OffsetToDict;
  short AnzDicts;
  char  LockedBy[CB_LOCKEDBY];
  };

struct DictEntry {
  short Version;
  long VOffset;
  long COffset;
  long VSize;
  long CSize;
  };
#pragma pack()

#define VERSION_STRING  "_Version"
LPSTR ReadBlock (int FAR *Size,int Version,LPSTR Name,BOOL do_lock,LPSTR errmsg,BOOL WithComment);
BOOL WriteBlock (LPSTR FileName,LPSTR errmsg,LPSTR Comment,int CommentSize);
BOOL Unlock (LPSTR FileName,LPSTR errmsg);
#ifdef _DOSPRG
LPSTR ReadComment (int FAR &CommentSize);
LPSTR ReadCommentFromFile (LPSTR FileName,LPSTR errmsg,int FAR &size);
BOOL WriteBlockFromBuffer (LPSTR res,int Size,LPSTR ControlName,LPSTR errmsg,LPSTR Comment,int CommentSize,LPSTR FileName);
#endif

