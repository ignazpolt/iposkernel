////////////////////////////////////////////////////////////////////////
//  Durchfuehren der eigentlichen Operationen
////////////////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/dbbtrv/rev/opbtrv.cpv   1.77   13 Oct 1998 13:04:04   Gerhold  $
//  $Log:   P:/marille/clinicum/dbbtrv/rev/opbtrv.cpv  $
// 
//    Rev 1.77   13 Oct 1998 13:04:04   Gerhold
// HINSTANCE hLibInst wegen VC6
// 
//    Rev 1.76   21 Aug 1998 10:44:28   Hannes
// Timestamp die 25.
// 
//    Rev 1.75   10 Aug 1998 17:03:46   Hannes
// Umstellen des Timestamps auf UNSIGNED
// 
//    Rev 1.74   04 Aug 1998 17:55:40   Hannes
// Timestamp
// 
//    Rev 1.73   06 Mar 1998 17:07:04   Hannes
// 
//    Rev 1.72   13 Jan 1998 17:57:34   Hannes
// 
//    Rev 1.71   12 Jan 1998 17:50:58   Hannes
// Chuncks variabl gross
// 
//    Rev 1.70   01 Dec 1997 19:39:58   Hannes
// Diverse Anpassungen / Replikator
// 
//    Rev 1.69   23 Oct 1997 11:56:52   Hannes
// Kein SetDBVersion, Rosaschirmhandling bei Nichtexistenz verbessert
// 
//    Rev 1.68   08 Sep 1997 12:20:08   Hannes
// diverse Verbesserungen
// 
//    Rev 1.67   25 Aug 1997 12:41:16   Hannes
// Bei Blobs... entsprechenden Typ zurueckgeben
// 
//    Rev 1.66   04 Aug 1997 11:14:02   Hannes
// SetDBVersion
// 
//    Rev 1.65   18 Jul 1997 08:06:34   Hannes
// 
//    Rev 1.64   30 Apr 1997 10:29:06   Hannes
// 
//    Rev 1.63   30 Apr 1997 09:32:10   Hannes
// 
//    Rev 1.62   30 Apr 1997 09:20:38   Hannes
// 
//    Rev 1.61   28 Feb 1997 14:39:46   Hannes
// Hashtabelle mit den File - Pfaden
// 
//    Rev 1.60   18 Dec 1996 17:50:28   HANNES
// 
//    Rev 1.59   17 Dec 1996 18:36:20   HANNES
// Abfrage aus dem dbbtrv.ini [Use] Direct = "yes" | "no"
// 
//    Rev 1.58   17 Dec 1996 11:13:38   HANNES
// 
//    Rev 1.57   13 Dec 1996 14:34:24   MARTIN
// USE_DIRECT in der DEBUG-Variante
// 
//    Rev 1.56   04 Dec 1996 14:23:48   HANNES
// 
//    Rev 1.55   04 Dec 1996 14:11:30   HANNES
// 
//    Rev 1.54   04 Dec 1996 12:52:40   HANNES
// 
//    Rev 1.53   27 Nov 1996 18:13:12   HANNES
// 
//    Rev 1.52   27 Nov 1996 15:53:20   HANNES
// 
//    Rev 1.51   27 Nov 1996 08:40:58   HANNES
// 
//    Rev 1.50   26 Nov 1996 19:06:56   HANNES
// 
//    Rev 1.49   26 Nov 1996 08:00:20   HANNES
// Automatischer Update
// 
//    Rev 1.48   08 Nov 1996 13:26:48   HANNES
// QLong, Replikator
// 
//    Rev 1.47   28 Oct 1996 17:49:34   HANNES
// 
//    Rev 1.46   12 Sep 1996 23:10:56   HANNES
// DBOP_ENDOFCONVERSION
// 
//    Rev 1.45   03 Sep 1996 10:06:28   HANNES
// Kleine Effizienzsteigerung durch veraendern der Konstanten
// 
//    Rev 1.44   17 Jun 1996 15:40:20   HANNES
// 
//    Rev 1.41   04 Feb 1996 21:42:04   HANNES
// 
//    Rev 1.40   04 Feb 1996 15:37:58   HANNES
// 
//    Rev 1.39   02 Feb 1996 10:42:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.38   04 Dec 1995 20:56:48   HANNES
// MyStrCmp ... Fuer Zeichen > 128
// 
//    Rev 1.37   04 Dec 1995 15:21:52   HANNES
// 
//    Rev 1.36   10 Nov 1995 12:23:12   MARTIN
// Korrekturen Hannes
// 
//    Rev 1.34   02 Nov 1995 19:11:18   martin
// StackData von LPVOID aud struct
// 
//    Rev 1.33   31 Jul 1995 17:32:46   HANNES
// CompareSigned,CompareUnsigned
// 
//    Rev 1.32   25 Jul 1995 12:03:32   HANNES
// 
//    Rev 1.31   25 Jul 1995 10:39:46   HANNES
// Verbesserte Filterpruefung
// 
//    Rev 1.30   14 Jul 1995 16:55:08   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.29   14 Jun 1995 13:10:16   HANNES
// FreeTempararyTable auf jeden Fall aufgerufen
// 
//    Rev 1.28   09 Jun 1995 00:26:14   HANNES
// Rejectcounthandling
// 
//    Rev 1.27   26 Apr 1995 15:33:18   HANNES
// 
//    Rev 1.26   31 Mar 1995 18:23:28   HANNES
//  
// 
//    Rev 1.25   29 Mar 1995 16:23:02   HANNES
// 
//    Rev 1.24   20 Mar 1995 12:10:22   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.23   24 Feb 1995 11:14:30   HANNES
//  
// 
//    Rev 1.22   16 Feb 1995 12:46:26   HANNES
// Erweiterung um SQL-Faehigkeiten
// 
//    Rev 1.21   09 Dec 1994 19:43:50   HANNES
// 
//    Rev 1.20   08 Dec 1994 22:05:02   HANNES
// divlong,on_notfiltersatisfy
// 
//    Rev 1.19   07 Dec 1994 15:30:54   GERHOLD
// Umstellung auf MSC 8.00
// 
//    Rev 1.18   07 Dec 1994 15:09:16   HANNES
// Concurrent transactions
// 
//    Rev 1.17   19 Nov 1994 18:32:16   HANNES
// Ueberpruefung auf Laenge bei Stringparametern fuer Schluessel verzichtet
// 
//    Rev 1.16   16 Nov 1994 14:58:24   HANNES
// 
//    Rev 1.15   09 Nov 1994 14:32:28   HANNES
// StrCmp
// 
//    Rev 1.14   08 Nov 1994 12:42:48   HANNES
// Parameter als Resultat
// 
//    Rev 1.13   07 Nov 1994 11:41:24   HANNES
// Alle Strings auf ZString, neue Alternate Sequenz
// 
//    Rev 1.12   31 Oct 1994 10:37:28   hannes
// - Statt DBRecord::Set DBRecord::Initialize aufgerufen
// - Transaktionen
// - Files schliessen
// 
//    Rev 1.11   19 Oct 1994 22:30:52   hannes
// Schluesselwort Continue
// Handling bei Joins in OnStore
// 
//    Rev 1.10   06 Oct 1994 19:29:50   HANNES
// Bufferhandle - Umstellung
// 
//    Rev 1.9   20 Sep 1994 11:22:34   HANNES
// CompareTime
// 
//    Rev 1.8   14 Sep 1994 19:33:10   HANNES
// Schon wieder eine Aenderung an PushToLockList
// 
//    Rev 1.7   08 Sep 1994 09:08:44   HANNES
// NCPLock (vorerst) wieder raus, CompareDate
// 
//    Rev 1.6   24 Aug 1994 19:41:30   HANNES
// Vergleich mit Datentyp BDT_STRING
// 
//    Rev 1.5   10 Aug 1994 12:07:50   HANNES
// SetPrimaryKey ... schwerer Fehler
// 
//    Rev 1.4   05 Aug 1994 17:08:14   HANNES
// 
//    Rev 1.3   17 Jul 1994 14:39:28   HANNES
// Umorganisation der Primaerschluesselvergabe
// 
//    Rev 1.2   27 Jun 1994 15:14:26   HANNES
// 
//    Rev 1.1   27 Jun 1994 14:09:26   HANNES
// NextOnEndOfFile
// 
//    Rev 1.0   24 Jun 1994 16:43:24   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#define JUST_EM
#include "dds.hpp"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbbtrv.hpp"
#define MODULENUM 14
#include "winass.hpp"
#include "tbkw.h"
#include "tbfnc.hpp"
#include "dbrecord.hpp"
#ifndef WIN32
#include "dos.h"
#endif
#include "btrieve.hpp"
#include "opbtrv.hpp"

extern "C" {
#include "wbtrv.h"
  }
#include "lock.hpp"
#include "hash.hpp"
#include "compile.hpp"

#define REJECT_COUNT    60
#define REJECT_NOMORE   64

#define B_UNLOCK        27

extern LPSTR WINAPI makeIni(LPSTR txt);
BOOL UseDirect ()
  {
  static BOOL UseDirect_read;
  static BOOL useDirect ;
  if (!UseDirect_read) {
    char answ[32];
    GetPrivateProfileString ("Use","Direct","no",answ,sizeof(answ),makeIni("dbbtrv.ini"));
    if (lstrcmp (answ,"yes") == 0) useDirect = TRUE ;
    UseDirect_read = TRUE ;
    }
  return useDirect;
  }

#define USE_DIRECT UseDirect()

/*------< Transaktionshandling >------*/
static BOOL _IsInTransaction;
BOOL IsInTransaction ()
  {
  return (_IsInTransaction);
  }
#define B_BEGINTRANSACTION  1319
#define B_ENDTRANSACTION    20
#define B_ABORTTRANSACTION  21
extern void LogCmd (LPSTR t1,LPSTR t2,LPSTR t3,LPSTR t4);
extern BOOL DoLog(void);
DLLExport void _export WINAPI DoBeginTransaction (BOOL doLarge)
  {
  if (DoLog())
    LogCmd ("\rBEGINTRANSACTION\r----------------",NULL,NULL,NULL);
  WIN_ASSERT_TEXT (!IsInTransaction(),"Geschachtelter Transaktionsauf");
  int status = BTRCALL (B_BEGINTRANSACTION,NULL,NULL,NULL,
                                NULL,0,0);
  TestST (status,"");
  _IsInTransaction = TRUE ;
  }

extern DLLExport void _export OnEndTransaction ();
DLLExport void _export WINAPI DoEndTransaction ()
  {
  if (DoLog())
    LogCmd ("\rENDTRANSACTION\r--------------",NULL,NULL,NULL);
  int status = BTRCALL (B_ENDTRANSACTION,NULL,NULL,NULL,
                                NULL,0,0);
  _IsInTransaction = FALSE ;
  OnEndTransaction();
  TestST (status,"");

  RestoreCNV();
  }

DLLExport void _export WINAPI DoAbortTransaction ()
  {
  if (DoLog())
    LogCmd ("\rABORTTRANSACTION\r----------------",NULL,NULL,NULL);
  int status = BTRCALL (B_ABORTTRANSACTION,NULL,NULL,NULL,
                                NULL,0,0);
  _IsInTransaction = FALSE ;
  TestST (status,"");

  DeleteCNV();
  OnEndTransaction ();
  }

void TestDBOpContext (WORD Op,LPBTRSTATEMENT stmt)
  {
  static WORD OpsInTransaction[] = {
    B_INSERT ,
    B_UPDATE ,
    B_DELETE
    };
  BOOL mustBeInTransaction = FALSE ;
  for (int i = 0 ; i < sizeof(OpsInTransaction) / sizeof (OpsInTransaction[0]) ; i++)
    if (OpsInTransaction[i] == Op) mustBeInTransaction = TRUE ; 
  if ((mustBeInTransaction) && (!IsInTransaction()) && (!InAlter())) {
    char msgstr[256];
    wsprintf (msgstr,"Nicht Transaktionale Operation in %s",stmt->req->SelectionName);
    WIN_ASSERT_TEXT (FALSE,msgstr);
    }
  }

/*------< Bufferhandling >------*/
#define MAX_BUFFERHANDLES 64
static struct {
  GLOBALHANDLE hGmem ;
  GLOBALHANDLE hGOld;
  } BufferHandle [MAX_BUFFERHANDLES];
  
static BOOL IsBufferUsed [MAX_BUFFERHANDLES];
void InitializeBuffers()
  {
  if (BufferHandle[0].hGmem != NULL) return ;
  for (int i = 0 ; i < MAX_BUFFERHANDLES ; i++)
    BufferHandle[i].hGmem = GlobalAlloc (GMEM_MOVEABLE,BUFFER_SIZE);
  }
void ReleaseBuffers()
  {
  for (int i = 0 ; i < MAX_BUFFERHANDLES ; i++) {
    if (BufferHandle[i].hGmem) {
      // GlobalUnlock (BufferHandle[i].hGmem);
      GlobalFree (BufferHandle[i].hGmem);
      BufferHandle[i].hGmem = 0;
      }
    }
  }
GLOBALHANDLE GetBufferHandle (GLOBALHANDLE old)
  {
  for (int i = 0 ; i < MAX_BUFFERHANDLES ; i++) {
    if (!IsBufferUsed[i]) {
      IsBufferUsed[i] = TRUE ;
      BufferHandle[i].hGOld = old ;
      return BufferHandle[i].hGmem ;
      }
    }
  WIN_ASSERT (FALSE);
  return 0;
  }

GLOBALHANDLE ReleaseBufferHandle (GLOBALHANDLE hGmem)
  {
  for (int i = 0 ; i < MAX_BUFFERHANDLES ; i++) {
    if (BufferHandle[i].hGmem == hGmem) {
      IsBufferUsed[i] = FALSE ;
      GlobalUnlock (hGmem);
      return BufferHandle[i].hGOld ;
      }
    }
  WIN_ASSERT (FALSE);
  return 0 ;
  }

extern HINSTANCE hLibInst;
/*------< Implementierung der uebergorneten Fileverwaltung >-------*/
#define BE_LOCKED       85
char ResOpenMode();
void CatName (LPSTR path,LPSTR FName)
  {
  for ( LPSTR h = path ; ; h++)
    if (*h == '\0') break ;
  for ( LPSTR x = FName ; *x ; ) {
    if (*x == '.') break ;
    *h ++ = *x ++ ;
    }
  *h ++ = '\0' ;
  }

hash FAR *fNamHash;
void GetFileName (LPTABLEDEF td,LPSTR path,LPSTR AltName)
  {
  if (GetCNVPath (td) != NULL)
    lstrcpy (path,GetCNVPath(td));
  else {
    LPSTR Name = (AltName != NULL) ? AltName : td->GetName() ;
    if (fNamHash == NULL)
      fNamHash = new hash (111,STRKEY);
    LPSTR hPath = LPSTR(fNamHash->GetData (Name));
    if (hPath != NULL)
      lstrcpy (path,hPath);
    else {
      GetPrivateProfileString ("Path",Name,"",path,PATH_SIZE,makeIni("dbbtrv.ini"));
      if (!*path) {
        GetPrivateProfileString ("Path","Directory","",path,PATH_SIZE,makeIni("dbbtrv.ini"));
        WIN_ASSERT_TEXT(*path,"Zumindest das Directory muss angegeben sein");
        CatName (path,td->GetFileName());
        lstrcat (path,".DAT");
        }
      fNamHash->SetData (Name,path,lstrlen(path) + 1);
      }
    }
  }

static BOOL InCreate ;
BOOL IsDDF(LPSTR Path)
  {
  LPSTR lastP = Path ;
  for (LPSTR h = Path ; *h ; h++) {
    if (*h == '.') lastP = h + 1;
    }
  char ext[32];
  lstrcpy (ext,lastP);
  AnsiUpper (ext);
  return (lstrcmp (ext,"DDF") == 0);
  }
bFile::bFile (LPTABLEDEF td,LPSTR alternateName)
  {
  InitializeBuffers();
  LPBTRVTABLE t = LPBTRVTABLE(td->GetDLLDef());
  GetFileName (td,Path,alternateName);
  rd = LPRECDESC(GetGlobMem (t->GetDescRef()->StructSize));
  lmemcpy (rd,t->GetDescRef(),t->GetDescRef()->StructSize);
  if (*Path) {
    int status = BE_LOCKED ;
    char ownerbuffer[128];
    unsigned cownerbuffer;
    for ( ; status == BE_LOCKED ; ) {
      lmemset (ownerbuffer,'\0',sizeof (ownerbuffer));
      cownerbuffer = sizeof(ownerbuffer);
      char om;
      if ((td->GetTableID() >= RESOURCEIDMIN) && (td->GetTableID() < RESOURCEIDMAX)) {
        if (((lstrcmp (td->GetName(),"ScriptDB") == 0)) ||
            ((lstrcmp (td->GetName(),"DataDict") == 0)) ||
            ((lstrcmp (td->GetName(),"ResDB") == 0)))
          om = ResOpenMode ();
        else
          om = MODE_NORMAL ;
        }
      else
        om = MODE_NORMAL ;
      status = BTRCALL (B_OPEN,pb,ownerbuffer,&cownerbuffer,
                                    Path,lstrlen(Path)+1,
                                    om);
      if (status == BE_LOCKED) {
        DWORD t = GetTickCount ();
        for ( ; GetTickCount () < t + 200 ; ) ;
        }
      }

    if (status == BRFILENOTFOUND) {
      BOOL doCreate;
      if ((!InAlter ()) && (!InCreate)) {
        char outtxt[256];
        char pattern[128];
        LoadString (hLibInst,FILENOTFOUNE_PATTERN,pattern,sizeof(pattern));
        wsprintf (outtxt,pattern,ErrorName());
        WIN_ASSERT_TEXT (FALSE,outtxt);
        doCreate = FALSE ;
        }
      else
        doCreate = TRUE ;
      // Erzeugen des Files
      if (doCreate) {
        LPRECDESC k = LPRECDESC (GetGlobMem (GetBlockSize(rd)));
        lmemcpy (k,rd,GetBlockSize(rd));
        unsigned buffersize = k->StructSize - 2 * sizeof(WORD);
        status = BTRCALL (B_CREATE,pb,LPSTR(k) + 2 * sizeof(WORD),&buffersize,
                                    Path,lstrlen(Path)+1,-1);
        TestST (status,ErrorName());
        cownerbuffer = sizeof(ownerbuffer);
        status = BTRCALL (B_OPEN,pb,ownerbuffer,&cownerbuffer,
                                    Path,lstrlen(Path)+1,
                                    MODE_NORMAL);
        if (!InAlter()) {
          DelDefinition(td->GetName());
          CreateDefinition (td);
          }
        }
      }
    isOpen = (status == 0);
    TestST (status,ErrorName());
    // Speicher anfordenrn
    hGBuffer = GetBufferHandle(0);
    WIN_ASSERT (hGBuffer);
    btrBuffer = LPSTR(GlobalLock (hGBuffer));
    // So, nun noch einen Status ermitteln
    unsigned buffersize = BUFFER_SIZE;
    char nPath[128];
    status = BTRCALL (B_STATUS,pb,btrBuffer+2*sizeof(WORD),&buffersize,
                                nPath,sizeof(nPath),
                                0);
    TestST (status,ErrorName());
    LPRECDESC s = LPRECDESC (btrBuffer);
    if (!CompareStat (s,buffersize)) {
      char outtxt[256];
      char pattern[128];
      LoadString (hLibInst,STATDIFFERENT_PATTERN,pattern,sizeof(pattern));
      wsprintf (outtxt,pattern,ErrorName());
      WIN_ASSERT_TEXT (FALSE,outtxt);
      FileStatDifferent = TRUE ;
      }
    hGBuffer = ReleaseBufferHandle(hGBuffer);
    btrBuffer = NULL ;
    }
  else {
    char outtxt[256];
    wsprintf (outtxt,"No Entry in dbbtrv.ini for %s found",Name);
    WIN_ASSERT_TEXT (FALSE,outtxt);
    }
  }

BOOL bFile::CompareStat (LPRECDESC d,unsigned buffersize)
  {
  if (d->RecordLength != rd->RecordLength) return FALSE ;
#ifdef STRICT_TEST
  if (d->PageSize != rd->PageSize) return FALSE ;
  if ((d->flags & (FA_COMPRESS | FA_VARIABLE)) != 
      (rd->flags & (FA_COMPRESS | FA_VARIABLE)))
    return FALSE ;
#endif
  if (d->NumKeys != rd->NumKeys) return FALSE ;
  int j = 0;
  for (int i = 0 ; i < int(d->NumKeys) ; j ++) {
    if (d->k[j].position != rd->k[j].position) return FALSE ;
    if (d->k[j].length != rd->k[j].length) return FALSE ;
    if ((d->k[j].flag & KA_TESTFLAGS) !=
            (rd->k[j].flag & KA_TESTFLAGS)) return FALSE ;
    if ((d->k[j].flag & (KA_NULL | KA_MANUAL)) &&
          (d->k[j].nullVal != rd->k[j].nullVal)) return FALSE ;
    if ((d->k[j].flag & KA_SEGMENTED) == 0)
      i++ ;
    }
  if (WORD(LPSTR(&(d->k[j])) - LPSTR(&d->RecordLength)) < buffersize)
    // Alternate definiert
    lmemcpy (AlternateSequence,LPSTR(&(d->k[j]))+9,sizeof(AlternateSequence)) ,
    AlternateDefined = TRUE ;
  else
    AlternateDefined = FALSE ;
  return TRUE ;
  }

bFile::~bFile ()
  {
  if (rd != NULL)
    FreeGlobMem (rd);
  if (isOpen) {
    unsigned buffersize = 0;
    int status = BTRCALL (B_CLOSE,pb,NULL,&buffersize,
                                NULL,0,0);
    TestST (status,ErrorName());
    }
  hGBuffer = 0;
  }

/*------< Files wieder schliessen bei Bedarf >------*/
int MaxOpenCount ()
  {
  static int _maxOpen ;
  if (_maxOpen <= 0) {
    _maxOpen = GetPrivateProfileInt ("Data","MaxOpen",30,makeIni("dbbtrv.ini"));
    if (_maxOpen < 0) _maxOpen = 15 ;
    }
  return _maxOpen;
  }
FileList FAR *GetOldest (FileList FAR *FAR *prev)
  {
  DWORD ActTime = GetTickCount();
  FileList FAR *p = NULL ;
  FileList FAR *best = NULL ;
  for (FileList FAR *h = fl ; h != NULL ; h = h->Next) {
    if ((h->f != NULL) && (h->f->StmtCount == 0) && (h->f->LastAccessTime < ActTime)) {
      best = h ;
      ActTime = h->f->LastAccessTime;
      *prev = p;
      }
    p = h ;
    }
  return best ;
  }
void CloseOldFiles ()
  {
  int count = 0;
  for ( FileList FAR *h = fl ; h != NULL ; h = h->Next) count ++ ;
  if ((count > MaxOpenCount()) && (!IsInTransaction())) {
    for ( ; count > MaxOpenCount() ; ) {
      FileList FAR *prev;
      h = GetOldest (&prev);
      if (h != NULL) {
        delete h->f;
        count -- ;
        if (prev != NULL)
          prev->Next = h->Next ;
        else
          fl = h->Next ;
        FreeGlobMem (h);
        }
      else
        break ;
      }
    }
  }

LPBFILE GetFile (LPTABLEDEF td,LPSTR alternateName)
  {
  CloseOldFiles ();
  char path[256];
  GetFileName (td,path,alternateName);
  for ( FileList FAR *h = fl ; h != NULL ; h = h->Next) {
    if ((h->f != NULL) && (lstrcmp (h->f->Path,path) == 0)) {
      LPBTRVTABLE t = LPBTRVTABLE(td->GetDLLDef());
      if ((h->f->rd->StructSize != t->GetDescRef()->StructSize) || 
            (!lmemcmp (h->f->rd,t->GetDescRef(),h->f->rd->StructSize))) {
        DBWIN_ASSERT_TEXT (FALSE,"!!! Inkonsistenz in der File Deklaration !!!");
        }
      return h->f;
      }
    }
  h = (FileList FAR *) GetGlobMem (sizeof(*h));
  h->Next = fl;
  fl = h;
  return (h->f = new bFile (td,alternateName)) ;
  }

BOOL CloseFile (LPSTR Name)
  {
  FileList FAR *prev = NULL;
  for ( FileList FAR *h = fl ; h != NULL ; h = h->Next) {
    if ((h->f != NULL) && (lstrcmp (h->f->Path,Name) == 0)) {
      if (prev != NULL) prev->Next = h->Next ;
      else              fl         = h->Next ;

      delete h->f ;
      FreeGlobMem (h);

      break ;
      }
    prev = h ;
    }

  return TRUE ;
  }

void CloseAllDataFiles ()
  {
  for ( ; fl != NULL ; ) {
    FileList FAR *h = fl->Next;
    if (fl->f != NULL) delete fl->f;
    FreeGlobMem (fl);
    fl = h;
    }
  ReleaseBuffers();
  delete fNamHash;
  fNamHash = NULL ;
  }

struct Extended_Buffer {
  WORD BufferLength;
  char Stamp[2];
  WORD RejectCount;
  WORD NumTerms;
  };
Extended_Buffer FAR *InitializeFilter (LPBTRSTATEMENT stmt,LPVOID buffer)
  {
  Extended_Buffer FAR *e = (Extended_Buffer FAR *) buffer;
  e->BufferLength = sizeof(*e);
  e->Stamp[0] = 'E';
  e->Stamp[1] = 'G';
  e->RejectCount = (stmt->RejectCountSet) ? stmt->RejectCount : 0x7FFF;
  e->NumTerms = 0;
  return e;
  }
WORD SetFilter (LPBTRSTATEMENT stmt,LPVOID buffer,LPVOID filter)
  {
  // Vorbereiten des Datenbuffers
  Extended_Buffer FAR *e = InitializeFilter(stmt,buffer);
  if (filter != NULL) {
    e->BufferLength += GetBlockSize(filter) - sizeof(WORD);
    lmemcpy (&e->NumTerms,filter,GetBlockSize(filter));
    }
  return e->BufferLength;
  }
struct Extractor {
  WORD NumRecsToRetrieve;
  WORD NumFieldsToExtract;
  };
struct Extractor_field { 
  WORD Length;
  WORD Offset;
  };
WORD SetFieldsToExtract (LPVOID buffer,WORD fOffs,LPDBREQUEST req,int TableNum,WORD AnzRecs)
  {
  Extractor FAR *x = (Extractor FAR *) (LPSTR (buffer) + fOffs);
  x->NumFieldsToExtract = 0;
  Extended_Buffer FAR *e = (Extended_Buffer FAR *) buffer;
  e->BufferLength += sizeof(*x);
  WORD RecSize = 0;
  if (req->AnzElems > 0) {
    LPTABLEDEF  d = req->TableDef[TableNum];
    if (TableNum == 0) {
      for (int j = 0 ; j < d->GetAnzVars () ; j++) {
        LPVARDEF v = d->GetVarDef(j) ;
        if (v->mType == VAR_BLOB)
          return USE_GETPART ;
        }
      }
    for (WORD i = 0 ; i < WORD(req->AnzElems) ; i++) {
      if (req->elem[i].TableNumber == TableNum) {
        Extractor_field FAR *f = (Extractor_field FAR *) 
                (LPSTR(buffer) + e->BufferLength);
        WORD VarID = req->elem[i].VarID;
        LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
        LPVARDEF    v  = d->GetVarDef(VarID);
        if (v->mType == VAR_BLOB)
          return USE_GETPART ;
        if (v != NULL) {
          LPDDSVARDESC vb = LPDDSVARDESC (v->GetDLLData());
          if (vb->mapType != MAPTYPE_FIELD)    // Nur Standardfelder bitte!
            return USE_GETFULL ;    // Keinen GetNextExtended
          LPVBTRV b = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vb->b.dOffs);
          f->Length = b->VarLen;
          f->Offset = b->VarOffset;
          RecSize += f->Length;
          e->BufferLength += sizeof(*f);
          x->NumFieldsToExtract ++ ;
          }
        }
      }
    }
  else {
    LPTABLEDEF d = req->TableDef[0];
    for (int j = 0 ; j < d->GetAnzVars () ; j++) {
      LPVARDEF v = d->GetVarDef(j);
      if (v->mType == VAR_BLOB)
        return USE_GETPART ;
      else if (v->VarID != 0xFFFF)
        return USE_GETFULL ;
      }
    LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
    for (int i = 0 ; i < d->GetAnzVars() ; i++) {
      Extractor_field FAR *f = (Extractor_field FAR *) 
              (LPSTR(buffer) + e->BufferLength);
      LPVARDEF    v  = d->GetVarDef(i);
        if (v->mType == VAR_BLOB)
          return USE_GETPART ;
      if ((v != NULL) && (v->VarSize != 0xFFFF)) {
        LPDDSVARDESC   vb = LPDDSVARDESC (v->GetDLLData());
        if (vb->mapType != MAPTYPE_FIELD)
          return USE_GETFULL ;    // Keinen GetNextExtended
        WIN_ASSERT (vb->mapType == MAPTYPE_FIELD);    // Nur Standardfelder bitte!
        LPVBTRV b = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vb->b.dOffs);
        f->Length = b->VarLen;
        f->Offset = b->VarOffset;
        RecSize += f->Length;
        e->BufferLength += sizeof(*f);
        x->NumFieldsToExtract ++ ;
        }
      }
    }
  x->NumRecsToRetrieve = (BUFFER_SIZE - sizeof(WORD)) / (RecSize + sizeof(RecordImage));
  if (x->NumRecsToRetrieve > AnzRecs)
    x->NumRecsToRetrieve = AnzRecs;

  return USE_GETNEXTEXTENDED ;
  }

// Implementierung der Klasse BtrStatement
//////////////////////////////////////////////////////
LPVOID BtrStatement::PushToFilter(LPVOID filter,LPVOID data,WORD size)
  {
  WORD oSize;
  if (filter != NULL) oSize = GetBlockSize(filter);
  else                oSize = sizeof(WORD);
  LPSTR n = LPSTR(GetGlobMem (oSize + size));
  if (filter != NULL) lmemcpy (n,filter,oSize) , FreeGlobMem (filter);
  lmemcpy (n+oSize,data,size);
  filter = n;
  return filter;
  }
void BtrStatement::IncAnzTerms(LPVOID filter)
  {
  *(LPWORD)filter = *(LPWORD)filter + 1 ;
  }
//
// Test der logischen Operation
//
int MyStrCmp (LPSTR s1,LPSTR s2)
  {
  int res = 0 ;
  for ( ; ((*s1) && (*s2) && (res == 0)) ; s1 ++ , s2 ++)
    res = int (BYTE (*s1)) - int (BYTE(*s2)) ;
  if (res == 0) {
    if (*s1) res = *s1 ;
    if (*s2) res = - *s2 ;
    }
  return res ;
  }

BOOL CompareZString (LPBTRSTATEMENT stmt,LPVOID data,LPVOID cmpdata,WORD VarLen,WORD cmpCode,BOOL UseOEM = FALSE)
  {
  if ((cmpCode & 32) != 0) {    
    // Alternate Sequence
    LPSTR b1 = LPSTR(GetGlobMem (VarLen + 1));
    LPSTR b2 = LPSTR(GetGlobMem (VarLen + 1));
    if (stmt->File->AlternateDefined) {
      for (WORD i = 0 ; i < VarLen ; i++)
        b1[i] = stmt->File->AlternateSequence [((BYTE FAR *) (data))[i]];
      for (i = 0 ; i < VarLen ; i++)
        b2[i] = stmt->File->AlternateSequence [((BYTE FAR *) (cmpdata))[i]];
      }
    else {
      lmemcpy (b1,data,VarLen);
      lmemcpy (b2,cmpdata,VarLen);
      }
    BOOL res = CompareZString (stmt,b1,b2,VarLen,cmpCode & ~32,UseOEM);
    FreeGlobMem (b1);
    FreeGlobMem (b2);
    return res;
    }
  else {
    switch (cmpCode) {
      case BCMP_NOTEQUAL    :
        return (MyStrCmp (LPSTR(data),LPSTR(cmpdata)) != 0);
        break ;
      case BCMP_LESSEQAUL   :
        return (MyStrCmp (LPSTR(data),LPSTR(cmpdata)) <= 0);
        break ;
      case BCMP_LESS        :
        return (MyStrCmp (LPSTR(data),LPSTR(cmpdata)) < 0);
        break ;
      case BCMP_GREATEREQUAL:
        return (MyStrCmp (LPSTR(data),LPSTR(cmpdata)) >= 0);
        break ;
      case BCMP_GREATER     :
        return (MyStrCmp (LPSTR(data),LPSTR(cmpdata)) > 0);
        break ;
      case BCMP_EQUAL       :
        return (MyStrCmp (LPSTR(data),LPSTR(cmpdata)) == 0);
        break ;
      default :
        return FALSE ;
      }
    }
  }
BOOL CompareLString (LPBTRSTATEMENT stmt,LPVOID data,LPVOID cmpdata,WORD VarLen,WORD cmpCode)
  {
  LPSTR b1 = LPSTR(GetGlobMem (VarLen));
  LPSTR b2 = LPSTR(GetGlobMem (VarLen));
  lmemcpy (b1,LPSTR(data)+1,*(LPSTR(data)));
  lmemcpy (b2,LPSTR(cmpdata)+1,*(LPSTR(cmpdata)));
  BOOL res = CompareZString (stmt,b1,b2,VarLen,cmpCode,TRUE);
  FreeGlobMem (b1);
  FreeGlobMem (b2);
  return res;
  }
BOOL CompareUString (LPBTRSTATEMENT stmt,LPVOID data,LPVOID cmpdata,WORD VarLen,WORD cmpCode)
  {
  LPSTR b1 = LPSTR(GetGlobMem (VarLen+1));
  LPSTR h = LPSTR(data);
  for (WORD i = 0 ; i < VarLen ; i++) {
    if (*h) b1[i] = *h++;
    else    b1[i] = '\0';
    }
  b1[i] = '\0';
  BOOL res = lstrcmp (b1,LPSTR(cmpdata));
  return res;
  }
BOOL CompareSigned (LPVOID d1,LPVOID d2,WORD vLen,WORD cmpCode)
  {
  BYTE FAR *b1 = (BYTE FAR *) GetGlobMem(vLen);
  lmemcpy (b1,d1,vLen);
  BYTE FAR *b2 = (BYTE FAR *) GetGlobMem(vLen);
  lmemcpy (b2,d2,vLen);
  int s1 = (b1[vLen-1] & 0x80) ? -1 : 1 ;
  int s2 = (b2[vLen-1] & 0x80) ? -1 : 1 ;
  b1[vLen-1] &= 0x7F;
  b2[vLen-1] &= 0x7F;
  int diff = 0;
  for (int i = vLen - 1 ; ((i >= 0) && (diff == 0)) ; i--)
    diff = int(b1[i]) - int(b2[i]);
  BOOL res;
  switch (cmpCode) {
    case BCMP_NOTEQUAL    :
      res = ((s1 != s2) || (diff != 0)) ;
      break ;
    case BCMP_LESSEQAUL   :
      res = ((s1 < s2) || (((s1 < 0) && (s2 < 0) && (diff >= 0)) || ((s1 > 0) && (s2 > 0) && (diff <= 0))));
      break ;
    case BCMP_LESS        :
      res = ((s1 < s2) || (((s1 < 0) && (s2 < 0) && (diff > 0)) || ((s1 > 0) && (s2 > 0) && (diff < 0))));
      break ;
    case BCMP_GREATEREQUAL:
      res = ((s1 > s2) || (((s1 < 0) && (s2 < 0) && (diff <= 0)) || ((s1 > 0) && (s2 > 0) && (diff >= 0))));
      break ;
    case BCMP_GREATER     :
      res = ((s1 > s2) || (((s1 < 0) && (s2 < 0) && (diff < 0)) || ((s1 > 0) && (s2 > 0) && (diff > 0))));
      break ;
    case BCMP_EQUAL       :
      res = ((s1 == s2) && (diff == 0)) ;
      break ;
    default :
      res = FALSE ;
    }
  FreeGlobMem (b1);
  FreeGlobMem (b2);
  return res;
  }
BOOL CompareUnsigned (LPVOID d1,LPVOID d2,WORD vLen,WORD cmpCode)
  {
  BYTE FAR *b1 = (BYTE FAR *)d1;
  BYTE FAR *b2 = (BYTE FAR *)d2;
  int diff = 0;
  for (int i = vLen - 1 ; ((i >= 0) && (diff == 0)) ; i--)
    diff = int(b1[i]) - int(b2[i]);
  BOOL res;
  switch (cmpCode) {
    case BCMP_NOTEQUAL    :
      res = (diff != 0) ;
      break ;
    case BCMP_LESSEQAUL   :
      res = (diff <= 0);
      break ;
    case BCMP_LESS        :
      res = (diff < 0);
      break ;
    case BCMP_GREATEREQUAL:
      res = (diff >= 0);
      break ;
    case BCMP_GREATER     :
      res = (diff > 0);
      break ;
    case BCMP_EQUAL       :
      res = (diff == 0);
      break ;
    }
  return res;
  }

BOOL CompareDate (LPVOID d1,LPVOID d2,WORD vLen,WORD cmpCode)
  {
  struct bdt { BYTE day ; BYTE month ; short int year ; } ;
  bdt FAR *b1 = (bdt FAR *) (d1);
  bdt FAR *b2 = (bdt FAR *) (d2);
  BOOL res ;
  switch (cmpCode) {
    case BCMP_NOTEQUAL    :
      res = ((b1->year != b2->year) ||
             (b1->month != b2->month) ||
             (b1->day != b2->day)) ;
      break ;
    case BCMP_LESSEQAUL   :
      res = ((CompareDate (d1,d2,vLen,BCMP_LESS)) ||
             (CompareDate (d1,d2,vLen,BCMP_EQUAL)));
      break ;
    case BCMP_LESS        :
      res = ((b1->year < b2->year) || 
             ((b1->year == b2->year) &&
              ((b1->month < b2->month) ||
               ((b1->month == b2->month) &&
                (b1->day < b2->day)))));
      break ;
    case BCMP_GREATEREQUAL:
      res = ((CompareDate (d1,d2,vLen,BCMP_GREATER)) ||
             (CompareDate (d1,d2,vLen,BCMP_EQUAL)));
      break ;
    case BCMP_GREATER     :
      res = ((b1->year > b2->year) || 
             ((b1->year == b2->year) &&
              ((b1->month > b2->month) ||
               ((b1->month == b2->month) &&
                (b1->day > b2->day)))));
      break ;
    case BCMP_EQUAL       :
      res = ((b1->year == b2->year) &&
             (b1->month == b2->month) &&
             (b1->day == b2->day)) ;
      break ;
    }
  return res;
  }

BOOL CompareTime (LPVOID d1,LPVOID d2,WORD vLen,WORD cmpCode)
  {
  struct btime { BYTE hundred_second ; BYTE second ; BYTE minute ; BYTE hour ; } ;
  btime FAR *b1 = (btime FAR *) (d1);
  btime FAR *b2 = (btime FAR *) (d2);
  BOOL res ;
  switch (cmpCode) {
    case BCMP_NOTEQUAL    :
      res = ((b1->second != b2->second) ||
             (b1->minute != b2->minute) ||
             (b1->hour != b2->hour)) ;
      break ;
    case BCMP_LESSEQAUL   :
      res = ((CompareTime (d1,d2,vLen,BCMP_LESS)) ||
             (CompareTime (d1,d2,vLen,BCMP_EQUAL)));
      break ;
    case BCMP_LESS        :
      res = ((b1->hour < b2->hour) || 
             ((b1->hour == b2->hour) &&
              ((b1->minute < b2->minute) ||
               ((b1->minute == b2->minute) &&
                (b1->second < b2->second)))));
      break ;
    case BCMP_GREATEREQUAL:
      res = ((CompareTime (d1,d2,vLen,BCMP_GREATER)) ||
             (CompareTime (d1,d2,vLen,BCMP_EQUAL)));
      break ;
    case BCMP_GREATER     :
      res = ((b1->hour > b2->hour) || 
             ((b1->hour == b2->hour) &&
              ((b1->minute > b2->minute) ||
               ((b1->minute == b2->minute) &&
                (b1->second > b2->second)))));
      break ;
    case BCMP_EQUAL       :
      res = ((b1->hour == b2->hour) &&
             (b1->minute == b2->minute) &&
             (b1->second == b2->second)) ;
      break ;
    }
  return res;
  }

BOOL CompareFloat (LPVOID d1,LPVOID d2,WORD vLen,WORD cmpCode)
  {
  WIN_ASSERT(vLen == sizeof(float));
  BOOL res;
  switch (cmpCode) {
    case BCMP_NOTEQUAL    :
      res = (((float FAR *) d1) != ((float FAR *) d2));
      break ;
    case BCMP_LESSEQAUL   :
      res = (((float FAR *) d1) <= ((float FAR *) d2));
      break ;
    case BCMP_LESS        :
      res = (((float FAR *) d1) < ((float FAR *) d2));
      break ;
    case BCMP_GREATEREQUAL:
      res = (((float FAR *) d1) >= ((float FAR *) d2));
      break ;
    case BCMP_GREATER     :
      res = (((float FAR *) d1) > ((float FAR *) d2));
      break ;
    case BCMP_EQUAL       :
      res = (((float FAR *) d1) == ((float FAR *) d2));
      break ;
    }
  return res;
  }
BOOL CompareData (LPBTRSTATEMENT stmt,WORD btrDataType,LPVOID d1,LPVOID d2,WORD VarLen,WORD cmpCode)
  {
  BOOL res ;
  switch (btrDataType) {
    case BDT_ZSTRING :
      res = CompareZString (stmt,d1,d2,VarLen,cmpCode);
      break ;
    case BDT_LSTRING :
      res = CompareLString (stmt,d1,d2,VarLen,cmpCode);
      break ;
    case BDT_STRING :
      res = CompareUString (stmt,d1,d2,VarLen,cmpCode);
      break ;
    case BDT_INTEGER :
    case BDT_AUTOINC :
      res = CompareSigned (d1,d2,VarLen,cmpCode);
      break ;
    case DT_SPRIVATE :
    case BDT_UNSIGNED :
      //if (VarLen == 8) {
      //  res = CompareDate (LPSTR (d1) + sizeof(packtime),LPSTR (d2) + sizeof(packtime),sizeof(packdate),cmpCode);
      //  if (res == 0)
      //    res = CompareTime (d1,d2,sizeof(packtime),cmpCode);
      //  }
      //else
        res = CompareUnsigned (d1,d2,VarLen,cmpCode);
      break ;
    case BDT_TIME :
      res = CompareTime (d1,d2,VarLen,cmpCode);
      break ;
    case BDT_DATE :
      res = CompareDate (d1,d2,VarLen,cmpCode);
      break ;
    case BDT_FLOAT :
      res = CompareFloat (d1,d2,VarLen,cmpCode);
      break ;
    case DT_PRIVATE :
      res = CompareDate (LPSTR (d1) + sizeof(packtime),LPSTR (d2) + sizeof(packtime),sizeof(packdate),cmpCode);
      if (res == 0)
        res = CompareTime (d1,d2,sizeof(packtime),cmpCode);
      break ;
    default :
      WIN_ASSERT (FALSE);
    }
  return res;
  }
BOOL TestFilter (LPVOID filter,LPBTRSTATEMENT stmt)
  {
  if (filter == NULL) return TRUE ;   // dieser Filter ist eher leicht
                                      // zu befriedigen
  FilterHeader FAR *f = (FilterHeader FAR *) (LPSTR(filter) + sizeof(WORD));
  BOOL gesamtres = FALSE;
  WORD lastOp = WORD(-1);
  for ( ; ; ) {
    BYTE FAR *op = (BYTE FAR *) (f + 1);
    LPVOID cmpData = op + 1;
    BOOL res = CompareData (stmt,f->btrDataType,LPSTR(stmt->File->btrBuffer)+f->VarOffset,cmpData,f->VarLen,f->cmpCode);
    switch (lastOp) {
      case BOP_AND :
        gesamtres = gesamtres && res ;
        break ;
      case BOP_OR :
        gesamtres = gesamtres || res ;
        break ;
      default :
        gesamtres = res ;
      }
    lastOp = *op ;
    if (*op == BOP_END) break ;
    if ((gesamtres) && (*op == BOP_OR)) break;
    if ((!gesamtres) && (*op == BOP_AND)) break ;
    f = (FilterHeader FAR *) (LPSTR(f+1) + 1 + (((f->cmpCode & 64) != 0) ? 2 : f->VarLen));
    }
  return gesamtres ;
  }

BOOL TestFilter (LPBTRSTATEMENT stmt)
  {
  return TestFilter (stmt->filter,stmt);
  }

// Abarbeiten von Expressions
////////////////////////////////
ElemRef FAR *ElemRef::Next ()
  {
  ElemRef FAR *res;
  switch (Type) {
    case ER_CASCADE     :
    case ER_POP         :
    case ER_PUSH        :
      res = (ElemRef FAR *) (LPSTR(this) + sizeof(WORD));
      break ;
    case ER_KEYELEM     :
    case ER_DATAELEM    :
      res = this + 1;
      break ;
    case ER_CONSTSTRING :
      res = (ElemRef FAR *) (LPSTR(this) + sizeof(WORD) + lstrlen(x.str) + 1);
      break ;
    case ER_CONSTINT    :
      res = (ElemRef FAR *) (LPSTR(this) + sizeof(WORD) + sizeof(DWORD));
      break ;
    case ER_OP          :
    case ER_PARAMETER   :
    case ER_RESULT      :
      res = (ElemRef FAR *) (LPSTR(this) + sizeof(WORD) + sizeof(WORD));
      break ;
    }
  return res;
  }

// Ausfuehrungsfunktionen
///////////////////////////////////////
void OnEndOfSelection (LPVOID params,LPBTRSTATEMENT stmt)  { }
void OnMsg (LPVOID params,LPBTRSTATEMENT stmt) { WIN_ASSERT_TEXT (FALSE,LPSTR(params)); }
void DoNothing (LPVOID params,LPBTRSTATEMENT stmt) { }
void OnUseKey (WORD Number,LPBTRSTATEMENT stmt) 
  {
  stmt->KeyNmbr = Number;
  if (stmt->KeyBuffer != NULL) FreeGlobMem (stmt->KeyBuffer) , stmt->KeyBuffer = NULL;
  if (stmt->KeyNmbr != 0xFFFF) {
    LPBTRVTABLE t = LPBTRVTABLE(stmt->req->TableDef[0]->GetDLLDef());
    LPKEYDEF k = t->GetKey (stmt->KeyNmbr,FALSE);
    stmt->KeyBuffer = GetGlobMem (k->KeySize);
    }
  }
void OnUseKey (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  OnUseKey (*(LPWORD)params,stmt);
  }
void OnDBOp (WORD Op,WORD ExtraCmd,LPBTRSTATEMENT stmt)
  {
  TestDBOpContext (Op,stmt);
  if (Op == B_GETPOS) {
    unsigned bs = sizeof(DWORD);
    BTRCALL (Op,stmt->File->pb,LPSTR(&stmt->recPosition),&bs,
              NULL,0,(char) stmt->KeyNmbr
            );
    }
  else if ((Op == B_INSERT) || (Op == B_UPDATE)) {
    stmt->opStatus =
      BTRCALL (Op,stmt->File->pb,LPSTR(stmt->File->btrBuffer),&stmt->bufferSize,
                LPSTR(stmt->KeyBuffer),(unsigned char) GetBlockSize(stmt->KeyBuffer),
                (char) stmt->KeyNmbr
              );
    }
  else {
    LPSTR buffer;
    if (ExtraCmd == DBOP_KEYONLY) {
      buffer = NULL;
      stmt->bufferSize = 0;
      Op += 50;
      }
    if (ExtraCmd == DBOP_NOWAITLOCK) {
      WIN_ASSERT(FALSE);
      }
    else {
      buffer = stmt->File->btrBuffer;
      stmt->bufferSize = BUFFER_SIZE;
      if ((Op == B_GETNEXTEXTENDED) || (Op == B_GETPREVEXTENDED)) {
        // Jetzt wird komplizierter
        WORD fOffs = SetFilter (stmt,buffer,stmt->filter);
        SetFieldsToExtract (buffer,fOffs,stmt->req,0,stmt->RecsToGet);
        }
      }
    WIN_ASSERT(stmt->KeyBuffer != NULL);
    if (Op == B_GETDIRECT)
      *(LPDWORD)buffer = stmt->recPosition;
    stmt->opStatus = 
      BTRCALL (Op,stmt->File->pb,buffer,&stmt->bufferSize,
                LPSTR(stmt->KeyBuffer),(unsigned char) GetBlockSize(stmt->KeyBuffer),
                (char) stmt->KeyNmbr
              );
    }
  }
void OnDBOp (LPVOID params,LPBTRSTATEMENT stmt)
  {
  OnDBOp ((LPWORD(params))[0],(LPWORD(params))[0],stmt);
  }
LPBLOBDESC BtrStatement::ReadBlob (DWORD Size,DWORD recPosition)
  {
  static BlobDesc dres;
  dres.Size = Size ;
  dres.hGmem = GlobalAlloc (GMEM_MOVEABLE,Size);
  char huge *actPtr = (char huge *) GlobalLock (dres.hGmem);
  // Aktuelle Position lesen
  char chBuffer[1024];
  LPTABLEDEF d = req->TableDef[0];
  LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
  DWORD ActOffset = t->GetDescRef()->RecordLength ;
  GLOBALHANDLE hGtmp = GlobalAlloc (GMEM_MOVEABLE,MAXCHUNKLEN);
  LPVOID buffer = LPVOID (GlobalLock (hGtmp));
  for ( ; ; ) {
    DWORD FAR *rPos = (DWORD FAR *) chBuffer ;
    *rPos = recPosition ;
    ChunkDescriptor FAR *cd = (ChunkDescriptor FAR *) (rPos + 1) ;
    cd->SubFunction = GETDIRECTCHUNK_INDIRECT ;
    cd->NumChunks = 1 ;
    ChunkStruct FAR *csi = (ChunkStruct FAR *) (cd + 1) ;
    csi->ChunkOffset = ActOffset ;
    csi->ChunkLen = min(MAXCHUNKLEN,Size);
    csi->ChunkBuffer = buffer ;
    unsigned SizeDone = sizeof(DWORD) + sizeof (*cd) + sizeof(*csi) ;
    opStatus =
      BTRCALL (B_GETDIRECTCHUNK,File->pb,chBuffer,&SizeDone,
                NULL,0,
                -2
              );
    if ((opStatus == 0) && (SizeDone != csi->ChunkLen))
      opStatus = 103 ;
    TestST (opStatus,File->Path) ;
    if (opStatus == 0) {
      // Zeiger weiterschalten
      hmemcpy (actPtr,buffer,csi->ChunkLen);
      Size -= csi->ChunkLen ;
      if (Size == 0L) {
        // Alles gemacht, gut so.
        break ;
        }
      ActOffset += csi->ChunkLen ;
      actPtr += csi->ChunkLen ;
      }
    else {
      // So nicht, mein Herr
      GlobalUnlock (dres.hGmem) ;
      GlobalFree (dres.hGmem) ;
      return NULL ;
      }
    }
  GlobalUnlock (dres.hGmem);
  GlobalUnlock (hGtmp);
  GlobalFree (hGtmp);

  return &dres ;
  }
LPBLOBDESC BtrStatement::ReadBlob ()
  {
  LPTABLEDEF d = req->TableDef[0];
  LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
  int Offs = -1 ;
  for (int i = 0 ; i < d->GetAnzVars() ; i++) {
    LPVARDEF v = d->GetVarDef(i);
    if (v->mType == VAR_BLOB) {
      LPDDSVARDESC   vb = LPDDSVARDESC (v->GetDLLData());
      LPVBTRV b = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vb->b.dOffs);
      Offs = b->VarOffset;
      break ;
      }
    }
  WIN_ASSERT (Offs >= 0);
  DWORD Size ;
  if (bufferSize >= Offs + sizeof(DWORD)) {
    Size = *(DWORD FAR *) (File->btrBuffer + Offs) ;
    }
  else {
    Size = 0L ;
    }
  if (Size > 0L) {
    // Da isn Chunk, der wird Stueckweise gelesen
    OnDBOp (B_GETPOS,0,this);

    return ReadBlob (Size,recPosition);
    }
  else
    return NULL ;
  }
void OnStore (WORD pos,LPBTRSTATEMENT stmt,BOOL getPrimKey)
  {
  if (stmt->opStatus == 0) {
    DBRecord FAR *r = new DBRecord (stmt->req);
    LPVOID hdata = NULL;
    if (r->GetType () == DBR_TYPE_FULL) {
      LPTABLEDEF d = stmt->req->TableDef[0];
      LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
      for (WORD i = 0 ; i < WORD(d->GetAnzVars()) ; i++) {
        LPVARDEF v = d->GetVarDef(i);
        if (v != NULL) {
          if (v->mType == VAR_BLOB) {
            LPBLOBDESC b = stmt->ReadBlob ();
            if (b != NULL) {
              r->Initialize (i,b,sizeof(*b));
              }
            }
          else {
            WORD rSize;
            LPVOID res = LPDDSVARDESC (v->GetDLLData())->
                    Extract(t,stmt->File->btrBuffer,stmt->bufferSize,&rSize,&hdata);
            if (res != NULL)
              r->Initialize (i,res,rSize);
            }
          }
        }
      }
    else {
      for (WORD i = 0 ; i < r->GetAnzVars() ; i++) {
        WORD VarID;
        if (r->GetTableNumber (i) != 0) break;
        LPTABLEDEF d = r->GetTableDef (i,&VarID);
        LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
        LPVARDEF v = d->GetVarDef(VarID);
        if (v != NULL) {
          if (v->mType == VAR_BLOB) {
            LPBLOBDESC b = stmt->ReadBlob ();
            if (b != NULL) {
              r->Initialize (i,b,sizeof(*b));
              }
            }
          else {
            WORD rSize;
            LPVOID res = LPDDSVARDESC (v->GetDLLData())->
                    Extract(t,stmt->File->btrBuffer,stmt->bufferSize,&rSize,&hdata);
            if (res != NULL)
              r->Initialize (i,res,rSize);
            }
          }
        }
      }
    FreeHData (hdata);
    if (getPrimKey) {
      PrimKey k;
      r->CalcPrimKey (0,&k);
      r->SetPrimKey (&k);
      }
    // So, noch den Join
    if (stmt->SatisfyJoin (r)) {
      stmt->RecsToGet -- ;
      stmt->res->AddLine (WORD(stmt->req->AnzTables),pos);
      stmt->res->SetRes (0,r);
      }
    else {
      delete r;     // No nicht..
      }
    }
  }
void OnStore (LPVOID params,LPBTRSTATEMENT stmt)
  {
  OnStore (*(LPWORD (params)),stmt,TRUE);
  }
struct RecordExtension {
  RecordExtension FAR *Next;
  LPDBRECORD r ;
  DWORD btrPos ;
  DWORD Size;
  };
RecordExtension FAR *BlobList,FAR *BlockedList;
void PushRecordToBlobList (LPDBRECORD r,DWORD btrPos,DWORD Size)
  {
  RecordExtension FAR *h = (RecordExtension FAR *) GetGlobMem (sizeof *h);
  h->Next = BlobList;
  h->btrPos = btrPos ;
  h->r = r;
  h->Size = Size;
  BlobList = h ;
  }
void PushRecordToBlockedList (LPDBRECORD r,DWORD btrPos)
  {
  RecordExtension FAR *h = (RecordExtension FAR *) GetGlobMem (sizeof *h);
  h->Next = BlockedList;
  h->btrPos = btrPos ;
  h->r = r;
  BlockedList = h ;
  }
void WorkOnBlobList (LPBTRSTATEMENT stmt)
  {
  for ( RecordExtension FAR *h = BlobList ; BlobList != NULL ; h = BlobList ) {
    BlobList = h->Next ;
    for (WORD i = 0 ; i < h->r->GetAnzVars() ; i++) {
      WORD VarID;
      if (h->r->GetTableNumber (i) != 0) break;
      LPTABLEDEF d = h->r->GetTableDef (i,&VarID);
      LPVARDEF v = d->GetVarDef(VarID);
      if ((v != NULL) && (v->mType == VAR_BLOB)) {
        LPBLOBDESC bd = stmt->ReadBlob (h->Size,h->btrPos);
        if (bd != NULL) {
          h->r->Initialize (i,bd,sizeof(*bd));
          }
        }
      }
    FreeGlobMem (h);
    }
  }
void WorkOnBlockedList (LPBTRSTATEMENT stmt)
  {
  for (RecordExtension FAR *h = BlockedList ; BlockedList != NULL ; h = BlockedList ) {
    stmt->recPosition = h->btrPos ;
    OnDBOp (B_GETDIRECT,0,stmt);
    TestST (stmt->opStatus,stmt->File->Path);
    LPVOID hdata = NULL;
    for (WORD i = 0 ; i < h->r->GetAnzVars() ; i++) {
      WORD VarID;
      if (h->r->GetTableNumber (i) != 0) break;
      LPTABLEDEF d = h->r->GetTableDef (i,&VarID);
      LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
      LPVARDEF v = d->GetVarDef(VarID);
      if (v != NULL) {
        LPDDSVARDESC vd = LPDDSVARDESC (v->GetDLLData());
        if (vd->mapType == MAPTYPE_MBLOCKED) {
          WORD rSize;
          LPVOID res = LPDDSVARDESC (v->GetDLLData())->
                  Extract(t,stmt->File->btrBuffer,stmt->bufferSize,&rSize,&hdata);
          if (res != NULL)
            h->r->Initialize (i,res,rSize);
          }
        }
      }
    FreeHData (hdata);
    BlockedList = h->Next ;
    FreeGlobMem (h);
    }
  }

WORD StoreMulti (WORD Pos,LPBTRSTATEMENT stmt,BOOL getPrimKey,LPVOID KeyBuffer,char KeyNmbr)
  {
  WORD res = 0;
  if ((stmt->opStatus == 0) || 
         (stmt->opStatus == ENDOFFILE) ||
         (stmt->opStatus == REJECT_COUNT) ||
         (stmt->opStatus == REJECT_NOMORE)) {
    BOOL recSet = FALSE ;
    RecordImage_header FAR *hd = (RecordImage_header FAR *) stmt->File->btrBuffer;
    RecordImage FAR *img = (RecordImage FAR *) (hd + 1);
    BOOL recRead = FALSE ;
    int Status = stmt->opStatus ;
    DWORD aPos;
    for (WORD count = 0 ; count < hd->AnzRecords ; count++) {
      DBRecord FAR *r = new DBRecord (stmt->req);
      LPSTR data = LPSTR(img+1);
      BOOL mtypePushed = FALSE ;
      for (WORD i = 0 ; i < r->GetAnzVars() ; i++) {
        WORD VarID;
        if (r->GetTableNumber (i) != 0) break;
        LPTABLEDEF d = r->GetTableDef (i,&VarID);
        LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
        LPVARDEF v = d->GetVarDef(VarID);
        if (v != NULL) {
          LPDDSVARDESC vd = LPDDSVARDESC (v->GetDLLData());
          if (vd->mapType == MAPTYPE_FIELD) {
            // Standardfeld
            LPVBTRV   vb = LPVBTRV (LPSTR(t->GetVarRef(FALSE)) + vd->b.dOffs);
            WORD rSize;
            if (v->mType == VAR_BLOB) {
              if (!recRead) {
                OnDBOp (B_GETPOS,0,stmt);
                aPos = stmt->recPosition;
                recRead = TRUE ;
                }
              DWORD FAR *Size = (DWORD FAR *) vd->Extract_extended (t,data,stmt->bufferSize,&rSize);
              if ((Size != NULL) && (*Size != 0L))
                PushRecordToBlobList (r,img->btrPos,*Size);
              }
            else {
              LPVOID res = vd->Extract_extended(t,data,stmt->bufferSize,&rSize);
              if (res != NULL)
                r->Initialize (i,res,rSize);
              }
            data += vb->VarLen;
            }
          else if (vd->mapType == MAPTYPE_MBLOCKED) {
            // Markieren, dass dieser Satz noch genauer analysiert werden muss
            if (!mtypePushed) {
              PushRecordToBlockedList (r,img->btrPos);
              mtypePushed = TRUE ;
              }
            if (!recRead) {
              OnDBOp (B_GETPOS,0,stmt);
              aPos = stmt->recPosition;
              recRead = TRUE ;
              }
            }
          }
        }
      img = (RecordImage FAR *) (LPSTR(img + 1) + img->rLength);
      if (getPrimKey) {
        PrimKey k;
        r->CalcPrimKey (0,&k);
        r->SetPrimKey (&k);
        }
      // Und eventuelle Joins
      if (stmt->SatisfyJoin (r)) {
        stmt->RecsToGet -- ;
        stmt->res->AddLine (WORD(stmt->req->AnzTables),Pos);
        stmt->res->SetRes (0,r);
        recSet = TRUE ;
        }
      else
        delete r;     // No nicht..
      }
    res = count ;
    WorkOnBlobList (stmt);        // Noch einige Kleinigkeiten abarbeiten
    WorkOnBlockedList (stmt);
    if (recRead) {
      stmt->bufferSize = stmt->GetFirstBufferSize();
      *(LPDWORD)stmt->File->btrBuffer = aPos;
      stmt->opStatus = 
        BTRCALL (B_GETDIRECT,stmt->File->pb,stmt->File->btrBuffer,&stmt->bufferSize,
                  LPSTR(KeyBuffer),(unsigned char) GetBlockSize(KeyBuffer),
                  (char) KeyNmbr
                );
      if (stmt->opStatus == 22)
        stmt->opStatus = 0;
      TestST (stmt->opStatus,stmt->File->Path);
      }
    stmt->opStatus = Status ;
    }
  return res;
  }
void StoreMulti (LPVOID params,LPBTRSTATEMENT stmt)
  {
  StoreMulti (*(LPWORD(params)),stmt,TRUE);
  }
int stackptr;
#define PNSTACKDEPTH  20
struct {
  LPVOID Data;
  BOOL ExternNull;
  } StackData[PNSTACKDEPTH];
void Push (LPVOID data,WORD Size,BOOL ExternNull)
  {
  LPVOID h;
  if (data != NULL) {
    h = GetGlobMem (Size);
    lmemcpy (h,data,Size);
    }
  else
    h = NULL;
  if (StackData[stackptr].Data != NULL) FreeGlobMem (StackData[stackptr].Data);
  StackData[stackptr].Data = h;
  StackData[stackptr].ExternNull = ExternNull;
  stackptr ++ ;
  }
LPVOID Pop(BOOL FAR *ExternNull)
  {
  stackptr --;
  WIN_ASSERT(stackptr >= 0);
  if (ExternNull != NULL)
    *ExternNull = StackData[stackptr].ExternNull;
  return StackData[stackptr].Data;
  }
WORD StackElemSize()
  {
  return GetBlockSize(StackData[stackptr-1].Data);
  }
void ClearStack()
  {
  for (int i = 0 ; i < PNSTACKDEPTH ; i++)
    if (StackData [i].Data != NULL) FreeGlobMem (StackData[i].Data) , StackData[i].Data = NULL;
  }
typedef void (* DOOPERATOR) (LPBTRSTATEMENT stmt);
void Nothing   (LPBTRSTATEMENT stmt) { WIN_ASSERT (FALSE) ; }
void BinaryCat (LPBTRSTATEMENT stmt) 
  { 
  LPVOID r2 = Pop() ; 
  LPVOID r1 = Pop() ; 
  if ((r1 != NULL) && (r2 != NULL)) {
    LPVOID r = GetGlobMem(GetBlockSize(r1) + GetBlockSize(r2));
    lmemcpy (r,r1,GetBlockSize(r1));
    lmemcpy (LPSTR(r)+GetBlockSize(r1),r2,GetBlockSize(r2));
    Push (r,GetBlockSize(r));
    FreeGlobMem(r);
    }
  else
    Push (NULL,0);
  }
void Padd (LPBTRSTATEMENT stmt) 
  { 
  LPVOID size = Pop() ; 
  LPVOID obj = Pop() ; 
  if ((obj != NULL) && (size != NULL)) {
    WIN_ASSERT(GetBlockSize(obj) <= *(LPWORD)size);
    LPVOID r = GetGlobMem(*(LPWORD (size)));
    lmemcpy (r,obj,GetBlockSize(obj));
    lmemset (LPSTR(r)+GetBlockSize(obj),'\0',*(LPWORD (size)) - GetBlockSize(obj));
    Push (r,GetBlockSize(r));
    FreeGlobMem(r);
    }
  else
    Push (NULL,0);
  }
void Extract (LPBTRSTATEMENT stmt)
  {
  LPDWORD end = LPDWORD(Pop());
  LPDWORD beg = LPDWORD(Pop());
  LPSTR data = LPSTR(Pop());
  if ((end != NULL) && (beg != NULL) && (data != NULL) && 
          (GetBlockSize(data) >= WORD(*end)) && (*end > *beg))
    Push (data+*beg,WORD(*end-*beg));
  else
    Push (NULL,0);
  }
void StrCat (LPBTRSTATEMENT stmt) 
  { 
  LPSTR s2 = LPSTR(Pop()) ; 
  LPSTR s1 = LPSTR(Pop()) ; 
  if ((s1 != NULL) && (s2 != NULL) && (*s1) && (*s2)) {
    LPSTR r = LPSTR(GetGlobMem(lstrlen(s1) + lstrlen(s2) + 1));
    lstrcpy (r,s1);
    lstrcat (r,s2);
    Push (r,GetBlockSize(r));
    FreeGlobMem(r);
    }
  else
    Push (NULL,0);
  }
char NextInAlternate (BYTE ch,LPBTRSTATEMENT stmt)
  {
  if (stmt->File->AlternateDefined) {
    char b = stmt->File->AlternateSequence[ch] + 1;
    char cbest = 0;
    int dold = 256;
    for (int i = 0 ; i < 256 ; i++) {
      int d = (stmt->File->AlternateSequence[i] - b);
      if ((d >= 0) && (d < dold))
        cbest = char (i) , dold = d;
      }
    return cbest;
    }
  else
    return ch + 1;
  }
void NextChar (LPBTRSTATEMENT stmt) 
  { 
  LPSTR s = LPSTR(Pop()) ; 
  if ((s != NULL) && (*s)) {
    LPSTR r = LPSTR(GetGlobMem(lstrlen(s) + 1));
    lstrcpy (r,s);
    r[lstrlen(r)-1] = NextInAlternate(BYTE(r[lstrlen(r)-1]),stmt);
    Push (r,GetBlockSize(r));
    FreeGlobMem(r);
    }
  else
    Push (NULL,0);
  }
void AddLong (LPBTRSTATEMENT stmt) 
  { 
  LPDWORD s1 = LPDWORD(Pop()) ; 
  LPDWORD s2 = LPDWORD(Pop()) ; 
  if ((s1 != NULL) && (s2 != NULL)) {
    DWORD r = *s1 + *s2 ;
    Push (&r,sizeof(r));
    }
  else
    Push (NULL,0);
  }
void MulLong (LPBTRSTATEMENT stmt) 
  { 
  LPDWORD s1 = LPDWORD(Pop()) ; 
  LPDWORD s2 = LPDWORD(Pop()) ; 
  if ((s1 != NULL) && (s2 != NULL)) {
    DWORD r = *s1 * *s2 ;
    Push (&r,sizeof(r));
    }
  else
    Push (NULL,0);
  }
void DivLong (LPBTRSTATEMENT stmt) 
  { 
  LPDWORD s1 = LPDWORD(Pop()) ; 
  LPDWORD s2 = LPDWORD(Pop()) ; 
  if ((s1 != NULL) && (s2 != NULL)) {
    DWORD r = *s2 / *s1 ;
    Push (&r,sizeof(r));
    }
  else
    Push (NULL,0);
  }
void SubLong (LPBTRSTATEMENT stmt) 
  { 
  LPDWORD s1 = LPDWORD(Pop()) ; 
  LPDWORD s2 = LPDWORD(Pop()) ; 
  if ((s1 != NULL) && (s2 != NULL)) {
    DWORD r = *s2 - *s1 ;
    Push (&r,sizeof(r));
    }
  else
    Push (NULL,0);
  }
void Increment (LPBTRSTATEMENT stmt) 
  { 
  LPVOID s1 = Pop() ; 
  if (s1 != NULL) {
    if (GetBlockSize (s1) == 1) {
      BYTE res = *((BYTE FAR *) s1) + 1 ;
      Push (&res,sizeof(res));
      }
    else if (GetBlockSize (s1) == 2) {
      WORD res = *((WORD FAR *) s1) + 1 ;
      Push (&res,sizeof(res));
      }
    else if (GetBlockSize (s1) == 4) {
      DWORD res = *((DWORD FAR *) s1) + 1 ;
      Push (&res,sizeof(res));
      }
    else
      WIN_ASSERT(FALSE);
    }
  else
    Push (NULL,0);
  }
void Decrement (LPBTRSTATEMENT stmt) 
  { 
  LPVOID s1 = Pop() ; 
  if (s1 != NULL) {
    if (GetBlockSize (s1) == 1) {
      BYTE res = *((BYTE FAR *) s1) - 1 ;
      Push (&res,sizeof(res));
      }
    else if (GetBlockSize (s1) == 2) {
      WORD res = *((WORD FAR *) s1) - 1 ;
      Push (&res,sizeof(res));
      }
    else if (GetBlockSize (s1) == 4) {
      DWORD res = *((DWORD FAR *) s1) - 1 ;
      Push (&res,sizeof(res));
      }
    else
      WIN_ASSERT(FALSE);
    }
  else
    Push (NULL,0);
  }
static DOOPERATOR doOperator[] = { 
/* OPERATOR_UNKNOWN    0 */ Nothing ,
/* OPERATOR_BINCAT     1 */ BinaryCat ,
/* OPERATOR_PADD       2 */ Padd ,
/* OPERATOR_EXTRACT    3 */ Extract ,
/* OPERATOR_STRCAT     4 */ StrCat ,
/* OPERATOR_NEXTCHAR   5 */ NextChar ,
/* OPERATOR_ADDLONG    6 */ AddLong ,
/* OPERATOR_MULLONG    7 */ MulLong ,
/* OPERATOR_INCREMENT  8 */ Increment ,
/* OPERATOR_DECREMENT  9 */ Decrement ,
/* OPERATOR_DIVLONG   10 */ DivLong ,
/* OPERATOR_SUBLONG   11 */ SubLong
  };

void ElemRef::DoIt (LPBTRSTATEMENT stmt)
  {
  LPVOID res;
  WORD   Size;
  switch (Type) {
    case ER_KEYELEM :
      res = x.v.Extract (LPSTR(stmt->KeyBuffer)+x.v.VarOffset,&Size);
      Push (res,Size);
      break ;
    case ER_DATAELEM :
      res = x.v.Extract (LPSTR(stmt->File->btrBuffer)+x.v.VarOffset,&Size);
      Push (res,Size);
      break ;
    case ER_CONSTSTRING :
      Push (x.str,lstrlen(x.str)+1);
      break ;
    case ER_CONSTINT :
      Push (&x.iVal,sizeof(x.iVal));
      break ;
    case ER_PARAMETER :
      Push (stmt->req->Param[x.parNum],GetBlockSize (stmt->req->Param[x.parNum]));
      break ;
    case ER_OP :
      (* doOperator [x.op]) (stmt);
      break ;
    case ER_RESULT :
      res = stmt->res->act->rec[0]->Get (x.ResColomn);
      Push (res,GetBlockSize(res));
      break ;
    case ER_POP :
      // Nix mehr zu machen...
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  }
void ElemRef::SetRes (LPBTRSTATEMENT stmt)
  {
  switch (Type) {
    case ER_KEYELEM :
      if (x.v.DataType != BDT_ZSTRING) {
        WIN_ASSERT (GetBlockSize (stmt->KeyBuffer) >= x.v.VarOffset + StackElemSize());
        }
      x.v.SetData (LPSTR(stmt->KeyBuffer)+x.v.VarOffset,Pop());
      break ;
    case ER_DATAELEM :
      x.v.SetData (LPSTR(stmt->File->btrBuffer)+x.v.VarOffset,Pop());
      break ;
    case ER_CASCADE :
      stmt->CallCascade (Pop());
      break;
    case ER_PUSH :
      // Einfach nichts tun
      break ;
    case ER_PARAMETER :
      // Parameter wird als Resultat verwendet
      {
      if (stmt->req->Param[x.parNum] != NULL)
        FreeGlobMem (stmt->req->Param[x.parNum]);
      LPVOID res = Pop();
      if (res != NULL) {
        stmt->req->Param[x.parNum] = GetGlobMem (GetBlockSize(res));
        lmemcpy (stmt->req->Param[x.parNum],res,GetBlockSize(res));
        }
      else
        stmt->req->Param[x.parNum] = NULL ;
      }
      break ;
    default :
      WIN_ASSERT(FALSE);
    }
  }
void OnAssign (LPVOID params,LPBTRSTATEMENT stmt)
  {
  // 1. Ueberspringen des Resultates
  ElemRef FAR *res = (ElemRef FAR *) (LPSTR(params) + sizeof(WORD));
  ElemRef FAR *end = (ElemRef FAR *) (LPSTR(params) + *(LPWORD(params)));
  // Ausfuehren aller Operationen
  for (ElemRef FAR *h = res->Next() ; h < end ; h = h->Next()) {
    h->DoIt (stmt);
    }
  res->SetRes (stmt);
  }
void OnAbort (LPVOID params,LPBTRSTATEMENT stmt)
  {
  stmt->retVal = *(LPWORD)params;
  }
struct PackList {
  int AnzVars;
  int VarSize;
  };
FilterHeader FAR *FilterStatement (LPBTRSTATEMENT stmt,FilterHeader FAR *f)
  {
  FilterHeader FAR *res ;
  BOOL doList = (f->cmpCode == BCMP_LIST) ;
  if (doList)
    f->cmpCode = BCMP_EQUAL ;
  else
    stmt->PushToFilter (f,sizeof(*f));
  LPWORD expsize = LPWORD (f + 1);
  ElemRef FAR *end = (ElemRef FAR *) (LPSTR(expsize) + *expsize);
  for (ElemRef FAR *h = (ElemRef FAR *) (expsize+1) ; h < end ; h = h->Next()) {
    h->DoIt (stmt);
    }
  VBtrv v;
  v.DataType   = f->btrDataType;
  v.VarOffset = 0;
  v.VarLen    = f->VarLen;
  v.Dimension = 1;
  v.EntryLen  = sizeof(v);
  v.Name[0]   = '\0';
  LPVOID Buffer = GetGlobMem (f->VarLen);
  BYTE FAR *op = (BYTE FAR *) end;
  if (doList) {
    PackList FAR *l = (PackList FAR *) Pop();
    if (l == NULL) {
      char teststr[128];
      wsprintf (teststr,"Listenschluessel existiert nicht in %d",stmt->req->SelectionName);
      WIN_ASSERT_TEXT (FALSE,teststr);
      }
    LPVOID hptr = GetGlobMem (l->VarSize);
    LPSTR actvar = LPSTR(l + 1);
    for (int i = 0 ; i < l->AnzVars ; i++) {
      stmt->PushToFilter (f,sizeof(*f));
      lmemcpy (hptr,actvar,l->VarSize);
      v.SetData (Buffer,hptr);
      actvar += l->VarSize;
      stmt->LastOp = GetBlockSize(stmt->filter);
      if (i == (l->AnzVars - 1)) 
        stmt->PushToFilter(op,1);
      else {
        BYTE vop = BOP_OR ;
        stmt->PushToFilter(&vop,1);
        }
      stmt->IncAnzTerms();
      stmt->PushToFilter(Buffer,GetBlockSize(Buffer));
      }
    FreeGlobMem (hptr);
    }
  else {
    v.SetData (Buffer,Pop());
    stmt->LastOp = GetBlockSize(stmt->filter);
    stmt->PushToFilter(op,1);
    stmt->IncAnzTerms();
    stmt->PushToFilter(Buffer,GetBlockSize(Buffer));
    }
  FreeGlobMem (Buffer);
  if (*op == BOP_END) res = NULL ;
  else                res = (FilterHeader FAR *) (op + 1);
  if (doList)
    f->cmpCode = BCMP_LIST ;
  return res;
  }
void OnFilter (LPVOID params,LPBTRSTATEMENT stmt)
  {
  stmt->ClearFilter();
  FilterHeader FAR *f = (FilterHeader FAR *)(LPSTR(params) + sizeof(WORD));
  for ( ; f != NULL ; )
    f = FilterStatement (stmt,f);
  }
void OnNextFilter (LPVOID params,LPBTRSTATEMENT stmt)
  {
  BYTE FAR *aop = (BYTE FAR *)(LPSTR(params) + sizeof(WORD));
  if (stmt->filter != NULL) {
    BYTE FAR *lop = ((BYTE FAR *) stmt->filter) + stmt->LastOp;
    *lop = *aop;
    }
  FilterHeader FAR *f = (FilterHeader FAR *) (aop + 1);
  for ( ; f != NULL ; )
    f = FilterStatement (stmt,f);
  }
void OnTestFilter (LPVOID params,LPBTRSTATEMENT stmt) { }
void OnNotTestFilter (LPVOID params,LPBTRSTATEMENT stmt) { }
void OnInitializeRecord (LPVOID params,LPBTRSTATEMENT stmt)
  {
  LPTABLEDEF  d    = stmt->req->TableDef[0];
  LPBTRVTABLE t    = LPBTRVTABLE (d->GetDLLDef());
  stmt->bufferSize = t->GetDescRef()->RecordLength;
  // Den Fixen Teil zuerst einmal auf '\0' setzen
  LPSTR Buffer     = stmt->File->btrBuffer;
  lmemset (Buffer,'\0',stmt->bufferSize);
  // Jetzt noch alle Elemente initilisieren
  for (WORD i = 0 ; i < WORD(d->GetAnzVars()) ; i++) {
    LPVARDEF v = d->GetVarDef(i);
    if (v != NULL)
      LPDDSVARDESC (v->GetDLLData())->
                SetNULLData (t,Buffer,&stmt->bufferSize,NULL);
    }
  }

// Anlegen eines Chunks fuer den ersten Datensatz
//////////////////////////////////////////////////////
void BtrStatement::CreateChunk (LPBTRVTABLE t,WORD mode)
  {
  LPRECDESC rd = t->GetDescRef ();
  int rNum ;
  LPVOID RecordData ;
  if (mode != SRMODE_IGNOREFIXED) {
    lpChunkHandles = (GLOBALHANDLE FAR *)GetGlobMem (sizeof(*lpChunkHandles));
    lpChunkHandles[0] = GlobalAlloc (GMEM_MOVEABLE,rd->RecordLength);
    RecordData = LPVOID(GlobalLock (lpChunkHandles[0]));
    lmemcpy (RecordData,File->btrBuffer,rd->RecordLength);
    rNum = 1 ;
    }
  else {
    rNum = 0 ;
    }
  ChunkDescriptor FAR *cd = (ChunkDescriptor FAR *) File->btrBuffer;
  if (USE_DIRECT)
    cd->SubFunction = UPDATECHUNK_RANDOMDIRECT;
  else
    cd->SubFunction = UPDATECHUNK_RANDOMINDIRECT;
  cd->NumChunks = rNum ;
  if (rNum > 0) {
    ChunkStruct FAR *cs0 = (ChunkStruct FAR *) (cd + 1) ;
    cs0->ChunkOffset = 0 ;
    cs0->ChunkLen = rd->RecordLength ;
    cs0->SetBuffer(RecordData);
    bufferSize = sizeof(ChunkDescriptor) + sizeof(ChunkStruct) ;
    }
  else
    bufferSize = sizeof(ChunkDescriptor);
  SkipChunkFrom = rd->RecordLength ;
  }

void BtrStatement::AddChunk (LPVOID Data,DWORD Size)
  {
  ChunkDescriptor FAR *cd = (ChunkDescriptor FAR *) File->btrBuffer;
  ChunkStruct FAR *csi = (ChunkStruct FAR *) (cd + 1) + cd->NumChunks;
  csi->ChunkOffset = SkipChunkFrom ;
  csi->ChunkLen = Size ;
  GLOBALHANDLE FAR *nChunkHandles = (GLOBALHANDLE FAR *) GetGlobMem (int ((cd->NumChunks + 1) * sizeof(GLOBALHANDLE)));
  if (lpChunkHandles != NULL) {
    lmemcpy (nChunkHandles,lpChunkHandles,sizeof(*lpChunkHandles) * cd->NumChunks);
    FreeGlobMem (lpChunkHandles);
    }
  lpChunkHandles = nChunkHandles;
  lpChunkHandles[cd->NumChunks] = csi->AllocateBuffer() ;
  hmemcpy (csi->ChunkBuffer,Data,WORD (Size));
  SkipChunkFrom += Size ;
  cd->NumChunks ++ ;
  bufferSize += sizeof(ChunkStruct);
  doSkipChunk = TRUE ;
  }

void BtrStatement::SkipChunk ()
  {
  ChunkDescriptor FAR *cd = (ChunkDescriptor FAR *) File->btrBuffer;
  bufferSize = sizeof(ChunkStruct);
  cd->SubFunction = UPDATECHUNK_SKIP ;
  cd->NumChunks = SkipChunkFrom ;
  OnDBOp (B_UPDATECHUNK,0,this);
  if (opStatus == 103) opStatus = 0 ;
  }

void BtrStatement::AddChunk (LPBLOBDESC d)
  {
  if (d != NULL) {
    DWORD s = d->Size ;
    char huge *h = (char huge *) GlobalLock (d->hGmem);
    for ( ; ; ) {
      DWORD as = min(MAXCHUNKLEN,s);
      if (as > 0) {
        AddChunk (h,as);
        h += as ;
        s -= as ;
        }
      else
        break ;
      }
    GlobalUnlock (d->hGmem);
    }
  else {
    doSkipChunk = TRUE ;
    }
  }

void UpdateAllChunks (LPBTRSTATEMENT stmt)
  {
  ChunkDescriptor FAR *cd = (ChunkDescriptor FAR *) stmt->File->btrBuffer;
  int Nums = int (cd->NumChunks) ;
  ChunkStruct FAR *csi = (ChunkStruct FAR *) (cd + 1) ;
  ChunkStruct FAR *csiBackup = (ChunkStruct FAR *) GetGlobMem (sizeof(*csi) * int(cd->NumChunks));
  lmemcpy (csiBackup,csi,sizeof(*csi) * int(cd->NumChunks));
  for (int i = 0 ; i < Nums ; i++) {
    csi[0] = csiBackup[i] ;
    cd->NumChunks = 1 ;
    if (USE_DIRECT) {
      lmemcpy (csi+1,csi[0].ChunkBuffer,int(csi[0].ChunkLen));
      stmt->bufferSize = sizeof(ChunkDescriptor) + sizeof(ChunkStruct) + int(csi[0].ChunkLen) ;
      }
    else
      stmt->bufferSize = sizeof(ChunkDescriptor) + sizeof(ChunkStruct) ;
    BOOL doRepeat = TRUE ;
    for (int count = 0 ; ((count < LOCK_RETRY_COUNT) && (doRepeat)) ; count++ ) {
      OnDBOp (B_UPDATECHUNK,0,stmt);
      doRepeat = (stmt->opStatus == 84) ;
      if (doRepeat)
        doWait (count);
      }
    if (IsCritical (stmt->opStatus))
      TestST (stmt->opStatus,stmt->File->Path);
    if (stmt->opStatus != 0)
      break ;       // Keinesfalls weitermachen, sonst steht hinten ein
                    // Semmel
    }
  cd->NumChunks = Nums ;
  FreeGlobMem (csiBackup);
  }

void BtrStatement::ClearChunkBuffers()
  {
  ChunkDescriptor FAR *cd = (ChunkDescriptor FAR *) File->btrBuffer;
  for (int i = 0 ; i < int (cd->NumChunks) ; i++) {
    GlobalFree (lpChunkHandles[i]);
    }
  cd->NumChunks = 0 ;
  FreeGlobMem (lpChunkHandles);
  lpChunkHandles = NULL;
  }

WORD OnSetRecord (LPVOID params,LPBTRSTATEMENT stmt,WORD mode,BOOL doRemove) 
  {
  // Setzen eines Records aus dem RecBuffer[0]
  //////////////////////////////////////////////
  WORD resOp;
  LPTABLEDEF  d    = stmt->req->TableDef[0];
  LPBTRVTABLE t    = LPBTRVTABLE (d->GetDLLDef());
  LPSTR Buffer;
  stmt->doSkipChunk = FALSE ;
  if ((mode != SRMODE_IGNOREBLOBS) && (d->HoldBlobs())) {
    stmt->CreateChunk (t,mode);
    Buffer = stmt->ChunkBuffer (0); // Chunkoperation
    resOp = B_UPDATECHUNK ;
    }
  else {
    Buffer = stmt->File->btrBuffer; // StandardUpdate
    resOp = B_UPDATE ;
    }
  LPVOID      h    = NULL;
  // Und los gehts
  LPDBRECORD rec = stmt->res->First()->rec[0];
  if (rec->GetType () == DBR_TYPE_FULL) {
    LPTABLEDEF d = stmt->req->TableDef[0];
    LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
    for (WORD i = 0 ; i < WORD(d->GetAnzVars()) ; i++) {
      LPVARDEF v = d->GetVarDef(i);
      if (v != NULL) {
        if (v->mType == VAR_BLOB) {
          LPBLOBDESC bd = LPBLOBDESC(rec->Get(i));
          if (bd != NULL) {
            if (mode != SRMODE_IGNOREBLOBS)
              stmt->AddChunk (bd);
            if (mode != SRMODE_IGNOREFIXED) {
              LPDWORD lpSz = LPDWORD(GetGlobMem (sizeof(*lpSz)));
              *lpSz = bd->Size ;
              LPDDSVARDESC (v->GetDLLData())->
                      SetData (t,Buffer,&stmt->bufferSize,lpSz,&h);
              FreeGlobMem (lpSz);
              }
            }
          else {
            if (mode != SRMODE_IGNOREFIXED)
              LPDDSVARDESC (v->GetDLLData())->
                      SetNULLData (t,Buffer,&stmt->bufferSize,&h);
            }
          }
        else {
          if (mode != SRMODE_IGNOREFIXED) {
            LPVOID Data = rec->Get (i);
            if (Data != NULL)
              LPDDSVARDESC (v->GetDLLData())->
                      SetData (t,Buffer,&stmt->bufferSize,Data,&h);
            else
              LPDDSVARDESC (v->GetDLLData())->
                      SetNULLData (t,Buffer,&stmt->bufferSize,&h);
            }
          }
        }
      }
    }
  else {
    for (WORD i = 0 ; i < rec->GetAnzVars() ; i++) {
      WORD VarID;
      LPTABLEDEF d = rec->GetTableDef (i,&VarID);
      if (d->GetTableID() != stmt->req->TableDef[0]->GetTableID()) continue;    
                // Der wird schon noch beim join kommen
      LPBTRVTABLE t = LPBTRVTABLE(d->GetDLLDef());
      LPVARDEF v = d->GetVarDef(VarID);
      if (v != NULL) {
        if (v->mType == VAR_BLOB) {
          LPBLOBDESC bd = LPBLOBDESC(rec->Get(i));
          if (bd != NULL) {
            if (mode != SRMODE_IGNOREBLOBS)
              stmt->AddChunk (bd);
            if (mode != SRMODE_IGNOREFIXED) {
              LPDWORD lpSz = LPDWORD(GetGlobMem (sizeof(*lpSz)));
              *lpSz = bd->Size ;
              LPDDSVARDESC (v->GetDLLData())->
                      SetData (t,Buffer,&stmt->bufferSize,lpSz,&h);
              FreeGlobMem (lpSz);
              }
            }
          else {
            if (mode != SRMODE_IGNOREFIXED)
              LPDDSVARDESC (v->GetDLLData())->
                      SetNULLData (t,Buffer,&stmt->bufferSize,&h);
            }
          }
        else {
          if (mode != SRMODE_IGNOREFIXED) {
            LPVOID Data = rec->Get (i);
            if (Data != NULL)
              LPDDSVARDESC (v->GetDLLData())->
                      SetData (t,Buffer,&stmt->bufferSize,Data,&h);
            else
              LPDDSVARDESC (v->GetDLLData())->
                      SetNULLData (t,Buffer,&stmt->bufferSize,&h);
            }
          }
        }
      }
    }
  if (mode != SRMODE_IGNOREFIXED)
    SetHData (t,Buffer,&stmt->bufferSize,h);

  // Diese Linie abnehmen
  if (doRemove) {
    RecBufferLine FAR *n = stmt->res->first->Next;
    FreeGlobMem (stmt->res->first);
    stmt->res->first = n;
    }
  return resOp ;
  }

void OnSetRecord (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  OnSetRecord (params,stmt,SRMODE_IGNOREBLOBS,TRUE);
  }

void OnTestDBStatus (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  TestST (stmt->opStatus,stmt->File->Path);
  }
void OnSetReject (LPVOID params,LPBTRSTATEMENT stmt)
  {
  stmt->RejectCountSet = TRUE ;
  stmt->RejectCount = *LPWORD(params);
  }
void PushToLockList (LPVOID params,LPBTRSTATEMENT stmt) 
  {
#ifdef UEBERLEGT
  LONG ConnID = CallNCPLock (stmt->res->act->rec[0]->GetPrimKey(),
                             stmt->res->act->rec[0]->GetTableID(),
                             COMMAND_LOCK
                            );
  if (ConnID == 0) {
    stmt->res->act->rec[0]->setLocked();
    LockListElem FAR *e = (LockListElem FAR *) GetGlobMem (sizeof(*e));
    e->Next = stmt->lele;
    stmt->lele = e;
    e->key     = *stmt->res->act->rec[0]->GetPrimKey();
    e->TableID = stmt->res->act->rec[0]->GetTableID();
    }
#else
  stmt->res->act->rec[0]->setLocked();
#endif
  }
void OnSetPrimKey (LPVOID params,LPBTRSTATEMENT stmt)
  {
  LPVOID parData = stmt->req->Param[0];
  WIN_ASSERT (stmt->KeyBuffer != NULL);
  if (parData == NULL) {
    lmemset (stmt->KeyBuffer,'\0',GetBlockSize(stmt->KeyBuffer));
    }
  else {
    WIN_ASSERT (GetBlockSize (stmt->KeyBuffer) >= GetBlockSize(parData));
    lmemcpy (stmt->KeyBuffer,parData,GetBlockSize(parData));
    if (GetBlockSize (stmt->KeyBuffer) >= GetBlockSize(parData))
      lmemset (LPSTR(stmt->KeyBuffer)+GetBlockSize(parData),'\0',GetBlockSize (stmt->KeyBuffer) - GetBlockSize(parData));
    }
  }
LPBTRVCOMMAND NextEndOfSelection (LPVOID params,LPBTRSTATEMENT stmt) { return NULL ; }
LPBTRVCOMMAND NextMsg (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND (LPSTR(params) + lstrlen(LPSTR(params)) + 1) ; }
LPBTRVCOMMAND NextOnFirst (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_GETFIRST) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnLast (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_GETLAST) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnNext (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_GETNEXT) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnPrev (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_GETPREV) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnDelete (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_DELETE) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnInsert (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_INSERT) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnUpdate (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_UPDATE) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnGet (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->Op == DBOP_GET) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextUseKey (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND (LPSTR(params) + sizeof(WORD)) ; }
LPBTRVCOMMAND NextDBOp (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  LPWORD par = LPWORD(params);
  if ((par[1] == DBOP_KEYONLY) || (par[1] == DBOP_NOWAITLOCK))
    return LPBTRVCOMMAND(par+2);
  else                        
    return LPBTRVCOMMAND(par+1);
  }
LPBTRVCOMMAND NextStore (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND(LPSTR(params) + sizeof(WORD)) ; }
LPBTRVCOMMAND NextAssign (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND(LPSTR(params) + *(LPWORD(params))) ; }
LPBTRVCOMMAND NextOnSuccess     (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->opStatus == 0          ) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnEndOfFile   (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  return LPBTRVCOMMAND (((stmt->opStatus == ENDOFFILE) || 
                         (stmt->opStatus == REJECT_COUNT) ||
                         (stmt->opStatus == REJECT_NOMORE)) ?
      LPSTR(params) + sizeof(WORD) : 
      LPSTR(params) + * LPWORD(params)) ; 
  }
LPBTRVCOMMAND NextOnRecNotFound (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->opStatus == REQNOTFOUND) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnMore    (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->RecsToGet > 0) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)); }
LPBTRVCOMMAND NextEndOnMore (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->RecsToGet == 0) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * ((short FAR *)(params)) + sizeof(WORD)) ; }
LPBTRVCOMMAND NextAbort (LPVOID params,LPBTRSTATEMENT stmt) { return NULL ; }
LPBTRVCOMMAND NextOnError (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((stmt->opStatus != 0) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextOnFatalError (LPVOID params,LPBTRSTATEMENT stmt) 
  { return LPBTRVCOMMAND (((stmt->opStatus != 0) && (stmt->opStatus != ENDOFFILE) &&
        (stmt->opStatus != REQNOTFOUND) && (stmt->opStatus != REJECT_COUNT) && (stmt->opStatus != REJECT_NOMORE))
          ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextIf (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  LPWORD par = LPWORD(stmt->req->Param[(LPWORD(params))[1]]);
  BOOL flag = ((par != NULL) && (*par == (LPWORD(params))[2]));
  return LPBTRVCOMMAND ((flag) ? LPSTR(params) + 3 * sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ;
  }
LPBTRVCOMMAND NextOnReduced (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  if (stmt->req->AnzElems > 0) {
    LPTABLEDEF t = stmt->req->TableDef[0];
    for (int i = 0 ; i < stmt->req->AnzElems ; i++) {
      if (stmt->req->elem[i].TableNumber == 0) {
         LPVARDEF v = LPVARDEF(t->GetVarDef(stmt->req->elem[i].VarID));
         if ((v != NULL) && (!LPDDSVARDESC(v->GetDLLData())->IsReducedAllowed()))
           return LPBTRVCOMMAND(LPSTR(params) + * LPWORD(params)) ;   // Nix
        }
      }
    return LPBTRVCOMMAND(LPSTR(params) + sizeof(WORD));            // Alles ok
    }
  else
    return LPBTRVCOMMAND(LPSTR(params) + * LPWORD(params)) ;       // Sowieso nix
  }
LPBTRVCOMMAND NextForAll    (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  stmt->res->act = stmt->res->First();
  return LPBTRVCOMMAND ((stmt->res->act != NULL) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)); 
  }
LPBTRVCOMMAND NextEndForAll (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  stmt->res->act = stmt->res->act->Next;
  return LPBTRVCOMMAND ((stmt->res->act == NULL) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * ((short FAR *)(params)) + sizeof(WORD)) ; 
  }
LPBTRVCOMMAND NextRepeat    (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  return LPBTRVCOMMAND (LPSTR(params) + sizeof(WORD));
  }
LPBTRVCOMMAND NextEndRepeat (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  return LPBTRVCOMMAND (LPSTR(params) + * ((short FAR *)(params)) + sizeof(WORD));
  }
LPBTRVCOMMAND NextBreak (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  return LPBTRVCOMMAND (LPSTR(params) + * LPWORD(params));
  }
LPBTRVCOMMAND NextContinue (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  return LPBTRVCOMMAND (LPSTR(params) + * LPWORD(params) - 2 * sizeof(WORD));
  }
LPBTRVCOMMAND NextFilter (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND (LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextTestFilter (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((TestFilter(stmt)) ? LPSTR(params) + sizeof(WORD) : LPSTR(params) + * LPWORD(params)) ; }
LPBTRVCOMMAND NextNotTestFilter (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND ((TestFilter(stmt)) ? LPSTR(params) + * LPWORD(params) : LPSTR(params) + sizeof(WORD)) ; }
LPBTRVCOMMAND NextSetRecord (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND(params) ; }
LPBTRVCOMMAND NextTestDBStatus (LPVOID params,LPBTRSTATEMENT stmt) { return LPBTRVCOMMAND(params) ; }
LPBTRVCOMMAND NextOnParam (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  LPWORD parnr = LPWORD(params);  // parnr[0] .. Else Offset
                                  // parnr[1] .. Anzahl Parameter
                                  // parnr[2-..] .. Parameter, die zu untersuchen sind
  BOOL flag = TRUE ;
  for (WORD i = 0 ; ((i < parnr[1]) && (flag)) ; i++)
    flag = (((stmt->req->Param[parnr[2+i] & 0x7FFF] != NULL) && ((parnr[2+i] & 0x8000) == 0)) ||
            ((stmt->req->Param[parnr[2+i] & 0x7FFF] == NULL) && ((parnr[2+i] & 0x8000) != 0)));

  return LPBTRVCOMMAND ((flag) ? LPSTR(params) + (2 + parnr[1]) * sizeof(WORD) : LPSTR(params) + parnr[0]) ;
  }
LPBTRVCOMMAND NextOnSetReject (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  return LPBTRVCOMMAND(LPSTR(params) + sizeof(WORD));
  }
LPBTRVCOMMAND NextOnInitializeRecord (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  return LPBTRVCOMMAND(params);
  }
LPBTRVCOMMAND NextOnLock (LPVOID params,LPBTRSTATEMENT stmt) 
  { 
  return LPBTRVCOMMAND ((stmt->req->doLock[0]) ? LPSTR(params) + sizeof(WORD) : 
                                                 LPSTR(params) + * LPWORD(params)
                       ) ; 
  }
LPBTRVCOMMAND NextPushToLockList (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  return LPBTRVCOMMAND(params);
  }
LPBTRVCOMMAND NextSetPrimKey (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  return LPBTRVCOMMAND(params);
  }
LPBTRVCOMMAND NextSetInnerJoins (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  return LPBTRVCOMMAND(params);
  }
void OnSetInnerJoins (LPVOID params,LPBTRSTATEMENT stmt) 
  {
  stmt->JustInnerJoins = TRUE ;
  }

typedef void (* DOSTMT) (LPVOID params,LPBTRSTATEMENT stmt);
typedef LPBTRVCOMMAND (* NEXTSTMT) (LPVOID params,LPBTRSTATEMENT stmt);
static DOSTMT doIt [] = {
  OnEndOfSelection        , // DBFNC_END
  OnMsg                   , // DBFNC_MSG
  DoNothing               , // DBFNC_ONFIRST
  DoNothing               , // DBFNC_ONLAST  
  DoNothing               , // DBFNC_ONNEXT  
  DoNothing               , // DBFNC_ONPREV  
  DoNothing               , // DBFNC_ONDELETE
  DoNothing               , // DBFNC_ONINSERT
  DoNothing               , // DBFNC_ONUPDATE
  DoNothing               , // DBFNC_ONGET   
  OnUseKey                , // DBFNC_USEKEY
  OnDBOp                  , // DBFNC_DBOP
  OnStore                 , // DBFNC_STORE
  OnAssign                , // DBFNC_ASSIGN
  DoNothing               , // DBFNC_ONSUCCESS    
  DoNothing               , // DBFNC_ONENDOFFILE  
  DoNothing               , // DBFNC_ONRECNOTFOUND
  DoNothing               , // DBFNC_ONMORE   
  DoNothing               , // DBFNC_ENDONMORE
  OnAbort                 , // DBFNC_ABORT
  DoNothing               , // DBFNC_ONERROR
  DoNothing               , // DBFNC_IF
  DoNothing               , // DBFNC_ONREDUCED
  StoreMulti              , // DBFNC_STOREMULTI
  DoNothing               , // DBFNC_ONFATALERROR
  DoNothing               , // DBFNC_FORALL
  DoNothing               , // DBFNC_ENDFORALL
  OnFilter                , // DBFNC_FILTER
  OnTestFilter            , // DBFNC_TESTFILTER
  OnSetRecord             , // DBFNC_SETRECORD
  OnTestDBStatus          , // DBFNC_TESTDBSTATUS
  DoNothing               , // DBFNC_ONPARAM
  OnSetReject             , // DBFNC_SETREJECT
  OnInitializeRecord      , // DBFNC_INITIALIZERECORD
  DoNothing               , // DBFNC_ONLOCK
  PushToLockList          , // DBFNC_PUSHTOLOCKLIST
  DoNothing               , // DBFNC_REPEAT
  DoNothing               , // DBFNC_ENDREPEAT
  DoNothing               , // DBFNC_BREAK
  OnNextFilter            , // DBFNC_MOREFILTER 
  OnSetPrimKey            , // DBFNC_SETPRIMKEY
  OnSetInnerJoins         , // DBFNC_SETINNERJOINS
  DoNothing               , // DBFNC_CONTINUE
  OnNotTestFilter           // DBFNC_NOTTESTFILTER
  };
static NEXTSTMT Next [] = {
  NextEndOfSelection      , // DBFNC_END
  NextMsg                 , // DBFNC_MSG
  NextOnFirst             , // DBFNC_ONFIRST
  NextOnLast              , // DBFNC_ONLAST  
  NextOnNext              , // DBFNC_ONNEXT  
  NextOnPrev              , // DBFNC_ONPREV  
  NextOnDelete            , // DBFNC_ONDELETE
  NextOnInsert            , // DBFNC_ONINSERT
  NextOnUpdate            , // DBFNC_ONUPDATE
  NextOnGet               , // DBFNC_ONGET   
  NextUseKey              , // DBFNC_USEKEY
  NextDBOp                , // DBFNC_DBOP
  NextStore               , // DBFNC_STORE
  NextAssign              , // DBFNC_ASSIGN
  NextOnSuccess           , // DBFNC_ONSUCCESS    
  NextOnEndOfFile         , // DBFNC_ONENDOFFILE  
  NextOnRecNotFound       , // DBFNC_ONRECNOTFOUND
  NextOnMore              , // DBFNC_ONMORE   
  NextEndOnMore           , // DBFNC_ENDONMORE
  NextAbort               , // DBFNC_ABORT
  NextOnError             , // DBFNC_ONERROR
  NextIf                  , // DBFNC_IF
  NextOnReduced           , // DBFNC_ONREDUCED
  NextStore               , // DBFNC_STOREMULTI
  NextOnFatalError        , // DBFNC_ONFATALERROR
  NextForAll              , // DBFNC_FORALL
  NextEndForAll           , // DBFNC_ENDFORALL
  NextFilter              , // DBFNC_FILTER
  NextTestFilter          , // DBFNC_TESTFILTER
  NextSetRecord           , // DBFNC_SETRECORD
  NextTestDBStatus        , // DBFNC_TESTDBSTATUS
  NextOnParam             , // DBFNC_ONPARAM
  NextOnSetReject         , // DBFNC_SETREJECT
  NextOnInitializeRecord  , // DBFNC_INITIALIZERECORD
  NextOnLock              , // DBFNC_ONLOCK
  NextPushToLockList      , // DBFNC_PUSHTOLOCKLIST
  NextRepeat              , // DBFNC_REPEAT
  NextEndRepeat           , // DBFNC_ENDREPEAT
  NextBreak               , // DBFNC_BREAK
  NextFilter              , // DBFNC_MOREFILTER 
  NextSetPrimKey          , // DBFNC_SETPRIMKEY
  NextSetInnerJoins       , // DBFNC_SETINNERJOINS
  NextContinue            , // DBFNC_CONTINUE
  NextNotTestFilter         // DBFNC_NOTTESTFILTER
  };

void FreeLocks (LPBTRSTATEMENT stmt)
  {
#ifdef UEBERLEGT
  for (LockListElem FAR *h = stmt->lele ; h != NULL ; ) {
    LockListElem FAR *n = h->Next ;
    LONG ConnID = CallNCPLock (&h->key,
                                h->TableID,
                                COMMAND_UNLOCK
                              );
    FreeGlobMem (h);
    h = n;
    }
#endif
  stmt->lele = NULL;
  }

int DoDBCall (LPBTRVTABLE t,WORD Op,int AnzLines,LPDBREQUEST req,LPBTRSTATEMENT stmt,RecBuffer FAR *res)
  {
  switch (Op) {
    case DBOP_RESET :
    case DBOP_UNLOCK :
      break ;
    default :
      LPACCESSDEF access = t->GetAccess (req->SelectionName,FALSE);
      if (access == NULL) {
        char outtxt[256];
        wsprintf (outtxt,"Zugriff %s in %s nicht definiert",req->SelectionName,req->TableDef[0]->GetName());
        WIN_ASSERT_TEXT (FALSE,outtxt);
        stmt->File->hGBuffer = ReleaseBufferHandle (stmt->File->hGBuffer);
        if (stmt->File->hGBuffer)
          stmt->File->btrBuffer = LPSTR(GlobalLock (stmt->File->hGBuffer));
        return DBCALL_ERROR_NOACCESS;
        }
      // Ausfuehren der Kommandos
      LPBTRVCOMMAND cmd = LPBTRVCOMMAND (access->Name + lstrlen(access->Name) + 1);
      stackptr = 0;
      for ( ; cmd != NULL ; ) {
        (* (doIt [*cmd])) (cmd+1,stmt);
        cmd = (* (Next[*cmd])) (cmd+1,stmt);
        }
      return stmt->retVal;
      break ;
    }
  return DBCALL_SUCCESS ;
  }

BOOL GetFile (LPBTRSTATEMENT stmt,BOOL first)
  {
  if (stmt->req->TableDef[0] != NULL) {
    stmt->File = GetFile (stmt->req->TableDef[0],stmt->req->AlternateName);
    stmt->File->hGBuffer = GetBufferHandle (stmt->File->hGBuffer);
    stmt->File->btrBuffer = LPSTR(GlobalLock (stmt->File->hGBuffer));
    stmt->File->SetTimeStamp();
    if ((stmt->File->isOpen) && (first)) {
      stmt->File->IncrementUseCount();
      }
    return stmt->File->FileStatDifferent;
    }
  else
    return TRUE ;
  }

int DBCall_Work (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  InitializeBuffers();

  switch (Op) {
    case DBOP_ENDOFCONVERSION :
      return DBCALL_SUCCESS;
    case DBOP_RESET :
      // Statement wieder freigeben
      if (*hstmt != NULL) {
        LPBTRSTATEMENT stmt = LPBTRSTATEMENT (*hstmt);
        if (stmt->File != NULL)
          stmt->File->DecrementUseCount();
        FreeLocks (stmt);
        if (stmt->TempTableID)
          GetTableAdmin()->FreeTemporaryTable (stmt->TempTableID);

        delete stmt;
        *hstmt = NULL ;
        }
      return DBCALL_SUCCESS;
    case DBOP_UNLOCK :
      // Locks wieder aufheben
      if (*hstmt != NULL) {
        LPBTRSTATEMENT stmt = LPBTRSTATEMENT (*hstmt);
        FreeLocks (stmt);
        }
      return DBCALL_SUCCESS;
    case DBOP_STARTOFUPDATE :
      return DBCALL_SUCCESS;
    case DBOP_ENDOFUPDATE :
      return DBCALL_SUCCESS;
    default :
      if (req->Type == DBCALLTYPE_CLOSEALL) {
        CloseAllDataFiles ();
        return DBCALL_SUCCESS ;
        }
      LPBTRSTATEMENT stmt = LPBTRSTATEMENT (*hstmt);
      // Laufende Initialisierungen
      BOOL first ;
      if (stmt == NULL) {
        stmt            = new BtrStatement ();
        *hstmt          = stmt;
        stmt->req       = req;
        first           = TRUE ;
        }
      else
        first           = FALSE ;
      stmt->retVal         = DBCALL_SUCCESS;
      stmt->req            = req;
      stmt->Op             = Op;
      stmt->RecsToGet      = AnzLines;
      stmt->res            = res;
      stmt->retVal         = DBCALL_SUCCESS;
      if (req->Type == DBCALLTYPE_CREATE)
        InCreate = TRUE ;
      BOOL gf = GetFile (stmt,first);
      LPBTRVTABLE t;
      if (req->TableDef[0] != NULL)
        t = LPBTRVTABLE(req->TableDef[0]->GetDLLDef());
      else
        t = NULL;
      if ((req->Type == DBCALLTYPE_EXECUTE) ||
          (req->Type == DBCALLTYPE_EXECUTESINGLE)) {
        stmt->retVal = DoDBGet (t,Op,AnzLines,req,stmt,res);
        }
      else if ((req->Type != DBCALLTYPE_TEST) && (req->Type != DBCALLTYPE_CREATE)) {
        if ((stmt->File != NULL) && (stmt->File->isOpen)) {
          if (!req->foreignDone)
            req->BuildForeign ();   // Und noch die Fremdzugriffe ...

          switch (req->Type) {
            case DBCALLTYPE_EXTENDED :
              stmt->retVal = DoDBCall (t,Op,AnzLines,req,stmt,res);
              break ;
            default :
              stmt->retVal = DoDBGet (t,Op,AnzLines,req,stmt,res);
              break ;
            }
          }
        else
          stmt->retVal = DBCALL_ERROR ;
        }
      else {
        stmt->retVal = (gf) ? DBCALL_NODATA : DBCALL_SUCCESS ;
        }
      // Stack der Polnischen Notation aufraemen
      ClearStack();
      stmt->ClearFilter();
      WIN_ASSERT (stackptr == 0);
      if (stmt->File != NULL) {
        stmt->File->hGBuffer = ReleaseBufferHandle (stmt->File->hGBuffer);
        if (stmt->File->hGBuffer)
          stmt->File->btrBuffer = LPSTR(GlobalLock (stmt->File->hGBuffer));
        }
      return stmt->retVal;
      break ;
    }

  return DBCALL_SUCCESS ;
  }

DLLExport int _export WINAPI DBCall (WORD Op,int AnzLines,LPDBREQUEST req,LPVOID FAR *hstmt,RecBuffer FAR *res)
  {
  return DBCall_Work (Op,AnzLines,req,hstmt,res);
  }

