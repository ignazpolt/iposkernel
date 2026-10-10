//////////////////////////////////////////////////////////////////////
//  Klasse TableDifference
//  Vergleich von Tabellendefinitionen
//////////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/tbdiff.hpv   1.1   30 Mar 1998 20:27:54   Hannes  $
//  $Log:   P:/marille/clinicum/include/rev/tbdiff.hpv  $
// 
//    Rev 1.1   30 Mar 1998 20:27:54   Hannes
// t0,t1,SameIDs
// 
//    Rev 1.0   26 Nov 1996 08:08:50   HANNES
// Initial revision.
struct _v2v {
  short vFrom;
  short vTo;
  };

class FAR TableDifference {
 private :
  LPTABLEDEF t0,t1;
 public :
  _v2v FAR *v2v;
  short FAR *Modified;
  short FAR *VarsToAdd;
  short FAR *VarsToDrop;
  short FAR *KeysToAdd;
  short FAR *KeysToDrop;

  int AnzVarsToCopy ()
    {
    return GetBlockSize (v2v) / sizeof(*v2v) ; 
    }
  int AnzModified ()
    {
    return GetBlockSize (Modified) / sizeof(*Modified);
    }
  int AnzVarsToAdd ()
    {
    return GetBlockSize (VarsToAdd) / sizeof(*VarsToAdd);
    }
  int AnzVarsToDrop ()
    {
    return GetBlockSize (VarsToDrop) / sizeof(*VarsToDrop);
    }
  int AnzKeysToAdd ()
    {
    return GetBlockSize (KeysToAdd) / sizeof(*KeysToAdd);
    }
  int AnzKeysToDrop ()
    {
    return GetBlockSize (KeysToDrop) / sizeof(*KeysToDrop);
    }
  BOOL IsToAdd (short n)
    {
    int j = AnzVarsToAdd() ;
    for (int i = 0 ; i < j ; i++)
      if (VarsToAdd[i] == n) return TRUE ;
    return FALSE ;
    }
  BOOL IsToCopy (short n)
    {
    int j = AnzVarsToCopy() ;
    for (int i = 0 ; i < j ; i++)
      if (v2v[i].vFrom == n) return TRUE ;
    return FALSE ;
    }
  DLLExport _export WINAPI ~TableDifference ();
  DLLExport BOOL _export WINAPI SameSort ();
  DLLExport BOOL _export WINAPI SameIDs ();
  DLLExport BOOL _export WINAPI NoDifference ();
  LPVOID operator new (size_t size)
    {
    return GetGlobMem (size);
    }
  void operator delete (LPVOID obj)
    {
    FreeGlobMem (obj);
    }
  DLLExport short _export WINAPI VarIDFrom (short VarIDTo);
  DLLExport BOOL _export WINAPI TableDifference::IsToModify (short vTo);
  DLLExport BOOL _export WINAPI IsSameKey (LPTABLEDEF t1,LPTABLEDEF t2,int KeyNmbr,BOOL FAR *doStop,BOOL FAR *r1Found,BOOL FAR *r2Found);
  DLLExport _export WINAPI TableDifference (LPTABLEDEF told,LPTABLEDEF tnew,
                        WORD PropFilter,WORD KPropFilter
                  );
  };

DLLExport void _export WINAPI InitializeDefVal (DefVal FAR *dv,int AnzDefs,LPTABLEDEF tnew);
DLLExport LPDBRECORD _export WINAPI ConvertRecord (LPTABLEDEF tnew,LPDBRECORD h,TableDifference FAR *td,int AnzDefs,DefVal FAR *dv);

