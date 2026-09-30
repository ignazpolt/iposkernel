//-----------------------------------------------------------------------
// fsyntax.hpp - Syntax fuer die Funktionsprototypenerstellung
//
// $Header:   P:/marille/clinicum/include/rev/fsyntax.hpv   1.12   09 May 2000 15:40:10   Wolfgang  $
// $Log:   P:/marille/clinicum/include/rev/fsyntax.hpv  $
// 
//    Rev 1.12   09 May 2000 15:40:10   Wolfgang
// 1.) Syntax fuer optionale Parameter korrigiert.
// 
//    Rev 1.11   16 Feb 2000 15:02:48   Wolfgang
// 1.) Neue FDEF-Syntax.
// 
//    Rev 1.10   04 Aug 1998 17:48:16   Hannes
// Timestamp
// 
//    Rev 1.9   17 May 1998 17:52:40   Hannes
// Variable viele Parameter
// 
//    Rev 1.8   13 Mar 1997 19:07:22   Hannes
// blobs
// 
//    Rev 1.7   08 Nov 1996 13:25:04   HANNES
// Einbau von QLong
// 
//    Rev 1.6   02 Feb 1996 11:01:22   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.5   27 Jun 1995 13:55:22   HANNES
// Auch Bitmaps und Bilder in Expressions zulassen
// 
//    Rev 1.4   15 May 1995 08:23:04   HANNES
// structs im normalen Script
// 
//    Rev 1.3   28 Apr 1995 17:17:48   HANNES
// 
//    Rev 1.2   05 Dec 1994 17:37:30   HANNES
// Endgueltiger Einbau der Expressions
// 
//    Rev 1.1   08 Aug 1994 10:14:26   HANNES
// PARTIMEVAR
// 
//    Rev 1.0   24 Jun 1994 17:52:54   HANNES
// Initial revision.
//-----------------------------------------------------------------------
#define INITERM(A,B) ((struct syntax_node *) ((A) + ((B) << 8)))

void pushprototypepar (void);
void setfunchash (void);
void storefncnumber (void);        
void setfuncname (void);
void inclevel (void);
void defoparg (void);
void defopres (void);
void CheckAnzOPArgs (void);
void makecmplt (void);
void SetExpArg (void);
void StoreResTyp (void);
void setexpfnc (void);
void setbinop (void);
void setopallowed (void);
void setassop (void);
void setscondop (void);
void setcmpop (void);
void defopcpy (void);
void defopcpx (void);
void defopcstr (void);
void defopcfloat (void);
void defopcint (void);

void startprototype (void);
void startfdef (void);
void endfdef (void);
void startparams (void);
void startparfree (void);
void endparfree (void); 
void startparcnt (void);
void defparcnt (void);
void endparcnt (void);  
void startparopt (void);
void endparopt (void);  
void checkparfix (void);
void checkparfixfree (void);
void setdescitemname (void);
void setdescitemstring (void);
void enddescitem (void);
void setdescas (void);
void setparflags (void);
void setpardescname (void);
void setpardescstring (void);
void endpardesc (void);
void pushprototypepar (void);
void setresultdescstring (void);

// Parameter in Funktionsprototypen
// = int | dec | string | strvar | intvar | decvar | pointvar | contvar | strarr | flag
syntax_node pdf_voidvar  = { NULL , NULL           , TRUE , INITERM (KEYWORD , KWVOID)         , pushprototypepar } ;
syntax_node pdf_dtvar    = { NULL , &pdf_voidvar   , TRUE , INITERM (KEYWORD , PARDATETIMEVAR) , pushprototypepar } ;
syntax_node pdf_objvar   = { NULL , &pdf_dtvar     , TRUE , INITERM (KEYWORD , PAROBJVAR)      , pushprototypepar } ;
syntax_node pdf_blobvar  = { NULL , &pdf_objvar    , TRUE , INITERM (KEYWORD , PARBLOBVAR)     , pushprototypepar } ;
syntax_node pdf_qwordvar = { NULL , &pdf_blobvar   , TRUE , INITERM (KEYWORD , QLONGVAR)       , pushprototypepar } ;
syntax_node pdf_dwordvar = { NULL , &pdf_qwordvar  , TRUE , INITERM (KEYWORD , PARDWORDVAR)    , pushprototypepar } ;
syntax_node pdf_imagevar = { NULL , &pdf_dwordvar  , TRUE , INITERM (KEYWORD , PARIMAGE)       , pushprototypepar } ;
syntax_node pdf_procvar  = { NULL , &pdf_imagevar  , TRUE , INITERM (KEYWORD , PARPROCVAR)     , pushprototypepar } ;
syntax_node pdf_timevar  = { NULL , &pdf_procvar   , TRUE , INITERM (KEYWORD , PARTIMEVAR)     , pushprototypepar } ;
syntax_node pdf_datevar  = { NULL , &pdf_timevar   , TRUE , INITERM (KEYWORD , PARDATEVAR)     , pushprototypepar } ;
syntax_node pdf_bitvar   = { NULL , &pdf_datevar   , TRUE , INITERM (KEYWORD , PARPICTVAR)     , pushprototypepar } ;
syntax_node pdf_pictvar  = { NULL , &pdf_bitvar    , TRUE , INITERM (KEYWORD , PARBITMAPVAR)   , pushprototypepar } ;
syntax_node pdf_scalevar = { NULL , &pdf_pictvar   , TRUE , INITERM (KEYWORD , PARSCALEVAR)    , pushprototypepar } ;
syntax_node pdf_flagvar  = { NULL , &pdf_scalevar  , TRUE , INITERM (KEYWORD , PARFLAGVAR)     , pushprototypepar } ;
syntax_node pdf_strarrvar= { NULL , &pdf_flagvar   , TRUE , INITERM (KEYWORD , PARSTRARR)      , pushprototypepar } ;
syntax_node pdf_contvar  = { NULL , &pdf_strarrvar , TRUE , INITERM (KEYWORD , PARCONTVAR)     , pushprototypepar } ;
syntax_node pdf_pointvar = { NULL , &pdf_contvar   , TRUE , INITERM (KEYWORD , PARPOINTVAR)    , pushprototypepar } ;
syntax_node pdf_decvar   = { NULL , &pdf_pointvar  , TRUE , INITERM (KEYWORD , PARDECVAR)      , pushprototypepar } ;
syntax_node pdf_intvar   = { NULL , &pdf_decvar    , TRUE , INITERM (KEYWORD , PARINTVAR)      , pushprototypepar } ;
syntax_node pdf_strvar   = { NULL , &pdf_intvar    , TRUE , INITERM (KEYWORD , PARSTRVAR)      , pushprototypepar } ;
syntax_node pdf_string   = { NULL , &pdf_strvar    , TRUE , INITERM (KEYWORD , PARSTRING)      , pushprototypepar } ;
syntax_node pdf_dec      = { NULL , &pdf_string    , TRUE , INITERM (KEYWORD , PARDEC)         , pushprototypepar } ;
syntax_node pdf          = { NULL , &pdf_dec       , TRUE , INITERM (KEYWORD , PARINT)         , pushprototypepar } ;

/*
// ALT++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 1. Funktionsprototypen
// fdef name ( { par1 , } ) : nummer ;
syntax_node fdef_end  = { NULL , NULL , TRUE , INITERM (KEYWORD, SEMICOLON) , NULL } ;
syntax_node fdef_extra= { &fdef_end , NULL , TRUE , INITERM (T_INTEGER , 0) , setfunchash } ;
syntax_node fdef_q    = { &fdef_extra , NULL , TRUE , INITERM (KEYWORD , FSLASH) , NULL } ;
syntax_node fdef_nmb  = { &fdef_q , NULL , TRUE , INITERM (T_INTEGER , 0) , storefncnumber } ;
syntax_node fdef_dp   = { &fdef_nmb , NULL , TRUE , INITERM (KEYWORD , DOUBLEPOINT) , NULL } ;
syntax_node fdef_bc   = { &fdef_dp , NULL , TRUE , INITERM (KEYWORD , BRACECLOSE) , NULL } ;
syntax_node fdef_fp   = { &fdef_bc , NULL , TRUE , INITERM (KEYWORD , FREEPAR) , pushpartype } ;
extern syntax_node fdef_par;
syntax_node fdef_c    = { &fdef_par , &fdef_bc , TRUE , INITERM (KEYWORD , COLON) , NULL } ;
syntax_node fdef_par  = { &fdef_c , &fdef_fp , FALSE , &pdf , NULL } ;
syntax_node fdef_bo   = { &fdef_par , &fdef_fp , TRUE , INITERM (KEYWORD , BRACEOPEN) , NULL } ;
syntax_node fdef_name = { &fdef_bo , NULL , TRUE , INITERM (UNKNOWNIDENT , 0) , setfuncname } ;
syntax_node fdef      = { &fdef_name, NULL , TRUE , INITERM (KEYWORD , FDEF) , inclevel } ;
// ALT------------------------------------------------------------------------------------------
*/

// 1. Funktionsprototypen
// Types of fdef-Lines
syntax_node f_deftype_o = { NULL, NULL,         TRUE, INITERM (KEYWORD , ODEF), NULL } ;
syntax_node f_deftype_m = { NULL, &f_deftype_o, TRUE, INITERM (KEYWORD , MDEF), NULL } ;
syntax_node f_deftype   = { NULL, &f_deftype_m, TRUE, INITERM (KEYWORD , FDEF), NULL } ;

// Parameter of fdef-Line
syntax_node f_free_old = { NULL,        NULL,        TRUE,  INITERM (KEYWORD, FREEPAR),        pushprototypepar } ;

syntax_node f_par_end  = { NULL,        NULL,        TRUE , INITERM (FREECHAR, 0),             endpardesc } ;
syntax_node f_par_desc = { &f_par_end,  &f_par_end,  TRUE , INITERM (STRING, 0),               setpardescstring } ;
syntax_node f_par_name = { &f_par_desc, &f_par_desc, TRUE , INITERM (UNKNOWNIDENT, 0),         setpardescname } ;

syntax_node f_par_fix1 = { &f_par_name, &f_par_end,  TRUE,  INITERM (UNKNOWNIDENT, 0),         setparflags } ;
syntax_node f_par_fix  = { &f_par_fix1, NULL,        FALSE, &pdf ,                             checkparfix } ;

syntax_node f_free_bc  = { NULL,        NULL,        TRUE,  INITERM (KEYWORD, CBRACECLOSE),  endparfree } ;
extern syntax_node f_free_par;
syntax_node f_free_nxt = { &f_free_par, &f_free_bc,  TRUE,  INITERM (KEYWORD, COLON),          NULL } ;
syntax_node f_free_par = { &f_free_nxt, &f_free_bc,  FALSE, &f_par_fix,                        NULL } ;
syntax_node f_par_free = { &f_free_par, NULL,        TRUE,  INITERM (KEYWORD, CBRACEOPEN),   startparfree } ;

extern syntax_node f_par_free, f_par_opt;
syntax_node f_par_cnt4 = { NULL,        NULL,        FALSE, &f_par_free,                       endparcnt } ;
syntax_node f_par_cnt3 = { NULL,        &f_par_cnt4, FALSE, &f_par_opt,                        endparcnt } ;
syntax_node f_par_cnt2 = { &f_par_cnt3, NULL,        TRUE,  INITERM(BINOP, 0),                 defparcnt } ;
syntax_node f_par_cnt1 = { &f_par_cnt2, NULL,        FALSE, &f_par_name,                       setopallowed } ;
syntax_node f_par_cnt  = { &f_par_cnt1, NULL,        TRUE,  INITERM (KEYWORD, COUNTVAR),       startparcnt } ;

syntax_node f_par_opte = { NULL,        NULL,        TRUE,  INITERM (KEYWORD, ARRBRACECLOSE),  endparopt } ;
syntax_node f_par_opt3 = { &f_par_opte, NULL,        FALSE, &f_par_free,                       NULL } ;
syntax_node f_par_opt2 = { &f_par_opte, &f_par_opt3, FALSE, &f_par_cnt,                        NULL } ;
syntax_node f_par_opt1 = { &f_par_opte, &f_par_opt2, FALSE, &f_par_fix,                        NULL } ;
syntax_node f_par_opt  = { &f_par_opt1, NULL,        TRUE,  INITERM (KEYWORD, ARRBRACEOPEN),   startparopt } ;

syntax_node f_param4   = { NULL,        NULL,        FALSE, &f_free_old,                       NULL } ;
syntax_node f_param3   = { NULL,        &f_param4,   FALSE, &f_par_free,                       NULL } ;
syntax_node f_param2   = { NULL,        &f_param3,   FALSE, &f_par_opt,                        NULL } ;
syntax_node f_param1   = { NULL,        &f_param2,   FALSE, &f_par_cnt,                        NULL } ;
syntax_node f_param    = { NULL,        &f_param1,   FALSE, &f_par_fix,                        NULL } ;

syntax_node f_paramsbc = { NULL,        NULL,        TRUE,  INITERM (KEYWORD, BRACECLOSE),     NULL } ;
extern syntax_node f_params0;
syntax_node f_params1  = { &f_params0,  &f_paramsbc, TRUE,  INITERM (KEYWORD, COLON),          NULL } ;
syntax_node f_params0  = { &f_params1,  &f_paramsbc, FALSE, &f_param,                          NULL } ;
syntax_node f_paramlst = { &f_params0,  NULL,        TRUE,  INITERM (KEYWORD, BRACEOPEN),      startparams } ;

// function description
// ["{" {<<item-name>>: <<item-description-string>>]}... "}" | DESCRIBED_AS identifier];
syntax_node f_descnone = { NULL,        NULL,        TRUE,  INITERM (FREECHAR, 0),             NULL } ;
syntax_node f_desc_as1 = { NULL,        NULL,        TRUE,  INITERM (UNKNOWNIDENT, 0),         setdescas } ;
syntax_node f_desc_as  = { &f_desc_as1, &f_descnone, TRUE,  INITERM (KEYWORD, DESCRIBED_AS),   NULL } ;
syntax_node f_descend  = { NULL,        NULL,        TRUE,  INITERM (KEYWORD, CBRACECLOSE),    enddescitem } ;
extern syntax_node f_descitem;
syntax_node f_descstr  = { &f_descitem, NULL,        TRUE,  INITERM (STRING, 0),               setdescitemstring } ;
syntax_node f_desc_dp  = { &f_descstr,  NULL,        TRUE,  INITERM (KEYWORD, DOUBLEPOINT),    NULL } ;
syntax_node f_descitem = { &f_desc_dp,  &f_descend,  TRUE,  INITERM (UNKNOWNIDENT, 0),         setdescitemname } ;
syntax_node f_desc     = { &f_descitem, &f_descnone, TRUE,  INITERM (KEYWORD, CBRACEOPEN),     NULL } ;

// fdef-Line
// {f|o|m}def <<name>> ([<f_param>[,<f_param>]...]) : <<number>> private <<size>> <f_desc>;
syntax_node fdef_end   = { NULL,        NULL,        TRUE,  INITERM (KEYWORD, SEMICOLON),      endfdef } ;
syntax_node fdef_desc  = { &fdef_end,   NULL,        FALSE, &f_desc,                           NULL } ;
syntax_node fdef_size  = { &fdef_desc,  NULL,        TRUE,  INITERM (T_INTEGER, 0),            setfunchash } ;
syntax_node fdef_priv  = { &fdef_size,  NULL,        TRUE,  INITERM (KEYWORD, FSLASH),         NULL } ;
syntax_node fdef_nmb   = { &fdef_priv,  NULL,        TRUE,  INITERM (T_INTEGER, 0),            storefncnumber } ;
syntax_node fdef_dp    = { &fdef_nmb,   NULL,        TRUE,  INITERM (KEYWORD, DOUBLEPOINT),    NULL } ;
syntax_node fdef_pars  = { &fdef_dp,    NULL,        FALSE, &f_paramlst,                       NULL } ;
syntax_node fdef_name  = { &fdef_pars,  NULL,        TRUE,  INITERM (UNKNOWNIDENT, 0),         setfuncname } ;
syntax_node fdef       = { &fdef_name,  NULL,        FALSE, &f_deftype,                        startfdef } ;

// Operatoren
////////////////
// Definition der Operatoren - Mappings
///////////////////////////////////////////
// Resultat, Parameterdef.
syntax_node resvtyp15 = { NULL , NULL       , TRUE , INITERM (KEYWORD,PARDATETIMEVAR) , NULL } ;
syntax_node resvtyp14 = { NULL , &resvtyp15 , TRUE , INITERM (KEYWORD,PARBLOBVAR) , NULL } ;
syntax_node resvtyp13 = { NULL , &resvtyp14 , TRUE , INITERM (KEYWORD,PARBITMAPVAR) , NULL } ;
syntax_node resvtyp12 = { NULL , &resvtyp13 , TRUE , INITERM (KEYWORD,PARPICTVAR) , NULL } ;
syntax_node resvtyp11 = { NULL , &resvtyp12 , TRUE , INITERM (KEYWORD,PARSCALEVAR) , NULL } ;
syntax_node resvtyp10 = { NULL , &resvtyp11 , TRUE , INITERM (KEYWORD,PARTIMEVAR) , NULL } ;
syntax_node resvtyp9a = { NULL , &resvtyp10 , TRUE , INITERM (KEYWORD,QLONGVAR) , NULL } ;
syntax_node resvtyp9  = { NULL , &resvtyp9a , TRUE , INITERM (KEYWORD,PARDWORDVAR) , NULL } ;
syntax_node resvtyp8  = { NULL , &resvtyp9  , TRUE , INITERM (KEYWORD,PARFLAGVAR) , NULL } ;
syntax_node resvtyp7  = { NULL , &resvtyp8  , TRUE , INITERM (KEYWORD,PARDATEVAR) , NULL } ;
syntax_node resvtyp6  = { NULL , &resvtyp7  , TRUE , INITERM (KEYWORD,PARCONTVAR) , NULL } ;
syntax_node resvtyp5  = { NULL , &resvtyp6  , TRUE , INITERM (KEYWORD,PARSTRARR) , NULL } ;
syntax_node resvtyp4  = { NULL , &resvtyp5  , TRUE , INITERM (KEYWORD,PAROBJVAR) , NULL } ;
syntax_node resvtyp3  = { NULL , &resvtyp4  , TRUE , INITERM (KEYWORD,PARPOINTVAR) , NULL } ;
syntax_node resvtyp2  = { NULL , &resvtyp3  , TRUE , INITERM (KEYWORD,PARSTRVAR) , NULL } ;
syntax_node resvtyp1  = { NULL , &resvtyp2  , TRUE , INITERM (KEYWORD,PARINTVAR) , NULL } ;
syntax_node resvtyp   = { NULL , &resvtyp1  , TRUE , INITERM (KEYWORD,PARDECVAR) , NULL } ;
                                           
syntax_node fdc7      = { NULL  , NULL  , TRUE , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
syntax_node fdc6      = { &fdc7 , NULL  , TRUE , INITERM(DECIMAL,0) , defopcpy } ;
syntax_node fdc5      = { &fdc6 , NULL  , TRUE , INITERM(KEYWORD,COLON) , NULL } ;
syntax_node fdc4      = { &fdc5 , NULL  , TRUE , INITERM(DECIMAL,0) , defopcpx } ;
syntax_node fdc3      = { &fdc4 , NULL  , TRUE , INITERM(KEYWORD,BRACEOPEN) , NULL } ;
syntax_node fdc2      = { NULL  , &fdc3 , TRUE , INITERM(STRING,0) , defopcstr } ;
syntax_node fdc1      = { NULL  , &fdc2 , TRUE , INITERM(DECIMAL,0) , defopcfloat } ;
syntax_node fdefconst = { NULL  , &fdc1 , TRUE , INITERM(T_INTEGER,0) , defopcint } ;

// Map - Variablendefinition
syntax_node mppd4  = { NULL   , NULL , TRUE , INITERM(KEYWORD,ARRBRACECLOSE) , NULL } ;
syntax_node mppd3  = { &mppd4 , NULL , FALSE , &fdefconst , NULL } ;
syntax_node mppd2  = { &mppd3 , NULL , TRUE , INITERM(KEYWORD,ARRBRACEOPEN) , NULL } ;
syntax_node mppd1  = { NULL   , &mppd2 , TRUE , INITERM(T_INTEGER,0) , defoparg } ;
syntax_node mppdef = { NULL   , &mppd1 , TRUE , INITERM(KEYWORD,MPRES) , defopres } ;

// 1. Funktionsprototypen
// Types of mappings
syntax_node maptype_o = { NULL, NULL,       TRUE, INITERM (KEYWORD , KWOMAP), NULL } ;
syntax_node maptype   = { NULL, &maptype_o, TRUE, INITERM (KEYWORD , KWMAP), NULL } ;

// Map - Definition
extern syntax_node map3;
syntax_node map5  = { NULL , NULL ,   TRUE ,  INITERM(KEYWORD,BRACECLOSE) , CheckAnzOPArgs } ;
syntax_node map4  = { &map3 , &map5 , TRUE ,  INITERM(KEYWORD,COLON) ,      NULL } ;
syntax_node map3  = { &map4 , NULL ,  FALSE , &mppdef ,                     NULL } ;
syntax_node map2  = { &map3 , NULL ,  TRUE ,  INITERM(KEYWORD,BRACEOPEN) ,  NULL } ;
syntax_node map1  = { &map2 , NULL ,  TRUE ,  INITERM(FUNCTIONID, 0) ,      makecmplt } ;
syntax_node map   = { &map1 , NULL ,  FALSE , &maptype ,                    NULL } ;

//extern syntax_node dop3;
extern syntax_node dofn;
syntax_node dop8  = { NULL  , NULL , TRUE ,  INITERM(KEYWORD,SEMICOLON) , NULL } ;
syntax_node dop7  = { &dop8 , NULL,  FALSE,  &f_desc,                     NULL } ;
syntax_node dop6  = { &dop7 , NULL , FALSE , &map ,                       NULL } ;
//syntax_node dop5  = { &dop6 , NULL , TRUE , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
//syntax_node dop4  = { &dop3 , &dop5 , TRUE , INITERM(KEYWORD,COLON) ,     NULL } ;
//syntax_node dop3  = { &dop4 , NULL , FALSE , &resvtyp , SetExpArg } ;
//syntax_node dop2a = { &dop6 , &dop3 , TRUE , INITERM(KEYWORD,BRACECLOSE) , NULL } ;
//syntax_node dop2  = { &dop2a, NULL , TRUE , INITERM(KEYWORD,BRACEOPEN) ,  NULL } ;
syntax_node dop2  = { &dop6,  NULL , FALSE , &f_paramlst ,                 NULL } ;
syntax_node dop1  = { &dop2 , NULL , FALSE , &dofn ,                      startprototype } ;
syntax_node defop = { &dop1 , NULL , FALSE , &resvtyp ,                   StoreResTyp } ;

// Funktionsname, Operator
syntax_node fnn1   = { NULL , NULL , TRUE , INITERM(FNCEXP,0) , setexpfnc } ;
syntax_node ffname = { NULL , &fnn1 , TRUE , INITERM (UNKNOWNIDENT,0) , setexpfnc } ;

syntax_node opn1   = { NULL , NULL , TRUE , INITERM(BINOP,0) , setbinop } ;
syntax_node opname = { NULL , &opn1 , TRUE , INITERM(UNKNOWNIDENT,0) , setbinop } ;

syntax_node dofn5  = { NULL,    NULL,    TRUE ,  INITERM (FREECHAR, 0),        NULL } ;
syntax_node dofn4  = { NULL ,   &dofn5 , TRUE ,  INITERM (STRING, 0),          setresultdescstring } ;
syntax_node dofn3  = { &dofn4 , NULL ,   FALSE , &ffname ,                     NULL } ;
syntax_node dofn2  = { NULL ,   &dofn3 , TRUE ,  INITERM(KEYWORD,ASSIGNMENT) , setassop } ;
syntax_node dofn1  = { NULL ,   NULL ,   FALSE , &opname ,                     NULL } ;
syntax_node dofn   = { &dofn1 , &dofn2 , TRUE ,  INITERM(KEYWORD, OPERATOR) ,  setopallowed } ;

syntax_node cmph3     = { NULL , NULL , TRUE , INITERM(CMPOP,0) , setcmpop } ;
syntax_node cmph2     = { NULL , &cmph3 , TRUE , INITERM(UNKNOWNIDENT,0) , setcmpop } ;
syntax_node cmpophead = { &cmph2 , NULL , TRUE , INITERM(KEYWORD,CMPOPERATOR) , setopallowed } ;
syntax_node defcmpop  = { &dop2 , NULL , FALSE , &cmpophead , startprototype } ;

syntax_node defscond = { &dop2 , NULL , TRUE , INITERM(KEYWORD,SCOND) , setscondop } ;

extern syntax_node fprot;
syntax_node end    = { NULL , &fprot  , TRUE  , INITERM(KEYWORD,PRGEND) , NULL } ;
syntax_node fprot3 = { &end , NULL    , FALSE , &defcmpop , NULL } ;
syntax_node fprot2 = { &end , &fprot3 , FALSE , &defscond , NULL } ;
syntax_node fprot1 = { &end , &fprot2 , FALSE , &defop    , NULL } ;
syntax_node fprot  = { &end , &fprot1 , FALSE , &fdef     , NULL } ;

