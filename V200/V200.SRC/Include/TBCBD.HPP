//  Callbackdaten fuer das ctool ...
//
// $Header:   P:/marille/clinicum/include/rev/tbcbd.hpv   1.4   02 Feb 1996 11:00:50   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/tbcbd.hpv  $
// 
//    Rev 1.4   02 Feb 1996 11:00:50   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.3   05 Apr 1995 16:13:16   HANNES
// 
//    Rev 1.2   04 Apr 1995 12:09:40   HANNES
// 
//    Rev 1.1   31 Mar 1995 13:11:58   HANNES
//  
// 
//    Rev 1.0   27 Mar 1995 13:17:42   HANNES
// Initial revision.
//
class toolbar_cbdata {
 public :
  mdiChild *c;
  LPCONNEXTRAINFO Extra;
  toolbar_cbdata (mdiChild *mc)
    {
    c = mc ;
    LPCONNEXTRAINFO x = mc->_GetRecExtra () ;
    if (x != NULL) {
      Extra = LPCONNEXTRAINFO (GetGlobMem (GetBlockSize(x)));
      lmemcpy (Extra,x,GetBlockSize(x));
      }
    else
      Extra = NULL;
    }
  };
typedef toolbar_cbdata FAR *LPTBD;


