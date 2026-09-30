//////////////////////////////////////////////////////////
//  Funktionen zur Konstruktion von Punkten
//////////////////////////////////////////////////////////
//
//  $Header:   P:/marille/clinicum/include/rev/reconst.hpv   1.1   02 Feb 1996 10:59:18   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/reconst.hpv  $
// 
//    Rev 1.1   02 Feb 1996 10:59:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:58   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   15 Nov 1993 14:03:56   HANNES
// Initial revision.
//
//
typedef fpt FAR *LPFPT;
typedef float FAR *LPFLOAT;
typedef BOOL FAR *LPBOOL;

DLLExport void _export WINAPI GetThirdPt (LPFPT p1,LPFPT p2,LPFPT p3,LPFLOAT l1,LPFLOAT l2,LPBOOL right);
DLLExport void _export WINAPI GetNAbstPt (LPFPT p1,LPFPT p2,LPFPT p3,LPFPT p4,LPFLOAT a1,LPFLOAT a2);
DLLExport void _export WINAPI GetRotPt   (LPFPT p1,LPFPT p2,LPFPT p3,LPFLOAT l,LPFLOAT phi);
DLLExport void _export WINAPI GetMidPts (LPFPT pg1,LPFPT pg2,LPFPT pm1,LPFPT pm2,
                                   LPFPT pl11,LPFPT pl12,LPFPT pl21,LPFPT pl22,
                                   LPFLOAT lpdy,LPFLOAT lpc,LPFPT r1,LPFPT r2);

