/*************************************************************************
 *
 * DDS.H    Headerdatei fuer die Dentale Diagnostik - Software
 *
 * $Header:   P:/marille/clinicum/include/rev/dds.h_v   1.1   02 Feb 1996 11:02:30   GERHOLD  $
 * $Log:   P:/marille/clinicum/include/rev/dds.h_v  $
 * 
 *    Rev 1.1   02 Feb 1996 11:02:30   GERHOLD
 * 1.Umstellung auf 32 Bit
 * 
 *    Rev 1.0   24 Jun 1994 17:00:58   HANNES
 * Neuuebernahme clinicum
 * 
 *    Rev 1.12   24 May 1993 14:19:42   HANNES
 * Umstellung der Reihenfolge
 * 
 *    Rev 1.11   02 Apr 1993 18:07:34   HANNES
 * Login vom Menue aus
 * 
 *    Rev 1.10   11 Mar 1993 11:42:26   HANNES
 * IDC_FR_PREVSIDE,IDC_FR_NEXTSIDE
 * 
 *    Rev 1.9   27 Feb 1993 17:09:36   MARTIN
 * neuer Knopf fuer VTO: Weichteileditiermodus einschalten
 * 
 *    Rev 1.8   26 Feb 1993 13:48:18   HANNES
 * Neue Ident's, Notizblock
 * 
 *    Rev 1.7   22 Feb 1993 17:21:48   HANNES
 * Verschiedene neue Idents
 * 
 *    Rev 1.6   01 Feb 1993 12:10:38   HANNES
 * Korrektur der VTO - Idents
 * 
 *    Rev 1.5   29 Jan 1993 20:19:50   HANNES
 * Idents fuer die VTO
 * 
 *    Rev 1.4   14 Dec 1992 18:24:32   HANNES
 * Neues Knopfchen im Image (IDC_IM_SHOWNAM)
 * 
 *    Rev 1.3   12 Dec 1992 13:48:34   HANNES
 * Elemination der Schiebebalken in den Imagefenstern und der Overlap - Buttons
 * 
 *    Rev 1.2   11 Dec 1992 16:23:58   HANNES
 * Neuen Ident fuer Image, MI_WINDOW korrigiert
 * 
 *    Rev 1.1   04 Dec 1992 19:32:04   HANNES
 * Korrektur des Idents fuer Die Call back Liste
 * 
 *    Rev 1.0   02 Dec 1992 16:00:26   HANNES
 * Initial revision.
 *
 *************************************************************************/

//-----------------------------------------------------------------------
//      Menue - Items
//-----------------------------------------------------------------------

// Daten
#define MI_Patient                     200
#define MI_ExistingData                201
#define MI_EnterDoc                    202
#define MI_Documents                   216
#define MI_QUIT                        217
#define MI_PrintJob                    218
#define MI_patList                     219

// Bearbeitem
#define MI_Insert                      220
#define MI_Copy                        221
#define MI_Cut                         222
// Konfiguration
#define MI_Digitizer                   230
#define MI_Scanner                     231
#define MI_Config                      232
#define MI_Formats                     233

#define MI_LOGIN                       240

// Anzeige
#define MI_Anzeige                     250

// Makro
#define MI_M_ausfuehren                270
#define MI_M_Tastatur                  271
#define MI_M_Anweisung                 272

// Optionen
#define MI_DocList		       280
#define MI_SelOption		       281
#define MI_KeyNumber                   282
#define MI_DateOption                  283

// Fenster
#define MI_WINDOW                      2        // Position des Popupmenues Fenster
#define MI_CASCADE                     290
#define MI_TILE                        291
#define MI_ARRANGE                     292

#define MI_USERLIST                    950

// Hilfe
#define MI_H_Help_DDS                  295
#define MI_H_Learn_DDS                 296
#define MI_ABOUT                       297
#define MI_CALLREFLIST                 999
#define MI_SHOWIMGSTAT                 998
#define MI_SHOWSEGS                    997

// Bitmaps
//#define MI_B_DOCUMENT                  298
#define MI_B_LLIST                     298
#define MI_B_GLOBPAT                   299

// Layout - Menue
#define MI_LAYOUT_NEXT                 500
#define MI_LAYOUT_PREV                 501


//-----------------------------------------------------------------------
//      Child - Id's
//-----------------------------------------------------------------------
#define FIRSTCHILD      1000

//-----------------------------------------------------------------------
//      Dialog - Items
//-----------------------------------------------------------------------


#define LS_DataList           10000

//-----------------------------------------------------------------------
//      String - Indizess
//-----------------------------------------------------------------------
#define TESTDATA	2000

#define DOCDATA		2030

#define FRAMENAMEID     3000

#define TESTGR		4000

#define PATIENT		5000

#define TESTTEXT	6000

#define KWNAME          7000

#define OVERLAPSTR      7999
#define ASKTOSTORE      8000
#define OPENERROR       8002
#define READERROR       8004
#define WRITEERROR      8006
#define NONOTEPAD       8008

///////////////////////////////////////////////////////////////////////////
//      Ident's der Controls
///////////////////////////////////////////////////////////////////////////
#define IDC_TR_BASE        4000
#define IDC_TR_SCROLL      4000
#define IDC_TR_PRINT       4001
#define IDC_TR_RULER       4002
#define IDC_TR_RESCALE     4003
#define IDC_TR_HELP        4004
#define IDC_TR_BEM         4005
#define IDC_TR_XFACT       4006
#define IDC_TR_XDATE       4007
#define IDC_TR_FIX         4008
#define IDC_TR_COMMENT     4009
#define IDC_TR_PATIENT     4010
#define IDC_TR_END         4011

#define IDC_VT_BASE        4050
#define IDC_VT_SCROLL      4050
#define IDC_VT_PRINT       4051
#define IDC_VT_RULER       4052
#define IDC_VT_RESCALE     4053
#define IDC_VT_HELP        4054
#define IDC_VT_CUT         4055
#define IDC_VT_SOFTED      4056
#define IDC_VT_LINTRANS    4057
#define IDC_VT_STARTVTO    4058
#define IDC_VT_BEM         4059
#define IDC_VT_XFACT       4060
#define IDC_VT_XDATE       4061
#define IDC_VT_FIX         4062
#define IDC_VT_COMMENT     4063
#define IDC_VT_PATIENT     4064
#define IDC_VT_END         4065

#define IDC_NM_BASE        4100
#define IDC_NM_PRINT       4100
#define IDC_NM_HELP        4101
#define IDC_NM_GAUSS       4102
#define IDC_NM_BSIZE       4103
#define IDC_NM_TXTSC       4104
#define IDC_NM_BEM         4105
#define IDC_NM_XFACT       4106
#define IDC_NM_XDATE       4107
#define IDC_NM_FIX         4108
#define IDC_NM_COMMENT     4109
#define IDC_NM_PATIENT     4110
#define IDC_NM_END         4111

#define IDC_GR_BASE        4150
#define IDC_GR_HELP        4150
#define IDC_GR_BSIZE       4151
#define IDC_GR_TXTSC       4152
#define IDC_GR_BEM         4153
#define IDC_GR_XFACT       4154
#define IDC_GR_XDATE       4155
#define IDC_GR_COMMENT     4156
#define IDC_GR_PATIENT     4157
#define IDC_GR_XEND        4158

#define IDC_TX_BASE        4300
#define IDC_TX_PRINT       4300
#define IDC_TX_CENTER      4301
#define IDC_TX_BLOCK       4302
#define IDC_TX_RIGHT       4303
#define IDC_TX_LEFT        4304
#define IDC_TX_STRIKEOUT   4305
#define IDC_TX_UNDERLINE   4306
#define IDC_TX_ITALIC      4307
#define IDC_TX_BOLD        4308
#define IDC_TX_TXTSC       4309
#define IDC_TX_RESET       4310
#define IDC_TX_FORMAT      4311
#define IDC_TX_BEM         4312
#define IDC_TX_XFACT       4313
#define IDC_TX_XDATE       4314
#define IDC_TX_COMMENT     4315
#define IDC_TX_PATIENT     4316
#define IDC_TX_END         4317

#define IDC_EN_BASE        4400
#define IDC_EN_SCROLL      4400
#define IDC_EN_NEXT        4401
#define IDC_EN_PREV        4402
#define IDC_EN_HELP        4403
#define IDC_EN_STORE       4404
//#define IDC_EN_LIST        4405
#define IDC_EN_PTLIST      4405
#define IDC_EN_BEM         4406
#define IDC_EN_XFACT       4407
#define IDC_EN_XDATE       4408
#define IDC_EN_FIX         4409
#define IDC_EN_COMMENT     4410
#define IDC_EN_PATIENT     4411
#define IDC_EN_END         4412

#define IDC_IM_BASE        4450
#define IDC_IM_NEW         4450
#define IDC_IM_INSERT      4451
#define IDC_IM_NEXT        4452
#define IDC_IM_PREV        4453
#define IDC_IM_HELP        4454
#define IDC_IM_STORE       4455
#define IDC_IM_RESET       4456
#define IDC_IM_HISTO       4457
#define IDC_IM_KONTRAST    4458
#define IDC_IM_CRISP       4459
#define IDC_IM_MEDIAN      4460
#define IDC_IM_SOBEL       4461
#define IDC_IM_ZOOM        4462
#define IDC_IM_SHOWNAM     4463
#define IDC_IM_ENTPT       4464
#define IDC_IM_PTLIST      4465
#define IDC_IM_BEM         4466
#define IDC_IM_XFACT       4467
#define IDC_IM_XDATE       4468 
#define IDC_IM_FIX         4469
#define IDC_IM_COMMENT     4470
#define IDC_IM_PATIENT     4471
#define IDC_IM_END         4472

#define IDC_ZI_BASE        4475
#define IDC_ZI_ABBRUCH     4475
#define IDC_ZI_RESET       4476
#define IDC_ZI_MAL4        4477
#define IDC_ZI_MAL2        4478
#define IDC_ZI_MAL1        4479
#define IDC_ZI_HISTO       4480
#define IDC_ZI_KONTRAST    4481
#define IDC_ZI_CRISP       4482
#define IDC_ZI_MEDIAN      4483
#define IDC_ZI_SOBEL       4484
#define IDC_ZI_END         4485

#define IDC_CT_BASE        4500
#define IDC_CT_CENTER      4500
#define IDC_CT_BLOCK       4501 
#define IDC_CT_RIGHT       4502
#define IDC_CT_LEFT        4503
#define IDC_CT_STRIKEOUT   4504
#define IDC_CT_UNDERLINE   4505
#define IDC_CT_ITALIC      4506
#define IDC_CT_BOLD        4507
#define IDC_CT_TXTSC       4508
#define IDC_CT_OK          4509
#define IDC_CT_ABBRUCH     4510
#define IDC_CT_FORMAT      4511
#define IDC_CT_END         4512

#define IDC_SF_BASE        4550
#define IDC_SF_PREVFIELD   4550
#define IDC_SF_NEXTFIELD   4551
#define IDC_SF_BSIZE       4552
#define IDC_SF_TXTSC       4553
#define IDC_SF_OK          4554
#define IDC_SF_END         4555

#define IDC_FR_BASE        4600
#define IDC_FR_PRINT       4600
#define IDC_FR_PREVFIELD   4601
#define IDC_FR_NEXTFIELD   4602
#define IDC_FR_BSIZE       4603
#define IDC_FR_TXTSC       4604
#define IDC_FR_BEM         4605
#define IDC_FR_STORE       4606
#define IDC_FR_PSIDE       4607
#define IDC_FR_NSIDE       4608
#define IDC_FR_XDATE       4609
#define IDC_FR_ACTDATE     4610
#define IDC_FR_FIX         4611
#define IDC_FR_COMMENT     4612
#define IDC_FR_PATIENT     4613
#define IDC_FR_END         4614

#define IDC_HL_BASE        4700
#define IDC_HL_TXTSC       4700
#define IDC_HL_ABBRUCH     4701
#define IDC_HL_END         4702

#define IDC_ME_BASE        4800
#define IDC_ME_SCROLL      4800
#define IDC_ME_P1          4801
#define IDC_ME_P2          4802
#define IDC_ME_PREV        4803
#define IDC_ME_NEXT        4804
#define IDC_ME_ABBRUCH     4805
#define IDC_ME_OK          4806
#define IDC_ME_END         4807

#define IDC_MP_BASE        4825
#define IDC_MP_SCROLL      4825
#define IDC_MP_PREV        4826
#define IDC_MP_NEXT        4827
#define IDC_MP_ABBRUCH     4828
#define IDC_MP_OK          4829
#define IDC_MP_END         4830

#define IDC_MC_BASE        4850
#define IDC_MC_SCROLL      4850
#define IDC_MC_STATUS      4851
#define IDC_MC_MINUS       4852
#define IDC_MC_PLUS        4853
#define IDC_MC_PREV        4854
#define IDC_MC_NEXT        4855
#define IDC_MC_ABBRUCH     4856
#define IDC_MC_OK          4857
#define IDC_MC_END         4858

#define IDC_DG_BASE        4900
#define IDC_DG_ABBRUCH     4900
#define IDC_DG_END         4901

#define IDC_LW_BASE        4950
#define IDC_LW_ZOOM        4950
#define IDC_LW_PRINT       4951
#define IDC_LW_NEXTPAGE    4952
#define IDC_LW_PREVPAGE    4953
#define IDC_LW_COMMENT     4954
#define IDC_LW_PATIENT     4955
#define IDC_LW_END         4956

#define IDC_FE_BASE        4999

