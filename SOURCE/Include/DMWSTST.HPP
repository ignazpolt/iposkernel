///////////////////////////////////////////////////////
//  Defines, Prototypen fuer Zusammenspiel der
//  Testutility mit der Marille
///////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/dmwstst.hpv   1.1   02 Feb 1996 11:01:14   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/dmwstst.hpv  $
// 
//    Rev 1.1   02 Feb 1996 11:01:14   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.0   24 Jun 1994 17:01:16   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.0   13 Apr 1994 14:38:10   HANNES
// Initial revision.
//
#define WMU_GETDOCFIRSTNMBR   WM_USER+0x1000    // wP = 0, lP = 0
    // return:  DokumentNummer bei Erfolg
    //          < 0 im Fehlerfall
#define WMU_GETDOCNEXTNMBR    WM_USER+0x1001    // wP = 0, lP = Letzte Dokumentnummer
    // return:  DokumentNummer bei Erfolg
    //          < 0 im Fehlerfall
#define WMU_GETDOCTYPE        WM_USER+0x1002    // wP = 0, lP = Dokumentnummer
#define TST_DOCTYPE_DSLIST      0
#define TST_DOCTYPE_NODSLIST    1
#define TST_DOCTYPE_EXTRA       2
    // return:  TST_DOCTYPE_DSLIST   ... normales Dokument (mit Datensatzliste)
    //          TST_DOCTYPE_NODSLIST ... normales Dokument (ohne Datensatzliste)
    //          TST_DOCTYPE_EXTRA    ... Hilfsdokument (nicht aufrufbar)
    //          < 0 im Fehlerfall
#define WMU_OPENDOC           WM_USER+0x1003    // wP = 0, lP = Dokumentnummer
    // return:  ... keine Bedeutung
#define WMU_DOCDATAEXIST      WM_USER+0x1004    // wP = 0, lP = Dokumentnummer
#define TST_DOCDATA_NONE      0
#define TST_DOCDATA_EXIST     1
    // Funktion wird nur fuer Dokumente des Types 0 aufgerufen
    // return:  TST_DOCDATA_NONE  ... Keine Daten -> Keine Datensatzliste
    //          TST_DOCDATA_EXIST ... Daten -> Datesatzliste
    //          < 0 im Fehlerfall
#define WMU_GETTSTLIST        WM_USER+0x1005    // wP = Dokumentnummer
                                                // lP = Adresse des Strings, muss mind. 512 Byte lang sein
    // Funktion liefert die Namen der Testmodule, mit denen das
    // Dokument getestet werden soll
    // return: Anzahl Zeichen, die gelesen wurden


LONG TestToolFunc (unsigned msg, WORD wP,LONG lP);

