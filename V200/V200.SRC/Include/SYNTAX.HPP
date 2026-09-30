//----------------------------------------------------------
// syntax.hpp - Funktionsprototypen der Funktionen, 
//              die zur Codegeneration benoetigt werden                     
//              Beschreibung der Syntax                             
//
// $Header:   P:/marille/clinicum/include/rev/syntax.hpv   1.42   18 Aug 2000 17:02:24   Wolfgang  $
// $Log:   P:/marille/clinicum/include/rev/syntax.hpv  $
// 
//    Rev 1.42   18 Aug 2000 17:02:24   Wolfgang
// 1.) VarCheckOff bei Kontextuebergabedefinition.
// 
//    Rev 1.41   21 Apr 2000 15:50:40   Hannes
// 
//    Rev 1.40   21 Apr 2000 14:22:56   Hannes
// 
//    Rev 1.39   16 Feb 2000 15:02:54   Wolfgang
// 1.) Neue Schluesselwoerter fuer neue FDEF-Syntax.
// 
//    Rev 1.38   04 Aug 1999 18:43:12   Hannes
// Neues Syntaxelement: passthrough
// 
//    Rev 1.37   22 Apr 1999 10:24:50   Hannes
// TOFLAG
// 
//    Rev 1.36   26 Mar 1999 18:08:28   Wolfgang
// 1.) VirtualModule eingebaut.
// 
//    Rev 1.35   28 Jan 1999 12:20:46   Hannes
// Erweiterte SQL - Syntax
// 
//    Rev 1.34   19 Aug 1998 20:55:02   Hannes
// NULL Als Parameter von normalen Funktionen
// 
//    Rev 1.33   04 Aug 1998 17:48:04   Hannes
// Timestamp, Funktionsname gleich Variablenname
// 
//    Rev 1.32   17 May 1998 17:52:48   Hannes
// No change.
// 
//    Rev 1.31   26 Jan 1998 19:59:04   Hannes
// NULL als Schluesselwort
// 
//    Rev 1.30   05 Jan 1998 07:48:06   Hannes
// Einsparungen im Scriptheader
// 
//    Rev 1.29   25 Aug 1997 18:50:38   Hannes
// 
//    Rev 1.28   16 Jun 1997 07:47:38   Hannes
// TOOBJ
// 
//    Rev 1.27   27 May 1997 11:17:24   Hannes
// Definition von Privaten Strukturen, Listenvariable als Expression
// 
//    Rev 1.26   24 Mar 1997 11:41:14   Hannes
// Void - Funktionsaufruf auch in For - Blocks
// 
//    Rev 1.25   13 Mar 1997 19:07:26   Hannes
// blobs
// 
//    Rev 1.24   19 Feb 1997 12:04:42   Hannes
// Scriptfunktionen
// 
//    Rev 1.23   26 Nov 1996 07:57:44   HANNES
// Versionshistory von DDD's
// 
//    Rev 1.22   08 Nov 1996 13:25:04   HANNES
// Einbau von QLong
// 
//    Rev 1.21   30 Oct 1996 08:42:00   HANNES
// Compilererweiterung: break, continue, staticcall
// 
//    Rev 1.20   21 Oct 1996 18:51:24   HANNES
// Einbau von Aliasnamen in das Script
// 
//    Rev 1.19   26 Feb 1996 15:52:50   HANNES
// 
//    Rev 1.18   02 Feb 1996 10:59:26   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.17   09 Nov 1995 19:43:12   HANNES
// Geschachtelte ForSchleifen
// 
//    Rev 1.16   25 Sep 1995 20:49:06   HANNES
// 
//    Rev 1.15   14 Sep 1995 09:59:10   HANNES
// 
//    Rev 1.14   24 Aug 1995 00:13:02   HANNES
// No change.
// 
//    Rev 1.13   15 May 1995 08:23:06   HANNES
// structs im normalen Script
// 
//    Rev 1.12   28 Apr 1995 17:17:54   HANNES
// No change.
// 
//    Rev 1.11   20 Mar 1995 14:12:38   HANNES
// 
//    Rev 1.10   20 Mar 1995 12:08:58   HANNES
// Konstantenhanling, RunNmbr
// 
//    Rev 1.9   08 Mar 1995 09:11:46   HANNES
// Forschleifen u.a.
// 
//    Rev 1.8   16 Feb 1995 12:44:36   HANNES
// 
//    Rev 1.7   08 Dec 1994 22:04:18   HANNES
// 
//    Rev 1.6   05 Dec 1994 17:37:32   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.5   08 Nov 1994 12:39:08   HANNES
// Abort eingebaut
// 
//    Rev 1.4   31 Oct 1994 10:03:16   hannes
// Optionsscriptangabe
// 
//    Rev 1.3   03 Sep 1994 14:54:10   HANNES
// Formulartyp in den Header
// 
//    Rev 1.2   24 Aug 1994 19:40:10   HANNES
// Erweiterungen im Header
// 
//    Rev 1.1   05 Aug 1994 19:32:36   HANNES
// Time eingebaut
// 
//    Rev 1.0   24 Jun 1994 17:49:50   HANNES
// Neuuebernahme clinicum
// 
//    Rev 1.19   04 Feb 1994 16:52:00   HANNES
// Dynamisches Linken eingebaut
// 
//    Rev 1.18   04 Jan 1994 17:29:36   HANNES
// RECALLKEY als Datentyp
// 
//    Rev 1.17   09 Dec 1993 15:10:02   HANNES
// Direktes Include der Pascal Files
// 
//    Rev 1.16   16 Nov 1993 04:26:58   HANNES
// Verallgemeinerung der Benutzerdaten
// 
//    Rev 1.15   08 Oct 1993 17:56:00   HANNES
// Benutzer Daten
// 
//    Rev 1.14   22 Sep 1993 09:24:36   HANNES
// Version nach St. Poelten
// 
//    Rev 1.13   05 Sep 1993 22:07:42   HANNES
// 
//    Rev 1.12   18 Aug 1993 10:42:48   HANNES
// Icons..
// 
//    Rev 1.11   20 Jul 1993 12:38:52   HANNES
// Icons
// 
//    Rev 1.10   05 Jul 1993 14:54:12   HANNES
// Bitmaps, Commondata
// 
//    Rev 1.9   24 May 1993 14:28:06   HANNES
// Expressions
// 
//    Rev 1.7   02 Apr 1993 18:08:42   HANNES
// ?
// 
//    Rev 1.6   08 Mar 1993 14:20:10   HANNES
// Erweiterungen in Bezug auf den Editor
// 
//    Rev 1.5   22 Feb 1993 17:20:46   HANNES
// Erweiterung des Compilers auf Arrays
// 
//    Rev 1.4   29 Jan 1993 20:25:02   HANNES
// Dokumenttyp Simulation
// 
//    Rev 1.3   29 Jan 1993 19:06:20   HANNES
// Implementierung des Datentyp DCDATA
// 
//    Rev 1.2   18 Jan 1993 16:55:38   HANNES
// Neue Datentypen: long und obj
// 
//    Rev 1.1   13 Jan 1993 18:56:16   HANNES
// Veraenderungen des Compile Headers (mehrere Datentypen fuer ein Dokument)
// 
//    Rev 1.0   02 Dec 1992 16:08:48   HANNES
// Initial revision.
//
//----------------------------------------------------------


/*------< Moegliche Schluesselwoerter >--------------*/
//
// Die Nummer der Schluesselwoerter muessen mit dem
// Resource - File uebereinstimmen !!!!
//
#define SEMICOLON       0
#define PARCONTVAR      1
#define PARPOINTVAR     2
#define PARDECVAR       3
#define PARINTVAR       4
#define PARSTRVAR       5
#define PARSTRING       6
#define PARINT          7
#define PARDEC          8
#define DOUBLEPOINT     9
#define BRACECLOSE      10
#define BRACEOPEN       11
#define COLON           12
#define FREEPAR         13
#define FDEF            14
#define DTLOCAL         15
#define PARPOINT        16
#define PARCONT         17
#define PRGSTART        18
#define PRGEND          19
#define OPAND           20
#define OPOR            21
#define OPNOT           22
#define KWIF            23
#define CBRACEOPEN      24
#define CBRACECLOSE     25
#define KWELSE          26
#define STARTPROC       27
#define ENDPROC         28
#define CALL            29
#define FSLASH          30
#define VARSTRARR       31
#define PARSTRARR       32
#define FULLNAME        33
#define DOCTYP          34
#define DOC_FORM        35
#define DOC_TEXT        36
#define DOC_ENTER       37
#define DOC_TRACING     38
#define DOC_NUMANA      39
#define KWCASE          40
#define KWFURTHER       41
#define PARFLAG         42
#define PARSCALE        43
#define PARFLAGVAR      44
#define PARSCALEVAR     45
#define PARPICTVAR      46
#define PARPICTURE      47
#define PARDATEVAR      48
#define PARDATE         49
#define DOC_GRANA       50
#define DOC_IMAGE       51
#define PARPROCVAR      52
#define PARIMAGE        53
#define VARIMAGE        54
#define CONSTOPEN       55
#define CONSTCLOSE      56
#define INLINE          57
#define ENUM            58
#define EQUAL           59
#define LOOP            60
#define STERN           61
#define ARRBRACEOPEN    62
#define ARRBRACECLOSE   63
#define MPENT           64
#define SINGLEENT       65
#define CATEGORY        66
#define PARDWORD        67
#define PARDWORDVAR     68
#define PAROBJ          69
#define PAROBJVAR       70
#define DOC_VTO         71
#define DTHELP          72
#define OPERATOR        73
#define KWMAP           74
#define MPRES           75
#define PARBITMAP       76
#define PARBITMAPVAR    77
#define KWICON          78
#define KWEXPORTKONTEXT 79
#define KWIMPORTKONTEXT 80
#define KWEXPORTPROC    81
#define KWUSETABLE      82
#define KWALIAS         83
#define DEFVSP          84
#define DEFVER          85
#define BESEL           86
#define ISTVS           87
#define ISTVE           88
#define DIVV            89
#define DIFS            90
#define PARTIMEVAR      91
#define PARTIME         92
#define DIKV            93
#define NOMDI           94
#define TFORMOHNE       95
#define TFORMMIT        96
#define TFACHOHNE       97
#define TFACHMIT        98
#define TMAPPE          99
#define TINTERN         100
#define OPTSC           101
#define KWABORT         102
#define ASSIGNMENT      103
#define SCOND           104
#define CMPOPERATOR     105
#define FOR             106
#define SELECT          107
#define FROM            108
#define WHERE           109
#define ORDER           110
#define INNERLIST       111
#define OUTERLIST       112
#define REMOVE          113
#define INSERT          114
#define INTO            115
#define SET             116
#define AFTER           117
#define BEFORE          118
#define KWIN            119
#define WITH            120
#define PROPERTY        121
#define STRUCT          122
#define FORALL          123
#define REVERSE         124
#define DOWITH          125
#define KWBREAK         126
#define KWSTATICCALL    127
#define KWCONTINUE      128
#define QLONG           129
#define QLONGVAR        130
#define VIEW            131
#define CONSTPREFIX     132
#define KWRETURN        133
#define KWVOID          134
#define KWEXTERN        135
#define KWBASE          136
#define KWOVERLOAD      137
#define KWSTATIC        138
#define TOSTRING        139
#define TOTIME          140
#define TODATE          141
#define TOFLOAT         142
#define TOLONG          143
#define TOSHORT         144
#define PARBLOBVAR      145
#define PARBLOB         146
#define TOBLOB          147
#define TOOBJ           148
#define KWNULL          149
#define PARDATETIMEVAR  150
#define PARDATETIME     151
#define TODATETIME      152
#define KWIMPORTVIRTUAL 153
#define TOFLAG          154
#define DBSEL           155
#define COUNTVAR        156
#define DESCRIBED_AS    157
#define ODEF            158
#define MDEF            159
#define KWOMAP          160

#ifdef SYNTAX_MAIN
/*------< Funktionsprototypen >--------*/
/*-------------------------------------*/
// ScriptHeader
void GenerateStruct ();
void GenerateView ();
void MarkStructName ();
void MarkStructStart ();
void MarkViewStart ();

void SetProperty();
void SetDarfInFachsein ();
void SetDarfImVerzeichnisVorkommen ();
void SetDarfInKrankengeschichteVorkommen ();
void SetIstVerweisErzeuger ();
void SetIstVerweisSpeicherer ();
void SetBearbeiteSelektor ();
void SetDefaultVerweisErzeuger ();
void SetDefaultVerweisSpeicherer ();
void SetOptionScript ();
void SetNoMDI ();
void SetFormType ();

// Funktionsprototypen
void inclevel (void);           // Codebuffer - Level inkrementieren
void inclevel_CheckOn (void);           // Codebuffer - Level inkrementieren
void inclevel_breakallowed (void);
void pushpartype (void);        // Type des Parameters in den Codebuffer 
                                // bringen
void SetAliasName ();
void SetAliasVar ();

// Variablendeklaration
void setdatabasenumber (void);  // Merken der Datenbank nummer
void setvartype (void);         // Merken des Variablentyps
void setvarname (void);         // Merken des Variablennames
void setvarhash (void);         // Erstellen der Hashtabelle
void pushpars0  (void);         // Erstellen der Hashtabelle
void inc2level (void);          // Extrainformation 2 level hoeher setzen
void dec2level (void);          // Codegeneratorbuffer wieder in Ordnung 
void setvardim (void);
// Funktionsaufruf
void pushpar (void);            // Schreiben eines Parameters
void push_funchead (void);      // Schreiben des Funktionsidentifiers, 
                                // Vorbereitung des Parameterchecks
void GetFuncCopy (void);        // Nur fuer den Editor !!!
void MarkEdBraceOpen ();        // Nur fuer den Editor !!!

// Conditions
void startcond (void);
void popbuffer (void);          // Bufferinhalt nach oben kopieren
void pushop (void);             // Operator + Zeiger schreiben
void marknot (void);            // Invertierungszeichen vorsetzen

void UseTable ();
void SetTableName ();
void SetAliasTable ();

// Statement
void popstatement (void);       // Laenge des Buffers eintragen und pop
void endproc      (void);       // Prozedur abschliessen
void markif       (void);       // Prefix fuer if
void markelse     (void);       // Prefix fuer if
void marknoelse   (void);       // nop einfuegen, damit kein irrtuemlicher
                                // else auftreten kann

// Procedurverwaltung
void markstart (void);
void markproc (void);
void markexportproc (void);
void pushcall (void);
void pushstaticcall (void);
void lookup (void);
void pushbreak (void);
void pushcontinue (void);

// Headerdefinition
void marknumana (void);
void markgrana (void);
void markform (void);
void marktext (void);
void markenter (void);
void markimage (void);
void marktracing (void);
void markvto (void);
void strore_fullname (void);

// Case - Verwaltung
void markrunnr (void) ;
void markfurther (void) ;
void markcase (void) ;

// Freie Vergabe eines Integers
void setfreevarhash (void) ;
void setfreevarhash_VarCheckOff_InFunction (void);
void setnextvar (void);

// Konstanten
void setptx (void);
void setpty (void);
void setconstpt (void);
void setconststr (void);
void setconstind (void);
void setconstdec (void);
void pushconstpar (void);
void setconstqword (void);
void setconstdword (void);
void setconstflag (void);
void setdbldef (void);
void pushnull (void);

// lokale (inline) funktionen
void setfncpar (void);
void storefnc (void);
void startfnc (void);
void storeinlinename (void);
void startinlinefunction (void);
void startinlinepar (void);
void endinlinepar (void);
void pushfncpar (void);
void makeprogcopy (void);
void pushprog (void);
void startInlineCall (void);
void FixupPar ();
void FixupEnumEle ();
void FixupEnumPar ();
void FixupConstPar ();

// Enum Variablen
void StoreEnumConstVar (void);
void StoreEnumInt (void);
void StoreEnumDec (void);
void StoreEnumVar (void);
void storeenum (void);
void storeenumtype (void);
void setloopcount (void);

void setsingleent (void);
void setmpent (void);
void setsubcat (void);
void setabort (void);

void setopallowed ();
void popexpression1 ();
void popexpression2 ();

void storeiconfile ();
void markExportKontext ();
void importKontext ();
void importBase ();
void setsimplecond ();
void setcmpcond ();
void setfreevarhash_withres ();
void SetReverse ();
void SetNormal ();
void PushForAllBlock ();
void PushDoWithBlock ();
void VarCheckOff ();
void VarCheckOn_UseTable ();
void VarCheckOn ();
void VarCheckOff_InFunction ();
void VarCheckOff_InFunction_UnqualifiedOff ();

// Makro fuer Zuweisung der Struktur Term in syntax_node
// (es kann leider nur das erste Element einer union initialisiert werden !!
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

/*-----< Syntax - Beschreibung >--------*/
/*-------------------------------------*/
// Datenbanktypen
syntax_node vbh         = { NULL , NULL , TRUE , INITERM (KEYWORD, DTHELP) , setdatabasenumber } ;
syntax_node vb          = { NULL , &vbh , TRUE , INITERM (KEYWORD, DTLOCAL) , setdatabasenumber } ;


// Variablentype
syntax_node vt_datet  = { NULL , NULL , TRUE , INITERM(KEYWORD,PARDATETIME) , setvartype } ;
syntax_node vt_obj    = { NULL , &vt_datet , TRUE , INITERM(KEYWORD,PAROBJ) , setvartype } ;
syntax_node vt_blob   = { NULL , &vt_obj , TRUE , INITERM(KEYWORD,QLONG) , setvartype } ;
syntax_node vt_qword  = { NULL , &vt_blob , TRUE , INITERM(KEYWORD,PARBLOB) , setvartype } ;
syntax_node vt_dword  = { NULL , &vt_qword , TRUE , INITERM(KEYWORD,PARDWORD) , setvartype } ;
syntax_node vt_scale  = { NULL , &vt_dword , TRUE , INITERM (KEYWORD, PARSCALE) , setvartype } ;
syntax_node vt_flag   = { NULL , &vt_scale , TRUE , INITERM (KEYWORD, PARFLAG) , setvartype } ;
syntax_node vt_strarr = { NULL , &vt_flag , TRUE , INITERM (KEYWORD, VARSTRARR) , setvartype } ;
syntax_node vt_str    = { NULL , &vt_strarr , TRUE , INITERM (KEYWORD, PARSTRING) , setvartype } ;
syntax_node vt_dec    = { NULL , &vt_str , TRUE , INITERM (KEYWORD, PARDEC) , setvartype } ;
syntax_node vt_int    = { NULL , &vt_dec , TRUE , INITERM (KEYWORD, PARINT) , setvartype } ;
syntax_node vt_image  = { NULL , &vt_int , TRUE , INITERM (KEYWORD, VARIMAGE) , setvartype } ;
syntax_node vt_time   = { NULL , &vt_image , TRUE , INITERM (KEYWORD, PARTIME) , setvartype } ;
syntax_node vt_date   = { NULL , &vt_time , TRUE , INITERM (KEYWORD, PARDATE) , setvartype } ;
syntax_node vt_pt     = { NULL , &vt_date , TRUE , INITERM (KEYWORD, PARPOINT) , setvartype } ;
syntax_node vt        = { NULL , &vt_pt , TRUE , INITERM (KEYWORD, PARCONT) , setvartype } ;

// Variablentype
extern void EnlargeStructData();
syntax_node ut_datet  = { NULL , NULL , TRUE , INITERM(KEYWORD,PARDATETIME) , EnlargeStructData } ;
syntax_node ut_obj    = { NULL , &ut_datet , TRUE , INITERM(KEYWORD,PAROBJ) , EnlargeStructData } ;
syntax_node ut_blob   = { NULL , &ut_obj , TRUE , INITERM(KEYWORD,QLONG) , EnlargeStructData } ;
syntax_node ut_qword  = { NULL , &ut_blob , TRUE , INITERM(KEYWORD,PARBLOB) , EnlargeStructData } ;
syntax_node ut_dword  = { NULL , &ut_qword , TRUE , INITERM(KEYWORD,PARDWORD) , EnlargeStructData } ;
syntax_node ut_scale  = { NULL , &ut_dword , TRUE , INITERM (KEYWORD, PARSCALE) , EnlargeStructData } ;
syntax_node ut_flag   = { NULL , &ut_scale , TRUE , INITERM (KEYWORD, PARFLAG) , EnlargeStructData } ;
syntax_node ut_strarr = { NULL , &ut_flag , TRUE , INITERM (KEYWORD, VARSTRARR) , EnlargeStructData } ;
syntax_node ut_str    = { NULL , &ut_strarr , TRUE , INITERM (KEYWORD, PARSTRING) , EnlargeStructData } ;
syntax_node ut_dec    = { NULL , &ut_str , TRUE , INITERM (KEYWORD, PARDEC) , EnlargeStructData } ;
syntax_node ut_int    = { NULL , &ut_dec , TRUE , INITERM (KEYWORD, PARINT) , EnlargeStructData } ;
syntax_node ut_image  = { NULL , &ut_int , TRUE , INITERM (KEYWORD, VARIMAGE) , EnlargeStructData } ;
syntax_node ut_time   = { NULL , &ut_image , TRUE , INITERM (KEYWORD, PARTIME) , EnlargeStructData } ;
syntax_node ut_date   = { NULL , &ut_time , TRUE , INITERM (KEYWORD, PARDATE) , EnlargeStructData } ;
syntax_node ut_pt     = { NULL , &ut_date , TRUE , INITERM (KEYWORD, PARPOINT) , EnlargeStructData } ;
syntax_node ut        = { NULL , &ut_pt , TRUE , INITERM (KEYWORD, PARCONT) , EnlargeStructData } ;

// 2. Variablendeklaration
syntax_node dd_2   = { NULL  , NULL , TRUE , INITERM (KEYWORD,ARRBRACECLOSE) , NULL };
syntax_node dd_1   = { &dd_2 , NULL , TRUE , INITERM (T_INTEGER,0) , setvardim };
syntax_node dimdef = { &dd_1 , NULL , TRUE , INITERM (KEYWORD,ARRBRACEOPEN) , NULL };
extern syntax_node var_init;
extern syntax_node expression ;
extern syntax_node func_start ;

syntax_node var_noinit2 = { &var_init , NULL , TRUE , INITERM (UNKNOWNIDENT, 0) , setnextvar } ;
syntax_node var_noinit1 = { &var_noinit2 , &func_start , TRUE , INITERM (KEYWORD, COLON) , setfreevarhash_VarCheckOff_InFunction } ;
syntax_node var_noinit  = { NULL , &var_noinit1 , TRUE , INITERM (KEYWORD, SEMICOLON) , setfreevarhash } ;

syntax_node var_dimd3 = { &var_init , NULL , TRUE , INITERM (UNKNOWNIDENT, 0) , setnextvar } ;
syntax_node var_dimd2 = { &var_dimd3 , NULL , TRUE , INITERM (KEYWORD, COLON) , setfreevarhash } ;
syntax_node var_dimd1 = { NULL , &var_dimd2 , TRUE , INITERM (KEYWORD, SEMICOLON) , setfreevarhash } ;
syntax_node var_dimd  = { &var_dimd1 , &var_noinit , FALSE , &dimdef , NULL };

syntax_node var_init4 = { &var_init  , NULL , TRUE , INITERM (UNKNOWNIDENT,0) , setnextvar } ;
syntax_node var_init3 = { &var_init4 , NULL , TRUE , INITERM (KEYWORD,COLON) , VarCheckOff_InFunction } ;
syntax_node var_init2 = { NULL , &var_init3 , TRUE , INITERM (KEYWORD,SEMICOLON) , NULL } ;
syntax_node var_init1 = { &var_init2 , NULL , FALSE , &expression , matchexpression } ;
syntax_node var_init  = { &var_init1 , &var_dimd , TRUE , INITERM (KEYWORD,EQUAL) , setfreevarhash_withres } ;

syntax_node var_dbl = { &func_start , NULL , TRUE , INITERM (VARID , 0) , setvarname } ;
syntax_node var_nme = { &var_init, &var_dbl , TRUE , INITERM (UNKNOWNIDENT , 0) , setvarname } ;
syntax_node var_typ = { &var_nme , NULL , FALSE , &vt , VarCheckOff_InFunction_UnqualifiedOff } ;
syntax_node vdef    = { &var_typ , &var_typ , FALSE , &vb , NULL } ;

syntax_node ptconste = { NULL     , NULL , TRUE , INITERM (KEYWORD, BRACECLOSE) , NULL } ;
syntax_node ptconsty = { &ptconste, NULL , TRUE , INITERM (DECIMAL, 0) , setpty } ;
syntax_node ptconstc = { &ptconsty, NULL , TRUE , INITERM (KEYWORD, COLON) , NULL } ;
syntax_node ptconstx = { &ptconstc, NULL , TRUE , INITERM (DECIMAL, 0) , setptx } ;
syntax_node ptconst  = { &ptconstx, NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , NULL } ;

syntax_node fconst3 = { NULL      , NULL , TRUE , INITERM (KEYWORD, BRACECLOSE) , NULL } ;
syntax_node fconst2 = { &fconst3 , NULL , TRUE , INITERM (T_INTEGER, 0) , setconstflag } ;
syntax_node fconst1 = { &fconst2 , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , NULL } ;
syntax_node fconst  = { &fconst1 , NULL , TRUE , INITERM (KEYWORD, PARFLAG) , NULL } ;

syntax_node dwconst3 = { NULL      , NULL      , TRUE , INITERM (KEYWORD, BRACECLOSE) , NULL } ;
syntax_node dwconst4 = { &dwconst3 , NULL      , TRUE , INITERM (T_LINTEGER, 0) , setconstdword } ;
syntax_node dwconst2 = { &dwconst3 , &dwconst4 , TRUE , INITERM (T_INTEGER, 0) , setconstdword } ;
syntax_node dwconst1 = { &dwconst2 , NULL      , TRUE , INITERM (KEYWORD, BRACEOPEN) , NULL } ;
syntax_node dwconst  = { &dwconst1 , NULL      , TRUE , INITERM (KEYWORD, PARDWORD) , NULL } ;

syntax_node qconst = { NULL , NULL , TRUE , INITERM (T_QINTEGER,0) , setconstqword } ;
syntax_node longconst = { NULL , &qconst , TRUE , INITERM (T_LINTEGER,0) , setconstdword } ;

syntax_node const_ptf1 = { NULL        , NULL , FALSE , &ptconst , NULL } ;
syntax_node const_ptf  = { &const_ptf1 , NULL , TRUE , INITERM(KEYWORD,PARPOINT) , NULL } ;

syntax_node const_e   = { NULL , NULL , TRUE , INITERM (KEYWORD, ARRBRACECLOSE) , NULL } ;
syntax_node const_f   = { &const_e , NULL , FALSE , &fconst , NULL } ;
syntax_node const_dw  = { &const_e , &const_f , FALSE , &dwconst , NULL } ;
syntax_node const_pt  = { &const_e , &const_dw , FALSE , &ptconst , setconstpt } ;
syntax_node const_str = { &const_e , &const_pt , TRUE , INITERM (STRING , 0) , setconststr } ;
syntax_node const_ind = { &const_e , &const_str , TRUE , INITERM (T_INTEGER, 0) , setconstind } ;
syntax_node const_b   = { &const_e , &const_ind , TRUE , INITERM (DECIMAL, 0) , setconstdec } ;
syntax_node constdef  = { &const_b , &longconst , TRUE , INITERM (KEYWORD, ARRBRACEOPEN) , NULL } ;

// Parameter von Funktionsaufrufen
syntax_node par_null = { NULL , NULL , TRUE , INITERM (UNKNOWNIDENT , 0) , pushnull } ;
syntax_node par_unknown = { NULL , &par_null , TRUE , INITERM (UNKNOWNIDENT , 0) , pushpar } ;
#ifdef UEBERLEGT
syntax_node par_expression = { NULL , &par_unknown , FALSE , &expression , pushparexpression } ;
syntax_node par_fncpar = { NULL , &par_expression , TRUE , INITERM (PARID, 0) , pushfncpar } ;
syntax_node par_const = { NULL , &par_fncpar , FALSE , &constdef , pushconstpar } ;
syntax_node par_int = { NULL , &par_const , TRUE , INITERM (T_INTEGER, 0) , pushpar } ;
syntax_node par_dec = { NULL , &par_int , TRUE , INITERM (DECIMAL, 0) , pushpar } ;
syntax_node par = { NULL , &par_dec , TRUE , INITERM (STRING, 0) , pushpar } ;
#else
syntax_node par = { NULL , &par_unknown , FALSE , &expression , pushparexpression } ;
#endif

// 3. Funktionsaufruf
extern syntax_node fc_p;
extern syntax_node fc_c;
syntax_node fc_bc0 = { NULL , &fc_p , TRUE , INITERM (KEYWORD, BRACECLOSE) , GetFuncCopy } ;
syntax_node fc_bc1 = { NULL , &fc_c , TRUE , INITERM (KEYWORD, BRACECLOSE) , GetFuncCopy } ;
syntax_node fc_p   = { &fc_bc1 , NULL , FALSE , &par, NULL } ;
syntax_node fc_c   = { &fc_p , NULL , TRUE , INITERM (KEYWORD, COLON) , NULL } ;
syntax_node fc_bo  = { &fc_bc0 , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , MarkEdBraceOpen } ;
syntax_node fc     = { &fc_bo , NULL , TRUE , INITERM (FUNCTIONID, 0) , push_funchead } ;

// Verbindungs - Operatoren
syntax_node op_and = { NULL , NULL , TRUE , INITERM (KEYWORD, OPAND) , pushop } ;
syntax_node op     = { NULL , &op_and , TRUE , INITERM (KEYWORD, OPOR) , pushop } ;

// Einfache Operatoren
syntax_node sop    = { NULL , NULL , TRUE , INITERM (KEYWORD, OPNOT) , marknot } ;

extern syntax_node termsym,in_cond;
syntax_node doscond1 = { NULL , NULL , TRUE , INITERM (FREECHAR, 0) , NULL } ;
syntax_node doscond  = { NULL , &doscond1 , FALSE , &in_cond , NULL } ;
syntax_node expcond2 = { NULL , NULL , FALSE , &expression , NULL } ;
syntax_node expcond1 = { &expcond2 , &doscond , TRUE  , INITERM(CMPOP,0) , setcmpcond } ;
syntax_node expcond  = { &expcond1 , NULL     , FALSE , &expression , setsimplecond } ;

// 4. Conditions
extern syntax_node cond ;
extern syntax_node cond_sop ;
extern syntax_node cond_fnc ;
syntax_node cond_op   = { &cond_sop , NULL , FALSE , &op, NULL } ;
syntax_node cond_bc   = { NULL , &cond_op , TRUE , INITERM (KEYWORD, BRACECLOSE) , popbuffer } ;
syntax_node cond_cond = { &cond_bc , &cond_fnc , FALSE , &cond , NULL } ;
syntax_node cond_fnc1 = { &cond_bc , NULL , FALSE , &expcond , matchexpression } ;
syntax_node cond_fnc  = { &cond_bc , &cond_fnc1 , FALSE , &fc , NULL } ;
syntax_node cond_sop  = { &cond_cond , &cond_cond , FALSE , &sop , NULL } ;
syntax_node cond      = { &cond_sop , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , startcond } ;

// Block
extern syntax_node statement ;
extern syntax_node st_st ;
void matchexpression_return ();
void prepreturn ();
syntax_node st_sg   = { NULL , NULL , FALSE , &statement, NULL } ;
syntax_node st_bcc  = { NULL , &st_st , TRUE , INITERM(KEYWORD,CBRACECLOSE) , NULL } ;
syntax_node st_st   = { &st_bcc , NULL , FALSE , &statement , FALSE } ;
syntax_node block   = { &st_st , &st_sg , TRUE , INITERM(KEYWORD,CBRACEOPEN) , NULL } ;

// 5. Statement
extern syntax_node flc;
extern syntax_node loopdef;
extern syntax_node ifnc;
extern syntax_node enumdef;

void createfncnode_r();
extern syntax_node expression;
extern syntax_node _struct;
extern syntax_node _view;
extern syntax_node vf_start;
extern syntax_node fncexp;
syntax_node st_fcall1     = { NULL       , NULL      , TRUE , INITERM(KEYWORD,SEMICOLON) , NULL } ;
syntax_node st_fcall      = { &st_fcall1 , NULL      , FALSE , &fncexp , matchexpression } ;
syntax_node st_abort1     = { NULL       , NULL      , TRUE , INITERM(KEYWORD,SEMICOLON) , NULL } ;
syntax_node st_abort      = { &st_abort1 , &st_fcall , TRUE , INITERM(KEYWORD,KWABORT) , setabort } ;
syntax_node st_loopc      = { NULL       , NULL      , TRUE , INITERM (KEYWORD, SEMICOLON) , NULL } ;
syntax_node st_loop       = { &st_loopc  , &st_abort , FALSE , &flc , NULL } ;
syntax_node st_slc        = { NULL       , NULL      , TRUE , INITERM (KEYWORD, SEMICOLON) , NULL } ;
syntax_node st_flc        = { &st_slc    , &st_loop  , FALSE , &loopdef , NULL } ;
syntax_node st_edef       = { NULL       , &st_flc   , FALSE , &enumdef , NULL } ;
syntax_node st_idef       = { NULL       , &st_edef  , FALSE , &ifnc    , NULL } ;
syntax_node st_vdef       = { NULL       , &st_idef  , FALSE , &_view  , NULL } ;
syntax_node st_sdef       = { NULL       , &st_vdef  , FALSE , &_struct , NULL } ;
syntax_node ext_statement = { NULL       , &st_sdef  , FALSE , &vdef    , NULL } ;

extern syntax_node _for,with,_remove,insert,fncbo;
extern void copyExpConstRes();
extern void patchcmpltstatic();
extern syntax_node etptr1,vfncbo,etptr;
void MarkTableToReuse();
syntax_node st_vfcall2     = { &fncbo , &fncbo , FALSE   , &etptr , MarkTableToReuse } ;
syntax_node st_vfcall1     = { &st_vfcall2 , &st_vfcall2 , TRUE , INITERM (KEYWORD,KWSTATIC) , patchcmpltstatic } ;
syntax_node st_vfcall      = { &st_vfcall1  , NULL       , TRUE , INITERM (VFNCEXP,0) , createfncnode_r } ;

extern syntax_node typemodify;
syntax_node st_continue    = { NULL      , NULL         , TRUE , INITERM(KEYWORD,KWCONTINUE) , pushcontinue } ;
syntax_node st_break       = { NULL      , &st_continue , TRUE , INITERM(KEYWORD,KWBREAK) , pushbreak } ;
syntax_node st_remove      = { NULL      , &st_break    , FALSE , &_remove , NULL } ;
syntax_node st_exp         = { NULL      , NULL         , FALSE , &expression , matchexpression } ;
syntax_node st_vf          = { NULL      , NULL         , FALSE , &st_vfcall , matchexpression } ;
syntax_node st_ass1        = { &st_exp   , &st_vf       , TRUE , INITERM (KEYWORD,EQUAL) , NULL } ;
syntax_node st_cfv         = { &st_vf    , &st_remove   , TRUE , INITERM (STRING,0) , copyExpConstRes } ;
syntax_node st_assign      = { &st_ass1  , &st_cfv      , TRUE , INITERM (VARID,0) , copyExpRes } ;
syntax_node st_ass0        = { &st_assign, &st_assign   , FALSE, &typemodify , NULL } ;
syntax_node st_scname      = { NULL      , NULL         , TRUE , INITERM (UNKNOWNIDENT,0) , lookup } ;
syntax_node st_scall       = { &st_scname, &st_ass0     , TRUE , INITERM (KEYWORD,KWSTATICCALL) , pushstaticcall } ;
syntax_node st_cname       = { NULL      , NULL         , TRUE , INITERM (UNKNOWNIDENT,0) , lookup } ;
syntax_node st_call        = { &st_cname , &st_scall    , TRUE , INITERM (KEYWORD,CALL) , pushcall } ;
syntax_node sing_statement = { NULL      , &st_call     , FALSE , &fc , NULL } ;

syntax_node st_insert    = { NULL      , &st_remove , FALSE , &insert , NULL } ;
syntax_node st_with      = { NULL      , &st_insert , FALSE , &with , NULL } ;
syntax_node st_sync      = { NULL , NULL , TRUE , INITERM (FREECHAR, 0) , marknoelse } ;
syntax_node st_blk1      = { NULL , NULL , FALSE , &block , popstatement } ;
syntax_node st_else      = { &st_blk1 , &st_sync , TRUE , INITERM (KEYWORD, KWELSE) , markelse } ;
syntax_node st_blk0      = { &st_else , NULL , FALSE , &block , popstatement } ;
syntax_node st_cond      = { &st_blk0 , NULL , FALSE , &cond , inclevel } ;
syntax_node if_statement = { &st_cond , &st_with , TRUE , INITERM (KEYWORD, KWIF) , markif } ;

syntax_node st4       = { NULL , NULL , FALSE , &_for , NULL } ;
syntax_node st3       = { NULL , &st4 , FALSE , &ext_statement , NULL } ;
syntax_node st2       = { NULL , &st3 , FALSE , &if_statement  , NULL } ;
syntax_node st1       = { NULL , NULL , TRUE  , INITERM (KEYWORD, SEMICOLON) , NULL } ;
syntax_node statement = { &st1 , &st2 , FALSE , &sing_statement , NULL } ;

// 6. Prozedurdefinition
extern syntax_node proc_stt;
syntax_node proc_end   = { NULL , &proc_stt , TRUE , INITERM (KEYWORD, ENDPROC) , endproc } ;
syntax_node proc_stt   = { &proc_end , NULL , FALSE , &statement , NULL } ;
syntax_node proc_name  = { &proc_end , NULL , TRUE , INITERM (UNKNOWNIDENT, 0), markproc } ;
syntax_node proc       = { &proc_name , NULL , TRUE , INITERM (KEYWORD, STARTPROC) , NULL } ;
// syntax_node proc       = { &prockw , &prockw , TRUE , INITERM (KEYWORD, KWEXPORTPROC) , markexportproc } ;

// Funktionsdefinition (Der Name der Funktion befindet sich in Pars0,
//                        Der Level ist erhoeht worden)
//-------------------------------------------------------------------
void endfunction ();
void startfunction ();
void marknores_UnqualifiedOff ();
void setfreevarhash_closefuncdef ();
void markvarnobind ();
void markFuncExport ();
extern syntax_node func_s1;
extern syntax_node func_stt;
void startfuncdefinition();
void setfreevarhash_closefuncdefinition();
void closefuncdefinition();
void closefuncdef();
void markFuncExtern();
void PushTableInd();
void markFuncOverload();
void OnStartFunc();
extern syntax_node dfunc_s1;
extern syntax_node tptr1;
syntax_node tptr3 = { NULL , NULL , TRUE , INITERM(KEYWORD,ARRBRACECLOSE) , VarCheckOn } ;
syntax_node tptr2 = { &tptr1 , &tptr3 , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node tptr1a = { &tptr2 , NULL , TRUE , INITERM(VARID,0) , PushTableInd } ;
syntax_node tptr1  = { &tptr2 , &tptr1a , TRUE , INITERM(UNKNOWNIDENT,0) , PushTableInd } ;
syntax_node tptr  = { &tptr1 , NULL , TRUE , INITERM(KEYWORD,ARRBRACEOPEN) , VarCheckOff } ;

// syntax_node dfunc_s6    = { NULL , NULL , TRUE , INITERM(KEYWORD,SEMICOLON) , NULL } ;
// syntax_node dfunc_s5    = { &dfunc_s6 , NULL , TRUE , INITERM(KEYWORD,BRACECLOSE) , setfreevarhash_closefuncdefinition } ;
// syntax_node dfunc_s4    = { &dfunc_s1 , &dfunc_s5 , TRUE , INITERM(KEYWORD,COLON) , setfreevarhash } ;
// syntax_node dfunc_s3a   = { &dfunc_s4 , &dfunc_s4 , TRUE , INITERM(VARID,0) , setvarname } ;
// syntax_node dfunc_s3    = { &dfunc_s4 , &dfunc_s3a , TRUE , INITERM(UNKNOWNIDENT,0) , setvarname } ;
// syntax_node dfunc_s2    = { &dfunc_s3 , NULL , FALSE , &vt , NULL } ;
// syntax_node dfunc_s1    = { &dfunc_s2 , &dfunc_s2 , TRUE , INITERM(KEYWORD,CONSTPREFIX) , markvarnobind } ;
// syntax_node dfunc_s0b   = { &dfunc_s6 , &dfunc_s1 , TRUE , INITERM(KEYWORD,BRACECLOSE) , closefuncdefinition } ;
// syntax_node dfunc_s0    = { &dfunc_s0b , NULL , TRUE , INITERM(KEYWORD,BRACEOPEN) , startfuncdefinition } ;
// syntax_node dfunc_s0c   = { &dfunc_s0 , &dfunc_s0 , FALSE , &tptr , NULL } ;

extern syntax_node func_s5a;
syntax_node func_s7    = { NULL , &func_stt , TRUE , INITERM(KEYWORD,CBRACECLOSE) , endfunction } ;
syntax_node st_fc3 = { NULL , NULL , TRUE , INITERM(KEYWORD,CBRACECLOSE) , endfunction } ;
syntax_node st_fc2 = { &st_fc3 , NULL , TRUE , INITERM(KEYWORD,SEMICOLON) , NULL } ;
syntax_node st_fc1 = { &st_fc2 , NULL , FALSE , &expression , matchexpression_return } ;
syntax_node st_fc0  = { &st_fc1 , NULL , TRUE , INITERM(KEYWORD,KWRETURN) , prepreturn } ;
syntax_node func_stt    = { &func_s7 , &st_fc0 , FALSE , &statement , NULL } ;
syntax_node func_s6     = { &func_s7 , &func_s5a , TRUE , INITERM(KEYWORD,CBRACEOPEN) , OnStartFunc } ;
syntax_node func_s5b    = { &func_s6 , NULL , FALSE , &vdef, NULL } ;
syntax_node func_s5a    = { &func_s6 , &func_s5b , FALSE , &proc, NULL } ;
syntax_node func_s5     = { &func_s6 , NULL , TRUE , INITERM(KEYWORD,BRACECLOSE) , setfreevarhash_closefuncdef } ;
syntax_node func_s4     = { &func_s1 , &func_s5 , TRUE , INITERM(KEYWORD,COLON) , setfreevarhash } ;
syntax_node func_s3a    = { &func_s4 , &func_s4 , TRUE , INITERM(VARID,0) , setvarname } ;
syntax_node func_s3     = { &func_s4 , &func_s3a , TRUE , INITERM(UNKNOWNIDENT,0) , setvarname } ;
syntax_node func_s2     = { &func_s3 , NULL , FALSE , &vt , NULL } ;
syntax_node func_s1     = { &func_s2 , &func_s2 , TRUE , INITERM(KEYWORD,CONSTPREFIX) , markvarnobind } ;
syntax_node func_s0b    = { &func_s6 , &func_s1 , TRUE , INITERM(KEYWORD,BRACECLOSE) , closefuncdef } ;
syntax_node func_s0     = { &func_s0b , NULL , TRUE , INITERM(KEYWORD,BRACEOPEN) , startfunction } ;
syntax_node func_s0c    = { &func_s0 , &func_s0 , FALSE , &tptr , NULL } ;
syntax_node func_s0d    = { &func_s0c , &func_s0c , TRUE , INITERM(KEYWORD,KWOVERLOAD) , markFuncOverload } ;
syntax_node func_start  = { &func_s0c , &func_s0d , TRUE , INITERM(KEYWORD,KWEXPORTPROC) , markFuncExport } ;
// syntax_node func_start  = { &dfunc_s0c , &func_s0a , TRUE , INITERM(KEYWORD,KWEXTERN) , markFuncExtern } ;

syntax_node vf_s2    = { &func_start , NULL , TRUE , INITERM(VARID,0) , setvarname } ;
syntax_node vf_s1    = { &func_start , &vf_s2 , TRUE , INITERM(UNKNOWNIDENT,0) , setvarname } ;
syntax_node vf_start = { &vf_s1 , NULL , TRUE , INITERM(KEYWORD,KWVOID) , marknores_UnqualifiedOff } ;

// 7. Dokumententypen
syntax_node docm6 = { NULL , NULL , TRUE , INITERM(KEYWORD,TFORMOHNE) , SetFormType } ;
syntax_node docm5 = { NULL , &docm6 , TRUE , INITERM(KEYWORD,TFORMMIT) , SetFormType } ;
syntax_node docm4 = { NULL , &docm5 , TRUE , INITERM(KEYWORD,TFACHOHNE) , SetFormType } ;
syntax_node docm3 = { NULL , &docm4 , TRUE , INITERM(KEYWORD,TFACHMIT) , SetFormType } ;
syntax_node docm2 = { NULL , &docm3 , TRUE , INITERM(KEYWORD,TMAPPE) , SetFormType } ;
syntax_node docm1 = { NULL , &docm2 , TRUE , INITERM(KEYWORD,TINTERN) , SetFormType } ;
syntax_node docm  = { &docm1 , NULL , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node docimage= { &docm , NULL , TRUE , INITERM (KEYWORD, DOC_IMAGE) , markimage } ;
syntax_node docgana = { &docm , &docimage , TRUE , INITERM (KEYWORD, DOC_GRANA) , markgrana } ;
syntax_node docnana = { &docm , &docgana , TRUE , INITERM (KEYWORD, DOC_NUMANA) , marknumana } ;
syntax_node docvto  = { &docm , &docnana , TRUE , INITERM (KEYWORD, DOC_VTO) , markvto } ;
syntax_node doctr   = { &docm , &docvto, TRUE , INITERM (KEYWORD, DOC_TRACING) , marktracing } ;
syntax_node docdigi = { &docm , &doctr , TRUE , INITERM (KEYWORD, DOC_FORM) , markform } ;
syntax_node docform = { &docm , &docdigi , TRUE , INITERM (KEYWORD, DOC_ENTER) , markenter } ;
syntax_node doc     = { &docm , &docform , TRUE , INITERM (KEYWORD, DOC_TEXT) , marktext } ;


// Dokumentenkategorie
syntax_node dc5    = { NULL , NULL , TRUE , INITERM (KEYWORD, BRACECLOSE) , NULL } ;
syntax_node dc4    = { &dc5 , NULL , TRUE , INITERM (T_INTEGER, NULL) , setsubcat } ;
syntax_node dc3    = { &dc4 , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , NULL } ;
syntax_node dc2    = { &dc3 , &dc2 , TRUE , INITERM (KEYWORD, MPENT) , setmpent } ;
syntax_node dc1    = { &dc3 , &dc2 , TRUE , INITERM (KEYWORD, SINGLEENT) , setsingleent } ;
syntax_node dcat   = { &dc1 , NULL , TRUE , INITERM (KEYWORD, CATEGORY) , NULL } ;

// Icon - Definition
syntax_node dic1  = { NULL  , NULL , TRUE , INITERM (STRING,0) , storeiconfile } ;
syntax_node dicon = { &dic1 , NULL , TRUE , INITERM (KEYWORD,KWICON), NULL } ;

// Export - Statement
syntax_node expkont = { NULL , NULL , TRUE , INITERM (KEYWORD,KWEXPORTKONTEXT) , markExportKontext } ;

// Import - Statement
extern syntax_node impkont1;
syntax_node impkont3 = { &impkont1 , NULL , TRUE , INITERM (KEYWORD,COLON) , NULL } ;
syntax_node impkont2 = { NULL , &impkont3 , TRUE , INITERM (KEYWORD,SEMICOLON) , NULL } ;
syntax_node impkont1 = { &impkont2 , NULL , TRUE , INITERM (STRING,0) , importKontext } ;
syntax_node impkont  = { &impkont1 , NULL , TRUE , INITERM (KEYWORD,KWIMPORTKONTEXT) , NULL } ;

// Base - Statement
void SetBaseModule ();
extern syntax_node base1;
syntax_node base3 = { &base1 , NULL ,   TRUE , INITERM (KEYWORD,COLON) , NULL } ;
syntax_node base2 = { NULL ,   &base3 , TRUE , INITERM (KEYWORD,SEMICOLON) , NULL } ;
syntax_node base1 = { &base2 , NULL ,   TRUE , INITERM (STRING,0) , SetBaseModule } ;
syntax_node base  = { &base1 , NULL ,   TRUE , INITERM (KEYWORD,KWBASE) , NULL } ;

// Import_Virtual - Statement
void SetVirtualModule ();
extern syntax_node impvirt1;
syntax_node impvirt3 = { &impvirt1 , NULL ,    TRUE , INITERM (KEYWORD,COLON) ,           NULL } ;
syntax_node impvirt2 = { NULL ,    &impvirt3 , TRUE , INITERM (KEYWORD,SEMICOLON) ,       NULL } ;
syntax_node impvirt1 = { &impvirt2 , NULL ,    TRUE , INITERM (STRING,0) ,                SetVirtualModule } ;
syntax_node impvirt  = { &impvirt1 , NULL ,    TRUE , INITERM (KEYWORD,KWIMPORTVIRTUAL) , NULL } ;

// 9. Dokumentdefinition
extern syntax_node pd5;
extern syntax_node scn;
syntax_node pd11   = { NULL , NULL , TRUE  , INITERM (FREECHAR, 0) , NULL } ;
syntax_node pd10   = { &pd11, NULL , FALSE , &scn , NULL } ;
syntax_node pd9    = { &pd10, &pd10, FALSE , &expkont , NULL } ;
syntax_node pd8    = { &pd9 , &pd9 , FALSE , &dicon , NULL } ;
syntax_node pd7    = { &pd8 , &pd8 , FALSE , &dcat , NULL } ;
syntax_node pd3    = { &pd7 , NULL , FALSE , &doc , NULL } ;
syntax_node pd2    = { &pd3 , NULL , TRUE , INITERM (KEYWORD, DOCTYP) , NULL } ;
syntax_node pd1    = { &pd2 , NULL , TRUE , INITERM (STRING, 0) , strore_fullname } ;
syntax_node pd0    = { &pd1 , NULL , TRUE , INITERM (KEYWORD, FULLNAME) , NULL } ;

// Parameter in Funktionsprototypen
// = int | dec | string | strvar | intvar | decvar | pointvar | contvar | strarr | flag
syntax_node pd_datetvar = { NULL , NULL          , TRUE , INITERM (KEYWORD , PARDATETIMEVAR) , pushpartype } ;
syntax_node pd_objvar   = { NULL , &pd_datetvar  , TRUE , INITERM (KEYWORD , PAROBJVAR) , pushpartype } ;
syntax_node pd_blobvar  = { NULL , &pd_objvar    , TRUE , INITERM (KEYWORD , PARBLOBVAR) , pushpartype } ;
syntax_node pd_qwordvar = { NULL , &pd_blobvar   , TRUE , INITERM (KEYWORD , QLONGVAR) , pushpartype } ;
syntax_node pd_dwordvar = { NULL , &pd_qwordvar  , TRUE , INITERM (KEYWORD , PARDWORDVAR) , pushpartype } ;
syntax_node pd_imagevar = { NULL , &pd_dwordvar  , TRUE , INITERM (KEYWORD , PARIMAGE) , pushpartype } ;
syntax_node pd_procvar  = { NULL , &pd_imagevar  , TRUE , INITERM (KEYWORD , PARPROCVAR) , pushpartype } ;
syntax_node pd_timevar  = { NULL , &pd_procvar   , TRUE , INITERM (KEYWORD , PARTIMEVAR) , pushpartype } ;
syntax_node pd_datevar  = { NULL , &pd_timevar   , TRUE , INITERM (KEYWORD , PARDATEVAR) , pushpartype } ;
syntax_node pd_bitvar   = { NULL , &pd_datevar   , TRUE , INITERM (KEYWORD , PARPICTVAR) , pushpartype } ;
syntax_node pd_pictvar  = { NULL , &pd_bitvar    , TRUE , INITERM (KEYWORD , PARBITMAPVAR) , pushpartype } ;
syntax_node pd_scalevar = { NULL , &pd_pictvar   , TRUE , INITERM (KEYWORD , PARSCALEVAR) , pushpartype } ;
syntax_node pd_flagvar  = { NULL , &pd_scalevar  , TRUE , INITERM (KEYWORD , PARFLAGVAR) , pushpartype } ;
syntax_node pd_strarrvar= { NULL , &pd_flagvar   , TRUE , INITERM (KEYWORD , PARSTRARR) , pushpartype } ;
syntax_node pd_contvar  = { NULL , &pd_strarrvar , TRUE , INITERM (KEYWORD , PARCONTVAR) , pushpartype } ;
syntax_node pd_pointvar = { NULL , &pd_contvar , TRUE , INITERM (KEYWORD , PARPOINTVAR) , pushpartype } ;
syntax_node pd_decvar   = { NULL , &pd_pointvar, TRUE , INITERM (KEYWORD , PARDECVAR) , pushpartype } ;
syntax_node pd_intvar   = { NULL , &pd_decvar,   TRUE , INITERM (KEYWORD , PARINTVAR) , pushpartype } ;
syntax_node pd_strvar   = { NULL , &pd_intvar,   TRUE , INITERM (KEYWORD , PARSTRVAR) , pushpartype } ;
syntax_node pd_string   = { NULL , &pd_strvar,   TRUE , INITERM (KEYWORD , PARSTRING) , pushpartype } ;
syntax_node pd_dec      = { NULL , &pd_string,   TRUE , INITERM (KEYWORD , PARDEC) , pushpartype } ;
syntax_node pd          = { NULL , &pd_dec,      TRUE , INITERM (KEYWORD , PARINT) , pushpartype } ;

// 10. Lokale Funktion
syntax_node fncpar1 = { NULL , NULL , TRUE , INITERM (UNKNOWNIDENT, 0) , setfncpar } ;
syntax_node fncpar = { &fncpar1 , NULL , FALSE , &pd , NULL } ;

extern syntax_node ifnc_fe;
syntax_node ifnc_stt = { &ifnc_fe , NULL , FALSE , &statement , NULL } ;
syntax_node ifnc_fe = { NULL , &ifnc_stt , TRUE , INITERM (KEYWORD, CBRACECLOSE) , storefnc } ;
syntax_node ifnc_fs = { &ifnc_fe , NULL , TRUE , INITERM (KEYWORD, CBRACEOPEN) , startfnc } ;
extern syntax_node ifnc_par;
syntax_node ifnc_parcol = { &ifnc_par , NULL , TRUE , INITERM (KEYWORD, COLON) , NULL } ;
syntax_node ifnc_bc1 = { &ifnc_fs , &ifnc_parcol , TRUE , INITERM (KEYWORD, BRACECLOSE) , endinlinepar } ;
syntax_node ifnc_par = { &ifnc_bc1, NULL , FALSE , &fncpar , NULL } ;
syntax_node ifnc_bc = { &ifnc_fs , &ifnc_par , TRUE , INITERM (KEYWORD, BRACECLOSE) , endinlinepar } ;
syntax_node ifnc_bo = { &ifnc_bc , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , startinlinepar } ;
syntax_node ifnc_name = { &ifnc_bo , NULL , TRUE , INITERM (UNKNOWNIDENT, 0) , storeinlinename } ;
syntax_node ifnc   = { &ifnc_name , NULL , TRUE , INITERM (KEYWORD, INLINE) , startinlinefunction } ;

syntax_node enumbc   = { NULL      , NULL , TRUE , INITERM (KEYWORD,ARRBRACECLOSE), NULL } ;
syntax_node enumi    = { &enumbc   , NULL , TRUE , INITERM (T_INTEGER,0), FixupEnumEle } ;
syntax_node enumbo   = { &enumi    , NULL , TRUE , INITERM (KEYWORD,ARRBRACEOPEN), NULL } ;
syntax_node enumname = { &enumbo   , NULL , TRUE , INITERM (ENUMVARID,0), NULL } ;
syntax_node enumele  = { &enumname , NULL , TRUE , INITERM (KEYWORD,STERN), NULL } ;

// 11. Aufruf einer lokalen Funktion
syntax_node flcpar_ee    = { NULL , NULL , FALSE , &enumele , NULL } ;
syntax_node flcpar_enum  = { NULL , &flcpar_ee , TRUE , INITERM (ENUMVARID, 0) , FixupEnumPar } ;
syntax_node flcpar_const = { NULL , &flcpar_enum , FALSE , &constdef , FixupConstPar } ;
syntax_node flcpar_int  = { NULL , &flcpar_const , TRUE , INITERM (T_INTEGER, 0) , FixupPar } ;
syntax_node flcpar_dec  = { NULL , &flcpar_int , TRUE , INITERM (DECIMAL, 0) , FixupPar } ;
syntax_node flcpar      = { NULL , &flcpar_dec , TRUE , INITERM (VARID, 0) , FixupPar } ;

extern syntax_node flc_p;
extern syntax_node flc_c;
syntax_node flc_bc0 = { NULL , &flc_p , TRUE , INITERM (KEYWORD, BRACECLOSE) , pushprog } ;
syntax_node flc_bc1 = { NULL , &flc_c , TRUE , INITERM (KEYWORD, BRACECLOSE) , pushprog } ;
syntax_node flc_p   = { &flc_bc1 , NULL , FALSE , &flcpar, NULL } ;
syntax_node flc_c   = { &flc_p , NULL , TRUE , INITERM (KEYWORD, COLON) , NULL } ;
syntax_node flc_bo  = { &flc_bc0 , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , makeprogcopy } ;
syntax_node flc     = { &flc_bo , NULL , TRUE , INITERM (LOCALFUNCTIONID, 0) , startInlineCall } ;

// 12. Enum - Variable
syntax_node evar_const = { NULL , NULL , FALSE , &constdef , StoreEnumConstVar } ;
syntax_node evar_int   = { NULL , &evar_const , TRUE , INITERM (T_INTEGER, 0) , StoreEnumInt } ;
syntax_node evar_dec   = { NULL , &evar_int , TRUE , INITERM (DECIMAL, 0) , StoreEnumDec } ;
syntax_node evar       = { NULL , &evar_dec , TRUE , INITERM (VARID, 0) , StoreEnumVar } ;

extern syntax_node enum_var ;
syntax_node enum_c    = { &enum_var , NULL , TRUE , INITERM (KEYWORD, COLON) , NULL } ;
syntax_node enum_bcc  = { NULL , &enum_c , TRUE , INITERM (KEYWORD, CBRACECLOSE) , storeenum } ;
syntax_node enum_var  = { &enum_bcc , NULL , FALSE , &evar , NULL } ;
syntax_node enum_bco  = { &enum_var , NULL , TRUE , INITERM (KEYWORD , CBRACEOPEN) , NULL } ;
syntax_node enum_eq   = { &enum_bco , NULL , TRUE , INITERM (KEYWORD , EQUAL) , NULL } ;
syntax_node enum_name = { &enum_eq , NULL , TRUE , INITERM (UNKNOWNIDENT, 0) , storeinlinename } ;
syntax_node enum_typ  = { &enum_name , NULL , FALSE , &pd , storeenumtype } ;
syntax_node enumdef   = { &enum_typ , NULL , TRUE , INITERM (KEYWORD, ENUM) , inclevel } ;

// 13. loop einer inline funktion
extern syntax_node loop_cv ;
syntax_node loop_fnc  = { NULL , NULL , FALSE , &flc , NULL } ;
syntax_node loop_c    = { &loop_cv , NULL , TRUE , INITERM (KEYWORD, COLON) , NULL } ;
syntax_node loop_cc   = { &loop_fnc , &loop_c , TRUE , INITERM (KEYWORD, ARRBRACECLOSE) , NULL } ;
syntax_node loop_cv   = { &loop_cc , NULL , TRUE , INITERM (ENUMVARID, 0) , setloopcount } ;
syntax_node loop_co   = { &loop_cv , NULL , TRUE , INITERM (KEYWORD, ARRBRACEOPEN) , NULL } ;
syntax_node loopdef   = { &loop_co , NULL , TRUE , INITERM (KEYWORD, LOOP) , NULL } ;

// Programm
extern syntax_node vb1 ;
extern syntax_node stt;
extern syntax_node tbuse;
extern syntax_node alias;
syntax_node prgend    = { NULL , &stt , TRUE , INITERM (KEYWORD,PRGEND) , endproc } ;
syntax_node stt       = { &prgend , NULL , FALSE , &statement , NULL } ;
syntax_node progdef   = { &prgend , NULL , FALSE , &pd0 , NULL } ;
syntax_node prgstart  = { &progdef , &vb1 , TRUE , INITERM (KEYWORD,PRGSTART) , markstart } ;
syntax_node st_vfnc   = { &prgstart , NULL , FALSE , &vf_start , NULL } ;
syntax_node vb7       = { &prgstart , &st_vfnc  , FALSE , &alias, NULL } ;
syntax_node vb6b      = { &prgstart , &vb7  , FALSE , &impvirt, NULL } ;
syntax_node vb6a      = { &prgstart , &vb6b , FALSE , &base, NULL } ;
syntax_node vb6       = { &prgstart , &vb6a , FALSE , &impkont, NULL } ;
syntax_node vb5       = { &prgstart , &vb6  , FALSE , &tbuse , NULL } ;
syntax_node vb4       = { &prgstart , &vb5  , FALSE , &enumdef , NULL } ;
syntax_node vb3       = { &prgstart , &vb4  , FALSE , &ifnc , NULL } ;
syntax_node vb2       = { &prgstart , &vb3  , FALSE , &proc , NULL } ;
syntax_node vb1b      = { &prgstart , &vb2  , FALSE , &_view , NULL } ;
syntax_node vb1a      = { &prgstart , &vb1b , FALSE , &_struct , NULL } ;
syntax_node vb1       = { &prgstart , &vb1a , FALSE , &vdef , NULL } ;

extern syntax_node mvb1,nscn110;
syntax_node mst_vf     = { NULL , NULL , FALSE , &vf_start , NULL } ;
syntax_node mvb8       = { NULL , &mst_vf , FALSE , &nscn110, NULL } ;
syntax_node mvb7       = { NULL , &mvb8  , FALSE , &alias, NULL } ;
syntax_node mvb6b      = { NULL , &mvb7  , FALSE , &impvirt, NULL } ;
syntax_node mvb6a      = { NULL , &mvb6b , FALSE , &base, NULL } ;
syntax_node mvb6       = { NULL , &mvb6a , FALSE , &impkont, NULL } ;
syntax_node mvb5       = { NULL , &mvb6  , FALSE , &tbuse , NULL } ;
syntax_node mvb4       = { NULL , &mvb5  , FALSE , &enumdef , NULL } ;
syntax_node mvb3       = { NULL , &mvb4  , FALSE , &ifnc , NULL } ;
syntax_node mvb2       = { NULL , &mvb3  , FALSE , &proc , NULL } ;
syntax_node mvb1b      = { NULL , &mvb2  , FALSE , &_view , NULL } ;
syntax_node mvb1a      = { NULL , &mvb1b , FALSE , &_struct , NULL } ;
syntax_node mvb1       = { NULL , &mvb1a , FALSE , &vdef , NULL } ;

syntax_node prog = { NULL , NULL , FALSE , &prgstart , NULL } ;
extern syntax_node mod;
syntax_node modend = { NULL , &mod , TRUE , INITERM (KEYWORD,PRGEND) , NULL } ;
syntax_node mod = { &modend , NULL , FALSE , &mvb1 , NULL } ;

////////////////////////////////////////////////////////////////////////
//      Expressions
////////////////////////////////////////////////////////////////////////

// Terminalsymbole
///////////////////////////

syntax_node const_explf    = { NULL , NULL , FALSE   , &fconst , NULL } ;
syntax_node const_expldw   = { NULL , &const_explf , FALSE   , &dwconst , NULL } ;
syntax_node const_explpt   = { NULL , &const_expldw  , FALSE , &ptconst , setconstpt } ;
syntax_node const_explstr  = { NULL , &const_explpt  , TRUE , INITERM (STRING , 0) , setconststr } ;
syntax_node const_explind  = { NULL , &const_explstr , TRUE , INITERM (T_INTEGER, 0) , setconstind } ;
syntax_node const_explicit = { NULL , &const_explind , TRUE , INITERM (DECIMAL, 0) , setconstdec } ;

void SetNextType();
syntax_node tm9        = { NULL , NULL , TRUE , INITERM(KEYWORD,TOFLAG) , SetNextType } ;
syntax_node tm8        = { NULL , &tm9 , TRUE , INITERM(KEYWORD,TODATETIME) , SetNextType } ;
syntax_node tm7        = { NULL , &tm8 , TRUE , INITERM(KEYWORD,TOOBJ) , SetNextType } ;
syntax_node tm6        = { NULL , &tm7 , TRUE , INITERM(KEYWORD,TOBLOB) , SetNextType } ;
syntax_node tm5        = { NULL , &tm6 , TRUE , INITERM(KEYWORD,TOSTRING) , SetNextType } ;
syntax_node tm4        = { NULL , &tm5 , TRUE , INITERM(KEYWORD,TOTIME) , SetNextType } ;
syntax_node tm3        = { NULL , &tm4 , TRUE , INITERM(KEYWORD,TODATE) , SetNextType } ;
syntax_node tm2        = { NULL , &tm3 , TRUE , INITERM(KEYWORD,TOFLOAT) , SetNextType } ;
syntax_node tm1        = { NULL , &tm2 , TRUE , INITERM(KEYWORD,TOLONG) , SetNextType } ;
syntax_node typemodify = { NULL , &tm1 , TRUE , INITERM(KEYWORD,TOSHORT) , SetNextType } ;

syntax_node termsym_5 = { NULL , NULL , TRUE , INITERM (VARID, 0)  , createvarnode } ;
syntax_node termsym_4 = { &termsym_5 , NULL , FALSE , &typemodify , NULL } ;
syntax_node termsym_3 = { NULL , &termsym_4 , FALSE , &const_explicit , createconstnode } ;
syntax_node termsym_2 = { NULL , &termsym_3 , FALSE , &constdef , createconstnode } ;
syntax_node termsym_1 = { NULL , &termsym_2 , TRUE , INITERM (PARID, 0) , createparnode } ;
syntax_node termsym   = { NULL , &termsym_1 , TRUE , INITERM (VARID, 0) , createvarnode } ;

// Einfache Expressions
////////////////////////////
extern syntax_node sexp;
extern syntax_node fncexp;
extern syntax_node expression;
void createfncnode_v ();
void createfncnode_n ();
void ExchangeTableToReuse();

syntax_node etptr3 = { NULL , NULL , TRUE , INITERM(KEYWORD,ARRBRACECLOSE) , VarCheckOn } ;
syntax_node etptr2 = { &etptr1 , &etptr3 , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node etptr1a = { &etptr2 , NULL , TRUE , INITERM(VARID,0) , ExchangeTableToReuse } ;
syntax_node etptr1  = { &etptr2 , &etptr1a , TRUE , INITERM(UNKNOWNIDENT,0) , ExchangeTableToReuse } ;
syntax_node etptr  = { &etptr1 , NULL , TRUE , INITERM(KEYWORD,ARRBRACEOPEN) , VarCheckOff } ;

syntax_node sexp_end = { NULL , NULL , TRUE , INITERM (FREECHAR, 0) , NULL } ;
syntax_node sexp_vfc2 = { &fncbo , &fncbo , FALSE , &etptr , MarkTableToReuse } ;
syntax_node sexp_vfc1 = { &sexp_vfc2 , &sexp_vfc2 , TRUE , INITERM (KEYWORD,KWSTATIC) , patchcmpltstatic } ;
syntax_node sexp_vfc = { &sexp_vfc1 , &sexp_end , TRUE , INITERM (VFNCEXP,0) , createfncnode_v } ;
syntax_node sexp_op =  { &sexp , &sexp_vfc , TRUE , INITERM (BINOP, 0) , createopnode } ;
syntax_node sexp_fc =  { &sexp_op , NULL , FALSE , &fncexp , setopallowed } ;
syntax_node sexp_ts =  { &sexp_op , &sexp_fc , FALSE , &termsym , setopallowed } ;
syntax_node sexp_bc =  { &sexp_op , NULL , TRUE , INITERM (KEYWORD, BRACECLOSE) , popexpression1 } ;
syntax_node sexp_exp = { &sexp_bc , NULL , FALSE , &expression , NULL } ;
syntax_node sexp =     { &sexp_exp , &sexp_ts , TRUE , INITERM (KEYWORD, BRACEOPEN) , pushexpression } ;

extern syntax_node fncep;
//syntax_node fncbc1  = { &sexp_op  , &fncep , TRUE , INITERM (KEYWORD , BRACECLOSE) , popexpression1 } ;
syntax_node fncbc1  = { &sexp_op  , &fncep , TRUE , INITERM (KEYWORD , BRACECLOSE) , popexpression2 } ;
syntax_node fncbc   = { &sexp_op  , NULL , TRUE , INITERM (KEYWORD , BRACECLOSE) , popexpression2 } ;
syntax_node fncc    = { &fncep , &fncbc , TRUE , INITERM (KEYWORD, COLON) , poppush } ;
syntax_node fncep   = { &fncc  , NULL , FALSE , &expression , NULL } ;
syntax_node fncbo   = { &fncbc1 , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , pushexpression } ;
syntax_node vfncbo  = { &fncbc1 , NULL , TRUE , INITERM (KEYWORD, BRACEOPEN) , NULL } ;
syntax_node fncexp2 = { &fncbo , &fncbo , FALSE , &etptr , MarkTableToReuse } ;
syntax_node fncexp1 = { &fncexp2 , &fncexp2 , TRUE , INITERM (KEYWORD, KWSTATIC) , patchcmpltstatic } ;
syntax_node fncexp  = { &fncexp1 , NULL , TRUE , INITERM (FNCEXP, 0) , createfncnode_n } ;


syntax_node exp2       = { NULL , NULL , TRUE , INITERM(KEYWORD,KWNULL) , pushnull } ;
syntax_node exp1       = { NULL , &exp2 , FALSE , &sexp , NULL } ;
syntax_node expression = { NULL , &exp1 , FALSE , &fncexp , NULL } ;

// Tabellendefinition
extern syntax_node tbuse1;
extern syntax_node tbuse20;
void PushStructDataToConst();
syntax_node tbuse3  = { NULL      , NULL     , TRUE , INITERM(KEYWORD,SEMICOLON) , VarCheckOn_UseTable } ;
syntax_node tbuse2a = { &tbuse1   , &tbuse3  , TRUE , INITERM(KEYWORD,COLON) , UseTable } ;
syntax_node tbuse22 = { &tbuse2a  , NULL     , TRUE , INITERM(KEYWORD,CBRACECLOSE) , PushStructDataToConst } ;
syntax_node tbuse21 = { &tbuse20  , &tbuse22 , TRUE , INITERM(KEYWORD,COLON), NULL } ;
syntax_node tbuse20 = { &tbuse21  , NULL     , FALSE , &ut , NULL } ;
syntax_node tbuse2  = { &tbuse20  , &tbuse2a , TRUE , INITERM(KEYWORD,CBRACEOPEN) , NULL } ;
syntax_node tbuse1a = { &tbuse2a  , &tbuse2  , TRUE , INITERM(UNKNOWNIDENT,0) , SetAliasTable } ;
syntax_node tbuse1  = { &tbuse1a  , NULL     , TRUE , INITERM(UNKNOWNIDENT,0) , SetTableName } ;
syntax_node tbuse   = { &tbuse1   , NULL     , TRUE , INITERM(KEYWORD,KWUSETABLE) , VarCheckOff } ;

// Aliasdefinition
extern syntax_node alias1;
syntax_node alias5 = { NULL    , NULL    , TRUE , INITERM(KEYWORD,SEMICOLON) , NULL } ;
syntax_node alias4 = { &alias1 , &alias5 , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node alias3 = { &alias4 , NULL    , TRUE , INITERM(VARID,0) , SetAliasVar } ;
syntax_node alias2 = { &alias3 , NULL    , TRUE , INITERM(KEYWORD,EQUAL) , NULL } ;
syntax_node alias1 = { &alias2 , NULL    , TRUE , INITERM(UNKNOWNIDENT,0) , SetAliasName } ;
syntax_node alias  = { &alias1 , NULL    , TRUE , INITERM(KEYWORD,KWALIAS) , NULL } ;

// ScriptHeader
syntax_node nscn113 = { NULL     , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node nscn112 = { &nscn113 , NULL , TRUE , INITERM(STRING,0), SetProperty } ;
syntax_node nscn111 = { &nscn112 , NULL , TRUE , INITERM(KEYWORD,EQUAL), NULL } ;
syntax_node nscn110 = { &nscn111 , NULL , TRUE , INITERM(KEYWORD,PROPERTY), NULL } ;

syntax_node scn114 = { NULL    , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn113 = { NULL    , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn112 = { &scn113 , NULL , TRUE , INITERM(STRING,0), SetProperty } ;
syntax_node scn111 = { &scn112 , NULL , TRUE , INITERM(KEYWORD,EQUAL), NULL } ;
syntax_node scn110 = { &scn111 , &scn114 , TRUE , INITERM(KEYWORD,PROPERTY), NULL } ;

syntax_node scn102 = { NULL    , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn101 = { NULL    , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn100 = { &scn101 , &scn102 , TRUE , INITERM(KEYWORD,NOMDI), SetNoMDI } ;

syntax_node scn93 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn92 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn91 = { &scn92 , NULL , TRUE , INITERM(UNKNOWNIDENT,0), SetOptionScript } ;
syntax_node scn90 = { &scn91 , &scn93 , TRUE , INITERM(KEYWORD,OPTSC), NULL } ;

syntax_node scn83 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn82 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn81 = { &scn82 , NULL , TRUE , INITERM(UNKNOWNIDENT,0), SetDefaultVerweisSpeicherer } ;
syntax_node scn80 = { &scn81 , &scn83 , TRUE , INITERM(KEYWORD,DEFVSP), NULL } ;

syntax_node scn73 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn72 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn71 = { &scn72 , NULL , TRUE , INITERM(UNKNOWNIDENT,0), SetDefaultVerweisErzeuger } ;
syntax_node scn70 = { &scn71 , &scn73 , TRUE , INITERM(KEYWORD,DEFVER), NULL } ;

syntax_node scn63 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn62 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn61 = { &scn62 , NULL , TRUE , INITERM(UNKNOWNIDENT,0), SetBearbeiteSelektor } ;
syntax_node scn60 = { &scn61 , &scn63 , TRUE , INITERM(KEYWORD,BESEL), NULL } ;

syntax_node scn52 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn51 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn50 = { &scn51 , &scn52 , TRUE , INITERM(KEYWORD,ISTVS), SetIstVerweisSpeicherer } ;

syntax_node scn42 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn41 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn40 = { &scn41 , &scn42 , TRUE , INITERM(KEYWORD,ISTVE), SetIstVerweisErzeuger } ;

syntax_node scn32 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn31 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn30 = { &scn31 , &scn32 , TRUE , INITERM(KEYWORD,DIKV), SetDarfInKrankengeschichteVorkommen } ;

syntax_node scn22 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn21 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn20 = { &scn21 , &scn22 , TRUE , INITERM(KEYWORD,DIVV), SetDarfImVerzeichnisVorkommen } ;

syntax_node scn12 = { NULL   , NULL , TRUE , INITERM(FREECHAR,0), NULL } ;
syntax_node scn11 = { NULL   , NULL , TRUE , INITERM(KEYWORD,SEMICOLON), NULL } ;
syntax_node scn10 = { &scn11 , &scn12 , TRUE , INITERM(KEYWORD,DIFS), SetDarfInFachsein } ;

syntax_node scn1a = { NULL   , NULL , FALSE , &scn110 , NULL } ;
syntax_node scn9  = { &scn1a , NULL , FALSE , &scn100 , NULL } ;
syntax_node scn8  = { &scn9  , NULL , FALSE , &scn90  , NULL } ;
syntax_node scn7  = { &scn8  , NULL , FALSE , &scn80  , NULL } ;
syntax_node scn6  = { &scn7  , NULL , FALSE , &scn70  , NULL } ;
syntax_node scn5  = { &scn6  , NULL , FALSE , &scn60  , NULL } ;
syntax_node scn4  = { &scn5  , NULL , FALSE , &scn50  , NULL } ;
syntax_node scn3  = { &scn4  , NULL , FALSE , &scn40  , NULL } ;
syntax_node scn2  = { &scn3  , NULL , FALSE , &scn30  , NULL } ;
syntax_node scn1  = { &scn2  , NULL , FALSE , &scn20  , NULL } ;
syntax_node scn   = { &scn1  , NULL , FALSE , &scn10  , NULL } ;
                            
// Forschleife
///////////////////////////
syntax_node fvar_noinit = { NULL        , NULL         , TRUE  , INITERM(FREECHAR,0) , setfreevarhash } ;
syntax_node fvar_init1  = { NULL        , NULL         , FALSE , &expression , matchexpression } ;
syntax_node fvar_init   = { &fvar_init1 , &fvar_noinit , TRUE  , INITERM (KEYWORD,EQUAL) , setfreevarhash_withres } ;

syntax_node fvdef3  = { NULL    , NULL    , FALSE , &fvar_init , NULL } ;
syntax_node fvdef2  = { &fvdef3 , NULL    , TRUE  , INITERM(UNKNOWNIDENT,0) , setvarname } ;
syntax_node fvdef1  = { &fvdef2 , NULL    , FALSE , &vt        , NULL } ;
syntax_node fvdef   = { &fvdef1 , &fvdef1 , FALSE , &vb        , NULL } ;

syntax_node fst3         = { NULL , NULL  , FALSE , &fncexp , matchexpression } ;
syntax_node fst2         = { NULL , &fst3 , FALSE , &_for  , NULL } ;
syntax_node fst1         = { NULL , &fst2 , FALSE , &if_statement  , NULL } ;
syntax_node forStatement = { NULL , &fst1 , FALSE , &sing_statement , NULL } ;

extern syntax_node forBlock,fh6a,fdb11,fil3,fil;
extern void markforBlock ();
extern void markfor ();
extern void setfortable ();
extern void fortype_cond ();
extern void fortype_select ();
extern void setforobj ();
extern void setforparam ();
extern void fortype_dbsel ();
extern void pushdbselpar ();
extern void pushselectpar ();
extern void SetDBName ();
extern void SetDBSelCount ();
extern void SetDBSelReverse ();
extern void SetWhereExp ();
extern void SetOrderExp ();
extern void SetDBForExp ();
extern void fortype_innerobj ();
extern void fortype_outerobj ();
extern void SetObjTableNr ();
extern void SetObjCondVar ();
extern void fortype_initlist ();
extern void PushInitListExpression ();
extern void PushInitVar ();
extern void noforblock ();
extern void forendproc ();
syntax_node fbEnd    = { NULL      , NULL   , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node fbNext1  = { NULL      , NULL   , FALSE , &forBlock , NULL } ;
syntax_node fbNext   = { &fbNext1  , &fbEnd , TRUE  , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fb1      = { &fbNext   , &fbEnd , FALSE , &fvdef , NULL } ;
syntax_node forBlock = { &fbNext   , &fb1 , FALSE , &forStatement , NULL } ;

extern syntax_node fse3;
syntax_node fse5    = { NULL   , NULL   , TRUE , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node fse4    = { &fse3  , &fse5  , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fse3    = { &fse4  , &fse5  , FALSE , &expression , SetDBForExp } ;
syntax_node fse2    = { &fse3  , NULL   , TRUE  , INITERM(KEYWORD,BRACEOPEN) , NULL } ;
syntax_node fse1    = { &fse2  , &fse2  , TRUE  , INITERM(T_INTEGER,0) , SetDBSelCount } ;
syntax_node fse0    = { &fse1  , NULL   , FALSE , &expression , pushselectpar } ;
syntax_node fse     = { &fse0  , &fse0  , TRUE  , INITERM(KEYWORD,DBSEL) , NULL } ;

syntax_node fdb13   = { NULL   , NULL   , TRUE , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node fdb12   = { &fdb11 , &fdb13 , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fdb11   = { &fdb12 , &fdb13 , FALSE , &expression , SetDBForExp } ;
syntax_node fdb9    = { &fdb11 , NULL   , TRUE  , INITERM(KEYWORD,BRACEOPEN) , NULL } ;
syntax_node fdb8    = { &fdb9  , NULL   , FALSE , &expression , SetOrderExp } ;
syntax_node fdb6    = { &fdb8  , &fdb9  , TRUE , INITERM(KEYWORD,ORDER) , NULL } ;
syntax_node fdb5    = { &fdb6  , NULL   , FALSE , &expression , SetWhereExp } ;
syntax_node fdb3    = { &fdb5  , NULL   , TRUE  , INITERM(KEYWORD,WHERE) , NULL } ;
syntax_node fdb2    = { &fdb3  , NULL   , TRUE  , INITERM(STRING,0) , SetDBName } ;
syntax_node fdb1    = { &fdb2  , NULL   , TRUE  , INITERM(KEYWORD,FROM) , NULL } ;
syntax_node fdbb    = { &fdb1  , &fdb1  , TRUE  , INITERM(KEYWORD,REVERSE) , SetDBSelReverse } ;
syntax_node fdba    = { &fdbb  , &fdbb  , TRUE  , INITERM(T_INTEGER,0) , SetDBSelCount } ;
syntax_node fdb     = { &fdba  , NULL   , TRUE  , INITERM(KEYWORD,SELECT) , pushdbselpar } ;
syntax_node fio3    = { NULL   , NULL   , TRUE , INITERM(FREECHAR,0) , VarCheckOn } ;
syntax_node fio2    = { &fio3  , &fio3  , TRUE , INITERM(UNKNOWNIDENT,0) , SetObjTableNr } ;
syntax_node fio1    = { &fio2  , NULL   , TRUE , INITERM(VARID,0) , SetObjCondVar } ;
syntax_node fio_a   = { &fio1  , &fio1  , TRUE , INITERM(KEYWORD,REVERSE) , SetReverse } ;
syntax_node fio     = { &fio_a , NULL   , TRUE , INITERM(KEYWORD,INNERLIST) , SetNormal } ;
syntax_node foo3    = { NULL   , NULL   , TRUE , INITERM(FREECHAR,0) , VarCheckOn } ;
syntax_node foo2    = { &fio3  , &fio3  , TRUE , INITERM(UNKNOWNIDENT,0) , SetObjTableNr } ;
syntax_node foo1    = { &fio2  , NULL   , TRUE , INITERM(VARID,0) , SetObjCondVar } ;
syntax_node foo     = { &foo1  , NULL   , TRUE , INITERM(KEYWORD,OUTERLIST) , NULL } ;

syntax_node fil8    = { NULL  , NULL  , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node fil7    = { &fil  , &fil8 , TRUE  , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fil6    = { &fil7 , NULL  , TRUE  , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node fil5    = { &fil3 , &fil6 , TRUE  , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fil3    = { &fil5 , NULL  , FALSE , &expression , PushInitListExpression } ;
syntax_node fil2    = { &fil3 , NULL  , TRUE  , INITERM(KEYWORD,BRACEOPEN) , NULL } ;
syntax_node fil1    = { &fil2 , NULL  , TRUE  , INITERM(KEYWORD,EQUAL) , NULL } ;
syntax_node fil     = { &fil1 , NULL  , TRUE  , INITERM(VARID,0) , PushInitVar } ;

syntax_node fc6     = { NULL , NULL , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node fc5     = { NULL , &fc6 , FALSE , &fse , fortype_select } ;
syntax_node fc4     = { NULL , &fc5 , FALSE , &fil , fortype_initlist } ;
syntax_node fc3     = { NULL , &fc4 , FALSE , &fio , fortype_innerobj } ;
syntax_node fc2     = { NULL , &fc3 , FALSE , &foo , fortype_outerobj } ;
syntax_node fc1     = { NULL , &fc2 , FALSE , &fdb , fortype_dbsel } ;
syntax_node forcond = { NULL , &fc1 , FALSE , &cond , fortype_cond } ;

syntax_node fh4    = { NULL , NULL , TRUE , INITERM(FREECHAR,0) , NULL } ;
syntax_node fh8    = { NULL , NULL , TRUE , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node fh7    = { &fh6a, &fh8 , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fh6    = { &fh7 , NULL , TRUE , INITERM(VARID,0) , setforparam } ;
syntax_node fh6a   = { &fh6 , &fh6 , FALSE, &typemodify , NULL } ;
syntax_node fh5    = { &fh6a, &fh4 , TRUE , INITERM(KEYWORD,BRACEOPEN) , NULL } ;
syntax_node fh3    = { &fh5 , &fh5 , TRUE , INITERM(STRING,0) , setfortable } ;
syntax_node fh2    = { &fh5 , NULL , TRUE , INITERM(STRING,0) , setfortable } ;
syntax_node fh1    = { &fh2 , NULL , TRUE , INITERM(KEYWORD,EQUAL) , NULL } ;
syntax_node forhd  = { &fh1 , &fh3 , TRUE , INITERM(VARID,0) , setforobj } ;

syntax_node _for11 = { NULL    , NULL    , FALSE , &block , forendproc } ;
syntax_node _for10 = { NULL    , &_for11 , TRUE  , INITERM(KEYWORD,SEMICOLON) , noforblock } ;
syntax_node _for9  = { &_for10 , NULL    , TRUE  , INITERM(KEYWORD,BRACECLOSE) , markforBlock } ;
syntax_node _for8  = { &_for9  , NULL    , FALSE , &forBlock , popstatement } ;
syntax_node _for7  = { &_for8  , NULL    , TRUE  , INITERM(KEYWORD,SEMICOLON) , inclevel_breakallowed } ;
syntax_node _for6  = { &_for7  , NULL    , FALSE , &forcond , NULL } ;
syntax_node _for5  = { &_for6  , NULL    , TRUE  , INITERM(KEYWORD,SEMICOLON) , NULL } ;
syntax_node _for4  = { &_for5  , NULL    , FALSE , &forBlock , popstatement } ;
syntax_node _for3  = { &_for4  , NULL    , TRUE  , INITERM(KEYWORD,SEMICOLON) , inclevel } ;
syntax_node _for2  = { &_for3  , NULL    , FALSE , &forhd , NULL } ;
syntax_node _for1  = { &_for2  , NULL    , TRUE  , INITERM(KEYWORD,BRACEOPEN) , NULL } ;
syntax_node _for   = { &_for1  , NULL    , TRUE  , INITERM(KEYWORD,FOR) , markfor } ;

// with - statement
///////////////////////////
extern syntax_node eqexp;
void SetWithTable ();
void SetInTableNr ();
void SetInsertTableNr ();
void SetRemoveTableNr ();
void PushWithVar ();
void PushWithVar_CheckOff ();
void PushWithBlock ();
void PushWithConst ();
void CheckExpRes ();
void PushInsertBlock ();
void SetInsertTypeBefore ();
void SetInsertTypeAfter ();
void PushRemoveBlock ();
void PushWithExp ();
void markwithblock ();
syntax_node eqe4   = { NULL   , NULL  , TRUE  , INITERM(FREECHAR,0) , NULL } ;
syntax_node eqe3   = { &eqexp , &eqe4 , TRUE  , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node eqe2   = { &eqe3  , NULL  , TRUE  , INITERM(VARID,0) , PushWithVar } ;
syntax_node eqe1   = { &eqe2  , NULL  , TRUE  , INITERM(KEYWORD,EQUAL) , NULL } ;
syntax_node eqexp  = { &eqe1  , NULL  , FALSE , &expression , PushWithExp } ;

syntax_node with8  = { NULL    , NULL   , TRUE  , INITERM (FREECHAR, 0) , marknoelse } ;
syntax_node with7  = { NULL    , NULL   , FALSE , &block , popstatement } ;
syntax_node with6  = { &with7  , &with8 , TRUE  , INITERM (KEYWORD, KWELSE) , markelse } ;
syntax_node with5  = { &with6  , NULL   , FALSE , &block , endproc } ;
syntax_node with4  = { &with5  , NULL   , TRUE  , INITERM(KEYWORD,BRACECLOSE) , markwithblock } ;
syntax_node with3  = { &with4  , NULL   , FALSE , &eqexp , NULL } ;
syntax_node with2  = { &with3  , NULL   , TRUE  , INITERM(KEYWORD,BRACEOPEN) , VarCheckOn } ;
syntax_node with1a = { &with2  , &with2 , TRUE  , INITERM(UNKNOWNIDENT,0) , SetWithTable } ;
// syntax_node with1  = { &with1a , NULL   , TRUE  , INITERM(VARID,0) , PushWithVar_CheckOff } ;
syntax_node with1  = { &with1a , NULL   , FALSE , &expression , PushWithVar_CheckOff } ;
syntax_node withb  = { &with1  , NULL   , TRUE  , INITERM(KEYWORD,DOWITH) , PushDoWithBlock } ;
syntax_node witha  = { &with1  , &withb , TRUE  , INITERM(KEYWORD,FORALL) , PushForAllBlock } ;
syntax_node with   = { &with1  , &witha , TRUE  , INITERM(KEYWORD,WITH) , PushWithBlock } ;

// in - condition (die erste Variable ist bereits als exp_res gespeichert)
////////////////////////////////////////////////////////////////////////////
extern syntax_node inc5;
syntax_node inc7    = { NULL     , NULL  , TRUE  , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node inc6    = { &inc5    , &inc7 , TRUE  , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node inc5    = { &inc6    , NULL  , TRUE  , INITERM(VARID,0) , PushWithVar } ;
syntax_node inc4    = { &inc5    , NULL  , TRUE  , INITERM(KEYWORD,BRACEOPEN) , VarCheckOn } ;
syntax_node inc3a   = { &inc4    , &inc4 , TRUE  , INITERM(UNKNOWNIDENT,0) , SetInTableNr } ;
syntax_node inc3    = { &inc3a   , NULL  , FALSE , &expression , PushWithVar_CheckOff } ;
syntax_node inc2    = { &inc3    , NULL  , TRUE  , INITERM(KEYWORD,KWIN) , CheckExpRes } ;
syntax_node inc1    = { &in_cond , NULL  , FALSE , &expression , NULL } ;
syntax_node in_cond = { &inc1    , &inc2 , TRUE  , INITERM(KEYWORD,COLON) , CheckExpRes } ;

// insert - statement
///////////////////////////
syntax_node isp2    = { NULL  , NULL  , FALSE , &eqexp , NULL } ;
syntax_node isp1    = { &isp2 , NULL  , TRUE  , INITERM(KEYWORD,BEFORE) , SetInsertTypeBefore } ;
syntax_node isp     = { &isp2 , &isp1 , TRUE  , INITERM(KEYWORD,AFTER) , SetInsertTypeAfter } ;

syntax_node is5     = { NULL  , NULL , FALSE , &block , popstatement } ;
syntax_node is4     = { &is5  , NULL , TRUE  , INITERM(KEYWORD,SET) , inclevel_CheckOn } ;
syntax_node is3a    = { &is4  , &is4 , TRUE  , INITERM(UNKNOWNIDENT,0) , SetInsertTableNr } ;
syntax_node is3     = { &is3a , NULL , FALSE , &expression , PushWithVar_CheckOff } ;
syntax_node is2     = { &is3  , NULL , TRUE  , INITERM(KEYWORD,INTO) , NULL } ;
syntax_node is1     = { &is2  , &is2 , FALSE , &isp , NULL } ;
syntax_node insert  = { &is1  , NULL , TRUE  , INITERM(KEYWORD,INSERT) , PushInsertBlock } ;

// remove - statement
////////////////////////////
syntax_node rm5     = { NULL  , NULL , TRUE  , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node rm4     = { &rm5  , NULL , FALSE , &eqexp , NULL } ;
syntax_node rm3     = { &rm4  , NULL , TRUE  , INITERM(KEYWORD,BRACEOPEN) , VarCheckOn } ;
syntax_node rm2a    = { &rm3  , &rm3 , TRUE  , INITERM(UNKNOWNIDENT,0) , SetRemoveTableNr } ;
syntax_node rm2     = { &rm2a , NULL , FALSE , &expression , PushWithVar_CheckOff } ;
syntax_node rm1     = { &rm2  , NULL , TRUE  , INITERM(KEYWORD,FROM) , NULL } ;
syntax_node _remove = { &rm1  , NULL , TRUE  , INITERM(KEYWORD,REMOVE) , PushRemoveBlock } ;

extern syntax_node str3,str2 ;
syntax_node str5     = { &str3 , NULL  , TRUE , INITERM(T_ALL,0) , NULL } ;
syntax_node str4     = { NULL , NULL  , TRUE , INITERM(KEYWORD,SEMICOLON) , GenerateStruct } ;
syntax_node str3     = { &str4 , &str5  , TRUE , INITERM(KEYWORD,CBRACECLOSE) , NULL } ;
syntax_node str2a    = { &str2 , NULL  , TRUE , INITERM(T_ALL,0) , NULL } ;
syntax_node str2     = { &str3 , &str2a  , TRUE , INITERM(KEYWORD,CBRACEOPEN) , NULL } ;
syntax_node str1a    = { &str2 , NULL  , TRUE , INITERM(VARID,0) , MarkStructName } ;
syntax_node str1     = { &str2 , &str1a , TRUE , INITERM(UNKNOWNIDENT,0) , MarkStructName } ;
syntax_node _struct  = { &str1 , NULL  , TRUE , INITERM(KEYWORD,STRUCT) , MarkStructStart } ;

extern syntax_node v3,v7 ;
syntax_node v8     = { &v7   , NULL  , TRUE , INITERM(T_ALL,0) , NULL } ;
syntax_node v7     = { &v3   , &v8   , TRUE , INITERM(KEYWORD,CBRACECLOSE) , NULL } ;
syntax_node v6     = { &v3   , NULL  , TRUE , INITERM(T_ALL,0) , NULL } ;
syntax_node v5     = { &v7   , &v6   , TRUE , INITERM(KEYWORD,CBRACEOPEN) , NULL } ;
syntax_node v4     = { NULL  , NULL  , TRUE , INITERM(KEYWORD,SEMICOLON) , GenerateView } ;
syntax_node v3     = { &v4   , &v5   , TRUE , INITERM(KEYWORD,CBRACECLOSE) , NULL } ;
syntax_node v2     = { &v3   , NULL  , TRUE , INITERM(KEYWORD,CBRACEOPEN) , NULL } ;
syntax_node v1b    = { &v2   , NULL  , TRUE , INITERM(KEYWORD,EQUAL) , NULL } ;
syntax_node v1a    = { &v1b  , NULL  , TRUE , INITERM(VARID,0) , MarkStructName } ;
syntax_node v1     = { &v1b  , &v1a  , TRUE , INITERM(UNKNOWNIDENT,0) , MarkStructName } ;
syntax_node _view  = { &v1   , NULL  , TRUE , INITERM(KEYWORD,VIEW) , MarkViewStart } ;

#else

// Als Einstieg wird der Knoten prog verwendet
extern syntax_node prog;
extern syntax_node mod;

#endif

