//////////////////////////////////////////////////////////////////////
//  Verwalten von Tabellendefinitionen
//////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/dbhelp/rev/tbdef.cpv   1.59   30 Apr 1999 21:56:16   Hannes  $
//  $Log:   P:/marille/clinicum/dbhelp/rev/tbdef.cpv  $
// 
//    Rev 1.59   30 Apr 1999 21:56:16   Hannes
// Delete PropertyHash
// 
//    Rev 1.58   23 Nov 1998 14:21:16   Hannes
// AnzTableDef vergroessert
// 
//    Rev 1.57   05 Oct 1998 11:09:48   Gerhold
// Vorbereitung auf C6 (Type Casts)
// 
//    Rev 1.56   11 Aug 1998 08:42:44   Hannes
// 
//    Rev 1.55   04 Aug 1998 17:54:56   Hannes
// Timestamp
// 
//    Rev 1.54   28 Jul 1998 19:59:30   Hannes
// Properties, CalculateTableID, Convertto mit TransactionDLL = ConvertDLL ->
// DBAlter
// 
//    Rev 1.53   05 Jan 1998 07:50:48   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.52   19 Dec 1997 17:57:58   Hannes
// InitializeTable.. Fehlerkorrektur wegen GlobalReAlloc
// 
//    Rev 1.51   19 Nov 1997 18:45:34   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.50   10 Nov 1997 10:49:02   Hannes
// Beschleunigungsmassnahmen
// 
//    Rev 1.49   27 May 1997 11:15:46   Hannes
// Id - Handling bei Tabellen ohne Namen..
// 
//    Rev 1.48   06 May 1997 08:26:38   Hannes
// Alle Zugriffe auf convert.ini mit makeini geklammert
// 
//    Rev 1.47   05 May 1997 11:36:24   Hannes
// Speicherfresser verbessert
// 
//    Rev 1.46   30 Apr 1997 11:09:54   Hannes
// 
//    Rev 1.45   30 Apr 1997 08:43:28   Hannes
// Fehlerkorrektur in NewPack
// 
//    Rev 1.44   01 Apr 1997 17:24:52   gerhold
// Tabellendefinition testen auch in 32 Bit-Version
// 
//    Rev 1.43   18 Mar 1997 17:36:18   Hannes
// Liste mit Aktuellen Versionen, die in den Updates verwendet werden sollen
// 
//    Rev 1.42   28 Feb 1997 14:41:06   Hannes
// Fehlerkorrektur in GetDLLFor
// 
//    Rev 1.41   19 Feb 1997 12:06:54   Hannes
// Scriptfunktionen -> Vater von Tabellen fuer Ableitungen
// 
//    Rev 1.40   23 Dec 1996 14:59:58   MARTIN
// auch DBVersion und UpdateStep testen
// 
//    Rev 1.39   20 Dec 1996 21:36:56   MARTIN
// _TEST auch fuer datadict, resdb und scriptdb durchfuehren
// 
//    Rev 1.38   13 Dec 1996 13:17:08   GERHOLD
// ein #endif war falsch positioniert => Compile error bei WIN32
// 
//    Rev 1.37   04 Dec 1996 08:15:54   HANNES
// 
//    Rev 1.36   03 Dec 1996 16:42:04   HANNES
// Namen in Hashtabellen
// 
//    Rev 1.35   26 Nov 1996 07:54:12   HANNES
// Automatischer Update
// 
//    Rev 1.34   08 Nov 1996 13:27:46   HANNES
// Einbau des Replikators
// 
//    Rev 1.33   29 Oct 1996 12:01:08   GERHOLD
// bei DDS _TEST werden die Tabellen und der Fortschritt angezeigt
// 
//    Rev 1.32   12 Sep 1996 23:29:34   HANNES
// Konvertierungslogik verbessert
// 
//    Rev 1.31   03 Sep 1996 10:12:40   HANNES
// HoldBlobs beschleunigt
// 
//    Rev 1.30   05 Jul 1996 08:06:42   martin
// 32 Bit - Aenderungen
// 
//    Rev 1.29   26 Jun 1996 12:24:54   MARTIN
// structs bitte nicht testen (in DBTest())
// 
//    Rev 1.28   20 Jun 1996 23:14:16   MARTIN
// 
//    Rev 1.27   17 Jun 1996 15:46:22   HANNES
// Einbau von BLOBS
// 
//    Rev 1.26   04 Feb 1996 21:41:54   HANNES
// 
//    Rev 1.25   04 Feb 1996 17:53:28   HANNES
// 
//    Rev 1.24   04 Feb 1996 15:37:06   gerhold
// Teile von DBHELP in DDSMEM
// 
//    Rev 1.23   02 Feb 1996 10:42:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.22   31 Jan 1996 18:13:18   HANNES
// 
//    Rev 1.21   04 Dec 1995 20:54:58   HANNES
// FreeTemporaryTableDef
// 
//    Rev 1.20   04 Dec 1995 11:40:52   HANNES
// Aufraeumen der Temparary Tables
// 
//    Rev 1.19   14 Jul 1995 16:56:26   HANNES
// Horizontale Fileteilung
// 
//    Rev 1.18   09 Jun 1995 00:36:10   HANNES
// Aenderung in VarDef
// 
//    Rev 1.17   24 May 1995 17:13:24   HANNES
// Hashliste der dbrecords fuer FindSame
// 
//    Rev 1.16   15 May 1995 08:24:26   HANNES
// RemoveMDIHandleList
// 
//    Rev 1.15   26 Apr 1995 15:32:56   HANNES
// 
//    Rev 1.14   01 Apr 1995 19:43:40   HANNES
// 
//    Rev 1.13   01 Apr 1995 18:09:06   HANNES
//  
// 
//    Rev 1.12   23 Mar 1995 11:46:34   GERHOLD
// WIN_ASSERT in LoadDataDictContent auskommentiert!
// 
//    Rev 1.11   03 Mar 1995 19:07:36   hannes
//  
// 
//    Rev 1.10   24 Feb 1995 11:12:42   HANNES
//  
// 
//    Rev 1.9   16 Feb 1995 12:48:52   HANNES
//  
// 
//    Rev 1.8   29 Jan 1995 11:46:06   HANNES
// 
//    Rev 1.7   24 Jan 1995 10:59:28   HANNES
// Schluesseldefinition in das Clientdictionary mit aufegenommen
// 
//    Rev 1.6   20 Jan 1995 15:54:16   HANNES
// Daten in das Clientdictionary aufnehmen
// 
//    Rev 1.5   10 Jan 1995 15:00:40   HANNES
// 
//    Rev 1.4   08 Nov 1994 12:41:52   HANNES
// Default MAXDLLS vergroessert
// 
//    Rev 1.3   07 Nov 1994 11:43:52   HANNES
// Namen der nicht freigegebenen DLLs
// 
//    Rev 1.2   17 Jul 1994 14:34:20   HANNES
// Umbau der Primaerschluesselverwaltung
// 
//    Rev 1.1   04 Jul 1994 14:47:20   HANNES
// IsViewAllowed
// 
//    Rev 1.0   24 Jun 1994 16:44:52   HANNES
// Neuuebernahme clinicum
//
#include <windows.h>
#include <stdio.h>
#include "dds32.h"

#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 79
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#define NOCOMPILE
#include "compile.hpp"

extern LPSTR WINAPI GetIniName();

// Erzeugen der Speicherinternen Variablendefinitionen
///////////////////////////////////////////////////////////
LPVARDEF GetNewVar (LPSTR Name,LPVOID DLLDefData,DWORD DefDataSize)
  {
  LPVARDEF res ;
  WIN_ASSERT (DefDataSize + lstrlen(Name) + sizeof(*res) < 0x4000);
  int Size = lstrlen (Name) + int(DefDataSize) + sizeof(*res);
  res = LPVARDEF (GetGlobMem (Size));
  res->structSize = Size;
  res->DLLDataOffs = sizeof(*res) + lstrlen(Name);
  lstrcpy (res->GetName(),Name);
  lmemcpy (res->GetDLLData(),DLLDefData,WORD(DefDataSize));

  return res;
  }

// Setzen der Daten vom Compiler aus
///////////////////////////////////////////
void TableDef::SetName (LPSTR n)
  {
  Name.ptr = GetGlobMem (lstrlen(n) + 1);
  lstrcpy (LPSTR(Name.ptr),n);
  }

void TableDef::SetFileName (LPSTR n)
  {
  File.ptr = GetGlobMem (lstrlen(n) + 1);
  lstrcpy (LPSTR(File.ptr),n);
  }

DLLExport void _export WINAPI TableDef::SetDLLDef (LPVOID Data,DWORD Size)
  {
  if (Data != NULL) {
    DLLDefSize = Size;
    d.hGDLLmem = GlobalAlloc (GMEM_MOVEABLE,Size + 32);
    LPSTR ptr  = LPSTR(GlobalLock  (d.hGDLLmem));
    hmemcpy (ptr,Data,Size);
    GlobalUnlock (d.hGDLLmem);
    }
  else {
    DLLDefSize = 0L;
    d.hGDLLmem = 0;
    }
  }

LPTABLEDEF TableDef::PushVar (WORD RowNumber,LPVARDEF var)
  {
  int nAnzVars = max(int(RowNumber + 1),AnzVars);
  DWORD size  = DWORD(sizeof(*this)) + DWORD (nAnzVars) * DWORD(sizeof(LPVOID)) ;
  DWORD osize = DWORD(sizeof(*this)) + DWORD (AnzVars) * DWORD(sizeof(LPVOID)) ;
  GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,size + 32);
  LPTABLEDEF res = LPTABLEDEF (GlobalLock(hGres));
  hmemcpy (res,this,osize);
  res->g.hGmem = hGres;
  res->VarTable.ptr = LPSTR(res) + sizeof(*res);
  LPVARDEF HUGE * ptbl = (LPVARDEF HUGE *) res->VarTable.ptr;
  WIN_ASSERT(ptbl[RowNumber] == NULL);
  ptbl[RowNumber] = LPVARDEF (GetGlobMem (var->StructSize ()));
  lmemcpy (ptbl[RowNumber],var,var->StructSize ());
  res->AnzVars = nAnzVars;

  return res ;
  }

DLLExport LPTABLEDEF _export WINAPI TableDef::AddVar (LPVARDEF v)
  {
  WORD VarNr = AnzVars ;
  AnzVars ++ ;
  DWORD size = DWORD(sizeof(*this)) + DWORD (AnzVars) * DWORD(sizeof(LPVOID)) ;
  GLOBALHANDLE hGres = GlobalAlloc (GMEM_MOVEABLE | GMEM_ZEROINIT,size + 32);
  LPTABLEDEF res = LPTABLEDEF (GlobalLock(hGres));
  hmemcpy (res,this,size - sizeof(DWORD));
  res->g.hGmem = hGres;
  res->VarTable.ptr = LPSTR(res) + sizeof(*res);
  LPVARDEF HUGE * ptbl = (LPVARDEF HUGE *) res->VarTable.ptr;
  ptbl[VarNr] = LPVARDEF (GetGlobMem (v->StructSize ()));
  lmemcpy (ptbl[VarNr],v,v->StructSize ());
  GlobalUnlock (g.hGmem);
  GlobalFree (g.hGmem);
  return res;
  }

DLLExport void _export WINAPI TableDef::AddKey (LPCLKEYDEF k)
  {
  AnzKeySegs ++ ;
  LPCLKEYDEF FAR *n = (LPCLKEYDEF FAR *) GetGlobMem (AnzKeySegs * sizeof(LPCLKEYDEF));
  if (AnzKeySegs > 1) {
    lmemcpy (n,KeyTable.ptr,(AnzKeySegs-1)*sizeof(LPCLKEYDEF));
    FreeGlobMem (KeyTable.ptr);
    }
  n[AnzKeySegs-1] = LPCLKEYDEF(GetGlobMem (int (k->structSize)));
  lmemcpy (n[AnzKeySegs-1],k,int(k->structSize));
  KeyTable.ptr = n;
  }

DLLExport void _export WINAPI TableDef::AddForeign (LPCLRIDEF r)
  {
  AnzRIDefs ++ ;
  LPCLRIDEF FAR *n = (LPCLRIDEF FAR *) GetGlobMem (AnzRIDefs * sizeof(LPCLRIDEF));
  if (AnzRIDefs > 1) {
    lmemcpy (n,RITable.ptr,(AnzRIDefs-1)*sizeof(LPCLRIDEF));
    FreeGlobMem (RITable.ptr);
    }
  n[AnzRIDefs-1] = LPCLRIDEF(GetGlobMem (int (r->structSize)));
  lmemcpy (n[AnzRIDefs-1],r,int(r->structSize));
  RITable.ptr = n;
  }

void DelId (WORD Id2);
DLLExport void _export WINAPI TableDef::Clear ()
  {
  // Freigeben des Namens und der DLLDefinition
  if (Name.ptr) FreeGlobMem (Name.ptr);
  if (File.ptr) FreeGlobMem (File.ptr);
  DelId(tRef.TableNr);
  if (d.hGDLLmem) {
    GlobalFree  (d.hGDLLmem);
    d.hGDLLmem = 0;
    }

  // Freigeben der Variablendeklarationen
  LPVARDEF HUGE * ptbl = (LPVARDEF HUGE *) VarTable.ptr;
  for (int i = 0 ; i < GetAnzVars() ; i++)
    if (ptbl[i] != NULL) FreeGlobMem (ptbl[i]);

  // Freigeben der Schluesseldefinitionen
  LPCLKEYDEF HUGE * ktbl = (LPCLKEYDEF HUGE *) KeyTable.ptr;
  if (ktbl != NULL) {
    for (int i = 0 ; i < AnzKeySegs ; i++)
      if (ktbl[i] != NULL) FreeGlobMem (ktbl[i]);
    FreeGlobMem (ktbl);
    }

  // Freigeben der Foreigndefinition
  LPCLRIDEF HUGE * rtbl = (LPCLRIDEF HUGE *) RITable.ptr;
  if (rtbl != NULL) {
    for (int i = 0 ; i < AnzRIDefs ; i++)
      if (rtbl[i] != NULL) FreeGlobMem (rtbl[i]);
    FreeGlobMem (rtbl);
    }
  }

/*--------------< friend functions of TableDef >----------------*/
// Initialisieren einer Tabellendefinition
hash FAR *PropertyHash;
DLLExport TableDef FAR * _export WINAPI InitializeTable (GLOBALHANDLE hGres)
  {
  LPTABLEDEF res = LPTABLEDEF (GlobalLock (hGres));
  res->g.hGmem = hGres;

  // Zeiger in die Fixstrukturen eintragen
  ////////////////////////////////////////////
  res->Name.ptr     = LPSTR(res) + res->Name.offs;
  res->File.ptr     = LPSTR(res) + res->File.offs;

  res->VarTable.ptr = LPSTR(res) + res->VarTable.offs;
  if (res->AnzKeySegs)
    res->KeyTable.ptr = LPSTR(res) + res->KeyTable.offs;
  if (res->AnzRIDefs)
    res->RITable.ptr = LPSTR(res) + res->RITable.offs;

  // fuer die Variablen Kopien anlegen
  ///////////////////////////////////////
  LPVARDEF HUGE * ptbl = (LPVARDEF HUGE *) res->VarTable.ptr;
  DWORD    HUGE * otbl = (DWORD    HUGE *) res->VarTable.ptr;
  for (int i = 0 ; i < res->GetAnzVars() ; i++) {
    if (otbl[i] != NULL) {
      ptbl[i] = LPVARDEF (((char HUGE *) res) + otbl[i]);
      ptbl[i]->Initialize ();
      }
    }

  if (res->AnzKeySegs > 0) {
    LPCLKEYDEF HUGE * ktbl = (LPCLKEYDEF HUGE *) res->KeyTable.ptr;
    DWORD      HUGE * otbl = (DWORD      HUGE *) res->KeyTable.ptr;
    for (i = 0 ; i < res->AnzKeySegs ; i++) {
      if (otbl[i] != NULL) {
        ktbl[i] = LPCLKEYDEF (((char HUGE *) res) + otbl[i]);
        }
      }
    }

  if (res->AnzRIDefs > 0) {
    LPCLRIDEF HUGE * rtbl = (LPCLRIDEF HUGE *) res->RITable.ptr;
    DWORD     HUGE * otbl = (DWORD     HUGE *) res->RITable.ptr;
    for (i = 0 ; i < res->AnzRIDefs ; i++) {
      if (otbl[i] != NULL) {
        rtbl[i] = LPCLRIDEF (((char HUGE *) res) + otbl[i]);
        }
      }
    }

  if (res->DLLDefSize) {
    res->d.DLLDef.ptr = LPSTR(res) + res->d.DLLDef.offs;
    if ((!res->IsTemporaryTable()) && (!res->IsInternTable()) && (!res->IsGlobalTable()) && (res->DLLDefSize)) {
      //
      // Es handelt sich um die Properties. Diese werden ausgelagert, damit die
      // eigentliche Information mit DataDict_NewTableDef ermittelt werden kann.
      //
      if (PropertyHash == NULL) PropertyHash = new hash (237,WORDKEY);
      PropertyHash->SetDataW (res->GetTableID(),res->d.DLLDef.ptr,res->DLLDefSize);
      res->DLLDefSize = 0L ;
      res->d.DLLDef.ptr = NULL;
      }
    }
  if ((!res->IsTemporaryTable()) && (!res->IsInternTable()) && (!res->IsGlobalTable())) {
    // Noch die Datenbankdefinition herstellen
    LPDLLENTRY ent = GetDLLAdmin()->GetDLLEntry(res->GetDLLHandle());
    DWORD dllSize;
    BOOL error = FALSE;
    LPVOID dllDef = ent->DataDict_NewTableDef (res,"",&error,&dllSize);
    WIN_ASSERT (!error);

    if (dllDef != NULL) {
      GLOBALHANDLE hGResOld = hGres;
      DWORD offs = GlobalSize(hGres);
      char huge *resOld = (char huge *) res ;
      GLOBALHANDLE hGres1 = GlobalAlloc (GMEM_MOVEABLE,offs + dllSize);
      res = LPTABLEDEF (GlobalLock (hGres1));
      hmemcpy (res,resOld,GlobalSize (hGres));
      res->g.hGmem = hGres1 ;

      hmemcpy (res->d.DLLDef.ptr = (char HUGE *) res + offs,dllDef,dllSize);

      ent->DataDict_FreeTableDef (dllDef);

      // Die Zeiger neu setzen
      res->Name.ptr     = LPSTR(res) + DWORD ((char huge *) res->Name.ptr - resOld) ;
      res->File.ptr     = LPSTR(res) + DWORD ((char huge *) res->File.ptr - resOld) ;

      res->VarTable.ptr = LPSTR(res) + DWORD ((char huge *) res->VarTable.ptr - resOld) ;
      if (res->AnzKeySegs)
        res->KeyTable.ptr = LPSTR(res) + DWORD ((char huge *) res->KeyTable.ptr - resOld) ;
      if (res->AnzRIDefs)
        res->RITable.ptr = LPSTR(res) + DWORD ((char huge *) res->RITable.ptr - resOld) ;

      // fuer die Variablen Kopien anlegen
      ///////////////////////////////////////
      LPVARDEF HUGE * ptbl = (LPVARDEF HUGE *) res->VarTable.ptr;
      for (int i = 0 ; i < res->GetAnzVars() ; i++) {
        if ((ptbl[i] != NULL) && (ptbl[i]->DLLDataOffs == 0)) {
          // Daten nicht von der DLL geaendert
          ptbl[i] = LPVARDEF (((char HUGE *) res) + DWORD ((char huge *) (ptbl[i]) - resOld));
          }
        }

      if (res->AnzKeySegs > 0) {
        LPCLKEYDEF HUGE * ktbl = (LPCLKEYDEF HUGE *) res->KeyTable.ptr;
        for (i = 0 ; i < res->AnzKeySegs ; i++) {
          if (ktbl[i] != NULL) {
            ktbl[i] = LPCLKEYDEF (((char HUGE *) res) + DWORD ((char huge *) (ktbl[i]) - resOld));
            }
          }
        }

      if (res->AnzRIDefs > 0) {
        LPCLRIDEF HUGE * rtbl = (LPCLRIDEF HUGE *) res->RITable.ptr;
        for (i = 0 ; i < res->AnzRIDefs ; i++) {
          if (rtbl[i] != NULL) {
            rtbl[i] = LPCLRIDEF (((char HUGE *) res) + DWORD ((char huge *) (rtbl[i]) - resOld));
            }
          }
        }
      GlobalUnlock (hGResOld);
      GlobalFree (hGResOld);
      }
    }

  return res;
  }

// Erzeugen einer neuen Tabellendefinition
TableDef FAR *TableDef_New (LPSTR Name,LPSTR FileName,WORD TableId,WORD Version,LPVOID DLLData,DWORD Size)
  {
  LPTABLEDEF res;
  GLOBALHANDLE hGres = GlobalAlloc (GHND,sizeof(*res) + 32);
  res = LPTABLEDEF (GlobalLock (hGres));
  res->g.hGmem = hGres;
  res->VarTable.ptr = LPSTR(res) + sizeof(*res);
  res->SetName     (Name);
  res->SetFileName (FileName);
  res->SetTableID  (TableId,Version);
  res->SetDLLDef   (DLLData,Size);

  return res;
  }

// Variable anhaengen
TableDef FAR *TableDef_PushVar (WORD RowNumber,LPTABLEDEF table,LPVARDEF var)
  {
  LPTABLEDEF res = table->PushVar (RowNumber,var);
  GLOBALHANDLE hGold = table->g.hGmem;
  GlobalUnlock (hGold);
  GlobalFree (hGold);
  return res;
  }

// Struktur packen, bevor sie gespeichert wird
DWORD NextOffset (DWORD Size,DWORD RoundTo)
  {
  if ((Size % RoundTo) != 0) {
    Size = ((Size / RoundTo) + 1) * RoundTo ;
    }
  return Size;
  }

LPSTR GetDefaultDLLName(LPSTR Name)
  {
  GetPrivateProfileString ("DataBase","DefaultDLL","dbbtrv.dll",
                          Name,64,
                          GetIniName());
  return Name;
  }

DLLExport TableDef FAR *_export WINAPI TableDef_NewPack (TableDef FAR *table,DWORD FAR *GesSize)
  {
  // Ermitteln der Gesamtgroesse
  DWORD Size = NextOffset (sizeof(*table),sizeof(DWORD));
  Size += lstrlen(table->GetName()) + 1;
  Size = NextOffset (Size,sizeof(DWORD));
  Size += lstrlen(table->GetFileName()) + 1;
  Size = NextOffset (Size,sizeof(DWORD));
  Size += table->DLLDefSize;
  Size = NextOffset (Size,sizeof(DWORD));
  Size += table->GetAnzVars() * sizeof(DWORD);
  LPVARDEF HUGE * ptbl = (LPVARDEF HUGE *) table->VarTable.ptr;
  for (int i = 0 ; i < table->GetAnzVars () ; i++) {
    if (ptbl[i] != NULL) {
      Size += ptbl[i]->StructSize();
      Size = NextOffset (Size,sizeof(DWORD));
      }
    }

  // Groesse der Schluesselinfo
  Size += table->AnzKeySegs * sizeof(DWORD);
  LPCLKEYDEF HUGE * ktbl = (LPCLKEYDEF HUGE *) table->KeyTable.ptr;
  for (i = 0 ; i < table->AnzKeySegs ; i++) {
    if (ktbl[i] != NULL) {
      Size += ktbl[i]->structSize;
      Size = NextOffset (Size,sizeof(DWORD));
      }
    }

  // Groesse der RI - Def
  Size += table->AnzRIDefs * sizeof(DWORD);
  LPCLRIDEF HUGE * rtbl = (LPCLRIDEF HUGE *) table->RITable.ptr;
  for (i = 0 ; i < table->AnzRIDefs ; i++) {
    if (rtbl[i] != NULL) {
      Size += rtbl[i]->structSize;
      Size = NextOffset (Size,sizeof(DWORD));
      }
    }

  GLOBALHANDLE hGres = GlobalAlloc (GHND,Size + 32);
  LPTABLEDEF res = LPTABLEDEF (GlobalLock (hGres));
  *res = *table;

  // Alles der Reihe nach hineinkopieren und Offsets eintragen
  res->g.hGmem = hGres;
  Size = NextOffset (sizeof(*table),sizeof(DWORD));

  res->Name.offs = Size;
  lstrcpy (LPSTR(res) + res->Name.offs,table->GetName());
  Size += lstrlen(table->GetName()) + 1;
  Size = NextOffset (Size,sizeof(DWORD));

  res->File.offs = Size;
  lstrcpy (LPSTR(res) + res->File.offs,table->GetFileName());
  Size += lstrlen(table->GetFileName()) + 1;
  Size = NextOffset (Size,sizeof(DWORD));

  if (table->DLLDefSize) {
    LPVOID DLLData = LPVOID (GlobalLock (table->d.hGDLLmem));
    hmemcpy (LPSTR(res) + Size,DLLData,table->DLLDefSize);
    GlobalUnlock (table->d.hGDLLmem);
    }
  res->d.DLLDef.offs = Size;
  Size += table->DLLDefSize;
  Size = NextOffset (Size,sizeof(DWORD));
  ptbl = (LPVARDEF HUGE *) table->VarTable.ptr;
  res->VarTable.offs = Size;
  DWORD FAR * otbl = (DWORD HUGE *) ((char HUGE *) res + res->VarTable.offs);
  Size += table->GetAnzVars() * sizeof(DWORD);
  for (i = 0 ; i < table->GetAnzVars () ; i++) {
    if (ptbl[i] != NULL) {
      otbl[i] = Size ;
      hmemcpy ((char HUGE *) res + otbl[i],ptbl[i],ptbl[i]->StructSize());
      Size += ptbl[i]->StructSize();
      Size = NextOffset(Size,sizeof(DWORD));
      }
    else
      otbl[i] = 0L;
    }

  // Kopieren der Schluesselinfo
  if (res->AnzKeySegs > 0) {
    res->KeyTable.offs = Size;
    DWORD FAR * otbl = (DWORD HUGE *) ((char HUGE *) res + res->KeyTable.offs);
    Size += table->AnzKeySegs * sizeof(DWORD);
    for (i = 0 ; i < table->AnzKeySegs ; i++) {
      if (ktbl[i] != NULL) {
        otbl[i] = Size ;
        hmemcpy ((char HUGE *) res + otbl[i],ktbl[i],ktbl[i]->structSize);
        Size += ktbl[i]->structSize;
        Size = NextOffset(Size,sizeof(DWORD));
        }
      else
        otbl[i] = 0L;
      }
    }

  // Kopieren der RI - Info
  if (res->AnzRIDefs > 0) {
    res->RITable.offs = Size;
    DWORD FAR * otbl = (DWORD HUGE *) ((char HUGE *) res + res->RITable.offs);
    Size += table->AnzRIDefs * sizeof(DWORD);
    for (i = 0 ; i < table->AnzRIDefs ; i++) {
      if (rtbl[i] != NULL) {
        otbl[i] = Size ;
        hmemcpy ((char HUGE *) res + otbl[i],rtbl[i],rtbl[i]->structSize);
        Size += rtbl[i]->structSize;
        Size = NextOffset(Size,sizeof(DWORD));
        }
      else
        otbl[i] = 0L;
      }
    }

  *GesSize = Size;

  return res;
  }

// Tabelle freigeben
DLLExport void _export WINAPI FreeTableDef (TableDef FAR *res)
  {
  if ((!res->IsTemporaryTable()) &&
      (!res->IsInternTable()) &&
      (!res->IsGlobalTable())) {
    for (int i = 0 ; i < res->GetAnzVars() ; i++) {
      LPVARDEF v = res->GetVarDef(i);
      if (v->DLLDataOffs > 0)
        FreeGlobMem (v);
      }
    }
  if (res->IsTemporaryTable()) {
    if (res->d.DLLDef.ptr != NULL)
      FreeGlobMem (res->d.DLLDef.ptr);
    res->d.DLLDef.ptr = NULL;
    res->Clear ();
    }
  GLOBALHANDLE hGres = res->g.hGmem;
  GlobalUnlock (hGres);
  GlobalFree (hGres);
  }

// Resourcendatenbank abgrasen und die volle Tabelle daraus machen
//  Laden einer Tabellendefinition von der Datenbank
//////////////////////////////////////////////////////////////////
DLLExport WORD _export WINAPI TableDef::GetVarID (LPSTR VarName,WORD FAR *dt,BOOL FAR *found)
  {
  *found = FALSE ;
  for (int i = 0 ; i < GetAnzVars() ; i++) {
    LPVARDEF v = GetVarDef (i);
    if (lstrcmp (v->GetName (),VarName) == 0) {
      *found = TRUE ;
      *dt = v->mType ;
      return WORD(i);
      }
    }
  return 0;
  }

DLLExport void _export WINAPI TableDef::GetReqElem (LPREQELEM e,WORD VarID)
  {
  if ((IsInternTable()) || (IsTemporaryTable()))
    LPINTTABLE (GetDLLDef())->GetReqElem (e,VarID);
  else {
    e->TableNumber = 0;
    e->VarID = VarID;
    }
  }

WORD TableDef::GetVarInd(LPSTR Name)
  {
  for (WORD i = 0 ; i < WORD(GetAnzVars ()) ; i++) {
    LPVARDEF v = GetVarDef(i);
    if ((v != NULL) && (lstrcmp (Name,v->GetName()) == 0))
      return i;
    }
  return 0xFFFF;
  }

DLLExport BOOL _export WINAPI TableDef::HasForeignKeysFor (LPTABLEDEF td,WORD FAR *VarID,CHECKKEYALLOWED ckafnc,LPVOID data,LPSTR AccessName,LPSTR DelName)
  {
  WIN_ASSERT ((!IsInternTable()) && (!IsTemporaryTable()));
  char TableName[64];
  char aName[64];
  char dName[64];
  SegNamePtrs pt;
  for (int i = 0 ; i < GetAnzVars () ; i++) {
    if ((IsForeignKey (i,TableName,sizeof(TableName),aName,sizeof(aName),dName,sizeof(dName),&pt)) &&
           (lstrcmp (TableName,td->GetName()) == 0) &&
                ((ckafnc == NULL) || ((* ckafnc) (GetTableID(),WORD(i),data)))) {
      // Na wunderbar
      lstrcpy (AccessName,aName);
      if (DelName != NULL)
        lstrcpy (DelName,dName);
      VarID[0] = WORD(i);
      for (WORD j = 0 ; j < 3 ; j++) {
        if (pt.kn[j] != NULL)
          VarID[j+1] = GetVarInd(pt.kn[j]);
        else
          VarID[j+1] = 0xFFFF;
        }
      return TRUE ;
      }
    }
  return FALSE ;
  }

int TableDef::GetKeySegs (int KeyNum,WORD FAR *VarID)
  {
  int i = 0 ;
  VarID[i] = 0xFFFF;
  for (int j = 0 ; j < AnzKeySegs ; j++) {
    LPCLKEYDEF k = GetKeyDef(j);
    if (int(k->KeyNmbr) == KeyNum) {
      VarID[i++] = k->VarID;
      VarID[i] = 0xFFFF;
      }
    if (int(k->KeyNmbr) > KeyNum) break ;
    }
  return i;
  }

DLLExport BOOL _export WINAPI TableDef::GetPrimKeySegs (WORD FAR *VarID)
  {
  return (GetKeySegs (0,VarID) > 0) ;
  }
DLLExport BOOL _export WINAPI TableDef::IsViewAllowed (LPSTR AccessName)
  {
  return FALSE ;
  }

/*------------------------------------------------------------*/
/*  Klasse TableAdmin                                         */
/*------------------------------------------------------------*/
ContEntry FAR *ContEntry::Next (LPVOID Base,DWORD ContSize)
  {
  LPCONTENTRY n = LPCONTENTRY (LPSTR(this) + Len);
  DWORD offs = LPSTR(n) - LPSTR(Base);
  if (offs < ContSize) return n;
  else                 return NULL;
  }

DLLExport LPCONTENTRY _export WINAPI DataDictCont::First ()
  {
  return AnzTables ? &ent0 : NULL ;
  }

DLLExport LPCONTENTRY _export WINAPI DataDictCont::Next (LPCONTENTRY prev)
  {
  return prev->Next (this,ContSize);
  }

GLOBALHANDLE PushEntry (GLOBALHANDLE hGold,WORD TableID,WORD Version,WORD ParentID,WORD ParentVersion,LPSTR TableName)
  {
  WORD nwSize = sizeof(ContEntry) + lstrlen(TableName);
  GLOBALHANDLE hGres;
  LPDDCONT d;
  if (hGold) {
    LPDDCONT old = LPDDCONT (GlobalLock (hGold));
    DWORD oSize = old->ContSize;
    GlobalUnlock (hGold);
    hGres = GlobalReAlloc (hGold,oSize + nwSize,GMEM_MOVEABLE);
    d = LPDDCONT (GlobalLock (hGres));
    }
  else {
    hGres = GlobalAlloc (GMEM_MOVEABLE,sizeof(*d) - sizeof(ContEntry) + nwSize + 32);
    d = LPDDCONT (GlobalLock (hGres));
    d->ContSize  = sizeof(*d) - sizeof(ContEntry);
    d->AnzTables = 0;
    }
  d->AnzTables ++;
  LPCONTENTRY n = LPCONTENTRY(LPSTR(d) + d->ContSize);
  d->ContSize += nwSize;
  n->Len = nwSize;
  n->tRef.TableNr = TableID;
  n->tRef.Version = Version;
  n->ParentRef.TableNr = ParentID ;
  n->ParentRef.Version = ParentVersion ;
  lstrcpy (n->TableName,TableName);

  GlobalUnlock (hGres);
  return hGres;
  }

BOOL FindEntry (GLOBALHANDLE hGold,WORD TableID,WORD Version,LPSTR TableName)
  {
  BOOL res = FALSE ;
  if (hGold) {
    LPDDCONT old = LPDDCONT (GlobalLock (hGold));
    LPCONTENTRY n = LPCONTENTRY(old + 1);
    for (int i = 0 ; i < int (old->AnzTables) ; i ++) {
      if (n->tRef.TableNr == TableID) {
        if ((Version < DBMAXVERSION) && (n->tRef.Version < Version))
          n->tRef.Version = Version;
        res = TRUE ;
        }
      n = LPCONTENTRY(LPSTR(n) + n->Len);
      }
    GlobalUnlock (hGold);
    }
  return res;
  }

/*---< Erzeugen des Inhaltsverzeichnisses (Wobei nur die neueste Version aufgenommen wird) >-----*/
DLLExport void _export WINAPI CreateDataDictContent ()
  {
  // Abgrasen der Datenbank
  GLOBALHANDLE hGContMem = 0;
  DBList FAR *res = GetAllDataDict (0);
  for ( DBRecord FAR *r = res->GetFirst () ; r != NULL ; r = res->GetNext (r) ) {
    LPSTR TableName = LPSTR (r->Get(1));
    WORD TableID = *(WORD FAR *) r->Get(2);
    WORD Version = *(WORD FAR *) r->Get(4);
    WORD ParentID = *(WORD FAR *) r->Get(5);
    WORD ParentVersion = *(WORD FAR *) r->Get(6);
    if (!FindEntry (hGContMem,TableID,Version,TableName))
      hGContMem = PushEntry (hGContMem,TableID,Version,ParentID,ParentVersion,TableName);
    }
  WIN_ASSERT (hGContMem);

  // Schreiben des Inhaltsverzeichnisses
  LPDDCONT Content = LPDDCONT(GlobalLock (hGContMem));

  WriteDataDict (1,"CONT",0,0,0,0,hGContMem,Content->ContSize);
  delete res ;
  }

static TableAdmin tbAdmin;
DLLExport LPTABLEADMIN _export WINAPI GetTableAdmin ()
  {
  return &tbAdmin;
  }

hash FAR *IdHash,FAR *HoldBlobHash,FAR *NameHash;
void TableAdmin::LoadDataDictContent ()
  {
  printf("[tbdef] LoadDataDictContent entry hGContMem=%p Content=%p NameHash=%p\n",hGContMem,Content,NameHash);
  if (hGContMem) {
    GlobalUnlock (hGContMem);
    GlobalFree (hGContMem);
    hGContMem = NULL;
    Content = NULL;
    delete NameHash ;
    NameHash = new hash (237,STRKEY);
    }
  DWORD ContSize;
  hGContMem = ReadDataDict (1,0,0,&ContSize);
  printf("[tbdef] after ReadDataDict hGContMem=%p ContSize=%lu\n",hGContMem,ContSize);
  if (hGContMem == NULL) {
    Content = NULL;
    printf("[tbdef] LoadDataDictContent returning because no data\n");
    return;
    }

  Content = LPDDCONT (GlobalLock (hGContMem));
  printf("[tbdef] Content locked=%p\n",Content);
  if (Content != NULL) {
    for (LPCONTENTRY h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      NameHash->SetData (h->TableName,&h->tRef,sizeof(&h->tRef));
      }
    }
  }

int AnzUsedTables;
BOOL TableAdmin::CheckDataDictContent (LPSTR Name,WORD TableID,WORD Version,WORD ParentID,WORD ParentVersion)
  {
  BOOL found = FALSE ;
  BOOL versionChanged = FALSE ;
  WORD oldVersion;
  if (Content == NULL) LoadDataDictContent();
  if (Content != NULL) {
    for (LPCONTENTRY h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      if (lstrcmp (h->TableName,Name) == 0) {
        if ((Version < DBMAXVERSION) && (h->tRef.Version < Version)) {
          oldVersion = h->tRef.Version;
          h->tRef.Version = Version ;
          h->ParentRef.TableNr = ParentID ;
          h->ParentRef.Version = ParentVersion ;
          versionChanged = TRUE ;
          // Version auch in der Hashtabelle nachziehen
          TableRef FAR *t = (TableRef FAR *) NameHash->GetData(Name);
          t->Version = Version ; 
          }
        else
          oldVersion = h->tRef.Version ;
        found = TRUE ;
        break ;
        }
      }
    }
  if (!found) {
    if (hGContMem)
      GlobalUnlock (hGContMem);
    hGContMem = PushEntry (hGContMem,TableID,Version,ParentID,ParentVersion,Name);
    Content = LPDDCONT(GlobalLock (hGContMem));
    WriteDataDict (1,"CONT",0,0,0,0,hGContMem,Content->ContSize);
    TableRef tRef;
    tRef.Version = Version ;
    tRef.TableNr = TableID ;
    NameHash->SetData (Name,&tRef,sizeof(&tRef));
    }
  else {
    if (versionChanged) {
      WriteDataDict (1,"CONT",0,0,0,0,hGContMem,Content->ContSize);
      }
    // Die Definition muss neu geladen werden...
    TableNode FAR *prev = NULL ;
    for ( TableNode FAR *n = TableList ; n != NULL ; n = n->Next) {
      if (lstrcmp (n->def->GetName(),Name) == 0) {
        if (n->Count == 0) {
          IdHash->DelData(MAKELONG(n->tRef.TableNr,oldVersion));
          AnzUsedTables -- ;
          if (prev != NULL) prev->Next = n->Next ;
          else              TableList = n->Next;
          FreeTableDef (n->def);
          FreeGlobMem (n);
          }
        break ;
        }
      prev = n;
      }
    }
  return found;
  }


int TableAdmin::GetAnzTables ()
  {
  int Cnt = 0;
  if (Content != NULL)
    for (LPCONTENTRY h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      if (h->tRef.TableNr < GLOBALTBIDMIN) Cnt ++ ;
      }

  return Cnt;
  }


BOOL TableAdmin::DelTableDef (LPSTR Name)
  {
  BOOL found = FALSE ;
  if (Content == NULL) LoadDataDictContent();
  LPCONTENTRY h = NULL;
  if (Content != NULL) {
    for (h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      if (lstrcmp (h->TableName,Name) == 0) {
        found = TRUE ;
        break ;
        }
      }
    }
  BOOL referenced = FALSE ;
  if (found) {
    for ( TableNode FAR *n = TableList ; n != NULL ; n = n->Next) {
      if ((n->tRef.TableNr == h->tRef.TableNr) && (n->Count != 0)) {
        referenced = TRUE ;
        break ;
        }
      }
    }
  if ((found) && (!referenced)) {
    // Aus der Datenbank loeschen
    DelDataDict (0,h->tRef.TableNr,h->tRef.Version);
    if (hGContMem) {
      GlobalUnlock (hGContMem);
      GlobalFree (hGContMem);
      }
    CreateDataDictContent ();
    LoadDataDictContent();
    }
  return !referenced;
  }

extern void InitializeRecAdmin ();
extern void ExitRecAdmin ();
DLLExport void _export WINAPI TableAdmin::Initialize (BOOL doTest)
  {
  printf("[tbdef] Initialize start\n");
  MaxTables = GetPrivateProfileInt ("Tables","AnzTableDefs",500,GetIniName());
  IdHash = new hash (111,LONGKEY);
  HoldBlobHash = new hash (47,LONGKEY);
  NameHash = new hash (247,STRKEY);
  AnzUsedTables = 0 ;
  printf("[tbdef] before DefineResourceDBs\n");
  DefineResourceDBs();
  printf("[tbdef] before LoadDataDictContent\n");
  LoadDataDictContent ();
  printf("[tbdef] after LoadDataDictContent hGContMem=%p Content=%p\n",hGContMem,Content);
  InitializeRecAdmin ();
  printf("[tbdef] before LoadTableIdents\n");
  LoadTableIdents (doTest);
  printf("[tbdef] Initialize ok\n");
  }

// Freigeben der Tabellen, wenn Counter >= 0 dann Error
extern void ShowStatistics ();
DLLExport void _export WINAPI RemoveMDIHandleList ();
extern void DelResHash ();
extern void ResetCmdFifo ();
hash FAR *Id2hash,FAR *Id1hash;
WORD GetTableIDFromID (DWORD Id)
  {
  if (Id2hash != NULL) {
    WORD FAR *res = (WORD FAR *) Id2hash->GetData(Id);
    if (res != NULL) return *res ;
    else             return 0xFFFF ;
    }
  else             return 0xFFFF ;
  }

DWORD GetIDFromTableID (WORD Id)
  {
  if (Id2hash != NULL) {
    DWORD FAR *res = (DWORD FAR *) Id1hash->GetDataW(Id);
    if (res != NULL) return *res ;
    else             return 0xFFFFFFFF ;
    }
  else             return 0xFFFFFFFF ;
  }

void SetIds (WORD Id2,DWORD Id4)
  {
  if (Id2hash == NULL) {
    Id2hash = new hash (57,LONGKEY);
    Id1hash = new hash (57,WORDKEY);
    }
  Id2hash->SetData (Id4,&Id2,sizeof(WORD));
  Id1hash->SetDataW (Id2,&Id4,sizeof(DWORD));
  }

void DelId (WORD Id2)
  {
  DWORD Id4 = GetIDFromTableID (Id2);
  if ((Id4 != 0xFFFFFFFF) && (Id2hash != NULL)) {
    Id2hash->DelData (Id4);
    Id1hash->DelDataW (Id2);
    }
  }

DLLExport void _export WINAPI TableAdmin::OnExit ()
  {
  for ( ; TableList != NULL ; ) {
//    WIN_ASSERT_TEXT (TableList->Count == 0,TableList->def->GetName());
    FreeTableDef (TableList->def);
    TableNode FAR *n = TableList->Next;
    FreeGlobMem (TableList);
    TableList = n;
    }
  if (hGContMem) {
    GlobalUnlock (hGContMem);
    GlobalFree (hGContMem);
    hGContMem = NULL;
    }
  Content = NULL;
  delete IdHash ;
  IdHash = NULL;
  delete NameHash ;
  NameHash = NULL;
  AnzUsedTables = 0 ;
  RemoveMDIHandleList();
  ExitRecAdmin ();
  ShowStatistics ();
  delete HoldBlobHash ;
  HoldBlobHash = NULL;
  ResetCmdFifo ();
  DelResHash ();
  if (Id2hash != NULL) {
    delete Id2hash;
    delete Id1hash;
    }
  Id2hash = Id1hash = NULL;
  if (PropertyHash != NULL)
    delete PropertyHash;
  PropertyHash = NULL;
  }

DLLExport void _export WINAPI TableAdmin::ReInitialize ()
  {
  OnExit ();
  Initialize ();
  }

TableNode FAR *TableAdmin::Find (WORD TableId,WORD Version)
  {
  TableNode FAR * FAR *lptn = (TableNode FAR * FAR *) IdHash->GetData (MAKELONG(TableId,Version));
  if (lptn != NULL) return *lptn;
  else              return NULL ;
#ifdef UEBERLEGT
  for (TableNode FAR *res = TableList ; res != NULL ; res = res->Next) {
    if (res->TableId == TableId) break ;
    }
  return res;
#endif
  }

WORD TableAdmin::GetTableCount ()
  {
#ifdef UEBERLEGT
  WORD count = 0;
  for (TableNode FAR *h = TableList ; h != NULL ; h = h->Next)
    count ++ ;
  return count;
#endif
  return AnzUsedTables ;
  }

#define OVERLOAD    (MaxTables / 5)
void TableAdmin::CleanUnused ()
  {
  if (GetTableCount () <= MaxTables + OVERLOAD) return;

  LPTABLENODE FAR *prev = &TableList;
  for (TableNode FAR *h = TableList ; h != NULL ; ) {
    if (h->Count == 0) {
      IdHash->DelData(MAKELONG(h->tRef.TableNr,h->tRef.Version));
      AnzUsedTables -- ;

      *prev = h->Next;
      FreeTableDef (h->def);
      FreeGlobMem (h);
      h = *prev;

      if (GetTableCount () <= MaxTables) break;
      }
    else {
      prev = &h->Next;
      h = h->Next ;
      }
    }
  }

void TableAdmin::CleanTableNode (WORD TableID,WORD Version)
  {
  LPTABLENODE FAR *prev = &TableList;
  for (TableNode FAR *h = TableList ; h != NULL ; ) {
    if ((h->tRef.TableNr == TableID) && (h->tRef.Version == Version)) {
      IdHash->DelData(MAKELONG(h->tRef.TableNr,h->tRef.Version));
      AnzUsedTables -- ;

      *prev = h->Next;
      FreeTableDef (h->def);
      FreeGlobMem (h);
      h = *prev;
      break;
      }
    else {
      prev = &h->Next;
      h = h->Next ;
      }
    }
  }

DLLExport void _export WINAPI GetDLLForTable (LPSTR DLLName,LPSTR TableName)
  {
  char Name[64];
  GetPrivateProfileString ("Tables",TableName,"",
                            Name,sizeof(Name),
                            GetIniName());
  if (*Name == '\0') {
    // Keinen spezialeintrag gefunden -> Im Default nachsehen
    GetPrivateProfileString ("DataBase","DefaultDLL","MV1",
                            Name,sizeof(Name),
                            GetIniName());
    }
  lstrcpy (DLLName,Name);
  }

void TableAdmin::GetDLLFor (LPSTR DLLName,WORD TableID)
  {
  // Ermitteln des Names der Tabelle aus dem Inhaltsverzeichnis
  LPCONTENTRY h = NULL;
  if (Content != NULL) {
    for ( h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      if (h->tRef.TableNr == TableID) {
        if ((h->tRef.TableNr >= GLOBALTBIDMIN) && (h->tRef.TableNr <= TEMPORARYTBIDMAX)) {
          lstrcpy (DLLName,GetInternDLLName());
          }
        else {
          GetDLLForTable (DLLName,h->TableName);
          }
        break ;
        }
      }
    }
  WIN_ASSERT (h != NULL);
  }

DLLExport LPTABLEDEF _export WINAPI TableAdmin::GetTableDef (WORD TableID,WORD Version)
  {
  LPTABLENODE h = Find (TableID,Version);
  if (h != NULL) {
    h->Count ++ ;
    }
  else {
    BOOL found = FALSE;
    BOOL oldVersion = FALSE;
    LPCONTENTRY x = NULL;
    if (Content != NULL) {
      for ( x = Content->First() ; x != NULL ; x = Content->Next(x)) {
        if (x->tRef.TableNr == TableID) {
          if (x->tRef.Version == Version) found = TRUE ;
          else                            oldVersion = TRUE ;
          }
        }
      }

    if ((!found) && (!oldVersion)) return NULL;

    // Erzeugen eines neuen Eintrages
    char DLLName[64];
    GetDLLFor (DLLName,TableID);

    for (LPTABLENODE FAR *prev = &TableList ; *prev != NULL ; prev = &((*prev)->Next)) ;
    *prev = h = LPTABLENODE (GetGlobMem (sizeof(*h)));
    h->Next = NULL;
    h->tRef.TableNr = TableID;
    h->tRef.Version = Version;
    h->Count = 1;

    IdHash->SetData(MAKELONG(h->tRef.TableNr,h->tRef.Version),&h,sizeof(h));
    AnzUsedTables ++ ;

    DWORD DataSize;
    GLOBALHANDLE hGmem = ReadDataDict (0,TableID,Version,&DataSize);
    char teststr[64];
    wsprintf (teststr,"No data for %d / %d",TableID,Version);
    WIN_ASSERT_TEXT (hGmem,teststr);
    h->def = LPTABLEDEF (GlobalLock (hGmem));
    h->def->SetDLLHandle (GetDLLAdmin()->LoadDLL(DLLName));
    GlobalUnlock (hGmem);
    h->def = InitializeTable (hGmem);
    }
  return h->def;
  }

DLLExport void _export WINAPI TableAdmin::FreeTable (WORD TableID,WORD Version)
  {
  LPTABLENODE h = Find (TableID,Version);
  if (h != NULL) {
    h->Count -- ;
    if (h->Count == 0) {
      if (h->def->IsTemporaryTable()) {
        LPTABLENODE FAR *prev = &TableList;
        for (TableNode FAR *x = TableList ; x != NULL ; ) {
          if (x == h) {
            IdHash->DelData(MAKELONG(h->tRef.TableNr,h->tRef.Version));
            AnzUsedTables -- ;

            *prev = h->Next;
            FreeTableDef (h->def);
            FreeGlobMem (h);
            h = *prev;
            break ;
            }
          else {
            prev = &x->Next;
            x = x->Next ;
            }
          }
        }
      else
        CleanUnused ();
      }
    }
  }

extern HINSTANCE hLibInst;
DLLExport LPSTR _export WINAPI GetMTypeName(WORD Type)
  {
  static char res[64];
  int cbloaded = LoadString (hLibInst,10000+Type,res,sizeof(res));
  if (cbloaded == 0)
    wsprintf (res,"???");
  return res;
  }

DLLExport LPSTR _export WINAPI GetRealMTypeName(WORD Type)
  {
  static char res[64];
  int cbloaded = LoadString (hLibInst,11000+Type,res,sizeof(res));
  if (cbloaded == 0)
    wsprintf (res,"???");
  return res;
  }

DLLExport LPTABLEDEF _export WINAPI TableAdmin::GetTableDefByNr (int Nr)
  {
  int i = 0;
  if (Content != NULL) {
    for ( LPCONTENTRY h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      if (i++ == Nr)
        // Laden der vollen Definition
        return GetTableDef (h->tRef.TableNr,h->tRef.Version);
      }
    }
  return NULL;
  }

DLLExport WORD _export WINAPI GetVersionFrom (LPSTR Name)
  {
  WORD res = 0xFFFF ;
  for ( LPSTR h = Name ; ((*h) && (*h != '.')) ; h++) ;
  if ((*h == '.') && (h[1] >= '0') && (h[1] <= '9')) {
    *h++ = '\0' ;
    for (res = 0 ; *h ; h++)
      res = res * 10 + *h - '0' ;
    }
  return res;
  }

DLLExport void _export WINAPI GetPrefix (LPSTR r,LPSTR p)
  {
  *r = '@' ;
  LPSTR pStart = p;
  for (LPSTR h = p ; *h ; h++) if ((*h == '\\') || (*h == ':')) pStart = h + 1 ;
  for (LPSTR x = r + 1 ; ; ) {
    if (*pStart == '.') { *x = '\0' ; break ; }
    else if (*pStart)   { *x++ = *pStart++ ; }
    else                { break ; }
    }
  }

extern WORD CheckResName (LPSTR Name,BOOL FAR *found,WORD FAR *Version);
struct ActVersion {
  WORD Version;
  char Name[64];
  ActVersion FAR *Next;
  };
struct ActVersion FAR *avList;
DLLExport void _export WINAPI SetActVersionFor (LPSTR Name,WORD Version)
  {
  for ( ActVersion FAR *h = avList ; h != NULL ; h = h->Next ) {
    if (lstrcmp (h->Name,Name) == 0) {
      h->Version = Version;
      return ;
      }
    }
  ActVersion FAR *n = (ActVersion FAR *) GetGlobMem (sizeof(*n));
  lstrcpy (n->Name,Name);
  n->Version = Version ;
  n->Next = avList ;
  avList = n ;
  }

DLLExport void _export WINAPI DelActVersionList ()
  {
  for ( ; avList != NULL ; ) {
    ActVersion FAR *n = avList->Next ;
    FreeGlobMem (avList);
    avList = n ;
    }
  }

BOOL GetActVersion (LPSTR Name,WORD FAR *Version)
  {
  for ( ActVersion FAR *h = avList ; h != NULL ; h = h->Next ) {
    if (lstrcmp (h->Name,Name) == 0) {
      *Version = h->Version;
      return TRUE ;
      }
    }
  return FALSE ;
  }

DLLExport WORD _export WINAPI TableAdmin::GetTableID (LPSTR ScriptPrefix,LPSTR TableName,BOOL FAR *found,WORD FAR *Version)
  {
  *found = FALSE ;
  // Ermitteln des Names der Tabelle aus dem Inhaltsverzeichnis
  char t1[256],t2[256];
  lstrcpy (t1,TableName);
  WORD rVersion = GetVersionFrom (t1);

#ifdef UEBERLEGT
  if (ScriptPrefix != NULL) {
    GetPrefix (t2,ScriptPrefix);
    lstrcat (t2,t1);
    }
  else
    *t2 = '\0' ;

  if (Content != NULL) {
    for ( LPCONTENTRY h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      if ((lstrcmp (t1,h->TableName) == 0) || 
          (lstrcmp (t2,h->TableName) == 0)) {
        *found = TRUE ;
        if (rVersion != 0xFFFF)
          *Version = rVersion;
        else
          *Version = h->tRef.Version;
        return h->tRef.TableNr;
        }
      }
    }
  // Wenn dies nicht funktioniert hat, dann
  // ermitteln des Names der Tabelle aus den bereits geladenen Tabellen
  // (ev. noetig fuer Resourcetabellen....)
  for (TableNode FAR *n = TableList ; n != NULL ; n = n->Next) {
    if (((lstrcmp (n->def->GetName(),t1) == 0) ||
         ((*t2) && (lstrcmp (n->def->GetName(),t2) == 0))) &&
          ((rVersion == 0xFFFF) || (rVersion == n->tRef.Version))) {
      *found = TRUE ;
      *Version = n->tRef.Version;
      return n->tRef.TableNr;
      }
    }
#else
  // Mit dem Normalen Namen probieren
  TableRef FAR *tref = (TableRef FAR *) NameHash->GetData (t1);
  if (tref != NULL) {
    if (rVersion != 0xFFFF)
      *Version = rVersion ;
    else if (!GetActVersion (t1,Version))
      *Version = tref->Version ;
    *found = TRUE ;
    return tref->TableNr ;
    }

  // Mit dem privaten Namen probieren
  if (ScriptPrefix != NULL) {
    GetPrefix (t2,ScriptPrefix);
    lstrcat (t2,t1);
    }
  else
    *t2 = '\0' ;

  if (*t2) {
    tref = (TableRef FAR *) NameHash->GetData (t1);
    if (tref != NULL) {
      *Version = tref->Version ;
      *found = TRUE ;
      return tref->TableNr ;
      }
    }

  return CheckResName (t1,found,Version);

#endif
  return 0;
  }

DLLExport WORD _export WINAPI CalcTableID (LPSTR TableName)
  {
  BOOL found;
  WORD Version;
  return GetTableAdmin () -> GetTableID (NULL,TableName,&found,&Version);
  }

// Erstellen der Tabellenliste
DLLExport TableEntry FAR *_export WINAPI TableAdmin::CreateTableList ()
  {
  TableEntry FAR *aList = NULL;
  TableEntry FAR *eList = NULL;
  if (Content != NULL) {
    for ( LPCONTENTRY h = Content->First() ; h != NULL ; h = Content->Next(h)) {
      LPTABLEDEF t = GetTableDef (h->tRef.TableNr,h->tRef.Version);
      if (!t->IsInternTable()) {
        TableEntry FAR *n = (TableEntry FAR *) GetGlobMem (sizeof(*n));
        if (eList != NULL) eList->Next = n;
        else               aList = n;
        eList = n;
        n->td = t;
        }
      else 
        FreeTable(h->tRef.TableNr,h->tRef.Version);
      }
    }
  return aList;
  }

// Tabellenliste wieder freigeben
DLLExport void _export WINAPI TableAdmin::DestroyTableList (TableEntry FAR *aList)
  {
  for ( ; aList != NULL ; ) {
    TableEntry FAR *n = aList->Next;
    FreeTable(aList->td->GetTableID(),aList->td->GetVersion());
    FreeGlobMem (aList);
    aList = n;
    }
  }


DLLExport LPTABLEDEF _export WINAPI TableAdmin::GetFirstTableDef (LPVOID FAR *h)
  {
  if (Content != NULL) {
    for ( LPCONTENTRY e = Content->First() ; e != NULL ; e = Content->Next(e)) {
      LPTABLEDEF res = GetTableDef (e->tRef.TableNr,e->tRef.Version);
      if (!res->IsInternTable()) {
        *h = e;
        return res;
        }
      else
        FreeTable (e->tRef.TableNr,e->tRef.Version);
      }
    }
  return NULL;
  }

DLLExport LPTABLEDEF _export WINAPI TableAdmin::GetNextTableDef (LPVOID FAR *h)
  {
  LPCONTENTRY e = LPCONTENTRY (*h);
  FreeTable (e->tRef.TableNr,e->tRef.Version);
  for ( e = Content->Next(e) ; e != NULL ; e = Content->Next(e) ) {
    LPTABLEDEF res = GetTableDef (e->tRef.TableNr,e->tRef.Version);
    if (!res->IsInternTable()) {
      *h = e;
      return res;
      }
    else
      FreeTable (e->tRef.TableNr,e->tRef.Version);
    }
  return NULL;
  }

inline LPSTR SkipPath(LPSTR FileName)
  {
  for (LPSTR h = FileName ; *h ; h ++) {
    if ((*h == '\\') || (*h == ':')) FileName = h + 1;
    }
  return FileName;
  }

DLLExport LPTABLEDEF _export WINAPI GetEmptyTable (LPSTR TableName,LPSTR FileName)
  {
  LPTABLEDEF res;
  GLOBALHANDLE hGres = GlobalAlloc (GHND,sizeof(*res) + 32);
  res = LPTABLEDEF (GlobalLock (hGres));
  res->g.hGmem = hGres;
  res->VarTable.ptr = LPSTR(res) + sizeof(*res);
  res->SetName     (TableName);
  res->SetFileName (SkipPath(FileName));
  // Ermitteln der TableID
  return res;
  }

DLLExport void _export WINAPI TableDef::InitializeTableID (WORD idmin,WORD idmax,WORD Version)
  {
  WORD TableNr = ReadTableID(0,GetName(),idmin,idmax);
  SetTableID (TableNr,Version);
  }

DLLExport BOOL _export WINAPI TableDef::HoldBlobs ()
  {
  BOOL FAR *h = (BOOL FAR *) HoldBlobHash->GetData (MAKELONG(tRef.TableNr,tRef.Version));
  if (h != NULL) return *h;
  BOOL res = FALSE;
  for (int i = 0 ; i < AnzVars ; i++) {
    if (GetVarDef(i)->mType == VAR_BLOB) {
      res = TRUE ;
      break ;
      }
    }
  HoldBlobHash->SetData (MAKELONG(tRef.TableNr,tRef.Version),&res,sizeof(res));
  return res ;
  }

WORD TableAdmin::GetTemporaryID (WORD IdMin)
  {
  for (WORD res = IdMin ; ; res ++) {
    BOOL found = FALSE ;
    TableNode FAR * FAR *lptn = (TableNode FAR * FAR *) IdHash->GetData (MAKELONG(res,0));
    if (lptn != NULL) found = TRUE ;
#ifdef UEBERLEGT
    for (TableNode FAR *h = TableList ; ((h != NULL) && (!found)) ; h = h->Next) {
      if (h->def->GetTableID() == res) found = TRUE ;
      }
#endif
    if (!found)
      return res;
    }
  }

WORD TableAdmin::GetTemporaryID ()
  {
  return GetTemporaryID(TEMPORARYTBIDMIN);
  }

void DivideName (LPSTR TableName,LPSTR VarName,LPSTR fullName)
  {
  LPSTR d = TableName;
  BOOL pointFound = FALSE ;
  for (LPSTR h = fullName ; *h ; h++) {
    if (*h == '.') {
      d = VarName;
      pointFound = TRUE ;
      }
    else
      *d++ = *h ;
    }
  *d++ = '\0';
  if (!pointFound)
    lstrcpy (VarName,TableName) , *TableName = '\0';
  }

LPVARDEF CheckVarName (int AnzVars,LPSTR FAR *VarNames,LPTABLEDEF rTable,int vNum,WORD FAR *VarID)
  {
  if (AnzVars == 0) {
    *VarID = WORD (vNum);
    return rTable->GetVarDef(vNum);
    }
  char VarName[64],TableName[64];
  DivideName (TableName,VarName,VarNames[vNum]);
  if ((*TableName) && (lstrcmp (rTable->GetName(),TableName) != 0)) return NULL;
  for (int i = 0 ; i < rTable->GetAnzVars(); i++) {
    LPVARDEF v = rTable->GetVarDef(i);
    if (lstrcmp(v->GetName(),VarName) == 0) {
      *VarID = i;
      return v;
      }
    }
  return NULL;
  }

DLLExport LPTABLEDEF _export WINAPI TableAdmin::GetTemporaryTable (int AnzVars,LPSTR FAR *VarNames,int AnzTables,LPSTR FAR *TableNames)
  {
  if (AnzTables != 1) return NULL;
  BOOL found ;
  WORD Version;
  WORD TId = GetTableID (NULL,TableNames[0],&found,&Version);
  if (!found) return 0;
  LPTABLEDEF rTable = GetTableDef (TId,Version);
  int nAnzVars;
  if (AnzVars == 0) nAnzVars = rTable->GetAnzVars() ;
  else              nAnzVars = AnzVars ;
  LPTABLEDEF res = GetEmptyTable ("","");
  res->tRef.TableNr = GetTemporaryID ();
  res->tRef.Version = 0;

  res->d.DLLDef.ptr = GetGlobMem (sizeof(InternTable) + sizeof(partTable) + 
                                  (nAnzVars - 1) * sizeof(WORD)
                                 );
  LPINTTABLE it = LPINTTABLE (res->d.DLLDef.ptr);
  it->AnzTables = AnzTables ;
  it->pTable[0].Offs = sizeof(InternTable);
  LPPTABLE p = it->GetTableByNum(0);
  p->tRef.TableNr = rTable->GetTableID();
  p->tRef.Version = rTable->GetVersion();
  p->AnzVars = nAnzVars;
  for (int i = 0 ; i < nAnzVars ; i++) {
    WORD VarID;
    LPVARDEF v = CheckVarName (AnzVars,VarNames,rTable,i,&VarID);
    if (v == NULL) {
      FreeTable (TId,Version);
      if (res->d.DLLDef.ptr != NULL)
        FreeGlobMem (res->d.DLLDef.ptr);
      res->d.DLLDef.ptr = NULL;
      res->Clear ();
      return NULL;
      }
    p->VarID[i] = VarID ;
    res = res->AddVar (v);
    }

  // In die Liste der verwalteten Tabellen einhaengen
  for (LPTABLENODE FAR *prev = &TableList ; *prev != NULL ; prev = &((*prev)->Next)) ;
  LPTABLENODE h = LPTABLENODE (GetGlobMem (sizeof(*h)));
  *prev = h;
  h->Next = NULL;
  h->tRef.TableNr = res->GetTableID();
  h->tRef.Version = res->GetVersion();
  h->Count = 1;
  h->def = res ;
  h->def->SetDLLHandle (GetDLLAdmin()->LoadDLL(GetInternDLLName()));

  IdHash->SetData (MAKELONG(h->tRef.TableNr,h->tRef.Version),&h,sizeof(h));
  AnzUsedTables ++ ;

  FreeTable (TId,Version);
  return res;
  }

void TableAdmin::AddTableDef (LPTABLEDEF res,DLLHANDLE hDLL)
  {
  for (LPTABLENODE FAR *prev = &TableList ; *prev != NULL ; prev = &((*prev)->Next)) ;
  LPTABLENODE h = LPTABLENODE (GetGlobMem (sizeof(*h)));
  *prev = h;
  h->Next = NULL;
  h->tRef.TableNr = res->GetTableID();
  h->tRef.Version = res->GetVersion();
  h->Count = 1;
  h->def = res ;
  h->def->SetDLLHandle (hDLL);

  IdHash->SetData (MAKELONG(h->tRef.TableNr,h->tRef.Version),&h,sizeof(h));
  AnzUsedTables ++ ;
  }

void TableAdmin::FreeTemporaryTable (WORD TableID)
  {
  LPTABLEDEF td = GetTableDef (TableID,0);
  if (td != NULL) {
    if (td->d.DLLDef.ptr != NULL)
      FreeGlobMem (td->d.DLLDef.ptr);
    td->d.DLLDef.ptr = NULL;
    CleanTableNode (TableID,0);
    }
  }


BOOL doAbortTest = FALSE;
DLLExport BOOL FAR PASCAL _export TestTableDlgProc (HWND hDlg, UINT message, 
                                                    WPARAM wP, LPARAM lP)
  {
  BOOL res = FALSE;
  switch (message) {
    //-----------------------------------------------------------------
    case WM_INITDIALOG:
      res = TRUE ;

    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDCANCEL:
          doAbortTest = TRUE ;
          return TRUE ;
        }

    default :
      res = FALSE ;
    }  // end switch()

  return res ;
  }

//---- Testen aller Tabellen ------
DLLExport void _export WINAPI DBTest (BOOL doCreate)
  {
//#ifndef WIN32
  //-------------------------------------------------------------------
  // Erzeugen eines Fensters, welches die getesteten Tabellen und den
  // Fortschritt anzeigt
  //-------------------------------------------------------------------
  int AnzTables = 0;
  int CurTable = 0;
  char textstr[8];

  HWND outDlg = CreateDialog (hLibInst,"DIALOG_2",GetActiveWindow(),DLGPROC(TestTableDlgProc));

  if (outDlg) {
    AnzTables = GetTableAdmin()->GetAnzTables();
    }
//#endif

  BOOL found;
  WORD Version,TableID;
  // zunaechst einmal die Resource-Tabellen testen
  for (int i = 0; i < 5; i++) {
    LPSTR h;
    if (i == 0) h = "DataDict";
    if (i == 1) h = "ResDB";
    if (i == 2) h = "ScriptDB";
    if (i == 3) h = "DBVersion";
    if (i == 4) h = "UpdateStep";
    TableID = GetTableAdmin()->GetTableID(NULL,h,&found,&Version);
    if (found) {
      LPTABLEDEF t = GetTableAdmin()->GetTableDef(TableID,Version);
      LPDBREQUEST req = InitializeRequest ("",1,(doCreate) ? DBCALLTYPE_CREATE : DBCALLTYPE_TEST,NULL);
      req->AddTableDef (t);
      LPVOID hstmt = NULL;
      int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,-1,req,&hstmt,NULL);
      GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,-1,req,&hstmt,NULL);
      FreeRequest (req);
      GetTableAdmin()->FreeTable(TableID,Version);
      }
    }

  for (LPCONTENTRY c = GetTableAdmin()->Content->First() ; (c != NULL) && (!doAbortTest); c = GetTableAdmin()->Content->Next(c)) {
    if (c->tRef.TableNr < GLOBALTBIDMIN) {
      LPTABLEDEF t = GetTableAdmin()->GetTableDef (c->tRef.TableNr,c->tRef.Version);
      LPDBREQUEST req = InitializeRequest ("",1,(doCreate) ? DBCALLTYPE_CREATE : DBCALLTYPE_TEST,NULL);
      req->AddTableDef (t);
      LPVOID hstmt = NULL;
      int res = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,-1,req,&hstmt,NULL);
      GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,-1,req,&hstmt,NULL);
      FreeRequest (req);

      if (res == DBCALL_SUCCESS)
        SetDBVersion (t->GetName(),t->GetVersion());

//#ifndef WIN32
      //-------------------------------------------------------------------
      // Tabellennamen und Fortschritt schreiben, Nachrichten durchlassen
      //-------------------------------------------------------------------
      if (outDlg != NULL) {
        CurTable++;
        wsprintf (textstr, "%u %%", UINT((100L * LONG(CurTable)) / LONG(AnzTables)));
        SetDlgItemText (outDlg, 102, textstr);

        SetDlgItemText (outDlg,101,t->GetName());

        MSG m;
        while (PeekMessage(&m, 0, 0, 0, PM_REMOVE)) {
          TranslateMessage (&m);
          DispatchMessage (&m);
          }
        }
//#endif
      }

    GetTableAdmin()->FreeTable (c->tRef.TableNr,c->tRef.Version);
    }

//#ifndef WIN32
  if (outDlg != NULL)
    DestroyWindow (outDlg);
//#endif
  }

//--------- Konvertieren einer Datenbank --------
BOOL doAbortConvert;
DLLExport BOOL _export WINAPI ConvertDlgProc (HWND hDlg, UINT message, WPARAM wP,
                                                               LPARAM lP)
  {
  BOOL res = FALSE;
  switch (message) {
    //-----------------------------------------------------------------
    case WM_INITDIALOG:
      res = TRUE ;
    case WM_COMMAND :
      CRACKER_VARS
      CRACK_MESSAGEsc

      switch (CRACKER_wID) {
        case IDCANCEL:
          doAbortConvert = TRUE ;
          return TRUE ;
        }
    default :
      res = FALSE ;
    }  // end switch()

  return res ;
  }

/*--------------------------------------*/
/*  Konvertierung von Datenbanken       */
/*--------------------------------------*/
extern DLLExport LPSTR _export WINAPI makeIni (LPSTR name);
static BOOL doConvert (LPSTR Name)
  {
  static char defaultString[5] ;
  static BOOL defaultRead;
  char res[5];
  if (!defaultRead) {
    GetPrivateProfileString ("Tables","Default","y",
                             defaultString,sizeof(defaultString),
                             makeIni ("convert.ini")
                            );
    defaultRead = TRUE ;
    }
  GetPrivateProfileString ("Tables",Name,defaultString,
                          res,sizeof(res),
                          makeIni ("convert.ini")
                          );
  return (*res == 'y') ;
  }

class FAR msg {
  LPSTR ptr;
 public :
  msg()
    {
    ptr = "" ;
    }
  msg(LPSTR Text)
    {
    ptr = LPSTR(GetGlobMem (lstrlen(Text) + 1));
    lstrcpy (ptr,Text);
    }
  msg FAR &operator += (LPSTR Text)
    {
    LPSTR n;
    if (ptr != NULL) {
      n = LPSTR (GetGlobMem (lstrlen(ptr) + lstrlen(Text) + 1));
      lstrcpy (n,ptr);
      }
    else
      n = LPSTR (GetGlobMem (lstrlen(Text) + 1));
    lstrcat (n,Text);
    if (ptr != NULL)
      FreeGlobMem (ptr);
    ptr = n ;
    return *this ;
    }
  msg FAR &operator + (LPSTR Text)
    {
    *this += Text ;
    return *this ;
    }
  ~msg ()
    {
    if (ptr != NULL)
      FreeGlobMem (ptr);
    }
  friend void WriteMessage (msg FAR *m);
  };
void WriteMessage (msg FAR *m)
  {
  OFSTRUCT Of;
  static LPSTR fname = "convert.msg" ;
  HFILE f = OpenFile (fname,&Of,OF_EXIST | OF_SHARE_EXCLUSIVE);
  if (f == HFILE_ERROR) {
    f = OpenFile (fname,&Of,OF_CREATE | OF_SHARE_EXCLUSIVE);
    _lclose(f);
    }
  f = OpenFile (fname,&Of,OF_READWRITE | OF_SHARE_EXCLUSIVE);
  _llseek (f,0L,SEEK_END);
  _lwrite (f,m->ptr,lstrlen(m->ptr));
  _lclose (f);
  }

void GetWhereStmt (msg FAR &f,LPTABLEDEF t,LPDBRECORD rec)
  {
  BOOL first = TRUE ;
  for (int i = 0 ; i < t->GetAnzKeySegs () ; i++) {
    LPCLKEYDEF k = t->GetKeyDef(i);
    if (k->KeyNmbr == 0) {
      if (!first) f = f + " AND " ;
      LPVARDEF v = t->GetVarDef(k->VarID);
      f = f + v->GetName () + " = " ;
      if (v->mType == VAR_STR) f = f + "'" ;
      char buffer[512];
      rec->GetOutTxt (buffer,k->VarID);
      f = f + buffer ;
      if (v->mType == VAR_STR) f = f + "'" ;
      first = FALSE ;
      }
    }
  }

extern LPTABLEDEF DefineOneResourceDB(LPSTR Name,DLLHANDLE ResDLL,BOOL doAdmin);
static void ConvertOneTable(LPTABLEDEF t,DLLHANDLE toDLL,HWND outDlg,DLLHANDLE fromDLL)
  {
  if (toDLL == fromDLL) {
    GetDLLAdmin()->GetDLLEntry(toDLL)->DBAlter (t,t,NULL);
    return ;
    }
  char outTxt[64];
  MSG m;

  msg o ("KONVERTIERE TABELLE ");
  o = o + t->GetName () + "\r\n" ;
  WriteMessage (&o);
  // Erzeugen der Tabelledefinition fuer die Zieldatenbank
  WORD TableID = t->GetTableID();
  WORD Version = t->GetVersion();
  LPTABLEDEF t1;
  if ((TableID >= RESOURCEIDMIN) && (TableID <= RESOURCEIDMAX)) {
    t1 = DefineOneResourceDB(t->GetName(),toDLL,FALSE);
    }
  else {
    DWORD DataSize;
    GLOBALHANDLE hGmem = ReadDataDict (0,TableID,Version,&DataSize);
    char teststr[64];
    wsprintf (teststr,"No data for %d",TableID);
    WIN_ASSERT_TEXT (hGmem,teststr);
    t1 = LPTABLEDEF (GlobalLock (hGmem));
    t1->SetDLLHandle (toDLL);
    t1 = InitializeTable (hGmem);
    }
  DWORD RecNr = 0 ;
  DWORD FNr = 0 ;
  SetDlgItemText (outDlg,101,t->GetName());
  wsprintf (outTxt,"%ld",RecNr);
  SetDlgItemText (outDlg,102,outTxt);
  wsprintf (outTxt,"%ld",FNr);
  SetDlgItemText (outDlg,103,outTxt);

  // Dem System wieder etwas Verschnaufpause verschaffen
  //////////////////////////////////////////////////////
  while (PeekMessage(&m, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage (&m);
    DispatchMessage (&m);
    }

  // Erzeugen einer Liste, mit dem 
  static ParamBlock p;
  lmemset (&p,'\0',sizeof(p));
  DBList FAR *res = new DBList (t,0L,"",300,300,&p,FALSE);
  res->SetOrder ("");

  for ( LPDBRECORD rec = res->GetFirst (); ((rec != NULL) && (!doAbortConvert)) ; rec = res->GetNext (rec) ) {
    LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,0L);
    req->tRef.TableNr = TableID;
    req->tRef.Version = Version;
    GetTableAdmin()->GetTableDef (req->GetTableID(),req->GetVersion());   // To force the count right
    req->AddTableDef (t1);
    req->SetParam (1,&TableID,sizeof(TableID));
    req->AnzParam = 1;
    RecBuffer rb;
    lmemset (&rb,'\0',sizeof(rb));
    rb.AddLine (1,ADDLINEPOS_START);
    rb.act->rec[0] = rec ;
    LPVOID hstmt = NULL;
    int st = GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_GET,1,req,&hstmt,&rb);
    GetDLLAdmin()->GetDLLEntry(req->GetDLLHandle())->DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
    rb.Clear ();
    req->ClearParams();
    req->FreeTableDefs();
    FreeRequest (req);
    if (st == DBCALL_SUCCESS) {
      RecNr ++ ;
      }
    else {
      FNr ++ ;
      msg f ("FEHLER BEIM INSERT:\r\n") ;
      f = f + "  Read Record with: \r\n  <" ;
      GetWhereStmt (f,t,rec);
      f = f + ">\r\n" ;
      WriteMessage (&f);
      }
    res->ThrowAtHead (rec);

    if ((RecNr + FNr) % 10L == 0L) {
      wsprintf (outTxt,"%ld",RecNr);
      SetDlgItemText (outDlg,102,outTxt);
      wsprintf (outTxt,"%ld",FNr);
      SetDlgItemText (outDlg,103,outTxt);
      }

    // Dem System wieder etwas Verschnaufpause verschaffen
    //////////////////////////////////////////////////////
    while (PeekMessage(&m, 0, 0, 0, PM_REMOVE)) {
      TranslateMessage (&m);
      DispatchMessage (&m);
      }
    }
  // Der DLL Mitteilen, dass es sich um den letzten Insert gehandelt hat
  LPDBREQUEST req_end = InitializeRequest ("",-1,0,0L);
  req_end->AddTableDef (t1);
  int st = GetDLLAdmin()->GetDLLEntry(req_end->GetDLLHandle())->DBCall (DBOP_ENDOFCONVERSION,1,req_end,NULL,NULL);
  req_end->FreeTableDefs();
  FreeRequest (req_end);

  delete res ;

  FreeTableDef (t1);    // Zieltabelle wieder freigeben
  msg e (t->GetName ()) ;
  wsprintf (outTxt,"%ld",RecNr);
  e = e + " fertig\r\n  Konvertiert: " + outTxt + "\r\n" ;
  SetDlgItemText (outDlg,102,outTxt);
  wsprintf (outTxt,"%ld",FNr);
  if (FNr) {
    e = e + "  Fehler: " + outTxt + "\r\n" ;
    }
  WriteMessage (&e);
  SetDlgItemText (outDlg,103,outTxt);
  while (PeekMessage(&m, 0, 0, 0, PM_REMOVE)) {
    TranslateMessage (&m);
    DispatchMessage (&m);
    }
  }

LPSTR NextTableName (LPSTR h)
  {
  for ( ; *h ; h ++ ) {
    if (*h == ',') {
      *h = '\0' ;
      return h + 1 ;
      }
    }
  return h ;
  }

DLLExport void _export WINAPI DBConvert (LPSTR ConvertTo)
  {
  DLLHANDLE toDLL = GetDLLAdmin()->LoadDLL(ConvertTo);
  DLLHANDLE fromDLL = GetTransactionDLL();

  LPVOID h;
  HWND outDlg = CreateDialog (hLibInst,"DIALOG_1",GetActiveWindow(),DLGPROC(ConvertDlgProc));
  char ConvertExplicit[256];
  GetPrivateProfileString ("Tables","ConvertExplicit","",
                           ConvertExplicit,sizeof(ConvertExplicit),
                           makeIni ("convert.ini")
                          );
  if (*ConvertExplicit != '\0') {
    BOOL found;
    LPSTR h ;
    for ( LPSTR next = NextTableName (h = ConvertExplicit) ; *h ; ) {
      WORD Version;
      WORD TableID = GetTableAdmin()->GetTableID(NULL,h,&found,&Version);
      if (found) {
        LPTABLEDEF t = GetTableAdmin()->GetTableDef(TableID,Version);
        ConvertOneTable(t,toDLL,outDlg,fromDLL);
        GetTableAdmin()->FreeTable(TableID,Version);
        }
      h = next ;
      if (*h)
        next = NextTableName (h) ;
      }
    }
  else {
    for ( LPTABLEDEF t = GetTableAdmin()->GetFirstTableDef (&h);
          ((t != NULL) && (!doAbortConvert)) ; ) {
      if ((t->GetTableID() < GLOBALTBIDMIN) && (doConvert (t->GetName()))) {
        ConvertOneTable(t,toDLL,outDlg,fromDLL);
        }
      // Und weiter gehts
      ////////////////////////
      t = GetTableAdmin()->GetNextTableDef (&h);
      }
    }
  DestroyWindow (outDlg);
  }

DLLExport BOOL _export WINAPI EntwicklungsUmgebung ()
  {
  static BOOL ev,evGelesen;
  if (!evGelesen) {
    char ans[32];
    GetPrivateProfileString ("DataBase","Entwicklung","no",
                            ans,32,
                            GetIniName());
    ev = (lstrcmp (ans,"yes") == 0) ;
    }
  return ev;
  }

DLLExport WORD GetTableDefFromID (DWORD Id,WORD AnzVars,BYTE FAR *mType)
  {
  // Ermitteln der Gesamtgroesse
  WORD TableID = GetTableIDFromID (Id);
  if (TableID == 0xFFFF) {
    DWORD Size = NextOffset (sizeof(TableDef),sizeof(DWORD));
    GLOBALHANDLE hGres = GlobalAlloc (GMEM_ZEROINIT,Size + sizeof(LPVARDEF) * AnzVars);
    LPTABLEDEF tdef = LPTABLEDEF (GlobalLock (hGres));
    tdef->g.hGmem = hGres;
    tdef->AnzVars = AnzVars ;
    tdef->Name.ptr = GetGlobMem (1);
    tdef->File.ptr = GetGlobMem (1);
    tdef->tRef.TableNr = GetTableAdmin()->GetTemporaryID ();
    TableID = tdef->tRef.TableNr;
    SetIds (TableID,Id);
    tdef->VarTable.ptr = LPSTR(tdef) + Size;
    for (int i = 0 ; i < int(AnzVars) ; i++) {
      LPVARDEF v = LPVARDEF(GetGlobMem (sizeof(*v)));
      v->mType = mType[i] ;
      v->VarSize = 0xFFFF ;
      v->VarID = 0xFFFF ;
      v->structSize = sizeof(*v) ;
      tdef->SetVarDef (v,i);
      }

    // In die Liste der verwalteten Tabellen einhaengen
    for (LPTABLENODE FAR *prev = &GetTableAdmin()->TableList ; *prev != NULL ; prev = &((*prev)->Next)) ;
    LPTABLENODE h = LPTABLENODE (GetGlobMem (sizeof(*h)));
    *prev = h;
    h->Next = NULL;
    h->tRef.TableNr = tdef->GetTableID();
    h->tRef.Version = tdef->GetVersion();
    h->Count = 0;   // Sie ist noch nicht gelockt, damit sie wieder freigegeben werden kann
    h->def = tdef ;
    h->def->SetDLLHandle (GetDLLAdmin()->LoadDLL(GetInternDLLName()));

    IdHash->SetData (MAKELONG(h->tRef.TableNr,h->tRef.Version),&h,sizeof(h));
    AnzUsedTables ++ ;
    }
  return TableID;
  }

BOOL myStrCmp (LPSTR FAR &h,LPSTR Name)
  {
  for ( ; ; ) {
    if (*h != *Name) {
      if ((*h == ':') && (*Name == '\0')) {
        h++ ;
        return TRUE ;
        }
      else
        return FALSE ;
      }
    h++ ;
    Name ++ ;
    }
  }

DLLExport int _export WINAPI TableDef::GetTableProperty (LPSTR Name,LPSTR Buffer,int Size)
  {
  if (PropertyHash == NULL)
    PropertyHash = new hash (237,WORDKEY);
  LPSTR str = LPSTR (PropertyHash->GetDataW (GetTableID()));
  if (str != NULL) {
    for ( LPSTR h = str ; *h ; ) {
      if (myStrCmp (h,Name)) {
        for ( int i = 0 ; i < Size - 1 ; i++) {
          if ((*h != ';') && (*h))
            Buffer[i] = *h++ ;
          else
            break ;
          }
        Buffer[i] = '\0';
        return i ;
        }
      else {
        for ( BOOL breakNext = FALSE ; ; ) {
          if (!*h) break ;
          if (*h == ';') breakNext = TRUE ;
          if ((*h != ';') && (*h) && (breakNext))
            break ;
          h ++ ;
          }
        }
      }
    }
  return 0;
  }
