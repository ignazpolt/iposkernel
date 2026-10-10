///////////////////////////////////////////////////////////
//  Resourcenverwaltung mit Hilfe der Btrieve - Datei
///////////////////////////////////////////////////////////
//
// $Header:   P:/marille/clinicum/dbbtrv/rev/rsbtrv.cpv   1.16   18 Feb 1999 14:00:30   Martin  $
// $Log:   P:/marille/clinicum/dbbtrv/rev/rsbtrv.cpv  $
// 
//    Rev 1.16   18 Feb 1999 14:00:30   Martin
// BeginTransaction hat jetzt eine Auswirkung
// 
//    Rev 1.15   13 Oct 1998 17:56:26   Gerhold
// VC6  HANDLE - >HLIBINST
// 
//    Rev 1.14   27 Apr 1998 11:10:28   Hannes
// Begintransaction vor dem rosa Schirm
// 
//    Rev 1.13   15 Dec 1997 17:57:26   Hannes
// WIN_ASSERT->DBWIN_ASSERT
// 
//    Rev 1.12   12 Sep 1996 23:11:56   HANNES
// Naechste Korrektur am OpenMode
// 
//    Rev 1.11   03 Sep 1996 10:07:02   HANNES
// ResOpenMode public gemacht
// 
//    Rev 1.10   02 Feb 1996 10:42:32   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.8   26 Jun 1995 10:22:50   GERHOLD
// Laufende-Nummer bei Bitmaps von 0 auf 0xFFFF gesetzt.
// 
//    Rev 1.7   16 Feb 1995 12:46:16   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.6   29 Jan 1995 11:45:14   HANNES
// 
//    Rev 1.5   10 Jan 1995 15:00:10   HANNES
// Fehlerkorrektur in ClearRow
// 
//    Rev 1.4   07 Dec 1994 15:02:46   GERHOLD
// 
//    Rev 1.3   07 Nov 1994 11:43:14   HANNES
// 
//    Rev 1.2   08 Sep 1994 10:26:40   HANNES
// Buffer etwas vergroessert, damit das lokale btrieve Funktioniert
// ... (Btrieve Fehler)
// 
//    Rev 1.1   24 Aug 1994 19:41:50   HANNES
// Aenderungen im Scriptheader
// 
//    Rev 1.0   24 Jun 1994 16:43:26   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   18 Apr 1994 20:42:16   HANNES
// Erste Fehler
// 
//    Rev 1.0   18 Apr 1994 20:16:26   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "rsbtrv.hpp"
#include "globmem.h"
#include "btrieve.hpp"
extern "C" {
#include "wbtrv.h"
  }
#define MODULENUM   75
#include "winass.hpp"

#include "scripthd.hpp"
#include "dlladmin.h"
#include "dlladmin.hpp"

#define DATASECTION     "Data"
extern LPSTR WINAPI GetIniName();
extern LPSTR WINAPI makeIni(LPSTR txt);
#define MYINI           makeIni("dbbtrv.ini")
#define MYINID          makeIni("dmw.ini")

#define ASSIGN(A,B) A = B
void lstrncpy (LPSTR res,LPSTR src,int size)
  {
  lmemset (res,'\0',size);
  for (int i = 0 ; i < size - 1 ; i++)
    if (!(*res++ = *src++)) break ;
  *res = '\0';
  }

BOOL hmemcmp (LPVOID c1,LPVOID c2,DWORD cmpSize)
  {
  char huge *h1 = (char huge *) c1;
  char huge *h2 = (char huge *) c2;
  BOOL res = TRUE ;
  for ( DWORD i = 0 ; i < cmpSize ; i++ ) {
    if (*h1++ != *h2++) {
      res = FALSE ;
      break ;
      }
    }
  return res;
  }

static LPSTR MsgStr (int st)
  {
  switch (st) {
    case 1 :
      return "Invalid Operation" ;
    case 2 :
      return "I/O Error" ;
    case 3 :
      return "File not Open" ;
    case 4 :
      return "Key Value not Found" ;
    case 5 :
      return "Duplicate Key Value" ;
    case 6 :
      return "Invalid Key Number" ;
    case 7 :
      return "Different Key Number" ;
    case 8 :
      return "Invalid Positioning" ;
    case 9 :
      return "End of File" ;
    case 10 :
      return "Modifiable Key Value Error" ;
    case 11 :
      return "Invalid File Name" ;
    case 12 :
      return "File not found" ;
    case 13 :
      return "Extended File Error" ;
    case 14 :
      return "Pre-Image Open Error" ;
    case 15 :
      return "Pre-Image I/O Error" ;
    case 16 :
      return "Expansion Error" ;
    case 17 :
      return "Close Error" ;
    case 18 :
      return "Disk Full" ;
    case 19 :
      return "Unrecoverable Error" ;
    case 20 :
      return "Record Manager Inactive" ;
    case 21 :
      return "Key Buffer too short" ;
    case 22 :
      return "Data Buffer Length" ;
    case 23 :
      return "Position Block Length" ;
    case 24 :
      return "Page Size Error" ;
    case 25 :
      return "Create I/O Error" ;
    case 26 :
      return "Number of Keys" ;
    case 27 :
      return "Invalid Key Position" ;
    case 28 :
      return "Invalid Record Length" ;
    case 29 :
      return "Invalid Key Length" ;
    case 30 :
      return "Not a Btrieve File" ;
    case 31 :
      return "File already extended" ;
    case 32 :
      return "Extended I/O Error" ;
    case 34 :
      return "Invalide Extension name" ;
    case 35 :
      return "Directory Error" ;
    case 36 :
      return "Transaction Error" ;
    case 37 :
      return "Transaction is active" ;
    case 38 :
      return "Transaction control file I/O Error" ;
    case 39 :
      return "End/Abort Transaction Error" ;
    case 40 :
      return "Transaction max Files" ;
    case 41 :
      return "Operation not allowed" ;
    case 42 :
      return "Incomplete Accelerated access" ;
    case 43 :
      return "Invalid Record address" ;
    case 44 :
      return "null key path" ;
    case 45 :
      return "inconsistent key flags" ;
    case 46 :
      return "access to file denied" ;
    case 47 :
      return "maximum open files" ;
    case 48 :
      return "invalid alternate sequence definition" ;
    case 49 :
      return "key type error" ;
    case 50 :
      return "owner already set" ;
    case 51 :
      return "Invalid owner" ;
    case 52 :
      return "error writing cache" ;
    case 53 :
      return "invalid interface" ;
    case 54 :
      return "variable page error" ;
    case 55 :
      return "autoincrement error" ;
    case 56 :
      return "incomplete index" ;
    case 57 :
      return "expanded memory error" ;
    case 58 :
      return "compression buffer too short" ;
    case 59 :
      return "file already exists" ;
    case 60 :
      return "reject count reached" ;
    case 61 :
      return "work space too small" ;
    case 62 :
      return "incorrect descriptor" ;
    case 63 :
      return "invalid extended insert buffer" ;
    case 64 :
      return "filter limit reached" ;
    case 65 :
      return "incorrect field offset" ;
    case 74 :
      return "automatic transaction abort" ;
    case 78 :
      return "deadlock detected" ;
    case 80 :
      return "confict" ;
    case 81 :
      return "lock error" ;
    case 82 :
      return "lost position" ;
    case 83 :
      return "read outside transaction" ;
    case 84 :
      return "record locked" ;
    case 85 :
      return "file locked" ;
    case 86 :
      return "file table full" ;
    case 87 :
      return "handle table full" ;
    case 88 :
      return "incompatible mode error" ;
    case 90 :
      return "redirected device table full" ;
    case 91 :
      return "server error" ;
    case 92 :
      return "transaction table full" ;
    case 93 :
      return "incompatible lock type" ;
    case 94 :
      return "permisson error" ;
    case 95 :
      return "session no longer valid" ;
    case 96 :
      return "communications environment error" ;
    case 97 :
      return "data message too small" ;
    case 98 :
      return "internal transaction error" ;
    default :
      return "???";
    }

  }

extern BOOL _export FAR PASCAL InTransaction();
void TestST (int st,LPSTR FileName)
  {
  if (st) {
    char msgstr[256];
    wsprintf (msgstr,"Btrieve Fehler: Datei %s\rFehler %d(%s)",
                    FileName,st,MsgStr(st)
             );
    char answer[32];
    GetPrivateProfileString ("DataBase","Entwicklung","no",
                                answer,sizeof(answer),
                                MYINID
                            );
    if (lstrcmp (answer,"yes") == 0) {
      if (!InTransaction ())
        BeginTransaction (FALSE);
      }
    DBWIN_ASSERT_TEXT (FALSE,msgstr);
    }
  }

GLOBALHANDLE PushBlock (GLOBALHANDLE hGres,DWORD FAR *RecSize,
                        LPVOID buffer,DWORD buffersize
                       )
  {
  if (hGres)
    hGres = GlobalReAlloc (hGres,*RecSize+buffersize,GMEM_MOVEABLE);
  else
    hGres = GlobalAlloc (GMEM_MOVEABLE,*RecSize+buffersize);
  char huge *resBuffer = (char huge *) GlobalLock (hGres);
  hmemcpy (resBuffer+*RecSize,buffer,buffersize);
  *RecSize += buffersize;
  GlobalUnlock (hGres);
  return hGres;
  }

//////////////////////////////////////////////////////////////////
// Klasse ResourceDB :
//    Allgemein verwendete Datenbankfunktionen
//////////////////////////////////////////////////////////////////
class FAR ResourceDB {
 protected :
  BOOL TableIsOpen;
 public :
  char posblock[128];

  virtual LPSTR GetItemName  () { return NULL ; }
  virtual LPSTR GetFileName  () { return NULL ; }
  virtual WORD  HeaderSize   () { return 0 ; }
  virtual WORD  BufferSize   () { return 0 ; }
  virtual WORD  MinBufferSize() { return HeaderSize () ; }
  virtual void GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum) { }
  virtual unsigned char GetKeySize (int KeyNum) { return 0 ; }
  virtual void IncrementLaufendeNummer (LPVOID header) { } 

  void Open ();
  BOOL TestRec (LPVOID FirstHeader,LPVOID buffer);
  GLOBALHANDLE Read (DWORD FAR *RecSize,LPVOID FirstRec,LPVOID key,int keySize,WORD Op,int KeyNum);
  void Put (LPVOID hd,LPVOID buffer,LPVOID BlockData,DWORD BlockSize,WORD KeyNum,BOOL moredata);
  void Update (LPVOID hd,LPVOID BlockData,DWORD BlockSize,WORD KeyNumber);
  void Close ();
  };

class FAR RsDataDict : public ResourceDB {
 public :
  virtual LPSTR GetItemName () 
    { return "DDict" ; }
  virtual LPSTR GetFileName ()
    { return "rsddict.dat" ; }
  virtual WORD HeaderSize ()   
    { return sizeof(rsdata_header) ; }
  virtual WORD  BufferSize  () 
    { return 0x7F00 ; }
  virtual void GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum); 
  virtual unsigned char GetKeySize (int KeyNum);
  virtual void IncrementLaufendeNummer (LPVOID header);
  };

class FAR RsScript : public ResourceDB {
 public :
  virtual LPSTR GetItemName () 
    { return "Script" ; }
  virtual LPSTR GetFileName ()
    { return "rsscript.dat" ; }
  virtual WORD HeaderSize ()   
    { return sizeof(rsscript_header) ; }
  virtual WORD  BufferSize  () 
    { return 0x3000 ; }
  virtual WORD  MinBufferSize() 
    { return sizeof(rsscript_header) + sizeof(ScriptContent_Entry) ; }
  virtual void GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum); 
  virtual unsigned char GetKeySize (int KeyNum);
  virtual void IncrementLaufendeNummer (LPVOID header);
  };

class FAR RsResource : public ResourceDB {
 public :
  virtual LPSTR GetItemName () 
    { return "Resource" ; }
  virtual LPSTR GetFileName ()
    { return "rsres.dat" ; }
  virtual WORD HeaderSize ()   
    { return sizeof(rsres_header) ; }
  virtual WORD  BufferSize  () 
    { return 0x7F00 ; }
  virtual void  GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum); 
  virtual unsigned char GetKeySize (int KeyNum);
  virtual void IncrementLaufendeNummer (LPVOID header);
  };

class FAR RsTemp : public ResourceDB {
 public :
  virtual LPSTR GetItemName () 
    { return "TempData" ; }
  virtual LPSTR GetFileName ()
    { return "rstemp.dat" ; }
  virtual WORD HeaderSize ()   
    { return sizeof(rstmp_header) ; }
  virtual WORD  BufferSize  () 
    { return 0x7F00 ; }
  virtual void  GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum); 
  virtual unsigned char GetKeySize (int KeyNum);
  virtual void IncrementLaufendeNummer (LPVOID header);
  };

/*------------------------------------------------------*/
/*  Virtuelle Funktionen der Klasse RsDataDict          */
/*------------------------------------------------------*/
static void GetKey_Primary (LPRSDHEADER hd,LPVOID Key)
  {
  ASSIGN (((Key_Primary FAR *) Key)->InterneNummer    ,hd->InterneNummer);
  }

static void GetTableKey_Name (LPRSDHEADER hd,LPVOID Key)
  {
  ASSIGN  (((TableKey_Name FAR *) Key)->Type          ,hd->Type);
  lmemcpy (((TableKey_Name FAR *) Key)->dllName       ,hd->dllName,sizeof(hd->dllName));
  lmemcpy (((TableKey_Name FAR *) Key)->TableName     ,hd->TableName,sizeof(hd->TableName));
  ASSIGN  (((TableKey_Name FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

static void GetTableKey_Ident (LPRSDHEADER hd,LPVOID Key)
  {
  ASSIGN  (((TableKey_Ident FAR *) Key)->Type          ,hd->Type);
  lmemcpy (((TableKey_Ident FAR *) Key)->dllName       ,hd->dllName,sizeof(hd->dllName));
  ASSIGN  (((TableKey_Ident FAR *) Key)->TableIdent    ,hd->TableIdent);
  ASSIGN  (((TableKey_Ident FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

static void GetVarKey_Name (LPRSDHEADER hd,LPVOID Key)
  {
  ASSIGN  (((VarKey_Name FAR *) Key)->Type          ,hd->Type);
  lmemcpy (((VarKey_Name FAR *) Key)->dllName       ,hd->dllName,sizeof(hd->dllName));
  ASSIGN  (((VarKey_Name FAR *) Key)->TableIdent    ,hd->TableIdent);
  lmemcpy (((VarKey_Name FAR *) Key)->VarName       ,hd->VarName,sizeof(hd->VarName));
  ASSIGN  (((VarKey_Name FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

static void GetVarKey_Ident (LPRSDHEADER hd,LPVOID Key)
  {
  ASSIGN  (((VarKey_Ident FAR *) Key)->Type          ,hd->Type);
  lmemcpy (((VarKey_Ident FAR *) Key)->dllName       ,hd->dllName,sizeof(hd->dllName));
  ASSIGN  (((VarKey_Ident FAR *) Key)->TableIdent    ,hd->TableIdent);
  ASSIGN  (((VarKey_Ident FAR *) Key)->VarIdent      ,hd->VarIdent);
  ASSIGN  (((VarKey_Ident FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

static void GetKey_Type (LPRSDHEADER hd,LPVOID Key)
  {
  ASSIGN  (((Key_Type FAR *) Key)->Type          ,hd->Type);
  lmemcpy (((Key_Type FAR *) Key)->dllName       ,hd->dllName,sizeof(hd->dllName));
  ASSIGN  (((Key_Type FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

typedef void (* GETDKEY) (LPRSDHEADER hd,LPVOID Key);
static GETDKEY DDGetKeyFromHeader [6] = {
  GetKey_Primary    ,
  GetTableKey_Name  ,
  GetTableKey_Ident ,
  GetVarKey_Name    ,
  GetVarKey_Ident   ,
  GetKey_Type
  };

static unsigned char DDKeySize[6] = {
  sizeof (Key_Primary)    ,
  sizeof (TableKey_Name)  ,
  sizeof (TableKey_Ident) ,
  sizeof (VarKey_Name)    ,
  sizeof (VarKey_Ident)   ,
  sizeof (Key_Type)
  };

void RsDataDict::GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum)
  {
  (* (DDGetKeyFromHeader[KeyNum])) (LPRSDHEADER (header),key);
  }

unsigned char RsDataDict::GetKeySize (int KeyNum)
  {
  return DDKeySize [KeyNum];
  }

void RsDataDict::IncrementLaufendeNummer (LPVOID header)
  {
  ((LPRSDHEADER)header)->LaufendeNummer ++ ;
  }

/*------------------------------------------------------*/
/*  Virtuelle Funktionen der Klasse RsScript            */
/*------------------------------------------------------*/
void GetKey_SPrimary (LPRSSHEADER hd,LPVOID Key)
  {
  ASSIGN (((Key_SPrimary FAR *) Key)->InterneNummer,hd->InterneNummer);
  }

void GetKey_DocName (LPRSSHEADER hd,LPVOID Key)
  {
  ASSIGN   (((Key_DocName FAR *) Key)->Type          ,hd->Type);
  lstrncpy (((Key_DocName FAR *) Key)->DocumentName  ,hd->DocumentName,sizeof(hd->DocumentName));
  ASSIGN   (((Key_DocName FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

typedef void (* GETSKEY) (LPRSSHEADER hd,LPVOID Key);
static GETSKEY DSGetKeyFromHeader [2] = {
  GetKey_SPrimary ,
  GetKey_DocName
  };
static unsigned char DSKeySize[2] = {
  sizeof (Key_SPrimary) ,
  sizeof (Key_DocName)
  };

void RsScript::GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum)
  {
  (* (DSGetKeyFromHeader[KeyNum])) (LPRSSHEADER (header),key);
  }

unsigned char RsScript::GetKeySize (int KeyNum)
  {
  return DSKeySize [KeyNum];
  }

void RsScript::IncrementLaufendeNummer (LPVOID header)
  {
  ((LPRSSHEADER)header)->LaufendeNummer ++ ;
  }

/*------------------------------------------------------*/
/*  Virtuelle Funktionen der Klasse RsResource          */
/*------------------------------------------------------*/
void GetKey_RPrimary (LPRSRHEADER hd,LPVOID Key)
  {
  ASSIGN (((Key_RPrimary FAR *) Key)->InterneNummer,hd->InterneNummer);
  }

void GetKey_ResId (LPRSRHEADER hd,LPVOID Key)
  {
  ASSIGN   (((Key_ResId FAR *) Key)->ResID         ,hd->ResID);
  ASSIGN   (((Key_ResId FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

void GetKey_ResName (LPRSRHEADER hd,LPVOID Key)
  {
  ASSIGN   (((Key_ResName FAR *) Key)->Type         ,hd->Type);
  lstrncpy (((Key_ResName FAR *) Key)->ResName      ,hd->ResName,sizeof(((Key_ResName FAR *) Key)->ResName      ));
  ASSIGN   (((Key_ResName FAR *) Key)->LaufendeNummer,hd->LaufendeNummer);
  }

typedef void (* GETRKEY) (LPRSRHEADER hd,LPVOID Key);
static GETRKEY DRGetKeyFromHeader [3] = {
  GetKey_RPrimary ,
  GetKey_ResId ,
  GetKey_ResName 
  };
static unsigned char DRKeySize[3] = {
  sizeof (Key_RPrimary) ,
  sizeof (Key_ResId) ,
  sizeof (Key_ResName)
  };

void RsResource::GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum)
  {
  (* (DRGetKeyFromHeader[KeyNum])) (LPRSRHEADER (header),key);
  }

unsigned char RsResource::GetKeySize (int KeyNum)
  {
  return DRKeySize [KeyNum];
  }

void RsResource::IncrementLaufendeNummer (LPVOID header)
  {
  ((LPRSRHEADER)header)->LaufendeNummer ++ ;
  }

/*------------------------------------------------------*/
/*  Virtuelle Funktionen der Klasse RsTemp              */
/*------------------------------------------------------*/
void RsTemp::GetKeyFromHeader (LPVOID header,LPVOID key,int KeyNum)
  {
  switch (KeyNum) {
    case 0 :
      *((DWORD FAR *) key) = *((DWORD FAR *) header);
      break ;
    case 1 :
      lmemcpy (key,&((rstmp_header FAR *)header)->Type,sizeof(Key_Tres));
      break ;
    }
  }
unsigned char RsTemp::GetKeySize (int KeyNum)
  {
  return (KeyNum == 0) ? sizeof(Key_TPrimary) : sizeof(Key_Tres) ;
  }
void RsTemp::IncrementLaufendeNummer (LPVOID header)
  {
  ((rstmp_header FAR *) header)->LaufendeNummer++ ;
  }

/*------------------------------------------------------*/
/*  Implementierung der Klasse ResourceDB               */
/*------------------------------------------------------*/

extern HINSTANCE hLibInst;
char ResOpenMode()
  {
  static char om = 1;
#ifdef DEBUG
  om = MODE_NORMAL;
#else
  if (om > 0) {
    static char szModulePath[260];
    GetModuleFileName(hLibInst,szModulePath,sizeof(szModulePath));
    AnsiLowerBuff(szModulePath,lstrlen(szModulePath));
    if (!lstrcmp(szModulePath + lstrlen(szModulePath) - 10,"dbbtrv.dll")) {
      om = -2;
      }
    else if (!lstrcmp(szModulePath + lstrlen(szModulePath) - 11,"dbbtrv1.dll")) {
      om = MODE_NORMAL;
      }
    else {
      WIN_ASSERT_TEXT(FALSE,"falscher Modulname");
      om = MODE_NORMAL;
      }
    }
#endif
  return om;
  }

void ResourceDB::Open ()
  {
  if (!TableIsOpen) {
    char ownerbuffer[128];
    lmemset (ownerbuffer,'\0',sizeof (ownerbuffer));
    unsigned cownerbuffer = sizeof (ownerbuffer);
    char path[256];
    GetPrivateProfileString (DATASECTION,GetItemName(),".\\",
                                path,sizeof(path),
                                MYINI
                            );
    lstrcat (path,GetFileName ());
    int status = BTRCALL (B_OPEN,posblock,ownerbuffer,&cownerbuffer,
                                  path,lstrlen(path)+1,
                                  ResOpenMode());
    TestST (status,GetFileName());
    TableIsOpen = TRUE ;
    }
  }

BOOL ResourceDB::TestRec (LPVOID FirstHeader,LPVOID buffer)
  {
  return lmemcmp (LPSTR(FirstHeader)+sizeof(DWORD),LPSTR(buffer)+sizeof(DWORD),
                  HeaderSize()-sizeof(WORD)-sizeof(DWORD)
                 );
  }

GLOBALHANDLE ResourceDB::Read (DWORD FAR *RecSize,LPVOID FirstRec,LPVOID key,int keySize,WORD Op,int KeyNum)
  {
  LPVOID keyBuffer = GetGlobMem (keySize);
  lmemcpy (keyBuffer,key,keySize);
  unsigned buffersize = BufferSize ();
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,buffersize);
  GLOBALHANDLE hGres = 0;
  LPSTR buffer = LPSTR(GlobalLock (hGtemp));
  *RecSize = 0L;
  int status = BTRCALL (Op,posblock,buffer,&buffersize,
                                LPSTR(keyBuffer),(unsigned char) keySize,char (KeyNum));
  if ((status != REQNOTFOUND) && (status != ENDOFFILE)) {
    TestST (status,GetFileName());

    lmemcpy (FirstRec,buffer,HeaderSize ());

    hGres = PushBlock (hGres,RecSize,buffer + HeaderSize(),
                                     buffersize - HeaderSize ());
    while ( buffersize >= BufferSize() ) {
      buffersize = BufferSize() ;
      status = BTRCALL (B_GETNEXT,posblock,buffer,&buffersize,
                                LPSTR(keyBuffer),(unsigned char) keySize,char (KeyNum));
      if (status != ENDOFFILE) {
        TestST (status,GetFileName());
        if (TestRec (FirstRec,buffer))
          hGres = PushBlock (hGres,RecSize,buffer + MinBufferSize(),
                                           buffersize - MinBufferSize());
        else
          break ;
        }
      else break ;
      } 
    }
  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);
  FreeGlobMem (keyBuffer);
  return hGres;
  }

void ResourceDB::Put (LPVOID hd,LPVOID buffer,LPVOID BlockData,DWORD BlockSize,WORD KeyNum,BOOL moredata)
  {
  // Ermitteln des Schluessels aus dem Header
  ///////////////////////////////////////////
  LPSTR KeyBuffer = LPSTR(GetGlobMem (GetKeySize(KeyNum)));
  GetKeyFromHeader (hd,KeyBuffer,KeyNum);
  unsigned buffersize = BufferSize ();
  int status = BTRCALL (B_GETEQ,posblock,LPSTR(buffer),&buffersize,
                                KeyBuffer,GetKeySize(KeyNum),char (KeyNum));
  // Zusammenbasteln des neuen Records
  unsigned dsize;
  if (moredata)
    dsize = MinBufferSize () - HeaderSize ();
  else
    dsize = 0;
  if (dsize > 0) {
    lmemset (LPSTR(buffer) + HeaderSize(),'\0',dsize);
    }
  // Nun noch die Daten
  hmemcpy (LPSTR(buffer) + HeaderSize () + dsize,BlockData,BlockSize);
  buffersize = HeaderSize() + dsize + unsigned (BlockSize);
  if (status == REQNOTFOUND) {
    // Neuen Block einfuegen
    lmemcpy (buffer,hd,HeaderSize());
    *((DWORD FAR *) (buffer)) = 0L;
    status = BTRCALL (B_INSERT,posblock,LPSTR(buffer),&buffersize,
                               KeyBuffer,GetKeySize(KeyNum),char (KeyNum)
                     );
    TestST(status,GetFileName());
    }
  else {
    // Austauschen
    status = BTRCALL (B_UPDATE,posblock,LPSTR(buffer),&buffersize,
                               KeyBuffer,GetKeySize(KeyNum),char (KeyNum));
    TestST(status,GetFileName());
    }
  FreeGlobMem (KeyBuffer);
  }

void ResourceDB::Update (LPVOID hd,LPVOID BlockData,DWORD BlockSize,WORD KeyNumber)
  {
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,BufferSize()+1);
  LPSTR buffer = LPSTR(GlobalLock (hGtemp));
  
  for ( BOOL first = TRUE ; ; IncrementLaufendeNummer (hd) , first = FALSE ) {
    unsigned hdsize;
    if (first) hdsize = HeaderSize();
    else       hdsize = MinBufferSize();
    DWORD StructSize = min (BufferSize() - hdsize,BlockSize);
    Put (hd,buffer,BlockData,StructSize,KeyNumber,!first);
    BlockData = ((char huge *) BlockData) + StructSize;
    BlockSize -= StructSize;
    if (BlockSize <= 0) break ;
    }
  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);
  }

void ResourceDB::Close ()
  {
  if (TableIsOpen) {
    unsigned buffersize = 0;
    int status = BTRCALL (B_CLOSE,posblock,NULL,&buffersize,
                                  NULL,0,0);
    TestST (status,GetFileName());
    TableIsOpen = FALSE ;
    }
  }


// veschiedene Hilfsfunktionen 
//////////////////////////////////////
#define INTERNNAME "-"
void InsertTableDef (LPRSDHEADER hd,ResourceDB FAR *d,WORD TableIdMin,WORD TableIdMax)
  {
  // Suchen der Nummer
  TableKey_Name tk;
  d->GetKeyFromHeader (hd,&tk,KEY_TABLENAME);
  lstrncpy (tk.dllName   ,INTERNNAME,sizeof(tk.dllName));

  unsigned buffersize = d->BufferSize();
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,d->BufferSize()+1);
  LPSTR buffer = LPSTR(GlobalLock (hGtemp));
  int status = BTRCALL (B_GETEQ,d->posblock,buffer,&buffersize,
                          LPSTR(&tk),sizeof(tk),KEY_TABLENAME
                       );
  if (status == REQNOTFOUND) {
    // Referenzrecord setzen
    /////////////////////////////////
    TableKey_Ident ti;
    d->GetKeyFromHeader (hd,&ti,KEY_TABLEIDENT);
    lstrncpy (ti.dllName   ,INTERNNAME,sizeof(ti.dllName));
    ASSIGN   (ti.TableIdent,TableIdMax);
    buffersize = 0;
    status = BTRCALL (B_GETKEYLE,d->posblock,NULL,&buffersize,
                      LPSTR(&ti),sizeof(ti),KEY_TABLEIDENT
                     );
    if ((status == REQNOTFOUND) || (status == ENDOFFILE) || (lstrcmp (ti.dllName,INTERNNAME) != 0) ||
        (ti.Type != RST_TBDATADICT) || (ti.TableIdent < TableIdMin))
      hd->TableIdent = TableIdMin;
    else
      hd->TableIdent = ti.TableIdent + 1;

    // Einfuegen des Referenzdatensatzes
    ////////////////////////////////////////
    rsdata_header hdtmp;
    hdtmp = *hd ;
    lstrncpy (hdtmp.dllName      ,INTERNNAME,sizeof(hdtmp.dllName));
    ASSIGN   (hdtmp.InterneNummer,0L);
    buffersize = sizeof(hdtmp);
    DWORD interneNummer;
    status = BTRCALL(B_INSERT,d->posblock,LPSTR(&hdtmp),&buffersize,
                              LPSTR(&interneNummer),sizeof(interneNummer),KEY_AUTOINC);
                              
    TestST (status,d->GetFileName());
    }
  else {
    TestST (status,d->GetFileName());
    WIN_ASSERT ((((LPRSDHEADER)buffer)->TableIdent >= TableIdMin) &&
                (((LPRSDHEADER)buffer)->TableIdent <= TableIdMax));
    hd->TableIdent = ((LPRSDHEADER)buffer)->TableIdent;
    }

  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);
  }

void InsertVarDef (LPRSDHEADER hd,ResourceDB FAR *d)
  {
  // Suchen der Nummer
  VarKey_Name tk;
  d->GetKeyFromHeader (hd,&tk,KEY_VARNAME);
  lstrncpy (tk.dllName   ,INTERNNAME,sizeof(tk.dllName));

  unsigned buffersize = d->BufferSize();
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,d->BufferSize()+1);
  LPSTR buffer = LPSTR(GlobalLock (hGtemp));
  int status = BTRCALL (B_GETEQ,d->posblock,buffer,&buffersize,
                          LPSTR(&tk),sizeof(tk),KEY_VARNAME
                       );
  if (status == REQNOTFOUND) {
    // Referenzrecord setzen
    /////////////////////////////////
    VarKey_Ident ti;
    d->GetKeyFromHeader (hd,&ti,KEY_VARIDENT);
    lstrncpy (ti.dllName   ,INTERNNAME,sizeof(ti.dllName));
    ASSIGN   (ti.VarIdent,0xFFFF);
    buffersize = 0;
    status = BTRCALL (B_GETKEYLE,d->posblock,NULL,&buffersize,
                      LPSTR(&ti),sizeof(ti),KEY_VARIDENT
                     );
    if ((status == REQNOTFOUND) || (status == ENDOFFILE) || (lstrcmp (ti.dllName,INTERNNAME) != 0) ||
        (ti.Type != RST_VRDATADICT) || (ti.TableIdent != hd->TableIdent))
      hd->VarIdent = 0;
    else
      hd->VarIdent = ti.VarIdent + 1;

    // Einfuegen des Referenzdatensatzes
    ////////////////////////////////////////
    rsdata_header hdtmp;
    hdtmp = *hd ;
    lstrncpy (hdtmp.dllName      ,INTERNNAME,sizeof(hdtmp.dllName));
    ASSIGN   (hdtmp.InterneNummer,0L);
    buffersize = sizeof(hdtmp);
    DWORD interneNummer;
    status = BTRCALL(B_INSERT,d->posblock,LPSTR(&hdtmp),&buffersize,
                              LPSTR(&interneNummer),sizeof(interneNummer),KEY_AUTOINC);
                              
    TestST (status,d->GetFileName());
    }
  else {
    TestST (status,d->GetFileName());
    hd->VarIdent = ((LPRSDHEADER)buffer)->VarIdent;
    }

  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);
  }

void InsertResDef (LPRSRHEADER hd,ResourceDB FAR *d)
  {
  // Suchen der Nummer
  DWORD interneNummer;

  unsigned buffersize = sizeof(*hd);
  int status = BTRCALL(B_INSERT,d->posblock,LPSTR(hd),&buffersize,
                              LPSTR(&interneNummer),sizeof(interneNummer),KEY_RPRIMARY);
  TestST (status,d->GetFileName());
  hd->InterneNummer = interneNummer;
  hd->ResID         = interneNummer;
  status = BTRCALL(B_UPDATE,d->posblock,LPSTR(hd),&buffersize,
                              LPSTR(&interneNummer),sizeof(interneNummer),KEY_RPRIMARY);
  TestST (status,d->GetFileName());
  }

/*---------------------------------------------------------------------*/
/*  Exportierte Funktionen                                             */
/*---------------------------------------------------------------------*/
static RsDataDict ddict;
static RsScript   dscript;
static RsResource dresource;
static RsTemp     dhlp;
// 
// Setzen der Tabellendefinition. Fr eine 
// Versionsverwaltung ist es n”tig, eine 
// etwailige Žnderung der Definition als 
// Resultat zu erhalten.
// 
DLLExport WORD _export WINAPI DataRes_SetTableDef 
            (LPSTR DLLName,
             LPSTR TableName,
             WORD TableIdMin,WORD TableIdMax,
             LPVOID TableData,DWORD TableSize,
             BOOL FAR *changed
            )
  {
  ddict.Open ();

  // Versuch, die Definition zu lesen
  TableKey_Name key;
  ASSIGN   (key.Type          ,RST_TBDATADICT);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  lstrncpy (key.TableName     ,TableName,sizeof(key.TableName));
  ASSIGN   (key.LaufendeNummer,0);

  DWORD RecSize;
  rsdata_header hd,hdold;
  GLOBALHANDLE hGres = ddict.Read (&RecSize,&hdold,&key,sizeof(key),B_GETEQ,KEY_TABLENAME);

  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.Type          ,RST_TBDATADICT);
  lstrncpy (hd.dllName       ,DLLName,sizeof(hd.dllName));
  lstrncpy (hd.TableName     ,TableName,sizeof(hd.TableName));
  ASSIGN   (hd.TableIdent    ,0);
  lmemset  (hd.VarName       ,'\0',sizeof(hd.VarName));
  ASSIGN   (hd.VarIdent      ,0);
  ASSIGN   (hd.LaufendeNummer,0);

  WORD res;

  if (hGres) {
    // Hat geklappt -> Untersuchen, ob sich die Daten geaendert haben
    res = hd.TableIdent = hdold.TableIdent;
    LPVOID oldTableData = GlobalLock (hGres);
    if ((RecSize != TableSize) || (!hmemcmp (oldTableData,TableData,RecSize))) {
      // Update noetig
      *changed = TRUE ;
      ddict.Update (&hd,TableData,TableSize,KEY_TABLENAME);
      }
    else {
      // braucht nix gemacht werden
      *changed = FALSE ;
      }
    GlobalUnlock (hGres);
    GlobalFree (hGres);
    }
  else {
    // Nix gewesen -> Insert noetig
    // Mit diesem die Daten schreiben
    *changed = TRUE ;
    InsertTableDef (&hd,&ddict,TableIdMin,TableIdMax);
    res = hd.TableIdent;
    ddict.Update (&hd,TableData,TableSize,KEY_TABLENAME);
    }
  return res;
  }

//
// Setzen einer Spaltendefinition
//
DLLExport WORD _export WINAPI DataRes_SetRowDef 
            (LPSTR DLLName,
             WORD TableIdent,
             LPSTR VarName,
             LPVOID VarData,DWORD VarSize,
             BOOL FAR *changed
            )
  {
  ddict.Open ();

  // Versuch, die Definition zu lesen
  VarKey_Name key;
  ASSIGN   (key.Type          ,RST_VRDATADICT);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,TableIdent);
  lstrncpy (key.VarName       ,VarName,sizeof(key.VarName));
  ASSIGN   (key.LaufendeNummer,0);

  DWORD RecSize;
  rsdata_header hd,hdold;
  GLOBALHANDLE hGres = ddict.Read (&RecSize,&hdold,&key,sizeof(key),B_GETEQ,KEY_VARNAME);

  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.Type          ,RST_VRDATADICT);
  lstrncpy (hd.dllName       ,DLLName,sizeof(hd.dllName));
  lmemset  (hd.TableName     ,'\0',sizeof(hd.TableName));
  ASSIGN   (hd.TableIdent    ,TableIdent);
  lstrncpy (hd.VarName       ,VarName,sizeof(hd.VarName));
  ASSIGN   (hd.VarIdent      ,0);
  ASSIGN   (hd.LaufendeNummer,0);

  WORD res;

  if (hGres) {
    // Hat geklappt -> Untersuchen, ob sich die Daten geaendert haben
    res = hd.VarIdent = hdold.VarIdent;
    LPVOID oldVarData = GlobalLock (hGres);
    if ((RecSize != VarSize) || (!hmemcmp (oldVarData,VarData,RecSize))) {
      // Update noetig
      *changed = TRUE ;
      ddict.Update (&hd,VarData,VarSize,KEY_VARNAME);
      }
    else {
      // braucht nix gemacht werden
      *changed = FALSE ;
      }
    GlobalUnlock (hGres);
    GlobalFree (hGres);
    }
  else {
    // Nix gewesen -> Insert noetig
    // Mit diesem die Daten schreiben
    *changed = TRUE ;
    InsertVarDef (&hd,&ddict);
    res = hd.VarIdent;
    ddict.Update (&hd,VarData,VarSize,KEY_VARNAME);
    }
  return res;
  }

//
// Lesen der ersten Spaltendefinition
//
DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFirstRowDef 
            (LPSTR DLLName,
             WORD TableIdent,
             LPSTR RowName,
             WORD FAR *RowIdent,
             DWORD FAR *HeaderSize,
             DWORD FAR *RowSize
            )
  {
  ddict.Open ();

  // Versuch, die Definition zu lesen
  VarKey_Ident key;
  ASSIGN   (key.Type          ,RST_VRDATADICT);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,TableIdent);
  ASSIGN   (key.VarIdent      ,0);
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  *RowSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (RowSize,&hd,&key,sizeof(key),B_GETGTE,KEY_VARIDENT);

  if (hGres) {
    if ((hd.Type == RST_VRDATADICT) && (lstrcmp (hd.dllName,DLLName) == 0)
            && (hd.TableIdent == TableIdent)) {
      *RowIdent = hd.VarIdent;
      lstrcpy (RowName,hd.VarName);
      }
    else {
      GlobalFree (hGres);
      hGres = 0;
      }
    }

  *HeaderSize = 0L;
  return hGres;
  }

//
// Lesen der weiteren Spaltendefinitionen
//
DLLExport GLOBALHANDLE _export WINAPI DataRes_GetNextRowDef 
            (LPSTR DLLName,
             WORD TableIdent,
             WORD PrevRow,
             LPSTR RowName,
             WORD FAR *RowIdent,
             DWORD FAR *HeaderSize,
             DWORD FAR *RowSize
            )
  {
  ddict.Open ();

  // Versuch, die Definition zu lesen
  VarKey_Ident key;
  ASSIGN   (key.Type          ,RST_VRDATADICT);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,TableIdent);
  ASSIGN   (key.VarIdent      ,PrevRow);
  ASSIGN   (key.LaufendeNummer,0xFFFF);

  rsdata_header hd;
  *RowSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (RowSize,&hd,&key,sizeof(key),B_GETGT,KEY_VARIDENT);

  if (hGres) {
    if ((hd.Type == RST_VRDATADICT) && (lstrcmp (hd.dllName,DLLName) == 0) 
            && (hd.TableIdent == TableIdent)) {
      *RowIdent = hd.VarIdent;
      lstrcpy (RowName,hd.VarName);
      }
    else {
      GlobalFree (hGres);
      hGres = 0 ;
      }
    }

  *HeaderSize = 0L;
  return hGres;
  }

//
// Speichern der vollen Tabellendefinition
//
DLLExport void _export WINAPI DataRes_SetFullTableDef (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  LPVOID TableData,
                  DWORD TableSize
                                        )
  {
  ddict.Open ();

  rsdata_header hd;
  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.Type          ,RST_TBFDATADICT);
  lstrncpy (hd.dllName       ,DLLName,sizeof(hd.dllName));
  lstrncpy (hd.TableName     ,TableName,sizeof(hd.TableName));
  ASSIGN   (hd.TableIdent    ,TableIdent);
  lmemset  (hd.VarName       ,'\0',sizeof(hd.VarName));
  ASSIGN   (hd.VarIdent      ,0);
  ASSIGN   (hd.LaufendeNummer,0);

  ddict.Update (&hd,TableData,TableSize,KEY_TABLENAME);
  }

// Lesen der Tabellendefinition
DLLExport GLOBALHANDLE _export WINAPI DataRes_GetTableDef (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  DWORD FAR *HeaderSize,
                  DWORD FAR *TableSize
                                        )
  {
  ddict.Open ();

  TableKey_Ident key;
  ASSIGN   (key.Type          ,RST_TBDATADICT);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,TableIdent);
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  *TableSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (TableSize,&hd,&key,sizeof(key),B_GETEQ,KEY_TABLEIDENT);
  if (hGres)
    lstrcpy (TableName,hd.TableName);

  *HeaderSize = 0L;
  return hGres;
  }


//
// Lesen der vollen Tabellendefinition
//
DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFullTableDef (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  DWORD FAR *HeaderSize,
                  DWORD FAR *TableSize
                                        )
  {
  ddict.Open ();

  TableKey_Ident key;
  ASSIGN   (key.Type          ,RST_TBFDATADICT);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,TableIdent);
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  *TableSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (TableSize,&hd,&key,sizeof(key),B_GETEQ,KEY_TABLEIDENT);
  if (hGres)
    lstrcpy (TableName,hd.TableName);

  *HeaderSize = 0L;
  return hGres;
  }


//
// Lesen der ersten Tabellendefinition
//
DLLExport BOOL _export WINAPI DataRes_GetFirstTableDef 
            (WORD FAR *TableIdent,
             LPSTR TableName
            )
  {
  ddict.Open ();

  // Versuch, die Definition zu lesen
  TableKey_Ident key;
  ASSIGN   (key.Type          ,RST_TBDATADICT);
  lstrncpy (key.dllName       ,INTERNNAME,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,0);
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  DWORD RowSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (&RowSize,&hd,&key,sizeof(key),B_GETGTE,KEY_TABLEIDENT);

  BOOL res = FALSE;
  if (hGres) {
    if ((hd.Type == RST_TBDATADICT) && (lstrcmp (hd.dllName,INTERNNAME) == 0)) {
      *TableIdent = hd.TableIdent;
      lstrcpy (TableName,hd.TableName);
      res = TRUE ;
      }
    GlobalFree (hGres);
    }
  return res;
  }

//
// Lesen der weiteren Tabellendefinition
//
DLLExport BOOL _export WINAPI DataRes_GetNextTableDef 
            (WORD PrevIdent,
             WORD FAR *TableIdent,
             LPSTR TableName
            )
  {
  ddict.Open ();

  // Versuch, die Definition zu lesen
  TableKey_Ident key;
  ASSIGN   (key.Type          ,RST_TBDATADICT);
  lstrncpy (key.dllName       ,INTERNNAME,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,PrevIdent);
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  DWORD RowSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (&RowSize,&hd,&key,sizeof(key),B_GETGT,KEY_TABLEIDENT);

  BOOL res = FALSE;
  if (hGres) {
    if ((hd.Type == RST_TBDATADICT) && (lstrcmp (hd.dllName,INTERNNAME) == 0)) {
      *TableIdent = hd.TableIdent;
      lstrcpy (TableName,hd.TableName);
      res = TRUE ;
      }
    GlobalFree (hGres);
    }
  return res;
  }

DLLExport void _export WINAPI DataRes_SetDictCont (LPVOID Data,DWORD DataSize)
  {
  ddict.Open ();

  rsdata_header hd;
  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.Type          ,RST_DDCONT);
  lstrncpy (hd.dllName       ,INTERNNAME,sizeof(hd.dllName));
  lmemset  (hd.TableName     ,'\0',sizeof(hd.TableName));
  ASSIGN   (hd.TableIdent    ,0);
  lmemset  (hd.VarName       ,'\0',sizeof(hd.VarName));
  ASSIGN   (hd.VarIdent      ,0);
  ASSIGN   (hd.LaufendeNummer,0);

  ddict.Update (&hd,Data,DataSize,KEY_TYPE);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetDictCont (
        DWORD FAR *HeaderSize,
        DWORD FAR *DataSize
                                                    )
  {
  ddict.Open ();

  Key_Type key;
  ASSIGN   (key.Type          ,RST_DDCONT);
  lstrncpy (key.dllName       ,INTERNNAME,sizeof(key.dllName));
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  *DataSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (DataSize,&hd,&key,sizeof(key),B_GETEQ,KEY_TYPE);

  *HeaderSize = 0L;
  return hGres;
  }

//  Alle Spaltendefinitionen (auch die Referenznamen) loeschen
DLLExport void _export WINAPI DataRes_ClearRowDefs (LPSTR DLLName,WORD TableIdent)
  {
  ddict.Open ();

  unsigned buffersize = ddict.BufferSize ();
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,buffersize);
  LPSTR buffer = LPSTR(GlobalLock (hGtemp));
  for (int i = 0 ; i < 2 ; i++) {
    for ( ; ; ) {
      VarKey_Ident key;
      ASSIGN   (key.Type          ,RST_VRDATADICT);
      lstrncpy (key.dllName       ,(i == 0) ? INTERNNAME : DLLName,sizeof(key.dllName));
      ASSIGN   (key.TableIdent    ,TableIdent);
      ASSIGN   (key.VarIdent      ,0);
      ASSIGN   (key.LaufendeNummer,0);

      buffersize = ddict.BufferSize ();
      int status = BTRCALL (B_GETGTE,ddict.posblock,buffer,&buffersize,
                                  LPSTR(&key),(unsigned char) sizeof(key),KEY_VARIDENT
                          );
      if ((status == 0) && (key.Type == RST_VRDATADICT) && (key.TableIdent == TableIdent)) {
        status = BTRCALL (B_DELETE,ddict.posblock,NULL,&buffersize,
                                  LPSTR(&key),(unsigned char) sizeof(key),KEY_VARIDENT
                        );
      
        TestST (status,ddict.GetFileName());
        }
      else
        break ;
      }
    }
  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);
  }

DLLExport void _export WINAPI DataRes_DelTableDef (LPSTR DLLName,WORD TableIdent)
  {
  ddict.Open ();

  DataRes_ClearRowDefs (DLLName,TableIdent);

  unsigned buffersize = ddict.BufferSize ();
  GLOBALHANDLE hGtemp = GlobalAlloc (GMEM_MOVEABLE,buffersize);
  LPSTR buffer = LPSTR(GlobalLock (hGtemp));

  // Loeschen der Vollen Tabelledefinition
  for ( ; ; ) {
    TableKey_Ident key;
    ASSIGN   (key.Type          ,RST_TBFDATADICT);
    lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
    ASSIGN   (key.TableIdent    ,TableIdent);
    ASSIGN   (key.LaufendeNummer,0);

    buffersize = ddict.BufferSize ();
    int status = BTRCALL (B_GETGTE,ddict.posblock,buffer,&buffersize,
                                LPSTR(&key),(unsigned char) sizeof(key),KEY_TABLEIDENT
                        );
    if ((status == 0) && (key.Type == RST_TBFDATADICT) && (key.TableIdent == TableIdent)) {
      status = BTRCALL (B_DELETE,ddict.posblock,NULL,&buffersize,
                                LPSTR(&key),(unsigned char) sizeof(key),KEY_TABLEIDENT
                      );
    
      TestST (status,ddict.GetFileName());
      }
    else
      break ;
    }
  // Loeschen der Teiltabelledefinition
  for (int i = 0 ; i < 2 ; i++) {
    for ( ; ; ) {
      TableKey_Ident key;
      ASSIGN   (key.Type          ,RST_TBDATADICT);
      lstrncpy (key.dllName       ,(i == 0) ? INTERNNAME : DLLName,sizeof(key.dllName));
      ASSIGN   (key.TableIdent    ,TableIdent);
      ASSIGN   (key.LaufendeNummer,0);

      buffersize = ddict.BufferSize ();
      int status = BTRCALL (B_GETGTE,ddict.posblock,buffer,&buffersize,
                                  LPSTR(&key),(unsigned char) sizeof(key),KEY_TABLEIDENT
                          );
      if ((status == 0) && (key.Type == RST_TBDATADICT) && (key.TableIdent == TableIdent)) {
        status = BTRCALL (B_DELETE,ddict.posblock,NULL,&buffersize,
                                  LPSTR(&key),(unsigned char) sizeof(key),KEY_TABLEIDENT
                        );
    
        TestST (status,ddict.GetFileName());
        }
      else
        break ;
      }
    }
  // Loeschen der Serverdefinition
  for ( ; ; ) {
    TableKey_Ident key;
    ASSIGN   (key.Type          ,RST_DSERVSRC);
    lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
    ASSIGN   (key.TableIdent    ,TableIdent);
    ASSIGN   (key.LaufendeNummer,0);

    buffersize = ddict.BufferSize ();
    int status = BTRCALL (B_GETGTE,ddict.posblock,buffer,&buffersize,
                                LPSTR(&key),(unsigned char) sizeof(key),KEY_TABLEIDENT
                        );
    if ((status == 0) && (key.Type == RST_DSERVSRC) && (key.TableIdent == TableIdent)) {
      status = BTRCALL (B_DELETE,ddict.posblock,NULL,&buffersize,
                                LPSTR(&key),(unsigned char) sizeof(key),KEY_TABLEIDENT
                      );
    
      TestST (status,ddict.GetFileName());
      }
    else
      break ;
    }

  GlobalUnlock (hGtemp);
  GlobalFree (hGtemp);
  }

//  Den Sourcetext der Serverdefinition schreiben
//////////////////////////////////////////////////////
DLLExport void _export WINAPI DataRes_SetServerSource (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  LPVOID TableData,
                  DWORD TableSize
                                                )
  {
  ddict.Open ();

  rsdata_header hd;
  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.Type          ,RST_DSERVSRC);
  lstrncpy (hd.dllName       ,DLLName,sizeof(hd.dllName));
  lstrncpy (hd.TableName     ,TableName,sizeof(hd.TableName));
  ASSIGN   (hd.TableIdent    ,TableIdent);
  lmemset  (hd.VarName       ,'\0',sizeof(hd.VarName));
  ASSIGN   (hd.VarIdent      ,0);
  ASSIGN   (hd.LaufendeNummer,0);

  ddict.Update (&hd,TableData,TableSize,KEY_TABLENAME);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetServerSource (
                  LPSTR DLLName,
                  WORD TableIdent,
                  LPSTR TableName,
                  DWORD FAR *HeaderSize,
                  DWORD FAR *TableSize
                                        )
  {
  ddict.Open ();

  TableKey_Ident key;
  ASSIGN   (key.Type          ,RST_DSERVSRC);
  lstrncpy (key.dllName       ,DLLName,sizeof(key.dllName));
  ASSIGN   (key.TableIdent    ,TableIdent);
  ASSIGN   (key.LaufendeNummer,0);

  rsdata_header hd;
  *TableSize = 0L;
  GLOBALHANDLE hGres = ddict.Read (TableSize,&hd,&key,sizeof(key),B_GETEQ,KEY_TABLEIDENT);
  if (hGres)
    lstrcpy (TableName,hd.TableName);

  *HeaderSize = 0L;
  return hGres;
  }

DLLExport void _export WINAPI DataRes_SetDocDef (LPSTR DocName,LPVOID DocData,DWORD DataSize)
  {
  dscript.Open ();

  rsscript_header hd;
  ASSIGN   (hd.InterneNummer ,0L);
  ASSIGN   (hd.Type          ,RSS_TYPEDOCDEF);
  lstrncpy (hd.DocumentName  ,DocName,sizeof(hd.DocumentName));
  ASSIGN   (hd.LaufendeNummer,0);

  dscript.Update (&hd,DocData,DataSize,KEY_DOCNAME);
  }

DLLExport void _export WINAPI DataRes_SetFuncDef (LPVOID DocData,DWORD DataSize)
  {
  dscript.Open ();

  rsscript_header hd;
  ASSIGN   (hd.InterneNummer ,0L);
  ASSIGN   (hd.Type          ,RSS_TYPEFNCPROT);
  lstrncpy (hd.DocumentName  ,INTERNNAME,sizeof(hd.DocumentName));
  ASSIGN   (hd.LaufendeNummer,0);

  dscript.Update (&hd,DocData,DataSize,KEY_DOCNAME);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetDocDef (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  dscript.Open ();

  Key_DocName key;
  ASSIGN   (key.Type          ,RSS_TYPEDOCDEF);
  lstrncpy (key.DocumentName  ,DocName,sizeof(key.DocumentName));
  ASSIGN   (key.LaufendeNummer,0);

  rsscript_header hd;
  GLOBALHANDLE hGres = dscript.Read (DocSize,&hd,&key,sizeof(key),B_GETEQ,KEY_DOCNAME);

  *HeaderSize = 0;

  return hGres;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFuncDef (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  dscript.Open ();

  Key_DocName key;
  ASSIGN   (key.Type          ,RSS_TYPEFNCPROT);
  lstrncpy (key.DocumentName  ,INTERNNAME,sizeof(key.DocumentName));
  ASSIGN   (key.LaufendeNummer,0);

  rsscript_header hd;
  GLOBALHANDLE hGres = dscript.Read (DocSize,&hd,&key,sizeof(key),B_GETEQ,KEY_DOCNAME);

  *HeaderSize = 0;

  return hGres;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFirstDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  dscript.Open ();

  Key_DocName key;
  ASSIGN   (key.Type          ,RSS_TYPEDOCDEF);
  lmemset  (key.DocumentName  ,'\0',sizeof(key.DocumentName));
  ASSIGN   (key.LaufendeNummer,0);

  rsscript_header hd;
  GLOBALHANDLE hGres = dscript.Read (DocSize,&hd,&key,sizeof(key),B_GETGTE,KEY_DOCNAME);

  if (hGres) {
    if (hd.Type == RSS_TYPEDOCDEF)
      lstrcpy (DocName,hd.DocumentName);
    else {
      GlobalFree (hGres);
      hGres = 0;
      }
    }
  else
    *DocName = 0L;
  *HeaderSize = 0;

  return hGres;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetNextDoc (LPSTR DocName,DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  dscript.Open ();

  Key_DocName key;
  ASSIGN   (key.Type          ,RSS_TYPEDOCDEF);
  lstrncpy (key.DocumentName  ,DocName,sizeof(key.DocumentName));
  ASSIGN   (key.LaufendeNummer,0xFFFF);

  rsscript_header hd;
  GLOBALHANDLE hGres = dscript.Read (DocSize,&hd,&key,sizeof(key),B_GETGT,KEY_DOCNAME);

  if (hGres) {
    if (hd.Type == RSS_TYPEDOCDEF)
      lstrcpy (DocName,hd.DocumentName);
    else {
      GlobalFree (hGres);
      hGres = 0;
      }
    }
  else
    *DocName = 0L;
  *HeaderSize = 0;

  return hGres;
  }

DLLExport void _export WINAPI DataRes_SetDocCont (LPVOID DocData,DWORD DataSize)
  {
  dscript.Open ();

  rsscript_header hd;
  ASSIGN   (hd.InterneNummer ,0L);
  ASSIGN   (hd.Type          ,RSS_TYPEDOCCONT);
  lstrncpy (hd.DocumentName  ,INTERNNAME,sizeof(hd.DocumentName));
  ASSIGN   (hd.LaufendeNummer,0);

  dscript.Update (&hd,DocData,DataSize,KEY_DOCNAME);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetDocCont (DWORD FAR *HeaderSize,DWORD FAR *DocSize)
  {
  dscript.Open ();

  Key_DocName key;
  ASSIGN   (key.Type          ,RSS_TYPEDOCCONT);
  lstrncpy (key.DocumentName  ,INTERNNAME,sizeof(key.DocumentName));
  ASSIGN   (key.LaufendeNummer,0);

  rsscript_header hd;
  GLOBALHANDLE hGres = dscript.Read (DocSize,&hd,&key,sizeof(key),B_GETEQ,KEY_DOCNAME);

  *HeaderSize = 0;

  return hGres;
  }

DLLExport DWORD _export WINAPI DataRes_SetResource (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize)
  {
  dresource.Open ();

  // Versuch, die Definition zu lesen
  Key_ResName key;
  ASSIGN   (key.Type          ,Type);
  lstrncpy (key.ResName       ,Name,sizeof(key.ResName));
  ASSIGN   (key.LaufendeNummer,0);

  DWORD RecSize;
  rsres_header hd,hdold;
  GLOBALHANDLE hGres = dresource.Read (&RecSize,&hdold,&key,sizeof(key),B_GETEQ,KEY_RESNAME);

  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.ResID         ,0);
  ASSIGN   (hd.Type          ,Type);
  lstrncpy (hd.ResName       ,Name,sizeof(hd.ResName));
  ASSIGN   (hd.LaufendeNummer,0);

  DWORD res;

  if (hGres) {
    // Hat geklappt -> Untersuchen, ob sich die Daten geaendert haben
    res = hd.ResID = hdold.ResID;
    LPVOID oldResData = GlobalLock (hGres);
    if ((RecSize != DataSize) || (!hmemcmp (oldResData,Data,RecSize))) {
      // Update noetig
      dresource.Update (&hd,Data,DataSize,KEY_RESNAME);
      }
    GlobalUnlock (hGres);
    GlobalFree (hGres);
    }
  else {
    // Nix gewesen -> Insert noetig
    // Mit diesem die Daten schreiben
    InsertResDef (&hd,&dresource);
    res = hd.ResID;
    dresource.Update (&hd,Data,DataSize,KEY_RESNAME);
    }
  return res;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetResource (DWORD ResID,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  dresource.Open ();

  Key_ResId key;
  ASSIGN   (key.ResID         ,ResID);
  ASSIGN   (key.LaufendeNummer,0);

  rsres_header hd;
  GLOBALHANDLE hGres = dresource.Read (DataSize,&hd,&key,sizeof(key),B_GETEQ,KEY_RESID);

  *HeaderSize = 0;

  return hGres;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetFirstResource
            (WORD Type,DWORD FAR *Id,LPSTR ResName,
             DWORD FAR *HeaderSize,
             DWORD FAR *DataSize
            )
  {
  dresource.Open ();

  // Versuch, die Definition zu lesen
  Key_ResName key;
  ASSIGN   (key.Type          ,Type);
  lmemset  (key.ResName       ,'\0',sizeof(key.ResName));
  ASSIGN   (key.LaufendeNummer,0);

  rsres_header hd;
  *DataSize = 0L;
  GLOBALHANDLE hGres = dresource.Read (DataSize,&hd,&key,sizeof(key),B_GETGTE,KEY_RESNAME);

  if (hGres) {
    if (hd.Type == Type) {
      *Id = hd.ResID;
      lstrcpy (ResName,hd.ResName);
      }
    else {
      GlobalFree (hGres);
      hGres = 0;
      }
    }

  *HeaderSize = 0L;
  return hGres;
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetNextResource
            (WORD Type,DWORD FAR *Id,LPSTR ResName,
             DWORD FAR *HeaderSize,
             DWORD FAR *DataSize
            )
  {
  dresource.Open ();

  // Versuch, die Definition zu lesen
  Key_ResName key;
  ASSIGN   (key.Type          ,Type);
  lstrncpy (key.ResName       ,ResName,sizeof(key.ResName));
  ASSIGN   (key.LaufendeNummer,0xFFFF);

  rsres_header hd;
  *DataSize = 0L;
  GLOBALHANDLE hGres = dresource.Read (DataSize,&hd,&key,sizeof(key),B_GETGT,KEY_RESNAME);

  if (hGres) {
    if (hd.Type == Type) {
      *Id = hd.ResID;
      lstrcpy (ResName,hd.ResName);
      }
    else {
      GlobalFree (hGres);
      hGres = 0;
      }
    }

  *HeaderSize = 0L;
  return hGres;
  }

DLLExport void _export WINAPI DataRes_SetResCont (WORD Type,LPVOID Data,DWORD DataSize)
  {
  dresource.Open ();

  DataRes_SetResource (Type+0x8000,INTERNNAME,Data,DataSize);
  }

DLLExport GLOBALHANDLE _export WINAPI DataRes_GetResCont (WORD Type,DWORD FAR *HeaderSize,DWORD FAR *DataSize)
  {
  dresource.Open ();

  // Versuch, die Definition zu lesen
  Key_ResName key;
  ASSIGN   (key.Type          ,Type+0x8000);
  lstrncpy (key.ResName       ,INTERNNAME,sizeof(key.ResName));
  ASSIGN   (key.LaufendeNummer,0);

  rsres_header hd;
  *DataSize = 0L;
  GLOBALHANDLE hGres = dresource.Read (DataSize,&hd,&key,sizeof(key),B_GETEQ,KEY_RESNAME);

  *HeaderSize = 0L;
  return hGres;
  }

////////////////////////////////////////////////////////////////////////
// Aufraeumarbeiten der Resourcedatenbanken
////////////////////////////////////////////////////////////////////////
void ResetResDB ()
  {
  ddict.Close     ();
  dscript.Close   ();
  dresource.Close ();
  dhlp.Close ();
  }

/*--------< Hilfsdatenbank zur Verwaltung von Restool - Info >-------*/
DLLExport void _export WINAPI DBHelp_Put (WORD Type,LPSTR Name,LPVOID Data,DWORD DataSize)
  {
  dhlp.Open ();
  rstmp_header hd;
  ASSIGN   (hd.InterneNummer ,0);
  ASSIGN   (hd.Type          ,Type);
  lstrncpy (hd.TempName      ,Name,sizeof(hd.TempName));
  ASSIGN   (hd.LaufendeNummer,0);
  dhlp.Update (&hd,Data,DataSize,1);
  }

DLLExport GLOBALHANDLE _export WINAPI DBHelp_Get (WORD Type,LPSTR Name,DWORD FAR *TableSize)
  {
  dhlp.Open ();

  Key_Tres key;
  ASSIGN   (key.Type          ,Type);
  lstrncpy (key.TempName      ,Name,sizeof(key.TempName));
  ASSIGN   (key.LaufendeNummer,0);

  rstmp_header hd;
  *TableSize = 0L;
  return dhlp.Read (TableSize,&hd,&key,sizeof(key),B_GETEQ,1);
  }

DLLExport GLOBALHANDLE _export WINAPI DBHelp_List (WORD Type)
  {
  dhlp.Open ();

  Key_Tres key;
  ASSIGN   (key.Type          ,Type);
  lmemset  (key.TempName      ,'\0',sizeof(key.TempName));
  ASSIGN   (key.LaufendeNummer,0);

  rstmp_header hd;
  DWORD TableSize = 0;
  DWORD gSize = 0;
  GLOBALHANDLE res = 0;
  GLOBALHANDLE hGres = dhlp.Read (&TableSize,&hd,&key,sizeof(key),B_GETGT,1);
  for ( ; hGres ; ) {
    GlobalFree (hGres) ;
    if (hd.Type != Type) break ;
    res = PushBlock (res,&gSize,hd.TempName,lstrlen(hd.TempName)+1);
    hGres = dhlp.Read (&TableSize,&hd,&key,sizeof(key),B_GETNEXT,1);
    }
  res = PushBlock (res,&gSize,"\0\0",2);
  return res;
  }
