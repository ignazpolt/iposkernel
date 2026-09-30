// -----------------------------------------------------------
//            Druckerkopf - Textinterpretierung
// -----------------------------------------------------------
//
// $Header:   P:/marille/clinicum/rev/headtxt.cpv   1.8   07 Aug 1997 11:53:12   Hannes  $
// $Log:   P:/marille/clinicum/rev/headtxt.cpv  $
// 
//    Rev 1.8   07 Aug 1997 11:53:12   Hannes
// 
//    Rev 1.7   18 Sep 1996 20:46:54   HANNES
// 
//    Rev 1.6   10 Jun 1996 10:08:28   GERHOLD
// pragma pack
// 
//    Rev 1.5   02 Feb 1996 10:35:04   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.4   16 Sep 1995 02:06:22   MARTIN
// 
//    Rev 1.3   24 Aug 1995 00:20:24   HANNES
// DBWIN_ASSERT
// 
//    Rev 1.2   20 Mar 1995 11:56:10   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.1   19 Nov 1994 21:09:00   HANNES
// Schluesselwortinterpreter wieder aktiviert
// 
//    Rev 1.0   24 Jun 1994 17:05:08   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.8   12 Jan 1994 11:09:18   HANNES
// Unnoetige Includes raus
// 
//    Rev 1.7   09 Dec 1993 14:59:16   HANNES
// Seitennummerierung
// 
//    Rev 1.6   18 Jun 1993 15:13:50   MARTIN
// Protoptyp von GetData
// 
//    Rev 1.5   02 Jun 1993 19:51:42   HANNES
// Umbau des Prototypen von uDiffYears
// 
//    Rev 1.4   02 Apr 1993 17:29:30   HANNES
// strukturbereinigung, Beschleunigung
// 
//    Rev 1.3   17 Mar 1993 17:37:34   HANNES
// License, andere Logik bei der Schluesselwortsuche
// 
//    Rev 1.2   02 Mar 1993 22:33:20   HANNES
// Einige neue Schluesselwoerter
// 
//    Rev 1.1   13 Jan 1993 18:49:20   HANNES
// Erweiterung der Dokumente auf mehrere Datensaetze
// 
//    Rev 1.0   02 Dec 1992 15:33:22   HANNES
// Initial revision.
//

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "dds32.h"
#include "dds.hpp"
#include "dds.h"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "winextra.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"

#define MODULENUM 135
#include "winass.hpp"

#pragma pack(1)
struct FAR InstallKeyWord_param {
  WORD parSize;
  DWORD key;
  DWORD res;
  DWORD ProcToCall;
  DWORD flagres;
  DWORD kwbuffer;
  LPSTR KeyWord (mdiChild *c)
    { return LPSTR (c->ReadlData (key)); }
  BOOL withFlagRes ()
    {
    return (parSize >= sizeof(*this) - sizeof(DWORD));
    }
  BOOL needkwbuffer ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()
struct FAR IKWBSet {
  IKWBSet FAR *Next;
  LPSTR KeyWord;
  mdiChild *c;
  DWORD procToCall;
  DWORD res;
  InstallKeyWord_param FAR *par;

  void SetKeyWord (LPSTR Name)
    { 
    KeyWord = LPSTR(GetGlobMem (lstrlen(Name)+1));
    lstrcpy (KeyWord,Name);
    }
  };
typedef IKWBSet FAR *LPKW;
LPKW kList;

BOOL mystrcmp (LPSTR kw,LPSTR txt)
  {
  for ( ; ((*kw) && (*txt) && (*kw == *txt )) ; kw ++ , txt ++ ) ;
  return *kw == '\0';
  }

LPKW FindKW (LPSTR txt,int FAR *kwlen)
  {
  for (LPKW res = kList ; res != NULL ; res = res->Next) {
    if (mystrcmp (res->KeyWord,txt)) {
      *kwlen = lstrlen(res->KeyWord);
      return res;
      }
    }
  *kwlen = 0;
  return NULL ;
  }

void RemoveKW (LPVOID par)
  {
  LPKW prev = NULL;
  for (LPKW h = kList ; h != NULL ; h = h->Next) {
    if (h->par == par) {
      if (prev != NULL) prev->Next = h->Next ;
      else              kList = h->Next ;
      FreeGlobMem (h->KeyWord);
      FreeGlobMem (h);
      break ;
      }
    prev = h ;
    }
  }

extern void AddDDEItem (LPSTR Item);
extern void RemoveDDEItem (LPSTR Item);
BOOL InstallKeyWord (mdiChild FAR *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InstallKeyWord_param FAR *par = (InstallKeyWord_param FAR *) param;
    LPSTR k = par->KeyWord(c);
    int dummy;
    DBWIN_ASSERT (FindKW(k,&dummy) == NULL);
    LPKW n = LPKW(GetGlobMem (sizeof(*n)));
    n->SetKeyWord (k);
    n->c = c ;
    n->res = par->res;
    n->par = par ;
    n->procToCall = par->ProcToCall;
    n->Next = kList;
    kList = n;
    AddDDEItem (k);
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    InstallKeyWord_param FAR *par = (InstallKeyWord_param FAR *) param;
    RemoveDDEItem (par->KeyWord(c));
    RemoveKW (param);
    }
  return FALSE ;
  }

LPSTR GetKW (LPSTR kw,int FAR *kwlen,BOOL FAR *flgRes)
  {
  LPKW n = FindKW (kw,kwlen);
  if (n != NULL) {
    if (n->par->needkwbuffer ()) {
      LPSTR kwbuffer = LPSTR(GetGlobMem (*kwlen + 1));
      lmemcpy (kwbuffer,kw,*kwlen);
      n->c->WritelData (n->par->kwbuffer,kwbuffer,*kwlen + 1,LPSTR(n->par) - sizeof(WORD));
      FreeGlobMem (kwbuffer);
      }
    n->c->ExCuteProc (n->procToCall,EM_LOAD | EM_CHANGETOTRUE);
    n->c->ExCuteProc (n->procToCall,EM_RESET);
    LPSTR res = LPSTR (n->c->ReadlData (n->res));
    InstallKeyWord_param FAR *par = (InstallKeyWord_param FAR *) n->par ;
    if (par->withFlagRes()) {
      DBBOOL FAR *lpflg = (DBBOOL FAR *) n->c->ReadlData (par->flagres);
      if (lpflg != NULL)
        *flgRes = *lpflg ;
      else
        *flgRes = FALSE ;
      }
    else
      *flgRes = ((res != NULL) && (*res)) ;
    return res;
    }
  else {
    *flgRes = FALSE ;
    return NULL ;
    }
  }

GLOBALHANDLE PushChar (GLOBALHANDLE hGmem,WORD *Size,char ch)
  {
  if (hGmem)
    hGmem = GlobalReAlloc (hGmem,*Size+2,GMEM_MOVEABLE);
  else
    hGmem = GlobalAlloc (GMEM_MOVEABLE,2);
  char FAR *buffer = LPSTR(GlobalLock (hGmem));
  buffer[*Size] = ch ;
  buffer[*Size+1] = '\0' ;
  GlobalUnlock (hGmem);
  (*Size)++ ;
  return hGmem;
  }

GLOBALHANDLE PushSent (GLOBALHANDLE hGmem,WORD *Size,char FAR *txt)
  {
  int slen = lstrlen (txt) ;
  if (hGmem)
    hGmem = GlobalReAlloc (hGmem,*Size+slen+1,GMEM_MOVEABLE);
  else
    hGmem = GlobalAlloc (GMEM_MOVEABLE,slen+1);
  char FAR *buffer = LPSTR(GlobalLock (hGmem));
  lstrcpy (buffer + *Size,txt);
  GlobalUnlock (hGmem);
  *Size += slen ;
  return hGmem;
  }

inline BOOL isSkipChar (char ch)
  {
  return ((ch == ' ') || (ch == '\0') || (ch == '\t') ||
          (ch == '\r') || (ch == '\n') || (ch == '@') ||
          (ch == ',') || (ch == ';') || (ch == ':'));
  }

GLOBALHANDLE ConvertText (char FAR *txt,GLOBALHANDLE hGPar)
  {
  // Initialisieren des Rueckgabebuffers
  WORD Size = 0;
  GLOBALHANDLE hGres = 0;
  hGres = PushChar (hGres,&Size,'\0');
  Size = 0 ;
  BOOL flg;

  int level = 0 ;
  int testlevel = 0 ;
  BOOL doskip = FALSE ;

  // Durchscannen des gesamten Textes
  for ( ; *txt ; ) {
    switch (*txt) {
      case '{' :
        level ++ ;
        txt ++ ;
        break ;
      case '}' :
        if (-- level == testlevel) doskip = FALSE ;
        txt ++ ;
        break ;
      case '@' :
        if (!doskip) {
          int kwlen;
          if (mystrcmp ("IF(",txt + 1)) {
            LPSTR res = GetKW (txt+4,&kwlen,&flg);
            txt += 4 + kwlen ;
            for ( ; ((*txt) && (*txt != '{')) ; txt ++ ) ;
            doskip = !flg ;
            testlevel = level ;
            }
          else if (mystrcmp ("IFNOT(",txt + 1)) {
            LPSTR res = GetKW (txt+7,&kwlen,&flg);
            txt += 7 + kwlen ;
            for ( ; ((*txt) && (*txt != '{')) ; txt ++ ) ;
            doskip = flg ;
            testlevel = level ;
            }
          else {
            int kwlen=0;
            LPSTR res = GetKW (txt+1,&kwlen,&flg);
            if (res != NULL)
              hGres = PushSent (hGres,&Size,res);
            txt = txt+kwlen+1;
            }
          }
        else
          txt ++ ;
        break ;
      default :
        if (!doskip)
          hGres = PushChar (hGres,&Size,*txt++);
        else
          txt ++ ;
        break ;
      }
    }
  return hGres;
  }

