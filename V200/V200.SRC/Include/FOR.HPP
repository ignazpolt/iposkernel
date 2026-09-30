/////////////////////////////////////////////////////////////////////////
//  for.hpp Strukturen, die im Zusammenhang mit Listen benoetigt werden
/////////////////////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/include/rev/for.hpv   1.2   21 Oct 1996 18:53:56   HANNES  $
//  $Log:   P:/marille/clinicum/include/rev/for.hpv  $
// 
//    Rev 1.2   21 Oct 1996 18:53:56   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.1   02 Feb 1996 11:00:52   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   20 Mar 1995 12:07:44   HANNES
// Initial revision.
//
struct InnerListDesc {
  RecordList FAR *list;
  WORD TableId;
  LPTABLEDEF td;
  short TableInd;
#ifdef LIST_MAIN
  ListObj FAR *lo;
#else
  LPVOID FAR *lo;
#endif
  };
typedef InnerListDesc FAR *LPINNERLISTDESC;

