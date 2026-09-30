//
//  Alter Table Statements fuer Oracle
//
//  $Header:   P:/marille/clinicum/ddsora/rev/altora.cpv   1.52   05 Apr 2000 18:43:44   Wolfgang  $
//  $Log:   P:/marille/clinicum/ddsora/rev/altora.cpv  $
// 
//    Rev 1.52   05 Apr 2000 18:43:44   Wolfgang
// 1.) DATE und TIME ohne Kopieren in DATETIME updatebar.
// 
//    Rev 1.51   22 Feb 2000 12:46:16   Hannes
// Drop Constraint
// 
//    Rev 1.50   17 Jan 2000 21:05:40   Martin
// Einbau von UserOrb
// 
//    Rev 1.49   27 Jul 1999 12:03:48   Hannes
// Kein DoBeginTransaction, sonder BeginTransaction aufrufen...
// 
//    Rev 1.48   16 Jul 1999 18:19:50   Martin
// ORACLE_Check=Orbis eingebaut
// 
//    Rev 1.47   10 May 1999 17:18:10   Wolfgang
// 1.) Indexes nur droppen und kreieren, wenn noch nicht komplett neu erzeugt.
// 
//    Rev 1.46   07 May 1999 00:22:10   Hannes
// Groessencheck nicht nur bei Strings...
// 
//    Rev 1.45   07 May 1999 00:18:50   Hannes
// Verbesserungen beim Update...
// 
//    Rev 1.44   27 Apr 1999 07:29:06   Hannes
// Triggernamenslaenge
// 
//    Rev 1.43   12 Mar 1999 14:42:36   Martin
// DROP CTEMP_*_TRIGGER nur versuchen, wenn Tabelle caseinsensitive
// 
//    Rev 1.42   11 Mar 1999 19:43:36   Martin
// DROP TRIGGER CTEMP_*_TRIGGER, DelFromTableHash
// 
//    Rev 1.41   05 Mar 1999 16:08:54   Martin
// error = TRUE nur wenn Fehler !
// 
//    Rev 1.40   05 Mar 1999 10:54:52   Martin
// Diverse Fehlerabfragen, Verbesserte Synonym - Erzeugung
// 
//    Rev 1.39   11 Feb 1999 11:38:32   Martin
// Trigger vor dem Erzeugen loeschen
// 
//    Rev 1.38   29 Jan 1999 10:44:54   Hannes
// Prototyp von GetVarString
// 
//    Rev 1.37   11 Jan 1999 08:27:04   Hannes
// s_ -> SName()
// 
//    Rev 1.36   09 Oct 1998 18:17:40   Martin
// Synonymerzeugung, Rechtsuebergabe
// 
//    Rev 1.35   24 Aug 1998 14:16:46   Hannes
// Synonyme, UpdateUser
// 
//    Rev 1.34   10 Aug 1998 18:05:08   Martin
// Prefix-Fehler bei Sequences
// 
//    Rev 1.33   04 Aug 1998 17:56:24   Hannes
// Timestamp
// 
//    Rev 1.32   02 Jul 1998 10:27:06   Martin
// unnoetige CREATE TABLE Versuche beim UPDATE verhindert
// 
//    Rev 1.31   30 Jun 1998 14:39:18   Martin
// Transaktion bei ALTER TABLE ADD ... (wegen DEFAULTs)
// 
//    Rev 1.30   16 May 1998 09:06:34   Hannes
// Sonderbehandlung fuer neuaufgenommene _IDs
// 
//    Rev 1.29   06 Mar 1998 17:17:36   Hannes
// 
//    Rev 1.28   19 Feb 1998 11:14:12   Hannes
// Default NULL fuer mehr als eine Spalte
// 
//    Rev 1.27   18 Feb 1998 14:35:10   Hannes
// CreateIndex
// 
//    Rev 1.26   27 Nov 1997 18:46:10   Martin
// neuer Autoinc geht jetzt wieder
// 
//    Rev 1.25   25 Nov 1997 21:09:36   Hannes
// Verschiedene Verbesserungen
// 
//    Rev 1.24   21 Nov 1997 10:37:56   Hannes
// Verbesserung des For - STatements
// 
//    Rev 1.23   13 Nov 1997 14:45:34   Hannes
// 
//    Rev 1.22   10 Nov 1997 20:20:34   Hannes
// 
//    Rev 1.21   24 Sep 1997 16:27:00   Hannes
// Fehlerkorrektur in der Sync - Statement
// 
//    Rev 1.20   27 Aug 1997 13:01:40   Martin
// ein paar s.Clear eingebaut ...
// 
//    Rev 1.19   23 Jun 1997 12:33:52   Hannes
// 
//    Rev 1.18   23 May 1997 11:00:32   Hannes
// Korrekturen bei Schluesselerzeugen / Fehlerhandling korrigiert / entschaerft
// 
//    Rev 1.17   15 Apr 1997 13:01:40   Martin
// Fehlerhandling etwas verbessert
// 
//    Rev 1.16   10 Apr 1997 10:35:50   Hannes
// Erzeugen der Sequences
// 
//    Rev 1.15   19 Feb 1997 12:08:14   Hannes
// Bei Vergroesserungen von Feldern auch die KeyFelder vergroessert
// 
//    Rev 1.14   20 Dec 1996 18:12:30   HANNES
// 
//    Rev 1.13   20 Dec 1996 16:04:48   HANNES
// Abstand zwischen GetTypeName
// 
//    Rev 1.12   17 Dec 1996 17:04:52   HANNES
// 32 - Bit umstellung
// 
//    Rev 1.11   17 Dec 1996 11:53:06   HANNES
// Groessenaenderungen mit ueberpruefen
// 
//    Rev 1.10   17 Dec 1996 11:11:32   HANNES
// Stored - Procedures
// 
//    Rev 1.9   12 Dec 1996 14:46:56   HANNES
// 
//    Rev 1.8   06 Dec 1996 14:21:26   HANNES
// 
//    Rev 1.7   06 Dec 1996 13:10:02   HANNES
// 
//    Rev 1.6   06 Dec 1996 12:54:22   HANNES
// 
//    Rev 1.5   05 Dec 1996 11:11:00   HANNES
// 
//    Rev 1.4   04 Dec 1996 16:07:38   HANNES
// 
//    Rev 1.3   04 Dec 1996 14:49:34   HANNES
// 
//    Rev 1.2   04 Dec 1996 11:06:28   HANNES
// Abfrage bei bestimmten Fehler, ob trotzdem fortgesetzt werden soll.
// 
//    Rev 1.1   04 Dec 1996 10:02:06   HANNES
// TestTableDef -> TestTable
// 
//    Rev 1.0   26 Nov 1996 08:05:06   HANNES
// Initial revision.
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>           // >> FL 14.02.96
#include <ctype.h>            // >> FL 22.02.96
#include "dds32.h"

#include <string.h>
#define DLL_ORACLE 1
extern "C" {
  #include <oratypes.h>
  #include <ocidfn.h>       // LDA and CDA struct declarations
  #include <ociapr.h>
  //#ifdef __STDC__
  //#include <ociapr.h>
  //#else
  //#include <ocikpr.h>
  //#endif
  #include "ocicons.h"      // oci constants additionally used
}
#include "syb2ora.hpp"      // additional oci porting routines

#define NODDSDATA
#include "dds.hpp"
#include "globmem.h"
#include "dlladmin.h"
#include "dlladmin.hpp"
#include "tbdef.hpp"
#define MODULENUM 173
#include "winass.hpp"
#include "dbrecord.hpp"
#include "hash.hpp"
#define NOCOMPILE  
#include "compile.hpp"
#include "resadmin.hpp"

#include "opora.hpp"

#include "tbdiff.hpp"

class FAR keycheck : public sybstmt {
 public :
  keycheck () : sybstmt () { } 
  virtual int nRows (LPTABLEDEF ti,BOOL ignoreBlob = FALSE)
    { return 300 ; }
  virtual int nCols (LPTABLEDEF ti)
    { return 3 ; }
  virtual BOOL StoreData (LPTABLEDEF ti,int Row);
  virtual void GetColInfo(LPTABLEDEF ti);
  virtual ~keycheck () { }
  };

void keycheck::GetColInfo(LPTABLEDEF t0)
  {
  if (ColInfo == NULL) {
    blobCol = -1 ;
    dbCols = 3;
    ColInfo = (_COLINFO FAR *) GetGlobMem (dbCols * sizeof(*ColInfo));
    for (int i = 0 ; i < 2 ; i++) {
      // Datentypen fuer den Indexnamen und den Spaltennamen
      ColInfo[i].VarLen    = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarLen) * nRows(t0)) ;
      ColInfo[i].VarData   = GetSybDataType (&ColInfo[i].VarFormat,VAR_STR,64,nRows(t0));
      ColInfo[i].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarRetCode) * nRows(t0)) ;
      ColInfo[i].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarInd) * nRows(t0)) ;
      }
    // Datentypen fuer die Segmentposition
    ColInfo[i].VarLen    = (VARLEN_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarLen) * nRows(t0)) ;
    ColInfo[i].VarData   = GetSybDataType (&ColInfo[i].VarFormat,VAR_STRARR,sizeof(short),nRows(t0));
    ColInfo[i].VarRetCode = (VARRETCODE_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarRetCode) * nRows(t0)) ;
    ColInfo[i].VarInd     = (VARIND_TYPE FAR *) GetGlobMem (sizeof(*ColInfo[i].VarInd) * nRows(t0)) ;
    }
  }

struct FAR KeySegDef {
  LPSTR ColName;
  int ColPos;
  KeySegDef FAR *Next;
  };
struct FAR KeyDef {
  LPSTR KeyName;
  KeySegDef FAR *ks;
  KeyDef FAR *Next;
  void PushSeg (LPSTR ColName,int ColNamSize,int ColPos) 
    {
    KeySegDef FAR *n = (KeySegDef FAR *) GetGlobMem (sizeof(*n));
    n->ColName = LPSTR (GetGlobMem (ColNamSize + 1));
    lmemcpy (n->ColName,ColName,ColNamSize);
    n->ColPos = ColPos;
    if (ks == NULL)
      ks = n ;
    else {
      for (KeySegDef FAR *h = ks ; h->Next != NULL ; h = h->Next) ;
      h->Next = n ;
      }
    }
  void DestroySegs ()
    {
    for ( ; ks != NULL ; ) {
      KeySegDef FAR *n = ks->Next ;
      FreeGlobMem (ks->ColName) ;
      FreeGlobMem (ks);
      ks = n ;
      }
    }
  void FreeMem ()
    {
    DestroySegs ();
    FreeGlobMem (KeyName);
    }
  int FindCol (LPSTR ColName)
    {
    char colUpper [256];
    lstrcpy (colUpper,ColName);
    AnsiUpper (colUpper);
    for (KeySegDef FAR *h = ks ; h != NULL ; h = h->Next) {
      if (lstrcmp (h->ColName,colUpper) == 0) return h->ColPos;
      }
    return -1;
    }
  int ColCount ()
    {
    int i = 0;
    for (KeySegDef FAR *h = ks ; h != NULL ; h = h->Next)
      i++;
    return i;
    }
  };

static KeyDef FAR *checkres;
KeyDef FAR *PushName (LPSTR KeyName,int ksize)
  {
  for ( KeyDef FAR *k = checkres ; k != NULL ; k = k->Next)
    if (lmemcmp (k->KeyName,KeyName,ksize)) return k ;
  // Neuer Schluessel ;
  k = (KeyDef FAR *) GetGlobMem (sizeof(*k));
  k->KeyName = LPSTR(GetGlobMem (ksize + 1)) ;
  lmemcpy (k->KeyName,KeyName,ksize);
  k->Next = checkres ;
  checkres = k ;
  return k ;
  }

void PushKeySeg (LPSTR keyname,int keynamesize,LPSTR ColName,int ColNamSize,int ColPos)
  {
  KeyDef FAR *k = PushName (keyname,keynamesize);
  k->PushSeg (ColName,ColNamSize,ColPos) ;
  }

void DestroyKeyList ()
  {
  for ( ; checkres != NULL ; ) {
    KeyDef FAR *n = checkres->Next ;
    checkres->FreeMem ();
    FreeGlobMem (checkres);
    checkres = n;
    }
  }

BOOL keycheck::StoreData (LPTABLEDEF ti,int row)
  {
  WIN_ASSERT ((ColInfo[0].VarInd[row] != OCI_IND_NULL) &&
              (ColInfo[1].VarInd[row] != OCI_IND_NULL) &&
              (ColInfo[2].VarInd[row] != OCI_IND_NULL));
  LPVOID keyname = LPVOID (LPSTR (ColInfo[0].VarData) + row * ColInfo[0].VarFormat.maxlength) ;
  int keynamesize = int (ColInfo[0].VarLen[row]);
  LPVOID colname = LPVOID (LPSTR (ColInfo[1].VarData) + row * ColInfo[1].VarFormat.maxlength) ;
  int colnamesize = int (ColInfo[1].VarLen[row]);
  LPVOID colpos = LPVOID (LPSTR (ColInfo[2].VarData) + row * ColInfo[2].VarFormat.maxlength) ;
  int colpossize = int (ColInfo[2].VarLen[row]);

  PushKeySeg (LPSTR(keyname),keynamesize,
              LPSTR(colname),colnamesize,*(short FAR *) colpos);

  return TRUE ;
  }

extern BOOL IsOrbis (void);
LPSTR GetTablePrefix(LPTABLEDEF t,BOOL FAR *addName)
  {
  static BOOL prefRead;
  static char DBPrefix[32];
  static char TPrefix[32];
  if (t->GetTableProperty ("ORACLE_DBName",TPrefix,sizeof(TPrefix)) > 0) {
    *addName = FALSE;
    return TPrefix;
    }
  else if ((t->GetTableProperty ("ORACLE_Check",TPrefix,sizeof(TPrefix)) > 0) &&
           ((lstrcmp(TPrefix,"Orbis") == 0) && IsOrbis())) {
    *addName = TRUE;
    return "";
    }
  else {
    if (!prefRead) {
      char DefaultPrefix[4];
      if (IsOrbis())
        lstrcpy(DefaultPrefix,"CW_");
      else
        *DefaultPrefix = '\0';
      GetPrivateProfileString ("Oracle","DBPrefix", DefaultPrefix, DBPrefix, sizeof(DBPrefix),GetIniName());
      prefRead = TRUE;
      }
    }
  return DBPrefix;
  }

static LPTABLEDEF intTable;
LPSTR ORAGetTableName (LPTABLEDEF t,BOOL UsePrefix)
  {
  static char TNamBuffer[72];

  if (t->IsResourceTable ()) UsePrefix = FALSE;
  BOOL addName = TRUE;
  if (UsePrefix)
    lstrcpy (TNamBuffer,GetTablePrefix(t,&addName));
  else
    *TNamBuffer = '\0';

  if (t == intTable) {
    lstrcat (TNamBuffer,"CTEMP_");
    lstrcat (TNamBuffer,t->GetName());
    TNamBuffer[30] = '\0';
    return TNamBuffer;
    }
  else {
    if (addName)
      lstrcat (TNamBuffer,t->GetName());
    TNamBuffer[30] = '\0';
    return TNamBuffer;
    }
  }

extern char ActUserName[];
void PrepareKeyList (LPTABLEDEF td)
  {
  // Ermitteln des Schluesselnamens
  keycheck *c = new keycheck ();
  LongString s;
  char tnameUpper[64];
  lstrcpy (tnameUpper,ORAGetTableName (td,TRUE));
  AnsiUpper (tnameUpper);
  s = s + "SELECT /*+ RULE */ index_name,column_name,column_position FROM all_ind_columns " + 
                   "WHERE table_name = '" + tnameUpper + 
                   "' AND table_owner = '" + ActUserName + 
                   "' AND index_owner = '" + ActUserName + 
                   "' ORDER BY index_name,column_position" ;
  c->execute (s.Ptr(),NULL);
  delete c;
  }

BOOL GetKeyName (LPTABLEDEF td,int KeyNmbr,LPSTR KeyName)
  {
  for ( KeyDef FAR *h = checkres ; h != NULL ; h = h->Next ) {
    int j = 1;
    BOOL found = TRUE ;
    for (int i = 0 ; (i < (td->GetAnzKeySegs()) && (found)) ; i++) {
      LPCLKEYDEF k = td->GetKeyDef(i);
      if (k->KeyNmbr == WORD(KeyNmbr)) {
        LPVARDEF v = td->GetVarDef(k->VarID);
        LPSTR Name ;
        if (v->Property & VPROP_CASEINSENSITIVE)
          Name = GetKeyFieldName (v->GetName());
        else
          Name = GetAliasName (v->GetName());
        if (h->FindCol(Name) != j) 
          found = FALSE ;
        j ++ ;
        }
      }
    if (found && (h->ColCount() == (j - 1))) {
      lstrcpy (KeyName,h->KeyName);
      break ;
      }
    }

  return (h != NULL) ;
  }

BOOL AskForContinue (LPSTR msg,LPSTR TableName,BOOL doCat = TRUE)
  {
  char outtxt[512];
  wsprintf (outtxt,msg,TableName);
  if (doCat)
    lstrcat (outtxt,"\r\nBitte Setzen Sie nur dann fort, wenn Sie sich ganz sicher sind, daﬂ der Fehler ignoriert werden darf\r\n\r\nSoll trotzdem fortgesetzt werden?");
  int ret = MessageBox (GetActiveWindow (),outtxt,"WARNUNG!",MB_TASKMODAL | MB_ICONHAND | MB_YESNO);
  return (ret == IDYES) ;
  }

BOOL CreateIndex (LPTABLEDEF td,int KeyNmbr)
  {
  BOOL first = TRUE ;
  WORD oldKeyNr = 0xFFFF ;
  LongString c;
  sybstmt *h = new sybstmt ();

  BOOL res = TRUE ;

  for (int i = 0 ; ; i++) {
    LPCLKEYDEF k = (i < td->GetAnzKeySegs()) ? td->GetKeyDef (i) : NULL ;
    if ((k == NULL) || (k->KeyNmbr != oldKeyNr)) {
      if (!first) {
        c = c + ")" ;

        BOOL error = FALSE ;
        BOOL IsSet = IgnoreOracleError (955,TRUE); // Object already exists
        if (h->execute (c.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
        if (!IsSet) IgnoreOracleError (955,FALSE);

        if (error) {
          if (AskForContinue ("ERROR Beim Create Index",td->GetName()))
            error = FALSE ;
          }
        if (error) res = FALSE ;
        break ;
        }
      if (k != NULL) {
        if (k->KeyNmbr == WORD(KeyNmbr)) {
          char str[cMAX_VARNAMESIZE+1];
          strncpy(str, k->name, cMAX_VARNAMESIZE);
          str[cMAX_VARNAMESIZE] = 0;
          strncat(str, td->GetName(), cMAX_VARNAMESIZE - strlen(str));  
          str[cMAX_VARNAMESIZE] = 0;

          // create the index
          c.Clear ();
          LPVARDEF v = td->GetVarDef (k->VarID);
          BOOL keyIsUnique = (k->Attribute & CLKD_UNIQUE) != 0;
          c = c + "CREATE " ;
          if (keyIsUnique)
            c = c + "UNIQUE " ;
          LPSTR FName ;
          if (v->Property & VPROP_CASEINSENSITIVE)
            FName = GetKeyFieldName(v->GetName());
          else
            FName = GetAliasName(v->GetName());
          c = c + "INDEX \"" + str + "\" ON " + ORAGetTableName (td,TRUE) + "(" + FName ;
          first = FALSE ;
          }
        oldKeyNr = k->KeyNmbr;
        }
      else
        break ;
      }
    else if (k->KeyNmbr == WORD(KeyNmbr)) {
      LPVARDEF v = td->GetVarDef (k->VarID);
      LPSTR FName ;
      if (v->Property & VPROP_CASEINSENSITIVE)
        FName = GetKeyFieldName(v->GetName());
      else
        FName = GetAliasName(v->GetName());
      c = c + "," + FName ;
      }
    }
  delete h;

  return res ;
  }

BOOL CreateAllIndex (LPTABLEDEF td)
  {
  // Wieviele Schluessel gibts wirklich
  int LastKey = 0 ;
  for ( int i = 0 ; i < td->GetAnzKeySegs() ; i++) {
    if (int(td->GetKeyDef(i)->KeyNmbr) >= LastKey) LastKey = int(td->GetKeyDef(i)->KeyNmbr);
    }
  // Alle Schluessel erzeugen
  for ( i = 0 ; i <= LastKey ; i++)
    if (!CreateIndex (td,i)) return FALSE ;
  return TRUE ;
  }

void DropAllIndex (LPTABLEDEF td)
  {
  PrepareKeyList (td) ;
  LongString s;
  sybstmt *c = new sybstmt ();
  for ( KeyDef FAR *h = checkres ; h != NULL ; h = h->Next ) {
    s.Clear () ;
    BOOL IsSet = IgnoreOracleError (2429,TRUE); // Use Drop Constraint
    s = s + "DROP INDEX \"" + h->KeyName + "\"";
    if (c->execute (s.Ptr(),NULL) != CS_SUCCEED) {
      s.Clear () ;
      s = s + "ALTER TABLE " + ORAGetTableName (td,TRUE) + " DROP CONSTRAINT + \"" + h->KeyName + "\"";
      c->execute (s.Ptr(),NULL);
      }
    if (IsSet) IgnoreOracleError (2429,FALSE); // Object already exists
    }
  delete c;
  DestroyKeyList() ;
  }

BOOL TestAllIndex (LPTABLEDEF td)
  {
  BOOL res = TRUE ;
  PrepareKeyList (td) ;
  // Wieviele Schluessel gibts wirklich
  int LastKey = 0 ;
  for ( int i = 0 ; i < td->GetAnzKeySegs() ; i++) {
    if (int(td->GetKeyDef(i)->KeyNmbr) >= LastKey) LastKey = int(td->GetKeyDef(i)->KeyNmbr);
    }
  // Alle Schluessel erzeugen
  char KeyName[128];
  for ( i = 0 ; i <= LastKey ; i++) {
    if (!GetKeyName (td,i,KeyName)) {
      if (!CreateIndex (td,i)) {
        res = FALSE ;
        break ;
        }
      }
    }
  DestroyKeyList() ;
  return res ;
  }

#define justAlter   0  // Die Arbeit kann nur duch ein Alter
                       // durchgefuehrt werden
#define externTable 1  // Die Arbeit kann durch umschaufeln
                       // auf eine Fremdtabelle gemacht werden,
                       // jedoch mit SQL - Kommandos
#define ownTable    2  // Die Arbeit muss durch eine eigene
                       // Liste und eigenes Insert durchgefuehr werden
                       // (bloedester Fall)
#define CHECK(A) if (mode < A) mode = A;
BOOL AreThereVarIDS(LPTABLEDEF t)
  {
  for (int i = 0 ; i < t->GetAnzVars() ; i++)
    if (t->GetVarDef(i)->VarID != 0xFFFF) return TRUE ;
  return FALSE ;
  }
BOOL NewIDS(LPTABLEDEF tnew,LPTABLEDEF told,TableDifference FAR *tdi)
  {
  for ( int i = 0 ; i < tdi->AnzVarsToAdd () ; i++) {
    if ((tnew->GetVarDef(tdi->VarsToAdd[i])->VarSize >= 2000) ||
        (tnew->GetVarDef(tdi->VarsToAdd[i])->VarID != 0xFFFF)) return TRUE ;
    }
  // Wenn sie nicht in VarsToAdd sind, sind sie vielleicht so dazugekommen?
  // (Ev. Fehler in TableDiff, aus Kompatibilitaetsgruenden aber keine 
  // Korrektur)
  for ( i = 0 ; i < told->GetAnzVars() ; i++) {
    if (told->GetVarDef(i)->VarID != 0xFFFF) return FALSE ;
          // Der Alte hatte auch schon VarIDs
    }
  for ( i = 0 ; i < tnew->GetAnzVars() ; i++) {
    if (tnew->GetVarDef(i)->VarID != 0xFFFF) return TRUE ;
          // Der Neue hat VarIDs -> muss gemeldet werden
    }
  return FALSE ;
  }
BOOL SizeChanged (LPTABLEDEF tnew,LPTABLEDEF told,TableDifference FAR *td)
  {
  for ( int i = 0 ; i < td->AnzModified() ; i++) {
    LPVARDEF vold = told->GetVarDef(td->VarIDFrom (td->Modified[i])) ;
    LPVARDEF vnew = tnew->GetVarDef(td->Modified[i]);
    if (vold->mType != vnew->mType) {
      if ((vold->mType == VAR_STRARR) || (vold->mType == VAR_LONG)) {
        if ((vnew->mType == VAR_STRARR) || (vnew->mType == VAR_LONG))
          continue ;
        }
      else if ((vold->mType == VAR_DATE) || (vold->mType == VAR_TIME)) {
        if (vnew->mType == VAR_DATETIME)
          continue ;
        }
      }
    else {
      if (vold->VarSize != vnew->VarSize) {
        BOOL s1,s2;
        if (!((vold->VarSize < vnew->VarSize) && 
              (lstrcmp (GetTypeName (vold,i,&s1,told->GetKeyDef(0)),GetTypeName (vnew,i,&s2,tnew->GetKeyDef(0))) == 0)))
          return TRUE ;
        }
      }
    }
  return FALSE ;
  }
BOOL AreThereLONGS(LPTABLEDEF t)
  {
  for (int i = 0 ; i < t->GetAnzVars() ; i++) {
    if (t->GetVarDef(i)->VarID == 0xFFFF) {
      if (t->GetVarDef(i)->VarSize >= 2000) return TRUE ;
      }
    }
  return FALSE ;
  }
void MarkTableFromINTName (LPTABLEDEF tnew)
  {
  if (tnew) {
    WIN_ASSERT (intTable == NULL);
    intTable = tnew ;
    }
  else
    intTable = NULL ;
  }
BOOL PrefixChanged()
  {
  static BOOL prefRead,prefChanged;
  if (!prefRead) {
    char CheckPrefix[32];
    GetPrivateProfileString ("Oracle","SetPrefix", "", CheckPrefix, sizeof(CheckPrefix),GetIniName());
    prefChanged = (lstrcmp (CheckPrefix,"yes") == 0);
    prefRead = TRUE;
    }
  return prefChanged;
  }
#define STEPWITH  10
BOOL IsThereDefault (LPVARDEF v,int AnzDefs,DefVal FAR *dv)
  {
  for (int i = 0 ; i < AnzDefs ; i++) {
    if (lstrcmp(v->GetName(),dv[i].VarName) == 0) return TRUE ;
    }
  return FALSE ;
  }

void DefaultStatement (LongString FAR &s,LPVARDEF v,int AnzDefs,DefVal FAR *dv)
  {
  for (int i = 0 ; i < AnzDefs ; i++) {
    if (lstrcmp(v->GetName(),dv[i].VarName) == 0) {
      BOOL doFree;
      LPSTR vs = GetVarString (dv[i].DefaultValue,dv[i].mType,&doFree,
                    GetBlockSize (dv[i].DefaultValue),TRUE,0);
      s = s + " DEFAULT " + vs ;

      if (doFree)
        FreeGlobMem (vs);
      }
    }
  }

static BOOL _inAlter;
BOOL InAlter ()
  {
  return _inAlter;
  }

LPSTR TriggerName (LPTABLEDEF tnew)
  {
  static char res[31];
  res[22] = '\0';
  lstrncpy (res,ORAGetTableName (tnew,TRUE),22);
  lstrcat (res,"_TRIGGER");
  return res;
  }

void DeleteTrigger (sybstmt *h,LPTABLEDEF tnew)
  {
  BOOL first = TRUE ;
  for ( int i = 0 ; i < tnew->GetAnzVars () ; i++) {
    LPVARDEF v = tnew->GetVarDef(i);
    if (v->Property & VPROP_CASEINSENSITIVE) {
      first = FALSE ;
      break;
      }
    }
  if (!first) {  // nur dann, wenn caseinsensitive !
    LongString dt ;
    dt.Clear();
    dt = dt + "DROP TRIGGER " + TriggerName (tnew);
    BOOL IsSet = IgnoreOracleError (4080,TRUE);
    h->execute (dt.Ptr(),NULL);
    if (!IsSet) IgnoreOracleError (4080,FALSE);
    }
  }

BOOL TriggerStatement (sybstmt *h,LongString FAR &s,LPTABLEDEF tnew)
  {
  s.Clear ();
  s = s + "CREATE OR REPLACE TRIGGER " + TriggerName (tnew) +
      " BEFORE INSERT OR UPDATE OF " ;
  BOOL first = TRUE ;
  for ( int i = 0 ; i < tnew->GetAnzVars () ; i++) {
    LPVARDEF v = tnew->GetVarDef(i);
    if (v->Property & VPROP_CASEINSENSITIVE) {
      if (!first)
        s = s + "," ;
      s = s + GetAliasName (v->GetName()) ;
      first = FALSE ;
      }
    }
  if (!first) {
    s = s + " ON " + ORAGetTableName (tnew,TRUE) + " FOR EACH ROW BEGIN " ;
    for (int i = 0 ; i < tnew->GetAnzVars () ; i++) {
      LPVARDEF v = tnew->GetVarDef(i);
      if (v->Property & VPROP_CASEINSENSITIVE) {
        s = s + ":new." + GetKeyFieldName (v->GetName()) + 
              " := CLTrans(:new." + GetAliasName (v->GetName()) + ") ;" ;
        }
      }
    s = s + " END;" ;
    }
  if (!first) {
    // eventuell alten Trigger loeschen
    DeleteTrigger(h,tnew);
    }
  return !first ;
  }

static BOOL mystrcmp (LPSTR s1,LPSTR s2)
  {
  for ( ; ((*s1 == *s2) && (*s1) && (*s2)) ; s1 ++ , s2++) ;
  return (*s2 == '\0') ;
  }

BOOL NeuerAutoInc (TableDifference FAR *tx,LPTABLEDEF tnew)
  {
  if ((tx->AnzKeysToDrop () > 0) && 
      (tx->AnzKeysToAdd () > 0) &&
      (tx->KeysToDrop[0] == 0) &&
      (tx->KeysToAdd[0] == 0) &&
      ((tnew->GetKeyDef(0)->Attribute & CLKD_AUTOINC) == CLKD_AUTOINC))
    return TRUE ;
  else
    return FALSE ;
  }

LPSTR SName (LPSTR TName)
  {
  static char res[31];
  lstrcpy (res,"s_");
  lstrncpy (res + 2,TName,28);
  res[30] = '\0' ;

  return res;
  }

DLLExport BOOL _export WINAPI DBAlter (LPTABLEDEF told,LPTABLEDEF tnew,int AnzDefs,DefVal FAR *dv,__ALTERSUCCESS alts)
  {
  if (told == tnew) {
    if (PrefixChanged()) {
      CheckFile (NULL,FALSE,TRUE);
      sybstmt *h = new sybstmt ();
      BOOL error = !dbase->TestTable(tnew);
      LongString s ;
      s = s + "RENAME " + ORAGetTableName (tnew,FALSE) ;
      s = s + " TO " + ORAGetTableName (tnew,TRUE);
      if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
      s.Clear ();
      if (TriggerStatement (h,s,tnew)) {
        if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
        }
      delete h ;

      LPSTR SynTab = ORAGetTableName (tnew,TRUE);
      DoSynonym (SynTab,SynTab,"INSERT,UPDATE,DELETE,SELECT");
      UserOrb (SynTab);
      LPSTR SynSeq = GetSequenceName (tnew);
      DoSynonym (SynSeq,SynSeq,"SELECT");
      UserOrb (SynSeq);

      return error;
      }
    }

  BOOL error = FALSE;

  // wenn ORACLE_Check=Orbis, dann in ORBIS-Version nichts machen
  char OCheck[32];
  if (!((tnew->GetTableProperty ("ORACLE_Check",OCheck,sizeof(OCheck)) > 0) &&
           ((lstrcmp(OCheck,"Orbis") == 0) && IsOrbis()))) {

    _inAlter = TRUE ;
    TableDifference td(told,tnew,0xFFFF,0xFFFF);

    if (!td.NoDifference()) {
      // 
      // Ermitteln, in welchem modus das ganze gemacht werden muss
      //
      CheckFile (NULL,FALSE,TRUE);
      dbase->StartTableTest ();

      short mode = justAlter;
      if (SizeChanged (tnew,told,&td))
        CHECK(ownTable);
      if (td.AnzVarsToDrop () > 0) 
        CHECK(externTable);
      BOOL NewAuto = FALSE;
      if (NeuerAutoInc (&td,tnew)) {
        CHECK(ownTable);
        NewAuto = TRUE;
        }
      if (((mode == externTable) &&
          ((tnew->HoldBlobs()) || 
            (AreThereVarIDS(tnew)) || 
            (AreThereLONGS(tnew)) || 
            (AreThereVarIDS(told)) || 
            (AreThereLONGS(told)))) ||
          (NewIDS(tnew,told,&td)))
        CHECK(ownTable);

      BOOL askDone = FALSE ;

      switch (mode) {
        case justAlter :
          //
          // Alle neue Variablen mit Alter Table rein
          //
          {
          sybstmt *h = new sybstmt ();
          LongString s ;
          error = !dbase->TestTable(told);
          if (error) {
            if (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein",told->GetName()))
              error = FALSE ;
            askDone = TRUE ;
            }
          BOOL keyField = FALSE ;

          if (!error) {
            BOOL addDone = FALSE ;
            s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " ADD (" ;
            for ( int i = 0 ; i < td.AnzVarsToAdd() ; i++) {
              if (addDone) s = s + "," ;
              LPVARDEF v = tnew->GetVarDef(td.VarsToAdd[i]);
              BOOL doSize;
              s = s + GetAliasName (v->GetName()) + " " + GetTypeName (v,td.VarsToAdd[i],&doSize,tnew->GetKeyDef(0));
              if (doSize) {
                s = s + "(" + int(v->VarSize) + ")" ;
                }
              if (((v->Property & VPROP_NOTNULL) != 0) && (!IsThereDefault(v,AnzDefs,dv))) {
                s = s + " NOT NULL" ;
                }
              DefaultStatement (s,v,AnzDefs,dv);
              if (v->Property & VPROP_CASEINSENSITIVE) {
                s = s + "," ;
                s = s + GetKeyFieldName (v->GetName()) + " " + GetTypeName (v,td.VarsToAdd[i],&doSize,tnew->GetKeyDef(0));
                if (doSize) {
                  s = s + "(" + int(v->VarSize) + ")" ;
                  }
                if ((v->Property & VPROP_NOTNULL) != 0) {
                  s = s + " NOT NULL" ;
                  }
                keyField = TRUE;
                }

              addDone = TRUE ;
              }

            // Alle Variablen dazunehmen, die sich um die Property
            // VPROP_CASEINSENSITIVE geaendert haben
            for ( i = 0 ; i < td.AnzModified() ; i++) {
              LPVARDEF vold = told->GetVarDef(td.VarIDFrom (td.Modified[i])) ;
              LPVARDEF vnew = tnew->GetVarDef(td.Modified[i]) ;
              if (((vold->Property & VPROP_CASEINSENSITIVE) == 0) &&
                  (vnew->Property & VPROP_CASEINSENSITIVE)) {
                if (addDone) s = s + "," ;
                BOOL doSize;
                s = s + GetKeyFieldName (vnew->GetName()) + " " + GetTypeName (vnew,i,&doSize,tnew->GetKeyDef(0));
                if (doSize) {
                  s = s + "(" + int(vnew->VarSize) + ")" ;
                  }
                addDone = TRUE ;
                keyField = TRUE;
                }
              }

            if (addDone) {
              s = s + ")" ;

              DoBeginTransaction(TRUE);
              BOOL IsSet = IgnoreOracleError (1430,TRUE); // column already exists
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (1430,FALSE);
              DoEndTransaction();
              if (error) {
                if (AskForContinue ("Der ALTER TABLE Auf %s konnte nicht durchgef¸hrt werden",told->GetName()))
                  error = FALSE ;
                askDone = TRUE ;
                }
              }

            if ((keyField) && (!error)) {
              TriggerStatement (h,s,tnew);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              }
            }

          s.Clear ();
          if ((!error) && (AnzDefs > 0)) {
            // Alle Defaults wieder ausschalten
            //---------------------------------
            s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY (" ;
            BOOL first = TRUE ;
            for (int i = 0 ; i < AnzDefs ; i++) {
              if (!first) s = s + "," ;
              s = s + dv[i].VarName + " DEFAULT NULL" ;
              first = FALSE;
              }
            s = s + ")" ;
            if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
            }

          s.Clear ();
          if (!error) {
            BOOL first = TRUE ;
            // die Null - Values modifizieren
            //---------------------------------
            for (int i = 0 ; (i < td.AnzModified()) ; i++) {
              LPVARDEF vold = told->GetVarDef(td.VarIDFrom (td.Modified[i])) ;
              LPVARDEF vnew = tnew->GetVarDef(td.Modified[i]) ;
              if ((vold->Property & VPROP_NOTNULL) &&
                  ((vnew->Property & VPROP_NOTNULL) == 0)) {
                if (first) {
                  s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY (" ;
                  s = s + GetAliasName (vnew->GetName()) + " NULL" ;
                  first = FALSE ;
                  }
                else {
                  s = s + "," + GetAliasName (vnew->GetName()) + " NULL" ;
                  }
                }
              if (((vold->Property & VPROP_NOTNULL) == 0) &&
                  (vnew->Property & VPROP_NOTNULL)) {
                if (first) {
                  s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY (" ;
                  s = s + GetAliasName (vnew->GetName()) + " NOT NULL" ;
                  first = FALSE ;
                  }
                else {
                  s = s + "," + GetAliasName (vnew->GetName()) + " NOT NULL" ;
                  }
                }
              }
            // Alle Variablen, die mit dem Add dazugekommen sind und einen
            // Default hatten und not null sind, noch als NOT NULL aendern
            for (i = 0 ; (i < td.AnzVarsToAdd()) ; i++) {
              LPVARDEF v = tnew->GetVarDef(td.VarsToAdd[i]) ;
              if ((v->Property & VPROP_NOTNULL) && (IsThereDefault (v,AnzDefs,dv))) {
                if (first) {
                  s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY (" ;
                  s = s + GetAliasName (v->GetName()) + " NOT NULL" ;
                  first = FALSE ;
                  }
                else {
                  s = s + "," + GetAliasName (v->GetName()) + " NOT NULL" ;
                  }
                }
              }
            if (!first) {
              s = s + ")" ;
              BOOL IsSet = IgnoreOracleError (1442,TRUE); // Already not null
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (1442,FALSE);
              if (error) {
                if (AskForContinue ("Der MODIFY TABLE Auf %s konnte nicht durchgef¸hrt werden",told->GetName()))
                  error = FALSE ;
                askDone = TRUE ;
                }
              }
            }

          s.Clear ();
          if (!error) {
            BOOL first = TRUE ;
            // Die Groessen ev. nachaendern (sofern sie wirklich groesser geworden sind)
            //-------------------------------------------------------------------------------------------------
            for (int i = 0 ; (i < td.AnzModified()) ; i++) {
              LPVARDEF vold = told->GetVarDef(td.VarIDFrom (td.Modified[i])) ;
              LPVARDEF vnew = tnew->GetVarDef(td.Modified[i]) ;
              BOOL doSize;
              LPSTR TypeName = GetTypeName (vnew,td.Modified[i],&doSize,tnew->GetKeyDef(0));
              if ((vold->VarSize < vnew->VarSize) && (vold->mType == vnew->mType) && (doSize)) {
                if (first) {
                  s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY (" ;
                  s = s + GetAliasName (vnew->GetName()) + " " + TypeName + "(" + vnew->VarSize + ")" ;
                  first = FALSE ;
                  }
                else {
                  s = s + "," + GetAliasName (vnew->GetName()) + " " + TypeName + "(" + vnew->VarSize + ")" ;
                  }
                if ((vold->Property & VPROP_CASEINSENSITIVE) && (vnew->Property & VPROP_CASEINSENSITIVE)) {
                  s = s + "," + GetKeyFieldName (vnew->GetName()) + " " + TypeName + "(" + vnew->VarSize + ")" ;
                  }
                }
              }
            if (!first) {
              s = s + ")" ;
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              }
            }

          // Alle Triggers aktivieren
          s.Clear ();
          BOOL doUpdate;
          if ((keyField) && (askDone) && (!error))
            // Sicherheitshalber noch einmal nachfragen, damit der 
            // Update nicht doppelt gemacht wird.
            doUpdate = AskForContinue ("Es sind Fehler bei den vorhergehenden Aktionen auf %s aufgetreten.\r\nWollen Sie den Update durchf¸hren, oder soll dieser Schritt ¸bergangen werden\r\n(Dieser Schritt kann bei groﬂen Tabellen ev. lange dauern).",told->GetName(),FALSE);
          else
            doUpdate = TRUE ;
          int indexesDone = FALSE;
          if ((keyField) && (!error) && (doUpdate)) {
            DropAllIndex (tnew);
            // h->execute ("COMMIT",NULL);
            DoBeginTransaction(TRUE);
            // h->execute ("SET TRANSACTION USE ROLLBACK SEGMENT RB1",NULL);
            BOOL first = TRUE ;
            s = s + "UPDATE " + ORAGetTableName (tnew,TRUE) + " SET " ;
            for (int i = 0 ; i < tnew->GetAnzVars() ; i++) {
              LPVARDEF v = tnew->GetVarDef (i);
              if (v->Property & VPROP_CASEINSENSITIVE) {
                if (!first) s = s + "," ;
                s = s + GetAliasName (v->GetName()) + " = " + GetAliasName (v->GetName()) ;
                first = FALSE ;
                }
              }
            if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
            if (!error)
              DoEndTransaction ();
            else
              DoAbortTransaction ();
            CreateAllIndex (tnew);
            indexesDone = TRUE;
            }

          s.Clear ();
          if (!error) {
            // Alle Variablen, die wegen der Property
            // VPROP_CASEINSENSITIVE dazugekommen sind
            // ev. noch not null nachsetzen
            //---------------------------------
            s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY (" ;
            BOOL first = TRUE ;
            for ( int i = 0 ; i < td.AnzModified() ; i++) {
              LPVARDEF vold = told->GetVarDef(td.VarIDFrom (td.Modified[i])) ;
              LPVARDEF vnew = tnew->GetVarDef(td.Modified[i]) ;
              if (((vold->Property & VPROP_CASEINSENSITIVE) == 0) &&
                  (vnew->Property & VPROP_CASEINSENSITIVE) &&
                  (vnew->Property & VPROP_NOTNULL)) {
                if (!first) s = s + "," ;
                s = s + GetKeyFieldName (vnew->GetName()) + " NOT NULL" ;
                first = FALSE ;
                }
              }
            if (!first) {
              s = s + ")" ;
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (error) {
                if (AskForContinue ("Der MODIFY TABLE (NOT NULL) auf %s konnte nicht durchgef¸hrt werden",told->GetName()))
                  error = FALSE ;
                askDone = TRUE ;
                }
              }
            }

          // Alte Indizess wegnehmen
          //-----------------------------
          if ((!indexesDone) && (td.AnzKeysToDrop() > 0) && (!error)) {
            PrepareKeyList (told);
            for ( int i = 0 ; ((i < td.AnzKeysToDrop ()) && (!error)) ; i++) {
              char KeyName[256];
              s.Clear ();
              if (GetKeyName (told,td.KeysToDrop[i],KeyName)) {
                if (mystrcmp (KeyName,"SYS_C")) {
                  BOOL first = TRUE ;
                  s = s + "ALTER TABLE " + ORAGetTableName (told,TRUE) + " DROP UNIQUE (" ;
                  for (int j = 0 ; j < told->GetAnzKeySegs() ; j++) {
                    LPCLKEYDEF k = told->GetKeyDef (j);
                    if (k->KeyNmbr == WORD(td.KeysToDrop[i])) {
                      if (!first)
                        s = s + "," ;
                      LPVARDEF v = told->GetVarDef(k->VarID);
                      if (v->Property & VPROP_CASEINSENSITIVE)
                        s = s + GetKeyFieldName (v->GetName());
                      else
                        s = s + GetAliasName (v->GetName());
                      first = FALSE ;
                      }
                    }
                  s = s + ")" ;
                  }
                else {
                  s = s + "DROP INDEX \"" + KeyName + "\"";
                  }
                if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
                }
              }
            DestroyKeyList() ;
            }

          // Neue Indizess hinzunehmen
          //-----------------------------
          if (!indexesDone) {
            for ( int i = 0 ; ((i < td.AnzKeysToAdd ()) && (!error)) ; i++) {
              if (!CreateIndex (tnew,td.KeysToAdd[i]))
                error = TRUE ;
              }
            }

          delete h ;
          }
          break ;
        case externTable :
          {
          //
          // Zuerst wird die Tabelle in der neuen Struktur erzeugt
          //
          error = !dbase->TestTable (told);
          BOOL skipFurther = FALSE;
          if (error) {
            BOOL dontDoIt = dbase->TestTableDef (tnew);
            if (dontDoIt) {
              if (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein, Entspricht jedoch dem Aufbau der neuen Version. W‰hlen Sie JA um fortzufahren",told->GetName())) {
                error = FALSE ;
                skipFurther = TRUE ;
                }
              askDone = TRUE ;
              }
            else {
              if (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein",told->GetName()))
                error = FALSE ;
              askDone = TRUE ;
              }
            }
          if (!skipFurther) {
            sybstmt *h = new sybstmt ();
            LongString s;
            MarkTableFromINTName (tnew);
            if (!error) {
              // Sicherheitshalber die Zwischentabelle noch einmal
              // droppen
              LPSTR SynTab = ORAGetTableName (tnew,TRUE);
              DropSynonym (SynTab);
              s = s + "DROP TABLE " + SynTab;
              BOOL IsSet = IgnoreOracleError (942,TRUE);
              h->execute (s.Ptr(),NULL);
              if (!IsSet) IgnoreOracleError (942,FALSE);
              s.Clear ();
              LPSTR SynSeq = GetSequenceName (tnew);
              DropSynonym (SynSeq);
              s = s + "DROP SEQUENCE " + SynSeq;
              IsSet = IgnoreOracleError (2289,TRUE);
              h->execute (s.Ptr(),NULL);
              if (!IsSet) IgnoreOracleError (2289,FALSE);
              s.Clear ();
              }

            if (!error)
              error = !dbase->CreateTable (tnew,FALSE); // Ohne Schluessel

            // Alle Defaultwerte werden vernuenftig werden durch einen Alter
            // Table dazugefuegt
            s.Clear() ;
            if (!error) {
              for (int i = 0 ; ((i < AnzDefs) && (!error)) ; i++) {
                s.Clear();
                BOOL doFree;
                LPSTR vs = GetVarString (dv[i].DefaultValue,dv[i].mType,&doFree,
                              GetBlockSize (dv[i].DefaultValue),TRUE,0);
                s = s + "ALTER TABLE " + ORAGetTableName (tnew,TRUE) + " MODIFY " + 
                    GetAliasName (dv[i].VarName) + " DEFAULT " + vs ;

                if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;

                if (doFree)
                  FreeGlobMem (vs);
                }
              }

            // Zusammenbasteln eines Vernuenftigen INSERT Strings
            if (!error) {
              s.Clear ();
              s = s + "INSERT INTO " + ORAGetTableName (tnew,TRUE) + " (" ;
              BOOL first = TRUE ;
              for (int i = 0 ; i < told->GetAnzVars () ; i++) {
                if (td.IsToCopy (i)) {
                  if (!first) s = s + "," ;
                  s = s + GetAliasName (told->GetVarDef(i)->GetName()) ;
                  first = FALSE ;
                  }
                }
              s = s + ") SELECT " ;
              first = TRUE ;
              for (i = 0 ; i < told->GetAnzVars () ; i++) {
                if (td.IsToCopy (i)) {
                  if (!first) s = s + "," ;
                  s = s + GetAliasName (told->GetVarDef(i)->GetName()) ;
                  first = FALSE ;
                  }
                }
              s = s + " FROM " + ORAGetTableName (told,TRUE);

              // SET Transaction um moeglichst keinen Ueberlauf auf dem
              // Rollback segment zu provozieren (ev. spaeter auch einmal
              // ein anderes Rollbacksegment angeben lassen)
              // h->execute ("COMMIT",NULL);
              DoBeginTransaction(TRUE);
              // h->execute ("SET TRANSACTION USE ROLLBACK SEGMENT rb1",NULL);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              DoEndTransaction();
              }

            s.Clear ();
            if (!error) {
              // Jetzt wird die alte Tabelle gedroppt und von der Zwischentabelle
              // wird wieder alles rueberkopiert
              LPSTR SynTab = ORAGetTableName (told,TRUE);
              DropSynonym (SynTab);
              s = s + "DROP TABLE " + SynTab;
              BOOL IsSet = IgnoreOracleError (942,TRUE);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (942,FALSE);
              // die Sequence bleibt unangetastet
              }

            if (!error)
              DelFromTableHash(told);

  #ifdef UEBERLEGT
            if (!error) {
              MarkTableFromINTName (NULL);
              error = !dbase->CreateTable (tnew,FALSE);
              MarkTableFromINTName (tnew);
              }

            s.Clear ();
            if (!error) {
              s = s + "INSERT INTO " + ORAGetTableName (tnew,TRUE) + " SELECT * FROM " +
                      ORAGetTableName (tnew);

              // SET Transaction um moeglichst keinen Ueberlauf auf dem
              // Rollback segment zu provozieren (ev. spaeter auch einmal
              // ein anderes Rollbacksegment angeben lassen)
              // h->execute ("COMMIT",NULL);
              DoBeginTransaction(TRUE);
              // h->execute ("SET TRANSACTION USE ROLLBACK SEGMENT rb1",NULL);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              DoEndTransaction();
              // Alle Schluessel auf dem neuen File erzeugen
              if (!CreateAllIndex (tnew)) error = TRUE ;
              }

            s.Clear ();
            if (!error) {
              // Die Zwischentabelle kann gedroppt werden
              LPSTR SynTab = ORAGetTableName (tnew,TRUE);
              DropSynonym (SynTab);
              s = s + "DROP TABLE " + SynTab;
              BOOL IsSet = IgnoreOracleError (942,TRUE);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (942,FALSE);
              s.Clear ();
              LPSTR SynSeq = GetSequenceName (tnew);
              DropSynonym (SynSeq);
              s = s + "DROP SEQUENCE " + SynSeq;
              IsSet = IgnoreOracleError (2289,TRUE);
              h->execute (s.Ptr(),NULL);
              if (!IsSet) IgnoreOracleError (2289,FALSE);
              }

  #else
            // eventuell vorhandenes Synonym auf CTEMP_... loeschen
            LPSTR SynTab = ORAGetTableName (tnew,TRUE);
            DropSynonym (SynTab);
            // eventuell CTEMP_..._TRIGGER loeschen
            DeleteTrigger(h,tnew);
            s.Clear ();
            s = s + "RENAME " + ORAGetTableName (tnew,TRUE) + " TO " ;
            MarkTableFromINTName (NULL);
            s = s + ORAGetTableName (tnew,TRUE);
            if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
            if (!CreateAllIndex (tnew)) error = TRUE ;
  #endif
            MarkTableFromINTName (NULL);
            delete h ;
            }
          }
          break ;
        case ownTable :
          //
          // In der Tabelle sind BLOBS verstreut, deswegen kann leider kein
          // Statement zum umkopieren verwendet werden
          //
          {
          error = !dbase->TestTable (told);
          BOOL skipFurther = FALSE ;
          if (error) {
            BOOL dontDoIt = dbase->TestTableDef (tnew);
            if (dontDoIt) {
              if (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein, Entspricht jedoch dem Aufbau der neuen Version. W‰hlen Sie JA um fortzufahren",told->GetName())) {
                error = FALSE ;
                skipFurther = TRUE ;
                }
              askDone = TRUE ;
              }
            else {
              if (AskForContinue ("Alte Tabelle %s stimmt nicht mit der Definition ueberein",told->GetName()))
                error = FALSE ;
              askDone = TRUE ;
              }
            }

          if (!skipFurther) {
            MarkTableFromINTName (tnew);

            sybstmt *h = new sybstmt ();

            LongString s;
            if (!error) {
              // Sicherheitshalber die Zwischentabelle noch einmal
              // droppen
              LPSTR SynTab = ORAGetTableName (tnew,TRUE);
              DropSynonym (SynTab);
              s = s + "DROP TABLE " + SynTab;
              BOOL IsSet = IgnoreOracleError (942,TRUE);
              h->execute (s.Ptr(),NULL);
              if (!IsSet) IgnoreOracleError (942,FALSE);
              s.Clear ();
              LPSTR SynSeq = GetSequenceName (tnew);
              DropSynonym (SynSeq);
              s = s + "DROP SEQUENCE " + SynSeq;
              IsSet = IgnoreOracleError (2289,TRUE);
              h->execute (s.Ptr(),NULL);
              if (!IsSet) IgnoreOracleError (2289,FALSE);
              }

            s.Clear();

            if (!error)
              error = !dbase->CreateTable (tnew,NewAuto);

            // Bilden einer Liste auf das alte file
            DBList FAR *res = NULL;
            if (!error) {
              static ParamBlock p;
              lmemset (&p,'\0',sizeof(p));
              p.AnzPars = 0;

              res = new DBList (told,0L,"",100,100,&p,FALSE);
              res->SetOrder ("");
              if (res == NULL) error = TRUE ;
              else    res->SetSimpleList ();
              }

            // Alle Datensaetze in das neue File umkopieren
            DWORD row = 0L ;
            if (!error) {
              InitializeDefVal (dv,AnzDefs,tnew);
              for (LPDBRECORD h = res->GetFirst(); ((h != NULL) && (!error)) ; h = res->GetNext(h)) {
                DBRecord FAR *n = ConvertRecord (tnew,h,&td,AnzDefs,dv);

                LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,0L);
                WORD TableID = tnew->GetTableID();
                WORD Version = tnew->GetVersion();
                req->SetTableID(TableID,Version);
                req->AddTableDef (TableID,Version);
                req->SetParam (1,&TableID,sizeof(TableID));
                req->AnzParam = 0;

                RecBuffer rb;
                lmemset (&rb,'\0',sizeof(rb));
                rb.AddLine (1,ADDLINEPOS_START);
                rb.act->rec[0] = n ;

                LPVOID hstmt = NULL;
                int stat = DBCall (DBOP_GET,1,req,&hstmt,&rb);
                DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);

                rb.Clear ();
                req->ClearParams();
                req->FreeTableDefs();
                FreeRequest (req);

                delete n ;

                error = (stat != DBCALL_SUCCESS);

                res->ThrowAtHead(h);

                row ++ ;
                if ((row % STEPWITH) == 0L)
                  (* alts) (row) ;
                }
              }
            if (res != NULL)
              delete res ;

            // So, jetzt das ganze wieder zurueck
            s.Clear ();
            if (!error) {
              LPSTR SynTab = ORAGetTableName (told,TRUE);
              DropSynonym (SynTab);
              s = s + "DROP TABLE " + SynTab;
              BOOL IsSet = IgnoreOracleError (942,TRUE);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (942,FALSE);
              // die Sequence bleibt unangetastet
              s.Clear ();
              }

            if (!error)
              DelFromTableHash(told);

  #ifdef UEBERLEGT
            if (!error) {
              static ParamBlock p;
              lmemset (&p,'\0',sizeof(p));
              p.AnzPars = 0;

              res = new DBList (tnew,0L,"",100,100,&p,FALSE);
              res->SetOrder ("");
              if (res == NULL) error = TRUE ;
              }

            if (!error) {
              for (LPDBRECORD h = res->GetFirst(); ((h != NULL) && (!error)) ; h = res->GetNext(h)) {
                LPDBREQUEST req = InitializeRequest ("",-1,DBCALLTYPE_STANDARDINSERT,0L);
                WORD TableID = tnew->GetTableID();
                WORD Version = tnew->GetVersion();
                req->SetTableID(TableID,Version);
                req->AddTableDef (TableID,Version);
                req->SetParam (1,&TableID,sizeof(TableID));
                req->AnzParam = 0;

                RecBuffer rb;
                lmemset (&rb,'\0',sizeof(rb));
                rb.AddLine (1,ADDLINEPOS_START);
                rb.act->rec[0] = h ;

                LPVOID hstmt = NULL;
                MarkTableFromINTName (NULL);
                int stat = DBCall (DBOP_GET,1,req,&hstmt,&rb);
                DBCall (DBOP_RESET,0,NULL,&hstmt,NULL);
                MarkTableFromINTName (tnew);

                rb.Clear ();
                req->ClearParams();
                req->FreeTableDefs();
                FreeRequest (req);

                error = (stat != DBCALL_SUCCESS);

                res->ThrowAtHead(h);

                row ++ ;
                if ((row % STEPWITH) == 0L)
                  (* alts) (row) ;
                }
              }
            if (res != NULL)
              delete res ;

            s.Clear ();
            if (!error) {
              // Die Zwischentabelle kann gedroppt werden
              LPSTR SynTab = ORAGetTableName (tnew,TRUE);
              DropSynonym (SynTab);
              s = s + "DROP TABLE " + SynTab;
              BOOL IsSet = IgnoreOracleError (942,TRUE);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (942,FALSE);
              s.Clear ();
              LPSTR SynSeq = GetSequenceName (tnew);
              DropSynonym (SynSeq);
              s = s + "DROP SEQUENCE " + SynSeq;
              IsSet = IgnoreOracleError (2289,TRUE);
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (!IsSet) IgnoreOracleError (2289,FALSE);
              }
  #else
            if (!error) {
              // eventuell vorhandenes Synonym auf CTEMP_... loeschen
              LPSTR SynTab = ORAGetTableName (tnew,TRUE);
              DropSynonym (SynTab);
              // eventuell CTEMP_..._TRIGGER loeschen
              DeleteTrigger(h,tnew);
              LongString s1,s2;
              s.Clear ();
              s1.Clear ();
              s2.Clear ();
              s = s + "RENAME " + ORAGetTableName (tnew,TRUE) + " TO " ;
              s1 = s1 + "RENAME " + SName (ORAGetTableName (tnew,FALSE)) + " TO " ;
              MarkTableFromINTName (NULL);
              s = s + ORAGetTableName (tnew,TRUE);
              s1 = s1 + SName (ORAGetTableName (tnew,FALSE));
              s2 = s2 + "DROP SEQUENCE " + SName (ORAGetTableName (tnew,FALSE));
              if (h->execute (s.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
              if (NewAuto) {
                h->execute (s2.Ptr(),NULL);  // alte Sequence loeschen
                if (h->execute (s1.Ptr(),NULL) != CS_SUCCEED) error = TRUE ;
                // die Schluessel gibts in diesem Fall schon
                }
              else {
                if (!CreateAllIndex (tnew)) error = TRUE ;
                }
              }
  #endif

            delete h ;
            MarkTableFromINTName (NULL);
            }
          }
          break ;
        }

      LPSTR SynTab = ORAGetTableName (tnew,TRUE);
      DoSynonym (SynTab,SynTab,"INSERT,UPDATE,DELETE,SELECT");
      UserOrb (SynTab);
      LPSTR SynSeq = GetSequenceName (tnew);
      DoSynonym (SynSeq,SynSeq,"SELECT");
      UserOrb (SynSeq);
      }

    _inAlter = FALSE ;

    }  // wenn ORACLE_Check=Orbis, dann in ORBIS-Version nichts machen

  if (!error) {
    // DoBeginTransaction (FALSE);
    BeginTransaction (FALSE);
    return DBCALL_SUCCESS;
    }
  else
    return DBCALL_ERROR;
  }

//--------------------------------------------------------------------------
//
// Arbeiten mit Packages
//
//--------------------------------------------------------------------------
extern DLLExport LPSTR _export WINAPI makeIni (LPSTR name);
GLOBALHANDLE ReadPackageFile ()
  {
  LPSTR fName = makeIni ("clpack.txt");
  OFSTRUCT Of;
  HFILE f = OpenFile (fName,&Of,OF_READ);
  GLOBALHANDLE res;
  if (f > 0) {
    DWORD Size = _llseek (f,0L,SEEK_END);
    WIN_ASSERT (Size < 0xFFFF);
    res = GlobalAlloc (GMEM_MOVEABLE,Size + 1);
    LPSTR Buffer = LPSTR (GlobalLock (res));
    _llseek (f,0L,SEEK_SET);
    _hread (f,Buffer,Size);
    Buffer[Size] = '\0' ;
    GlobalUnlock (res);
    _lclose (f);
    }
  else
    res = NULL ;
  return res;
  }

extern BOOL myIsCharAlpha(char ch);
struct AliasElem {
  AliasElem FAR *Next;
  LPSTR TableName;
  LPSTR AliasName;
  };
AliasElem FAR *top;
void PushAliasName (LPSTR TableName,LPSTR TableEnd,LPSTR AliasName,LPSTR AliasEnd)
  {
  LPSTR tn = LPSTR (GetGlobMem (TableEnd - TableName + 1));
  lmemcpy (tn,TableName,TableEnd - TableName) ;
  LPSTR an = LPSTR (GetGlobMem (AliasEnd - AliasName + 1));
  if (AliasEnd > AliasName)
    lmemcpy (an,AliasName,AliasEnd - AliasName) ;
  AliasElem FAR *ae = (AliasElem FAR *) GetGlobMem (sizeof(*ae));
  ae->TableName = tn;
  ae->AliasName = an;
  ae->Next = top;
  top = ae;
  }

void FreeAliasList ()
  {
  for ( ; top != NULL ; ) {
    AliasElem FAR *ae = top->Next ;
    FreeGlobMem (top->TableName);
    FreeGlobMem (top->AliasName);
    FreeGlobMem (top);
    top = ae ;
    }
  }

LPSTR GetAliasName (LPSTR h,LPSTR FAR &TableName,LPSTR FAR &AliasName)
  {
  for (AliasElem FAR *ae = top ; ae != NULL ; ae = ae->Next) {
    if (mystrcmp (h,ae->AliasName)) {
      if (lstrlen (ae->AliasName) > 0) {
        AliasName = ae->AliasName ;
        h += lstrlen (ae->AliasName) + 1;
        }
      else
        AliasName = '\0' ;
      TableName = ae->TableName ;
      return h ;
      }
    }
  WIN_ASSERT (FALSE);
  return h ;
  }

LPSTR SkipComment (LPSTR h) 
  {
  LPSTR start = h ;
  for ( ; (*h == ' ') ; h++ ) ;
  if ((*h == '/') && (h[1] == '*')) {
    h += 2 ;
    for ( ; ((*h) && (*h != '\r') && (!((h[0] == '*') && (h[1] == '/')))) ; h ++ ) ;
    if ((h[0] == '*') && (h[1] == '/')) h += 2 ;
    return h ;
    }
  else
    return start ;
  }
LPSTR TypeName (char parStart) 
  {
  switch (parStart) {
    case 'I' :
      return "INT" ;
    case 'F' :
      return "REAL" ;
    case 'S' :
      return "VARCHAR2" ;
    case 'T' :
      return "LONG" ;
    case 'M' :
      return "LONG RAW" ;
    default :
      WIN_ASSERT (FALSE) ;
    }
  return NULL ;
  }

extern char ActUserName[256];
BOOL CreatePackage ()
  {
  BOOL error = FALSE ;
  GLOBALHANDLE hGmem = ReadPackageFile ();
  if (hGmem) {
    // 1. Parsen des Textes zum Erzeugen der Record - Typen
    LPSTR Buffer = LPSTR (GlobalLock (hGmem));
    BOOL first = TRUE ;
    LongString s;
    for (LPSTR h = Buffer ; ; ) {
      LPSTR LineStart = h ;
      // Parsen bis zum Doppelpunkt
      for ( ; ((*h) && (*h != ':')) ; h++) ;
      if (*h != ':') {
        break ;
        }
      if (first)
        s = s + "CREATE OR REPLACE PACKAGE CLINICUM AS " ;
      first = FALSE ;
      LPSTR procEnd = h ;
      s = s + "TYPE " + PartString (LineStart,procEnd - LineStart) + "_RECORD IS RECORD (" ;
      h ++ ;
      // Suchen der From Klausel
      for ( ; ((*h) && (*h != '\r') && (!mystrcmp (h,"FROM"))) ; h ++ ) ;
      if (!mystrcmp (h,"FROM")) {
        error = TRUE ;
        break ;
        }
      h += 4 ;  // Skippen von "FROM"

      // Aufstellen einer Alias - Liste
      for ( ; (!myIsCharAlpha (*h)) ; h++) ;
      for ( ; ((*h) && (*h != '\r') && (!mystrcmp (h,"WHERE"))) ; ) {
        for ( ; (!myIsCharAlpha (*h)) ; h++) ;
        // Jetzt kommt der Tabellenname
        LPSTR TableName = h ;
        for ( ; (myIsCharAlpha (*h)) ; h++) ;
        LPSTR TableEnd = h ;
        for ( ; (!myIsCharAlpha (*h)) ; h++) ;
        if ((mystrcmp (h,"WHERE")) || (*h == '\0') || (*h == '\r')) {
          // Es handelts sich um eine Einzeltabelle
          PushAliasName (TableName,TableEnd,h,h);
          }
        else {
          LPSTR AliasStart = h ;
          for ( ; (myIsCharAlpha (*h)) ; h++) ;
          PushAliasName (TableName,TableEnd,AliasStart,h);
          }
        for ( ; ((!myIsCharAlpha (*h)) && (*h != '\r')) ; h++) ;
        }

      // Das ganze nochmal von vorne um die richtigen Datentypen fuer den Record aufzustellen
      for (h = procEnd + 1 ; ((*h) && (*h != '\r') && (!mystrcmp (h,"SELECT"))) ; h++) ;
      if (!mystrcmp (h,"SELECT")) {
        error = TRUE ;
        break ;
        }

      h += lstrlen ("SELECT") ; 
      for ( BOOL firstVar = TRUE ; ; ) {
        h = SkipComment (h);
        for ( ; (!myIsCharAlpha (*h)) ; h ++ ) ;
        if (mystrcmp (h,"FROM")) break ;
        LPSTR TableName,AliasName;
        h = GetAliasName (h,TableName,AliasName);
        LPSTR VarName = h ;
        for ( ; (myIsCharAlpha (*h)) ; h++ ) ;
        if (!firstVar) s = s + "," ;
        if (AliasName)
          s = s + AliasName + "_" ;
        s = s + PartString (VarName,h - VarName) + " " + ActUserName + "." + TableName + "." + 
                PartString (VarName,h - VarName) + "%TYPE" ;
        firstVar = FALSE ;
        }
      if (!mystrcmp (h,"FROM")) {
        error = TRUE ;
        break ;
        }
      s = s + "); " ;

      // Erzeugen des Cursor - Typs
      s = s + "TYPE " + PartString (LineStart,procEnd - LineStart) + 
              "_CURSOR IS REF CURSOR RETURN " + PartString (LineStart,procEnd - LineStart) + 
              "_RECORD; " ;

      // Zusammenstellen Funktionsprototypen
      s = s + "PROCEDURE " + PartString (LineStart,procEnd - LineStart) + 
          " (cur IN OUT " + PartString (LineStart,procEnd - LineStart) + 
          "_CURSOR" ;
      for (h = procEnd + 1 ; ((*h) && (*h != '\r')) ; h ++ ) {
        if (*h == ':') {
          h ++ ;
          LPSTR parStart = h ;
          for ( ; (myIsCharAlpha(*h)) ; h ++ ) ;
          s = s + ",P" + PartString (parStart,h - parStart) + " IN " + TypeName(*parStart) ;
          }
        }
      s = s + "); " ;

      // Freigeben der Aliasliste
      FreeAliasList ();

      // Zeile fertig
      //------------------
      for ( ; ((*h == '\r') || (*h == '\n')) ; h++) ;
      }
    s = s + "END CLINICUM;" ;
    if (error) return FALSE ;

    // 2. Package erzeugen
    sybstmt *stmt = new sybstmt ();
    error = (stmt->execute (s.Ptr(),NULL) != CS_SUCCEED) ;
    s.Clear();
    delete stmt;
    if (error) return FALSE ;

    // 3. Parsen des Textes zum Erzeugen des Package - Bodys
    first = TRUE ;
    for (h = Buffer ; ; ) {
      LPSTR LineStart = h;
      // Parsen bis zum Doppelpunkt
      for ( ; ((*h) && (*h != ':')) ; h++) ;
      if (*h != ':') {
        break ;
        }
      LPSTR procEnd = h ;
      if (first)
        s = s + "CREATE OR REPLACE PACKAGE BODY CLINICUM AS " ;
      first = FALSE ;
      s = s + "PROCEDURE " + PartString (LineStart,procEnd - LineStart) + 
          " (cur IN OUT " + PartString (LineStart,procEnd - LineStart) + 
          "_CURSOR" ;
      // Zusammenstellen des Funktionsprototypen
      for (h = procEnd + 1 ; ((*h) && (*h != '\r')) ; h ++ ) {
        if (*h == ':') {
          h ++ ;
          LPSTR parStart = h ;
          for ( ; (myIsCharAlpha(*h)) ; h ++ ) ;
          s = s + ",P" + PartString (parStart,h - parStart) + " IN " + TypeName(*parStart) ;
          }
        }
      s = s + ") IS BEGIN OPEN cur FOR " ;
      // Alle ':' durch 'P' ersetzten
      for (h = procEnd + 1 ; ((*h) && (*h != '\r')) ; h ++ )
        if (*h == ':') *h = 'P' ;
      s = s + PartString (procEnd + 1,h - (procEnd + 1)) + "; END; " ;
      // Zeile fertig
      //------------------
      for ( ; ((*h == '\r') || (*h == '\n')) ; h++) ;
      }
    
    // 4. Erzeugen des Package - Bodys
    s = s + "END CLINICUM;" ;
    stmt = new sybstmt ();
    error = (stmt->execute (s.Ptr(),NULL) != CS_SUCCEED) ;
    s.Clear();
    delete stmt;
    if (error) return FALSE ;

    // fertig
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    }
  return !error ;
  }

void DropPackage ()
  {
  CheckFile (NULL,FALSE,TRUE);
  sybstmt *stmt = new sybstmt ();
  BOOL IsSet = IgnoreOracleError (4043,TRUE);
  stmt->execute ("DROP PACKAGE CLINICUM",NULL);
  if (!IsSet) IgnoreOracleError (4043,FALSE);
  delete stmt;
  }

hash FAR *procHash;
void ReadStmts ()
  {
  GLOBALHANDLE hGmem = ReadPackageFile ();
  if (hGmem) {
    for (LPSTR h = LPSTR (GlobalLock (hGmem)) ; *h ; ) {
      LPSTR procStart = h ;
      for ( ; ((*h) && (*h != ':')) ; h ++ ) ;
      if (*h != ':') break ;
      *h = '\0' ;
      h ++ ;
      LPSTR stmtStart = h ;
      for ( ; ((*h) && (*h != '\r') && (*h != '\n')) ; h++) ;
      BOOL doContinue ;
      if ((*h == '\r') || (*h == '\n')) doContinue = TRUE ;
      else                              doContinue = FALSE ;
      *h = '\0';
      procHash->SetData (stmtStart,procStart,lstrlen(procStart) + 1);
      if (doContinue) {
        h++ ;
        for ( ; ((*h == '\r') || (*h == '\n')) ; h++) ;
        }
      else
        break ;
      }
    GlobalUnlock (hGmem);
    GlobalFree (hGmem);
    }
  }

LPSTR ProcName (LPSTR Stmt)
  {
  if (procHash == NULL) {
    procHash = new hash (237,STRKEY);
    ReadStmts ();
    }
  return LPSTR (procHash->GetData (Stmt));
  }

