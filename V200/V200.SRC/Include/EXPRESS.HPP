//////////////////////////////////////////////////////////////
//      Funktionsprototypen zur Erzeugung von Expressions
//////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/express.hpv   1.2   16 Feb 2000 15:02:42   Wolfgang  $
//  $Log:   P:/marille/clinicum/include/rev/express.hpv  $
// 
//    Rev 1.2   16 Feb 2000 15:02:42   Wolfgang
// 1.) Prototyp fuer SetExpArgT neu.
// 
//    Rev 1.1   02 Feb 1996 10:59:54   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:49:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   24 May 1993 14:27:50   HANNES
// Initial revision.
void setbinop (void);
void setexpfnc (void);

void createconstnode (void);
void createparnode (void);
void createvarnode (void);
void createopnode (void);
void createfncnode (void);

void pushexpression (void);
void popexpression (void);
void poppush (void);

void SetExpArg ();
void SetExpArgT (BYTE t);
void StoreResTyp ();
void makecmplt ();
void defoparg ();
void defopres ();
void CheckAnzOPArgs();

void pushparexpression (void);
void matchexpression (void);
void copyExpRes ();
