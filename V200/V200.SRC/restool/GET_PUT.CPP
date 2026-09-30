//--------------------------------------------------------
//  Lesen / Schreiben des Versionsverwalteten Files
// $Header:   P:/marille/clinicum/restool/rev/get_put.cpv   1.9   14 Aug 1998 18:56:12   Hannes  $
// $Log:   P:/marille/clinicum/restool/rev/get_put.cpv  $
// 
//    Rev 1.9   14 Aug 1998 18:56:12   Hannes
// Include / Source Pfad wirklich trennen
// 
//    Rev 1.8   23 Feb 1998 09:18:12   Hannes
// 
//    Rev 1.7   05 Nov 1997 09:05:28   Gerhold
// 32 Bit
// 
//    Rev 1.6   28 Aug 1997 15:51:24   gerhold
// Umstellung 32 Bit
// 
//    Rev 1.5   18 Jun 1997 19:58:26   Hannes
// Ueberpruefung von VCSID verbessert
// 
//    Rev 1.4   04 Dec 1996 09:09:40   HANNES
// 
//    Rev 1.3   27 Nov 1996 13:18:20   HANNES
// 
//    Rev 1.2   26 Nov 1996 21:20:28   HANNES
// 
//    Rev 1.1   26 Nov 1996 19:07:40   HANNES
// 
//    Rev 1.0   26 Nov 1996 08:11:08   HANNES
// Initial revision.
//--------------------------------------------------------
#include <stdlib.h>
#ifdef _DOSPRG
#include <stdio.h>
#include <time.h>
#include <string.h>
#else
#include <windows.h>

#include "dds32.h"
#include "globmem.h"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"
#endif

#include "get_put.hpp"

void GetControlName (LPSTR ControlName,LPSTR FileName)
  {
  char fName[32];
  // Den Pfad vom Filenamen wegnehmen
  LPSTR fStart = FileName;
  for (LPSTR h = FileName ; *h ; h++)
    if ((*h == '\\') || (*h == ':')) fStart = h + 1;
  lstrcpy (fName,fStart);
  // Die Extension wegnehmen
  for (h = fName ; *h ; h ++) {
    if (*h == '.') *h = '\0' ;
    }
  lstrcat (fName,REV_EXTENSION);
#ifndef WINVER
  // Dos - Version -> Lesen mit der Enivornmentvariable
  char *path = getenv ("RPATH");
  if (path != NULL)
    lstrcpy (ControlName,path);
  else {
    lstrcpy (ControlName,FileName);
    LPSTR lastDir = ControlName;
    for (LPSTR h = ControlName ; *h ; h++)
      if ((*h == '\\') || (*h == ':')) lastDir = h + 1;
    *lastDir = '\0' ;
    }
  lstrcat (ControlName,fName);
#else
  // Die Windowsvarianten -> Lesen mit GetIncludeFileName
  char iName[128];
  GetIncludeFileName (fName,ControlName,iName,"source");
#endif
  }
LPSTR ReadBlock (int FAR *Size,int Version,LPSTR FileName,BOOL do_lock,LPSTR errmsg,BOOL WithComment)
  {
  OFSTRUCT Of;
  char ControlName[256];
  HFILE f = NULL;
  LPSTR res;
  BOOL error = FALSE;
  *errmsg = '\0';

  GetControlName (ControlName,FileName);
  int VComment;
  if (!error) {
    if (do_lock)
      f = OpenFile (ControlName,&Of,OF_READWRITE);
    else
      f = OpenFile (ControlName,&Of,OF_READ);
    if (!IsValidFile (f))
      error = TRUE ;
    }
  if (!error) {
    GetPut_Hd hd;
    DictEntry de;
    if (!error) {
      if (_lread (f,&hd,sizeof(hd)) != sizeof(hd))
        error = TRUE ;
      }
    if (do_lock) {
      if (*hd.LockedBy) {
        error = TRUE ;
        wsprintf (errmsg,"%s already locked by %s",FileName,LPSTR(hd.LockedBy));
        }
      if (!error) {
        char UserName[CB_LOCKEDBY];

#ifdef WIN32
        GetEnvironmentVariable ("VCSID",UserName,sizeof(UserName));
#else
        GetEnvironment ("VCSID",UserName,sizeof(UserName));
#endif

        if (*UserName) {
          lstrcpy (hd.LockedBy,UserName);
          _llseek (f,0L,SEEK_SET);

#ifdef WIN32
          if (_lwrite (f,LPSTR(&hd),sizeof(hd)) != sizeof(hd)) {
#else
          if (_lwrite (f,&hd,sizeof(hd)) != sizeof(hd)) {
#endif

            wsprintf (errmsg,"error writing %s",LPSTR(ControlName));
            error = TRUE ;
            }
          }
        else {
          wsprintf (errmsg,"no VCSID set");
          error = TRUE ;
          }
        }
      }
    if (!error) {
      if (Version == -1) {
        _llseek (f,hd.OffsetToDict + sizeof(DictEntry) * (hd.AnzDicts - 1),SEEK_SET);
        Version = hd.AnzDicts - 1 + FIRSTVERSION ;
        VComment = Version ;
        if (do_lock) Version ++ ;
        }
      else {
        VComment = Version ;
        if (Version - FIRSTVERSION < hd.AnzDicts)
          _llseek (f,hd.OffsetToDict + sizeof(DictEntry) * (Version - FIRSTVERSION),SEEK_SET);
        else {
          error = TRUE ;
          wsprintf (errmsg,"illegal version!");
          }
        }
      if (!error) {
        if (_lread (f,&de,sizeof(de)) != sizeof(de))
          error = TRUE ;
        }
      }
    if (!error) {
      int cLen = 0 ;
      int ceLen = 0 ;
      DictEntry FAR *vlist = NULL ;
      if (WithComment) {
        vlist = (DictEntry FAR *) GetGlobMem (sizeof(DictEntry) * VComment) ;
        _llseek (f,hd.OffsetToDict,SEEK_SET);
        if (_lread (f,vlist,sizeof(*vlist) * VComment) != sizeof(*vlist) * VComment) {
          error = TRUE ;
          }
        for (int i = 0 ; i < VComment ; i++) {
          cLen = cLen + int(vlist[i].CSize) ;
          }
        }
      int vlen = 0;
      if (!error) {
        char VersionString [256];
        wsprintf (VersionString,"%s %d\r\n",LPSTR(VERSION_STRING),Version);
        vlen = lstrlen (VersionString);
        if (WithComment)
          ceLen = lstrlen (COMMENT_END);
        else
          ceLen = 0 ;
        res = LPSTR (GetGlobMem (int (de.VSize) + vlen + ceLen + cLen + 1));  // Sicherheitshalber ein '\0' hinten dran !!!
        lstrcpy (res,VersionString);
        if (WithComment) {
          int offs = vlen ;
          for (int i = 0 ; ((i < VComment) && (!error)) ; i++) {
            if (vlist[i].COffset != 0L) {
              _llseek (f,vlist[i].COffset,SEEK_SET);
              if (int (_lread (f,res + offs,int(vlist[i].CSize))) != int (vlist[i].CSize)) {
                FreeGlobMem (res);
                res = NULL ;
                error = TRUE ;
                }
              else
                offs += int(vlist[i].CSize);
              }
            }
          if (!error) {
            lmemcpy (res + offs,COMMENT_END,ceLen);
            }
          }
        }
      if (!error) {
        _llseek (f,de.VOffset,SEEK_SET);
        if (int (_lread (f,res + vlen + cLen + ceLen,int(de.VSize))) != int (de.VSize)) {
          FreeGlobMem (res);
          res = NULL ;
          error = TRUE ;
          }
        else
          *Size = int(de.VSize) + vlen + cLen + ceLen;
        }
      if (vlist != NULL) FreeGlobMem (vlist) ;
      }
    }
  if (error) {
    if (!*errmsg)
      wsprintf (errmsg,"%s: Not a valid File",LPSTR(ControlName));
    res = NULL;
    }
  if (IsValidFile (f))
    _lclose (f);
  return res;
  }



#ifdef WIN32
  extern BOOL mystrcmp (LPSTR s1,LPSTR s2);
#else
  BOOL mystrcmp (LPSTR s1,LPSTR s2)
    {
    for ( ; ((*s1 == *s2) && (*s1) && (*s2)) ; s1 ++ , s2 ++ ) ;
    if (*s2 == '\0') return TRUE ;
    return FALSE ;
    }
#endif

int MyUpper (int ch)
  {
  if ((ch >= 'a') && (ch <= 'z'))
    return ch - 'a' + 'A' ;
  else
    return ch ;
  }
int ciStrCmp (LPSTR h1,LPSTR h2)
  {
  for ( ; ((*h1) && (*h2)) ; h1 ++ , h2 ++ ) {
    if (MyUpper (*h1) != MyUpper (*h2)) return -1 ;
    }
  return *h1 + *h2 ;
  }
int ScanVersion (LPSTR FAR *res,int FAR *Size)
  {
  LPSTR h = *res;
  h[lstrlen(VERSION_STRING)] = '\0';
  int Version = 0 ;
  if (lstrcmp (h,VERSION_STRING) == 0) {
    for ( h += lstrlen(VERSION_STRING) + 1 ; ((*h) && ((*h == ' ') || (*h == '\t'))) ; h++) ;
    for ( ; ((*h) && (*h >= '0') && (*h <= '9')) ; h ++ )
      Version = Version * 10 + *h - '0' ;
    for ( h ++ ; ((*h) && (*h == ' ') || (*h == '\t')) ; h++) ;
    if (*h == '\r') h ++ ;
    if (*h == '\n') h ++ ;
    // Suchen des Endes des Kommentarblockes
    for (LPSTR x = h ; *x ; x++) {
      if (mystrcmp (x,COMMENT_END)) {
        h = x + lstrlen(COMMENT_END);
        break ;
        }
      }
    *Size -= (h - *res);
    *res = h ;
    }
  return Version ;
  }

#ifdef _DOSPRG
BOOL WriteBlockFromBuffer (LPSTR res,int Size,LPSTR ControlName,LPSTR errmsg,LPSTR Comment,int CommentSize,LPSTR FileName)
  {
  BOOL error = FALSE ;
  char UserName[CB_LOCKEDBY];
  if (!error) {
    GetEnvironment ("VCSID",UserName,sizeof(UserName));
    if (!*UserName) {
      wsprintf (errmsg,"no VCSID set");
      error = TRUE ;
      }
    }

  int Version ;
  if (!error) {
    Version = ScanVersion (&res,&Size);
    if (Version == 0) {
      wsprintf (errmsg,"%s has illegal Format, must start with %s nnn!",LPSTR(FileName),LPSTR(VERSION_STRING));
      error = TRUE ;
      }
    }

  char RevString[64];
  int revSize;
  if (!error) {
    time_t long_time;
    time (&long_time);
    struct tm *newtime = localtime(&long_time);
    char astring[32];
    lstrcpy (astring,asctime(newtime));
    for (LPSTR h = astring ; *h ; h++)
      if (*h == '\n') *h = '\0' ;
    if (CommentSize > 0)
      wsprintf (RevString,"$ Rev. %d %s %s\r\n",Version,astring,UserName);
    else
      wsprintf (RevString,"$ Rev. %d %s %s",Version,astring,UserName);
    revSize = lstrlen(RevString);
    }
  GetPut_Hd hd,hdn;
  HFILE f;
  OFSTRUCT Of;
  if (!error) {
    f = OpenFile (ControlName,&Of,OF_READWRITE);
    if (IsValidFile (f)) {
      if (_lread (f,&hd,sizeof(hd)) != sizeof(hd))
        error = TRUE ;
      if (!error) {
        if (ciStrCmp  (hd.LockedBy,UserName) != 0) {
          error = TRUE ;
          wsprintf (errmsg,"no version locked by %s",LPSTR(UserName));
          }
        }
      if (!error) {
        if (Version != hd.AnzDicts + 1) {
          error = TRUE ;
          wsprintf (errmsg,"Version incorrect!, must be %d",hd.AnzDicts + 1);
          }
        }
      if (!error) {
        hdn = hd ;
        hdn.OffsetToDict = hd.OffsetToDict + Size + CommentSize + revSize;
        hdn.AnzDicts = hd.AnzDicts + 1 ;
        lmemset (hdn.LockedBy,'\0',sizeof(hdn.LockedBy));
        _llseek (f,0L,SEEK_SET);
        if (_lwrite (f,LPSTR(&hdn),sizeof(hdn)) != sizeof(hdn))
          error = TRUE ;

        DictEntry FAR *lpde = NULL ;
        if (!error) {
          lpde = (DictEntry FAR *) GetGlobMem (hd.AnzDicts * sizeof(*lpde));
          _llseek (f,hd.OffsetToDict,SEEK_SET);
          if (_lread (f,lpde,hd.AnzDicts * sizeof(*lpde)) != (hd.AnzDicts * sizeof(*lpde))) {
            error = TRUE ;
            }
          }
        if (!error) {
          _llseek (f,hd.OffsetToDict,SEEK_SET);
          if (int (_lwrite (f,res,Size)) != Size)
            error = TRUE ;
          if (int (_lwrite (f,RevString,revSize)) != revSize)
            error = TRUE ;
          if ((Comment != NULL) && (!error)) {
            if (int (_lwrite (f,Comment,CommentSize)) != CommentSize)
              error = TRUE ;
            }
          if (_lwrite (f,LPSTR (lpde),hd.AnzDicts * sizeof(*lpde)) != hd.AnzDicts * sizeof(*lpde))
            error = TRUE ;
          DictEntry de;
          de.Version = Version ;
          de.VOffset = hd.OffsetToDict ;
          de.VSize = Size ;
          if (Comment != NULL) {
            de.COffset = hd.OffsetToDict + Size ;
            de.CSize = CommentSize + revSize ;
            }
          else {
            de.COffset = hd.OffsetToDict + Size ;
            de.CSize = revSize ;
            }
          if (_lwrite (f,LPSTR (&de),sizeof(de)) != sizeof(de))
            error = TRUE ;
          }
        if (lpde != NULL)
          FreeGlobMem (lpde);
        }
      }
    else {
      if (Version != FIRSTVERSION) {
        error = TRUE ;
        wsprintf (errmsg,"Versionnumber incorrect!, must be %d",FIRSTVERSION);
        }
      if (!error) {
        f = OpenFile (ControlName,&Of,OF_CREATE);
        if (!IsValidFile (f)) error = TRUE ;
        }
      if (!error) {
        hdn.OffsetToDict = sizeof(hdn) + Size + CommentSize + revSize ;
        hdn.AnzDicts = 1 ;
        lmemset (hdn.LockedBy,'\0',sizeof(hdn.LockedBy));
        if (_lwrite (f,LPSTR (&hdn),sizeof(hdn)) != sizeof(hdn))
          error = TRUE ;
        if (!error) {
          if (int (_lwrite (f,res,Size)) != Size)
            error = TRUE ;
          }
        if (int (_lwrite (f,RevString,revSize)) != revSize)
          error = TRUE ;
        if ((!error) && (Comment != NULL)) {
          if (int (_lwrite (f,Comment,CommentSize)) != CommentSize)
            error = TRUE ;
          }
        if (!error) {
          DictEntry de;
          de.Version = 1 ;
          de.VOffset = sizeof(hdn) ;
          de.VSize = Size ;
          if (Comment != NULL) {
            de.COffset = sizeof(hdn) + Size ;
            de.CSize = CommentSize + revSize ;
            }
          else {
            de.COffset = sizeof(hdn) + Size ;
            de.CSize = revSize ;
            }
          if (_lwrite (f,LPSTR (&de),sizeof(de)) != sizeof(de))
            error = TRUE ;
          }
        }
      else
        error = TRUE ;
      }
    }
  if (error) {
    if (!*errmsg)
      wsprintf (errmsg,"%s: Not a valid File",LPSTR(ControlName));
    }

  if (IsValidFile (f))
    _lclose (f);

  return !error ;
  }

BOOL WriteBlock (LPSTR FileName,LPSTR errmsg,LPSTR Comment,int CommentSize)
  {
  OFSTRUCT Of,Of1;
  char ControlName[256];
  HFILE fn = NULL;
  BOOL error = FALSE;
  *errmsg = '\0';

  fn = OpenFile (FileName,&Of1,OF_READ);
  LPSTR res,base = NULL;
  int Size;
  if (IsValidFile(fn)) {
    Size = int (_llseek (fn,0L,SEEK_END));
    _llseek (fn,0L,SEEK_SET);
    res = base = LPSTR (GetGlobMem (Size));
    if (int (_lread (fn,base,Size)) != Size)
      error = TRUE ;
    _lclose (fn);
    }
  else {
    wsprintf (errmsg,"File %s not found",FileName);
    error = TRUE ;
    }

  if (!error)
    GetControlName (ControlName,FileName);


  WriteBlockFromBuffer (res,Size,ControlName,errmsg,Comment,CommentSize,FileName);

  if (base != NULL) {
    FreeGlobMem (base);
    }
#ifdef UEBERLEGT
  if (!error) {
    // File Loeschen
    f = OpenFile (FileName,&Of,OF_DELETE);
    }
#endif
  return !error ;
  }

BOOL Unlock (LPSTR FileName,LPSTR errmsg)
  {
  OFSTRUCT Of;
  char ControlName[256];
  HFILE f = NULL;
  BOOL error = FALSE;
  *errmsg = '\0';

  GetControlName (ControlName,FileName);

  char UserName[CB_LOCKEDBY];
  if (!error) {
    GetEnvironment ("VCSID",UserName,sizeof(UserName));
    if (!*UserName) {
      wsprintf (errmsg,"no VCSID set");
      error = TRUE ;
      }
    }

  GetPut_Hd hd,hdn;
  if (!error) {
    f = OpenFile (ControlName,&Of,OF_READWRITE);
    if (IsValidFile (f)) {
      if (_lread (f,&hd,sizeof(hd)) != sizeof(hd))
        error = TRUE ;
      if (!error) {
        if (ciStrCmp  (hd.LockedBy,UserName) != 0) {
          error = TRUE ;
          wsprintf (errmsg,"no version locked by %s",LPSTR(UserName));
          }
        }
      if (!error) {
        hdn = hd ;
        lmemset (hdn.LockedBy,'\0',sizeof(hdn.LockedBy));
        _llseek (f,0L,SEEK_SET);
        if (_lwrite (f,LPSTR(&hdn),sizeof(hdn)) != sizeof(hdn))
          error = TRUE ;
        }
      }
    }
  if (error) {
    if (!*errmsg)
      wsprintf (errmsg,"%s: Not a valid File",LPSTR(ControlName));
    }

  if (IsValidFile (f))
    _lclose (f);

  return !error ;
  }

LPSTR ReadComment (int FAR &CommentSize)
  {
  LPSTR res = NULL ;
  char InString[256];
  printf ("\r\nEnter Comment\r\n");
  int oldSize = 1;
  BOOL endFound = FALSE ;
  for ( ; (!endFound) ; ) {
    printf (">");
    if (gets (InString) != NULL) {
      if (lstrlen(InString) > 0) {
        int l = lstrlen(InString) + 4;
        LPSTR n = LPSTR(GetGlobMem (oldSize + l));
        if (res != NULL) {
          lmemcpy (n,res,oldSize - 1);
          FreeGlobMem (res);
          }
        lmemcpy (n + oldSize - 1,"$ ",2);
        lstrcpy (n + oldSize + 1,InString);
        lstrcat (n,"\r\n");
        oldSize += l ;
        res = n ;
        }
      else
        endFound = TRUE ;
      }
    else
      endFound = TRUE ;
    }
  CommentSize = oldSize - 1;
  return res ;
  }

LPSTR ReadCommentFromFile (LPSTR FileName,LPSTR errmsg,int FAR &size)
  {
  BOOL error = FALSE ;
  OFSTRUCT Of;
  HFILE f = OpenFile (FileName,&Of,OF_READ);
  LPSTR res = NULL;
  if (!IsValidFile (f))
    error = TRUE ;
  if (!error) {
    size = int(_llseek (f,0L,SEEK_END)) ;
    res = LPSTR (GetGlobMem (size + 3));
    _llseek (f,0L,SEEK_SET);
    if (int(_lread (f,res,size)) != size) {
      error = TRUE ;
      FreeGlobMem (res);
      res = NULL ;
      }
    else {
      res[size] = '\r';
      res[size+1] = '\n';
      res[size+2] = '\0';
      // Ueberpruefen der Syntax
      BOOL needComment = TRUE ;
      for (LPSTR h = res ; ((*h) && (!*errmsg)) ; h++) {
        if (*h == '$') needComment = FALSE ;
        if ((needComment) && 
              (!((*h == ' ') || (*h == '\t') || (*h == '\r') || (*h == '\n'))))
          error = TRUE ;
        if ((*h == '\n') || (*h == '\r')) needComment = TRUE ;
        }
      if (error) {
        lstrcpy (errmsg,"No '$' set in Commentfile !");
        FreeGlobMem (res);
        res = NULL ;
        }
      }
    }
  if ((error) && (!*errmsg))
    lstrcpy (errmsg,"ERROR on Commentfile");

  return res;
  }
#endif

