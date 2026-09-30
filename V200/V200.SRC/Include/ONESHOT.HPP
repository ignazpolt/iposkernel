//////////////////////////////////////////////////////
//  Verzoegertes Ausloesen einer Funktion
//////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/oneshot.hpv   1.3   21 Oct 1997 08:33:28   Martin  $
//  $Log:   P:/marille/clinicum/include/rev/oneshot.hpv  $
// 
//    Rev 1.3   21 Oct 1997 08:33:28   Martin
// Extradatenberuecksichtigung
// 
//    Rev 1.2   02 Feb 1996 11:00:08   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.1   19 Oct 1994 22:35:44   hannes
// Erweiterung oneshot
// 
//    Rev 1.0   24 Jun 1994 17:01:54   HANNES
// Neuuebernahme clinicum
//
typedef VOID (WINAPI * DELAYEDCALL) (LPVOID CallBackData,LPVOID Extra);

void SetOneShot (int delay,DELAYEDCALL func,LPVOID data,int dSize,int Multiply = 0,LPVOID edc = NULL);
BOOL CheckTimer (WORD wP);
void RemoveShot (LPVOID data,int dSize);
void CheckControlAction (MSG FAR *m);


