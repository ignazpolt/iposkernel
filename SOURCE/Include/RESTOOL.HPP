//  Defines und Funktionsprototypen...
//
//  $Header:   P:/marille/clinicum/include/rev/restool.hpv   1.55   07 Jun 2000 11:51:22   Wolfgang  $
//  $Log:   P:/marille/clinicum/include/rev/restool.hpv  $
// 
//    Rev 1.55   07 Jun 2000 11:51:22   Wolfgang
// 1.) GenFncProt gibt BOOL zurueck.
// 
//    Rev 1.54   01 May 2000 13:33:46   Hannes
// Auch 800x600 in den Bitmaps unterstuetzt
// 
//    Rev 1.53   26 Apr 1999 18:09:44   Wolfgang
// 1.) Zusaetzlicher Parameter setCheckOnly bei GenerateFull.
// 
//    Rev 1.52   26 Mar 1999 18:08:12   Wolfgang
// 1.) Konstanten fuer Messages zum Toggeln der Case-Sensitiven- und 
//     Wort-Suche neu.
// 2.) Konstante fuer Message zum Makefile-Generieren neu.
// 
//    Rev 1.51   18 Mar 1999 14:07:08   Wolfgang
// 1.) STATBAR_...-Konstanten fuer Angabe des Feldes bei SB_SETTEXT.
// 
//    Rev 1.50   16 Mar 1999 16:12:16   Wolfgang
// 1.) ShowScript mit Filenamen hat Fensterhandle als Rueckgabewert.
// 
//    Rev 1.49   04 Aug 1998 17:48:36   Hannes
// Timestamp
// 
//    Rev 1.48   22 Apr 1998 09:50:28   Gerhold
// MI_FINDMATCHINGBRACES
// 
//    Rev 1.47   02 Jan 1998 10:13:10   Gerhold
// MI_CALLVISUALC
// 
//    Rev 1.46   19 Nov 1997 18:45:18   Hannes
// Restool 32 Bit umstellung
// 
//    Rev 1.45   11 Jul 1997 11:26:32   Hannes
// 
//    Rev 1.44   13 Mar 1997 19:04:36   Hannes
// Blobs in DDD's,GDD's
// 
//    Rev 1.43   19 Feb 1997 12:37:38   Hannes
// 
//    Rev 1.42   26 Nov 1996 08:11:52   HANNES
// Automatischer Update
// 
//    Rev 1.41   08 Nov 1996 13:31:36   HANNES
// 
//    Rev 1.40   28 Oct 1996 08:46:42   HANNES
// 
//    Rev 1.39   21 Oct 1996 18:55:06   HANNES
// Fehlerkorrektur Editor / Erweiterung Debugger
// 
//    Rev 1.38   08 Sep 1996 14:10:02   HANNES
// 
//    Rev 1.37   16 Jun 1996 19:49:02   GERHOLD
// 
//    Rev 1.36   02 Feb 1996 11:00:12   GERHOLD
// 1.Umstellung auf 32 Bit
// 
//    Rev 1.35   27 Aug 1995 13:00:50   HANNES
// 
//    Rev 1.34   24 Aug 1995 00:18:20   HANNES
// 
//    Rev 1.33   23 Aug 1995 11:04:42   GERHOLD
// 
//    Rev 1.32   10 Jul 1995 19:57:42   GERHOLD
// ColorRect
// 
//    Rev 1.31   09 Jun 1995 00:30:20   HANNES
// KWSTATIC,KWINDEXED
// 
//    Rev 1.30   07 Jun 1995 12:19:18   GERHOLD
// Bookmarks
// 
//    Rev 1.29   23 May 1995 12:04:26   GERHOLD
// WMU_GETACTIVEWORD ... liefert das aktive Wort im Script-Fenster.
// 
//    Rev 1.28   17 May 1995 15:56:14   HANNES
// PT_TEXT
// 
//    Rev 1.27   15 May 1995 08:53:14   GERHOLD
// 
//    Rev 1.26   24 Apr 1995 15:47:16   GERHOLD
// 
//    Rev 1.25   27 Mar 1995 10:41:58   GERHOLD
// 
//    Rev 1.24   20 Mar 1995 08:45:30   HANNES
//  
// 
//    Rev 1.23   16 Feb 1995 12:34:40   HANNES
// Erweiterung um verbesserte DB - Tools
// 
//    Rev 1.22   13 Jan 1995 16:54:58   HANNES
// Variablen-Breakpoints
// 
//    Rev 1.21   09 Jan 1995 12:17:56   HANNES
// Debugger eingebaut
// 
//    Rev 1.20   04 Jan 1995 14:55:42   HANNES
// 
//    Rev 1.19   03 Jan 1995 12:04:16   HANNES
// 
//    Rev 1.18   02 Jan 1995 18:33:28   HANNES
// 
//    Rev 1.17   02 Jan 1995 16:43:18   GERHOLD
// WMU_FONTHASCHANGED
// 
//    Rev 1.16   02 Jan 1995 09:51:44   GERHOLD
// Umstellung auf MDI
// 
//    Rev 1.15   25 Oct 1994 11:53:50   GERHOLD
// 
//    Rev 1.14   19 Oct 1994 22:29:18   hannes
// 
//    Rev 1.13   03 Oct 1994 11:44:44   HANNES
// 
//    Rev 1.12   14 Sep 1994 16:59:18   GERHOLD
// Erweiterungen fuer Statuszeile
// 
//    Rev 1.11   05 Sep 1994 18:55:28   GERHOLD
// die dre neuen Listen werden jetzt angezeigt
// 
//    Rev 1.10   05 Sep 1994 11:41:26   GERHOLD
// UpDown Control
// 
//    Rev 1.9   26 Aug 1994 12:27:54   GERHOLD
// ToolTime, ToolShortInt
// 
//    Rev 1.8   10 Aug 1994 12:09:08   GERHOLD
// Hotkeys in RESTOOL
// 
//    Rev 1.7   09 Aug 1994 10:08:22   HANNES
// Time eingebaut
// 
//    Rev 1.6   05 Aug 1994 20:54:34   HANNES
// FrmTime eingebaut
// 
//    Rev 1.5   05 Aug 1994 11:57:46   GERHOLD
// XYFromRect, BmpTextPushButton
// 
//    Rev 1.4   01 Aug 1994 15:40:24   GERHOLD
// Drag & Drop fuer Farben
// 
//    Rev 1.3   25 Jul 1994 09:47:56   GERHOLD
// Formate & Farben
// 
//    Rev 1.2   20 Jul 1994 17:37:02   GERHOLD
// Erweiterungen fuer FONTCOL.CPP
// 
//    Rev 1.1   12 Jul 1994 14:46:28   HANNES
// Erweiterungen..
// 
//    Rev 1.0   24 Jun 1994 18:47:00   HANNES
// Initial revision.
//

#define WMU_FONTHASCHANGED     (WM_USER + 1)
#define WMU_GETACTIVEWORD      (WM_USER + 2)
#define WMU_GETACTIVEPREFIX    (WM_USER + 0)
// Achtung WM_USER+3 ist schon belegt (compile.hpp)!!!!!!


#define MENU_BASE          15000         // fuer StringTable!!!!

#define NOMENU             0
#define IDM_SYSMENU        1

#define MI_DATEI           170
#define MI_GENDDICT             171
#define MI_GENRES               172
#define MI_DBCONV               173
#define MI_SETFNC               174
#define MI_CONNECTTOSQL         175

#define MI_SCRIPTEDITOR    150
#define MI_OPENFORSCRIPTED      151

#define MI_SCRIPTS         200
#define MI_SCRIPTLIST           201
#define MI_GENERATESCRIPT       202

#define MI_TABELLEN        250
#define MI_TABLELIST            251
#define MI_GENINT               252
#define MI_RIDIAGS              253
#define MI_SHOWGLOB             254


#define MI_SHOWRES         300

#define MI_EINSTELLUNGEN   350
#define MI_SHOWFMT              351
#define MI_SHOWCOLOR            352

#define MI_FENSTER         400
#define MI_OUTPUTOPT            401
#define MI_CLEARSCREEN          402

#define IDM_COPY                103
#define IDM_CUT                 102
#define IDM_PASTE               104
#define IDM_CLEAR               454
#define IDM_DELLINE             460
#define MI_INSERTTEMPLATE       465

#define IDM_HELPONITEM          901


//#define MI_TABLELIST       0
//#define MI_GENDDICT        1
//#define MI_CLEARSCREEN     2
#define MI_LINEDOWN        3
#define MI_LINEUP          4 
#define MI_PAGEDOWN        5
#define MI_PAGEUP          6
#define MI_HOME            7
#define MI_END             8
//#define MI_OUTPUTOPT       9
//#define MI_DBCONV          10
//#define MI_GENRES          11
//#define MI_SHOWRES         12
//#define MI_SETFNC          13
//#define MI_SCRIPTS         14
#define MI_HDFONT          15
#define MI_LIFONT          16
//#define MI_GENINT          17
#define MI_CLOSESC         18
#define MI_MAINFILE        19
#define MI_DIALED          20
#define MI_STOREDIALOG     21
#define MI_DESTROYDIALOG   22
#define MI_WORKONELE       23
#define MI_INSETDLGBSP     24
#define MI_STOREED         25
#define MI_DUPLICATE       26
#define MI_WORKONSCREEN    27
#define MI_GENED           28
#define MI_DELELE          29
#define MI_NEXTBUFFER      30
#define MI_BIGGERSCALE     31
#define MI_SMALLERSCALE    32
#define MI_NEWHLINE        33
#define MI_NEWVLINE        34
#define MI_DELHLINE        35
#define MI_WORKONHLINE     36
#define MI_MULTIHLINE      37
//#define MI_OPENFORSCRIPTED 38
#define MI_SEARCH          39
#define MI_SEARCHMORE      40
#define MI_REPLACE         41
#define MI_REPLACEMORE     42
#define MI_MOVEELEMES      43
#define MI_SHOWSORT        44
#define MI_INDENVORDERGRUND 45
#define MI_INDENHINTERGRUND 46
//#define MI_SHOWFMT          47
//#define MI_SHOWCOLOR        48
#define MI_SETBREAK        49
#define MI_RUN             50
#define MI_WATCHVAR        51
#define MI_STEP            52
#define MI_STEPINTO        53
#define MI_SHOWSTACK       54
#define MI_SHOWUPDATE      55
#define MI_CREATEWATCH     56
#define MI_PREVIEWFORM     57
#define MI_SHOWRASTER      58
#define MI_BREAKLIST       59
#define MI_SEARCHUP        60
#define MI_REPLACEALL      61
#define MI_SEARCHCASE      62
#define MI_SEARCHWORD      63
#define MI_GENMAKEFILE     64

#define MI_TOGGLEBOOKMARK  70
#define MI_NEXTBOOKMARK    71
#define MI_PREVBOOKMARK    72

#define MI_SETRASTER       80

#define MI_EXPANDWATCH     81
#define MI_DELWATCH        82
#define MI_WATCHBREAK      83

#define MI_SHOWWATCHVAR    84

#define ID_CONTEXTCOMBO    85
#define ID_WATCHLIST       86

#define MI_FOCUSTOLIST     87
#define MI_DESTROYDDS      88
#define MI_GENED_DEPEND    89
#define MI_BREAKDDS        90
#define MI_CALLVISUALC     91
#define MI_FINDMATCHINGBRACES  92

#define MI_INCLUDE      1000
#define MI_DLGCOMMAND   2000
#define MI_WFILECOMMAND 3000

#define ID_LIST         101
#define ID_COLUMN       106
#define ID_ACCESS       107
#define ID_DESCHEAD     105
#define ID_DESC         102
#define ID_VIEW         109
#define ID_COMBO        110
#define ID_NEW          112
#define ID_VIEWPARAM    113
#define ID_GENERATE     114
#define ID_PRINTVIEW    115
#define ID_TBLCOUNT     108
#define ID_INC          111
#define ID_DEC          116
#define ID_WRITEINT     118
#define ID_TABLENAME    117
#define ID_VARPREFIX    119
#define ID_WORKON       120
#define ID_INSERTBEFORE 121
#define ID_SELECTALL    122
#define ID_SCREENNAME   103
#define ID_OBJECTNAME   104
#define ID_HLINEPOS     201
#define ID_ANZLINES     202
#define ID_ABSTHLINE    203
#define ID_SLIST        204
#define ID_ELIST        205
#define ID_SSTRING      206
#define ID_ESTRING      207
#define ID_CASESENSITIVE  300
#define ID_DOERSETZEN     301
#define ID_MOVEDX         211
#define ID_MOVEDY         212
#define IDB_EXTRA       250
#define IDB_FONT        251
#define IDLB_FORMAT     252

#define ID_LISTSORTDESC   350
#define ID_LISTSORTFILE   351
#define IDRB_SORTDESC     352
#define IDRB_SORTFILE     353


#define RSKW_BASE               1000
#define KWENDRES                0
#define KWEQUAL                 1
#define KWBRACEOPEN             2
#define KWDOPPELPUNKT           3
#define KWCOLON                 4
#define KWBRACECLOSE            5
#define KWSEMICOLON             6
#define KWTABLE                 7
#define KWIN                    8
#define KWCURBRACEOPEN          9
#define KWCURBRACECLOSE         10
#define KWVARLONG               11 
#define KWVARDEC                12 
#define KWVARSTR                13 
#define KWVARPOINT              14 
#define KWVARCONT               15 
#define KWVARSTRARR             16 
#define KWVARFLAG               17 
#define KWVARSCALE              18 
#define KWVARDATE               19 
#define KWVARDWORD              20 
#define KWVAROBJ                21 
#define KWFROM                  22
#define KWINTERN                23
#define KWPRIMKEY               24
#define KWAS                    25
#define KWGLOBAL                26
#define KWNEXTTABLE             27
#define KWSORT                  28
#define KWVARTIME               29 
#define KWSTATIC                30
#define KWINDEX                 31
#define KWINDEXNAME             32
#define KWVARQLONG              33
#define KWVARBLOB               34
#define KWLINDEX                35
#define KWVARDATETIME           36
#define KWEND                   37

#define RSCMPERROR_BASE         2000
#define RSCMPERROR_GENERROR     2001
#define RSCMPERROR_NOTABLE      2002
#define RSCMPERROR_ORDER        2003
#define RSCMPERROR_NOVARINTABLE 2004
#define RSCMPERROR_INCOMPATIBLE 2005

#define ID_TABLEPATTERN         3000
#define ID_COLUMNPATTERN        3001
#define ID_RSCMPHEADLINE        3002
#define ID_CFULLTABLE           3003
#define ID_INTERNTABLEPATTERN   3004
#define ID_ADDJOINVAR           3005
#define ID_RCCMPHEADLINE        3006
#define ID_RCCMPENDLINE         3007
#define ID_RSBMPPATTERN         3008
#define ID_RSWMFPATTERN         3009
#define ID_FCMPHEADLINE         3010
#define ID_FCMPENDLINE          3011
#define ID_GLOBVAR              3012

#define ID_CVCMPHEADLINE        4000

#define CVKW_BASE               5000
#define IDC_KWEQUAL             0
#define IDC_KWACCESS            1
#define IDC_KWBY                2
#define IDC_KWSEMICOLON         3
#define IDC_KWBRACEOPEN         4
#define IDC_KWBRACECLOSE        5
#define IDC_KWCOLON             6
#define IDC_KWSAMENAME          7
#define IDC_KWXXXX              8
#define IDC_KWEND               9

#define CVCMPERROR_BASE         6000
#define CVCMPERROR_EVENSIZE     6001
#define CVCMPERROR_INVHEXCHAR   6002
#define CVCMPERROR_NOTABLE      6003
#define CVCMPERROR_INSERROR     6004

#define IDHEADLINE_GENRES       7000
#define IDHEADLINE_DBCONV       7001
#define IDTRANSFER              7002
#define ID_CONVDONE             7003
#define IDHEADLINE_GENRC        7004
#define IDHEADLINE_FNCPROT      7005
#define ID_NEWSCRIPT            7006
#define IDHEADLINE_GENINT       7007
#define IDHEADLINE_SHOWSCRIP    7008
#define IDHEADLINE_CONNECTTOSQL 7009
#define IDHEADLINE_CREATERI     7010

#define RCCMPERROR_BASE         8000
#define RCCMPERROR_FNOTFOUND    8001

#define RCKW_BASE               9000
#define RCKW_BITMAP             0
#define RCKW_EQUAL              1
#define RCKW_DIMENSION          2
#define RCKW_COLON              3
#define RCKW_WMF                4
#define RCKW_SEMICOLON          5
#define RCKW_8x6                6
#define RCKW_XXXX               7
#define RCKW_END                8

#define RCFI_BASE               10000

#ifndef RC_INVOKED
BOOL GenResScript (HWND hWnd,LPSTR fname);
void PaintMessages (HDC hDC);
void FreeMsgs ();
void InitializeTables ();
void DestroyTables ();
BOOL WINAPI _export TableDialog (HWND hDlg, UINT msg, WORD wP, LONG lP);
void ToggleOutputState (HMENU hmenu);
void ShowMsg (LPSTR Text,BOOL priority = FALSE);
BOOL DoDBConv (HWND hWnd,LPSTR fname);
BOOL GenRScript (HWND hWnd,LPSTR fname);
void ToHex (LPSTR res,LPSTR data,int size);
void ShowResources (HWND hWnd);
void ShowFormat (HWND hWnd, BOOL EnableDragDrop = FALSE);
COLORREF ShowColor (HWND hWnd, BOOL EnableDragDrop = FALSE);
BOOL GenFncProt (HWND hwnd,LPSTR FName);
void WorkOnScripts (HWND hWnd);
void OpenProjects (HWND hWnd);
BOOL GetCmpName (HWND hWnd,int ResID,LPSTR Name,WORD cbName,BOOL mustExist = TRUE,int type = 0);
void GenIntTables (HWND hWnd,LPSTR fName);
void AnalyseIntTable (HWND hWnd,LPSTR fname);
void AnalyseInternTableName (LPSTR Name);
void AnalyseNextTable ();
void AnalyseInternVarName (LPSTR Name);
void AnalyseExternVarName (LPSTR Name);
void AnalyseAddInternVar (LPSTR Name);
void AnalyseInsertTableBehind (LPSTR Name);
HWND ShowScript (HWND hParent,LPSTR fname,BOOL MainFile = FALSE);
void EcToolExit ();
HWND GetScWnd();
void ShowTableList (HWND hwnd,BOOL forDrop = FALSE);
void AddBitmapTool (LPSTR name,WORD HelpIndex);
BOOL BitmapToolsLoaded ();
void FreeBitmapTools ();
void InsertTool (LPSTR Name,int x,int y);
void CreateToolWnd (HWND hParent);
void DestroyToolWnd ();
BOOL IsScriptOpen();
BOOL GenerateFull (HWND hWnd,LPSTR fname,BOOL setCheckOnly = FALSE);
LPSTR GetStartDirName ();
int MyGetProfInt (LPSTR Section,LPSTR Name,int def);
void MySetProfInt (LPSTR Section,LPSTR Name,int val);
void MyProfFlush ();
void CreateRIView (LPSTR Name);
void ShowDialogWithTemplates (HWND hWnd);

extern void OpenDBList (LPSTR SearchStr);
extern void OpenIntList (LPSTR prefix,LPSTR SearchStr);
extern void OpenGlobList (LPSTR prefix,LPSTR SearchStr);

#endif

#define IDDSC_BASE                    11000
#define IDPAR_BASE                    11500
#define IDPIC_BASE                    12000
#define IDHLP_BASE                    12500

#define dsc_PushButton                0
#define dsc_CheckButton               1
#define dsc_TextPushButton            2
#define dsc_TextCheckButton           3
#define dsc_TextRadioButton           4
#define dsc_ComboButton               5
#define dsc_UpDown                    6
#define dsc_ToolEdit                  7
#define dsc_ToolZoom                  8
#define dsc_ToolPage                  9
#define dsc_ToolDate                  10
#define dsc_ToolFloat                 11
#define dsc_GroupBox                  12
#define dsc_StaticTool                13
#define dsc_lShowList                 14
#define dsc_StaticBitmap              15
#define dsc_Line3D                    16
#define dsc_ColorLine                 17
#define dsc_ColorRect                 18
#define dsc_ActionBox                 19
#define dsc_FlapMap                   20
#define dsc_ToolPwd                   21
#define dsc_PushCheckButton           22
#define dsc_TransparentBitmap         23
#define dsc_AnimationBitmap           24
#define dsc_ToolBEdit                 25
#define dsc_BmpFloat                  26
#define dsc_ShowPermList              27
#define dsc_ShowStringList            28
#define dsc_ShowColumnList            29
#define dsc_ShowObjectList            30
#define dsc_ShowPMObjectList          31
#define dsc_ExternDocument            32
#define dsc_XYFromRect                33
#define dsc_BmpTextPushButton         34
#define dsc_ToolTime                  35
#define dsc_ToolShortInt              36 
#define dsc_CreateScreen              37
#define dsc_StdHeader                 38
#define dsc_FullHeader                39
#define dsc_DBCall_StringList         40
#define dsc_DBCall_ColumnList         41
#define dsc_DBCall_ObjList            42
#define dsc_DBCall_MPObjList          43
#define dsc_ToolLongInt               44
#define dsc_ToolMoney                 45
#define dsc_StdButton                 46
#define dsc_FullButton                47
#define dsc_SetButtons                48
#define dsc_BindInnerListToOutList    49

#define dsc_DefFrmField               100
#define dsc_DefFrmDate                101
#define dsc_DefFrmDec                 102
#define dsc_DefFrmSLDec               103
#define dsc_DefFrmStrList             104
#define dsc_DefFrmLine                106
#define dsc_DefFrmImage               107
#define dsc_Trc_DefCont               108
#define dsc_Trc_DefPattern            109
#define dsc_Trc_DefmPattern           110
#define dsc_Trc_DefLine               111
#define dsc_DefFrmSozNr               112
#define dsc_DefFrmDevDec              113
#define dsc_DefCheckBox               114
#define dsc_DefFrmShortStrList        115
#define dsc_Trc_DefArc                116
#define dsc_DefPattern                118
#define dsc_DefFrmTab                 119
#define dsc_DefFrmTabField            120
#define dsc_DefTabDecField            121
#define dsc_DefFrmTabShortStrList     122
#define dsc_DefTabFlagField           123
#define dsc_DefCheckField             124
#define dsc_DefTabCheckField          125
#define dsc_DefFrmStrDivList          126
#define dsc_DefTabDate                127
#define dsc_DefFrmTabStrList          128
#define dsc_DefTabColDec              129
#define dsc_DefFrmSlantField          133
#define dsc_DefFrmSlantDec            134
#define dsc_DefFrmSlantSLDec          135
#define dsc_DefMovePattern            136
#define dsc_DefFrmDefDec              137
#define dsc_DefFrmMultiField          138
#define dsc_DefTrcImage               139
#define dsc_DefFrmStaticBitmap        143
#define dsc_DefActivationRegion       144
#define dsc_DefFrmBField              145
#define dsc_Trc_DefRectangle          146
#define dsc_DefFrmTime                147
#define dsc_DefFrmShort               148
#define dsc_DefFrmLong                149
#define dsc_DefFrmMoney               150

#define PTNAME_BASE     13000
#define PT_OBJADDRESS   0
#define PT_INT          1
#define PT_STRING       2
#define PT_UNKNOWN      3
#define PT_WIDTH        4
#define PT_HEIGHT       5
#define PT_X            6
#define PT_Y            7
#define PT_BX           8
#define PT_BY           9
#define PT_BITMAP       10
#define PT_DEC          11
#define PT_POINT        12
#define PT_COLORVAR     13
#define PT_P1           14
#define PT_P2           15
#define PT_X1           16
#define PT_Y1           17
#define PT_X2           18
#define PT_Y2           19
#define PT_WMF          20
#define PT_FORMAT       21
#define PT_HOTKEY       22
#define PT_TEXT         23

#define IDDLGBSP_BASE   14000

#define GCKW_BASE       16000
#define GCKW_FPROT      0     // Funktionsprototypen
#define GCKW_RES        1     // Resourcen
#define GCKW_TABLES     2     // Tabellen
#define GCKW_SCRIPTS    3     // Scripts
#define GCKW_DBTABLES   4     // Datenbanktabellen, neue Konvention
#define GCKW_ITABLES    5     // 
#define GCKW_GTABLES    6     // 
#define GCKW_REP        7
#define GCKW_MODULES    8
#define GCKW_END        9

// Defines fuer Fontcol
#define IDS_PREVIEW  253
#define IDB_DELETE   254
#define IDED_FMTINFO 255
#define IDS_DSC      10030
#define IDED_NAME    400
#define IDED_DESCR   401
#define IDED_LEFT    402
#define IDED_RIGHT   403
#define IDED_DIST    404
#define IDRB_LEFT    410
#define IDRB_CENTER  411
#define IDRB_RIGHT   412
#define IDRB_BLOCK   413
#define IDB_NEW      414

// Defines fuer Statusbar
#define STATBAR_COLUMN  0
#define STATBAR_LINE    1
#define STATBAR_TEXT    2

