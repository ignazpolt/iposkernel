///////////////////////////////////////
//  Dynamisches Linken
///////////////////////////////////////
#ifndef DYNALINK_INCLUDED
#define DYNALINK_INCLUDED

class FAR dynalink {
 private :
  char fname[13];
 public :
  hash FAR *ProcHash;
  GLOBALHANDLE hGExtCommands;
  LPSTR ExtBase;

  dynalink () { };
  ~dynalink () { 
    if (hGExtCommands) { GlobalUnlock (hGExtCommands) ; GlobalFree (hGExtCommands) ; }
    if (ProcHash != NULL) delete ProcHash;
    }
  BOOL Load(LPSTR fn);
  DWORD GetProcAddr (LPSTR Name);
  LPVOID operator new (size_t size)
    { return GetGlobMem (size); }
  void operator delete (LPVOID obj)
    { FreeGlobMem (obj); }
  };

#endif
