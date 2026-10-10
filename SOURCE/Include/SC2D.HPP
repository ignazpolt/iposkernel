#ifndef SCALE_INCLUDED
#define SCALE_INCLUDED
/*-----< Representierung einer Transformationsmatrix >------*/
struct FAR tr2 {
  float A[2][2];
  float B[2];
  };
// $Header:   P:/marille/clinicum/include/rev/sc2d.hpv   1.2   02 Feb 1996 11:00:12   GERHOLD  $
// $Log:   P:/marille/clinicum/include/rev/sc2d.hpv  $
// 
//    Rev 1.2   02 Feb 1996 11:00:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   24 Jun 1994 19:18:34   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.1   02 Feb 1993 19:09:04   MARTIN
// Prototyp fuer CalcLinTrans eingefuegt
// 
//    Rev 1.0   02 Dec 1992 16:04:24   HANNES
// Initial revision.

/*-------< Funktionen zur Arbeit mit Transformationsmatrizen >------*/
DLLExport void _export WINAPI Sc2d (tr2 FAR *,fpt FAR *,fpt FAR *);
DLLExport void _export WINAPI CalcSc2d (tr2 FAR *,fpt FAR *,fpt FAR *,BOOL Normalize = FALSE);
DLLExport void _export WINAPI Stretch2d (tr2 FAR *,double);
DLLExport void _export WINAPI Stretch2dy (tr2 FAR *,double);
DLLExport void _export WINAPI InvSc2d (tr2 FAR *);
DLLExport void _export WINAPI Combine2d (tr2 FAR *,tr2 FAR *,tr2 FAR *);
DLLExport void _export WINAPI MScale2d (tr2 FAR *,fpt FAR *,fpt FAR *,fpt FAR *,fpt FAR *,BOOL Normalize = TRUE,double f = 1.0);
DLLExport void _export WINAPI CalcLinTrans (tr2 FAR *sc,fpt FAR *p0,double dx,double dy,double phi);
#endif
