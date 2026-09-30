//////////////////////////////////////////////////////////////
//  Datenbankdefinition der Recall - Datei
//////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/include/rev/recall.hpv   1.1   02 Feb 1996 11:00:10   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/recall.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:00:10   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:56   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.6   04 Jan 1994 17:11:32   HANNES
// Umstellung der Struktur der Recall - Datenbank...
// 
//    Rev 1.5   09 Dec 1993 15:06:24   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.4   05 Sep 1993 22:10:16   HANNES
// 
//    Rev 1.3   06 Jul 1993 14:01:32   HANNES
// Verarbeitung des variablen Teiles der Recall Daten
// 
//    Rev 1.2   05 Jul 1993 14:51:24   HANNES
// Handling des Variablen Teiles
// 
//    Rev 1.1   23 Jun 1993 11:21:00   HANNES
// CheckRecall
// 
//    Rev 1.0   02 Jun 1993 19:40:06   HANNES
// Initial revision.
//

//////////////////////////////////////////////////////////
//  Block - Struktur - Handling
//////////////////////////////////////////////////////////
struct FAR SubInfo {
  WORD Ident;
  WORD Length;
  };
DLLExport SubInfo FAR *_export WINAPI Get(LPVOID Data,WORD Ident);

typedef SubInfo FAR *LPSUBINFO;
typedef LPSUBINFO FAR *LPSIARR;
struct FAR SubBlock {
  WORD Length;
  SubInfo s;

  DLLExport int _export WINAPI AnalyseSubBlock (LPSIARR s,int MaxAnz);
  };

DLLExport SubBlock FAR *_export WINAPI Add (SubBlock FAR *act,SubInfo FAR *si);
DLLExport SubBlock FAR *_export WINAPI Add (SubBlock FAR *act,LPVOID Data,WORD Ident);


struct FAR ExtraInfo {
  BYTE Type;
  SubBlock b;

  ExtraInfo FAR *Next()
    { return (ExtraInfo FAR *) (LPSTR(this) + b.Length + sizeof(Type)); }
  };

#define DMW_RECALLPARAMETER   1
struct FAR VarBlock {
  WORD Length;
  ExtraInfo e;

  DLLExport ExtraInfo FAR *_export WINAPI Get(BYTE Type);
  DLLExport BOOL _export WINAPI Insert (ExtraInfo FAR *x,int BufferSize = -1);
  DLLExport BOOL _export WINAPI Insert (SubBlock FAR *s,BYTE Type,int BufferSize = -1);
  DLLExport void _export WINAPI Remove (BYTE Type);
  };

