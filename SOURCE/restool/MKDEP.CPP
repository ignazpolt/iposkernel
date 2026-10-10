//-----------------------------------------------------------------
// Kompilieren von Abhaengigkeiten
//-----------------------------------------------------------------
//  $Header:   P:/marille/clinicum/restool/rev/mkdep.cpv   1.9   27 Apr 1999 16:37:20   Wolfgang  $
//  $Log:   P:/marille/clinicum/restool/rev/mkdep.cpv  $
// 
//    Rev 1.9   27 Apr 1999 16:37:20   Wolfgang
// 1.) Zyklus-Check korrigiert.
// 
//    Rev 1.8   26 Apr 1999 18:11:36   Wolfgang
// 1.) Getrenntes IDD generieren ausgebaut.
// 2.) Bei DDD mit Abhaengigkeiten, Module die von Views abhaengig sind direkt 
//     ermitteln.
// 3.) Abhaengige Module ermitteln.
// 4.) Meldung bei zyklischer Abhaengigkeit.
// 
//    Rev 1.7   14 Apr 1999 18:14:20   Wolfgang
// 1.) Makefile mit end abschliessen.
// 
//    Rev 1.6   26 Mar 1999 18:14:22   Wolfgang
// 1.) Sortieren der Module nach Abhaengigkeiten vor Generierung.
// 2.) Generieren fuer Makefile und Schreiben desselben.
// 
//    Rev 1.5   18 Mar 1999 14:07:20   Wolfgang
// 1.) Angabe des Feldes bei SB_SETTEXT ueber Konstante.
// 
//    Rev 1.4   17 Aug 1998 17:59:02   Hannes
// SourceFileName verwendet
// 
//    Rev 1.3   05 Jan 1998 07:53:24   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.2   13 Mar 1997 19:04:58   Hannes
// 
//    Rev 1.1   19 Feb 1997 12:14:28   Hannes
// Modulabhaengigkeiten
// 
//    Rev 1.0   26 Nov 1996 08:11:16   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "btrieve.hpp"
#include "hash.hpp"
#include "compile.hpp"
#include "restool.hpp"
#define MODULENUM 175
#include "winass.hpp"

#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#include "tbcmpl.hpp"
#include "dbrecord.hpp"

#include "communic.hpp"
#include "scripthd.hpp"

#include "statbar.hpp"
#include "msdntb.h"

extern HWND hWndToolbar;

BOOL CheckDepended;
BOOL CheckToMakeFile;

struct FileMakeEntry {
  char FileName[13];
  BOOL IsGenerated;
  FileMakeEntry FAR *Prev;
  FileMakeEntry FAR *Next;
  };
typedef FileMakeEntry FAR *LPFILEMAKEENTRY;

LPFILEMAKEENTRY fme;

BOOL ExistEntry ()

  {
  return (fme !=NULL);
  }

LPFILEMAKEENTRY FindEntry (LPFILEMAKEENTRY FileList, LPSTR FileName)
  {
  for (LPFILEMAKEENTRY e = FileList ; e != NULL ; e = e->Next) {
    if (lstrcmp (e->FileName,FileName) == 0)
      return e ;
    }
  return NULL ;
  }

LPFILEMAKEENTRY FindSourceEntry (LPSTR FileName)
  {
  return FindEntry (fme, FileName);
  }

extern LPSTR GetFName(LPVOID fname);
extern LPSTR GetExtension (LPSTR fName);
extern LPSTR GetNameOnly (LPSTR fName);

void PushForMake (LPFILEMAKEENTRY FAR * FileList, LPSTR FileName, BOOL alreadyGenerated)
  {
  char FName[128];
  lstrcpy (FName,FileName);
  GetFName (FName);
  AnsiUpper (FName);
  if (FindEntry (*FileList, FName) == NULL) {
    LPFILEMAKEENTRY f = (LPFILEMAKEENTRY) GetGlobMem (sizeof(*f)) ;
    lstrcpy (f->FileName,FName);
    f->IsGenerated = alreadyGenerated;
    if (*FileList != NULL) {
      for (LPFILEMAKEENTRY e = *FileList ; e->Next != NULL ; e = e->Next) ;
      e->Next = f ;
      f->Prev = e ;
      }
    else
      *FileList = f ;
    }
  }

void PushSourceForMake (LPSTR FileName)
  {
  PushForMake (&fme, FileName, FALSE);
  }

void MarkGenerated (LPFILEMAKEENTRY FAR * FileList, LPSTR FileName)
  {
  char FName[128];
  lstrcpy (FName,FileName);
  GetFName (FName);
  AnsiUpper (FName);
  LPFILEMAKEENTRY f = FindEntry (*FileList, FName);
  if (f != NULL)
    f->IsGenerated = TRUE ;
  else
    PushForMake (FileList, FileName, TRUE);
  }

void MarkSourceGenerated (LPSTR FileName)
  {
  MarkGenerated (&fme, FileName);
  }

extern BOOL GenTbScript (HWND hWnd,LPSTR fname);
extern BOOL GenRepScript (HWND hWnd,LPSTR fname);
extern BOOL GenIntScript (HWND hWnd,LPSTR fname);
extern BOOL GenGScript (HWND hWnd,LPSTR fname);
void ShowErrScript (LPSTR FName)
  {
  char OutText[256];
  wsprintf (OutText,"Error on %s",FName);
  MessageBox (GetActiveWindow(),OutText,"Error",MB_ICONEXCLAMATION | MB_OK);
  }
extern HWND hWndStatusbar;

BOOL GenerateNextFile (LPFILEMAKEENTRY FileList, BOOL *error)
  {
  BOOL res = FALSE ;
  if (error != NULL)
    *error = FALSE;
  for (LPFILEMAKEENTRY e = FileList ; e != NULL ; e = e->Next) {
    if (!e->IsGenerated) {
      char outtxt[128];
      wsprintf (outtxt,"Compiling %s",e->FileName);
      char fName[128],fName1[128];
      SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(outtxt)));
      GetIncludeFileName (e->FileName,fName,fName1,"source");
      for ( LPSTR h = e->FileName ; ((*h != '.') && (*h)) ; h++ ) ;
      if (*h == '.') h++ ;
      if (lstrcmp (h,"DDD") == 0) {
        res = GenTbScript (GetActiveWindow (),fName);
        if (!res)
          ShowErrScript (e->FileName);
        }
      else if (lstrcmp(h,"REP") == 0) {
        res = GenRepScript (GetActiveWindow(),fName);
        if (!res)
          ShowErrScript (e->FileName);
        }
      else if (lstrcmp (h,"IDD") == 0) {
        res = GenIntScript (GetActiveWindow(),fName);
        if (!res)
          ShowErrScript (e->FileName);
        }
      else if (lstrcmp (h,"MOD") == 0) {
        int errorNum ;
        if ((errorNum = DoCompileMod (GetActiveWindow(),fName)) == 0) {
          CreateScriptContent(e->FileName);
          ClearCachedProg (e->FileName);
          res = TRUE ;
          }
        else
          ShowErrScript (e->FileName);
        }
      else {
        if (res = GenerateScript (GetActiveWindow(),fName)) {
          CreateScriptContent(e->FileName);
          ClearCachedProg (e->FileName);
          }
        else
          ShowErrScript (e->FileName);
        }
      e->IsGenerated = TRUE ;
      if (error != NULL)
        *error = !res;
      break ;
      }
    }
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("")));
  return res;
  }

BOOL GenerateNextSource (BOOL *error)
  {
  return GenerateNextFile (fme, error);
  }

extern void StartWrite ();
extern int WriteToBuff (HFILE fi,LPSTR Buff,DWORD Size);
extern void EndWrite (HFILE fi);

char sectionText [1024];

BOOL WriteToMakeFile (LPFILEMAKEENTRY FileList, LPSTR fName)

  {
  OFSTRUCT Ofs;
  int fi = OpenFile (fName,&Ofs,OF_CREATE | OF_WRITE);
  BOOL fault = FALSE ;
  if (fi >= 0) {
    StartWrite();
    char oldext[10] = "";
    for (LPFILEMAKEENTRY eNext, e = FileList ; e != NULL ; e = e->Next) {
      LPSTR name = GetNameOnly (e->FileName);
      LPSTR ext = GetExtension (e->FileName);
      if (lstrcmp (ext, oldext) != 0) {
        if (*oldext != '\0')
          sprintf (sectionText, "$************************* Ende der Sektion fuer %ss *************************\r\n\r\n",
                                oldext);
        else
          *sectionText = '\0';
        if (lstrcmp (ext, "DDD") == 0)
          lstrcat (sectionText, 
            "$--------------------------- Tabellen der Datenbank ---------------------------\r\n DB_Tabellen\r\n");
        else if (lstrcmp (ext, "IDD") == 0)
          lstrcat (sectionText, 
            "$----------------------------------- Views ------------------------------------\r\n INT_Tabellen\r\n");
        else if (lstrcmp (ext, "GDD") == 0)
          lstrcat (sectionText, 
            "$---------------------------------- Structs -----------------------------------\r\n GLOB_Tabellen\r\n");
        else if (lstrcmp (ext, "MOD") == 0)
          lstrcat (sectionText, 
            "$---------------------------------- Modules -----------------------------------\r\n Modules\r\n");
        else if (lstrcmp (ext, "TXT") == 0)
          lstrcat (sectionText, 
            "$---------------------------------- Scripts -----------------------------------\r\n Scripts\r\n");
        else
          lstrcat (sectionText, 
            "$?????????????????????????????????? Unkown ????????????????????????????????????\r\n Files with unkown Extension\r\n");
        WORD size = lstrlen (sectionText);   // Text ohne '\0'
        fault = WriteToBuff (fi,sectionText,size);
        }
      WORD size = lstrlen (name);   // Text ohne '\0'
      fault = WriteToBuff (fi,name,size);
      fault = WriteToBuff (fi,"\r\n",2);
      lstrcpy (oldext, ext);
      }
    if (*oldext != '\0') {
      sprintf (sectionText, "$************************* Ende der Sektion fuer %ss *************************\r\n\r\n",
                            oldext);
      WORD size = lstrlen (sectionText);   // Text ohne '\0'
      fault = WriteToBuff (fi,sectionText,size);
      }
    fault = WriteToBuff (fi,"end\r\n",5);
    EndWrite (fi);
    _lclose (fi);
    }
  else
    fault = TRUE ;
  return !fault;
  }

BOOL WriteSourcesToMakeFile (LPSTR fileName)

  {
  return WriteToMakeFile (fme, fileName);
  }

void SetCheck (BOOL value)
  {
  CheckDepended = value ;
  }

void SetCheckToMakeFile (BOOL value)
  {
  CheckToMakeFile = value ;
  SendMessage (hWndToolbar, TB_CHECKBUTTON, MI_GENMAKEFILE, MAKELPARAM(CheckToMakeFile,0));
  }

BOOL IsCheckToMakeFile ()
  {
  return CheckToMakeFile;
  }

void FreeFileEntrys (LPFILEMAKEENTRY FAR * FileList)

  {
  for ( ; *FileList != NULL ; ) {
    LPFILEMAKEENTRY n = (*FileList)->Next ;
    FreeGlobMem (*FileList);
    (*FileList) = n ;
    }
  }

void CheckClearUp ()
  {
  FreeFileEntrys (&fme);
  SetCheck (FALSE);
  SetCheckToMakeFile (FALSE);
  }

void MarkTable (WORD TableID, BOOL recursive)
  {
  if (TableID < GLOBALTBIDMIN) {
    // Es handelt sich um eine ddd -> Suchen aller IDDs
    for (ContEntry FAR *ce = GetTableAdmin()->GetContent()->First() ;
            ce != NULL ; ce = GetTableAdmin()->GetContent()->Next(ce) ) {
      if ((ce->tRef.TableNr >= INTERNTBIDMIN) && (ce->tRef.TableNr < INTERNTBIDMAX)) {
        SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR(ce->TableName)));
        // Tabelle muss genauer untersucht werden
        LPTABLEDEF td = GetTableAdmin()->GetTableDef (ce->tRef.TableNr,ce->tRef.Version);
        LPINTTABLE ti = LPINTTABLE (td->GetDLLDef()) ;
        for (int i = 0 ; i < int (ti->AnzTables) ; i++) {
          LPPTABLE pt = ti->GetTableByNum(i);
          if (pt->tRef.TableNr == TableID) {
            LPSTR fileName = td->GetFileName();
            PushSourceForMake (fileName);
            MarkTable (ce->tRef.TableNr, TRUE);
            break;
            }
          }
        GetTableAdmin()->FreeTable(ce->tRef.TableNr,ce->tRef.Version);
        }
      }
    }
  if (!recursive)
    SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Checking Scripts")));
  LoadScriptContent ();
  for (LPSCRIPTCONTENT sc = GetFirstScript (); sc != NULL ; sc = GetNextScript (sc) ) {
    for (int i = 0 ; i < int(sc->AnzTables) ; i++) {
      if (sc->TRef[i].TableNr == TableID) {
        PushSourceForMake (sc->fName);
        break;
        }
      }
    }
  }

void MarkTableForCheck (WORD TableID)
  {
  if (!CheckDepended) 
    return ;
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Checking Table")));
  MarkTable (TableID, FALSE);
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Checking done")));
  }


BOOL IsPartOf (LPSTR modulName, LPSTR baseModules)

  {
  if (baseModules == NULL)
    return FALSE;
  for ( LPSTR x = baseModules ; *x ; x += lstrlen (x) + 1 ) {
    if (lstrcmp (x, modulName) == 0)
      return TRUE;
    }
  return FALSE;
  }
  

hash FAR *ModuleHash; // Hash-Tabelle aller Module von denen aktuelles abhaengig ist

void MarkModule (HWND hWnd, LPSTR modulName)

  {
  ModuleHash->SetData (modulName,&modulName,sizeof(modulName));
  for (LPSCRIPTCONTENT sc = GetFirstScript (); sc != NULL ; sc = GetNextScript (sc)) {
    if (IsPartOf (modulName, sc->BaseModules)) {
      PushSourceForMake (sc->fName);
      if (ModuleHash->GetData (sc->fName) == NULL)
        MarkModule (hWnd, sc->fName);
      else {
        char outtxt[256];
        wsprintf (outtxt,"Zyklische Abhängigkeit mit Modul %s gebraucht von %s", sc->fName, modulName);
        MessageBox (hWnd,outtxt,"Warnung",MB_OK | MB_ICONEXCLAMATION);
        }
      }
    else if (IsPartOf (modulName, sc->VirtualModules) || 
             IsPartOf (modulName, sc->ImportModules)) {
      PushSourceForMake (sc->fName);
      }
    }
  ModuleHash->DelData (modulName);
  }

void MarkModuleForCheck (HWND hWnd, LPSTR modulName)

  {
  if (!CheckDepended) 
    return;
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Checking Scripts")));
  if (ModuleHash == NULL)
    ModuleHash = new hash (101,STRKEY);
  MarkModule (hWnd, modulName);
  SendMessage (hWndStatusbar, SB_SETTEXT, STATBAR_TEXT, LONG(LPSTR("Checking done")));
  }

  
void PushSort (LPFILEMAKEENTRY FAR * toList,   LPFILEMAKEENTRY FAR afterThis, 
               LPFILEMAKEENTRY FAR * fromList, LPFILEMAKEENTRY fromEntry)

  {
  // Wenn erster Eintrag in Ursprungliste, Zeiger der Ursprungsliste aendern
  if (*fromList == fromEntry)
    *fromList = fromEntry->Next;
  // und aus Ursprungsliste aushaengen
  if (fromEntry->Prev != NULL)
    fromEntry->Prev->Next = fromEntry->Next;
  if (fromEntry->Next != NULL)
    fromEntry->Next->Prev = fromEntry->Prev;
  // Vorgaenger auf Zielliste setzen
  fromEntry->Prev = afterThis;
  // Nachfolger auf Zielliste und Nachfolger des Vorgaengers in der Zielliste setzen
  if (afterThis == NULL) {
    // Am Anfang einfuegen
    fromEntry->Next = *toList;
    *toList = fromEntry;
    }
  else {
    fromEntry->Next = afterThis->Next;
    afterThis->Next = fromEntry;
    }
  // Vorgaenger des Nachfolgers in der Zielliste setzen
  if (fromEntry->Next != NULL)
    fromEntry->Next->Prev = fromEntry;
  }

BOOL FindBaseModule (LPSTR modules, LPFILEMAKEENTRY FileList)

  {
  if (modules != NULL) {
    for ( LPSTR x = modules ; *x ; x += lstrlen (x) + 1 ) {
      if (FindEntry (FileList, x))
        return TRUE;
      LPSCRIPTCONTENT lpscent = GetScriptEntry(x);
      if (FindBaseModule (lpscent->BaseModules, FileList))
        return TRUE;
      }
    }
  return FALSE;
  }

void PushExtToSort (LPFILEMAKEENTRY FAR * sortedList, LPFILEMAKEENTRY FAR * insertAt, 
                    LPFILEMAKEENTRY FAR * sourceList, LPSTR extSearch)

  {
  for (LPFILEMAKEENTRY eNext, e = *sourceList ; e != NULL ; e = eNext) {
    eNext = e->Next;
    LPSTR ext = GetExtension (e->FileName);
    if ((*extSearch == '\0') || (lstrcmp (ext, extSearch) == 0)) {
      PushSort (sortedList, *insertAt, sourceList, e);
      *insertAt = e;
      }
    }
  }

BOOL SortToGenerate (HWND hWnd, LPFILEMAKEENTRY FAR * FileList)

  {
  LPFILEMAKEENTRY sorted = NULL;
  LPFILEMAKEENTRY lastSorted = NULL;
  BOOL foundModule = TRUE;
  BOOL sortedModule = TRUE;
  LoadScriptContent ();
  for ( ; foundModule && sortedModule; ) {
    foundModule = FALSE;
    sortedModule = FALSE;
    for (LPFILEMAKEENTRY eNext, e = *FileList ; e != NULL ; e = eNext) {
      eNext = e->Next;
      if (lstrcmp (GetExtension (e->FileName), "MOD") == 0) {
        foundModule = TRUE;
        LPSCRIPTCONTENT lpscent = GetScriptEntry(e->FileName);
        if (!FindBaseModule (lpscent->BaseModules,    *FileList) && 
            !FindBaseModule (lpscent->VirtualModules, *FileList) &&
            !FindBaseModule (lpscent->ImportModules,  *FileList)) {
          PushSort (&sorted, lastSorted, FileList, e);
          lastSorted = e;
          sortedModule = TRUE;
          }
        }
      }
    }
  if (foundModule) {
    MessageBox (hWnd,"Zyklische Abhängigkeit vorhanden","Warnung",MB_OK | MB_ICONEXCLAMATION);
    }
  LPFILEMAKEENTRY lastSortedBegin = NULL;
  PushExtToSort (&sorted, &lastSortedBegin, FileList, "DDD");
  PushExtToSort (&sorted, &lastSortedBegin, FileList, "IDD");
  PushExtToSort (&sorted, &lastSortedBegin, FileList, "GDD");
  PushExtToSort (&sorted, &lastSorted,      FileList, "MOD"); // wenn alles gutgegangen keine mehr da
  PushExtToSort (&sorted, &lastSorted,      FileList, "TXT");
  *FileList = sorted;
  return (!foundModule); // Zurueckgeben, ob Sortierung gutgegangen
  }

BOOL SortSourcesToGenerate (HWND hWnd)
  {
  return SortToGenerate (hWnd, &fme);
  }

