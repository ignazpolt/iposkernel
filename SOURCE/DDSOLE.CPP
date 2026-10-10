///////////////////////////////////////////////////////////
//  Object Linking and Embedding
//
//  Einfaches Handling von der Marille aus
///////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/rev/ddsole.cpv   1.18   22 Nov 1999 09:28:04   Hannes  $
//  $Log:   P:/marille/clinicum/rev/ddsole.cpv  $
// 
//    Rev 1.18   22 Nov 1999 09:28:04   Hannes
// Diverse OLE - Erweiterungen
// 
//    Rev 1.17   14 Jun 1999 20:39:20   Hannes
// RunAutomacro
// 
//    Rev 1.16   15 Jan 1999 18:20:24   Hannes
// Propertie - Handling
// 
//    Rev 1.15   11 Jan 1999 23:09:12   Hannes
// 
//    Rev 1.14   05 Oct 1998 11:53:40   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.13   31 Aug 1998 17:42:32   Gerhold
// SetOleDocVar
// 
//    Rev 1.12   15 Aug 1998 15:58:48   Gerhold
// RunOleObjectFromBlob ... 2.Callbackprozedur vor Freigeben des Objektes
// SetOleDocVar ... free Parameter Extended
// 
//    Rev 1.11   13 Aug 1998 10:46:42   Gerhold
// SetOleDocVar ... wenn kein Eintrag wird Leerzeichen uebergeben
// 
//    Rev 1.10   10 Aug 1998 13:40:20   Hannes
// SetDocVar auch bei NULL - VALUE
// 
//    Rev 1.9   03 Aug 1998 18:04:10   Gerhold
// GetMyIUnknown war noch falsch
// 
//    Rev 1.8   31 Jul 1998 19:58:18   Martin
// bei CallCommandInClientTransaction wieder ein WMU_CALLCOMMAND posten
// 
//    Rev 1.7   31 Jul 1998 19:18:56   Martin
// InClientTransaction waehrend der lokalen Nachrichtenschleife setzen
// 
//    Rev 1.6   31 Jul 1998 11:46:06   Gerhold
// OLESetHostName
// 
//    Rev 1.5   29 Jul 1998 12:03:06   Gerhold
// OLEGetDocProp, OLERestrictInput, OLEUpdateFields
// 
//    Rev 1.4   28 Jul 1998 08:24:16   Gerhold
// Prototypen fuer SetOLEDocVar, GetOleDocVar, OLEPrint
// 
//    Rev 1.3   22 Aug 1997 12:28:54   Gerhold
// CreateOleObjectFromFile, RunOleObject
// 
//    Rev 1.2   02 Feb 1996 10:35:56   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Mar 1995 11:55:30   HANNES
// Konstantenhanling, RunNmbr...
// 
//    Rev 1.0   24 Jun 1994 17:04:12   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   03 Mar 1994 22:07:52   HANNES
// Initial revision.
//
#ifdef WIN32
//#define INC_OLE1
#endif

#include <windows.h>
#include <stdio.h>

#include "dds32.h"
#include "globmem.h"

#include <ole2.h>

#ifndef WIN32
//#include <ole.h>
#endif

#ifndef WIN32
//#include "ole.hpp"
#endif

#define MODULENUM   74
#include "winass.hpp"
#include "ddsmsg.h"
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


#ifdef DEBUG
  #include "mdiclien.hpp"
#endif

//#define INITGUIDS

#ifndef WIN32
  #include "dvobj.h"
  #include "win1632.h"
  #include "compobj.h"
#else
  #include <ole2.h>
#endif

#ifdef WIN32
#include <winbase.h>
#endif

#include "iclisite.hpp"
#include "olemain.hpp"


#ifdef OLE1
struct ddsole_param {
  WORD parSize;
  LPOLECLIENT lpoleclient;
  mdiChild *c;
  DWORD file;
  DWORD Name;
  DWORD fData;
  DWORD savePtr;
  DWORD exitPtr;
  };
#endif

DLLExport void _export WINAPI SaveOle (LPVOID param,GLOBALHANDLE data,int fnc)
  {
#ifdef OLE1
  ddsole_param FAR *par = (ddsole_param FAR *) param;
  switch (fnc) {
    case OLECB_SAVE :
      if (data) {
        par->c->WritelData (par->fData,&data,sizeof(data),LPSTR(param)-sizeof(WORD));
        par->c->ExCuteProc (par->savePtr,EM_LOAD | EM_CHANGETOTRUE);
        }
      break ;
    case OLECB_EXIT :
      par->c->ExCuteProc (par->exitPtr,EM_LOAD | EM_CHANGETOTRUE);
      break ;
    }
#endif
  }

BOOL DDSOle (mdiChild *c,LPVOID param,WORD mode)
  {
#ifdef OLE1
  static OLESAVEPROC osvproc;
  if (mode & EM_LOAD) {
    ddsole_param FAR *par = (ddsole_param FAR *) param;
    LPSTR fname = LPSTR (c->ReadlData (par->file));
    if (fname != NULL) {
      par->c = c;
      osvproc = OLESAVEPROC (MakeProcInstance (FARPROC(SaveOle),WBase::hInstance));
      par->lpoleclient = InitOLE (WBase::hFrameWin,osvproc,param);
      LPSTR name = LPSTR (c->ReadlData (par->Name));
      ObjCreateFromTemplate (par->lpoleclient,fname,name);
      }
    else
      par->lpoleclient = NULL;
    }
  if (mode & (EM_CLEAR | EM_RESET)) {
    ddsole_param FAR *par = (ddsole_param FAR *) param;
    if (par->lpoleclient != NULL) {
#ifndef WIN32
      FreeProcInstance (FARPROC(osvproc));
#endif
      EndClient (par->lpoleclient);
      }
    }
#endif
  return FALSE ;
  }


//--------------------------------------------------------------------------
//
//  OLE 2.x
// 
//--------------------------------------------------------------------------
static LPCOLEFRAME lpOle = NULL;

#pragma pack(1)
struct createoleobject_param {
  WORD parSize;
  DWORD filename;
  DWORD blob;
  DWORD mitActivate;
  };
#pragma pack()


BOOL CreateOleObjectFromFile (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    createoleobject_param FAR *par = (createoleobject_param FAR *) param;
    LPSTR lpfilename = LPSTR (c->ReadlData (par->filename));

    if ((lpfilename != NULL) && (*lpfilename)) {

      //---------------------
      // Erzeugen des Blobs
      //---------------------
      BlobDesc b ;
      b.Size = 0L ;
      b.hGmem = NULL ;

      OFSTRUCT of;
      HFILE hf = OpenFile (lpfilename, &of, OF_EXIST);
      if (hf != HFILE_ERROR) {

        DWORD lpSize;

        lpOle = new COleFrame (GetActiveWindow());

        if (lpOle) {

          lpOle->CreateObjFromFile (lpfilename);
          HGLOBAL hGlobal = lpOle->GetHGlobalFromOLEObj (&lpSize);

          if (hGlobal) {

            b.hGmem = hGlobal;
            b.Size  = lpSize;

  //          LPVOID lpBuf = GlobalLock (hGlobal);
  //          GlobalUnlock (hGlobal);
            }

  //        lpOle->SaveCompoundFile ("C:\\TEMP\\TEST.DDS");

          delete lpOle;
          lpOle = NULL;
          }
        }

      c->WritelData (par->blob,&b,sizeof(b),LPSTR(param)-sizeof(WORD));
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    createoleobject_param FAR *par = (createoleobject_param FAR *) param;
    c->ClearlConnection (par->filename, LPSTR(param) - sizeof(WORD));
    }

  return FALSE ;
  }


//===========================================================================
//
// RunOleObjectFromBlob
//
// Zweck:
//   Aufruf eines OLE-Objektes welches als Blob zur Verfgung steht und
//   Abspeichern der veraenderten Daten in einem neuen Blob.
//   Solange das OLE-Objekt im Server aktiv ist, kann das CLINICUM
//   nicht aktiviert werden (interne MessageLoop)
//
// Parameter:
//   inblob         Blob in dem das OLE-Objekt abgelegt ist (Quell-Objekt)
//                  wird nicht veraendert
//   outblob        Blob in dem die im OLE-Server geaenderten Objekt-Daten
//                  geschrieben werden
//   CallBackProc   Script-Prozedur die sofort nach dem Aufruf des Servers
//                  und dem Anzeigen der Daten im selben aufgerufen wird
//===========================================================================
#pragma pack(1)
struct PropParam {
  DWORD iKind;
  DWORD iIndex;
  DWORD sName;
  DWORD sValue;
  };
struct runoleobjectfromblob_param FAR {
  WORD parSize;
  DWORD inblob;
  DWORD outblob;
  DWORD PreCallBackProc;
  DWORD PostCallBackProc;
  PropParam pp[1];
  int Anzpp ()
    {
    return (parSize - (sizeof(*this) - sizeof(pp[0]))) / sizeof(pp[0]);
    }
  };
#pragma pack()

extern BOOL InClientTransaction;
extern BOOL CallCommandInClientTransaction;

BOOL RunOleObjectFromBlobEx (mdiChild *c,LPVOID param,WORD mode,BOOL mitActivate)
  {
  if (mode & EM_LOAD) {
    runoleobjectfromblob_param FAR *par = (runoleobjectfromblob_param FAR *) param;

    BlobDesc FAR *inblob = (BlobDesc FAR *) c->ReadlData (par->inblob);

    BlobDesc b ;
    b.Size = 0L ;
    b.hGmem = NULL ;

    if ((inblob != NULL) && (inblob->hGmem != NULL)) {

      HWND hWndActive = GetActiveWindow();
      lpOle = new COleFrame (hWndActive);

      BOOL done = FALSE;
      if (lpOle) {
        UINT res = lpOle->CreateObjFromHGlobal (inblob->hGmem,mitActivate);

        //-------------------
        // und war alles OK?
        //-------------------
        if (res != DOCERR_NONE) {
          char outtext[64];
          wsprintf (outtext, "\rOLE-Fehler #%d\r\rServer wird nicht gestartet", 
                    res);
          DBWIN_ASSERT_TEXT (FALSE, outtext);
          done = TRUE;
          }
        else {
          //--------------------------------------------------------------
          // Aufruf der Script Prozedur noch bevor der OLE-Server nichts
          // mehr zulaesst.
          // Hier koennen im SCRIPT(c) z.B. noch DDE-Kommandos an den
          // Server abgesetzt werden.
          //--------------------------------------------------------------
          c->ExCuteProc (par->PreCallBackProc,EM_LOAD | EM_CHANGETOTRUE);
          c->ExCuteProc (par->PreCallBackProc,EM_RESET | EM_CLEAR);
          }

        // Die Porps weitergeben
        for (int i = 0 ; i < par->Anzpp() ; i++) {
          DBINT FAR *iKind = (DBINT FAR *) (c->ReadlData (par->pp[i].iKind));
          DBINT FAR *iIndex = (DBINT FAR *) (c->ReadlData (par->pp[i].iIndex));
          lpOle->AddProp (i,*iKind,*iIndex);
          }
        if (!mitActivate)
          lpOle->PrintDoc (FALSE);

        //-----------------------------------------------------------
        // Jetzt wird ein bisschen die gute alte DOS-Zeit simuliert.
        // Wir bauen uns jetzt eine kleine Nachrichten-Schleife die
        // erst terminiert, wenn uns das OLE-Objekt benachrichtigt,
        // dass es jetzt nicht mehr aktiv ist, bzw wenn ein Fehler
        // beim OLE-Objekt aufgetreten ist.
        //-----------------------------------------------------------
        InClientTransaction = TRUE;
        MSG msg;
        for ( ; !done ; ) {
          while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WMU_OLESERVER_HAS_CLOSED) {
              done = TRUE;
              break;
              }
            else {
              TranslateMessage ( &msg );
              DispatchMessage ( &msg );
              }
            }
          }
        InClientTransaction = FALSE;
        if (CallCommandInClientTransaction) {
          PostMessage (WBase::hFrameWin,WMU_CALLCOMMAND,0,0L);
          CallCommandInClientTransaction = FALSE;
          }

//        MessageBox (hWndActive, "Objekt wird zerstört", "CLINICUM", MB_OK);

        //-------------------------------------------
        // Speicherhandle der OLE-Objekt-Bytes holen
        //-------------------------------------------
        DWORD lpSize;
        HGLOBAL hGlobal = lpOle->GetHGlobalFromOLEObj (&lpSize);

        if (hGlobal) {
          b.hGmem = GlobalAlloc (GMEM_MOVEABLE,lpSize);
          hmemcpy (GlobalLock (b.hGmem),GlobalLock (hGlobal),lpSize);
          b.Size  = lpSize;
          }

        if (par->parSize >= (sizeof(*par) - sizeof(par->pp[0]))) {
          c->ExCuteProc (par->PostCallBackProc,EM_LOAD | EM_CHANGETOTRUE);
          c->ExCuteProc (par->PostCallBackProc,EM_RESET | EM_CLEAR);
          }

        PropList FAR *pl = lpOle->GetProp ();
        for ( ; pl != NULL ; pl = pl->Next) {
          if ((pl->Value) && (pl->Name)) {
            c->WritelData (par->pp[pl->i].sName,pl->Name,lstrlen(pl->Name) + 1,LPSTR(param) - sizeof(WORD));
            c->WritelData (par->pp[pl->i].sValue,pl->Value,lstrlen(pl->Value) + 1,LPSTR(param) - sizeof(WORD));
            }
          }

        delete lpOle ;
        lpOle = NULL ;

//        MessageBeep (0);
        }

      }     // if (inblob != NULL)

    c->WritelData (par->outblob,&b,sizeof(b),LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    runoleobjectfromblob_param FAR *par = (runoleobjectfromblob_param FAR *) param;
    c->ClearlConnection (par->inblob, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

BOOL RunOleObjectFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  return RunOleObjectFromBlobEx (c,param,mode,TRUE);
  }

BOOL PrintOleObjectFromBlob (mdiChild *c,LPVOID param,WORD mode)
  {
  return RunOleObjectFromBlobEx (c,param,mode,FALSE);
  }

//===========================================================================
//
// SetOLEDocVar
//
// Zweck:
//   
//
// Parameter:
//   inblob         Blob in dem das OLE-Objekt abgelegt ist (Quell-Objekt)
//                  wird nicht veraendert
//   outblob        Blob in dem die im OLE-Server geaenderten Objekt-Daten
//                  geschrieben werden
//   CallBackProc   Script-Prozedur die sofort nach dem Aufruf des Servers
//                  und dem Anzeigen der Daten im selben aufgerufen wird
//===========================================================================
#pragma pack(1)
struct setoledocvar_param {
  WORD parSize;
  DWORD bResult;   // out ... Ergebnis des Aufrufs
  DWORD VarName;   // in .... Name der Dokvariable
  DWORD Value;     // in .... Wert der Dokvariable
  DWORD Extended;  // in .... Falls Wert der DokVariable nicht definiert
                   //         -> Spezialfunktion aufrufen
  };
#pragma pack()

BOOL SetOLEDocVar (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    setoledocvar_param FAR *par = (setoledocvar_param FAR *) param;

    LPSTR lpVar = LPSTR (c->ReadlData (par->VarName));
    LPSTR lpVal = LPSTR (c->ReadlData (par->Value));

    BOOL bResult = FALSE;

    BOOL bExtended = FALSE;

    if (par->parSize >= sizeof(*par)) {
      DBBOOL FAR *lpbExtended = (DBBOOL FAR *)c->ReadlData (par->Extended);

      bExtended = *lpbExtended;
      if (bExtended) {
        if (lpVar && *lpVar) {
          if (lpVal && *lpVal)
            bResult = lpOle->SetDocVarEx (lpVar, lpVal);
          else
            bResult = lpOle->SetDocVarEx (lpVar, " ");
          }
        }

      }

    if (!bExtended) {
      if ((lpVar != NULL) && *lpVar &&
          (lpVal != NULL) && *lpVal && lpOle) {
        bResult = lpOle->SetDocVar (lpVar, lpVal);
        }
      else
        bResult = lpOle->SetDocVar (lpVar, " ");
      }


    c->WritelData (par->bResult, &bResult, sizeof(bResult), LPSTR(param)-sizeof(WORD));

    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    setoledocvar_param FAR *par = (setoledocvar_param FAR *) param;
    c->ClearlConnection (par->VarName, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->Value, LPSTR(param) - sizeof(WORD));
    if (par->parSize >= sizeof(*par))
      c->ClearlConnection (par->Extended, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


#pragma pack(1)
struct getoledocvar_param {
  WORD parSize;
  DWORD bResult;
  DWORD VarName;
  DWORD Value;
  };
#pragma pack()

BOOL GetOLEDocVar (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    getoledocvar_param FAR *par = (getoledocvar_param FAR *) param;

    LPSTR lpVar = LPSTR (c->ReadlData (par->VarName));

    char lpVal[1024];

    BOOL bResult = FALSE;

    if ((lpVar != NULL) && *lpVar && lpOle) {
      bResult = lpOle->GetDocVar (lpVar, lpVal);

      if (lpVal != NULL)
        c->WritelData (par->Value, lpVal, lstrlen(lpVal)+1, LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->Value, LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->Value, LPSTR(param)-sizeof(WORD));

    c->WritelData (par->bResult, &bResult, sizeof(bResult), LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    getoledocvar_param FAR *par = (getoledocvar_param FAR *) param;
    c->ClearlConnection (par->VarName, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct oleprint_param {
  WORD parSize;
  DWORD bResult;
  DWORD bSelectPrinter;
  };
#pragma pack()

BOOL OLEPrint (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {

    oleprint_param FAR *par = (oleprint_param FAR *) param;

    BOOL bResult = FALSE;

    DBBOOL FAR *lpbSelectPrinter = (DBBOOL FAR *)(c->ReadlData (par->bSelectPrinter));
    BOOL bSelectPrinter = (lpbSelectPrinter != NULL) ? *lpbSelectPrinter : FALSE;

    if (lpOle != NULL) {
      bResult = lpOle->PrintDoc (bSelectPrinter);
      }

    c->WritelData (par->bResult, &bResult, sizeof(bResult), LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    oleprint_param FAR *par = (oleprint_param FAR *) param;
    c->ClearlConnection (par->bSelectPrinter, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


#pragma pack(1)
struct olegetiunknown_param {
  WORD parSize;
  DWORD MyIUnknown;
  };
#pragma pack()

BOOL GetMyIUnknown (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {

    olegetiunknown_param FAR *par = (olegetiunknown_param FAR *) param;

    if (lpOle != NULL) {

      LPUNKNOWN MyObj = NULL;
      lpOle->GetMyIUnknown (&MyObj);

      if (MyObj)
        c->WritelData (par->MyIUnknown, &MyObj, sizeof(MyObj), LPSTR(param)-sizeof(WORD));
      else
        c->DellData (par->MyIUnknown, LPSTR(param)-sizeof(WORD));
      }
    else
      c->DellData (par->MyIUnknown, LPSTR(param)-sizeof(WORD));

    }

  return FALSE;
  }


#pragma pack(1)
struct olegetdocprop_param {
  WORD parSize;
  DWORD bResult;         // out
  DWORD iKind;           // in
  DWORD iIndex;          // in
  DWORD lpszName;        // out
  DWORD lpszValue;       // out
  };
#pragma pack()

BOOL GetOLEDocProp (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    olegetdocprop_param FAR *par = (olegetdocprop_param FAR *) param;

    DBBOOL bResult = FALSE;

    if (lpOle != NULL) {
      DBINT FAR *iKind = (DBINT FAR *)c->ReadlData (par->iKind);
      DBINT FAR *iIndex = (DBINT FAR *)c->ReadlData (par->iIndex);

      if (iKind && iIndex) {

        char szValue[1024];
        char szName[1024];

        bResult = lpOle->GetOLEDocProp (*iKind, *iIndex, szName, szValue);

        if (szValue && szName) {
          c->WritelData (par->lpszName, szName, lstrlen(szName)+1, LPSTR(param)-sizeof(WORD));
          c->WritelData (par->lpszValue, szValue, lstrlen(szValue)+1, LPSTR(param)-sizeof(WORD));
          }
        else {
          c->DellData (par->lpszName, LPSTR(param)-sizeof(WORD));
          c->DellData (par->lpszValue, LPSTR(param)-sizeof(WORD));
          }
        }
      }

    c->WritelData (par->bResult, &bResult, sizeof(bResult), LPSTR(param)-sizeof(WORD));

    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    olegetdocprop_param FAR *par = (olegetdocprop_param FAR *) param;
    c->ClearlConnection (par->iKind, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->iIndex, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


#pragma pack(1)
struct olerestrictinput_param {
  WORD parSize;
  DWORD bResult;
  DWORD iLevel;
  DWORD lpszPassWord;
  };
#pragma pack()

BOOL OLERestrictInput (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    olerestrictinput_param FAR *par = (olerestrictinput_param FAR *) param;

    BOOL bResult = FALSE;

    if (lpOle != NULL) {

      DBINT FAR *lpiLevel = (DBINT FAR *)(c->ReadlData (par->iLevel));
      LPSTR lpszPassWord = (LPSTR)(c->ReadlData (par->lpszPassWord));

      if (lpiLevel && lpszPassWord)
        bResult = lpOle->RestrictInput (*lpiLevel, lpszPassWord);
      }

    c->WritelData (par->bResult, &bResult, sizeof(bResult), LPSTR(param)-sizeof(WORD));
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    olerestrictinput_param FAR *par = (olerestrictinput_param FAR *) param;
    c->ClearlConnection (par->iLevel, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->lpszPassWord, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


BOOL OLEUpdateFields (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {

    if (lpOle != NULL) {
      lpOle->UpdateFields ();
      }
    }

  return FALSE;
  }


#pragma pack(1)
struct olesethostname_param {
  WORD parSize;
  DWORD lpszHostName;
  };
#pragma pack()

BOOL OLESetHostName (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    olesethostname_param FAR *par = (olesethostname_param FAR *) param;

    LPSTR lpszHostName = (LPSTR)(c->ReadlData (par->lpszHostName));

    if (lpszHostName)
      SetOLEHostName (lpszHostName);
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    olesethostname_param FAR *par = (olesethostname_param FAR *) param;
    c->ClearlConnection (par->lpszHostName, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }

#pragma pack(1)
struct runmacro_param {
  WORD parSize;
  DWORD makroNum;
  };
#pragma pack()

BOOL RunAutomacro (mdiChild *c,LPVOID param,WORD mode)
  {
  if (mode & EM_LOAD) {
    runmacro_param FAR *par = (runmacro_param FAR *) param;

    DBINT FAR * mnum = (DBINT FAR *) c->ReadlData (par->makroNum);

    if ((lpOle != NULL) && (mnum != NULL)) {
      lpOle->RunAutoMacro (*mnum);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    runmacro_param FAR *par = (runmacro_param FAR *) param;
    c->ClearlConnection (par->makroNum, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//===========================================================================
//
// CloseApplicationWord
//
// Zweck: Schliesst den OLE Server.
//        Der Parameter bietet die Moeglichkeit der Interaktion beim
//        Schliessen.
//
// Parameter:
//   iSaveChanges   wdDoNotSaveChanges      0
//                  wdPromptToSaveChanges  -2
//                  wdSaveChanges          -1
//===========================================================================
#pragma pack(1)
struct closeapplicationword_param {
  WORD  parSize;
  DWORD iSaveChanges;   // in ... Schliessen Enumeration
  };
#pragma pack()

BOOL CloseApplicationWord (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    closeapplicationword_param FAR *par = (closeapplicationword_param FAR *) param;

    DBINT FAR * lpiSaveChanges = (DBINT FAR *) c->ReadlData (par->iSaveChanges);

    if ((lpOle != NULL) && (lpiSaveChanges  != NULL)) {
      lpOle->CloseApplicationWord (*lpiSaveChanges);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    closeapplicationword_param FAR *par = (closeapplicationword_param FAR *) param;
    c->ClearlConnection (par->iSaveChanges, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }


//===========================================================================
//
// SaveWordObjectAs
//
// Zweck:  Bietet die Moeglichkeit, das Dokument (zusaetzlich zum Blob in der
//         Datenbank) auch unter einem Dateinamen zu speichern.
//        
//
// Parameter:
//   szFileName   Dateiname, unter dem das Dokument abgelegt wird
//   iFileFormat  Format, unter dem die Datei abgespeichert wird
//                wdFormatDocument             0
//                wdFormatDOSText              4
//                wdFormatDOSTextLineBreaks    5
//                wdFormatEncodedText          7
//                wdFormatHTML                 8
//                wdFormatRTF                  6
//                wdFormatTemplate             1
//                wdFormatText                 2
//                wdFormatTextLineBreaks       3
//                wdFormatUnicodeText          7
//===========================================================================
#pragma pack(1)
struct savewordobjectas_param {
  WORD  parSize;
  DWORD szFileName;   // in ... Dateiname des Dokuments
  DWORD iFileFormat;  // in ... Dateiformat
  };
#pragma pack()

BOOL SaveWordObjectAs (mdiChild *c, LPVOID param, WORD mode)
  {
  if (mode & EM_LOAD) {
    savewordobjectas_param FAR *par = (savewordobjectas_param FAR *) param;

    LPSTR lpszFileName = (LPSTR)(c->ReadlData (par->szFileName));
    DBINT FAR * lpiFileFormat = (DBINT FAR *) c->ReadlData (par->iFileFormat);

    if ((lpOle != NULL) && 
        (lpszFileName && *lpszFileName) &&
        (lpiFileFormat != NULL)) {
      lpOle->SaveWordObjectAs (lpszFileName, *lpiFileFormat);
      }
    }

  if (mode & (EM_RESET | EM_CLEAR)) {
    savewordobjectas_param FAR *par = (savewordobjectas_param FAR *) param;
    c->ClearlConnection (par->szFileName, LPSTR(param) - sizeof(WORD));
    c->ClearlConnection (par->iFileFormat, LPSTR(param) - sizeof(WORD));
    }

  return FALSE;
  }
