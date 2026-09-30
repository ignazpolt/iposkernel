//
//      Kontur - Bearbeitungs - Funktionen
//
// $Header:   P:/marille/clinicum/include/rev/cont.hpv   1.4   21 Apr 1998 19:30:10   Hannes  $
// $Log:   P:/marille/clinicum/include/rev/cont.hpv  $
// 
//    Rev 1.4   21 Apr 1998 19:30:10   Hannes
// contclip in frmobj verlagert
// 
//    Rev 1.3   19 Nov 1997 18:45:26   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.2   02 Feb 1996 10:59:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   20 Mar 1995 12:07:30   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.0   24 Jun 1994 17:01:04   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.6   23 Feb 1994 18:23:16   HANNES
// Polinom Interpolation, Cosinus - Hyperbolicus Interpolation
// 
//    Rev 1.5   02 Jun 1993 22:21:10   MARTIN
// turnpt
// 
//    Rev 1.4   25 May 1993 15:34:10   MARTIN
// conn_cont korrigiert
// 
//    Rev 1.3   24 May 1993 14:31:44   MARTIN
// connect_cont
// 
//    Rev 1.2   05 May 1993 12:19:08   MARTIN
// esttang
// 
//    Rev 1.1   02 Apr 1993 18:04:08   HANNES
// contmcross
// 
//    Rev 1.0   02 Dec 1992 15:52:38   HANNES
// Initial revision.


GLOBALHANDLE smooth_cont (fpt FAR *,int,int,double,float FAR *P = NULL);
GLOBALHANDLE smextcont (fpt FAR *,int,int,double,double,double,int,LPFPT *);
GLOBALHANDLE combine_cont (LPFPT *,int,int,double);
GLOBALHANDLE connect_cont (LPFPT *,int,int FAR *);
void contmax (fpt FAR *,fpt FAR *,fpt FAR *,fpt FAR *);
void contcro (fpt FAR *,fpt FAR *,fpt FAR *,fpt FAR *,int);
void contmaxang (fpt FAR *,fpt FAR *,fpt FAR *,fpt FAR *,int);
void contnea (fpt FAR *,fpt FAR *,fpt FAR *);
void esttang (fpt FAR *,fpt FAR *,fpt FAR *,fpt FAR *);
void turnpt (fpt FAR *,fpt FAR *,fpt FAR *,int);
void contmcro (fpt FAR *res,fpt FAR *cont,fpt FAR *p1,fpt FAR *p2,fpt FAR *dir);
DLLExport fpt FAR * _export WINAPI contclip (fpt FAR *cnt,fpt FAR *p1,fpt FAR *p2);
BOOL ptincont (fpt FAR *cont,fpt FAR *p);

struct KoefDesc {
  int potenz;
  double val;
  };

DLLExport BOOL _export WINAPI SolveEquSys (double FAR *a,double FAR *b,double FAR *res);
DLLExport void _export WINAPI GetPolintKoeff(float FAR *x, float FAR *y, int Anz, KoefDesc FAR *Kx);
DLLExport void _export WINAPI polint_parametric(fpt FAR *pts, KoefDesc FAR *Kx, KoefDesc FAR *Ky);
DLLExport void _export WINAPI GetPolCnt (fpt FAR *cnt,int Anz,double xmin,double xmax,KoefDesc FAR *k);
DLLExport void _export WINAPI GetPolCnt (fpt FAR *cnt,int Anz,double tmin,double tmax,KoefDesc FAR *kx,KoefDesc FAR *ky);

struct KLParam {
  double a,b,c;
  double xmin,xmax;
  double ymin,ymax;
  };

DLLExport void _export WINAPI KettenlinienInterpolation (fpt FAR *p,int anz,double FAR *a,double FAR *b,double FAR *c,double direction);
DLLExport void _export WINAPI GetKettenLinie (fpt FAR *cnt,int Anz,KLParam FAR *p);


