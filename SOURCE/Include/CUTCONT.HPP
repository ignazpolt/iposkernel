//////////////////////////////////////////////
//  Deklarationen fuer geschnitte Konturen  //
//////////////////////////////////////////////
// $Header:   P:/marille/clinicum/include/rev/cutcont.hpv   1.4   10 Apr 1997 11:13:54   Martin  $
// $Log:   P:/marille/clinicum/include/rev/cutcont.hpv  $
// 
//    Rev 1.4   10 Apr 1997 11:13:54   Martin
// 32-bit-isiert
// 
//    Rev 1.3   02 Feb 1996 10:59:44   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.2   20 Mar 1995 12:16:02   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.1   24 Jun 1994 19:19:04   MARTIN
// Frmobject in DLL
// 
//    Rev 1.0   19 Apr 1993 01:30:18   MARTIN
// Initial revision.
// 

// grobe Struktur einer geschnittenen Kontur:
// * eine Kontur besteht aus einem oder mehreren Konturteilen;
//   bei zusammengehoerdenden Konturen (z.B Mandibula und Symphyse)
//   muessen entsprechende Teile in jeder Kontur die selbe Nummer haben
// * ein Konturteil besteht aus einem oder mehreren Konturstuecken
// * ein Konturstueck besteht aus einer Liste von Punkten
// * zusaetzlich werden noch Verbindungen zwischen verschiedenen Teilen
//   gespeichert, die angeben wo ein Konturstueck durch einen Schnitt
//   getrennt wurde

// Definitionen fuer boneside:
#define BS_CC_UNKNOWN   0
#define BS_CC_LEFT      1
#define BS_CC_RIGHT     2

#pragma pack(1)
struct cont_part {    // Konturteil
  short part_num;     // Nummer des Teiles
  short bone_side;    // auf welcher Seite des Konturteiles liegt Knochen ?
  short num_pieces;   // Anzahl der Stuecke dieses Teiles
  };                  // (die Stuecke folgen gleich im Anschluss)

struct cont_piece {   // Konturstueck
  short ptind_from;   // Stueck geht von Punkt Nr.
  short ptind_to;     // nach Punkt Nr.
  };

struct cont_link {    // Verbindung zwischen zwei Teilen
  short part_from;    // von Teil Nr.
  short ptind_from;   // von Punkt Nr.
  short part_to;      // nach Teil Nr.
  short ptind_to;     // nach Punkt Nr.
  };

struct cut_cont {     // geschnittene Kontur
  fpt invalid;  // wenn > 1.0E9 und BlockSize > sizeof(fpt) -> geschnitten
  short num_org_pts;
  short num_parts;
  short num_pieces;
  short num_links;
  short num_pts;
  // free:
  // { cont_part { cont_piece } } { cont_links } { fpts }
  };
#pragma pack()

typedef cont_part FAR *LPCONTPART;
typedef cont_piece FAR *LPCONTPIECE;
typedef cont_link FAR *LPCONTLINK;
typedef cut_cont FAR *LPCUTCONT;

DLLExport BOOL _export WINAPI is_cut(fpt FAR *cont);
DLLExport fpt FAR * _export WINAPI get_cont(fpt FAR *cont, int FAR *PtCount);

