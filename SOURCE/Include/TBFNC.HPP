////////////////////////////////////////////////////////////////
//  Funktionen zum Arbeiten mit Datenbanken
////////////////////////////////////////////////////////////////
//  $Header:   P:/marille/clinicum/include/rev/tbfnc.hpv   1.6   02 Feb 1996 11:01:18   GERHOLD  $
//  $Log:   P:/marille/clinicum/include/rev/tbfnc.hpv  $
// 
//    Rev 1.6   02 Feb 1996 11:01:18   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   09 Dec 1994 19:44:04   HANNES
// 
//    Rev 1.4   08 Dec 1994 22:05:16   HANNES
// 
//    Rev 1.3   19 Oct 1994 22:31:20   hannes
// 
//    Rev 1.2   05 Aug 1994 17:17:50   HANNES
// 
//    Rev 1.1   17 Jul 1994 14:40:26   HANNES
// Umorganisation der Primaerschluesselvergabe
// 
//    Rev 1.0   24 Jun 1994 17:01:28   HANNES
// Neuuebernahme clinicum
#define DBFNC_END                0
#define DBFNC_MSG                1
#define DBFNC_ONFIRST            2
#define DBFNC_ONLAST             3
#define DBFNC_ONNEXT             4
#define DBFNC_ONPREV             5
#define DBFNC_ONDELETE           6
#define DBFNC_ONINSERT           7
#define DBFNC_ONUPDATE           8
#define DBFNC_ONGET              9
#define DBFNC_USEKEY             10
#define DBFNC_DBOP               11
#define DBFNC_STORE              12
#define DBFNC_ASSIGN             13
#define DBFNC_ONSUCCESS          14
#define DBFNC_ONENDOFFILE        15
#define DBFNC_ONRECNOTFOUND      16
#define DBFNC_ONMORE             17
#define DBFNC_ENDONMORE          18
#define DBFNC_ABORT              19
#define DBFNC_ONERROR            20
#define DBFNC_IF                 21
#define DBFNC_ONREDUCED          22
#define DBFNC_STOREMULTI         23
#define DBFNC_ONFATALERROR       24
#define DBFNC_FORALL             25
#define DBFNC_ENDFORALL          26
#define DBFNC_FILTER             27
#define DBFNC_TESTFILTER         28
#define DBFNC_SETRECORD          29
#define DBFNC_TESTDBSTATUS       30
#define DBFNC_ONPARAM            31
#define DBFNC_SETREJECT          32
#define DBFNC_INITIALIZERECORD   33
#define DBFNC_ONLOCK             34
#define DBFNC_PUSHTOLOCKLIST     35
#define DBFNC_REPEAT             36
#define DBFNC_ENDREPEAT          37
#define DBFNC_BREAK              38
#define DBFNC_MOREFILTER         39
#define DBFNC_SETPRIMKEY         40
#define DBFNC_SETINNERJOINS      41
#define DBFNC_CONTINUE           42
#define DBFNC_NOTTESTFILTER      43


#define DBOP_KEYONLY    0xFFFF
#define DBOP_NOWAITLOCK 0xFFFE

#define OPERATOR_UNKNOWN    0
#define OPERATOR_BINCAT     1
#define OPERATOR_PADD       2
#define OPERATOR_EXTRACT    3
#define OPERATOR_STRCAT     4
#define OPERATOR_NEXTCHAR   5
#define OPERATOR_ADDLONG    6
#define OPERATOR_MULLONG    7
#define OPERATOR_INCREMENT  8
#define OPERATOR_DECREMENT  9
#define OPERATOR_DIVLONG    10
#define OPERATOR_SUBLONG    11

