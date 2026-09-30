//////////////////////////////////////
//  Allgemeine Hilfsfunktionen
//////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/misc.cpv   1.50   24 Jan 2000 00:15:18   Hannes  $
//  $Log:   P:/marille/clinicum/rev/misc.cpv  $
// 
//    Rev 1.50   24 Jan 2000 00:15:18   Hannes
// MoveBlobData
// 
//    Rev 1.49   14 Dec 1999 13:09:44   Martin
// Blob-Fehlerkorrekturen
//
//    Rev 1.48   22 Nov 1999 18:02:00   Wolfgang
// 1.) AddBlobToBlob, ExtractDataFromBlob, ExtractBlob und bCmpBlob neu.
//
//    Rev 1.47   13 Oct 1999 23:28:48   Hannes
// Loeschen des Blobs..
//
//    Rev 1.46   30 Sep 1999 19:32:00   Martin
// BlobFromFile: wenn Datei 0 Byte lang -> keinen Blob anlegen (DelData)
//
//    Rev 1.45   29 Sep 1999 16:55:56   Wolfgang
// 1.) Vor Generieren Init-/DoneModuleHash aufrufen.
//
//    Rev 1.44   13 Jul 1999 18:58:22   Hannes
// Prototyp Tagesauslaustung
//
//    Rev 1.43   07 Jun 1999 09:15:34   Hannes
// Tagesauslastung
//
//    Rev 1.42   19 Apr 1999 10:00:54   Hannes
// Fehlerkorrektur Blob - Update mit Groessenaenderung
//
//    Rev 1.41   17 Feb 1999 21:01:12   Hannes
// Blob aufbereiten
//
//    Rev 1.40   17 Feb 1999 15:58:00   Wolfgang
// 1.) ClearlConnection fuer MakeTimeStamp.
//
//    Rev 1.39   21 Oct 1998 14:39:08   Wolfgang
// 1.) SetBit hat einen neuen (optionalen) Parameter, der festlegt,
//     ob das Bit auf 0 oder 1 gesetzt wird.
//
//    Rev 1.38   21 Oct 1998 14:24:08   Hannes
// BlobAufbereiten vom leeren Blob
//
//    Rev 1.37   28 Aug 1998 13:35:50   Hannes
// Entsprechende Resets
//
//    Rev 1.36   02 Aug 1998 14:47:02   Gerhold
// SetCLinicumEnvironment ... EnableToolTips
//
//    Rev 1.35   08 May 1998 18:20:44   Hannes
//
//    Rev 1.34   08 May 1998 18:07:52   Hannes
//
//    Rev 1.33   08 May 1998 09:56:22   Hannes
//
//    Rev 1.32   07 May 1998 15:17:14   Hannes
// DatenVomBlob - Fehlerkorrektur
//
//    Rev 1.31   28 Apr 1998 11:01:46   Hannes
// ErsteDatenVomBlob, WeitereDatenVomBlob
//
//    Rev 1.30   27 Apr 1998 12:51:54   Hannes
// BlobAufbereiten
//
//    Rev 1.29   21 Apr 1998 19:34:38   Hannes
// PushToBlock
//
//    Rev 1.28   01 Apr 1998 17:23:38   Gerhold
// GetObjLen, TwipsToDlg ... EM_FIXCONNECTION -> EM_CLEAR | EM_RESET
//
//    Rev 1.27   03 Mar 1998 08:57:50   Gerhold
// SetClinicumEnvironment wurde um den Tooltip-Font erweitert
//
//    Rev 1.26   12 Feb 1998 08:21:38   Hannes
// InterpreteDouble erweitert
//
//    Rev 1.25   09 Feb 1998 09:59:52   Hannes
// InterpreteDouble
//
//    Rev 1.24   31 Oct 1997 12:51:06   Hannes
// Timestampfunktion
//
//    Rev 1.23   27 Oct 1997 19:51:06   Hannes
// Diverse Fehlerkorrekturen
//
//    Rev 1.22   16 Sep 1997 17:10:20   Hannes
// Prototyp von Blobcompiler
//
//    Rev 1.21   01 Sep 1997 13:21:40   gerhold
// Bitmanipulationsroutinen
//
//    Rev 1.20   07 Aug 1997 14:07:50   Hannes
//
//    Rev 1.19   07 Aug 1997 11:53:10   Hannes
//
//    Rev 1.18   14 Jul 1997 17:15:44   Hannes
//
//    Rev 1.17   14 Jul 1997 12:50:20   Hannes
//
//    Rev 1.16   11 Jul 1997 10:43:38   Martin
// pragma pack(1) vor copyblob
//
//    Rev 1.15   11 Jul 1997 10:14:38   Hannes
//
//    Rev 1.14   27 May 1997 11:30:12   Hannes
// Fehlerkorrektur in AddStringToBlob
//
//    Rev 1.13   12 May 1997 08:48:34   Hannes
// BlobFromFile
//
//    Rev 1.12   28 Apr 1997 14:15:44   Hannes
//
//    Rev 1.11   14 Mar 1997 12:28:36   gerhold
// _hwrite ... #ifdef WIN32
//
//    Rev 1.10   13 Mar 1997 18:57:12   Hannes
// Verschiedene Funktionen, speziell fuer Blobs
//
//    Rev 1.9   19 Feb 1997 12:17:30   Hannes
// CheckScriptScroll
//
//    Rev 1.8   15 Jan 1997 11:51:44   HANNES
// GetDBPointer
//
//    Rev 1.7   28 Sep 1996 15:24:32   GERHOLD
// Funktion "SetCLINICUMEnvironment" ... setzt Source-Code spezifische Variablen
//
//    Rev 1.6   10 Jun 1996 10:09:54   GERHOLD
// pragma pack
//
//    Rev 1.5   04 Mar 1996 17:47:58   GERHOLD
// GetDBHandler
//
//    Rev 1.4   02 Feb 1996 10:35:34   GERHOLD
// 1.Umstellung auf 32 Bit
//
//    Rev 1.3   24 Aug 1995 00:20:20   HANNES
// DBWIN_ASSERT
//
//    Rev 1.2   31 Mar 1995 18:23:24   HANNES
//
//
//    Rev 1.1   20 Mar 1995 12:09:10   GERHOLD
// Konstantenhandling, RunNmbr, Schleifen, ...
//
//    Rev 1.0   24 Jun 1994 17:05:16   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dds.hpp"

#include "printer.hpp"
#include "sc2d.hpp"
#include "font.hpp"
#include "paint.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "dbrecord.hpp"
#include "scripthd.hpp"
#include "mdichild.hpp"
#define MODULENUM 10
#include "winass.hpp"
#include "winextra.hpp"

#include "cfield.hpp"

#include "hash.hpp"
#include "compile.hpp"

#define NODLL
#define WITHINDDS
#include "toolbar.hpp"

#include "fcontain.hpp"
#include "dllchild.hpp"
#include "frmobj.hpp"
#include "cutcont.hpp"
#include "cutedit.hpp"
#include "trcobj.hpp"

#include "for.hpp"

// Passwort - Verschluesselung
void strctopascal (char FAR *pstr,char FAR *cstr,int size)
  {
  lmemset (pstr,'\0',size);
  char convstr[256];
  pstr[0] = min (lstrlen (cstr),size-1);
  AnsiToOem (cstr,convstr);
  lstrncpy (pstr+1,convstr,size);
  }

DLLExport DLLHANDLE _export FAR PASCAL GetTransactionDLL ();
#pragma pack(1)
struct GetDBHandler_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetDBHandler (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDBHandler_param FAR *par = (GetDBHandler_param FAR *) param;
    DLLHANDLE th = GetTransactionDLL();
    LPSTR Name = GetDLLAdmin()->GetDLLEntry (th)->GetDLLFName ();
    c->WritelData (par->res,Name,lstrlen(Name)+1,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetClinicumEnvironment_param {
  WORD parSize;
  DWORD Index;     // welche Variable soll geaendert werden ?
  DWORD Value;     // der Wert der Variablen
  };
#pragma pack()


#define ENV_INDEX_EINGABEFELDMITFOCUS   0      // Aendert das Fokus-Verhalten
                                               // von cFields
#define ENV_INDEX_TOOLTIPFONT           1      // Aendert den Font fuer
                                               // die Kurzhilfe
#ifdef TOOLTIP
#define ENV_INDEX_TOOLTIPENABLED        2      // erlaubt die Windows-internen
                                               // Tooltips
#endif

#define ENV_INDEX_ERROR                 0xFFFF // Fehlerhafter Index


BOOL SetCLINICUMEnvironment (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    SetClinicumEnvironment_param FAR *par = (SetClinicumEnvironment_param FAR *) param;

    DBINT FAR *lpIndex = (DBINT FAR *) c->ReadlData (par->Index);
    DBINT Index;

    if (lpIndex == NULL) {
      DBWIN_ASSERT_TEXT (FALSE, "Ungültiger Index in CLINICUM Environment");
      Index = DBINT(ENV_INDEX_ERROR);
      }
    else
      Index = *lpIndex;

    switch (Index) {
      case ENV_INDEX_EINGABEFELDMITFOCUS:
        {
        DBBOOL FAR *lpValue = (DBBOOL FAR *) c->ReadlData (par->Value);
        if (lpValue == NULL) {
          DBWIN_ASSERT_TEXT (FALSE, "Fehlerhafter Wert bei ENV_INDEX_EINGABEFELDMITFOCUS");
          }
        else
          SetFocusFlag (*lpValue);
//          SelectFocusedFields = *lpValue;
        }
        break;

      case ENV_INDEX_TOOLTIPFONT:
        {
        DBINT FAR *lpFont = (DBINT FAR *) c->ReadlData (par->Value);
        if (lpFont == NULL) {
          DBWIN_ASSERT_TEXT (FALSE, "Fehlerhafter Wert bei ENV_INDEX_TOOLTIPFONT");
          }
        else
          SetToolTipFont (*lpFont);
        }
        break;

#ifdef TOOLTIP
      case ENV_INDEX_TOOLTIPENABLED:
        {
        DBBOOL FAR *lpValue = (DBBOOL FAR *)c->ReadlData (par->Value);
        if (lpValue == NULL) {
          DBWIN_ASSERT_TEXT (FALSE, "Fehlerhafter Wert bei ENV_INDEX_TOOLTIPENABLED");
          }
        else
          EnableToolTips (*lpValue);
        }
        break;
#endif

      default:
        break;
      }
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    SetClinicumEnvironment_param FAR *par = (SetClinicumEnvironment_param FAR *) param;
    c->ClearlConnection (par->Index,LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct GetDBPointer_param {
  WORD parSize;
  DWORD res;
  };
#pragma pack()

BOOL GetDBPointer (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GetDBPointer_param FAR *par = (GetDBPointer_param FAR *) param;
    DLLHANDLE th = GetTransactionDLL();
    LPVOID res = GetDLLAdmin()->GetDLLEntry (th)->DBGetPointer ();
    if (res != NULL) {
      c->WritelData (par->res,res,GetBlockSize(res),LPSTR(param) - sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->res,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct IsKeyPressed_param {
  WORD parSize;
  DWORD res;
  DWORD vk;
  };
#pragma pack()

BOOL IsKeyPressed (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    IsKeyPressed_param FAR *par = (IsKeyPressed_param FAR *) param;
    DBINT FAR *vk = (DBINT FAR *) c->ReadlData (par->vk);
    DBBOOL res;
    if ((vk != NULL) && (GetKeyState (*vk) < 0))
      res = TRUE ;
    else
      res = FALSE ;
    c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    IsKeyPressed_param FAR *par = (IsKeyPressed_param FAR *) param;
    c->ClearlConnection (par->vk,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct SetScrollProc_param {
  WORD parSize;
  DWORD procBeforeScroll;
  DWORD procAfterScroll;
  };
#pragma pack()

BOOL SetScrollProc (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    c->DrawContext()->PutDocumentExtraData (DED_SCROLLPROC,&param,sizeof(LPVOID));
    }
  if (mode & EM_RESET) {
    c->DrawContext()->RemoveDocumentExtraData (DED_SCROLLPROC);
    }
  return FALSE ;
  }

void CheckScriptScroll (mdiChild *c,int Num)
  {
  SetScrollProc_param FAR *FAR *lppar = (SetScrollProc_param FAR *FAR *)c->GetDocumentExtraData (DED_SCROLLPROC);
  if (lppar != NULL) {
    DWORD procToCall ;
    if (Num == 0) procToCall = (*lppar)->procBeforeScroll ;
    else          procToCall = (*lppar)->procAfterScroll ;
    c->ExCuteProc (procToCall,EM_LOAD | EM_CHANGETOTRUE);
    c->ExCuteProc (procToCall,EM_CLEAR | EM_RESET);
    }
  }

#pragma pack(1)
struct AddStringToBlob_param {
  WORD parSize;
  DWORD blob;
  DWORD String;
  };
#pragma pack()
DWORD NextSize (DWORD Size)
  {
  return ((Size / 0x4000) + 1) * 0x4000 ;
  }

void AddToBlob (BlobDesc FAR *n,LPVOID data,DWORD size)
  {
  if (n->hGmem) {
    DWORD nSize = n->Size + size ;
    DWORD actSize = GlobalSize (n->hGmem);
    if (actSize < nSize) {
      n->hGmem = GlobalReAlloc (n->hGmem,NextSize(nSize),GMEM_MOVEABLE);
      }
    }
  else {
    n->hGmem = GlobalAlloc (GMEM_MOVEABLE,NextSize (size));
    }
  char huge *Base = (char huge *) GlobalLock (n->hGmem);
  hmemcpy (Base + n->Size,data,size);
  n->Size += size ;
  GlobalUnlock (n->hGmem);
  }

BOOL AddStringToBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddStringToBlob_param FAR *par = (AddStringToBlob_param FAR *) param ;
    BlobDesc FAR *bdsc = (BlobDesc FAR *) c->ReadlData (par->blob);
    LPSTR str = LPSTR (c->ReadlData (par->String));
    BlobDesc n ;
    if (bdsc != NULL)
      n = *bdsc ;
    else {
      n.Size = 0L ;
      n.hGmem = NULL ;
      }
    if (str != NULL) {
      AddToBlob (&n,str,lstrlen(str));
      c->WritelData (par->blob,&n,sizeof(n),LPSTR(param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    AddStringToBlob_param FAR *par = (AddStringToBlob_param FAR *) param ;
    c->ClearlConnection (par->String,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

BOOL AddVoidDataToBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddStringToBlob_param FAR *par = (AddStringToBlob_param FAR *) param ;
    BlobDesc FAR *bdsc = (BlobDesc FAR *) c->ReadlData (par->blob);
    LPVOID data = LPSTR (c->ReadlData (par->String));
    BlobDesc n ;
    if (bdsc != NULL)
      n = *bdsc ;
    else {
      n.Size = 0L ;
      n.hGmem = NULL ;
      }
    if (data != NULL) {
      AddToBlob (&n,data,GetBlockSize(data));
      c->WritelData (par->blob,&n,sizeof(n),LPSTR(param) - sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    AddStringToBlob_param FAR *par = (AddStringToBlob_param FAR *) param ;
    c->ClearlConnection (par->String,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

BOOL AddBlobToBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    AddStringToBlob_param FAR *par = (AddStringToBlob_param FAR *) param ;
    BlobDesc FAR *bdsc = (BlobDesc FAR *) c->ReadlData (par->blob);
    LPBLOBDESC data = LPBLOBDESC (c->ReadlData (par->String));
    BlobDesc n ;
    if (bdsc != NULL)
      n = *bdsc ;
    else {
      n.Size = 0L ;
      n.hGmem = NULL ;
      }
    if ((data != NULL) && (data->hGmem != NULL) && (data->Size > 0)) {
      LPVOID add = GlobalLock (data->hGmem);
      if (add != NULL) {
        AddToBlob (&n,add,data->Size);
        c->WritelData (par->blob,&n,sizeof(n),LPSTR(param) - sizeof(WORD));
        }
      GlobalUnlock (data->hGmem);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    AddStringToBlob_param FAR *par = (AddStringToBlob_param FAR *) param ;
    c->ClearlConnection (par->String,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR GenerateScriptFromBlob_param {
  WORD parSize;
  DWORD blobIn;
  DWORD blobOut;
  DWORD FName;
  DWORD ofFlag;
  BOOL MitofFlag ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()
BOOL GenerateScriptFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    GenerateScriptFromBlob_param FAR *par = (GenerateScriptFromBlob_param FAR *) param;
    BlobDesc FAR *blobOut = (BlobDesc FAR *) c->ReadlData (par->blobOut);
    BOOL ofFlag;
    if (par->MitofFlag())
      ofFlag = c->ReadConstInt (par->ofFlag);
    else
      ofFlag = TRUE ;
    WIN_ASSERT (blobOut == NULL);
    BlobDesc FAR *blobIn = (BlobDesc FAR *) c->ReadlData (par->blobIn);
    LPSTR FName = LPSTR (c->ReadlData (par->FName));
    if ((blobIn != NULL) && (FName != NULL)) {
      DWORD rSize;
      InitModuleHash ();
      GLOBALHANDLE hGres = DoCompileFromBlob (blobIn->hGmem,blobIn->Size,FName,&rSize,ofFlag);
      DoneModuleHash ();
      if (hGres) {
        BlobDesc res ;
        res.Size = rSize;
        res.hGmem = hGres;
        c->WritelData (par->blobOut,&res,sizeof(res),LPSTR(param) - sizeof(WORD));
        }
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    GenerateScriptFromBlob_param FAR *par = (GenerateScriptFromBlob_param FAR *) param;
    c->ClearlConnection (par->blobOut,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct DelBlob_param {
  WORD parSize;
  DWORD blob;
  };
#pragma pack()
BOOL DelBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    DelBlob_param FAR *par = (DelBlob_param FAR *) param;
    BlobDesc FAR *blob = (BlobDesc FAR *) c->ReadlData (par->blob);
    if (blob != NULL) {
      if (blob->hGmem)
        GlobalFree (blob->hGmem);
      c->DellData (par->blob,LPSTR(param)-sizeof(WORD));
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DelBlob_param FAR *par = (DelBlob_param FAR *) param;
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct CopyBlob_param {
  WORD parSize;
  DWORD dest;
  DWORD source;
  };
#pragma pack()
BOOL CopyBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CopyBlob_param FAR *par = (CopyBlob_param FAR *) param;
    BlobDesc FAR *blob = (BlobDesc FAR *) c->ReadlData (par->source);
    if ((blob != NULL) && (blob->hGmem)) {
      BlobDesc bdest ;
      bdest.Size = blob->Size;
      bdest.hGmem = GlobalAlloc (GMEM_MOVEABLE,bdest.Size);
      LPSTR src = LPSTR (GlobalLock (blob->hGmem));
      LPSTR dest = LPSTR (GlobalLock (bdest.hGmem));
      hmemcpy (dest,src,bdest.Size);
      GlobalUnlock (bdest.hGmem);
      GlobalUnlock (blob->hGmem);
      c->WritelData (par->dest,&bdest,sizeof(bdest),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->dest,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CopyBlob_param FAR *par = (CopyBlob_param FAR *) param;
    c->ClearlConnection (par->source,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct ExtractBlob_param {
  WORD parSize;
  DWORD res;
  DWORD source;
  DWORD rbeg;
  DWORD rend;
  };
#pragma pack()
BOOL ExtractBlobData (mdiChild *c,LPVOID param,WORD mode,BOOL toBlob)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    ExtractBlob_param FAR *par = (ExtractBlob_param FAR *) param;
    LPBLOBDESC source = (LPBLOBDESC) c->ReadlData (par->source);
    if ((source != NULL) && (source->hGmem != NULL)) {
      int beg = -1, end = -1;
      LPLONG lpbeg = (LPLONG) c->ReadlData (par->rbeg);
      if (lpbeg != NULL)
        beg = *lpbeg;
      LPLONG  lpend = (LPLONG ) c->ReadlData (par->rend);
      if (lpend != NULL)
        end = *lpend;
      if ((end < 0) || (int (source->Size) <= end))
        end = source->Size - 1;
      if ((beg >= 0) && (beg <= end) && (int (source->Size) > end)) {
        int len = end - beg + 1;
        LPVOID sourcePtr = LPSTR (GlobalLock (source->hGmem)) + beg;
        if (toBlob) {
          LPBLOBDESC dest = (LPBLOBDESC) c->ReadlData (par->res);
          if (dest != NULL) dest->FreeHandle();
          BlobDesc bdest ;
          bdest.Size = len;
          bdest.hGmem = GlobalAlloc (GMEM_MOVEABLE,bdest.Size);
          LPSTR destPtr = LPSTR (GlobalLock (bdest.hGmem));
          hmemcpy (destPtr,sourcePtr,bdest.Size);
          GlobalUnlock (bdest.hGmem);
          c->WritelData (par->res,&bdest,sizeof(bdest),LPSTR(param)-sizeof(WORD));
          }
        else
          c->WritelData (par->res, sourcePtr, len, LPSTR(param) - sizeof(WORD));
        GlobalUnlock (source->hGmem);
        }
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    ExtractBlob_param FAR *par = (ExtractBlob_param FAR *) param;
    c->SetlConnection (par->source,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->rbeg,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->rend,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ExtractBlob_param FAR *par = (ExtractBlob_param FAR *) param;
    c->ClearlConnection (par->source,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rbeg,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->rend,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }
BOOL ExtractDataFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  return ExtractBlobData (c, param, mode, FALSE);
  }
BOOL ExtractBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  return ExtractBlobData (c, param, mode, TRUE);
  }

#pragma pack(1)
struct bBlobEqual_param {
  WORD parSize;
  DWORD blob1;
  DWORD blob2;
  DWORD forEqual;
  };
#pragma pack()
BOOL bBlobEqual (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE ;
  if (mode & (EM_LOAD | EM_UPDATE)) {
    bBlobEqual_param FAR *par = (bBlobEqual_param FAR *) param;
    LPBLOBDESC blob1 = (LPBLOBDESC) c->ReadlData (par->blob1);
    LPBLOBDESC blob2 = (LPBLOBDESC) c->ReadlData (par->blob2);
    DBBOOL FAR * forEqual = (DBBOOL FAR * ) c->ReadlData (par->forEqual);
    if ((blob1 != NULL) && (blob2 != NULL)) {
      BOOL isEqual;
      isEqual = ((blob1->Size == blob2->Size) &&
                 memcmp (GlobalLock (blob1->hGmem), GlobalLock (blob2->hGmem), blob1->Size));
      if (*forEqual)
        res = isEqual;
      else
        res = (!isEqual);
      }
    else if ((blob1 == NULL) && (blob2 == NULL) && (*forEqual))
      res = TRUE ;
    else if ((((blob1 == NULL) && (blob2 != NULL)) || ((blob1 != NULL) && (blob2 == NULL))) &&
             (!(*forEqual)))
      res = TRUE ;
    }
  if (mode & EM_FIXCONNECTION) {
    bBlobEqual_param FAR *par = (bBlobEqual_param FAR *) param;
    c->SetlConnection (par->blob1,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->blob2,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    bBlobEqual_param FAR *par = (bBlobEqual_param FAR *) param;
    c->ClearlConnection (par->blob1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->blob2,LPSTR(param)-sizeof(WORD));
    }
  return res ;
  }

#pragma pack(1)
struct BlobToFile_param {
  WORD parSize;
  DWORD file;
  DWORD blob;
  DWORD Size;
  };
#pragma pack()
BOOL BlobToFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BlobToFile_param FAR *par = (BlobToFile_param FAR *) param;
    BlobDesc FAR *blob = (BlobDesc FAR *) c->ReadlData (par->blob);
    HFILE FAR* lphFile = (HFILE FAR *) c->ReadlData (par->file);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;
    if (blob != NULL) {
#ifdef WIN32
      _hwrite (HFILE(*lphFile), (LPSTR)GlobalLock (blob->hGmem), blob->Size);
#else
      _hwrite (HFILE(*lphFile), GlobalLock (blob->hGmem), blob->Size);
#endif
      GlobalUnlock (blob->hGmem);
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    BlobToFile_param FAR *par = (BlobToFile_param FAR *) param;
    c->ClearlConnection (par->blob,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

BOOL BlobFromFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    BlobToFile_param FAR *par = (BlobToFile_param FAR *) param;
    HFILE FAR* lphFile = (HFILE FAR *) c->ReadlData (par->file);
    DBWIN_ASSERT ((lphFile != NULL) && (*lphFile)) ;
    BlobDesc b;
    if (par->parSize == sizeof(*par)) {
      LONG FAR *lpSize = (LONG FAR *) c->ReadlData (par->Size);
      DBWIN_ASSERT (lpSize != NULL);
      b.Size = *lpSize;
      }
    else {
      b.Size = _llseek (HFILE(*lphFile), 0L, SEEK_END);
      _llseek (HFILE(*lphFile), 0L, SEEK_SET);
      }
    if (b.Size > 0) {
      b.hGmem = GlobalAlloc (GMEM_MOVEABLE,b.Size);
#ifdef WIN32
      _hread (HFILE(*lphFile), (LPSTR)GlobalLock (b.hGmem), b.Size);
#else
      _hread (HFILE(*lphFile), GlobalLock (b.hGmem), b.Size);
#endif
      GlobalUnlock (b.hGmem);
      c->WritelData (par->blob,&b,sizeof(b),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->blob,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    BlobToFile_param FAR *par = (BlobToFile_param FAR *) param;
    c->ClearlConnection (par->file,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR CallWithSignature_param {
  WORD parSize;
  DBINT lastCalled;
  DWORD key;
  struct {
    DWORD signature;
    DWORD procToCall;
    } p[1];
  int Anz()
    {
    return (parSize - (sizeof(*this) - sizeof(p[0]))) / sizeof(p[0]);
    }
  };
#pragma pack()
BOOL CallWithSignature (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CallWithSignature_param FAR *par = (CallWithSignature_param FAR *) param;
    LPVOID key = c->ReadlData (par->key);
    RestoreListFnc rlf(c);
    if (key != NULL) {
      int Anz = par->Anz();
      int start = par->lastCalled;
      for (int i = start ; ; ) {
        LPVOID signature = c->ReadlData (par->p[i].signature);
        if ((signature != NULL) && (GetBlockSize(signature) == GetBlockSize(key)) &&
            (lmemcmp (signature,key,GetBlockSize (signature)))) {
          c->ExCuteProc (par->p[i].procToCall,EM_LOAD | EM_CHANGETOTRUE);
          c->ExCuteProc (par->p[i].procToCall,EM_CLEAR | EM_RESET);
          par->lastCalled = DBINT(i);
          break ;
          }
        i = (i < Anz - 1) ? i + 1 : 0 ;
        if (i == start) break ;
        }
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CallWithSignature_param FAR *par = (CallWithSignature_param FAR *) param;
    c->ClearlConnection (par->key,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR GetObjLen_param {
  WORD parSize;
  DWORD rSize;
  DWORD obj;
  };
#pragma pack()
BOOL GetObjLen (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    GetObjLen_param FAR *par = (GetObjLen_param FAR *) param;
    LPVOID obj = c->ReadlData (par->obj);
    WORD mType = c->GetDataType (par->obj);
    if (obj != NULL) {
      if (mType == VAR_BLOB) {
        LONG ObjSize = LPBLOBDESC (obj)->Size;
        c->WritelData (par->rSize,&ObjSize,sizeof(ObjSize),LPSTR(param)-sizeof(WORD));
        }
      else {
        DBINT ObjSize = DBINT(GetBlockSize (obj));
        c->WritelData (par->rSize,&ObjSize,sizeof(ObjSize),LPSTR(param)-sizeof(WORD));
        }
      }
    else
      c->DellData (par->rSize,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    GetObjLen_param FAR *par = (GetObjLen_param FAR *) param;
    c->SetlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_RESET | EM_CLEAR)) {
    GetObjLen_param FAR *par = (GetObjLen_param FAR *) param;
    c->ClearlConnection (par->obj,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR TwipsToDlg_param {
  WORD parSize;
  DWORD res;
  DWORD len;
  };
#pragma pack()
BOOL TwipsToDlg (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    TwipsToDlg_param FAR *par = (TwipsToDlg_param FAR *) param;
    float FAR *len = (float FAR *) c->ReadlData (par->len);
    if (len != NULL) {
      PaintContext pc(WBase::hFrameWin);
      pc.LogicalTwips ();
      int w = pc.YLOGtoPHYS(int (*len + 0.5));
      double bu;
      GetBaseUnit (&bu);
      float res = float (double(w) / bu);
      c->WritelData (par->res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    TwipsToDlg_param FAR *par = (TwipsToDlg_param FAR *) param;
    c->SetlConnection (par->len,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    TwipsToDlg_param FAR *par = (TwipsToDlg_param FAR *) param;
    c->ClearlConnection (par->len,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


#pragma pack(1)
struct FAR definebitarray_param {
  WORD parSize;
  DWORD BitObj;
  DWORD CntBytes;
  };
#pragma pack()

BOOL DefineBitArray (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    definebitarray_param FAR *par = (definebitarray_param FAR *) param;

    DBINT FAR *CntBytes = (DBINT FAR *)c->ReadlData (par->CntBytes);

    if ((CntBytes != NULL) && *CntBytes) {
      LPSTR res = LPSTR (GetGlobMem (*CntBytes));
      lmemset (res, '\0', *CntBytes);
      c->WritelData (par->BitObj, res, *CntBytes, LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->BitObj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    definebitarray_param FAR *par = (definebitarray_param FAR *) param;
    c->ClearlConnection (par->CntBytes,LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct FAR SetBit_param {
  WORD parSize;
  DWORD BitObj;
  DWORD BitPos;
  DWORD BitVal; // optional
  BOOL MitBitVal ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

static BYTE bit_pattern[] =
        { 0x01 , 0x02 , 0x04 , 0x08 , 0x10 , 0x20 , 0x40 , 0x80 } ;

BOOL SetBit (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    SetBit_param FAR *par = (SetBit_param FAR *) param;

    LPSTR BitObj = (LPSTR)c->ReadlData (par->BitObj);
    DBINT FAR *BitNum = (DBINT FAR *)c->ReadlData (par->BitPos);

    if (BitObj != NULL) {
      int ObjSize = GetBlockSize (BitObj);

      if (ObjSize > 0) {
        BYTE FAR *h = (BYTE FAR *)BitObj + (ObjSize - 1 - *BitNum / 8) ;
        BOOL setTo1;
        if (par->MitBitVal ()) {
          DBINT FAR *BitVal = (DBINT FAR *)c->ReadlData (par->BitVal);
          if (*BitVal)
            setTo1 = TRUE;
          else
            setTo1 = FALSE;
          }
        else
          setTo1 = TRUE;
        if (setTo1)
          *h |= bit_pattern [*BitNum % 8];
        else
          *h &= ~bit_pattern [*BitNum % 8];
        }

      c->WritelData (par->BitObj, BitObj, ObjSize, LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->BitObj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    SetBit_param FAR *par = (SetBit_param FAR FAR *) param;
    c->ClearlConnection (par->BitPos,LPSTR(param) - sizeof(WORD));
    if (par->MitBitVal ())
      c->ClearlConnection (par->BitVal,LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

extern LPVOID GetLastOffset (void);
BOOL IsBitSet (mdiChild *c,LPVOID param,WORD mode)
  {
  BOOL res = FALSE;

  if (mode & (EM_LOAD | EM_UPDATE)) {
    definebitarray_param FAR *par = (definebitarray_param FAR *) param;

    LPSTR BitObj = (LPSTR)c->ReadlData (par->BitObj);
    DBINT FAR *BitNum = (DBINT FAR *)c->ReadlData (par->CntBytes);

    if (BitObj != NULL) {
      int ObjSize = GetBlockSize (BitObj);

      if (ObjSize > 0) {
        BYTE FAR *h = (BYTE FAR *)BitObj + (ObjSize - 1 - *BitNum / 8) ;

        res = *h & bit_pattern [*BitNum % 8];
        }
      }
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    definebitarray_param FAR *par = (definebitarray_param FAR *) param;
    c->ClearlConnection (par->CntBytes,GetLastOffset());
    }

  return res;
  }


#pragma pack(1)
struct FAR bitop_param {
  WORD parSize;
  DWORD ResultObj;
  DWORD Obj1;
  DWORD Obj2;
  DWORD OpMode;
  };
#pragma pack()


#define  OPMODE_AND  0
#define  OPMODE_OR   1


BOOL BitAND (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    bitop_param FAR *par = (bitop_param FAR *) param;

    LPVOID ResultObj = (LPVOID)c->ReadlData (par->ResultObj);
    LPVOID Obj1 = (LPVOID)c->ReadlData (par->Obj1);
    LPVOID Obj2 = (LPVOID)c->ReadlData (par->Obj2);
    DBINT FAR *OpMode = (DBINT FAR *)c->ReadlData (par->OpMode);

    BOOL res = (ResultObj != NULL) && (Obj1 != NULL) && (Obj2 != NULL) && (OpMode != NULL);

    WIN_ASSERT_TEXT (res, "Ungueltiger Parameter bei Mengen-Objekt");

    if (res) {
      short sizeres = GetBlockSize (ResultObj);
      short size1 = GetBlockSize (Obj1);
      short size2 = GetBlockSize (Obj2);

      short  minsize, maxsize;
      LPVOID maxobj, minobj;


      if (size1 > size2) {
        minsize = size2;
        maxsize = size1;
        minobj = Obj2;
        maxobj = Obj1;
        }
      else {
        minsize = size1;
        maxsize = size2;
        minobj = Obj1;
        maxobj = Obj2;
        }

      //----------------------------------------------------------------
      // jetzt wird das laengere Array mit dem kleineren Array maskiert
      //----------------------------------------------------------------
      BYTE h;
      for (int i = 0; i < minsize; i++) {
        h = *((BYTE FAR *)maxobj + (maxsize - 1 - i));

        if (*OpMode == OPMODE_OR)
          h |= *((BYTE FAR *)minobj + (minsize - 1 - i));
        else if (*OpMode == OPMODE_AND)
          h &= *((BYTE FAR *)minobj + (minsize - 1 - i));

        *((BYTE FAR *)ResultObj + (sizeres - 1 - i)) = h;
        }

      //------------------------------------------------------
      // im OR-Modus wird solange maskiert bis die Laenge des
      // Resultates erreicht wurde
      //------------------------------------------------------
      if (*OpMode == OPMODE_OR) {
        if (maxsize > sizeres)
          maxsize = sizeres;

        for (int i = minsize; i < maxsize; i++) {
          h = *((BYTE FAR *)maxobj + (maxsize - 1 - i));
          *((BYTE FAR *)ResultObj + (sizeres - 1 - i)) |= h;
 
          }
        }

      c->WritelData (par->ResultObj, ResultObj, sizeres, LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->ResultObj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    bitop_param FAR *par = (bitop_param FAR *) param;
    c->ClearlConnection (par->Obj1,LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->Obj2,LPSTR(param) - sizeof(WORD));
    }
  return FALSE;
  }


BOOL BitNOT (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    bitop_param FAR *par = (bitop_param FAR *) param;

    LPSTR ResultObj = (LPSTR)c->ReadlData (par->ResultObj);
    LPSTR BitObj = (LPSTR)c->ReadlData (par->Obj1);

    BOOL res = (ResultObj != NULL) && (BitObj != NULL);

    WIN_ASSERT_TEXT (res, "Ungueltiger Parameter bei Mengen-Objekt");

    if (res) {
      int ResultSize = GetBlockSize (ResultObj);
      int ObjSize = GetBlockSize (BitObj);

      BOOL res = (ResultSize != ObjSize);

      WIN_ASSERT_TEXT (res, "Unterschiedliche Parameterlaenge");

      if (res) {
        BYTE h;
        for (int i = 0; i < ResultSize; i++) {
          h = *((BYTE FAR *)BitObj + (ObjSize - 1 - i)) ;

          *((BYTE FAR *)ResultObj + (ObjSize - 1 - i)) = ~h;
          }
        }

      c->WritelData (par->ResultObj, ResultObj, ObjSize, LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->ResultObj,LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_CLEAR | EM_RESET)) {
    bitop_param FAR *par = (bitop_param FAR *) param;
    c->ClearlConnection (par->Obj1,LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct FAR CRC_param {
  WORD parSize;
  DWORD Res;
  DWORD Obj;
  };
#pragma pack()

DLLExport DWORD _export WINAPI GetCRC32(LPSTR buffer,int  size,DWORD _crc);
BOOL CRC32 (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    LPVOID obj = c->ReadlData (par->Obj);
    if (obj != NULL) {
      DWORD res = GetCRC32 (LPSTR(obj),GetBlockSize(obj),0x3228321A);
      c->WritelData (par->Res,&res,sizeof(res),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->Res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    c->SetlConnection (par->Obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    c->ClearlConnection (par->Obj,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

BOOL Encrypt32 (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    LPSTR obj = LPSTR (c->ReadlData (par->Obj));
    static unsigned char PATTERN[6] = { 0xAB , 0x55 , 0x0F , 0xF0 , 0xD2 , 0xFF } ;
    if (obj != NULL) {
      LPSTR res = LPSTR (GetGlobMem (GetBlockSize (obj)));
      for ( WORD i = 0 ; i < GetBlockSize (obj) ; i++)
        res[i] = obj[i] ^ PATTERN[i % sizeof(PATTERN)] ;
      c->WritelData (par->Res,&res,GetBlockSize (obj),LPSTR(param)-sizeof(WORD));
      FreeGlobMem (res);
      }
    else
      c->DellData (par->Res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    c->SetlConnection (par->Obj,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    c->ClearlConnection (par->Obj,LPSTR(param)-sizeof(WORD));
    }

  return FALSE;
  }

extern DLLExport void _export FAR PASCAL TimeStamp (LPSTR Msg);
BOOL MakeTimeStamp (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    TimeStamp (LPSTR (c->ReadlData (par->Res)));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    CRC_param FAR *par = (CRC_param FAR *) param;
    c->ClearlConnection (par->Res,LPSTR(param) - sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct InterpreteDouble_param {
  WORD parSize;
  DWORD res;
  DWORD dbl;
  DWORD minVal;
  DWORD maxVal;
  };
#pragma pack()
BOOL InterpreteDouble (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    InterpreteDouble_param FAR *par = (InterpreteDouble_param FAR *) param;
    LPVOID data = c->ReadlData (par->dbl);
    float FAR *minVal = (float FAR *) c->ReadlData(par->minVal);
    float FAR *maxVal = (float FAR *) c->ReadlData(par->maxVal);
    if (data != NULL) {
      BOOL isValid = TRUE ;
      if (minVal != NULL)
        isValid = ((* ((double FAR *) data)) >= (double) *minVal);
      if (maxVal != NULL)
        isValid = ((* ((double FAR *) data)) <= (double) *maxVal);
      if (isValid) {
        float r = float (* ((double FAR *) data));
        c->WritelData (par->res,&r,sizeof(r),LPSTR(param)-sizeof(WORD));
        }
      else
        c->DellData (par->res,LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    InterpreteDouble_param FAR *par = (InterpreteDouble_param FAR *) param;
    c->ClearlConnection (par->res,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct PushToBlob_param {
  WORD parSize;
  DWORD blob;
  DWORD KennNummer;
  DWORD HNr0;
  DWORD HNr1;
  DWORD date;
  DWORD time;
  DWORD Daten;
  DWORD DatSize;
  };
#pragma pack()

void DatenInDenBlob (
    mdiChild FAR *c,
    DWORD par_blob,
    DWORD FAR *lpKennNummer,
    DWORD FAR *lpHNr0,
    DBINT FAR *lpHNr1,
    packdate FAR *lpdate,
    packtime FAR *lptime,
    LPVOID Daten,
    DBINT FAR *lpDatSize,
    LPSTR pdOffs
    )
  {
  BlobDesc FAR *bd = (BlobDesc FAR *) c->ReadlData (par_blob);

  BlobDesc bdnew;
  BOOL doWrite = FALSE ;
  if (bd != NULL) {
    HPSTR alteDaten = HPSTR (GlobalLock (bd->hGmem));
    HPSTR end = alteDaten + bd->Size;

    BOOL done = FALSE ;

    for ( ContainElem FAR *h = (ContainElem FAR *) alteDaten ; ; ) {
      if (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1) > end) {
        // Das wuerde hinter das Ende zeigen -> So nicht!!!!!
        bd->Size = (HPSTR(h) - HPSTR(alteDaten));
        bdnew = *bd ;
        doWrite = TRUE;
        break ;
        }
      if ((h->HNr0 == *lpHNr0) &&
          (h->HNr1 == *lpHNr1) &&
          (h->KennNummer == *lpKennNummer)) {
        if (h->DatenGroesse == *lpDatSize) {
          // Die Daten koennen direkt ausgetauscht werden...
          hmemcpy (h->Daten,Daten,*lpDatSize);
          h->pd = *lpdate;
          h->pt = *lptime;
          done = TRUE;
          break ;
          }
        else {
          // Die Alten Daten muessen geloescht werden
          LONG newSize = bd->Size - (sizeof (*h) + h->DatenGroesse - 1);
          if (newSize > 0) {
            GLOBALHANDLE hGNew = GlobalAlloc (GMEM_MOVEABLE,newSize);

            HPSTR neueDaten = HPSTR (GlobalLock (hGNew));
            hmemcpy (neueDaten,alteDaten,HPSTR(h) - alteDaten);
            HPSTR DatenNach = HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1);
            hmemcpy (neueDaten + (HPSTR(h) - alteDaten),DatenNach,end - DatenNach);
            GlobalUnlock (hGNew);

            GlobalFree (bd->hGmem);
            bd->hGmem = hGNew ;
            bd->Size = newSize;

            bdnew = *bd ;
            }
          else {
            GlobalFree (bd->hGmem);
            bd->hGmem = NULL;
            bd->Size = 0L;
            bdnew = *bd;
            }
          doWrite = TRUE;

          break ;
          }
        }
      h = (ContainElem FAR *) (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1));
      if (HPSTR (h) >= end)
        break ;
      }

    if ((!done) && (Daten != NULL)) {
      // Daten gehoeren hinten angefuegt
      //--------------------------------
      DWORD nSize = bd->Size + (sizeof(ContainElem) + *lpDatSize - 1);
      GLOBALHANDLE hGNew = GlobalAlloc (GMEM_MOVEABLE,nSize);
      HPSTR newbd = HPSTR (GlobalLock (hGNew));
      HPSTR oldbd;
      if (bd->hGmem) {
        oldbd = HPSTR (GlobalLock (bd->hGmem));
        hmemcpy (newbd,oldbd,bd->Size);
        }
      else
        oldbd = NULL;

      ContainElem FAR *ce = (ContainElem FAR *) (newbd + bd->Size);
      ce->DatenGroesse = *lpDatSize;
      ce->KennNummer = *lpKennNummer;
      ce->HNr0 = *lpHNr0;
      ce->HNr1 = *lpHNr1;
      ce->pd = *lpdate;
      ce->pt = *lptime;
      hmemcpy (ce->Daten,Daten,*lpDatSize);
      GlobalUnlock (hGNew);

      GlobalUnlock (bd->hGmem);
      if (bd->hGmem)
        GlobalFree (bd->hGmem);
      bdnew.Size = nSize;
      bdnew.hGmem = hGNew;
      doWrite = TRUE ;
      }
    }
  else {
    if (Daten != NULL) {
      // Auf jeden Fall hinten Anfuegen
      GLOBALHANDLE hGMem = GlobalAlloc (GMEM_MOVEABLE,sizeof(ContainElem) + *lpDatSize - 1);
      ContainElem FAR *ce = (ContainElem FAR *) GlobalLock (hGMem);
      ce->DatenGroesse = *lpDatSize;
      ce->KennNummer = *lpKennNummer;
      ce->HNr0 = *lpHNr0;
      ce->HNr1 = *lpHNr1;
      ce->pd = *lpdate;
      ce->pt = *lptime;
      hmemcpy (ce->Daten,Daten,*lpDatSize);
      GlobalUnlock (hGMem);

      bdnew.Size = sizeof(ContainElem) + *lpDatSize - 1;
      bdnew.hGmem = hGMem;
      doWrite = TRUE;
      }
    }

  if (doWrite) {
    if (bdnew.hGmem)
      c->WritelData (par_blob,&bdnew,sizeof(bdnew),pdOffs);
    else
      c->DellData (par_blob,pdOffs);
    }
  }

BOOL PushToBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    PushToBlob_param FAR *par = (PushToBlob_param FAR *) param;
    DWORD FAR *lpKennNummer = (DWORD FAR *) c->ReadlData (par->KennNummer);
    DWORD FAR *lpHNr0 = (DWORD FAR *) c->ReadlData (par->HNr0);
    DBINT FAR *lpHNr1 = (DBINT FAR *) c->ReadlData (par->HNr1);
    packdate FAR *lpdate = (packdate FAR *) c->ReadlData (par->date);
    packtime FAR *lptime = (packtime FAR *) c->ReadlData (par->time);
    LPVOID Daten = c->ReadlData (par->Daten);
    DBINT FAR *lpDatSize = (DBINT FAR *) c->ReadlData (par->DatSize);

    DBWIN_ASSERT ((lpKennNummer != NULL) &&
                  (lpHNr0 != NULL) &&
                  (lpHNr1 != NULL) &&
                  (lpdate != NULL) &&
                  (lptime != NULL) &&
                  (lpDatSize != NULL)) ;

    DatenInDenBlob (
        c,
        par->blob,
        lpKennNummer,
        lpHNr0,
        lpHNr1,
        lpdate,
        lptime,
        Daten,
        lpDatSize,
        LPSTR(param)-sizeof(WORD)
        ) ;

    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    PushToBlob_param FAR *par = (PushToBlob_param FAR *) param;
    c->ClearlConnection (par->blob,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->KennNummer,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->HNr0,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->HNr1,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->date,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->time,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->Daten,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->DatSize,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct RemoveFromBlob_param {
  WORD parSize;
  DWORD blob;
  DWORD HNr0;
  };
#pragma pack()

BOOL RemoveFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    RemoveFromBlob_param FAR *par = (RemoveFromBlob_param FAR *) param;
    BlobDesc FAR *bd = (BlobDesc FAR *) c->ReadlData (par->blob);
    DWORD FAR *lpHNr0 = (DWORD FAR *) c->ReadlData (par->HNr0);

    DBWIN_ASSERT (lpHNr0 != NULL);

    BlobDesc bdnew;
    BOOL doWrite = FALSE ;
    if (bd != NULL) {
      HPSTR alteDaten = HPSTR (GlobalLock (bd->hGmem));
      HPSTR end = alteDaten + bd->Size;

      BOOL done = FALSE ;

      for ( ContainElem FAR *h = (ContainElem FAR *) alteDaten ; ; ) {
        if (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1) > end) {
          // Das wuerde hinter das Ende zeigen -> So nicht!!!!!
          doWrite = TRUE;
          bd->Size = (HPSTR(h) - HPSTR(alteDaten));
          bdnew = *bd;
          break ;
          }
        if (h->HNr0 == *lpHNr0) {
          // Die Alten Daten muessen geloescht werden
          WORD LoeschDatenGroesse = h->DatenGroesse;
          DWORD NeueGroesse = bd->Size - (sizeof (*h) + LoeschDatenGroesse - 1);
          if (NeueGroesse > 0L) {
            GLOBALHANDLE hGNew = GlobalAlloc (GMEM_MOVEABLE,bd->Size - (sizeof (*h) + LoeschDatenGroesse - 1));

            HPSTR neueDaten = HPSTR (GlobalLock (hGNew));
            hmemcpy (neueDaten,alteDaten,HPSTR(h) - alteDaten);
            HPSTR DatenNach = HPSTR(h) + (sizeof(*h) + LoeschDatenGroesse - 1);
            DWORD dwOffs = HPSTR(h) - alteDaten;
            hmemcpy (neueDaten + dwOffs,DatenNach,end - DatenNach);
            GlobalUnlock (hGNew);

            GlobalFree (bd->hGmem);
            bd->hGmem = hGNew ;
            bd->Size -= (sizeof(*h) + LoeschDatenGroesse - 1);

            bdnew = *bd ;
            doWrite = TRUE;

            alteDaten = neueDaten;
            h = (ContainElem FAR *) (alteDaten + dwOffs);
            end = alteDaten + bdnew.Size;
            }
          else {
            doWrite = TRUE ;
            bdnew.hGmem = NULL;
            bdnew.Size = 0L;
            break ;
            }
          }
        else
          h = (ContainElem FAR *) (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1));
        if (HPSTR (h) >= end)
          break ;
        }
      }

    if (doWrite) {
      if (bdnew.hGmem)
        c->WritelData (par->blob,&bdnew,sizeof(bdnew),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->blob,LPSTR(param)-sizeof(WORD));
      }


    return doWrite;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    RemoveFromBlob_param FAR *par = (RemoveFromBlob_param FAR *) param;
    c->ClearlConnection (par->blob,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->HNr0,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct MoveBlobData_param {
  WORD parSize;
  DWORD blob_alt;
  DWORD blob_neu;
  DWORD HNr0;
  };
#pragma pack()

BOOL MoveBlobData (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    MoveBlobData_param FAR *par = (MoveBlobData_param FAR *) param;
    BlobDesc FAR *bd_alt = (BlobDesc FAR *) c->ReadlData (par->blob_alt);
    DWORD FAR *lpHNr0 = (DWORD FAR *) c->ReadlData (par->HNr0);

    DBWIN_ASSERT (lpHNr0 != NULL);

    BlobDesc bdnew;
    BOOL doWrite = FALSE ;
    if (bd_alt != NULL) {
      HPSTR alteDaten = HPSTR (GlobalLock (bd_alt->hGmem));
      HPSTR end = alteDaten + bd_alt->Size;

      BOOL done = FALSE ;

      for ( ContainElem FAR *h = (ContainElem FAR *) alteDaten ; ; ) {
        if (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1) > end) {
          // Das wuerde hinter das Ende zeigen -> So nicht!!!!!
          doWrite = TRUE;
          bd_alt->Size = (HPSTR(h) - HPSTR(alteDaten));
          bdnew = *bd_alt;
          break ;
          }
        if (h->HNr0 == *lpHNr0) {
          // Die Daten muesse ruebergeschaufelt werden
          DatenInDenBlob (
              c,
              par->blob_neu,
              &h->KennNummer,
              &h->HNr0,
              &h->HNr1,
              &h->pd,
              &h->pt,
              h->Daten,
              &h->DatenGroesse,
              LPSTR(param)-sizeof(WORD)
              ) ;

          // Im Alten Blob die Daten loeschen werden
          WORD LoeschDatenGroesse = h->DatenGroesse;
          DWORD NeueGroesse = bd_alt->Size - (sizeof (*h) + LoeschDatenGroesse - 1);
          if (NeueGroesse > 0L) {
            GLOBALHANDLE hGNew = GlobalAlloc (GMEM_MOVEABLE,NeueGroesse);

            HPSTR neueDaten = HPSTR (GlobalLock (hGNew));
            hmemcpy (neueDaten,alteDaten,HPSTR(h) - alteDaten);
            HPSTR DatenNach = HPSTR(h) + (sizeof(*h) + LoeschDatenGroesse - 1);
            DWORD dwOffs = HPSTR(h) - alteDaten;
            hmemcpy (neueDaten + dwOffs,DatenNach,end - DatenNach);
            GlobalUnlock (hGNew);

            GlobalFree (bd_alt->hGmem);
            bd_alt->hGmem = hGNew ;
            bd_alt->Size -= (sizeof(*h) + LoeschDatenGroesse - 1);

            bdnew = *bd_alt ;
            doWrite = TRUE;

            alteDaten = neueDaten;
            h = (ContainElem FAR *) (alteDaten + dwOffs);
            end = alteDaten + bdnew.Size;
            }
          else {
            bdnew.hGmem = NULL;
            bdnew.Size = 0L;
            break ;
            }
          }
        else
          h = (ContainElem FAR *) (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1));
        if (HPSTR (h) >= end)
          break ;
        }
      }

    if (doWrite) {
      if (bdnew.hGmem)
        c->WritelData (par->blob_alt,&bdnew,sizeof(bdnew),LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->blob_alt,LPSTR(param)-sizeof(WORD));
      }

    return doWrite;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    MoveBlobData_param FAR *par = (MoveBlobData_param FAR *) param;
    c->ClearlConnection (par->blob_alt,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->blob_neu,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->HNr0,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack (1)
struct BlobAufbereiten_param {
  WORD parSize;
  hash FAR *rHash;
  DWORD res;
  DWORD blob;
  };
#pragma pack ()

void FreeBlobHash (hash FAR *h)
  {
  for (int i = 0 ; i < int (h->hash_dimension) ; i++) {
    for (LPhash_entry e = h->Table + i ; e != NULL ; ) {
      if (!h->is_empty (e)) {
        // Schluessel Speichern
        int dim = GetBlockSize (e->Data) / sizeof(SortContainElem FAR *);
        SortContainElem FAR *FAR *sc = (SortContainElem FAR * FAR *) e->Data;
        for (int j = 0 ; j < dim ; j++)
          FreeGlobMem (sc[j]);
        }
      e = e->Next ;
      }
    }
  delete h;
  }

BOOL BlobAufbereiten (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    BlobAufbereiten_param FAR * par = (BlobAufbereiten_param FAR *) param;
    if (par->rHash != NULL)
      FreeBlobHash (par->rHash);
    par->rHash = NULL;
    BlobDesc FAR *bd = (BlobDesc FAR *) c->ReadlData (par->blob);

    if ((bd != NULL) && (bd->Size > 0L)) {
      GLOBALHANDLE hGWork = GlobalAlloc (GMEM_MOVEABLE,4096 * sizeof (SortContainElem FAR * FAR *));
      SortContainElem FAR *FAR *nArr = (SortContainElem FAR *FAR *) GlobalLock (hGWork);

      par->rHash = new hash (111,LONGKEY);

      HPSTR alteDaten = HPSTR (GlobalLock (bd->hGmem));
      HPSTR end = alteDaten + bd->Size;

      for ( ContainElem FAR *h = (ContainElem FAR *) alteDaten ; ; ) {
        if (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1) > end)
          // Das wuerde hinter das Ende zeigen -> So nicht!!!!!
          break ;

        // Ein Element anfordern...
        SortContainElem FAR *FAR *sc = (SortContainElem FAR * FAR *) par->rHash->GetData (h->KennNummer);
        BOOL found;
        int nDim;
        if (sc != NULL) {
          nDim = GetBlockSize (sc) / sizeof (*sc) + 1;
          hmemcpy (nArr,sc,GetBlockSize (sc));
          found = TRUE;
          }
        else {
          nDim = 1;
          found = FALSE;
          }

        nArr[nDim - 1] = (SortContainElem FAR *) GetGlobMem (sizeof (SortContainElem) + h->DatenGroesse - 1) ;
        nArr[nDim - 1]->HNr0 =         h->HNr0 ;
        nArr[nDim - 1]->HNr1 =         h->HNr1 ;
        nArr[nDim - 1]->pd =           h->pd ;
        nArr[nDim - 1]->pt =           h->pt ;
        nArr[nDim - 1]->DatenGroesse = h->DatenGroesse ;
        lmemcpy (nArr[nDim - 1]->Daten,h->Daten,h->DatenGroesse);

        if (found)
          par->rHash->DelData (h->KennNummer);
        par->rHash->SetData (h->KennNummer,nArr,nDim * sizeof (SortContainElem FAR *FAR *));

        h = (ContainElem FAR *) (HPSTR(h) + (sizeof(*h) + h->DatenGroesse - 1));
        if (HPSTR (h) >= end)
          break ;
        }

      SortContainHash (par->rHash);

      GlobalUnlock (hGWork);
      GlobalFree (hGWork);
      }

    c->WritelData (par->res,&par->rHash,sizeof(par->rHash),LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    BlobAufbereiten_param FAR * par = (BlobAufbereiten_param FAR *) param;
    c->SetlConnection (par->blob,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    BlobAufbereiten_param FAR * par = (BlobAufbereiten_param FAR *) param;
    if (par->rHash != NULL)
      FreeBlobHash (par->rHash);
    par->rHash = NULL;
    c->ClearlConnection (par->blob,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct DatenVomBlob_par {
  WORD parSize;
  DWORD res;
  DWORD rHash;
  DWORD KennNummer;
  DWORD dmin;
  DWORD tmin;
  DWORD dmax;
  DWORD tmax;
  DWORD kRes;
  DWORD dact,tact;
  };
#pragma pack()

inline int clip (int dact,int dmax)
  {
  if (dact < 0) return 0;
  else if (dact >= dmax) return dmax - 1;
  else return dact;
  }

inline int max2 (int sact)
  {
  if (sact / 2 * 2 == sact) return sact / 2;
  else                      return sact / 2 + 1;
  }

INTTIME compare (INTTIME te,SortContainElem FAR * sc)
  {
  INTTIME ts = PackTime (&sc->pd);
  ts += INTTIME (LONG(sc->pt.hour) * 3600L + LONG(sc->pt.minute) * 60L + LONG(sc->pt.second));
  return te - ts;
  }

BOOL DatenVomBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    hash FAR * FAR *rHash = (hash FAR * FAR *) c->ReadlData (par->rHash);

    SortContainElem FAR *re = NULL;

    DWORD FAR *KennNummer = (DWORD FAR *) c->ReadlData (par->KennNummer);
    if ((rHash != NULL) && (*rHash != NULL) && (KennNummer)) {
      SortContainElem FAR *FAR *sc = (SortContainElem FAR * FAR *) (* rHash)->GetData (*KennNummer);
      if (sc != NULL) {
        packdate FAR *dstart = (packdate FAR *) c->ReadlData (par->dmin);
        packtime FAR *tstart = (packtime FAR *) c->ReadlData (par->tmin);
        packdate FAR *dend   = (packdate FAR *) c->ReadlData (par->dmax);
        packtime FAR *tend   = (packtime FAR *) c->ReadlData (par->tmax);

        int dim = GetBlockSize (sc) / sizeof(*sc);

        if (dend != NULL) {
          INTTIME te = PackTime (dend);
          if (tend != NULL)
            te += INTTIME (LONG(tend->hour) * 3600L + LONG(tend->minute) * 60L + LONG(tend->second));

          // Suchen des letzten Wertes zu dieser Zeit
          //    (Man kann von der Sortierung ausgehen)
          int dstep = max2 (dim);
          int dact = dim / 2;
          int dir;

          int dbest = -1;
          BOOL breakNext = FALSE;

          for ( ; ; ) {
            INTTIME diff = compare (te,sc[dact]);
            int dold = dact;
            if (diff >= 0) {
              // Kann genommen werden, es wird noch versucht einen groesseren zu finden
              dbest = dact;
              dir = 1;
              }
            else {
              // Kann nicht genommen, es wird versucht einen kleineren zu finden
              dir = -1;
              }
            if (breakNext) break ;
            if (dstep == 1) breakNext = TRUE;
            dstep = max2(dstep);
            dact = clip (dact + dir * dstep,dim) ;
            }
          if (dbest >= 0) {
            if (dstart != NULL) {
              // Vergleich mit der Startzeit
              INTTIME ts = PackTime (dstart);
              if (tstart != NULL)
                ts += INTTIME (LONG(tstart->hour) * 3600L + LONG(tstart->minute) * 60L + LONG(tstart->second));
              if (compare (ts,sc[dbest]) > INTTIME(0))
                dbest = -1;
              }
            if (dbest >= 0)
              re = sc[dbest];
            else
              re = NULL;
            }
          else
            re = NULL;
          }
        else
          re = sc[dim - 1];
        }
      }
    else
      re = NULL;

    LPVOID old = c->TryToReadData (par->res);
    if ((old != NULL) && (re == NULL))
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    else if ((re != NULL) &&
          ((old == NULL) ||
           (GetBlockSize(old) != re->DatenGroesse) ||
           (!lmemcmp (old,re->Daten,re->DatenGroesse))))
      c->WritelData (par->res,re->Daten,re->DatenGroesse,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    c->SetlConnection (par->rHash,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dmin,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tmin,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dmax,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tmax,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    c->ClearlConnection (par->rHash,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dmin,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tmin,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dmax,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tmax,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

BOOL ErsteDatenVomBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    hash FAR * FAR *rHash = (hash FAR * FAR *) c->ReadlData (par->rHash);

    SortContainElem FAR *re;

    DWORD FAR *KennNummer = (DWORD FAR *) c->ReadlData (par->KennNummer);
    if ((rHash != NULL) && (*rHash != NULL) && (KennNummer)) {
      SortContainElem FAR *FAR *sc = (SortContainElem FAR * FAR *) (* rHash)->GetData (*KennNummer);
      if (sc != NULL) {
        packdate FAR *dstart = (packdate FAR *) c->ReadlData (par->dmin);
        packtime FAR *tstart = (packtime FAR *) c->ReadlData (par->tmin);
        packdate FAR *dend   = (packdate FAR *) c->ReadlData (par->dmax);
        packtime FAR *tend   = (packtime FAR *) c->ReadlData (par->tmax);

        DBINT dim = GetBlockSize (sc) / sizeof(*sc);

        DBINT dact;
        if (dstart != NULL) {
          INTTIME ts = PackTime (dstart);
          if (tstart != NULL)
            ts += INTTIME (LONG(tstart->hour) * 3600L + LONG(tstart->minute) * 60L + LONG(tstart->second));

          // Suchen des ersten Wertes, der zu dieser Zeit passt
          //    (Man kann von der Sortierung ausgehen)
          for ( dact = 0 ; dact < dim ; dact ++ ) {
            INTTIME diff = compare (ts,sc[dact]);
            if (diff <= 0)
              break ;
            }
          }
        else
          dact = 0 ;

        if ((dact < dim) && (dend != NULL)) {
          INTTIME te = PackTime (dend);
          if (tend != NULL)
            te += INTTIME (LONG(tend->hour) * 3600L + LONG(tend->minute) * 60L + LONG(tend->second));
          if (compare (te,sc[dact]) < 0L) {
            // Nicht mehr verwenden, aufhoehern...
            dact = dim ;
            }
          }
        if (dact < dim)
          re = sc[dact];
        else
          re = NULL ;
        c->WritelData (par->kRes,&dact,sizeof(dact),LPSTR(param)-sizeof(WORD));
        }
      else
        re = NULL;
      }
    else
      re = NULL;

    if (re != NULL) {
      c->WritelData (par->res,re->Daten,re->DatenGroesse,LPSTR(param)-sizeof(WORD));
      c->WritelData (par->dact,&re->pd,sizeof(re->pd),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->tact,&re->pt,sizeof(re->pt),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    c->SetlConnection (par->rHash,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dmin,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tmin,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dmax,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tmax,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    c->ClearlConnection (par->rHash,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dmin,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tmin,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dmax,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tmax,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }


BOOL WeitereDatenVomBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    hash FAR * FAR *rHash = (hash FAR * FAR *) c->ReadlData (par->rHash);

    SortContainElem FAR *re = NULL;

    DWORD FAR *KennNummer = (DWORD FAR *) c->ReadlData (par->KennNummer);
    if ((rHash != NULL) && (*rHash != NULL) && (KennNummer)) {
      SortContainElem FAR *FAR *sc = (SortContainElem FAR * FAR *) (* rHash)->GetData (*KennNummer);
      if (sc != NULL) {
        packdate FAR *dend   = (packdate FAR *) c->ReadlData (par->dmax);
        packtime FAR *tend   = (packtime FAR *) c->ReadlData (par->tmax);

        DBINT dim = GetBlockSize (sc) / sizeof(*sc);

        DBINT FAR *lpdact = (DBINT FAR *) c->ReadlData (par->kRes);
        DBWIN_ASSERT (lpdact != NULL);
        DBINT dact = (*lpdact) + 1;

        if ((dact < dim) && (dend != NULL)) {
          INTTIME te = PackTime (dend);
          if (tend != NULL)
            te += INTTIME (LONG(tend->hour) * 3600L + LONG(tend->minute) * 60L + LONG(tend->second));
          if (compare (te,sc[dact]) < 0L) {
            // Nicht mehr verwenden, aufhoehern...
            dact = dim ;
            }
          }
        if (dact < dim)
          re = sc[dact];
        else
          re = NULL ;
        c->WritelData (par->kRes,&dact,sizeof(dact),LPSTR(param)-sizeof(WORD));
        }
      else
        re = NULL;
      }
    else
      re = NULL;

    if (re != NULL) {
      c->WritelData (par->res,re->Daten,re->DatenGroesse,LPSTR(param)-sizeof(WORD));
      c->WritelData (par->dact,&re->pd,sizeof(re->pd),LPSTR(param)-sizeof(WORD));
      c->WritelData (par->tact,&re->pt,sizeof(re->pt),LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->res,LPSTR(param)-sizeof(WORD));
    }
  if (mode & EM_FIXCONNECTION) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    c->SetlConnection (par->rHash,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dmin,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tmin,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->dmax,LPSTR(param)-sizeof(WORD));
    c->SetlConnection (par->tmax,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    DatenVomBlob_par FAR * par = (DatenVomBlob_par FAR *) param;
    c->ClearlConnection (par->rHash,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dmin,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tmin,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->dmax,LPSTR(param)-sizeof(WORD));
    c->ClearlConnection (par->tmax,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

#pragma pack(1)
struct FAR TagesAuslastung_param {
  WORD parSize;
  DWORD Liste;      // Liste, die durchsucht werden soll
  DWORD Selektor;   // Zu welchen (long) Attribut soll die Akkumulierung stattfinden
  DWORD tVon;       // VonZeit
  DWORD tBis;       // BisZeit
  DWORD SetzProzedur; // Setzprozedure
  DWORD SDatum;       // Testdatum
  DWORD SSelektor;    // Hilfsvariable fuer die Setzprozedure
  DWORD SAnzahl1;     // Anzahl1 in der Setzprozedur
  DWORD SAnzahl2;     // Anzahl2 in der Setzprozedur
  DWORD SAnzahl3;     // Anzahl3 in der Setzprozedur
  // Optionale Parameter
  DWORD Anz1,Anz2,Anz3;    // Schrittgroessen
  DWORD TypSelektor;  // ..
  DWORD CompareType;

  BOOL MitAnzahl ()
    {
    return (parSize >= sizeof(*this) - 2 * sizeof(DWORD));
    }
  BOOL MitTyp ()
    {
    return (parSize >= sizeof(*this));
    }
  };
#pragma pack()

struct Step {
  packdatetime t;
  DBINT dir1;
  DBINT dir2;
  DBINT dir3;
  };

#define STEPSIZEALLOC 100
packdate FAR &NaechsterTag (packdate FAR &pd)
  {
  static packdate res;
  INTTIME t = PackTime (&pd);
  t += INTTIME (LONG (24) * LONG (60) * LONG (60)) ;
  UnPackTime (t,&res);
  return res;
  }
packdate FAR &VorigerTag (packdate FAR &pd)
  {
  static packdate res;
  INTTIME t = PackTime (&pd);
  t -= INTTIME (LONG (24) * LONG (60) * LONG (60)) ;
  UnPackTime (t,&res);
  return res;
  }
struct StepList {
  DWORD Selektor;
  GLOBALHANDLE hGStep;
  int AnzSteps,AnzStepsMem;
  StepList FAR *Next;

  void PushToStep (packdatetime FAR *t,short d1,short d2,short d3)
    {
    int bestSize = ((AnzSteps + 1) / 100 + 1) * 100;
    if (bestSize > AnzStepsMem) {
      if (!hGStep) hGStep = GlobalAlloc (GMEM_MOVEABLE,bestSize * sizeof(Step));
      else         hGStep = GlobalReAlloc (hGStep,bestSize * sizeof(Step),GMEM_MOVEABLE);
      AnzStepsMem = bestSize;
      }
    Step FAR *b = (Step FAR *) GlobalLock (hGStep);
    b[AnzSteps].t = *t;
    b[AnzSteps].dir1 = d1;
    b[AnzSteps].dir2 = d2;
    b[AnzSteps].dir3 = d3;
    GlobalUnlock (hGStep);
    AnzSteps ++ ;
    }
  void SchreibeZwischenStufen (packdate FAR &d1,packdate FAR *d2,mdiChild *c,TagesAuslastung_param FAR * par,DBINT anz1,DBINT anz2,DBINT anz3)
    {
    c->WritelData (par->SAnzahl1,&anz1,sizeof(anz1),LPSTR(par)-sizeof(WORD));
    c->WritelData (par->SAnzahl2,&anz2,sizeof(anz2),LPSTR(par)-sizeof(WORD));
    c->WritelData (par->SAnzahl3,&anz3,sizeof(anz3),LPSTR(par)-sizeof(WORD));
    for ( packdate x = d1 ;
              ((d2 == NULL) || (!lmemcmp (&x,d2,sizeof(*d2)))) ; x = NaechsterTag (x) ) {
      c->WritelData (par->SDatum,&x,sizeof(x),LPSTR(par)-sizeof(WORD));
      c->ExCuteProc (par->SetzProzedur,EM_LOAD | EM_CHANGETOTRUE);
      c->ExCuteProc (par->SetzProzedur,EM_RESET | EM_CLEAR);
      if (d2 == NULL) break ;
      }
    }
  void ErzeugeTagesListe (mdiChild *c,TagesAuslastung_param FAR *par)
    {
    Step FAR *b = (Step FAR *) GlobalLock (hGStep);
    packdate altesDatum;
    altesDatum.year = 0;    // Damit beim ersten mal auf jeden Fall
                            // das != zutrifft, Kennzeichnung des
                            // Initialzustandes
    DBINT anz1 = 0;
    DBINT anz2 = 0;
    DBINT anz3 = 0;
    DBINT max1,max2,max3;
    for ( int i = 0 ; i < AnzSteps ; i++) {
      if (!lmemcmp (&b[i].t.pd,&altesDatum,sizeof(altesDatum))) {
        // Tageswechsel
        if (altesDatum.year > 0) {
          // -> Den zuletzt bearbeiteten Tag mit dessen
          //    Maximum schreiben
          SchreibeZwischenStufen (altesDatum,NULL,c,par,max1,max2,max3);
          // -> Alle weiteren Tage bis zum heutigen mit der
          //    aktuellen Anzahl schreiben
          SchreibeZwischenStufen (NaechsterTag (altesDatum),&b[i].t.pd,c,par,anz1,anz2,anz3);
          }
        // Das Tagesmaximum vorbelegen
        max1 = anz1 ;
        max2 = anz2 ;
        max3 = anz3 ;
        }
      anz1 += b[i].dir1 ;
      anz2 += b[i].dir2 ;
      anz3 += b[i].dir3 ;
      if (anz1 > max1) max1 = anz1;
      if (anz2 > max2) max2 = anz2;
      if (anz3 > max3) max3 = anz3;
      altesDatum = b[i].t.pd;
      }
    // Abschliessenden Tag schreiben
    SchreibeZwischenStufen (altesDatum,NULL,c,par,max1,max2,max3);

    // Naechsten Tag mit der aktuellen Anzeige schreiben
    SchreibeZwischenStufen (NaechsterTag(altesDatum),NULL,c,par,anz1,anz2,anz3);
    GlobalUnlock (hGStep);
    }
  };

StepList FAR *AddStep (StepList FAR *old,DWORD Sel,packdatetime FAR *t,short d1,short d2,short d3)
  {
  StepList FAR *nStep = NULL;
  StepList FAR *res = NULL;
  for (StepList FAR *h = old ; h != NULL ; h = h->Next) {
    if (h->Selektor == Sel) {
      res = h ;
      nStep = old;
      break ;
      }
    }
  if (res == NULL) {
    nStep = (StepList FAR *) GetGlobMem (sizeof (*nStep));
    nStep->Next = old;
    nStep->Selektor = Sel;

    res = nStep;
    }
  res->PushToStep (t,d1,d2,d3);

  return nStep;
  }

void FreeSteps (StepList FAR *s)
  {
  for ( ; (s != NULL) ; ) {
    StepList FAR *n = s->Next;
    if (s->hGStep) GlobalFree (s->hGStep);
    FreeGlobMem (s);
    s = n;
    }
  }

int CompareSTime (const void *e1,const void *e2)
  {
  packdatetime FAR *p1 = &((Step *)e1)->t;
  packdatetime FAR *p2 = &((Step *)e2)->t;

  if (p1->pd.year == p2->pd.year) {
    if (p1->pd.month == p2->pd.month) {
      if (p1->pd.day == p2->pd.day) {
        if (p1->pt.hour == p2->pt.hour) {
          if (p1->pt.minute == p2->pt.minute) {
            if (p1->pt.second == p2->pt.second) {
              // Die mit Schritte mit neg. Schritthoehen zuerst sortieren
              return ((Step *)e1)->dir1 - ((Step *)e2)->dir1;
              }
            else
              return (p1->pt.second > p2->pt.second) ? 1 : -1;
            }
          else
            return (p1->pt.minute > p2->pt.minute) ? 1 : -1;
          }
        else
          return (p1->pt.hour > p2->pt.hour) ? 1 : -1;
        }
      else
        return (p1->pd.day > p2->pd.day) ? 1 : -1;
      }
    else
      return (p1->pd.month > p2->pd.month) ? 1 : -1;
    }
  else
    return (p1->pd.year > p2->pd.year) ? 1 : -1;
  }
void SortAllSteps (StepList FAR *sl)
  {
  for ( StepList FAR *h = sl ; h != NULL ; h = h->Next) {
    if (h->AnzSteps > 0) {
      Step FAR *s = (Step FAR *)GlobalLock (h->hGStep);
      qsort (s,h->AnzSteps,sizeof(s[0]),CompareSTime);
      GlobalUnlock (h->hGStep);
      }
    }
  }

extern void GetListData (LPVOID FAR *lpp,RecordList FAR * &l,LPTABLEDEF &td,LPSTR &Alias);
BOOL TagesAuslastung (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & (EM_LOAD | EM_UPDATE)) {
    TagesAuslastung_param FAR *par = (TagesAuslastung_param FAR *) param;

    // Ermitteln der Liste
    LPVOID FAR *lpp = (LPVOID FAR *) c->ReadlData (par->Liste);
    RecordList FAR *l = NULL;
    LPTABLEDEF td;
    LPSTR Alias;
 
    GetListData (lpp,l,td,Alias);

    BOOL mitAnz = par->MitAnzahl ();
    BOOL mitTyp = par->MitTyp ();

    DBINT FAR *lpTyp;
    if (mitTyp) {
      lpTyp = (DBINT FAR *) c->ReadlData (par->CompareType);
      DBWIN_ASSERT (lpTyp != NULL);
      }

    // Alle Saetze der Liste durchgehen und in Array Schmeissen
    if (l != NULL) {
      StepList FAR *sl = NULL;
      for ( LPDBRECORD h = l->GetFirst () ; h != NULL ; h = l->GetNext(h)) {
        if (mitTyp) {
          // Typfilter
          DBINT FAR *aTyp = (DBINT FAR *) h->Get (HIWORD(par->TypSelektor));
          if ((aTyp == NULL) || (*aTyp != *lpTyp)) continue ;
          }
        LONG FAR *lpSelektor = (LONG FAR *) h->Get (HIWORD(par->Selektor));
        packdatetime FAR *tVon = (packdatetime FAR *) h->Get (HIWORD(par->tVon));
        packdatetime FAR *tBis = (packdatetime FAR *) h->Get (HIWORD(par->tBis));

        DBINT d1,d2,d3;
        if (mitAnz) {
          DBINT FAR *lpd1 = (DBINT FAR *) h->Get (HIWORD (par->Anz1));
          DBINT FAR *lpd2 = (DBINT FAR *) h->Get (HIWORD (par->Anz2));
          DBINT FAR *lpd3 = (DBINT FAR *) h->Get (HIWORD (par->Anz3));
          if (lpd1 != NULL) d1 = *lpd1 ; else d1 = 1;
          if (lpd2 != NULL) d2 = *lpd2 ; else d2 = 1;
          if (lpd3 != NULL) d3 = *lpd3 ; else d3 = 1;
          }
        else {
          d1 = 1;
          d2 = 1;
          d3 = 1;
          }
        if ((lpSelektor) && (tVon))
          sl = AddStep (sl,*lpSelektor,tVon,d1,d2,d3);
        if ((lpSelektor) && (tBis)) {
          if ((tBis->pt.hour == 0) &&
              (tBis->pt.minute == 0) &&
              (tBis->pt.second == 0)) {
            packdatetime tv;    // Vorigen Tag mit 23:59:59 setzen,
                                // damit dieser Tag nicht aufscheint..
            tv.pd = VorigerTag (tBis->pd);
            tv.pt.hour = 23;
            tv.pt.minute = 59;
            tv.pt.second = 59;
            sl = AddStep (sl,*lpSelektor,&tv,-d1,-d2,-d3);
            }
          else
            sl = AddStep (sl,*lpSelektor,tBis,-d1,-d2,-d3);
          }
        }

      // Alle Schrittlisten sortieren
      SortAllSteps (sl);

      // Fuer Alle Schrittlisten die Tageslisten bilden und diese Schreiben
      for ( StepList FAR *x = sl ; x != NULL ; x = x->Next ) {
        c->WritelData (par->SSelektor,&x->Selektor,sizeof(x->Selektor),LPSTR(par)-sizeof(WORD));
        x->ErzeugeTagesListe (c,par);
        }

      // Daten wieder Freigeben
      FreeSteps (sl);
      }
    }
  if (mode & EM_FIXCONNECTION) {
    TagesAuslastung_param FAR *par = (TagesAuslastung_param FAR *) param;
    c->SetlConnection (par->Liste,LPSTR(param)-sizeof(WORD));
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    TagesAuslastung_param FAR *par = (TagesAuslastung_param FAR *) param;
    c->ClearlConnection (par->Liste,LPSTR(param)-sizeof(WORD));
    }
  return FALSE ;
  }

