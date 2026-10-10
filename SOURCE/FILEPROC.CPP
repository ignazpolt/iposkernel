//////////////////////////////////////////////////////////////////////////////
//   Implementierung der Datei-Funktionen fuer den Script-Compiler
//////////////////////////////////////////////////////////////////////////////
//   $Header:   P:/marille/clinicum/rev/fileproc.cpv   1.31   27 Jun 2000 18:40:38   Martin  $
//   $Log:   P:/marille/clinicum/rev/fileproc.cpv  $
// 
//    Rev 1.31   27 Jun 2000 18:40:38   Martin
// WriteToIniFile erweitert (optionaler Parameter Ini-Filename)
// 
//    Rev 1.30   11 Apr 2000 11:59:32   Wolfgang
// 1.) Ein paar ClearlConnections hier und da machen sich auch ganz gut,
//     z.B. bei OpenFileDirect.
// 
//    Rev 1.29   10 Apr 2000 19:02:02   Wolfgang
// 1.) Bei FindFirst/Next lastWrite- statt CreationFileData zurueckgeben.
// 2.) FileDatum in lokale Zeitzone umwandeln.
// 
//    Rev 1.28   04 Feb 2000 19:29:00   Martin
// Rueckgabewert fuer CopyFileTo
// 
//    Rev 1.27   26 Jul 1999 22:16:54   Hannes
//
//    Rev 1.26   29 Jun 1999 18:28:40   Wolfgang
// 1.) ReadLn in Files mit nur LF funktioniert jetzt auch mit genau 1024
//     Zeichen langen Zeilen bzw. Leerzeilen.
//
//    Rev 1.25   12 Apr 1999 12:42:24   Hannes
// '\n' am Beginn eines Buffers...
//
//    Rev 1.24   15 Feb 1999 21:25:58   Martin
// BLOB cache
//
//    Rev 1.23   02 Feb 1999 21:30:06   Hannes
// WindowsEvent
//
//    Rev 1.22   05 Oct 1998 11:54:04   Gerhold
// Vorbereitung auf C6 (Type Casts)
//
//    Rev 1.21   04 May 1998 16:11:44   Hannes
// ReadLine: '\n' als Zeilenende alleine ebenso akzeptiert
//
//    Rev 1.20   02 Apr 1998 18:43:46   Hannes
// WriteFile ... Optional mit Laenge, CreateUniqueFile ... Optional ohne Key
//
//    Rev 1.19   18 Feb 1998 19:27:12   Hannes
// writelndata -> Mit ClearConnection
//
//    Rev 1.18   05 Dec 1997 17:44:40   Hannes
// diverse Verbesserungen
//
//    Rev 1.17   08 Oct 1997 15:14:28   Martin
// ReadLn: String auch am Dateiende mit \0 abschliessen
//
//    Rev 1.16   07 Aug 1997 08:37:54   gerhold
// Readln liest jetzt Strings bis 32 kB
//
//    Rev 1.15   27 May 1997 11:31:06   Hannes
// Fehlerhandling in ExcuteProgram
//
//    Rev 1.14   17 Dec 1996 11:00:22   GERHOLD
// 32 Bit - Umstellung
//
//    Rev 1.13   07 Aug 1996 12:50:00   MARTIN
// AnzVals in WriteScriptLog geaendert
//
//    Rev 1.12   06 Aug 1996 15:05:06   GERHOLD
// findfirst, findnext, splitpath
//
//    Rev 1.11   23 Jul 1996 16:02:18   GERHOLD
// ReameFile ... int Result -> LONG Result
//
//    Rev 1.10   10 Jun 1996 10:07:28   GERHOLD
// pragma pack
//
//    Rev 1.9   29 Apr 1996 08:22:12   MARTIN
// FileSeek
//
//    Rev 1.8   02 Feb 1996 10:36:12   GERHOLD
// 1.Umstellung auf 32 Bit
//
//    Rev 1.7   13 Sep 1995 01:22:30   HANNES
//
//    Rev 1.6   24 Aug 1995 00:19:48   HANNES
// DBWIN_ASSERT
//
//    Rev 1.5   23 May 1995 19:03:00   GERHOLD
// IsHandleValid
//
//    Rev 1.4   20 Mar 1995 11:55:42   HANNES
// Konstantenhanling, RunNmbr...
//
//    Rev 1.3   20 Jan 1995 15:34:12   GERHOLD
// RenameFile, WriteToIniFile
//
//    Rev 1.2   11 Nov 1994 16:19:00   HANNES
// DoWhile
//
//    Rev 1.1   02 Nov 1994 20:26:00   GERHOLD
// DestroyFile, SetFileAttr
//
//    Rev 1.0   31 Oct 1994 17:35:12   GERHOLD
// Initial revision.
//
//////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
//#include <print.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>
#include "dds32.h"
/*
#include <sys\types.h>
#include <sys\stat.h>
*/
#include "dds.hpp"
#include "globmem.h"
#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"
#include "image.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdiChild.hpp"
#include "dllchild.hpp"

//#include "winextra.hpp"
#define NODLL
#define WITHINDDS
//#include "toolbar.hpp"
#include "mdiclien.hpp"
#define MODULENUM 132
#include "winass.hpp"
/*
#include "cfield.hpp"
#include "frmobj.hpp"
#include "multl.hpp"
#include "dds.h"
*/


#pragma pack(1)
struct createunique_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD RelFileName;
  DWORD StartPath;
  DWORD Extention;
  DWORD Key;           // free
  };
#pragma pack()

//---------------------------------------------------------------------------
static BOOL MakeMissingDirs(LPSTR FullFileName, int PathNameLen)
  {
  char PathName[128];
  lstrcpy(PathName, FullFileName);
  LPSTR str = FullFileName + PathNameLen;
  LPSTR pstr = PathName + PathNameLen;
  while (*str) {
    while ((*str != '\0') && (*str != '\\')) *pstr++ = *str++;
    if (*str) {
      *pstr = '\0';
      _mkdir(PathName);
      *pstr++ = *str++;   // backslash verarbeiten
      }
    }
  return TRUE;
  }

//---------------------------------------------------------------------------
BOOL GetDirectories (LPSTR StartPath, LPSTR szPath, LPVOID PatNo)
  {
  char szPath1[9], szPath2[9];
 
  int CRCSum = GetCRC(LPSTR(PatNo), GetBlockSize(PatNo));
  unsigned iPath1 = (unsigned)CRCSum % 255;
  unsigned iPath2 = (unsigned)(CRCSum/13) % 255;
  wsprintf (szPath1, "%05d", iPath1);
  wsprintf (szPath2, "%05d", iPath2);

  lstrcpy (szPath, szPath1);
  lstrcat (szPath, "\\");
  lstrcat (szPath, szPath2);
  lstrcat (szPath, "\\");

//  lstrcat (StartPath, szPath);
 
  char szStartPath[256];
  lstrcpy (szStartPath, StartPath);
  lstrcat (szStartPath, szPath) ;

  DBWIN_ASSERT (lstrlen(StartPath) >= 1);
  return MakeMissingDirs (szStartPath,lstrlen (StartPath)-1);
  }

//---------------------------------------------------------------------------
static BOOL CreateUniqueFileName (LPSTR StartPath,LPSTR AdditionalPath,LPSTR FileName, LPSTR Ext)
  {
  srand(unsigned(LOWORD(GetTickCount())));
  for (int i = 0; i < 8; i++)
    FileName[i] = char(rand() % 26) + 'A';
  FileName[8] = '.';
  FileName[9] = '\0';
 
  lstrcat (FileName, Ext);

  char fullName[255];
  lstrcpy (fullName,StartPath);
  lstrcat (fullName,AdditionalPath);
  lstrcat (fullName,FileName);

  OFSTRUCT Of;
  int fi = OpenFile (fullName,&Of,OF_EXIST);
  return (fi <= 0) ;
  }


//---------------------------------------------------------------------------
BOOL CreateUniqueFile (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    createunique_param FAR *par = (createunique_param FAR *) param;

    LPSTR StartPath = LPSTR(c->ReadlData (par->StartPath));
    DBWIN_ASSERT_TEXT (StartPath != NULL,"Startpfad existiert nicht");
    LPSTR Extention = LPSTR(c->ReadlData (par->Extention));
    DBWIN_ASSERT (StartPath != NULL);
    LPSTR Key;
    if (par->parSize >= sizeof(*par)) {
      Key = LPSTR(c->ReadlData (par->Key));
      DBWIN_ASSERT (Key != NULL);
      }
    else
      Key = NULL;

    char AdditionalPath[33];
    char UniqueFileName[13];
    char RelFileName[40];
    char FullFileName[255];

    if (Key != NULL)
      GetDirectories (StartPath, AdditionalPath, Key);
    else
      *AdditionalPath = '\0' ;
 
    for ( int i = 0 ; i < 100 ; i++) {
      if (CreateUniqueFileName (StartPath, AdditionalPath, UniqueFileName, Extention))
        break ;
      }
    DBWIN_ASSERT (i < 100) ;
 
    lstrcpy (RelFileName, AdditionalPath);
    lstrcat (RelFileName, UniqueFileName);

    c->WritelData (par->RelFileName,RelFileName,lstrlen(RelFileName)+1, LPSTR(param)-sizeof(WORD));

    lstrcpy (FullFileName, StartPath);
    lstrcat (FullFileName, RelFileName);
    OFSTRUCT of;
    HFILE hFile = OpenFile (FullFileName, &of, OF_CREATE);
//    DBWIN_ASSERT (hFile != HFILE_ERROR)

    c->WritelData (par->FileHandle, &hFile, sizeof(hFile), LPSTR(param)-sizeof(WORD));
    }
 
  if (mode & (EM_CLEAR | EM_RESET)) {
    createunique_param FAR *par = (createunique_param FAR *) param;
    c->ClearlConnection (par->StartPath,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Extention,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Key,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct openfile_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD FileName;
  DWORD rMode;
  };
#pragma pack()

BOOL OpenFileDirect (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    openfile_param FAR *par = (openfile_param FAR *) param;

    OFSTRUCT of;
 
    // Referenz auf den Datenamen
    LPSTR FileName = LPSTR(c->ReadlData (par->FileName));
 
    HFILE hFile = OpenFile (FileName, &of, c->ReadConstInt(par->rMode));
//    DBWIN_ASSERT (hFile != HFILE_ERROR)

    c->WritelData (par->FileHandle, &hFile, sizeof(hFile), LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    openfile_param FAR *par = (openfile_param FAR *) param;
    c->ClearlConnection (par->FileName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rMode,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }
 
//----------------------------------------------------------------------------
#pragma pack(1)
struct closefile_param {
  WORD  parSize;
  DWORD FileHandle;
  };
#pragma pack()
 
BOOL CloseFile (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    closefile_param FAR *par = (closefile_param FAR *) param;
 
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile));

    HFILE CloseRes = _lclose (*lphFile);
    }
 
  return FALSE;
  }


//------------------------  IsFileValid  -------------------------------------
//
// Prueft ob das uebergebene Datei-Handle gueltig ist.
// soll nach jedem CreatUniqueFile od. OpenFileDirect aufgerufen werden.
//----------------------------------------------------------------------------
#pragma pack(1)
struct ishandlevalid_param {
  WORD  parSize;
  DWORD FileHandle;
  };
#pragma pack()

BOOL IsHandleValid (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    ishandlevalid_param FAR *par = (ishandlevalid_param FAR *) param;

    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    return ((lphFile != NULL) && (*lphFile != -1));
    }
 
  return FALSE;
  }

 
//----------------------------------------------------------------------------
#pragma pack(1)
struct writetofile_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD Data;
  DWORD Size;
  };
#pragma pack()
 
BOOL WriteToFile (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    writetofile_param FAR *par = (writetofile_param FAR *) param;
 
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;

    LPVOID szBuf = c->ReadlData (par->Data);
    if (szBuf != NULL) {
      UINT BufLen;
      if (par->parSize >= sizeof(*par)) {
        DBINT FAR * lpLen = (DBINT FAR *) c->ReadlData (par->Size);
        if (lpLen != NULL) BufLen = *lpLen;
        else               BufLen = GetBlockSize (szBuf);
        }
      else
        BufLen = GetBlockSize(szBuf);

  #ifdef WIN32
      _lwrite (HFILE(*lphFile), LPSTR(szBuf), BufLen);
  #else
      _lwrite (HFILE(*lphFile), szBuf, BufLen);
  #endif
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    writetofile_param FAR *par = (writetofile_param FAR *) param;
    c->ClearlConnection (par->Data,LPSTR(param)-sizeof(WORD));
    if (par->parSize >= sizeof(*par))
      c->ClearlConnection (par->Size,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

//----------------------------------------------------------------------------
//   SEEK_SET ... Beginning of file                  0
//   SEEK_CUR ... Current position of file pointer   1
//   SEEK_END ... End of file                        2
//----------------------------------------------------------------------------
#pragma pack(1)
struct readln_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD Buf;
  };
#pragma pack()

BOOL ReadLn (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    readln_param FAR *par = (readln_param FAR *) param;
    LPSTR LineBuffer;                // Ergebnisstring

    char ReadBuffer[1024];           // Lese-Buffer
 
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile));
 
    DWORD fOffs = _llseek (*lphFile,0L,SEEK_CUR);

    int noffs = 0 ;
    int BufferLen = 0;
    int cRead;

    BOOL bCRFound = FALSE;

    HGLOBAL hglbLine = GlobalAlloc (GHND, 0x7FFF);
    LineBuffer = LPSTR(GlobalLock(hglbLine));
    LPSTR BufferOffs = LineBuffer;              // Offset im Ergebnisstring

    //------------------------------------------------------------
    // Liest solange aus der Datei, bis ein CR gefunden, oder das
    // Ende der Datei erreicht wurde
    //------------------------------------------------------------
    for ( ; !bCRFound ; ) {
      int i = 0;
      cRead = _lread (*lphFile, ReadBuffer, sizeof(ReadBuffer));
      if (cRead > 0) {
        for (LPSTR h = ReadBuffer ; i < cRead ; i++ , h++) {
          if (*h == '\r') {     // CR-LF oder nur CR
            *h++ = '\0' ;
            i++;
            CHAR nextChar;
            if (i < sizeof(ReadBuffer))
              nextChar = *h;
            else {
              // So ein Pech, die Zeile endete genau an der Buffergrenze,
              // daher brauchen wir noch das naechste Zeichen um auf LF
              // zu pruefen.
              cRead = _lread (*lphFile, &nextChar, 1);
              if (cRead <= 0)
                nextChar = '\0';
              }
            if (nextChar == '\n') // CR-LF
              noffs = 1;

            bCRFound = TRUE;
            break ;
            }
          if (*h == '\n') { // nur LF
            *h++ = '\0' ;
            i++;
            bCRFound = TRUE;
            break ;
            }
          }
        DBWIN_ASSERT (BufferLen + i < 0x7FFE);    // Zeile zu lang!
        lmemcpy (BufferOffs, ReadBuffer, i);
        BufferOffs += i;
        BufferLen += i;
        fOffs = _llseek (*lphFile, DWORD(fOffs)+DWORD(i)+DWORD(noffs), SEEK_SET);
        }
      else {
        if (BufferLen > 0) {
          *BufferOffs++ = '\0';
          BufferLen += 1;
          }
        break;
        }
      }

    if (BufferLen > 0)
      c->WritelData (par->Buf, LineBuffer, BufferLen, LPSTR(param)-sizeof(WORD));
    else
      c->DellData (par->Buf, LPSTR(param)-sizeof(WORD));

    GlobalUnlock (hglbLine);
    GlobalFree (hglbLine);
    }

  return FALSE;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct FAR readbinary_param {
  WORD  parSize;
  DWORD FileHandle;
  struct {
    DWORD rsize;
    DWORD Data;
    } block[1];

  int AnzBlocks () {
    return ((parSize - (sizeof(*this) - sizeof(block[0]))) / sizeof(block[0])) ;
    }

  };
#pragma pack()

BOOL ReadBinary (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    readbinary_param FAR *par = (readbinary_param FAR *) param;
 
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;

    int AnzBlk = par->AnzBlocks();
    int BlockLen;
    LPBYTE lpBuf;
    DWORD fOffs;

    fOffs = _llseek (*lphFile, 0L, SEEK_CUR);
    for (int i = 0; i < AnzBlk; i++) {
      BlockLen = c->ReadConstInt (par->block[i].rsize);
      lpBuf = (LPBYTE)GetGlobMem (BlockLen);
 
      int cRead = _lread (*lphFile, lpBuf, BlockLen);

      fOffs = _llseek (*lphFile, DWORD(fOffs) + BlockLen, SEEK_SET);
 
      if (cRead > 0)
        c->WritelData (par->block[i].Data, lpBuf, cRead, LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->block[i].Data, LPSTR(param)-sizeof(WORD));
      FreeGlobMem (lpBuf);
      }
    }
  return FALSE;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct FAR writeln_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD String[1];

  int AnzStrings () {
    return ((parSize - (sizeof(*this) - sizeof(String[0]))) / sizeof(String[0])) ;
    }
  };
#pragma pack()

BOOL WriteLn (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    writeln_param FAR *par = (writeln_param FAR *) param;

    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;

    int AnzStr = par->AnzStrings();
 
    DWORD fOffs = _llseek (*lphFile, 0L, SEEK_CUR);
    for (int i = 0; i < AnzStr; i++) {
      LPSTR str = (LPSTR)c->ReadlData (par->String[i]);
 
      int len;
      if (str != NULL)
        len = lstrlen(str);
      else
        len = 0;
      LPSTR n = LPSTR(GetGlobMem(len+3));
      if (str != NULL) lmemcpy (n, str, len);    // ohne '\0'
      n[len] = '\r';
      n[++len] = '\n';
      n[++len] = '\0';
 
      len = lstrlen(n);
      int cWrite = _lwrite (*lphFile, n, len);
 
      FreeGlobMem (n);
      DBWIN_ASSERT (cWrite != HFILE_ERROR);

      fOffs = _llseek (*lphFile, DWORD(fOffs)+DWORD(len), SEEK_SET);
      }

    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    writeln_param FAR *par = (writeln_param FAR *) param;
    int AnzStr = par->AnzStrings();
 
    for (int i = 0; i < AnzStr; i++)
      c->ClearlConnection (par->String[i],LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct copyfileto_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD FileName;
  };
#pragma pack()

#define BUFSIZE 4096

BOOL CopyFileTo (mdiChild *c, LPVOID param, WORD mode)
  {
  BOOL res = TRUE;
  if (mode & EM_LOAD) {
    copyfileto_param FAR *par = (copyfileto_param FAR *) param;

    // Dateihandle lesen und auf Gueltigkeit pruefen
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;

    // Datei die kopiert werden soll auf Gueltigkeit pruefen
    OFSTRUCT of;
    LPSTR lpszCopyFile = (LPSTR)c->ReadlData (par->FileName);

    HFILE hReadFile = OpenFile (lpszCopyFile, &of, OF_READ);
    DBWIN_ASSERT (hReadFile != HFILE_ERROR);
 
    if (hReadFile == HFILE_ERROR)
      return FALSE;
 
    // Daten so lange kopieren bis nix mehr geht
    LPBYTE lpBuf;
    UINT cbRead;
    lpBuf = (LPBYTE)GetGlobMem (BUFSIZE);
    do {
      cbRead = _lread(hReadFile, lpBuf, BUFSIZE);
      if (_lwrite (*lphFile, LPSTR(lpBuf), cbRead) != cbRead)
        res = FALSE;
      } while (cbRead != 0);

    if (!FlushFileBuffers(HANDLE(*lphFile)))
      res = FALSE;

    FreeGlobMem (lpBuf);

    _lclose (hReadFile);
    }
 
  if (mode & (EM_CLEAR | EM_RESET)) {
    copyfileto_param FAR *par = (copyfileto_param FAR *) param;
    c->ClearlConnection (par->FileHandle,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->FileName,LPSTR(param)-sizeof(WORD));
    }
  return res;
  }
 

//----------------------------------------------------------------------------
#pragma pack(1)
struct winexec_param {
  WORD  parSize;
  DWORD Program;
  DWORD Parameter;
  };
#pragma pack()

BOOL ExecProgram (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    winexec_param FAR *par = (winexec_param FAR *) param;
 
    LPSTR Program = (LPSTR)c->ReadlData (par->Program);
    LPSTR Parameter = (LPSTR)c->ReadlData (par->Parameter);

    char szCommandLine[255];
    wsprintf (szCommandLine, "%s %s", Program, Parameter);
 
    HCURSOR hCurSave = SetCursor (LoadCursor(NULL, IDC_WAIT));
    UINT res = WinExec (szCommandLine, SW_SHOW);
    SetCursor (hCurSave);
 
    char szErr[30];
    wsprintf (szErr, "WinExec Fehler %u",res);
    DBWIN_ASSERT_TEXT (res >= 32, szErr);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    winexec_param FAR *par = (winexec_param FAR *) param;
    c->ClearlConnection (par->Program,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Parameter,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct destroyfile_param {
  WORD parSize;
  DWORD fName;
  };
#pragma pack()

BOOL DestroyFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    destroyfile_param FAR *par = (destroyfile_param FAR *) param;
    LPSTR fName = LPSTR (c->ReadlData (par->fName));
    if (fName != NULL) {
      OFSTRUCT Of;
      HFILE handle = OpenFile (fName, &Of, OF_DELETE);
      DBWIN_ASSERT (handle != HFILE_ERROR);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    destroyfile_param FAR *par = (destroyfile_param FAR *) param;
    c->ClearlConnection (par->fName,LPSTR(param)-sizeof(WORD));
    }

  return FALSE ;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct setfileattr_param {
  WORD parSize;
  DWORD fName;
  DWORD rAttr;
  };
#pragma pack()

BOOL SetFileAttr (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    setfileattr_param FAR *par = (setfileattr_param FAR *) param;
 
    LPSTR fName = LPSTR (c->ReadlData (par->fName));
    if (fName != NULL) {
      char szfName[256];
      lstrcpy (szfName,fName);
      _chmod (szfName, c->ReadConstInt (par->rAttr));
      }

    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    setfileattr_param FAR *par = (setfileattr_param FAR *) param;
    c->ClearlConnection (par->fName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rAttr,LPSTR(param)-sizeof(WORD));
    }

  return FALSE ;
  }

//----------------------------------------------------------------------------
#pragma pack(1)
struct DoWhile_param {
  WORD parSize;
  DWORD proc;
  DWORD flag;
  };
#pragma pack()

BOOL DoWhile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DoWhile_param FAR *par = (DoWhile_param FAR *) param;
    for ( ; ; ) {
      c->ExCuteProc (par->proc,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->proc,EM_RESET);
      DBBOOL FAR *flag = (DBBOOL FAR *) c->ReadlData (par->flag);
      DBWIN_ASSERT (flag != NULL) ;
      if (*flag) break ;
      }
    }
  return FALSE ;
  }


//------------------------  RenameFile  -------------------------------------
#pragma pack(1)
struct renamefile_param {
  WORD parSize;
  DWORD oldname;
  DWORD newname;
  DWORD result;
  };
#pragma pack()


BOOL RenameFile (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    renamefile_param FAR *par = (renamefile_param FAR *) param;

    char szoldname[256];
    char sznewname[256];

    LPSTR oldname = LPSTR (c->ReadlData (par->oldname));
    LPSTR newname = LPSTR (c->ReadlData (par->newname));
    if ((oldname != NULL) && (newname != NULL)) {
      lstrcpy (szoldname, oldname);
      lstrcpy (sznewname, newname);
      LONG result = (LONG)rename (szoldname, sznewname);
      c->WritelData (par->result, &result, sizeof(result), LPSTR(param)-sizeof(WORD));
      }

    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    renamefile_param FAR *par = (renamefile_param FAR *) param;
    c->ClearlConnection (par->oldname,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->newname,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


//------------------------  WriteToIniFile  ---------------------------------
#pragma pack(1)
struct writetoinifile_param {
  WORD parSize;
  DWORD lpszSection;
  DWORD lpszEntry;
  DWORD lpszString;
  WORD fRec,fId;    // wenn angegeben, Filename des .ini files, free
  };
#pragma pack()

BOOL WriteToIniFile (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    writetoinifile_param FAR *par = (writetoinifile_param FAR *) param;

    LPSTR Section = LPSTR (c->ReadlData (par->lpszSection));
    LPSTR Entry = LPSTR (c->ReadlData (par->lpszEntry));
    LPSTR String = LPSTR (c->ReadlData (par->lpszString));

    LPSTR IniName = NULL;
    if (par->parSize == sizeof(*par))
      IniName = LPSTR (c->ReadData (par->fRec,par->fId));
    if (IniName == NULL)
      IniName = MYINI;

    if ((Section != NULL) && (Entry != NULL) && (String != NULL)) {
      WritePrivateProfileString (Section, Entry, String, IniName);
      }

    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    writetoinifile_param FAR *par = (writetoinifile_param FAR *) param;
    c->ClearlConnection (par->lpszSection,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->lpszEntry,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->lpszString,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

//----------------------------------------------------------------------------
//   SEEK_SET ... Beginning of file                  0
//   SEEK_CUR ... Current position of file pointer   1
//   SEEK_END ... End of file                        2
//----------------------------------------------------------------------------
#pragma pack(1)
struct FileSeek_param {
  WORD  parSize;
  DWORD FileHandle;
  DWORD Offset;
  DWORD SeekMode;
  DWORD NewOffs;
  };
#pragma pack()

BOOL FileSeek (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    FileSeek_param FAR *par = (FileSeek_param FAR *) param;
    HFILE FAR* lphFile = (HFILE FAR *)c->ReadlData (par->FileHandle);
    LPDWORD lpOffset = (LPDWORD)c->ReadlData (par->Offset);
    LPWORD lpSeekMode = (LPWORD)c->ReadlData (par->SeekMode);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile));
    if ((lphFile != NULL) && (lpOffset != NULL) && (lpSeekMode != NULL)) {
      DWORD fOffs = _llseek (*lphFile,*lpOffset,*lpSeekMode);
      c->WritelData (par->NewOffs, &fOffs, sizeof(fOffs), LPSTR(param)-sizeof(WORD));
      }
    else {
      c->DellData (par->NewOffs, LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    FileSeek_param FAR *par = (FileSeek_param FAR *) param;
    c->ClearlConnection (par->FileHandle,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Offset,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->SeekMode,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->NewOffs,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }


//----------------------------------------------------------------------------
#pragma pack(1)
struct findfirst_param {
  WORD  parSize;
  DWORD SearchName;
  DWORD SearchAttrib;
  DWORD FindStruct;
  DWORD Result;
  DWORD FileName;
  DWORD Attrib;
  DWORD Size;
  DWORD Time;
  DWORD Date;
  };
#pragma pack()

#ifdef WIN32
struct _32FF {
  WIN32_FIND_DATA  FileData;
  HANDLE           hSearch;
  };
#endif
BOOL FindFirst (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    findfirst_param FAR *par = (findfirst_param FAR *) param;
    LPSTR SearchName = (LPSTR)c->ReadlData(par->SearchName);

    DBWIN_ASSERT (SearchName != NULL);

    WORD FAR *lpAttrib = (WORD FAR *)c->ReadlData(par->SearchAttrib);

    unsigned SearchAttrib;
    SearchAttrib = lpAttrib != NULL ? *lpAttrib : _A_NORMAL;

    char szSearchName[256];
    lstrcpy (szSearchName, SearchName);

#ifdef WIN32
    _32FF ff;
 
    lmemset (&ff.FileData,'\0',sizeof(ff.FileData));
    ff.hSearch = FindFirstFile (szSearchName, &ff.FileData);

    if (ff.hSearch != INVALID_HANDLE_VALUE) {
      DBINT Result = 0 ;
      c->WritelData (par->Result, &Result, sizeof(Result), LPSTR(param)-sizeof(WORD));
      }

    c->WritelData (par->FindStruct, &ff, sizeof(ff), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->FileName, &ff.FileData.cFileName, lstrlen (ff.FileData.cFileName) + 1, LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 5*sizeof(DWORD)) {
      DBINT rattrib = _A_NORMAL;
      if ((ff.FileData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) == FILE_ATTRIBUTE_NORMAL)
        rattrib = _A_NORMAL;
      if ((ff.FileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY)
        rattrib += _A_RDONLY;
      if ((ff.FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
        rattrib += _A_SUBDIR;
      if ((ff.FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE)
        rattrib += _A_ARCH;
      c->WritelData (par->Attrib, &rattrib, sizeof(rattrib), LPSTR(param)-sizeof(WORD));
      }

    if (par->parSize > sizeof(par->parSize) + 6*sizeof(DWORD)) {
      c->WritelData (par->Size, &ff.FileData.nFileSizeLow, sizeof(ff.FileData.nFileSizeLow), LPSTR(param)-sizeof(WORD));
      }

    if (par->parSize > sizeof(par->parSize) + 7*sizeof(DWORD)) {
      FILETIME localTime;
      FileTimeToLocalFileTime (&ff.FileData.ftLastWriteTime,&localTime);
      SYSTEMTIME syst;
      FileTimeToSystemTime (&localTime,&syst);
      packtime pt;
      pt.hour = UCHAR (syst.wHour);
      pt.minute = UCHAR (syst.wMinute);
      pt.second = UCHAR (syst.wSecond);

      c->WritelData (par->Time, &pt, sizeof(pt), LPSTR(param)-sizeof(WORD));

      if (par->parSize > sizeof(par->parSize) + 8*sizeof(DWORD)) {
        packdate pd;
        pd.year = syst.wYear;
        pd.month = UCHAR (syst.wMonth);
        pd.day = UCHAR (syst.wDay);

        c->WritelData (par->Date, &pd, sizeof(pd), LPSTR(param)-sizeof(WORD));
        }
      }
#else
    _find_t  fileinfo;
    short Result = (short)_dos_findfirst (szSearchName, SearchAttrib, &fileinfo);

    c->WritelData (par->Result, &Result, sizeof(Result), LPSTR(param)-sizeof(WORD));

    c->WritelData (par->FindStruct, &fileinfo, sizeof(fileinfo), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->FileName, &fileinfo.name, sizeof(fileinfo.name), LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 5*sizeof(DWORD))
      c->WritelData (par->Attrib, &fileinfo.attrib, sizeof(fileinfo.attrib), LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 6*sizeof(DWORD))
      c->WritelData (par->Size, &fileinfo.size, sizeof(fileinfo.size), LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 7*sizeof(DWORD)) {
      packtime pt;
      pt.hour = (fileinfo.wr_time && 0xF800) >> 11;
      pt.minute = (fileinfo.wr_time && 0x07E0) >> 5;
      pt.second = (fileinfo.wr_time && 0x001F);

      c->WritelData (par->Time, &pt, sizeof(pt), LPSTR(param)-sizeof(WORD));
      }

    if (par->parSize > sizeof(par->parSize) + 8*sizeof(DWORD)) {
      packdate pd;
      pd.year = ((fileinfo.wr_date && 0xFF00) >> 8) + 1980;
      pd.month = (fileinfo.wr_date && 0x00E0) >> 5;
      pd.day = (fileinfo.wr_date && 0x001F);

      c->WritelData (par->Date, &pd, sizeof(pd), LPSTR(param)-sizeof(WORD));
      }
#endif
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    findfirst_param FAR *par = (findfirst_param FAR *) param;
    c->ClearlConnection (par->SearchName,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->SearchAttrib,LPSTR(param)-sizeof(WORD));
    }
  return FALSE;
  }



//----------------------------------------------------------------------------
#pragma pack(1)
struct findnext_param {
  WORD  parSize;
  DWORD FindStruct;
  DWORD Result;
  DWORD FileName;
  DWORD Attrib;
  DWORD Size;
  DWORD Time;
  DWORD Date;
  };
#pragma pack()

BOOL FindNext (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    findnext_param FAR *par = (findnext_param FAR *) param;
#ifdef WIN32
    _32FF FAR *ff = (_32FF FAR *) c->ReadlData (par->FindStruct);
    DBWIN_ASSERT (ff != NULL);
    if (FindNextFile (ff->hSearch,&ff->FileData)) {
      DBINT Result = 0 ;
      c->WritelData (par->Result, &Result, sizeof(Result), LPSTR(param)-sizeof(WORD));

      c->WritelData (par->FileName, &ff->FileData.cFileName, lstrlen (ff->FileData.cFileName) + 1, LPSTR(param)-sizeof(WORD));

      if (par->parSize > sizeof(par->parSize) + 3*sizeof(DWORD)) {
        DBINT rattrib = _A_NORMAL;
        if ((ff->FileData.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) == FILE_ATTRIBUTE_NORMAL)
          rattrib = _A_NORMAL;
        if ((ff->FileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY) == FILE_ATTRIBUTE_READONLY)
          rattrib += _A_RDONLY;
        if ((ff->FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
          rattrib += _A_SUBDIR;
        if ((ff->FileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) == FILE_ATTRIBUTE_ARCHIVE)
          rattrib += _A_ARCH;
        c->WritelData (par->Attrib, &rattrib, sizeof(rattrib), LPSTR(param)-sizeof(WORD));
        }

      if (par->parSize > sizeof(par->parSize) + 4*sizeof(DWORD)) {
        c->WritelData (par->Size, &ff->FileData.nFileSizeLow, sizeof(ff->FileData.nFileSizeLow), LPSTR(param)-sizeof(WORD));
        }

      if (par->parSize > sizeof(par->parSize) + 5*sizeof(DWORD)) {
        FILETIME localTime;
        FileTimeToLocalFileTime (&ff->FileData.ftLastWriteTime,&localTime);
        SYSTEMTIME syst;
        FileTimeToSystemTime (&localTime,&syst);
        packtime pt;
        pt.hour = UCHAR (syst.wHour);
        pt.minute = UCHAR (syst.wMinute);
        pt.second = UCHAR (syst.wSecond);

        c->WritelData (par->Time, &pt, sizeof(pt), LPSTR(param)-sizeof(WORD));

        if (par->parSize > sizeof(par->parSize) + 6*sizeof(DWORD)) {
          packdate pd;
          pd.year = syst.wYear;
          pd.month = UCHAR (syst.wMonth);
          pd.day = UCHAR (syst.wDay);

          c->WritelData (par->Date, &pd, sizeof(pd), LPSTR(param)-sizeof(WORD));
          }
        }
      }
    else {
      FindClose (ff->hSearch);
      c->DellData (par->Result, LPSTR(param)-sizeof(WORD));
      }
#else
    _find_t FAR *lpfileinfo = (_find_t FAR *)c->ReadlData(par->FindStruct);

    DBWIN_ASSERT (lpfileinfo != NULL);

    _find_t fileinfo = *lpfileinfo;

    short Result = (short)_dos_findnext (&fileinfo);
 
    c->WritelData (par->Result, &Result, sizeof(Result), LPSTR(param)-sizeof(WORD));

    c->WritelData (par->FindStruct, &fileinfo, sizeof(fileinfo), LPSTR(param)-sizeof(WORD));
    c->WritelData (par->FileName, &fileinfo.name, sizeof(fileinfo.name), LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 3*sizeof(DWORD))
      c->WritelData (par->Attrib, &fileinfo.attrib, sizeof(fileinfo.attrib), LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 4*sizeof(DWORD))
      c->WritelData (par->Size, &fileinfo.size, sizeof(fileinfo.size), LPSTR(param)-sizeof(WORD));

    if (par->parSize > sizeof(par->parSize) + 5*sizeof(DWORD)) {
      packtime pt;
      pt.hour = (fileinfo.wr_time && 0xF800) >> 11;
      pt.minute = (fileinfo.wr_time && 0x07E0) >> 5;
      pt.second = (fileinfo.wr_time && 0x001F);

      c->WritelData (par->Time, &pt, sizeof(pt), LPSTR(param)-sizeof(WORD));
      }

    if (par->parSize > sizeof(par->parSize) + 6*sizeof(DWORD)) {
      packdate pd;
      pd.year = ((fileinfo.wr_date && 0xFF00) >> 8) + 1980;
      pd.month = (fileinfo.wr_date && 0x00E0) >> 5;
      pd.day = (fileinfo.wr_date && 0x001F);

      c->WritelData (par->Date, &pd, sizeof(pd), LPSTR(param)-sizeof(WORD));
      }
#endif
    }
  return FALSE;
  }


//----------------------------------------------------------------------------
#pragma pack(1)
struct FAR writescriptlog_param {
  WORD  parSize;
  DWORD ScriptText;
  DWORD ScriptMode;
  DWORD ScriptVars[1];
  int AnzVals ()
    { return (int (parSize) - (sizeof(*this) - sizeof(DWORD))) / sizeof(DWORD) ; }
  };
#pragma pack()


BOOL WriteScriptLog (mdiChild *c, LPVOID param, WORD mode)
  {
  static DWORD OldTick = GetTickCount();

  writescriptlog_param FAR *par = (writescriptlog_param FAR *) param;
  WORD FAR *lpScriptMode = (WORD FAR *)c->ReadlData(par->ScriptMode);

  DBWIN_ASSERT (lpScriptMode != NULL);

  if (mode & *lpScriptMode) {
    OFSTRUCT of;

    HFILE LogFile = OpenFile ("SCRIPT.LOG", &of, OF_EXIST);
    UINT OpenMode = LogFile != HFILE_ERROR ? OF_WRITE : OF_CREATE;

    LogFile = OpenFile ("SCRIPT.LOG", &of, OpenMode);
    if (LogFile != HFILE_ERROR) {
      //------------------------------------------------
      // an das Ende der Datei positionieren (== APPEND)
      //------------------------------------------------
      if (_llseek (LogFile, 0, 2) != HFILE_ERROR) {

        char szFileBuf[512];    // String der in die Datei geschrieben wird

        //------------------------------------------------
        // Zeitintervall zwischen den Aufrufen berechnen
        //------------------------------------------------
        DWORD CurrentTick = GetTickCount();
        DWORD DeltaTick = CurrentTick - OldTick;

        char szTimeStamp[30];
        wsprintf (szTimeStamp, "%10lu  %10lu ... ", DeltaTick, CurrentTick);

//        wsprintf (szFileBuf, "%30s", szTimeStamp);
        lstrcpy (szFileBuf, szTimeStamp);   // timestamp in den Dateibuffer

        //-------------------------------------------------------
        // Modus mit dem dieser Befehl aufgerufen wurde bestimmen
        //-------------------------------------------------------
        char szMode[128];
        lstrcpy (szMode, "Mode: ");

        if (mode & EM_LOAD)
          lstrcat (szMode, "EM_LOAD ");
        if (mode & EM_FIXCONNECTION)
          lstrcat (szMode, "EM_FIXCONNECTION ");
        if (mode & EM_UPDATE)
          lstrcat (szMode, "EM_UPDATE ");
        if (mode & EM_SAVE)
          lstrcat (szMode, "EM_SAVE ");
        if (mode & EM_CLEAR)
          lstrcat (szMode, "EM_CLEAR ");
        if (mode & EM_CHANGETOTRUE)
          lstrcat (szMode, "EM_CHANGETOTRUE ");
        if (mode & EM_CHANGETOFALSE)
          lstrcat (szMode, "EM_CHANGETOFALSE ");
        if (mode & EM_PAINT)
          lstrcat (szMode, "EM_PAINT ");
        if (mode & EM_RESET)
          lstrcat (szMode, "EM_RESET ");

        lstrcat (szFileBuf, szMode);   // Aufruf-Modus in den Dateibuffer

        //-----------------------------------------
        // Text der vom Script aus uebergeben wird
        //-----------------------------------------
        LPSTR lpText = (LPSTR)c->ReadlData (par->ScriptText);
        if (lpText != NULL) {
          lstrcat (szFileBuf, "  ");
          lstrcat (szFileBuf, lpText);
          }

        lstrcat (szFileBuf, "\r\n");  // den Text mit CR-LF abschliesen

        if (_lwrite (LogFile, szFileBuf, lstrlen(szFileBuf)) == HFILE_ERROR) {
          }

        _lclose (LogFile);
        }
      }

    OldTick = GetTickCount();
    }

  if (mode & EM_FIXCONNECTION) {
    for (int i = 0 ; i < par->AnzVals() ; i++)
      c->SetlConnection (par->ScriptVars[i],LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    c->ClearlConnection (par->ScriptText,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->ScriptMode,LPSTR(param)-sizeof(WORD));
    for (int i = 0 ; i < par->AnzVals() ; i++)
      c->ClearlConnection (par->ScriptVars[i],LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct WindowsEvent_param {
  WORD parSize;
  DWORD evName;
  DWORD procID;
  };
#pragma pack()

BOOL WindowsEvent (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WindowsEvent_param FAR * par = (WindowsEvent_param FAR *) param;
    LPSTR Name = LPSTR (c->ReadlData (par->evName));
    HANDLE hd = OpenEvent (EVENT_ALL_ACCESS,TRUE,Name);
    if (hd) {
      SetEvent (hd);
      CloseHandle (hd);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    WindowsEvent_param FAR * par = (WindowsEvent_param FAR *) param;
    c->ClearlConnection (par->evName,LPSTR(param) - sizeof(WORD));
    }
  return FALSE;
  }

BOOL WaitForSingleObject (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    WindowsEvent_param FAR * par = (WindowsEvent_param FAR *) param;
    LPSTR Name = LPSTR (c->ReadlData (par->evName));
    HANDLE hd = OpenEvent (EVENT_ALL_ACCESS,TRUE,Name);
    HANDLE procID;
    if (par->parSize >= sizeof(*par)) {
      HANDLE *lpprocID = (HANDLE *) c->ReadlData (par->procID);
      if (lpprocID)
        procID = *lpprocID;
      else
        procID = NULL;
      }
    else
      procID = NULL;

    DWORD dt ;
    if (procID)
      dt = 1000L;
    else
      dt = INFINITE;

    if (hd) {
      for ( ; ; ) {
        long res = WaitForSingleObject (hd,dt);
        if (res == WAIT_TIMEOUT) {
          DWORD code;
          if (GetExitCodeProcess (procID,&code)) {
            if (code != STILL_ACTIVE) break ;
            }
          else {
            DWORD error = GetLastError ();
            LPVOID lpMsgBuf;
 
            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL
            );

            //char text[32];
            //wsprintf (text,"%lX",error);
            DBWIN_ASSERT_TEXT (FALSE,LPSTR (lpMsgBuf));
            }
          }
        else
          break ;
        }
      CloseHandle (hd);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    WindowsEvent_param FAR * par = (WindowsEvent_param FAR *) param;
    c->ClearlConnection (par->evName,LPSTR(param) - sizeof(WORD));
    }
  return FALSE;
  }

#pragma pack(1)
struct CreateDir_param {
  WORD parSize;
  DWORD Directory;
  };
#pragma pack()

BOOL CreateDir (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    CreateDir_param FAR * par = (CreateDir_param FAR *) param;
    LPSTR Name = LPSTR (c->ReadlData (par->Directory));
    CreateDirectory(Name,NULL);
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CreateDir_param FAR * par = (CreateDir_param FAR *) param;
    c->ClearlConnection (par->Directory,LPSTR(param) - sizeof(WORD));
    }
  return FALSE;
  }

#pragma pack(1)
struct Wait_param {
  WORD parSize;
  DWORD msec;
  };
#pragma pack()

BOOL Wait (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    Wait_param FAR * par = (Wait_param FAR *) param;
    LPDWORD lpmsec = LPDWORD (c->ReadlData (par->msec));
    if (lpmsec != NULL) {
      DWORD starttime = GetTickCount();
      while ((GetTickCount() - starttime) < *lpmsec);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    Wait_param FAR * par = (Wait_param FAR *) param;
    c->ClearlConnection (par->msec,LPSTR(param) - sizeof(WORD));
    }
  return FALSE;
  }

