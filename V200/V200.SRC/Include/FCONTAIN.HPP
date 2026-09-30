//
// $Header:   P:/marille/clinicum/include/rev/fcontain.hpv   1.1   27 Apr 1998 12:51:04   Hannes  $
// $Log:   P:/marille/clinicum/include/rev/fcontain.hpv  $
// 
//    Rev 1.1   27 Apr 1998 12:51:04   Hannes
// Erweiterungen fuer die HashTabelle
// 
//    Rev 1.0   21 Apr 1998 19:30:58   Hannes
// Containerdefinition
//
#pragma pack(1)
struct ContainElem {
  short DatenGroesse;
  DWORD KennNummer;
  DWORD HNr0;
  short HNr1;
  packdate pd;
  packtime pt;
  char Daten[1];
  };

struct SortContainElem {
  DWORD HNr0;
  short HNr1;
  packdate pd;
  packtime pt;
  short DatenGroesse;
  char Daten[1];
  };

#pragma pack()
