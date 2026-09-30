//
//      Funktionsprototypen und Array
//      der Funktionen, die vom Interpreter
//      ausgefuehrt werden
//
// $Header:   P:/marille/clinicum/include/rev/fncarr.hpv   1.209   27 Jun 2000 18:37:18   Martin  $
// $Log:   P:/marille/clinicum/include/rev/fncarr.hpv  $
// 
//    Rev 1.209   27 Jun 2000 18:37:18   Martin
// Ltx()
// 
//    Rev 1.208   07 Jun 2000 10:23:02   Wolfgang
// 1.) DBCall_Parse neu.
// 
//    Rev 1.207   02 Jun 2000 14:42:38   Gerhold
// Zufallszahlengenerator
// 
//    Rev 1.206   26 Apr 2000 12:07:14   Martin
// MultiComboReset
// 
//    Rev 1.205   20 Mar 2000 09:51:38   Hannes
// 
//    Rev 1.204   03 Mar 2000 09:00:18   Dietmar
// Deklaration f. lInnerUpdate() eingefuegt (Abgleich f. Hannes)
//
//    Rev 1.202   24 Jan 2000 00:15:04   Hannes
// MoveBlobData
//
//    Rev 1.201   19 Dec 1999 21:26:50   Hannes
// ForcePageBreak
//
//    Rev 1.200   14 Dec 1999 06:11:22   Hannes
// BlockCopy
//
//    Rev 1.199   03 Dec 1999 02:37:46   Hannes
// ErrorText
//
//    Rev 1.198   25 Nov 1999 02:52:22   Hannes
// ObjInfo als String
//
//    Rev 1.197   23 Nov 1999 17:22:40   Hannes
// Div. Erweiterungen
//
//    Rev 1.196   22 Nov 1999 18:02:10   Wolfgang
// 1.) AddBlobToBlob, ExtractDataFromBlob, ExtractBlob und NetSendBlob neu.
//
//    Rev 1.195   22 Nov 1999 09:27:50   Hannes
// OLE - Erweiterungen
//
//    Rev 1.194   12 Oct 1999 12:06:34   Hannes
// Menue in Stationsgraphik
//
//    Rev 1.193   08 Oct 1999 14:21:30   Wolfgang
// 1.) IsInTransaction eingebaut.
//
//    Rev 1.192   10 Sep 1999 17:09:34   Wolfgang
// 1.) SetFeierTag und ClearFeierTage neu.
// 2.) Fehler bei Typen (zwischen GetFormatBaseHeight und RemoveCRLF fehlte
//     seit 1.79 einer) korrigiert.
//
//    Rev 1.191   20 Aug 1999 20:17:22   Martin
// CreateAllTables
//
//    Rev 1.190   26 Jul 1999 22:16:48   Hannes
//
//    Rev 1.189   27 Jun 1999 21:55:22   Hannes
// Hilfsfunktionen fuer Rechtschreibpruefung
//
//    Rev 1.188   14 Jun 1999 20:39:46   Hannes
// RunAutomacro
//
//    Rev 1.187   07 Jun 1999 09:15:48   Hannes
// Tagesauslastung
//
//    Rev 1.186   04 Jun 1999 01:28:58   Hannes
//
//    Rev 1.185   13 May 1999 22:27:44   Hannes
// SetDDSCapture
//
//    Rev 1.184   27 Apr 1999 01:48:38   Hannes
// dosqrt
//
//    Rev 1.183   31 Mar 1999 14:57:32   Gerhold
// htmlhelp
//
//    Rev 1.182   16 Mar 1999 17:08:02   Gerhold
// SpellCheck-Funktionen
//
//    Rev 1.181   05 Mar 1999 10:55:52   Hannes
// Diverse Verbesserunge Combo - Liste
//
//    Rev 1.180   23 Feb 1999 14:54:32   Hannes
// Neue Combo - Funktionen
//
//    Rev 1.179   15 Feb 1999 21:26:24   Martin
// BLOB cache
//
//    Rev 1.178   05 Feb 1999 21:38:02   Martin
// verbessertes Errorhandling
//
//    Rev 1.177   02 Feb 1999 21:29:00   Hannes
// WindowsEvent
//
//    Rev 1.176   19 Jan 1999 19:27:02   Hannes
// SetUserName
//
//    Rev 1.175   21 Dec 1998 20:19:52   Martin
// GetSystemPath
//
//    Rev 1.174   26 Nov 1998 08:22:30   Hannes
// GetDataWithName
//
//    Rev 1.173   10 Nov 1998 12:54:20   Martin
// SetScriptVersion -> GetVersionInfo
//
//    Rev 1.172   12 Oct 1998 09:41:10   Hannes
// Prototypen
//
//    Rev 1.171   09 Oct 1998 18:35:14   Wolfgang
// fncarr._hp
//
//    Rev 1.170   17 Sep 1998 18:52:06   Wolfgang
//
//    Rev 1.169   18 Aug 1998 19:28:04   Martin
// CallDllProcDynamic
//
//    Rev 1.168   13 Aug 1998 09:25:20   Martin
// MemoryMappedFiles,PostMessage,Halt/ResumeQueue
//
//    Rev 1.167   09 Aug 1998 22:39:58   Hannes
// Verbesserungen Kontextmenue
//
//    Rev 1.166   07 Aug 1998 00:02:04   Hannes
// SetPrinterCaption
//
//    Rev 1.165   04 Aug 1998 17:48:22   Hannes
// Timestamp
//
//    Rev 1.163   29 Jul 1998 12:04:30   Gerhold
// OLEGetDocProp, OLERestrictInput, OLEUpdateFields
//
//    Rev 1.162   28 Jul 1998 08:22:58   Gerhold
// SetOleDocVra, GetOLEDocVar, PrintOLE, GetTableId
//
//    Rev 1.161   27 Jul 1998 15:11:26   Hannes
//
//    Rev 1.160   08 Jul 1998 13:53:50   Hannes
//
//    Rev 1.159   08 Jul 1998 11:08:08   Hannes
// DenyNormalCursor
//
//    Rev 1.158   29 Jun 1998 19:49:22   Martin
// CommSignalStatus, CommEscape
//
//    Rev 1.157   29 Jun 1998 18:58:10   Hannes
// GetResolutionFact
//
//    Rev 1.156   25 Jun 1998 16:25:54   Martin
// TestDllProc
//
//    Rev 1.155   09 Jun 1998 19:29:38   Martin
// GetLastCommError
//
//    Rev 1.154   17 May 1998 18:20:04   Hannes
// No Autoscroll
//
//    Rev 1.153   17 May 1998 17:52:26   Hannes
// Statistik - Funktion
//
//    Rev 1.152   28 Apr 1998 11:02:02   Hannes
// ErsteDatenVomBlob, WeitereDatenVomBlob
//
//    Rev 1.151   27 Apr 1998 12:51:14   Hannes
//
//    Rev 1.150   21 Apr 1998 19:31:06   Hannes
//
//    Rev 1.149   30 Mar 1998 20:20:34   Martin
// ProfileOverrideBuffer
//
//    Rev 1.148   13 Mar 1998 18:55:34   Hannes
// Listenklickprozedur
//
//    Rev 1.147   02 Mar 1998 19:13:18   Hannes
// Trc_DefEllipse
//
//    Rev 1.146   23 Feb 1998 20:00:56   Hannes
// PressedChar
//
//    Rev 1.145   10 Feb 1998 18:25:54   Martin
// FrmGetImgRatio
//
//    Rev 1.144   09 Feb 1998 09:59:38   Hannes
// InterpreteDouble
//
//    Rev 1.143   06 Feb 1998 07:59:10   Hannes
// StartParamer
//
//    Rev 1.142   31 Jan 1998 22:23:42   Martin
// DIBFromClipboard, SetWindowPosition, MCICommand
//
//    Rev 1.141   30 Jan 1998 19:45:20   Hannes
// DocumentToPrinterFromBlob
//
//    Rev 1.140   26 Jan 1998 19:58:50   Hannes
// Listenfunktionen
//
//    Rev 1.139   19 Jan 1998 20:16:36   Hannes
//
//    Rev 1.138   19 Jan 1998 20:01:52   Martin
// Funktionen fuer Kommunikation ueber serielle Schnittstelle
//
//    Rev 1.137   05 Jan 1998 07:48:14   Hannes
// Einsparungen im Scriptheader
//
//    Rev 1.136   20 Nov 1997 19:33:56   Martin
// DataFromPointer
//
//    Rev 1.135   19 Nov 1997 18:45:26   Hannes
// Restool 32 Bit umstellung
//
//    Rev 1.134   12 Nov 1997 16:33:12   Martin
// TextFromStrArray,ReallyExtractPath
//
//    Rev 1.133   31 Oct 1997 12:50:02   Hannes
// Timestampfunktion
//
//    Rev 1.132   29 Oct 1997 18:59:36   Hannes
// Textbausteine
//
//    Rev 1.131   27 Oct 1997 19:51:16   Hannes
// Dict - Funktionen
//
//    Rev 1.130   27 Oct 1997 10:23:56   Martin
// FrmFreeDIB
//
//    Rev 1.129   08 Sep 1997 11:06:42   Gerhold
// AppendFrmContextMenu
//
//    Rev 1.128   04 Sep 1997 20:12:38   Hannes
// InnerListObjekte
//
//    Rev 1.127   01 Sep 1997 13:20:30   gerhold
// Bitmanipulationsroutinen (DefineBitArray ... BitNOT)
//
//    Rev 1.126   25 Aug 1997 14:53:48   Martin
// CreateCBDesc
//
//    Rev 1.125   22 Aug 1997 10:57:02   gerhold
// CreateOleObjectFromFile, RunOleObject
//
//    Rev 1.124   07 Aug 1997 11:54:08   Hannes
//
//    Rev 1.123   29 Jul 1997 09:50:56   Martin
// DDE_SetTimeOut
//
//    Rev 1.122   18 Jul 1997 08:07:00   Hannes
//
//    Rev 1.121   16 Jul 1997 11:56:18   Hannes
//
//    Rev 1.120   14 Jul 1997 12:43:50   Martin
// FrmgetImgInfo, FrmLoad/SaveDIB
//
//    Rev 1.119   01 Jul 1997 14:39:20   Hannes
//
//    Rev 1.118   20 Jun 1997 12:37:34   Hannes
//
//    Rev 1.117   27 May 1997 11:26:50   Hannes
//
//    Rev 1.116   12 May 1997 08:48:48   Hannes
// BlobFromFile
//
//    Rev 1.115   05 May 1997 17:24:14   Hannes
//
//    Rev 1.114   21 Apr 1997 20:47:02   Hannes
// TakeModifyFrom
//
//    Rev 1.113   08 Apr 1997 17:49:30   gerhold
// SetMapFont, SetFlapHeight, SetMapOffset
//
//    Rev 1.112   08 Apr 1997 17:46:50   Hannes
// DelActivePen
//
//    Rev 1.111   08 Apr 1997 10:21:26   Hannes
//
//    Rev 1.110   13 Mar 1997 19:00:58   Hannes
//
//    Rev 1.109   28 Feb 1997 15:05:38   Gerhold
// AppendContextMenu
//
//    Rev 1.108   28 Feb 1997 14:41:38   Hannes
//
//    Rev 1.107   19 Feb 1997 12:01:36   Hannes
//
//    Rev 1.105   01 Feb 1997 23:37:40   MARTIN
// AddMessageHook
//
//    Rev 1.104   27 Jan 1997 13:45:00   MARTIN
// ExeIs32Bit
//
//    Rev 1.103   15 Jan 1997 11:51:36   HANNES
// getDBPointer
//
//    Rev 1.102   12 Dec 1996 12:47:22   HANNES
//
//    Rev 1.101   09 Dec 1996 18:23:24   HANNES
//
//    Rev 1.100   03 Dec 1996 16:40:00   HANNES
//
//    Rev 1.99   26 Nov 1996 08:13:16   HANNES
//
//    Rev 1.98   08 Nov 1996 13:35:26   HANNES
// Replikatorfunktionen, QLong Funktionen
//
//    Rev 1.97   30 Oct 1996 08:42:28   HANNES
// Compilererweiterung: break, continue, staticcall
//
//    Rev 1.96   29 Oct 1996 09:02:22   MARTIN
//
//    Rev 1.95   28 Oct 1996 08:39:32   HANNES
// SetArrayData,GetArrayData
//
//    Rev 1.94   23 Oct 1996 19:38:54   HANNES
//
//    Rev 1.93   14 Oct 1996 15:29:08   MARTIN
// Sound: erste funktionierende Version
//
//    Rev 1.92   28 Sep 1996 15:53:08   GERHOLD
// SetCLINICUMEnvironment
//
//    Rev 1.91   18 Sep 1996 20:47:26   HANNES
//
//    Rev 1.90   06 Aug 1996 15:05:48   GERHOLD
// findfirst, findnext, writescriptlog
//
//    Rev 1.89   28 Jun 1996 14:35:00   hannes
// lSetHeaderClkCallBack
//
//    Rev 1.88   04 Jun 1996 13:02:28   GERHOLD
// GetToolCoordinates, SetDialogPos, SplitPath
//
//    Rev 1.87   09 May 1996 19:10:52   HANNES
//
//    Rev 1.86   06 May 1996 17:18:32   HANNES
// Nicht wiederholbare Elemente
//
//    Rev 1.85   06 May 1996 14:45:20   HANNES
// SetLineObjs
//
//    Rev 1.84   29 Apr 1996 08:22:36   MARTIN
// KisError, FileSeek
//
//    Rev 1.83   19 Apr 1996 17:46:02   MARTIN
// DLL-Anbindung
//
//    Rev 1.82   24 Mar 1996 12:33:24   hannes
// Umstellung auf mehrseitige cField
//
//    Rev 1.81   22 Mar 1996 12:20:54   HANNES
// Aenderungen Hannes
//
//    Rev 1.80   18 Mar 1996 16:58:28   GERHOLD
//
//    Rev 1.79   07 Mar 1996 18:44:00   GERHOLD
// RemoveCRLF
//
//    Rev 1.78   05 Mar 1996 10:01:30   MARTIN
// Prototyp von GetDBHandler
//
//    Rev 1.77   04 Mar 1996 17:48:56   GERHOLD
//
//    Rev 1.76   01 Mar 1996 11:49:50   GERHOLD
// IntersectionVektor und bVektorTeilmenge neu.
//
//    Rev 1.75   02 Feb 1996 10:59:20   GERHOLD
// 1.Umstellung auf 32 Bit
//
//    Rev 1.74   19 Jan 1996 20:38:06   MARTIN
// Drucker-Funktionen (Direkt...)
//
//    Rev 1.73   10 Jan 1996 18:21:56   MARTIN
//
//    Rev 1.72   02 Jan 1996 22:21:28   HANNES
//
//    Rev 1.71   05 Dec 1995 14:03:30   GERHOLD
// SetEditMode
//
//    Rev 1.70   23 Nov 1995 17:43:56   GERHOLD
// SetDocumentTitle (Fenstertext eines MDI-Fensters setzen)
//
//    Rev 1.69   16 Nov 1995 22:05:24   HANNES
//
//    Rev 1.68   15 Nov 1995 17:35:52   GERHOLD
// SetMapExtent ... Position und Groesse der Mappe aendern
//
//    Rev 1.67   02 Nov 1995 10:41:42   GERHOLD
// SetScriptVersion, SetFieldMode
//
//    Rev 1.66   31 Oct 1995 07:37:08   GERHOLD
//
//    Rev 1.65   18 Oct 1995 11:11:36   GERHOLD
// UpdateScreenImmediate
//
//    Rev 1.64   12 Oct 1995 11:13:58   MARTIN
// MultiDim
//
//    Rev 1.63   29 Sep 1995 16:55:26   MARTIN
// GetBaseUnit
//
//    Rev 1.62   16 Sep 1995 02:52:32   HANNES
//
//    Rev 1.61   11 Sep 1995 20:24:46   MARTIN
// OnSetFocusProc
//
//    Rev 1.60   07 Sep 1995 09:03:36   HANNES
//
//    Rev 1.59   27 Aug 1995 13:06:04   MARTIN
//
//    Rev 1.58   14 Aug 1995 08:26:22   HANNES
//
//    Rev 1.57   10 Aug 1995 09:28:50   MARTIN
//
//    Rev 1.56   31 Jul 1995 11:52:20   GERHOLD
// Word-Basic-Funktionen
//
//    Rev 1.55   26 Jul 1995 14:14:38   MARTIN
// Kis-Funktionen (Martin)
// ProjectCallBack (Hannes)
//
//    Rev 1.54   24 Jul 1995 16:38:46   GERHOLD
// GetFieldRightUpper
//
//    Rev 1.53   14 Jul 1995 16:54:40   HANNES
// SetNewFileRef
//
//    Rev 1.52   14 Jul 1995 13:31:42   GERHOLD
// DDE-Funktionen
//
//    Rev 1.51   10 Jul 1995 19:58:46   GERHOLD
// ColorRect
//
//    Rev 1.50   07 Jul 1995 17:22:24   GERHOLD
// CreatePostIt
//
//    Rev 1.49   02 Jul 1995 18:29:50   GERHOLD
//
//    Rev 1.48   11 Jun 1995 20:59:22   MARTIN
//
//    Rev 1.47   11 Jun 1995 10:01:34   GERHOLD
//
//    Rev 1.46   09 Jun 1995 09:35:22   MARTIN
//
//    Rev 1.45   23 May 1995 19:03:28   GERHOLD
//
//    Rev 1.44   23 May 1995 15:41:58   HANNES
//
//    Rev 1.43   20 May 1995 16:16:00   HANNES
//
//    Rev 1.42   15 May 1995 08:29:24   HANNES
//
//    Rev 1.41   12 Apr 1995 12:25:48   HANNES
//
//    Rev 1.40   04 Apr 1995 19:33:52   HANNES
//
//    Rev 1.39   02 Apr 1995 14:12:04   HANNES
//
//    Rev 1.38   27 Mar 1995 13:17:24   HANNES
//
//
//    Rev 1.37   22 Mar 1995 15:28:06   GERHOLD
//
//    Rev 1.36   21 Mar 1995 16:21:00   HANNES
//
//    Rev 1.35   20 Mar 1995 12:07:26   HANNES
// Konstantenhanling, RunNmbr
//
//    Rev 1.34   08 Mar 1995 09:14:58   HANNES
// Forschleifen u.a.
//
//    Rev 1.33   24 Feb 1995 11:17:56   HANNES
//
//
//    Rev 1.32   16 Feb 1995 12:52:26   HANNES
//
//    Rev 1.31   06 Feb 1995 16:52:08   HANNES
//
//    Rev 1.30   29 Jan 1995 11:50:44   HANNES
//
//    Rev 1.29   20 Jan 1995 15:34:38   GERHOLD
// RenameFile, WriteToIniFile
//
//    Rev 1.28   11 Dec 1994 14:49:06   HANNES
//
//    Rev 1.27   05 Dec 1994 17:43:10   HANNES
// Endgueltiger Einbau der Expressions
//
//    Rev 1.26   20 Nov 1994 18:30:02   HANNES
//
//    Rev 1.25   18 Nov 1994 19:57:54   GERHOLD
//
//    Rev 1.24   16 Nov 1994 18:39:18   GERHOLD
// GetDocBestWidth
//
//    Rev 1.23   11 Nov 1994 17:30:00   MARTIN
// DefFrmRectImage
//
//    Rev 1.22   11 Nov 1994 16:18:58   HANNES
//
//    Rev 1.21   10 Nov 1994 22:10:14   MARTIN
// uGetDevString
//
//    Rev 1.20   09 Nov 1994 13:18:48   MARTIN
// AvoidUpdates
//
//    Rev 1.19   08 Nov 1994 12:44:36   HANNES
//
//    Rev 1.18   07 Nov 1994 11:26:14   HANNES
//
//    Rev 1.17   05 Nov 1994 20:47:40   MARTIN
// CopyFrom/ToRecord
//
//    Rev 1.16   02 Nov 1994 20:26:30   GERHOLD
// DestroyFile, SetFileProc
//
//    Rev 1.15   31 Oct 1994 10:02:58   hannes
//
//    Rev 1.14   19 Oct 1994 22:36:50   hannes
//
//    Rev 1.13   17 Oct 1994 15:07:08   HANNES
// SetContrast
//
//    Rev 1.12   11 Oct 1994 09:45:00   HANNES
//
//    Rev 1.11   03 Oct 1994 18:02:52   HANNES
//
//    Rev 1.10   20 Sep 1994 11:46:04   HANNES
//
//    Rev 1.9   07 Sep 1994 10:50:24   HANNES
//
//    Rev 1.8   05 Sep 1994 15:37:40   HANNES
//
//    Rev 1.7   05 Sep 1994 11:41:12   GERHOLD
// UpDown-Control
//
//    Rev 1.6   26 Aug 1994 12:27:30   GERHOLD
// ToolTime, ToolShortInt
//
//    Rev 1.5   26 Aug 1994 10:12:12   HANNES
//
//    Rev 1.4   24 Aug 1994 19:43:52   HANNES
// ShowMPObjectList
//
//    Rev 1.3   05 Aug 1994 20:55:46   HANNES
// Zeitfunktionen
//
//    Rev 1.2   05 Aug 1994 17:16:30   HANNES
//
//    Rev 1.1   13 Jul 1994 21:18:54   HANNES
// LoadInternList erweitert->Alte Funktionen raus
//
//    Rev 1.0   24 Jun 1994 17:01:38   HANNES
// Neuuebernahme clinicum
//
//    Rev 1.113   29 Apr 1994 14:43:04   MARTIN
// FrmGetImageFileName
//
//    Rev 1.112   14 Apr 1994 16:59:04   HANNES
// SetEditOverwrite
//
//    Rev 1.111   13 Apr 1994 20:55:38   MARTIN
// viele neue Funktionen
//
//    Rev 1.109   10 Mar 1994 11:26:18   MARTIN
// Weichteil in Bild malen
//
//    Rev 1.108   04 Mar 1994 10:07:38   MARTIN
// OLE, ExtractPath
//
//    Rev 1.107   02 Mar 1994 21:01:02   MARTIN
// FrmSetImage und FrmWriteBMP
//
//    Rev 1.105   09 Feb 1994 15:18:42   HANNES
// GetTwainSources
//
//    Rev 1.104   04 Feb 1994 16:42:52   HANNES
// CallExternProc, WaitForFlag...
//
//    Rev 1.103   26 Jan 1994 20:48:42   HANNES
// IsField() bei CheckBoxen korrigiert
//
//    Rev 1.102   20 Jan 1994 23:56:18   HANNES
// ClearQueue
//
//    Rev 1.101   13 Jan 1994 16:03:32   HANNES
// SetEditCaretToEnd
//
//    Rev 1.100   12 Jan 1994 11:15:38   HANNES
// Alte Funktioen eleminiert
//
//    Rev 1.99   11 Jan 1994 19:07:20   HANNES
// GetDefaultPrinterName, SetCaretToEnd
//
//    Rev 1.98   07 Jan 1994 19:22:04   HANNES
// SetListAbort,ClearListAbort
//
//    Rev 1.97   04 Jan 1994 17:08:02   HANNES
// Neue Funktionen: RecallOp, CreatePrintDocument, GetPrinterType, SetPrinter
//
//    Rev 1.96   09 Dec 1993 15:05:38   HANNES
// Direktes Include der Pascal Files
//
//    Rev 1.95   29 Nov 1993 08:47:06   HANNES
//
//    Rev 1.94   18 Nov 1993 16:32:34   HANNES
// CopyHandle
//
//    Rev 1.93   16 Nov 1993 04:24:48   HANNES
// Verschiedenes
//
//    Rev 1.92   03 Nov 1993 19:22:38   HANNES
// GetDigits
//
//    Rev 1.91   20 Oct 1993 13:44:46   HANNES
//
//    Rev 1.90   18 Oct 1993 19:52:08   HANNES
//
//    Rev 1.89   15 Oct 1993 10:30:10   MARTIN
// Normfunktionen
//
//    Rev 1.88   15 Oct 1993 10:03:56   HANNES
//
//    Rev 1.87   13 Oct 1993 12:20:38   HANNES
//
//    Rev 1.86   11 Oct 1993 12:21:24   HANNES
//
//    Rev 1.85   06 Oct 1993 15:15:26   HANNES
// SetEntryHeight
//
//    Rev 1.84   06 Oct 1993 09:49:44   HANNES
// Verschiedenes
//
//    Rev 1.83   04 Oct 1993 09:45:50   HANNES
// Verschiedenes
//
//    Rev 1.82   27 Sep 1993 18:28:18   HANNES
// Neue Datumsfunktionen
//
//    Rev 1.81   24 Sep 1993 22:47:40   GERHOLD
//
//    Rev 1.80   22 Sep 1993 09:22:12   HANNES
// Version nach St. Poelten
//
//    Rev 1.79   05 Sep 1993 22:21:14   HANNES
// Erweiterungen, Alten scheiss raus
//
//    Rev 1.78   27 Aug 1993 16:47:26   MARTIN
// Vto_SetMode, Vto_Start, Vto_ApplyCut
//
//    Rev 1.77   25 Aug 1993 16:01:04   MARTIN
// Filterfunktionen
//
//    Rev 1.76   24 Aug 1993 10:34:10   HANNES
// uAddDate
//
//    Rev 1.75   23 Aug 1993 18:58:04   MARTIN
// FrmStoreImage
//
//    Rev 1.74   20 Aug 1993 12:12:58   HANNES
// DefEnt* (zunaechst Retired)
//
//    Rev 1.73   18 Aug 1993 10:40:10   HANNES
// ...
//
//    Rev 1.72   05 Aug 1993 13:14:12   HANNES
// Verschiedenes..
//
//    Rev 1.71   22 Jul 1993 20:56:54   HANNES
// Hauptsaechlich Datensatzfunktionen fuer die Liste
//
//    Rev 1.70   20 Jul 1993 12:36:14   HANNES
// Verschiedenes..
//
//    Rev 1.69   15 Jul 1993 16:32:36   GERHOLD
// Linien und ActionBox
//
//    Rev 1.68   14 Jul 1993 13:23:34   GERHOLD
// statisches Bitmap
//
//    Rev 1.67   13 Jul 1993 11:10:54   HANNES
// lPatListLast, lSelect
//
//    Rev 1.66   12 Jul 1993 07:59:02   HANNES
// Listenfunktionen
//
//    Rev 1.65   06 Jul 1993 20:44:52   HANNES
// GetUser, GetActUser
//
//    Rev 1.64   06 Jul 1993 20:06:32   MARTIN
// DefTrcImage
//
//    Rev 1.63   06 Jul 1993 14:00:52   HANNES
// GetProfileString, GetRecallData, ModifyRecall
//
//    Rev 1.62   05 Jul 1993 14:50:02   HANNES
// Einbau der Toolbar
//
//    Rev 1.61   27 Jun 1993 11:51:28   MARTIN
// uCalcSoftVect
//
//    Rev 1.60   17 Jun 1993 09:28:44   HANNES
// Vorlauefige Multiselektionslisten reingebracht
//
//    Rev 1.59   16 Jun 1993 16:56:30   MARTIN
// WriteCubSpl,uSetMulti,uCopyRefs
//
//    Rev 1.58   16 Jun 1993 12:05:16   HANNES
// Multilistenfelder..
//
//    Rev 1.57   15 Jun 1993 23:26:14   MARTIN
// ChangeCubSplPt, Vto_OnMove, Vto_DrawObject
//
//    Rev 1.56   15 Jun 1993 20:18:00   HANNES
// DefFrmMultiField
//
//    Rev 1.55   08 Jun 1993 17:44:16   MARTIN
// DefFrmDefDec
//
//    Rev 1.54   07 Jun 1993 15:11:12   MARTIN
// DefMovePattern
//
//    Rev 1.53   04 Jun 1993 17:24:22   NORBERT
// Neu: "NuMutualExcludeNone" - nichts defaultm„áig gesetzt
//
//    Rev 1.52   02 Jun 1993 22:21:20   MARTIN
// uTurningPoint
//
//    Rev 1.51   02 Jun 1993 19:57:40   HANNES
// ShowCalender..
//
//    Rev 1.50   02 Jun 1993 12:42:18   MARTIN
// uDelData
//
//    Rev 1.49   02 Jun 1993 12:40:26   HANNES
// ShowCalender
//
//    Rev 1.48   29 May 1993 17:00:42   MARTIN
// bIsVTO
//
//    Rev 1.47   24 May 1993 15:23:34   NORBERT
// Train_Network eingefuegt
//
//    Rev 1.46   24 May 1993 14:31:52   MARTIN
// uConnectCont
//
//    Rev 1.45   24 May 1993 14:19:30   HANNES
// Slantfelder
//
//    Rev 1.44   19 May 1993 20:01:26   MARTIN
// uStretchCont
//
//    Rev 1.43   19 May 1993 19:58:46   HANNES
// DefFrmSlantField
//
//    Rev 1.42   19 May 1993 19:02:00   MARTIN
// uCubSpl
//
//    Rev 1.41   18 May 1993 17:40:26   MARTIN
// uExpVal, uPowVal
//
//    Rev 1.40   17 May 1993 16:12:08   NORBERT
// Train_Network - neural network function
//
//    Rev 1.39   15 May 1993 18:19:46   MARTIN
// wenn ich Martin waere, wuesste ich's
//
//    Rev 1.38   10 May 1993 12:50:56   HANNES
// verschiedene neue Funktionen
//
//    Rev 1.37   06 May 1993 22:01:28   ANDI
//
//
//    Rev 1.36   05 May 1993 11:07:34   MARTIN
// uEstimateTang
//
//    Rev 1.35   28 Apr 1993 20:52:28   NORBERT
// Neue Cursor-Bewegung Funktionen: SetDirKey..UpDown & RightLeft
// uGetPrevCase neu
//
//    Rev 1.34   28 Apr 1993 18:52:40   NORBERT
// neue Tabelle-funktionen: DefFrmTabStrList, DefFrmTabDate
//
//    Rev 1.33   22 Apr 1993 21:05:06   MARTIN
// bContExist
// (bisher selbe Funktion wie bPointExist, jetzt
//  aber notwendig fuer geschnittene Konturen)
//
//    Rev 1.32   19 Apr 1993 01:32:18   MARTIN
// neue Funktion uScContPart
//
//    Rev 1.31   18 Apr 1993 22:57:28   MARTIN
// CheckField,
// Funktionen fuer Export
//
//    Rev 1.30   05 Apr 1993 18:55:30   MARTIN
// Funktion DefCutEdit
//
//    Rev 1.29   02 Apr 1993 18:03:00   HANNES
// Erweiterungen...
//
//    Rev 1.28   17 Mar 1993 18:05:12   HANNES
// 32 bit Umstellung, Strukturbereinigungen
//
//    Rev 1.27   10 Mar 1993 21:20:24   MARTIN
// Funktion DefPattern
//
//    Rev 1.26   08 Mar 1993 14:16:52   HANNES
// uSetDataSet
//
//    Rev 1.25   03 Mar 1993 15:42:16   MARTIN
// neue Funktion DefSoftEdit
//
//    Rev 1.24   02 Mar 1993 19:32:00   MARTIN
// neue Funktion Trc_DefArc
//
//    Rev 1.23   01 Mar 1993 12:26:42   MARTIN
// neue Funktion bLongEqual
//
//    Rev 1.22   22 Feb 1993 17:22:40   HANNES
// ...
//
//    Rev 1.21   17 Feb 1993 15:24:32   MARTIN
// Vto_ShowRotCent umbenannt in Vto_DefRotCent
// Trc_ShowObj retired
//
//    Rev 1.20   17 Feb 1993 13:21:10   HANNES
// bDatExist
//
//    Rev 1.19   16 Feb 1993 13:12:10   HANNES
// Erweiterungen der long Arithmetik
//
//    Rev 1.18   14 Feb 1993 16:09:26   HANNES
// Neue Funktion: DefFrmDevDec
//
//    Rev 1.17   12 Feb 1993 19:46:30   MARTIN
// Neue Funktion: uPtExplizit
//
//    Rev 1.16   11 Feb 1993 14:19:38   HANNES
// DefFrmSozNr
//
//    Rev 1.15   05 Feb 1993 19:36:48   MARTIN
// bScaleExist, uSubVect, uScExplicit, uScSkipOffset
//
//    Rev 1.14   02 Feb 1993 19:08:28   MARTIN
// uInvScale
//
//    Rev 1.13   02 Feb 1993 18:45:50   HANNES
// bStringExist..
//
//    Rev 1.12   02 Feb 1993 11:51:54   MARTIN
// Trc_DefLine
//
//    Rev 1.11   01 Feb 1993 12:00:58   MARTIN
// Vto-Funktionen Vto_Init, Vto_ShowRotCent, Vto_DefineGroup
//
//    Rev 1.10   01 Feb 1993 11:21:18   HANNES
// Neue Funktionen bezuelig FrmObjekte
//
//    Rev 1.9   29 Jan 1993 18:37:34   HANNES
// Neue Funktion: Frm_RecInd
//
//    Rev 1.8   21 Jan 1993 22:34:48   MARTIN
// Trc_DefPattern und Trc_DefmPattern
//
//    Rev 1.7   21 Jan 1993 20:25:46   HANNES
// uAddVect,uGenVect neu
//
//    Rev 1.6   21 Jan 1993 16:52:04   MARTIN
// Trc_DefCont
//
//    Rev 1.5   21 Jan 1993 16:45:24   HANNES
// uGetDecomp
//
//    Rev 1.4   20 Jan 1993 15:46:56   MARTIN
// neue Funktionen fuer Tracing-Objekte und fuer Stringmanipulation
//
//    Rev 1.3   18 Dec 1992 12:45:46   HANNES
// Neu Funktion (CopyCont)
//
//    Rev 1.2   06 Dec 1992 17:35:10   HANNES
// Erweiterung um Frm_ShowString und Frm_relShowString
//
//    Rev 1.1   06 Dec 1992 16:11:26   HANNES
// Txt_Date eingefuegt
//
//    Rev 1.0   02 Dec 1992 15:30:00   HANNES
// Initial revision.
//
#define FIRSTFUNCID             32

// Alle Funktionen sind von folgendem Typ
typedef BOOL (* DDSFUNC) (mdiChild *,void FAR *,WORD);

BOOL Retired(mdiChild *,void FAR *,WORD);

// Implementierte Funktionen
BOOL Txt_FixText              (mdiChild *,void FAR *,WORD);
BOOL Frm_String               (mdiChild *,void FAR *,WORD);
BOOL Txt_String               (mdiChild *,void FAR *,WORD);
BOOL uSetPoint                (mdiChild *,void FAR *,WORD);
BOOL Enter_ShowPicture        (mdiChild *,void FAR *,WORD);
BOOL Enter_EnterPoint         (mdiChild *,void FAR *,WORD);
BOOL Enter_EnterCont          (mdiChild *,void FAR *,WORD);
BOOL uSetVal                  (mdiChild *,void FAR *,WORD);
BOOL uPtDist                  (mdiChild *,void FAR *,WORD);
BOOL bButtonPressed           (mdiChild *,void FAR *,WORD);
BOOL uBringToHor              (mdiChild *,void FAR *,WORD);
BOOL uScPt                    (mdiChild *,void FAR *,WORD);
BOOL uScCont                  (mdiChild *,void FAR *,WORD);
BOOL uBringToOverlap          (mdiChild *,void FAR *,WORD);
BOOL uSmoothCont              (mdiChild *,void FAR *,WORD);
BOOL bPointExist              (mdiChild *,void FAR *,WORD);
BOOL uCalcRelPt               (mdiChild *,void FAR *,WORD);
BOOL uLinInt                  (mdiChild *,void FAR *,WORD);
BOOL uCombineCont             (mdiChild *,void FAR *,WORD);
BOOL uPerpPt                  (mdiChild *,void FAR *,WORD);
BOOL uParPt                   (mdiChild *,void FAR *,WORD);
BOOL uCntMax                  (mdiChild *,void FAR *,WORD);
BOOL uCntCro                  (mdiChild *,void FAR *,WORD);
BOOL uCntMaxAng               (mdiChild *,void FAR *,WORD);
BOOL uCntNea                  (mdiChild *,void FAR *,WORD);
BOOL uPtPro                   (mdiChild *,void FAR *,WORD);
BOOL uExtSmoothCont           (mdiChild *,void FAR *,WORD);
BOOL uAddFixVect              (mdiChild *,void FAR *,WORD);
BOOL uMaxPt                   (mdiChild *,void FAR *,WORD);
BOOL uDiffYears               (mdiChild *,void FAR *,WORD);
BOOL uMulVal                  (mdiChild *,void FAR *,WORD);
BOOL uAddVal                  (mdiChild *,void FAR *,WORD);
BOOL uDivVal                  (mdiChild *,void FAR *,WORD);
BOOL uSubVal                  (mdiChild *,void FAR *,WORD);
BOOL uPtNDist                 (mdiChild *,void FAR *,WORD);
BOOL uPtPDist                 (mdiChild *,void FAR *,WORD);
BOOL uDiffAng                 (mdiChild *,void FAR *,WORD);
BOOL uValRange                (mdiChild *,void FAR *,WORD);
BOOL bValGreater              (mdiChild *,void FAR *,WORD);
BOOL uSmoothCycCont           (mdiChild *,void FAR *,WORD);
BOOL lRefreshList             (mdiChild *,void FAR *,WORD);
BOOL uLinTrans                (mdiChild *,void FAR *,WORD);
BOOL uSetFlag                 (mdiChild *,void FAR *,WORD);
BOOL Txt_LoadText             (mdiChild *,void FAR *,WORD);
BOOL Txt_SaveText             (mdiChild *,void FAR *,WORD);
BOOL Txt_Val                  (mdiChild *,void FAR *,WORD);
BOOL Txt_StringInd            (mdiChild *,void FAR *,WORD);
BOOL uDevInd                  (mdiChild *,void FAR *,WORD);
BOOL uTrcDevInd               (mdiChild *,void FAR *,WORD);
BOOL Trc_ShowImage            (mdiChild *,void FAR *,WORD);
BOOL mShowWindow              (mdiChild *,void FAR *,WORD);
BOOL mShowMessage             (mdiChild *,void FAR *,WORD);
BOOL mRemoveWindow            (mdiChild *,void FAR *,WORD);
BOOL mQString                 (mdiChild *,void FAR *,WORD);
BOOL mPressButton             (mdiChild *,void FAR *,WORD);
BOOL uDivideCont              (mdiChild *,void FAR *,WORD);
BOOL uSymmetrieLine           (mdiChild *,void FAR *,WORD);
BOOL uGet33Arr                (mdiChild *,void FAR *,WORD);
BOOL uGenAgeNorm              (mdiChild *,void FAR *,WORD);
BOOL mShowWaitWin             (mdiChild *,void FAR *,WORD);
BOOL mShowProgress            (mdiChild *,void FAR *,WORD);
BOOL mDestroyWaitWin          (mdiChild *,void FAR *,WORD);
BOOL bIsValInNorm             (mdiChild *,void FAR *,WORD);
BOOL bImageExist              (mdiChild *,void FAR *,WORD);
BOOL uGetImgScale             (mdiChild *,void FAR *,WORD);
BOOL uCombineScale            (mdiChild *,void FAR *,WORD);
BOOL uGetNegX                 (mdiChild *,void FAR *,WORD);
BOOL uOverlapPoints           (mdiChild *,void FAR *,WORD);
BOOL uLinInterpol             (mdiChild *,void FAR *,WORD);
BOOL uVarCall                 (mdiChild *,void FAR *,WORD);
BOOL uShowList                (mdiChild *,void FAR *,WORD);
BOOL Trc_BestKontrast         (mdiChild *,void FAR *,WORD);
BOOL uArcInt                  (mdiChild *,void FAR *,WORD);
BOOL uCalcMiddDev             (mdiChild *,void FAR *,WORD);
BOOL uArcSin                  (mdiChild *,void FAR *,WORD);
BOOL Txt_Date                 (mdiChild *,void FAR *,WORD);
BOOL uCopyCont                (mdiChild *,void FAR *,WORD);
BOOL uSetLong                 (mdiChild *,void FAR *,WORD);
BOOL Trc_DefMark              (mdiChild *,void FAR *,WORD);
BOOL Str_Cpy                  (mdiChild *,void FAR *,WORD);
BOOL Str_Cat                  (mdiChild *,void FAR *,WORD);
BOOL Str_Printf               (mdiChild *,void FAR *,WORD);
BOOL uGetDecomp               (mdiChild *,void FAR *,WORD);
BOOL Trc_DefCont              (mdiChild *,void FAR *,WORD);
BOOL uGenVect                 (mdiChild *,void FAR *,WORD);
BOOL uAddVect                 (mdiChild *,void FAR *,WORD);
BOOL Trc_DefPattern           (mdiChild *,void FAR *,WORD);
BOOL Trc_DefmPattern          (mdiChild *,void FAR *,WORD);
BOOL DefFrmField              (mdiChild *,void FAR *,WORD);
BOOL DefFrmDate               (mdiChild *,void FAR *,WORD);
BOOL DefFrmDec                (mdiChild *,void FAR *,WORD);
BOOL DefFrmSLDec              (mdiChild *,void FAR *,WORD);
BOOL DefFrmStrList            (mdiChild *,void FAR *,WORD);
BOOL uFrmShowObject           (mdiChild *,void FAR *,WORD);
BOOL DefFrmRecInd             (mdiChild *,void FAR *,WORD);
BOOL DefFrmLine               (mdiChild *,void FAR *,WORD);
BOOL DefFrmImage              (mdiChild *,void FAR *,WORD);
BOOL FrmScanImage             (mdiChild *,void FAR *,WORD);
BOOL Vto_Init                 (mdiChild *,void FAR *,WORD);
BOOL Vto_DefRotCent           (mdiChild *,void FAR *,WORD);
BOOL Vto_DefineGroup          (mdiChild *,void FAR *,WORD);
BOOL Trc_DefLine              (mdiChild *,void FAR *,WORD);
BOOL uGetOrtsName             (mdiChild *,void FAR *,WORD);
BOOL uGetVorwahl              (mdiChild *,void FAR *,WORD);
BOOL bStrExist                (mdiChild *,void FAR *,WORD);
BOOL uInvScale                (mdiChild *,void FAR *,WORD);
BOOL uScExplicit              (mdiChild *,void FAR *,WORD);
BOOL uSubVect                 (mdiChild *,void FAR *,WORD);
BOOL bScaleExist              (mdiChild *,void FAR *,WORD);
BOOL uScSkipOffset            (mdiChild *,void FAR *,WORD);
BOOL uDateNow                 (mdiChild *,void FAR *,WORD);
BOOL DefFrmSozNr              (mdiChild *,void FAR *,WORD);
BOOL uPtExplicit              (mdiChild *,void FAR *,WORD);
BOOL DefFrmDevDec             (mdiChild *,void FAR *,WORD);
BOOL DefCheckBox              (mdiChild *,void FAR *,WORD);
BOOL uAddLong                 (mdiChild *,void FAR *,WORD);
BOOL uSubLong                 (mdiChild *,void FAR *,WORD);
BOOL uMaskLong                (mdiChild *,void FAR *,WORD);
BOOL uFindLong                (mdiChild *,void FAR *,WORD);
BOOL uGetLong                 (mdiChild *,void FAR *,WORD);
BOOL bDatExist                (mdiChild *,void FAR *,WORD);
BOOL DefFrmStrShortList       (mdiChild *,void FAR *,WORD);
BOOL uMutualExclude           (mdiChild *,void FAR *,WORD);
BOOL uSetDirKey               (mdiChild *,void FAR *,WORD);
BOOL bLongEqual               (mdiChild *,void FAR *,WORD);
BOOL Trc_DefArc               (mdiChild *,void FAR *,WORD);
BOOL DefSoftEdit              (mdiChild *,void FAR *,WORD);
BOOL uSetDataSet              (mdiChild *,void FAR *,WORD);
BOOL DefPattern               (mdiChild *,void FAR *,WORD);
BOOL uGetIndDec               (mdiChild *,void FAR *,WORD);
BOOL VTOSetEmptyCont          (mdiChild *,void FAR *,WORD);
BOOL SetVTORef                (mdiChild *,void FAR *,WORD);
BOOL DefFrmTab                (mdiChild *,void FAR *,WORD);
BOOL DefFrmTabField           (mdiChild *,void FAR *,WORD);
BOOL DefTabDecField           (mdiChild *,void FAR *,WORD);
BOOL DefTabShortStrListField  (mdiChild *,void FAR *,WORD);
BOOL DefTabFlagField          (mdiChild *,void FAR *,WORD);
BOOL CalcTabPos               (mdiChild *,void FAR *,WORD);
BOOL uCntmCro                 (mdiChild *,void FAR *,WORD);
BOOL mShowMessageBox          (mdiChild *,void FAR *,WORD);
BOOL DefCutEdit               (mdiChild *,void FAR *,WORD);
BOOL DefCheckField            (mdiChild *,void FAR *,WORD);
BOOL DefTabCheckField         (mdiChild *,void FAR *,WORD);
BOOL uExportString            (mdiChild *,void FAR *,WORD);
BOOL eFindSubStr              (mdiChild *,void FAR *,WORD);
BOOL eFirst                   (mdiChild *,void FAR *,WORD);
BOOL DefFrmStrDivList         (mdiChild *,void FAR *,WORD);
BOOL eSetRepeat               (mdiChild *,void FAR *,WORD);
BOOL uScContPart              (mdiChild *,void FAR *,WORD);
BOOL bContExist               (mdiChild *,void FAR *,WORD);
BOOL DefFrmTabDate            (mdiChild *,void FAR *,WORD);
BOOL bYearGreater             (mdiChild *,void FAR *,WORD);
BOOL DefTabStrListField       (mdiChild *,void FAR *,WORD);
BOOL uSetDirKeyUpDown         (mdiChild *,void FAR *,WORD);
BOOL uSetDirKeyLeftRight      (mdiChild *,void FAR *,WORD);
BOOL eGetPrevCase             (mdiChild *,void FAR *,WORD);
BOOL uEstimateTang            (mdiChild *,void FAR *,WORD);
BOOL DefTabColDec             (mdiChild *,void FAR *,WORD);
// BOOL DefFrmKuerzelField       (mdiChild *,void FAR *,WORD);
BOOL DefFKurve                (mdiChild *,void FAR *,WORD);
BOOL GetFieldLeftLower        (mdiChild *,void FAR *,WORD);
BOOL DefFrmBenList            (mdiChild *,void FAR *,WORD);
BOOL uOptimize                (mdiChild *,void FAR *,WORD);
BOOL uContDist                (mdiChild *,void FAR *,WORD);
BOOL Train_Network            (mdiChild *,void FAR *,WORD);
BOOL uExpVal                  (mdiChild *,void FAR *,WORD);
BOOL uPowVal                  (mdiChild *,void FAR *,WORD);
BOOL uCubSpl                  (mdiChild *,void FAR *,WORD);
BOOL DefFrmSlantField         (mdiChild *,void FAR *,WORD);
BOOL uStretchCont             (mdiChild *,void FAR *,WORD);
BOOL DefFrmSlantDec           (mdiChild *,void FAR *,WORD);
BOOL DefFrmSlantSLDec         (mdiChild *,void FAR *,WORD);
BOOL uConnectCont             (mdiChild *,void FAR *,WORD);
BOOL bIsVTO                   (mdiChild *,void FAR *,WORD);
// BOOL uShowClndr               (mdiChild *,void FAR *,WORD);
BOOL uDelData                 (mdiChild *,void FAR *,WORD);
BOOL uTurningPoint            (mdiChild *,void FAR *,WORD);
BOOL uMutualExcludeNone       (mdiChild *,void FAR *,WORD);
BOOL DefMovePattern           (mdiChild *,void FAR *,WORD);
BOOL DefFrmDefDec             (mdiChild *,void FAR *,WORD);
BOOL DefFrmMultiField         (mdiChild *,void FAR *,WORD);
BOOL ChangeCubSplPt           (mdiChild *,void FAR *,WORD);
BOOL Vto_OnMove               (mdiChild *,void FAR *,WORD);
BOOL Vto_DrawObject           (mdiChild *,void FAR *,WORD);
BOOL AddSHEnt                 (mdiChild *,void FAR *,WORD);
BOOL bFindInd                 (mdiChild *,void FAR *,WORD);
BOOL WriteCubSpl              (mdiChild *,void FAR *,WORD);
BOOL uSetMulti                (mdiChild *,void FAR *,WORD);
BOOL uCopyRefs                (mdiChild *,void FAR *,WORD);
BOOL uCalcSoftVect            (mdiChild *,void FAR *,WORD);
BOOL CreateScreen             (mdiChild *,void FAR *,WORD);
BOOL GenericTool              (mdiChild *,void FAR *,WORD);
BOOL CallProc                 (mdiChild *,void FAR *,WORD);
BOOL ActivateScreen           (mdiChild *,void FAR *,WORD);
BOOL SetScale                 (mdiChild *,void FAR *,WORD);
BOOL StoreData                (mdiChild *,void FAR *,WORD);
BOOL SetDocSide               (mdiChild *,void FAR *,WORD);
BOOL SetDocBestSize           (mdiChild *,void FAR *,WORD);
BOOL ModifyRecall             (mdiChild *,void FAR *,WORD);
BOOL GetRecallData            (mdiChild *,void FAR *,WORD);
BOOL GetProfileString         (mdiChild *,void FAR *,WORD);
BOOL DefTrcImage              (mdiChild *,void FAR *,WORD);
BOOL GetUserName              (mdiChild *,void FAR *,WORD);
BOOL GetActUser               (mdiChild *,void FAR *,WORD);
BOOL lPatListNext             (mdiChild *,void FAR *,WORD);
BOOL lPatListPrev             (mdiChild *,void FAR *,WORD);
BOOL lPatListFirst            (mdiChild *,void FAR *,WORD);
BOOL lPatListInit             (mdiChild *,void FAR *,WORD);
BOOL uSetPatNr                (mdiChild *,void FAR *,WORD);
BOOL lAlphaScroll             (mdiChild *,void FAR *,WORD);
BOOL lPatListLast             (mdiChild *,void FAR *,WORD);
BOOL lSelect                  (mdiChild *,void FAR *,WORD);
BOOL BuildDocIcons            (mdiChild *,void FAR *,WORD);
BOOL ShowDocIcons             (mdiChild *,void FAR *,WORD);
BOOL lPrint                   (mdiChild *,void FAR *,WORD);
BOOL LinkElements             (mdiChild *,void FAR *,WORD);
BOOL CreatePaintDocument      (mdiChild *,void FAR *,WORD);
BOOL SetIndIndex              (mdiChild *,void FAR *,WORD);
BOOL lFNrInit                 (mdiChild *,void FAR *,WORD);
BOOL lFNrFirst                (mdiChild *,void FAR *,WORD);
BOOL lFNrLast                 (mdiChild *,void FAR *,WORD);
BOOL lFNrNext                 (mdiChild *,void FAR *,WORD);
BOOL lFNrPrev                 (mdiChild *,void FAR *,WORD);
BOOL lGetFallNummer           (mdiChild *,void FAR *,WORD);
BOOL DestroyDocument          (mdiChild *,void FAR *,WORD);
BOOL InitHk                   (mdiChild *,void FAR *,WORD);
BOOL lFNrScNummer             (mdiChild *,void FAR *,WORD);
BOOL lSetrelFNr               (mdiChild *,void FAR *,WORD);
BOOL lPatSearchName           (mdiChild *,void FAR *,WORD);
BOOL lScrollAlpha             (mdiChild *,void FAR *,WORD);
BOOL CallOnUpdate             (mdiChild *,void FAR *,WORD);
BOOL TileDocuments            (mdiChild *,void FAR *,WORD);
BOOL ArrangeDocuments         (mdiChild *,void FAR *,WORD);
BOOL SwitchToNextWindow       (mdiChild *,void FAR *,WORD);
BOOL SwitchToPrevWindow       (mdiChild *,void FAR *,WORD);
BOOL CreateNewPatRec          (mdiChild *,void FAR *,WORD);
BOOL DestroyAllDocuments      (mdiChild *,void FAR *,WORD);
BOOL SwitchToNextField        (mdiChild *,void FAR *,WORD);
BOOL SwitchToPrevField        (mdiChild *,void FAR *,WORD);
BOOL ActivateApp              (mdiChild *,void FAR *,WORD);
BOOL Str_Scanf                (mdiChild *,void FAR *,WORD);
BOOL InstallClpObserver       (mdiChild *,void FAR *,WORD);
BOOL WriteClpBoard            (mdiChild *,void FAR *,WORD);
BOOL AvoidActivation          (mdiChild *,void FAR *,WORD);
BOOL RemoveObserver           (mdiChild *,void FAR *,WORD);
BOOL TaskExist                (mdiChild *,void FAR *,WORD);
BOOL OnTaskDestroy            (mdiChild *,void FAR *,WORD);
BOOL StartTask                (mdiChild *,void FAR *,WORD);
BOOL WatchCreation            (mdiChild *,void FAR *,WORD);
BOOL lGetSelCount             (mdiChild *,void FAR *,WORD);
BOOL ShowToolList             (mdiChild *,void FAR *,WORD);
BOOL GetTextFrom              (mdiChild *,void FAR *,WORD);
BOOL PrintDocument            (mdiChild *,void FAR *,WORD);
BOOL mNumSize                 (mdiChild *,void FAR *,WORD);
BOOL DefmNum                  (mdiChild *,void FAR *,WORD);
BOOL GetDataWithCodeData      (mdiChild *,void FAR *,WORD);
BOOL OnDocumentDestroy        (mdiChild *,void FAR *,WORD);
BOOL IsInJobList              (mdiChild *,void FAR *,WORD);
BOOL IsDocOpen                (mdiChild *,void FAR *,WORD);
BOOL PaddString               (mdiChild *,void FAR *,WORD);
BOOL ExtractString            (mdiChild *,void FAR *,WORD);
BOOL bCompareString           (mdiChild *,void FAR *,WORD);
BOOL GetUserNames             (mdiChild *,void FAR *,WORD);
BOOL GetIndFormKey            (mdiChild *,void FAR *,WORD);
BOOL GetKeyFromInd            (mdiChild *,void FAR *,WORD);
BOOL bLongVarEqual            (mdiChild *,void FAR *,WORD);
BOOL LockPatient              (mdiChild *,void FAR *,WORD);
BOOL StartLogin               (mdiChild *,void FAR *,WORD);
BOOL EndLogin                 (mdiChild *,void FAR *,WORD);
BOOL GetUserNmbr              (mdiChild *,void FAR *,WORD);
BOOL GetLicense               (mdiChild *,void FAR *,WORD);
BOOL Beeps                    (mdiChild *,void FAR *,WORD);
BOOL GetBemerkung             (mdiChild *,void FAR *,WORD);
BOOL DoHotkeyAction           (mdiChild *,void FAR *,WORD);
BOOL SetCharCallback          (mdiChild *,void FAR *,WORD);
BOOL PrgExit                  (mdiChild *,void FAR *,WORD);
BOOL SetWndFormat             (mdiChild *,void FAR *,WORD);
BOOL GetFormatStrings         (mdiChild *,void FAR *,WORD);
BOOL IsDocOpenName            (mdiChild *,void FAR *,WORD);
BOOL ActivateDoc              (mdiChild *,void FAR *,WORD);
BOOL GetDocFName              (mdiChild *,void FAR *,WORD);
BOOL DefEntParam              (mdiChild *,void FAR *,WORD);
BOOL DefEnterPoint            (mdiChild *,void FAR *,WORD);
BOOL DefEnterCont             (mdiChild *,void FAR *,WORD);
BOOL FrmImportImage           (mdiChild *,void FAR *,WORD);
BOOL GetFieldFormat           (mdiChild *,void FAR *,WORD);
BOOL GetFieldModify           (mdiChild *,void FAR *,WORD);
BOOL SetFieldModify           (mdiChild *,void FAR *,WORD);
BOOL ShowPatHisto             (mdiChild *,void FAR *,WORD);
BOOL DMWSLogout               (mdiChild *,void FAR *,WORD);
BOOL FrmStoreImage            (mdiChild *,void FAR *,WORD);
BOOL SetFocusToDoc            (mdiChild *,void FAR *,WORD);
BOOL uAddDays                 (mdiChild *,void FAR *,WORD);
BOOL ImgGetOriginal           (mdiChild *,void FAR *,WORD);
BOOL ImgUserFlt               (mdiChild *,void FAR *,WORD);
BOOL ImgBestContrast          (mdiChild *,void FAR *,WORD);
BOOL ImgCrispFlt              (mdiChild *,void FAR *,WORD);
BOOL ImgMedianFlt             (mdiChild *,void FAR *,WORD);
BOOL ImgSobelFlt              (mdiChild *,void FAR *,WORD);
BOOL ImgLocalContrast         (mdiChild *,void FAR *,WORD);
BOOL Vto_SetMode              (mdiChild *,void FAR *,WORD);
BOOL Vto_Start                (mdiChild *,void FAR *,WORD);
BOOL Vto_ApplyCut             (mdiChild *,void FAR *,WORD);
BOOL SynchorizeUpdate         (mdiChild *,void FAR *,WORD);
BOOL CloseDocument            (mdiChild *,void FAR *,WORD);
BOOL LinkToDList              (mdiChild *,void FAR *,WORD);
BOOL lDListNext               (mdiChild *,void FAR *,WORD);
BOOL lDListPrev               (mdiChild *,void FAR *,WORD);
BOOL lDListFirst              (mdiChild *,void FAR *,WORD);
BOOL lDListLast               (mdiChild *,void FAR *,WORD);
BOOL GetCreationData          (mdiChild *,void FAR *,WORD);
BOOL SetFNrRef                (mdiChild *,void FAR *,WORD);
BOOL GetFullDocumentName      (mdiChild *,void FAR *,WORD);
BOOL lDListInit               (mdiChild *,void FAR *,WORD);
BOOL ShowDocMaximized         (mdiChild *,void FAR *,WORD);
BOOL bDataEqual               (mdiChild *,void FAR *,WORD);
BOOL CallOnDestroy            (mdiChild *,void FAR *,WORD);
BOOL lDListGetScrollPos       (mdiChild *,void FAR *,WORD);
BOOL lDListGetLfndr           (mdiChild *,void FAR *,WORD);
BOOL uAddInd                  (mdiChild *,void FAR *,WORD);
BOOL uSubInd                  (mdiChild *,void FAR *,WORD);
BOOL uSetDate                 (mdiChild *,void FAR *,WORD);
BOOL ToBusy                   (mdiChild *,void FAR *,WORD);
BOOL RemoveControlFromLayer   (mdiChild *,void FAR *,WORD);
BOOL ActivateScreenLayer      (mdiChild *,void FAR *,WORD);
BOOL SetFocusToObject         (mdiChild *,void FAR *,WORD);
BOOL GetRecRefCount           (mdiChild *,void FAR *,WORD);
BOOL DelDataRecord            (mdiChild *,void FAR *,WORD);
BOOL CallWindowsHelp          (mdiChild *,void FAR *,WORD);
BOOL uAddMonths               (mdiChild *,void FAR *,WORD);
BOOL uAddYears                (mdiChild *,void FAR *,WORD);
BOOL SetWindowDimension       (mdiChild *,void FAR *,WORD);
BOOL SetWindowTitle           (mdiChild *,void FAR *,WORD);
BOOL GetDocInstance           (mdiChild *,void FAR *,WORD);
BOOL BringObjectToTail        (mdiChild *,void FAR *,WORD);
BOOL SetObjectSide            (mdiChild *,void FAR *,WORD);
BOOL DeleteFile               (mdiChild *,void FAR *,WORD);
BOOL FileSelector_Box         (mdiChild *,void FAR *,WORD);
BOOL DefPrgIcon               (mdiChild *,void FAR *,WORD);
BOOL GetLastBemerkung         (mdiChild *,void FAR *,WORD);
BOOL DefFrmStaticBitmap       (mdiChild *,void FAR *,WORD);
BOOL SetEntryHeight           (mdiChild *,void FAR *,WORD);
BOOL lUserListFirst           (mdiChild *,void FAR *,WORD);
BOOL lUserListLast            (mdiChild *,void FAR *,WORD);
BOOL lUserListNext            (mdiChild *,void FAR *,WORD);
BOOL lUserListPrev            (mdiChild *,void FAR *,WORD);
BOOL lUserListEq              (mdiChild *,void FAR *,WORD);
BOOL lUserListGetScroll       (mdiChild *,void FAR *,WORD);
BOOL hugeArrData              (mdiChild *,void FAR *,WORD);
BOOL findhugeArrData          (mdiChild *,void FAR *,WORD);
BOOL newUserEntry             (mdiChild *,void FAR *,WORD);
BOOL doCloseRecord            (mdiChild *,void FAR *,WORD);
BOOL checkDuplicateUserName   (mdiChild *,void FAR *,WORD);
BOOL OnActivation             (mdiChild *,void FAR *,WORD);
BOOL ShowmNumHelp             (mdiChild *,void FAR *,WORD);
BOOL ShowmNumGauss            (mdiChild *,void FAR *,WORD);
BOOL DefActivationRegion      (mdiChild *,void FAR *,WORD);
BOOL DefNormObj               (mdiChild *,void FAR *,WORD);
BOOL DefNormTab               (mdiChild *,void FAR *,WORD);
BOOL GetNorm                  (mdiChild *,void FAR *,WORD);
BOOL ListCharCallBack         (mdiChild *,void FAR *,WORD);
BOOL IsFirstCharAlpha         (mdiChild *,void FAR *,WORD);
BOOL IsFirstCharNumeric       (mdiChild *,void FAR *,WORD);
BOOL RemoveLastChar           (mdiChild *,void FAR *,WORD);
BOOL DefFrmBField             (mdiChild *,void FAR *,WORD);
BOOL GetCapStr                (mdiChild *,void FAR *,WORD);
BOOL GetDigits                (mdiChild *,void FAR *,WORD);
BOOL CreatePostIt             (mdiChild *,void FAR *,WORD);
BOOL RemoveSpaces             (mdiChild *,void FAR *,WORD);
BOOL uGetThirdPt              (mdiChild *,void FAR *,WORD);
BOOL uGetNAbstPt              (mdiChild *,void FAR *,WORD);
BOOL uGetRotPt                (mdiChild *,void FAR *,WORD);
BOOL uCalcNewPt               (mdiChild *,void FAR *,WORD);
BOOL GetGrowthVal             (mdiChild *,void FAR *,WORD);
BOOL GetMidPts                (mdiChild *,void FAR *,WORD);
BOOL uSin                     (mdiChild *,void FAR *,WORD);
BOOL uCos                     (mdiChild *,void FAR *,WORD);
BOOL uGetVGrid                (mdiChild *,void FAR *,WORD);
BOOL DefOutVGrid              (mdiChild *,void FAR *,WORD);
BOOL SetMouseScale            (mdiChild *,void FAR *,WORD);
BOOL InitializeData           (mdiChild *,void FAR *,WORD);
BOOL GetListHeight            (mdiChild *,void FAR *,WORD);
BOOL OptimizeHeight           (mdiChild *,void FAR *,WORD);
BOOL lFNrListGetScroll        (mdiChild *,void FAR *,WORD);
BOOL CopyHandle               (mdiChild *,void FAR *,WORD);
BOOL SetNewPts                (mdiChild *,void FAR *,WORD);
BOOL GrowPt                   (mdiChild *,void FAR *,WORD);
BOOL GrowCnt                  (mdiChild *,void FAR *,WORD);
BOOL CombineData              (mdiChild *,void FAR *,WORD);
BOOL GetFieldRightUpper       (mdiChild *,void FAR *,WORD);
BOOL uAddYearsDec             (mdiChild *,void FAR *,WORD);
BOOL SetFrmEditSize           (mdiChild *,void FAR *,WORD);
BOOL ExtractData              (mdiChild *,void FAR *,WORD);
BOOL DelAllPatData            (mdiChild *,void FAR *,WORD);
BOOL GetPrTextHeight          (mdiChild *,void FAR *,WORD);
BOOL RecallOp                 (mdiChild *,void FAR *,WORD);
BOOL CreatePrintDocument      (mdiChild *,void FAR *,WORD);
BOOL GetRecallType            (mdiChild *,void FAR *,WORD);
BOOL GetPrinterType           (mdiChild *,void FAR *,WORD);
BOOL SetPrinter               (mdiChild *,void FAR *,WORD);
BOOL SetListAbort             (mdiChild *,void FAR *,WORD);
BOOL ClearListAbort           (mdiChild *,void FAR *,WORD);
BOOL GetDefaultPrinterName    (mdiChild *,void FAR *,WORD);
BOOL SetCaretToEnd            (mdiChild *,void FAR *,WORD);
BOOL SetEditCaretToEnd        (mdiChild *,void FAR *,WORD);
BOOL ClearQueue               (mdiChild *,void FAR *,WORD);
BOOL Vto_CalcAllRotCents      (mdiChild *,void FAR *,WORD);
BOOL Start_TimeMark           (mdiChild *,void FAR *,WORD);
BOOL DefMoveField             (mdiChild *,void FAR *,WORD);
BOOL DefMoveLine              (mdiChild *,void FAR *,WORD);
BOOL DefHelpLine              (mdiChild *,void FAR *,WORD);
BOOL SetDblClkProc            (mdiChild *,void FAR *,WORD);
BOOL IsHandleValid            (mdiChild *,void FAR *,WORD);
BOOL CallExternProc           (mdiChild *,void FAR *,WORD);
BOOL GetTwainSources          (mdiChild *,void FAR *,WORD);
BOOL KettenLinienParameter    (mdiChild *,void FAR *,WORD);
BOOL GetKettenLinie           (mdiChild *,void FAR *,WORD);
BOOL BestPalette              (mdiChild *,void FAR *,WORD);
BOOL ModifyKettenLinienExt    (mdiChild *,void FAR *,WORD);
BOOL SplitCont                (mdiChild *,void FAR *,WORD);
BOOL DDSOle                   (mdiChild *,void FAR *,WORD);
BOOL FrmSetImage              (mdiChild *,void FAR *,WORD);
BOOL FrmWriteBMP              (mdiChild *,void FAR *,WORD);
BOOL ExtractPath              (mdiChild *,void FAR *,WORD);
BOOL FrmGetPixPerMeter        (mdiChild *,void FAR *,WORD);
BOOL FrmSetPixPerMeter        (mdiChild *,void FAR *,WORD);
BOOL FrmGetImgWidth           (mdiChild *,void FAR *,WORD);
BOOL FrmDrawContDirect        (mdiChild *,void FAR *,WORD);
BOOL uGetImgPhysScale         (mdiChild *,void FAR *,WORD);
BOOL CreateEdgeTable          (mdiChild *,void FAR *,WORD);
BOOL FillInEdges              (mdiChild *,void FAR *,WORD);
BOOL FrmMorphImage            (mdiChild *,void FAR *,WORD);
BOOL Trc_DefRectangle         (mdiChild *,void FAR *,WORD);
BOOL MakeCont                 (mdiChild *,void FAR *,WORD);
BOOL uMultiDivideCont         (mdiChild *,void FAR *,WORD);
BOOL SetIndElement            (mdiChild *,void FAR *,WORD);
BOOL MakeContFromDec          (mdiChild *,void FAR *,WORD);
BOOL FrmGetImageScaleFact     (mdiChild *,void FAR *,WORD);
BOOL SetEditOverwrite         (mdiChild *,void FAR *,WORD);
BOOL FrmGetImageFileName      (mdiChild *,void FAR *,WORD);
BOOL UseIntern                (mdiChild *,void FAR *,WORD);
BOOL Use                      (mdiChild *,void FAR *,WORD);
BOOL Out                      (mdiChild *,void FAR *,WORD);
BOOL InOut                    (mdiChild *,void FAR *,WORD);
BOOL NewRec                   (mdiChild *,void FAR *,WORD);
BOOL SetObjCallBack           (mdiChild *,void FAR *,WORD);
BOOL CreateDialogDocument     (mdiChild *,void FAR *,WORD);
BOOL lSetSelCallBack          (mdiChild *,void FAR *,WORD);
BOOL lChangeSelection         (mdiChild *,void FAR *,WORD);
BOOL CallOverSelection        (mdiChild *,void FAR *,WORD);
BOOL Do                       (mdiChild *,void FAR *,WORD);
BOOL GetNetWorkAddress        (mdiChild *,void FAR *,WORD);
BOOL PaintStdHeader           (mdiChild *,void FAR *,WORD);
BOOL EndCreateMappe           (mdiChild *,void FAR *,WORD);
BOOL AddMappElem              (mdiChild *,void FAR *,WORD);
BOOL StartCreateMappe         (mdiChild *,void FAR *,WORD);
BOOL CreateMapScreen          (mdiChild *,void FAR *,WORD);
BOOL SetMenuText              (mdiChild *,void FAR *,WORD);
BOOL AddMenuCommand           (mdiChild *,void FAR *,WORD);
BOOL SetButtons               (mdiChild *,void FAR *,WORD);
BOOL UseDialogDocument        (mdiChild *,void FAR *,WORD);
BOOL GetRecordPtr             (mdiChild *,void FAR *,WORD);
BOOL ReUseRecord              (mdiChild *,void FAR *,WORD);
BOOL LoadInternList           (mdiChild *,void FAR *,WORD);
BOOL MoveToolGroup            (mdiChild *,void FAR *,WORD);
BOOL SetToolExtension         (mdiChild *,void FAR *,WORD);
BOOL SetPrgCaption            (mdiChild *,void FAR *,WORD);
BOOL OnSizeChanged            (mdiChild *,void FAR *,WORD);
BOOL SetDelayedUpdate         (mdiChild *,void FAR *,WORD);
BOOL SetDestruktor            (mdiChild *,void FAR *,WORD);
BOOL CallForSelected          (mdiChild *,void FAR *,WORD);
BOOL LoadList                 (mdiChild *,void FAR *,WORD);
BOOL PackList                 (mdiChild *,void FAR *,WORD);
BOOL lSetSelChangeCallback    (mdiChild *,void FAR *,WORD);
BOOL lSetMaxSelCount          (mdiChild *,void FAR *,WORD);
BOOL CreateInnerList          (mdiChild *,void FAR *,WORD);
BOOL AddRecToInnerList        (mdiChild *,void FAR *,WORD);
BOOL bIsSelected              (mdiChild *,void FAR *,WORD);
BOOL CallOverInnerList        (mdiChild *,void FAR *,WORD);
BOOL RemoveRecFromInnerList   (mdiChild *,void FAR *,WORD);
BOOL CallInInnerListFor       (mdiChild *,void FAR *,WORD);
BOOL CatMultiString           (mdiChild *,void FAR *,WORD);
BOOL AddIconEleEx             (mdiChild *,void FAR *,WORD);
BOOL CreateIconFolder         (mdiChild *,void FAR *,WORD);
BOOL ShowIconFolder           (mdiChild *,void FAR *,WORD);
BOOL uTimeNow                 (mdiChild *,void FAR *,WORD);
BOOL uDiffTime                (mdiChild *,void FAR *,WORD);
BOOL DefFrmTime               (mdiChild *,void FAR *,WORD);
BOOL ActivateMapElem          (mdiChild *,void FAR *,WORD);
BOOL lCallDefSel              (mdiChild *,void FAR *,WORD);
BOOL lSetFocusFunction        (mdiChild *,void FAR *,WORD);
BOOL PaintFullHeader          (mdiChild *,void FAR *,WORD);
BOOL PaintFullBottom          (mdiChild *,void FAR *,WORD);
BOOL PaintStdBottom           (mdiChild *,void FAR *,WORD);
BOOL uAddTime                 (mdiChild *,void FAR *,WORD);
BOOL uSetTime                 (mdiChild *,void FAR *,WORD);
BOOL ScaleDateTime            (mdiChild *,void FAR *,WORD);
BOOL GetScaleDateTime         (mdiChild *,void FAR *,WORD);
BOOL uAddRelTime              (mdiChild *,void FAR *,WORD);
BOOL LoadInnerList            (mdiChild *,void FAR *,WORD);
BOOL CallProcOnMode           (mdiChild *,void FAR *,WORD);
BOOL SetOutContext            (mdiChild *,void FAR *,WORD);
BOOL PushToPackList           (mdiChild *,void FAR *,WORD);
BOOL SetToolRefHandle         (mdiChild *,void FAR *,WORD);
BOOL ActivateInInnerList      (mdiChild *,void FAR *,WORD);
BOOL DeActivateInInnerList    (mdiChild *,void FAR *,WORD);
BOOL Trc_DefFilledCont        (mdiChild *,void FAR *,WORD);
BOOL GetFieldRightLower       (mdiChild *,void FAR *,WORD);
BOOL bDateGreater             (mdiChild *,void FAR *,WORD);
BOOL DefFrmTable              (mdiChild *,void FAR *,WORD);
BOOL RestoreZoom              (mdiChild *,void FAR *,WORD);
BOOL ActivateZoom             (mdiChild *,void FAR *,WORD);
BOOL SetContrast              (mdiChild *,void FAR *,WORD);
BOOL RepeatedCall             (mdiChild *,void FAR *,WORD);
BOOL ClearSemaphore           (mdiChild *,void FAR *,WORD);
BOOL SetSemaphore             (mdiChild *,void FAR *,WORD);
BOOL TestSemaphore            (mdiChild *,void FAR *,WORD);
BOOL BeginTransaction         (mdiChild *,void FAR *,WORD);
BOOL AbortTransaction         (mdiChild *,void FAR *,WORD);
BOOL EndTransaction           (mdiChild *,void FAR *,WORD);
BOOL CallOptScript            (mdiChild *,void FAR *,WORD);
BOOL SetObjectColor           (mdiChild *,void FAR *,WORD);
BOOL bWordIndGreater          (mdiChild *,void FAR *,WORD);
BOOL GetLineCount             (mdiChild *,void FAR *,WORD);
BOOL EmptyInnerList           (mdiChild *,void FAR *,WORD);
BOOL BindInnerListToOuterList (mdiChild *,void FAR *,WORD);
BOOL GetCopy                  (mdiChild *,void FAR *,WORD);
BOOL IsUpdateDone             (mdiChild *,void FAR *,WORD);
BOOL CreateUniqueFile         (mdiChild *,void FAR *,WORD);
BOOL OpenFileDirect           (mdiChild *,void FAR *,WORD);
BOOL CloseFile                (mdiChild *,void FAR *,WORD);
BOOL WriteToFile              (mdiChild *,void FAR *,WORD);
BOOL ReadLn                   (mdiChild *,void FAR *,WORD);
BOOL ReadBinary               (mdiChild *,void FAR *,WORD);
BOOL WriteLn                  (mdiChild *,void FAR *,WORD);
BOOL CopyFileTo               (mdiChild *,void FAR *,WORD);
BOOL ExecProgram              (mdiChild *,void FAR *,WORD);
BOOL DestroyFile              (mdiChild *,void FAR *,WORD);
BOOL SetFileAttr              (mdiChild *,void FAR *,WORD);
BOOL UseDialogDocumentTellPar (mdiChild *,void FAR *,WORD);
BOOL ChangeUseDialogDocumentPars (mdiChild *,void FAR *,WORD);
BOOL CopyFromRecord           (mdiChild *,void FAR *,WORD);
BOOL CopyToRecord             (mdiChild *,void FAR *,WORD);
BOOL lSetListMode             (mdiChild *,void FAR *,WORD);
BOOL lSetDblClkCallBack       (mdiChild *,void FAR *,WORD);
BOOL LockTable                (mdiChild *,void FAR *,WORD);
BOOL UnlockTable              (mdiChild *,void FAR *,WORD);
BOOL AvoidInput               (mdiChild *,void FAR *,WORD);
BOOL SetStatText              (mdiChild *,void FAR *,WORD);
BOOL AvoidUpdates             (mdiChild *,void FAR *,WORD);
BOOL uGetDevString            (mdiChild *,void FAR *,WORD);
BOOL DoWhile                  (mdiChild *,void FAR *,WORD);
BOOL DefFrmRectImage          (mdiChild *,void FAR *,WORD);
BOOL SetDocBestWidth          (mdiChild *,void FAR *,WORD);
BOOL InstallKeyWord           (mdiChild *,void FAR *,WORD);
BOOL SetDigCnf                (mdiChild *,void FAR *,WORD);
BOOL DoIconEleSelect          (mdiChild *,void FAR *,WORD);
BOOL bCmpShort                (mdiChild *,void FAR *,WORD);
BOOL bCmpLong                 (mdiChild *,void FAR *,WORD);
BOOL bCmpFloat                (mdiChild *,void FAR *,WORD);
BOOL bCmpString               (mdiChild *,void FAR *,WORD);
BOOL bCmpDate                 (mdiChild *,void FAR *,WORD);
BOOL bCmpTime                 (mdiChild *,void FAR *,WORD);
BOOL RemoveFormatInfo         (mdiChild *,void FAR *,WORD);
BOOL WriteToIniFile           (mdiChild *,void FAR *,WORD);
BOOL RenameFile               (mdiChild *,void FAR *,WORD);
BOOL GetPascalString          (mdiChild *,void FAR *,WORD);
BOOL WinExit                  (mdiChild *,void FAR *,WORD);
BOOL GetConnNmbr              (mdiChild *,void FAR *,WORD);
BOOL DivideIntoFormatStrings  (mdiChild *,void FAR *,WORD);
BOOL AllowAdditionalSel       (mdiChild *,void FAR *,WORD);
BOOL DisableFlapChange        (mdiChild *,void FAR *,WORD);
BOOL DBCall_Get               (mdiChild *,void FAR *,WORD);
BOOL DBCall_Update            (mdiChild *,void FAR *,WORD);
BOOL DBCall_Insert            (mdiChild *,void FAR *,WORD);
BOOL DBCall_Excute            (mdiChild *,void FAR *,WORD);
BOOL LongToFloat              (mdiChild *,void FAR *,WORD);
BOOL ShortToFloat             (mdiChild *,void FAR *,WORD);
BOOL FloatToLong              (mdiChild *,void FAR *,WORD);
BOOL FloatToShort             (mdiChild *,void FAR *,WORD);
BOOL LongToShort              (mdiChild *,void FAR *,WORD);
BOOL ShortToLong              (mdiChild *,void FAR *,WORD);
BOOL ExtractDate              (mdiChild *,void FAR *,WORD);
BOOL BuildDate                (mdiChild *,void FAR *,WORD);
BOOL ExtractTime              (mdiChild *,void FAR *,WORD);
BOOL BuildTime                (mdiChild *,void FAR *,WORD);
BOOL FormatDate               (mdiChild *,void FAR *,WORD);
BOOL FormatTime               (mdiChild *,void FAR *,WORD);
BOOL DBCall_Delete            (mdiChild *,void FAR *,WORD);
BOOL DBCall_ForSelection      (mdiChild *,void FAR *,WORD);
BOOL IniDate                  (mdiChild *,void FAR *,WORD);
BOOL DefProjectPoint          (mdiChild *,void FAR *,WORD);
BOOL uGetx                    (mdiChild *,void FAR *,WORD);
BOOL uGety                    (mdiChild *,void FAR *,WORD);
BOOL UnScaleDateTime          (mdiChild *,void FAR *,WORD);
BOOL WaitOnMouseClk           (mdiChild *,void FAR *,WORD);
BOOL GetRecPrimKey            (mdiChild *,void FAR *,WORD);
BOOL SetDateMover             (mdiChild *,void FAR *,WORD);
BOOL SetDocVeryBestSize       (mdiChild *,void FAR *,WORD);
BOOL uClipCont                (mdiChild *,void FAR *,WORD);
BOOL DefClickPattern          (mdiChild *,void FAR *,WORD);
BOOL SortList                 (mdiChild *,void FAR *,WORD);
BOOL SortList_neg             (mdiChild *,void FAR *,WORD);
BOOL PresentData              (mdiChild *,void FAR *,WORD);
BOOL uAddDateTime             (mdiChild *,void FAR *,WORD);
BOOL uDiffDateTime            (mdiChild *,void FAR *,WORD);
BOOL DBCall_Copy              (mdiChild *,void FAR *,WORD);
BOOL bIsInIntervall           (mdiChild *,void FAR *,WORD);
BOOL GetIntervallBorders      (mdiChild *,void FAR *,WORD);
BOOL DelDefSel                (mdiChild *,void FAR *,WORD);
BOOL DBCall_FormComboList     (mdiChild *,void FAR *,WORD);
BOOL DBCall_ToolComboList     (mdiChild *,void FAR *,WORD);
BOOL DBCall_FormMultiComboList(mdiChild *,void FAR *,WORD);
BOOL DBCall_ToolMultiComboList(mdiChild *,void FAR *,WORD);
BOOL GetScriptProperty        (mdiChild *,void FAR *,WORD);
BOOL GetScriptProperty_Int    (mdiChild *,void FAR *,WORD);
BOOL GetScriptInfo            (mdiChild *,void FAR *,WORD);
BOOL GetNextScriptInfo        (mdiChild *,void FAR *,WORD);
BOOL GetFirstScriptInfo       (mdiChild *,void FAR *,WORD);
BOOL PackData                 (mdiChild *,void FAR *,WORD);
BOOL GetActiveElem            (mdiChild *,void FAR *,WORD);
BOOL CopySameVars             (mdiChild *,void FAR *,WORD);
BOOL GetDataWithChild_Code    (mdiChild *,void FAR *,WORD);
BOOL GetVarSize               (mdiChild *,void FAR *,WORD);
BOOL SetEditSize              (mdiChild *,void FAR *,WORD);
BOOL RestoreRecord            (mdiChild *,void FAR *,WORD);
BOOL SaveRecord               (mdiChild *,void FAR *,WORD);
BOOL GetFormatBaseHeight      (mdiChild *,void FAR *,WORD);
BOOL DefTransparentBitmap     (mdiChild *,void FAR *,WORD);
BOOL InstallSelectMode        (mdiChild *,void FAR *,WORD);
BOOL SetBitSelectMode         (mdiChild *,void FAR *,WORD);
BOOL RemoveCRLF               (mdiChild *,void FAR *,WORD);
BOOL DDE_Initiate             (mdiChild *,void FAR *,WORD);
BOOL DDE_Terminate            (mdiChild *,void FAR *,WORD);
BOOL DDE_Request              (mdiChild *,void FAR *,WORD);
BOOL DDE_Poke                 (mdiChild *,void FAR *,WORD);
BOOL DDE_Execute              (mdiChild *,void FAR *,WORD);
BOOL SetNewFileRef            (mdiChild *,void FAR *,WORD);
BOOL KisInit                  (mdiChild *,void FAR *,WORD);
BOOL KisExit                  (mdiChild *,void FAR *,WORD);
BOOL KisSelectionOpen         (mdiChild *,void FAR *,WORD);
BOOL KisSelectionClose        (mdiChild *,void FAR *,WORD);
BOOL KisRecordRead            (mdiChild *,void FAR *,WORD);
BOOL KisRecordWrite           (mdiChild *,void FAR *,WORD);
BOOL KisRecordCreate          (mdiChild *,void FAR *,WORD);
BOOL KisRecordFree            (mdiChild *,void FAR *,WORD);
BOOL KisTableOpen             (mdiChild *,void FAR *,WORD);
BOOL KisTableClose            (mdiChild *,void FAR *,WORD);
BOOL KisDataGet               (mdiChild *,void FAR *,WORD);
BOOL KisDataSet               (mdiChild *,void FAR *,WORD);
BOOL ProjectCallBack          (mdiChild *,void FAR *,WORD);
BOOL In_Str                   (mdiChild *,void FAR *,WORD);
BOOL Mid_Str                  (mdiChild *,void FAR *,WORD);
BOOL Str_Len                  (mdiChild *,void FAR *,WORD);
BOOL DDE_GetLastError         (mdiChild *,void FAR *,WORD);
BOOL KisConvBcdToMac          (mdiChild *,void FAR *,WORD);
BOOL KisConvMacToBcd          (mdiChild *,void FAR *,WORD);
BOOL DocumentToPrinter        (mdiChild *,void FAR *,WORD);
BOOL PrintDocumentEx          (mdiChild *,void FAR *,WORD);
BOOL InterpreteHdString       (mdiChild *,void FAR *,WORD);
BOOL ActivateObject           (mdiChild *,void FAR *,WORD);
BOOL ConnectToCheckBox        (mdiChild *,void FAR *,WORD);
BOOL GetScriptParameter       (mdiChild *,void FAR *,WORD);
BOOL Trc_DefRectImage         (mdiChild *,void FAR *,WORD);
BOOL DefMoveRect              (mdiChild *,void FAR *,WORD);
BOOL DefMoveRectImage         (mdiChild *,void FAR *,WORD);
BOOL uMulInd                  (mdiChild *,void FAR *,WORD);
BOOL uDivInd                  (mdiChild *,void FAR *,WORD);
BOOL uMulLong                 (mdiChild *,void FAR *,WORD);
BOOL uDivLong                 (mdiChild *,void FAR *,WORD);
BOOL DefFrmShort              (mdiChild *,void FAR *,WORD);
BOOL DefFrmLong               (mdiChild *,void FAR *,WORD);
BOOL DefFrmMoney              (mdiChild *,void FAR *,WORD);
BOOL IstFeierTag              (mdiChild *,void FAR *,WORD);
BOOL SetToolPalette           (mdiChild *,void FAR *,WORD);
BOOL BitEditMode              (mdiChild *,void FAR *,WORD);
BOOL PresentBitmap            (mdiChild *,void FAR *,WORD);
BOOL GetNextFlagInd           (mdiChild *,void FAR *,WORD);
BOOL SetSetFocusProc          (mdiChild *,void FAR *,WORD);
BOOL BitCount                 (mdiChild *,void FAR *,WORD);
BOOL bVektorInProd            (mdiChild *,void FAR *,WORD);
BOOL UnionVektor              (mdiChild *,void FAR *,WORD);
BOOL GenerateVector           (mdiChild *,void FAR *,WORD);
BOOL SetFilterProc            (mdiChild *,void FAR *,WORD);
BOOL PresentText              (mdiChild *,void FAR *,WORD);
BOOL RemoveChar               (mdiChild *,void FAR *,WORD);
BOOL ExpandBinary             (mdiChild *,void FAR *,WORD);
BOOL GetBaseUnit              (mdiChild *,void FAR *,WORD);
BOOL DefMultiDim              (mdiChild *,void FAR *,WORD);
BOOL WriteMultiDim            (mdiChild *,void FAR *,WORD);
BOOL ReadMultiDim             (mdiChild *,void FAR *,WORD);
BOOL LoadMultiDim             (mdiChild *,void FAR *,WORD);
BOOL UpdateScreenImmediate    (mdiChild *,void FAR *,WORD);
BOOL GetVersionInfo           (mdiChild *,void FAR *,WORD);
BOOL SetFieldMode             (mdiChild *,void FAR *,WORD);
BOOL SetMapExtent             (mdiChild *,void FAR *,WORD);
BOOL SetDocumentTitle         (mdiChild *,void FAR *,WORD);   // MDICHILD.CPP
BOOL SetEditMode              (mdiChild *,void FAR *,WORD);   // DDSTOOL.CPP
BOOL SetOnActivate            (mdiChild *,void FAR *,WORD);
BOOL SetOnDeactivate          (mdiChild *,void FAR *,WORD);
BOOL SetObjModify             (mdiChild *,void FAR *,WORD);
BOOL GetObjModify             (mdiChild *,void FAR *,WORD);
BOOL SetEditFormatMaps        (mdiChild *,void FAR *,WORD);
BOOL SetObjFormatMaps         (mdiChild *,void FAR *,WORD);
BOOL StrRemoveFormat          (mdiChild *,void FAR *,WORD);
BOOL OpenPrinterDirect        (mdiChild *,void FAR *,WORD);
BOOL PrintDirect              (mdiChild *,void FAR *,WORD);
BOOL ClosePrinterDirect       (mdiChild *,void FAR *,WORD);
BOOL CRtoCRLF                 (mdiChild *,void FAR *,WORD);
BOOL bVektorTeilmenge         (mdiChild *,void FAR *,WORD);
BOOL IntersectionVektor       (mdiChild *,void FAR *,WORD);
BOOL GetDBHandler             (mdiChild *,void FAR *,WORD);
BOOL CreateFormTool           (mdiChild *,void FAR *,WORD);
BOOL FormToolPictureButton    (mdiChild *,void FAR *,WORD);
BOOL FormToolTextButton       (mdiChild *,void FAR *,WORD);
BOOL SetToolObjectColor       (mdiChild *,void FAR *,WORD);
BOOL GetObjLineHeight         (mdiChild *,void FAR *,WORD);
BOOL SetObjLineHeight         (mdiChild *,void FAR *,WORD);
BOOL SetFieldPageBreak        (mdiChild *,void FAR *,WORD);
BOOL GetFieldLeftLowerSeite   (mdiChild *,void FAR *,WORD);
BOOL CallDllProcP             (mdiChild *,void FAR *,WORD);
BOOL CallDllProcC             (mdiChild *,void FAR *,WORD);
BOOL CallDllBoolProcP         (mdiChild *,void FAR *,WORD);
BOOL CallDllBoolProcC         (mdiChild *,void FAR *,WORD);
BOOL FreeExternDll            (mdiChild *,void FAR *,WORD);
BOOL KisError                 (mdiChild *,void FAR *,WORD);
BOOL FileSeek                 (mdiChild *,void FAR *,WORD);
BOOL SetLineObjects           (mdiChild *,void FAR *,WORD);
BOOL NonRepeativeObjects      (mdiChild *,void FAR *,WORD);
BOOL SetExtraModify           (mdiChild *,void FAR *,WORD);
BOOL GetToolCoordinates       (mdiChild *,void FAR *,WORD);
BOOL SetDialogPos             (mdiChild *,void FAR *,WORD);
BOOL SplitPath                (mdiChild *,void FAR *,WORD);
BOOL lSetHeaderClkCallBack    (mdiChild *,void FAR *,WORD);
BOOL FindFirst                (mdiChild *,void FAR *,WORD);
BOOL FindNext                 (mdiChild *,void FAR *,WORD);
BOOL WriteScriptLog           (mdiChild *,void FAR *,WORD);
BOOL ExpandRNT                (mdiChild *,void FAR *,WORD);
BOOL MakeRNT                  (mdiChild *,void FAR *,WORD);
BOOL SetRecHash               (mdiChild *,void FAR *,WORD);
BOOL ClearRecHash             (mdiChild *,void FAR *,WORD);
BOOL SetToolModify            (mdiChild *,void FAR *,WORD);
BOOL GetToolModify            (mdiChild *,void FAR *,WORD);
BOOL GetToolModify            (mdiChild *,void FAR *,WORD);
BOOL SetCLINICUMEnvironment   (mdiChild *,void FAR *,WORD);
BOOL SndDefObj                (mdiChild *,void FAR *,WORD);
BOOL SndClear                 (mdiChild *,void FAR *,WORD);
BOOL bSndIsEmpty              (mdiChild *,void FAR *,WORD);
BOOL SndReadWav               (mdiChild *,void FAR *,WORD);
BOOL SndWriteWav              (mdiChild *,void FAR *,WORD);
BOOL SndPlayStart             (mdiChild *,void FAR *,WORD);
BOOL SndPause                 (mdiChild *,void FAR *,WORD);
BOOL SndRestart               (mdiChild *,void FAR *,WORD);
BOOL SndPlayStop              (mdiChild *,void FAR *,WORD);
BOOL SndRecStart              (mdiChild *,void FAR *,WORD);
BOOL SndRecStop               (mdiChild *,void FAR *,WORD);
BOOL bSndIsCompatible         (mdiChild *,void FAR *,WORD);
BOOL ShowFormList             (mdiChild *,void FAR *,WORD);
BOOL InitializeVoidData       (mdiChild *,void FAR *,WORD);
BOOL SetArrayData             (mdiChild *,void FAR *,WORD);
BOOL GetArrayData             (mdiChild *,void FAR *,WORD);
BOOL LockDataKey              (mdiChild *,void FAR *,WORD);
BOOL HideScreen               (mdiChild *,void FAR *,WORD);
BOOL ShortToQLong             (mdiChild *,void FAR *,WORD);
BOOL FloatToQLong             (mdiChild *,void FAR *,WORD);
BOOL LongToQLong              (mdiChild *,void FAR *,WORD);
BOOL QLongToShort             (mdiChild *,void FAR *,WORD);
BOOL QLongToFloat             (mdiChild *,void FAR *,WORD);
BOOL QLongToLong              (mdiChild *,void FAR *,WORD);
BOOL uAddQLong                (mdiChild *,void FAR *,WORD);
BOOL uSubQLong                (mdiChild *,void FAR *,WORD);
BOOL uDivQLong                (mdiChild *,void FAR *,WORD);
BOOL uMulQLong                (mdiChild *,void FAR *,WORD);
BOOL DoDBRep                  (mdiChild *,void FAR *,WORD);
BOOL DoDBRepIn                (mdiChild *,void FAR *,WORD);
BOOL GetDBToken               (mdiChild *,void FAR *,WORD);
BOOL UnlockDBToken            (mdiChild *,void FAR *,WORD);
BOOL ClearMyTokens            (mdiChild *,void FAR *,WORD);
BOOL MouseMoveProc            (mdiChild *,void FAR *,WORD);
BOOL MarkUpdateError          (mdiChild *,void FAR *,WORD);
BOOL SystemUpdate             (mdiChild *,void FAR *,WORD);
BOOL AlterTable               (mdiChild *,void FAR *,WORD);
BOOL ActivateList             (mdiChild *,void FAR *,WORD);
BOOL MarkVarStatic            (mdiChild *,void FAR *,WORD);
BOOL MarkVarDynamic           (mdiChild *,void FAR *,WORD);
BOOL OnScreenButtonDown       (mdiChild *,void FAR *,WORD);
BOOL CreateTable              (mdiChild *,void FAR *,WORD);
BOOL GetDBPointer             (mdiChild *,void FAR *,WORD);
BOOL ExeIs32Bit               (mdiChild *,void FAR *,WORD);
BOOL AddMessageHook           (mdiChild *,void FAR *,WORD);
BOOL GetFrameWindowHandle     (mdiChild *,void FAR *,WORD);
BOOL bCmpQLong                (mdiChild *,void FAR *,WORD);
BOOL IsKeyPressed             (mdiChild *,void FAR *,WORD);
BOOL SetScrollProc            (mdiChild *,void FAR *,WORD);
BOOL PushData                 (mdiChild *,void FAR *,WORD);
BOOL PopData                  (mdiChild *,void FAR *,WORD);
BOOL DenyBusy                 (mdiChild *,void FAR *,WORD);
BOOL AllowBusy                (mdiChild *,void FAR *,WORD);
BOOL DefineParse              (mdiChild *,void FAR *,WORD);
BOOL CheckExpression          (mdiChild *,void FAR *,WORD);
BOOL InsertStrAtCaretObj      (mdiChild *,void FAR *,WORD);
BOOL InsertStrAtCaretTool     (mdiChild *,void FAR *,WORD);
BOOL SetStrAtCaretObj         (mdiChild *,void FAR *,WORD);
BOOL SetStrAtCaretTool        (mdiChild *,void FAR *,WORD);
BOOL WordIn_Str               (mdiChild *,void FAR *,WORD);
BOOL DefineRegion             (mdiChild *,void FAR *,WORD);
BOOL RegioFromPoint           (mdiChild *,void FAR *,WORD);
BOOL RegioFromRect            (mdiChild *,void FAR *,WORD);
BOOL BestRegioFromPoint       (mdiChild *,void FAR *,WORD);
BOOL ExchangeStringWithReplaceList (mdiChild *,void FAR *,WORD);
BOOL ReplaceString               (mdiChild *,void FAR *,WORD);
BOOL ModifierToString            (mdiChild *,void FAR *,WORD);
BOOL SetCaretTo                  (mdiChild *,void FAR *,WORD);
BOOL GetFieldLeftLowerAnzahlSeite (mdiChild *,void FAR *,WORD);
BOOL AppendContextMenu           (mdiChild *,void FAR *,WORD);
BOOL GetMDIClienData             (mdiChild *,void FAR *,WORD);
BOOL SetToolRefHandleExplizit    (mdiChild *,void FAR *,WORD);
BOOL AddStringToBlob             (mdiChild *c,LPVOID param,WORD mode);
BOOL AddVoidDataToBlob           (mdiChild *c,LPVOID param,WORD mode);
BOOL GenerateScriptFromBlob      (mdiChild *c,LPVOID param,WORD mode);
BOOL DelBlob                     (mdiChild *c,LPVOID param,WORD mode);
BOOL UseDialogDocumentFormBlob   (mdiChild *c,LPVOID param,WORD mode);
BOOL BlobToFile                  (mdiChild *c,LPVOID param,WORD mode);
BOOL SetModifyFlag               (mdiChild *c,LPVOID param,WORD mode);
BOOL CallWithSignature           (mdiChild *c,LPVOID param,WORD mode);
BOOL CreatePaintDocumentFromBlob (mdiChild *,void FAR *,WORD);
BOOL CreatePrintDocumentFromBlob (mdiChild *,void FAR *,WORD);
BOOL GetObjLen                   (mdiChild *c,LPVOID param,WORD mode);
BOOL AddParseFunction            (mdiChild *c,LPVOID param,WORD mode);
BOOL StartParse                  (mdiChild *c,LPVOID param,WORD mode);
BOOL DeleteActivationPens        (mdiChild *c,LPVOID param,WORD mode);
BOOL SetMapFont                  (mdiChild *c,LPVOID param,WORD mode);
BOOL SetFlapHeight               (mdiChild *c,LPVOID param,WORD mode);
BOOL SetMapOffset                (mdiChild *c,LPVOID param,WORD mode);
BOOL bToolSelectionInString      (mdiChild *c,LPVOID param,WORD mode);
BOOL TakeModifyFrom              (mdiChild *c,LPVOID param,WORD mode);
BOOL DefTrcGrid                  (mdiChild *c,LPVOID param,WORD mode);
BOOL BlobFromFile                (mdiChild *c,LPVOID param,WORD mode);
BOOL AddParseConversion          (mdiChild *c,LPVOID param,WORD mode);
BOOL WindowScroll                (mdiChild *c,LPVOID param,WORD mode);
BOOL MultiComboSet               (mdiChild *c,LPVOID param,WORD mode);
BOOL FrmGetImgInfo               (mdiChild *c,LPVOID param,WORD mode);
BOOL FrmLoadDIB                  (mdiChild *c,LPVOID param,WORD mode);
BOOL FrmSaveDIB                  (mdiChild *c,LPVOID param,WORD mode);
BOOL CopyBlob                    (mdiChild *c,LPVOID param,WORD mode);
BOOL GetParentInstance           (mdiChild *c,LPVOID param,WORD mode);
BOOL CloseAllFiles               (mdiChild *,void FAR *,WORD);
BOOL NoManipulate                (mdiChild *,void FAR *,WORD);
BOOL DDE_SetTimeOut              (mdiChild *,void FAR *,WORD);
BOOL TwipsToDlg                  (mdiChild *c,LPVOID param,WORD mode);
BOOL CreateOleObjectFromFile     (mdiChild *,void FAR *,WORD);
BOOL RunOleObjectFromBlob        (mdiChild *,void FAR *,WORD);
BOOL PrintOleObjectFromBlob        (mdiChild *,void FAR *,WORD);
BOOL CreateCBDesc                (mdiChild *,void FAR *,WORD);
BOOL DefineBitArray              (mdiChild *,void FAR *,WORD);
BOOL SetBit                      (mdiChild *,void FAR *,WORD);
BOOL IsBitSet                    (mdiChild *,void FAR *,WORD);
BOOL BitAND                      (mdiChild *,void FAR *,WORD);
BOOL BitNOT                      (mdiChild *,void FAR *,WORD);
BOOL ShowFormComboInnerList   (mdiChild *,void FAR *,WORD);
BOOL ShowToolComboInnerList   (mdiChild *,void FAR *,WORD);
BOOL AppendFrmContextMenu        (mdiChild *,void FAR *,WORD);
BOOL FrmFreeDIB                  (mdiChild *c,LPVOID param,WORD mode);
BOOL CRC32                       (mdiChild *c,LPVOID param,WORD mode);
BOOL Encrypt32                   (mdiChild *c,LPVOID param,WORD mode);
BOOL AddDictNode                 (mdiChild *c,LPVOID param,WORD mode);
BOOL GetFirstDictNode            (mdiChild *c,LPVOID param,WORD mode);
BOOL GetNextDictNode             (mdiChild *c,LPVOID param,WORD mode);
BOOL SetContextFunction          (mdiChild *c,LPVOID param,WORD mode);
BOOL MakeTimeStamp               (mdiChild *c,LPVOID param,WORD mode);
BOOL TextFromStrArray            (mdiChild *c,LPVOID param,WORD mode);
BOOL ReallyExtractPath           (mdiChild *c,LPVOID param,WORD mode);
BOOL uPtInCont                   (mdiChild *c,LPVOID param,WORD mode);
BOOL DataFromPointer             (mdiChild *c,LPVOID param,WORD mode);
BOOL GetMouseObject              (mdiChild *c,LPVOID param,WORD mode);
BOOL OpenCommPort                (mdiChild *c,LPVOID param,WORD mode);
BOOL CloseCommPort               (mdiChild *c,LPVOID param,WORD mode);
BOOL FlushCommPort               (mdiChild *c,LPVOID param,WORD mode);
BOOL WriteStrCommPort            (mdiChild *c,LPVOID param,WORD mode);
BOOL ReadStrCommPort             (mdiChild *c,LPVOID param,WORD mode);
BOOL CommBytesReceived           (mdiChild *c,LPVOID param,WORD mode);
BOOL SetListColor                (mdiChild *c,LPVOID param,WORD mode);
BOOL GetSysColor                 (mdiChild *c,LPVOID param,WORD mode);
BOOL SetFrameType                (mdiChild *c,LPVOID param,WORD mode);
BOOL DocumentToPrinterFromBlob   (mdiChild *,void FAR *,WORD);
BOOL DIBFromClipboard            (mdiChild *,void FAR *,WORD);
BOOL SetWindowPosition           (mdiChild *,void FAR *,WORD);
BOOL MCICommand                  (mdiChild *,void FAR *,WORD);
BOOL StartParameter              (mdiChild *,void FAR *,WORD);
BOOL InterpreteDouble            (mdiChild *,void FAR *,WORD);
BOOL FrmGetImgRatio              (mdiChild *,void FAR *,WORD);
BOOL PressedChar                 (mdiChild *,void FAR *,WORD);
BOOL Trc_DefEllipse              (mdiChild *,void FAR *,WORD);
BOOL SetListClickProc            (mdiChild *,void FAR *,WORD);
BOOL ProfileOverrideBuffer       (mdiChild *,void FAR *,WORD);
BOOL PushToBlob                  (mdiChild *,void FAR *,WORD);
BOOL Trc_DefContain              (mdiChild *,void FAR *,WORD);
BOOL BlobAufbereiten             (mdiChild *,void FAR *,WORD);
BOOL DatenVomBlob                (mdiChild *,void FAR *,WORD);
BOOL Trc_DefContain2             (mdiChild *,void FAR *,WORD);
BOOL RemoveFromBlob              (mdiChild *,void FAR *,WORD);
BOOL ErsteDatenVomBlob           (mdiChild *,void FAR *,WORD);
BOOL WeitereDatenVomBlob         (mdiChild *,void FAR *,WORD);
BOOL StatFunc                    (mdiChild *,void FAR *,WORD);
BOOL SetNoAutoScroll             (mdiChild *,void FAR *,WORD);
BOOL GetLastCommError            (mdiChild *,void FAR *,WORD);
BOOL TestDllProc                 (mdiChild *,void FAR *,WORD);
BOOL GetResFactor                (mdiChild *c,LPVOID param,WORD mode);
BOOL CommSignalStatus            (mdiChild *c,LPVOID param,WORD mode);
BOOL CommEscape                  (mdiChild *c,LPVOID param,WORD mode);
BOOL DenyNormalCursor            (mdiChild *c,LPVOID param,WORD mode);
BOOL GetScriptEntry              (mdiChild *c,LPVOID param,WORD mode);
BOOL lSetUpCallBack              (mdiChild *c,LPVOID param,WORD mode);
BOOL SetOLEDocVar                (mdiChild *c,LPVOID param,WORD mode);
BOOL GetOLEDocVar                (mdiChild *c,LPVOID param,WORD mode);
BOOL OLEPrint                    (mdiChild *c,LPVOID param,WORD mode);
BOOL GetTableID                  (mdiChild *c,LPVOID param,WORD mode);
BOOL GetMyIUnknown               (mdiChild *c,LPVOID param,WORD mode);
BOOL GetOLEDocProp               (mdiChild *c,LPVOID param,WORD mode);
BOOL OLEUpdateFields             (mdiChild *c,LPVOID param,WORD mode);
BOOL OLERestrictInput            (mdiChild *c,LPVOID param,WORD mode);
BOOL OLESetHostName              (mdiChild *c,LPVOID param,WORD mode);
BOOL MakeDateTime                (mdiChild *c,LPVOID param,WORD mode);
BOOL GetDateFromDateTime         (mdiChild *c,LPVOID param,WORD mode);
BOOL GetTimeFromDateTime         (mdiChild *c,LPVOID param,WORD mode);
BOOL bCmpDateTime                (mdiChild *c,LPVOID param,WORD mode);
BOOL SetPrinterCaption           (mdiChild *c,LPVOID param,WORD mode);
BOOL CreateMemoryFile            (mdiChild *c,LPVOID param,WORD mode);
BOOL ReadMemoryFile              (mdiChild *c,LPVOID param,WORD mode);
BOOL WriteMemoryFile             (mdiChild *c,LPVOID param,WORD mode);
BOOL PostWinMessage              (mdiChild *c,LPVOID param,WORD mode);
BOOL HaltQueue                   (mdiChild *c,LPVOID param,WORD mode);
BOOL ResumeQueue                 (mdiChild *c,LPVOID param,WORD mode);
BOOL CallDllProcDynamic          (mdiChild *c,LPVOID param,WORD mode);
BOOL PushDataMit                 (mdiChild *,void FAR *,WORD);
BOOL NetListen                   (mdiChild *c,LPVOID param,WORD mode);
BOOL NetAccept                   (mdiChild *c,LPVOID param,WORD mode);
BOOL NetConnect                  (mdiChild *c,LPVOID param,WORD mode);
BOOL NetReceive                  (mdiChild *c,LPVOID param,WORD mode);
BOOL NetSend                     (mdiChild *c,LPVOID param,WORD mode);
BOOL NetSendBlob                 (mdiChild *c,LPVOID param,WORD mode);
BOOL NetWorkAddressStrToBin      (mdiChild *c,LPVOID param,WORD mode);
BOOL NetWorkAddressBinToStr      (mdiChild *c,LPVOID param,WORD mode);
BOOL NetStatus                   (mdiChild *c,LPVOID param,WORD mode);
BOOL NetError                    (mdiChild *c,LPVOID param,WORD mode);
BOOL ColorObjSelection           (mdiChild *c,LPVOID param,WORD mode);
BOOL ColorToolSelection          (mdiChild *c,LPVOID param,WORD mode);
BOOL GetObjColor                 (mdiChild *c,LPVOID param,WORD mode);
BOOL GetToolColor                (mdiChild *c,LPVOID param,WORD mode);
BOOL ExchangeEscape              (mdiChild *c,LPVOID param,WORD mode);
BOOL ReexchangeEscape            (mdiChild *c,LPVOID param,WORD mode);
BOOL DataWithName                (mdiChild *c,LPVOID param,WORD mode);
BOOL GetSystemPath               (mdiChild *c,LPVOID param,WORD mode);
BOOL SetUserName                 (mdiChild *c,LPVOID param,WORD mode);
BOOL WindowsEvent                (mdiChild *c,LPVOID param,WORD mode);
BOOL SetErrorRef                 (mdiChild *c,LPVOID param,WORD mode);
BOOL CreateDir                   (mdiChild *c,LPVOID param,WORD mode);
BOOL Wait                        (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowFormMultiComboInnerList (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowToolMultiComboInnerList (mdiChild *c,LPVOID param,WORD mode);
BOOL DBCall_FormComboObjList     (mdiChild *c,LPVOID param,WORD mode);
BOOL DBCall_ToolComboObjList     (mdiChild *c,LPVOID param,WORD mode);
BOOL DBCall_FormMultiComboObjList (mdiChild *c,LPVOID param,WORD mode);
BOOL DBCall_ToolMultiComboObjList (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowFormComboInnerListObjList (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowToolComboInnerObjList   (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowFormMultiComboInnerObjList (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowToolMultiComboInnerObjList (mdiChild *c,LPVOID param,WORD mode);
BOOL RefreshDlgList              (mdiChild *c,LPVOID param,WORD mode);
BOOL DenyDlgClose                (mdiChild *c,LPVOID param,WORD mode);
BOOL SetDlgText                  (mdiChild *c,LPVOID param,WORD mode);
BOOL CheckBuffer                 (mdiChild *c,LPVOID param,WORD mode);
BOOL CloseSpell                  (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellSuggestion             (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellAnagram                (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellWildcard               (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellSetOptions             (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellGetOptions             (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellOpenUserDictionary     (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellAddToUserDictionary    (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellDelFromUserDictionary  (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellCloseUserDictionary    (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellAddToRAMCacheList      (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellDelFromRAMCacheList    (mdiChild *c,LPVOID param,WORD mode);
BOOL SpellClearRAMCacheList      (mdiChild *c,LPVOID param,WORD mode);
BOOL HtmlHelpInit                (mdiChild *c,LPVOID param,WORD mode);
BOOL CallHtmlHelp                (mdiChild *c,LPVOID param,WORD mode);
BOOL usqrt                       (mdiChild *c,LPVOID param,WORD mode);
BOOL SetDDSCapture               (mdiChild *c,LPVOID param,WORD mode);
BOOL InstallProcedure            (mdiChild *c,LPVOID param,WORD mode);
BOOL FireProcedure               (mdiChild *c,LPVOID param,WORD mode);
BOOL SetDocVeryBestWith          (mdiChild *c,LPVOID param,WORD mode);
BOOL TagesAuslastung             (mdiChild *c,LPVOID param,WORD mode);
BOOL RunAutomacro                (mdiChild *c,LPVOID param,WORD mode);
BOOL GetFrmFieldText             (mdiChild *c,LPVOID param,WORD mode);
BOOL SetSelection                (mdiChild *c,LPVOID param,WORD mode);
BOOL ChangeSelection             (mdiChild *c,LPVOID param,WORD mode);
BOOL WaitForSingleObject         (mdiChild *c,LPVOID param,WORD mode);
BOOL CreateAllTables             (mdiChild *c,LPVOID param,WORD mode);
BOOL SetFeierTag                 (mdiChild *c,LPVOID param,WORD mode);
BOOL ClearFeierTage              (mdiChild *c,LPVOID param,WORD mode);
BOOL IsInTransactionProc         (mdiChild *c,LPVOID param,WORD mode);
BOOL ShowPopupMenu               (mdiChild *c,LPVOID param,WORD mode);
BOOL CloseApplicationWord        (mdiChild *c,LPVOID param,WORD mode);
BOOL SaveWordObjectAs            (mdiChild *c,LPVOID param,WORD mode);
BOOL AddBlobToBlob               (mdiChild *c,LPVOID param,WORD mode);
BOOL ExtractDataFromBlob         (mdiChild *c,LPVOID param,WORD mode);
BOOL ExtractBlob                 (mdiChild *c,LPVOID param,WORD mode);
BOOL bBlobEqual                  (mdiChild *c,LPVOID param,WORD mode);
BOOL GetHelpPrefix               (mdiChild *c,LPVOID param,WORD mode);
BOOL SetObjInfo                  (mdiChild *c,LPVOID param,WORD mode);
BOOL GetObjInfo                  (mdiChild *c,LPVOID param,WORD mode);
BOOL GetObjContext               (mdiChild *c,LPVOID param,WORD mode);
BOOL GetLastErrorText            (mdiChild *c,LPVOID param,WORD mode);
BOOL BlockCopy                   (mdiChild *c,LPVOID param,WORD mode);
BOOL ForcePageBreak              (mdiChild *c,LPVOID param,WORD mode);
BOOL MoveBlobData                (mdiChild *c,LPVOID param,WORD mode);
BOOL GetClientWindowHandle       (mdiChild *c,LPVOID param,WORD mode);
BOOL ClientExtWindow 		         (mdiChild *c,LPVOID param,WORD mode);
BOOL lInnerUpdate                (mdiChild *c,LPVOID param,WORD mode);
BOOL SetFocusToSubDoc            (mdiChild *c,LPVOID param,WORD mode);
BOOL MultiComboReset             (mdiChild *c,LPVOID param,WORD mode);
BOOL Random                      (mdiChild *c,LPVOID param,WORD mode);
BOOL DBCall_Parse                (mdiChild *c,LPVOID param,WORD mode);
BOOL Ltx                         (mdiChild *c,LPVOID param,WORD mode);
BOOL SetNetWorkSubAddressID      (mdiChild *c,LPVOID param,WORD mode);
BOOL DirSelector_Box             (mdiChild *c,LPVOID param,WORD mode);
BOOL ChooseColorDialog           (mdiChild *c,LPVOID param,WORD mode);
BOOL SetDBLogState               (mdiChild *c,LPVOID param,WORD mode);
BOOL Code128bc                   (mdiChild *c,LPVOID param,WORD mode);
BOOL Jmethod                     (mdiChild *c,LPVOID param,WORD mode);
BOOL Jstaticmethod               (mdiChild *c,LPVOID param,WORD mode);
BOOL Jnew                        (mdiChild *c,LPVOID param,WORD mode);
BOOL Jdelete                     (mdiChild *c,LPVOID param,WORD mode);
BOOL Jnewstring                  (mdiChild *c,LPVOID param,WORD mode);
BOOL Jstartvm                    (mdiChild *c,LPVOID param,WORD mode);
BOOL Jdestroyvm                  (mdiChild *c,LPVOID param,WORD mode);
BOOL Jmethodparallel             (mdiChild *c,LPVOID param,WORD mode);
BOOL Jcatchexception             (mdiChild *c,LPVOID param,WORD mode);
BOOL Jlogexception               (mdiChild *c,LPVOID param,WORD mode);
BOOL Jinstanceof                 (mdiChild *c,LPVOID param,WORD mode);
BOOL Jmethodexists               (mdiChild *c,LPVOID param,WORD mode);
BOOL Jstaticmethodexists         (mdiChild *c,LPVOID param,WORD mode);
BOOL Jgetarraylength             (mdiChild *c,LPVOID param,WORD mode);
BOOL Jgetobjarrayelement         (mdiChild *c,LPVOID param,WORD mode);
BOOL Jsetreplacemode             (mdiChild *c,LPVOID param,WORD mode);
BOOL JBmethodexists              (mdiChild *c,LPVOID param,WORD mode);
BOOL JBstaticmethodexists        (mdiChild *c,LPVOID param,WORD mode);
BOOL JavaReferencesInc           (mdiChild *c,LPVOID param,WORD mode);

#ifdef DDSFUNC_MAIN
// Funktionsarray
DDSFUNC ddsfunc[] = {
  /*   32 */ GenericTool       ,       // ShowObjectList
  /*   33 */ GenericTool       ,       // 17 XYFromRect
  /*   34 */ GenericTool       ,       // 18 BmpTextPushButton
  /*   35 */ lCallDefSel       ,       // 19 lCallDefSel
  /*   36 */ lSetFocusFunction ,       // 20 lSetSelCallBack  (Txt_String)
  /*   37 */ GetRecPrimKey     ,
  /*   38 */ AddIconEleEx      ,       // 22
  /*   39 */ bDateGreater      ,       // 23
  /*   40 */ DefFrmTable       ,       // 24
  /*   41 */ uSetPoint         ,
  /*   42 */ CatMultiString    ,
  /*   43 */ uTimeNow          ,
  /*   44 */ uDiffTime         ,
  /*   45 */ DefFrmTime        ,
  /*   46 */ GenericTool       ,       // ShowMPObjectList
  /*   47 */ ActivateMapElem   ,       // NumAna_Val        ,
  /*   48 */ uSetVal           ,
  /*   49 */ uPtDist           ,
  /*   50 */ GenericTool       ,       // ToolTime
  /*   51 */ GenericTool       ,       // ToolShortInt
  /*   52 */ GenericTool       ,       // UpDown
  /*   53 */ bButtonPressed    ,
  /*   54 */ uBringToHor       ,
  /*   55 */ uScPt             ,
  /*   56 */ uScCont           ,
  /*   57 */ lSetListMode      ,       // uBringToOverlap   ,
  /*   58 */ GenericTool       ,       // ShowColumnList
  /*   59 */ uSmoothCont       ,
  /*   60 */ bPointExist       ,
  /*   61 */ uCalcRelPt        ,
  /*   62 */ uLinInt           ,
  /*   63 */ uCombineCont      ,
  /*   64 */ uPerpPt           ,
  /*   65 */ uParPt            ,
  /*   66 */ PaintFullHeader   ,       // Trc_Mark          ,
  /*   67 */ uCntCro           ,
  /*   68 */ uCntMax           ,
  /*   69 */ uCntMaxAng        ,
  /*   70 */ uCntNea           ,
  /*   71 */ uPtPro            ,
  /*   72 */ uExtSmoothCont    ,
  /*   73 */ uAddFixVect       ,
  /*   74 */ uMaxPt            ,
  /*   75 */ PaintFullBottom   ,       // Frm_Date          ,
  /*   76 */ PaintStdBottom    ,       // Frm_relDate       ,
  /*   77 */ uDiffYears        ,
  /*   78 */ uMulVal           ,
  /*   79 */ uAddVal           ,
  /*   80 */ uDivVal           ,
  /*   81 */ uSubVal           ,
  /*   82 */ uPtNDist          ,
  /*   83 */ uPtPDist          ,
  /*   84 */ uDiffAng          ,
  /*   85 */ uValRange         ,
  /*   86 */ bValGreater       ,
  /*   87 */ uAddTime          ,       // NumAna_SetSize    ,
  /*   88 */ uSetTime          ,       // Trc_mPattern      ,
  /*   89 */ ScaleDateTime     ,       // uShowTextButton   ,
  /*   90 */ uSmoothCycCont    ,
  /*   91 */ GetScaleDateTime  ,
  /*   92 */ uAddRelTime       ,
  /*   93 */ LoadInnerList     ,
  /*   94 */ CallProcOnMode    ,
  /*   95 */ uLinTrans         ,
  /*   96 */ SetOutContext     ,
  /*   97 */ PushToPackList    ,
  /*   98 */ SetToolRefHandle  ,
  /*   99 */ ActivateInInnerList ,
  /*  100 */ uSetFlag          ,
  /*  101 */ DeActivateInInnerList ,
  /*  102 */ Trc_DefFilledCont ,
  /*  103 */ RestoreZoom       ,
  /*  104 */ ActivateZoom      ,
  /*  105 */ SetContrast       ,
  /*  106 */ RepeatedCall      ,
  /*  107 */ ClearSemaphore    ,
  /*  108 */ SetSemaphore      ,
  /*  109 */ TestSemaphore     ,
  /*  110 */ BeginTransaction  ,
  /*  111 */ uDevInd           ,
  /*  112 */ uTrcDevInd        ,
  /*  113 */ EndTransaction    ,
  /*  114 */ AbortTransaction  ,
  /*  115 */ CallOptScript     ,
  /*  116 */ SetObjectColor    ,
  /*  117 */ bWordIndGreater   ,
  /*  118 */ GetLineCount      ,
  /*  119 */ EmptyInnerList    ,
  /*  120 */ uDivideCont       ,
  /*  121 */ uSymmetrieLine    ,
  /*  122 */ uGet33Arr         ,
  /*  123 */ uGenAgeNorm       ,
  /*  124 */ GenericTool       ,
  /*  125 */ BindInnerListToOuterList ,
  /*  126 */ GetCopy           ,
  /*  127 */ bIsValInNorm      ,
  /*  128 */ IsUpdateDone      ,
  /*  129 */ WaitOnMouseClk    ,
  /*  130 */ lSetDblClkCallBack,
  /*  131 */ bImageExist       ,
  /*  132 */ uGetImgScale      ,
  /*  133 */ uCombineScale     ,
  /*  134 */ uGetNegX          ,
  /*  135 */ uOverlapPoints    ,
  /*  136 */ uLinInterpol      ,
  /*  137 */ uVarCall          ,
  /*  138 */ LockTable         ,
  /*  139 */ UnlockTable       ,
  /*  140 */ AvoidInput        ,
  /*  141 */ CopyFromRecord    ,
  /*  142 */ CopyToRecord      ,
  /*  143 */ uArcInt           ,
  /*  144 */ UseDialogDocumentTellPar ,
  /*  145 */ ChangeUseDialogDocumentPars ,
  /*  146 */ uCalcMiddDev      ,
  /*  147 */ uArcSin           ,
  /*  148 */ CreateUniqueFile  ,
  /*  149 */ OpenFileDirect    ,
  /*  150 */ CloseFile         ,
  /*  151 */ WriteToFile       ,
  /*  152 */ ReadLn            ,
  /*  153 */ ReadBinary        ,
  /*  154 */ WriteLn           ,
  /*  155 */ CopyFileTo        ,
  /*  156 */ ExecProgram       ,
  /*  157 */ uCopyCont         ,
  /*  158 */ uSetLong          ,
  /*  159 */ Trc_DefMark       ,
  /*  160 */ SetStatText       ,
  /*  161 */ Str_Cpy           ,
  /*  162 */ Str_Cat           ,
  /*  163 */ Str_Printf        ,
  /*  164 */ AvoidUpdates      ,
  /*  165 */ Trc_DefCont       ,
  /*  166 */ uGenVect          ,
  /*  167 */ uAddVect          ,
  /*  168 */ Trc_DefPattern    ,
  /*  169 */ Trc_DefmPattern   ,
  /*  170 */ uGetDevString     ,
  /*  171 */ DefFrmField       ,
  /*  172 */ DefFrmDate        ,
  /*  173 */ DefFrmDec         ,
  /*  174 */ DefFrmSLDec       ,
  /*  175 */ DefFrmStrList     ,
  /*  176 */ uFrmShowObject    ,
  /*  177 */ DoWhile           ,
  /*  178 */ DefFrmLine        ,
  /*  179 */ DefFrmImage       ,
  /*  180 */ FrmScanImage      ,
  /*  181 */ Vto_Init          ,
  /*  182 */ Vto_DefRotCent    ,
  /*  183 */ Vto_DefineGroup   ,
  /*  184 */ Trc_DefLine       ,
  /*  185 */ DestroyFile       ,
  /*  186 */ SetFileAttr       ,
  /*  187 */ bStrExist         ,
  /*  188 */ uInvScale         ,
  /*  189 */ uScExplicit       ,
  /*  190 */ uSubVect          ,
  /*  191 */ bScaleExist       ,
  /*  192 */ uScSkipOffset     ,
  /*  193 */ uDateNow          ,
  /*  194 */ DefFrmSozNr       ,
  /*  195 */ uPtExplicit       ,
  /*  196 */ DefFrmDevDec      ,
  /*  197 */ DefFrmRectImage   ,
  /*  198 */ DefCheckBox       ,
  /*  199 */ uAddLong          ,
  /*  200 */ uMaskLong         ,
  /*  201 */ uFindLong         ,
  /*  202 */ uGetLong          ,
  /*  203 */ bDatExist         ,
  /*  204 */ DefFrmStrShortList,
  /*  205 */ uMutualExclude    ,
  /*  206 */ uSetDirKey        ,
  /*  207 */ bLongEqual        ,
  /*  208 */ Trc_DefArc        ,
  /*  209 */ DefSoftEdit       ,
  /*  210 */ SetDocBestWidth   ,
  /*  211 */ DefPattern        ,
  /*  212 */ uGetIndDec        ,
  /*  213 */ UnScaleDateTime   ,
  /*  214 */ VTOSetEmptyCont   ,
  /*  215 */ InstallKeyWord    ,
  /*  216 */ DefFrmTab         ,
  /*  217 */ DefFrmTabField    ,
  /*  218 */ DefTabDecField    ,
  /*  219 */ DefTabShortStrListField,
  /*  220 */ DefTabFlagField   ,
  /*  221 */ CalcTabPos        ,
  /*  222 */ uCntmCro          ,
  /*  223 */ mShowMessageBox   ,
  /*  224 */ DefCutEdit        ,
  /*  225 */ DefCheckField     ,
  /*  226 */ DefTabCheckField  ,
  /*  227 */ SetDigCnf         ,
  /*  228 */ eFindSubStr       ,
  /*  229 */ DoIconEleSelect   ,
  /*  230 */ DefFrmStrDivList  ,
  /*  231 */ bCmpShort         ,
  /*  232 */ uScContPart       ,
  /*  233 */ bContExist        ,
  /*  234 */ DefFrmTabDate     ,
  /*  235 */ bYearGreater      ,
  /*  236 */ DefTabStrListField,
  /*  237 */ uSetDirKeyUpDown  ,
  /*  238 */ uSetDirKeyLeftRight,
  /*  239 */ bCmpLong           ,
  /*  240 */ uEstimateTang      ,
  /*  241 */ DefTabColDec       ,
  /*  242 */ bCmpFloat          ,
  /*  243 */ DefFKurve          ,
  /*  244 */ GetFieldLeftLower  ,
  /*  245 */ GetFieldRightLower ,      // DefFrmBenList      ,
  /*  246 */ uOptimize          ,
  /*  247 */ uContDist          ,
  /*  248 */ bCmpString         ,
  /*  249 */ uExpVal            ,
  /*  250 */ uPowVal            ,
  /*  251 */ uCubSpl            ,
  /*  252 */ DefFrmSlantField   ,
  /*  253 */ uStretchCont       ,
  /*  254 */ DefFrmSlantDec     ,
  /*  255 */ DefFrmSlantSLDec   ,
  /*  256 */ uConnectCont       ,
  /*  257 */ bCmpDate           ,
  /*  258 */ bCmpTime           ,
  /*  259 */ uDelData           ,
  /*  260 */ uTurningPoint      ,
  /*  261 */ uMutualExcludeNone ,
  /*  262 */ DefMovePattern     ,
  /*  263 */ DefFrmDefDec       ,
  /*  264 */ DefFrmMultiField   ,
  /*  265 */ ChangeCubSplPt     ,
  /*  266 */ Vto_OnMove         ,
  /*  267 */ Vto_DrawObject     ,
  /*  268 */ AddSHEnt           ,
  /*  269 */ bFindInd           ,
  /*  270 */ WriteCubSpl        ,
  /*  271 */ uSetMulti          ,
  /*  272 */ uCopyRefs          ,
  /*  273 */ uCalcSoftVect      ,
  /*  274 */ CreateScreen       ,
  /*  275 */ GenericTool        ,      // PushButton
  /*  276 */ GenericTool        ,      // CheckButton
  /*  277 */ GenericTool        ,      // TextPushButton
  /*  278 */ GenericTool        ,      // TextCheckButton
  /*  279 */ GenericTool        ,      // TextRadioButton
  /*  280 */ GenericTool        ,      // ComboButton
  /*  281 */ GenericTool        ,      // ToolEdit
  /*  282 */ GenericTool        ,      // ToolZoom
  /*  283 */ GenericTool        ,      // ToolPage
  /*  284 */ GenericTool        ,      // ToolDate
  /*  285 */ GenericTool        ,      // ToolFloat
  /*  286 */ CallProc           ,
  /*  287 */ ActivateScreen     ,
  /*  288 */ SetScale           ,
  /*  289 */ StoreData          ,
  /*  290 */ SetDocSide         ,
  /*  291 */ SetDocBestSize     ,
  /*  292 */ RemoveFormatInfo   ,      // ModifyRecall       ,
  /*  293 */ GetPascalString    ,      // GetRecallData
  /*  294 */ GetProfileString   ,
  /*  295 */ DefTrcImage        ,
  /*  296 */ RenameFile         ,
  /*  297 */ WriteToIniFile     ,
  /*  298 */ GenericTool        ,      // GroupBox
  /*  299 */ GenericTool        ,      // StaticTool
  /*  300 */ GenericTool        ,      // lShowList
  /*  301 */ WinExit            ,
  /*  302 */ GetConnNmbr        ,
  /*  303 */ DivideIntoFormatStrings ,
  /*  304 */ AllowAdditionalSel ,
  /*  305 */ DisableFlapChange  ,
  /*  306 */ DBCall_Get         ,
  /*  307 */ GenericTool        ,      // DBCall_StringList
  /*  308 */ lSelect            ,
  /*  309 */ GenericTool        ,      // StaticBitmap-Tool
  /*  310 */ GenericTool        ,      // 3D Linien
  /*  311 */ GenericTool        ,      // faerbige Linien
  /*  312 */ GenericTool        ,      // Rechteck, welches Aktionen ausfuehrt
  /*  313 */ GenericTool        ,      // DBCall_ColumnList
  /*  314 */ GenericTool        ,      // DBCall_ObjList
  /*  315 */ lPrint             ,
  /*  316 */ LinkElements       ,
  /*  317 */ CreatePaintDocument ,
  /*  318 */ SetIndIndex        ,
  /*  319 */ GenericTool        ,      // DBCall_MPObjList
  /*  320 */ DBCall_Update      ,
  /*  321 */ DBCall_Insert      ,
  /*  322 */ DBCall_Excute      ,
  /*  323 */ LongToFloat        ,
  /*  324 */ ShortToFloat       ,
  /*  325 */ DestroyDocument    ,
  /*  326 */ InitHk             ,
  /*  327 */ FloatToLong        ,
  /*  328 */ FloatToShort       ,
  /*  329 */ LongToShort        ,
  /*  330 */ ShortToLong        ,
  /*  331 */ CallOnUpdate       ,
  /*  332 */ lRefreshList       ,
  /*  333 */ TileDocuments      ,
  /*  334 */ ArrangeDocuments   ,
  /*  335 */ SwitchToNextWindow ,
  /*  336 */ SwitchToPrevWindow ,
  /*  337 */ ExtractDate        ,
  /*  338 */ DestroyAllDocuments,
  /*  339 */ GenericTool        ,      // MapFlap
  /*  340 */ SwitchToNextField  ,
  /*  341 */ SwitchToPrevField  ,
  /*  342 */ ActivateApp        ,
  /*  343 */ Str_Scanf          ,
  /*  344 */ InstallClpObserver ,
  /*  345 */ WriteClpBoard      ,
  /*  346 */ AvoidActivation    ,
  /*  347 */ RemoveObserver     ,
  /*  348 */ TaskExist          ,
  /*  349 */ OnTaskDestroy      ,
  /*  350 */ StartTask          ,
  /*  351 */ WatchCreation      ,
  /*  352 */ lGetSelCount       ,
  /*  353 */ SetDateMover       ,
  /*  354 */ ShowToolList       ,
  /*  355 */ GetTextFrom        ,
  /*  356 */ PrintDocument      ,
  /*  357 */ mNumSize           ,
  /*  358 */ DefmNum            ,
  /*  359 */ GetDataWithCodeData,
  /*  360 */ OnDocumentDestroy  ,
  /*  361 */ IsInJobList        ,
  /*  362 */ IsDocOpen          ,
  /*  363 */ PaddString         ,
  /*  364 */ ExtractString      ,
  /*  365 */ bCompareString     ,
  /*  366 */ BuildDate          ,
  /*  367 */ ExtractTime        ,
  /*  368 */ BuildTime          ,
  /*  369 */ bLongVarEqual      ,
  /*  370 */ uSubInd            ,
  /*  371 */ uSubLong           ,
  /*  372 */ FormatDate         ,
  /*  373 */ FormatTime         ,
  /*  374 */ GetLicense         ,
  /*  375 */ Beeps              ,
  /*  376 */ DBCall_Delete      ,
  /*  377 */ DoHotkeyAction     ,
  /*  378 */ SetCharCallback    ,
  /*  379 */ GenericTool        ,   // ToolPwd
  /*  380 */ PrgExit            ,
  /*  381 */ SetWndFormat       ,
  /*  382 */ GetFormatStrings   ,
  /*  383 */ IsDocOpenName      ,
  /*  384 */ ActivateDoc        ,
  /*  385 */ GetDocFName        ,
  /*  386 */ DefEntParam        ,
  /*  387 */ DefEnterPoint      ,
  /*  388 */ DefEnterCont       ,
  /*  389 */ FrmImportImage     ,
  /*  390 */ GetFieldFormat     ,
  /*  391 */ DBCall_ForSelection ,
  /*  392 */ IniDate            ,
  /*  393 */ FrmStoreImage      ,
  /*  394 */ SetFocusToDoc      ,
  /*  395 */ uAddDays           ,
  /*  396 */ ImgGetOriginal     ,
  /*  397 */ ImgUserFlt         ,
  /*  398 */ ImgBestContrast    ,
  /*  399 */ ImgCrispFlt        ,
  /*  400 */ ImgMedianFlt       ,
  /*  401 */ ImgSobelFlt        ,
  /*  402 */ ImgLocalContrast   ,
  /*  403 */ Vto_SetMode        ,
  /*  404 */ DefProjectPoint    ,
  /*  405 */ Vto_ApplyCut       ,
  /*  406 */ SynchorizeUpdate   ,
  /*  407 */ CloseDocument      ,
  /*  408 */ uGetx              ,
  /*  409 */ uGety              ,
  /*  410 */ SetDocVeryBestSize    ,
  /*  411 */ uClipCont             ,
  /*  412 */ DefClickPattern       ,
  /*  413 */ GetCreationData       ,
  /*  414 */ SetFNrRef             ,
  /*  415 */ SortList              ,
  /*  416 */ GetFullDocumentName   ,
  /*  417 */ PresentData           ,
  /*  418 */ ShowDocMaximized      ,
  /*  419 */ uAddDateTime          ,
  /*  420 */ bDataEqual            ,
  /*  421 */ CallOnDestroy         ,
  /*  422 */ uDiffDateTime         ,
  /*  423 */ DBCall_Copy           ,
  /*  424 */ uAddInd               ,
  /*  425 */ uSetDate              ,
  /*  426 */ GenericTool           ,        // PushCheckButton
  /*  427 */ ToBusy                ,
  /*  428 */ RemoveControlFromLayer,
  /*  429 */ ActivateScreenLayer   ,
  /*  430 */ GenericTool           ,        // TransparentBitmap-Tool
  /*  431 */ GenericTool           ,        // AnimationBitmap-Tool
  /*  432 */ SetFocusToObject      ,
  /*  433 */ bIsInIntervall        ,
  /*  434 */ GetIntervallBorders   ,
  /*  435 */ GenericTool           ,        // unsichtbare Hilfe
  /*  436 */ CallWindowsHelp       ,
  /*  437 */ uAddMonths            ,
  /*  438 */ uAddYears             ,
  /*  439 */ DelDefSel             ,
  /*  440 */ SetWindowDimension    ,
  /*  441 */ CopySameVars          ,
  /*  442 */ SetWindowTitle        ,
  /*  443 */ GetDocInstance        ,
  /*  444 */ DBCall_FormComboList  ,
  /*  445 */ DBCall_ToolComboList  ,
  /*  446 */ GetScriptProperty     ,
  /*  447 */ GetScriptProperty_Int ,
  /*  448 */ GetScriptInfo         ,
  /*  449 */ GetNextScriptInfo     ,
  /*  450 */ GetFirstScriptInfo    ,
  /*  451 */ GetDataWithChild_Code ,
  /*  452 */ BringObjectToTail     ,
  /*  453 */ PackData              ,
  /*  454 */ GetActiveElem         ,
  /*  455 */ SetObjectSide         ,
  /*  456 */ DeleteFile            ,
  /*  457 */ FileSelector_Box      ,
  /*  458 */ DefPrgIcon            ,
  /*  459 */ GetVarSize            ,
  /*  460 */ DefFrmStaticBitmap    ,
  /*  461 */ SetEntryHeight        ,
  /*  462 */ SetEditSize           ,  // lUserListFirst        ,
  /*  463 */ RestoreRecord         ,
  /*  464 */ SaveRecord            ,
  /*  465 */ GetFormatBaseHeight   ,
  /*  466 */ GenericTool           ,         // TOOLTYPE_SHOWTRANSPARENTBITMAP
  /*  467 */ DefTransparentBitmap  ,
  /*  468 */ GenericTool           ,         // TOOLTYPE_BITSELECT
  /*  469 */ InstallSelectMode     ,
  /*  470 */ SetBitSelectMode      ,
  /*  471 */ RemoveCRLF            ,
  /*  472 */ SortList_neg          ,
  /*  473 */ SetNewFileRef         ,
  /*  474 */ OnActivation          ,
  /*  475 */ ShowmNumHelp          ,
  /*  476 */ ShowmNumGauss         ,
  /*  477 */ DefActivationRegion   ,
  /*  478 */ DefNormObj            ,
  /*  479 */ DefNormTab            ,
  /*  480 */ GetNorm               ,
  /*  481 */ ListCharCallBack      ,
  /*  482 */ IsFirstCharAlpha      ,
  /*  483 */ IsFirstCharNumeric    ,
  /*  484 */ RemoveLastChar        ,
  /*  485 */ DefFrmBField          ,
  /*  486 */ GenericTool           ,        // StaticBTool
  /*  487 */ GetCapStr             ,
  /*  488 */ GetDigits             ,
  /*  489 */ CreatePostIt       ,      // CreatePatNr  -> freilassen fuer Gerhold !
  /*  490 */ RemoveSpaces          ,
  /*  491 */ uGetThirdPt           ,
  /*  492 */ uGetNAbstPt           ,
  /*  493 */ uGetRotPt             ,
  /*  494 */ uCalcNewPt            ,
  /*  495 */ GetGrowthVal          ,
  /*  496 */ GetMidPts             ,
  /*  497 */ uSin                  ,
  /*  498 */ uCos                  ,
  /*  499 */ uGetVGrid             ,
  /*  500 */ DefOutVGrid           ,
  /*  501 */ SetMouseScale         ,
  /*  502 */ InitializeData        ,
  /*  503 */ GetListHeight         ,
  /*  504 */ OptimizeHeight        ,
  /*  505 */ ProjectCallBack       ,
  /*  506 */ DocumentToPrinter     ,
  /*  507 */ SetNewPts             ,
  /*  508 */ GrowPt                ,
  /*  509 */ GrowCnt               ,
  /*  510 */ CombineData           ,
  /*  511 */ GetFieldRightUpper    ,
  /*  512 */ uAddYearsDec          ,
  /*  513 */ SetFrmEditSize        ,
  /*  514 */ ExtractData           ,
  /*  515 */ GenericTool           ,   // ColorRect
  /*  516 */ GenericTool           ,      // GetBmpFloat
  /*  517 */ DDE_Initiate          ,      // DelAllPatData         ,
  /*  518 */ GetPrTextHeight       ,
  /*  519 */ DDE_Terminate       ,      // RecallOp              ,
  /*  520 */ CreatePrintDocument   ,      // CreatePrintDocument   ,
  /*  521 */ DDE_Request         ,      // GetRecallType         ,
  /*  522 */ GetPrinterType        ,
  /*  523 */ SetPrinter            ,
  /*  524 */ DDE_Poke            ,      // SetListAbort          ,
  /*  525 */ DDE_Execute         ,      // ClearListAbort        ,
  /*  526 */ GetDefaultPrinterName ,
  /*  527 */ SetCaretToEnd         ,
  /*  528 */ SetEditCaretToEnd     ,
  /*  529 */ ClearQueue            ,
  /*  530 */ Vto_CalcAllRotCents   ,
  /*  531 */ Start_TimeMark        ,
  /*  532 */ DefMoveField          ,
  /*  533 */ DefMoveLine           ,
  /*  534 */ DefHelpLine           ,
  /*  535 */ SetDblClkProc         ,
  /*  536 */ CallExternProc        ,
  /*  537 */ IsHandleValid         ,  //bStrIndGreater
  /*  538 */ GetTwainSources       ,
  /*  539 */ KettenLinienParameter ,
  /*  540 */ GetKettenLinie        ,
  /*  541 */ BestPalette           ,
  /*  542 */ ModifyKettenLinienExt ,
  /*  543 */ SplitCont             ,
  /*  544 */ DDSOle                ,
  /*  545 */ FrmSetImage           ,
  /*  546 */ FrmWriteBMP           ,
  /*  547 */ ExtractPath           ,
  /*  548 */ FrmGetPixPerMeter     ,
  /*  549 */ FrmSetPixPerMeter     ,
  /*  550 */ FrmGetImgWidth        ,
  /*  551 */ FrmDrawContDirect     ,
  /*  552 */ uGetImgPhysScale      ,
  /*  553 */ CreateEdgeTable       ,
  /*  554 */ FillInEdges           ,
  /*  555 */ FrmMorphImage         ,
  /*  556 */ Trc_DefRectangle      ,
  /*  557 */ MakeCont              ,
  /*  558 */ uMultiDivideCont      ,
  /*  559 */ SetIndElement         ,
  /*  560 */ PrintDocumentEx       ,
  /*  561 */ MakeContFromDec       ,
  /*  562 */ FrmGetImageScaleFact  ,
  /*  563 */ SetEditOverwrite      ,
  /*  564 */ FrmGetImageFileName   ,
  /*  565 */ UseIntern             ,
  /*  566 */ Use                   ,
  /*  567 */ GenericTool           ,     // lShowPermList
  /*  568 */ GenericTool           ,     // lShowStringList
  /*  569 */ Out                   ,
  /*  570 */ InOut                 ,
  /*  571 */ NewRec                ,
  /*  572 */ DBCall_FormMultiComboList , // ShowDDSList           ,
  /*  573 */ SetObjCallBack        ,
  /*  574 */ CreateDialogDocument  ,
  /*  575 */ DBCall_ToolMultiComboList  , // ShowToolDDSList       ,
  /*  576 */ lSetSelCallBack       ,
  /*  577 */ lChangeSelection      ,
  /*  578 */ CallOverSelection     ,
  /*  579 */ Do                    ,
  /*  580 */ GetNetWorkAddress     ,
  /*  581 */ PaintStdHeader        ,
  /*  582 */ EndCreateMappe        ,
  /*  583 */ AddMappElem           ,
  /*  584 */ StartCreateMappe      ,
  /*  585 */ CreateMapScreen       ,
  /*  586 */ SetMenuText           ,
  /*  587 */ AddMenuCommand        ,
  /*  588 */ SetButtons            ,
  /*  589 */ UseDialogDocument     ,
  /*  590 */ GetRecordPtr          ,
  /*  591 */ ReUseRecord           ,
  /*  592 */ LoadInternList        ,
  /*  593 */ MoveToolGroup         ,
  /*  594 */ SetToolExtension      ,
  /*  595 */ SetPrgCaption         ,
  /*  596 */ GenericTool           ,     // ExternDocument
  /*  597 */ OnSizeChanged         ,
  /*  598 */ SetDelayedUpdate      ,
  /*  599 */ SetDestruktor         ,
  /*  600 */ CallForSelected       ,
  /*  601 */ LoadList              ,
  /*  602 */ PackList              ,
  /*  603 */ lSetSelChangeCallback ,
  /*  604 */ lSetMaxSelCount       ,
  /*  605 */ CopyBlob              ,
  /*  606 */ CreateInnerList       ,
  /*  607 */ AddRecToInnerList     ,
  /*  608 */ bIsSelected           ,
  /*  609 */ CallOverInnerList     ,
  /*  610 */ RemoveRecFromInnerList,
  /*  611 */ CallInInnerListFor    ,
  /*  612 */ KisInit               ,
  /*  613 */ KisExit               ,
  /*  614 */ KisSelectionOpen      ,
  /*  615 */ KisSelectionClose     ,
  /*  616 */ KisRecordRead         ,
  /*  617 */ KisRecordWrite        ,
  /*  618 */ KisRecordCreate       ,
  /*  619 */ KisRecordFree         ,
  /*  620 */ KisTableOpen          ,
  /*  621 */ KisTableClose         ,
  /*  622 */ KisDataGet            ,
  /*  623 */ KisDataSet            ,
  /*  624 */ In_Str                ,
  /*  625 */ Mid_Str               ,
  /*  626 */ Str_Len               ,
  /*  627 */ DDE_GetLastError      ,
  /*  628 */ KisConvBcdToMac       ,
  /*  629 */ KisConvMacToBcd       ,
  /*  630 */ InterpreteHdString    ,
  /*  631 */ ActivateObject        ,
  /*  632 */ ConnectToCheckBox     ,
  /*  633 */ GetScriptParameter    ,
  /*  634 */ Trc_DefRectImage      ,
  /*  635 */ DefMoveRect           ,
  /*  636 */ DefMoveRectImage      ,
  /*  637 */ GenericTool           ,
  /*  638 */ GenericTool           ,
  /*  639 */ uMulInd               ,
  /*  640 */ uDivInd               ,
  /*  641 */ uMulLong              ,
  /*  642 */ uDivLong              ,
  /*  643 */ DefFrmShort           ,
  /*  644 */ DefFrmLong            ,
  /*  645 */ DefFrmMoney           ,
  /*  646 */ IstFeierTag           ,
  /*  647 */ SetToolPalette        ,
  /*  648 */ GenericTool           ,
  /*  649 */ GenericTool           ,
  /*  650 */ BitEditMode           ,
  /*  651 */ GenericTool           ,
  /*  652 */ PresentBitmap         ,
  /*  653 */ GetNextFlagInd        ,
  /*  654 */ SetSetFocusProc       ,
  /*  655 */ BitCount              ,
  /*  656 */ bVektorInProd         ,
  /*  657 */ UnionVektor           ,
  /*  658 */ GenerateVector        ,
  /*  659 */ SetFilterProc         ,
  /*  660 */ GenericTool           ,    /* MergeText */
  /*  661 */ PresentText           ,
  /*  662 */ RemoveChar            ,
  /*  663 */ ExpandBinary          ,
  /*  664 */ GetBaseUnit           ,
  /*  665 */ DefMultiDim           ,
  /*  666 */ WriteMultiDim         ,
  /*  667 */ ReadMultiDim          ,
  /*  668 */ LoadMultiDim          ,
  /*  669 */ UpdateScreenImmediate ,
  /*  670 */ GenericTool           ,    /* TextPushCheckButton */
  /*  671 */ GetVersionInfo        ,
  /*  672 */ SetFieldMode          ,
  /*  673 */ SetMapExtent          ,
  /*  674 */ SetDocumentTitle      ,
  /*  675 */ SetEditMode           ,
  /*  676 */ GetFieldModify        ,
  /*  677 */ SetFieldModify        ,
  /*  678 */ SetOnActivate         ,
  /*  679 */ SetOnDeactivate       ,
  /*  680 */ SetObjModify          ,
  /*  681 */ GetObjModify          ,
  /*  682 */ SetEditFormatMaps     ,
  /*  683 */ SetObjFormatMaps      ,
  /*  684 */ StrRemoveFormat       ,
  /*  685 */ OpenPrinterDirect     ,
  /*  686 */ PrintDirect           ,
  /*  687 */ ClosePrinterDirect    ,
  /*  688 */ CRtoCRLF              ,
  /*  689 */ bVektorTeilmenge      ,
  /*  690 */ IntersectionVektor    ,
  /*  691 */ GetDBHandler          ,
  /*  692 */ CreateFormTool        ,
  /*  693 */ FormToolPictureButton ,
  /*  694 */ FormToolTextButton    ,
  /*  695 */ SetToolObjectColor    ,
  /*  696 */ GetObjLineHeight      ,
  /*  697 */ SetObjLineHeight      ,
  /*  698 */ SetFieldPageBreak     ,
  /*  699 */ GetFieldLeftLowerSeite,
  /*  700 */ CallDllProcP          ,
  /*  701 */ CallDllProcC          ,
  /*  702 */ CallDllBoolProcP      ,
  /*  703 */ CallDllBoolProcC      ,
  /*  704 */ FreeExternDll         ,
  /*  705 */ GenericTool           ,    /* ExternWindow */
  /*  706 */ KisError              ,
  /*  707 */ FileSeek              ,
  /*  708 */ SetLineObjects        ,
  /*  709 */ NonRepeativeObjects   ,
  /*  710 */ SetExtraModify        ,
  /*  711 */ GetToolCoordinates    ,
  /*  712 */ SetDialogPos          ,
  /*  713 */ SplitPath             ,
  /*  714 */ lSetHeaderClkCallBack ,
  /*  715 */ FindFirst             ,
  /*  716 */ FindNext              ,
  /*  717 */ WriteScriptLog        ,
  /*  718 */ ExpandRNT             ,
  /*  719 */ MakeRNT               ,
  /*  720 */ SetRecHash            ,
  /*  721 */ ClearRecHash          ,
  /*  722 */ SetToolModify         ,
  /*  723 */ GetToolModify         ,
  /*  724 */ SetCLINICUMEnvironment,
  /*  725 */ SndDefObj             ,
  /*  726 */ SndClear              ,
  /*  727 */ bSndIsEmpty           ,
  /*  728 */ SndReadWav            ,
  /*  729 */ SndWriteWav           ,
  /*  730 */ SndPlayStart          ,
  /*  731 */ SndPause              ,
  /*  732 */ SndRestart            ,
  /*  733 */ SndPlayStop           ,
  /*  734 */ SndRecStart           ,
  /*  735 */ SndRecStop            ,
  /*  736 */ bSndIsCompatible      ,
  /*  737 */ ShowFormList          ,
  /*  738 */ InitializeVoidData    ,
  /*  739 */ SetArrayData          ,
  /*  740 */ GetArrayData          ,
  /*  741 */ LockDataKey           ,
  /*  742 */ HideScreen            ,
  /*  743 */ ShortToQLong          ,
  /*  744 */ FloatToQLong          ,
  /*  745 */ LongToQLong           ,
  /*  746 */ QLongToShort          ,
  /*  747 */ QLongToFloat          ,
  /*  748 */ QLongToLong           ,
  /*  749 */ uAddQLong             ,
  /*  750 */ uSubQLong             ,
  /*  751 */ uDivQLong             ,
  /*  752 */ uMulQLong             ,
  /*  753 */ DoDBRep               ,
  /*  754 */ DoDBRepIn             ,
  /*  755 */ GetDBToken            ,
  /*  756 */ UnlockDBToken         ,
  /*  757 */ ClearMyTokens         ,
  /*  758 */ MouseMoveProc         ,
  /*  759 */ MarkUpdateError       ,
  /*  760 */ SystemUpdate          ,
  /*  761 */ AlterTable            ,
  /*  762 */ ActivateList          ,
  /*  763 */ MarkVarStatic         ,
  /*  764 */ MarkVarDynamic        ,
  /*  765 */ OnScreenButtonDown    ,
  /*  766 */ CreateTable           ,
  /*  767 */ GetDBPointer          ,
  /*  768 */ ExeIs32Bit            ,
  /*  769 */ AddMessageHook        ,
  /*  770 */ GetFrameWindowHandle  ,
  /*  771 */ bCmpQLong             ,
  /*  772 */ IsKeyPressed          ,
  /*  773 */ SetScrollProc         ,
  /*  774 */ PushData              ,
  /*  775 */ PopData               ,
  /*  776 */ DenyBusy              ,
  /*  777 */ AllowBusy             ,
  /*  778 */ DefineParse           ,
  /*  779 */ CheckExpression       ,
  /*  780 */ CreatePaintDocumentFromBlob ,
  /*  781 */ CreatePrintDocumentFromBlob ,
  /*  782 */ CallWithSignature     ,
  /*  783 */ InsertStrAtCaretObj   ,
  /*  784 */ InsertStrAtCaretTool  ,
  /*  785 */ WordIn_Str            ,
  /*  786 */ DefineRegion          ,
  /*  787 */ RegioFromPoint        ,
  /*  788 */ RegioFromRect         ,
  /*  789 */ BestRegioFromPoint    ,
  /*  790 */ ExchangeStringWithReplaceList ,
  /*  791 */ ReplaceString         ,
  /*  792 */ ModifierToString      ,
  /*  793 */ SetCaretTo            ,
  /*  794 */ GetFieldLeftLowerAnzahlSeite,
  /*  795 */ AppendContextMenu ,
  /*  796 */ GetMDIClienData ,
  /*  797 */ SetToolRefHandleExplizit ,
  /*  798 */ AddStringToBlob ,
  /*  799 */ AddVoidDataToBlob ,
  /*  800 */ GenerateScriptFromBlob ,
  /*  801 */ DelBlob ,
  /*  802 */ UseDialogDocumentFormBlob ,
  /*  803 */ BlobToFile ,
  /*  804 */ GenericTool ,              // ExtBlobDoc
  /*  805 */ SetModifyFlag ,
  /*  806 */ GetObjLen ,
  /*  807 */ AddParseFunction ,
  /*  808 */ StartParse ,
  /*  809 */ DeleteActivationPens,
  /*  810 */ SetMapFont,
  /*  811 */ SetFlapHeight,
  /*  812 */ SetMapOffset,
  /*  813 */ bToolSelectionInString ,
  /*  814 */ TakeModifyFrom ,
  /*  815 */ DefTrcGrid ,
  /*  816 */ BlobFromFile ,
  /*  817 */ AddParseConversion ,
  /*  818 */ WindowScroll ,
  /*  819 */ MultiComboSet ,
  /*  820 */ FrmGetImgInfo ,
  /*  821 */ FrmLoadDIB ,
  /*  822 */ FrmSaveDIB ,
  /*  823 */ GetParentInstance ,
  /*  824 */ CloseAllFiles ,
  /*  825 */ NoManipulate ,
  /*  826 */ DDE_SetTimeOut ,
  /*  827 */ TwipsToDlg ,
  /*  828 */ CreateOleObjectFromFile ,
  /*  829 */ RunOleObjectFromBlob ,
  /*  830 */ CreateCBDesc,
  /*  831 */ DefineBitArray,
  /*  832 */ SetBit,
  /*  833 */ IsBitSet,
  /*  834 */ BitAND,
  /*  835 */ BitNOT,
  /*  836 */ ShowFormComboInnerList,
  /*  837 */ ShowToolComboInnerList,
  /*  838 */ AppendFrmContextMenu,
  /*  839 */ FrmFreeDIB,
  /*  840 */ CRC32,
  /*  841 */ Encrypt32,
  /*  842 */ AddDictNode,
  /*  843 */ GetFirstDictNode,
  /*  844 */ GetNextDictNode,
  /*  845 */ SetContextFunction,
  /*  846 */ MakeTimeStamp,
  /*  847 */ TextFromStrArray,
  /*  848 */ ReallyExtractPath,
  /*  849 */ uPtInCont,
  /*  850 */ DataFromPointer,
  /*  851 */ GetMouseObject,
  /*  852 */ OpenCommPort,
  /*  853 */ CloseCommPort,
  /*  854 */ FlushCommPort,
  /*  855 */ WriteStrCommPort,
  /*  856 */ ReadStrCommPort,
  /*  857 */ CommBytesReceived,
  /*  858 */ SetListColor,
  /*  859 */ GetSysColor,
  /*  860 */ SetFrameType,
  /*  861 */ DocumentToPrinterFromBlob,
  /*  862 */ DIBFromClipboard,
  /*  863 */ SetWindowPosition,
  /*  864 */ MCICommand,
  /*  865 */ StartParameter,
  /*  866 */ InterpreteDouble,
  /*  867 */ FrmGetImgRatio,
  /*  868 */ PressedChar,
  /*  869 */ Trc_DefEllipse,
  /*  870 */ SetListClickProc,
  /*  871 */ ProfileOverrideBuffer,
  /*  872 */ PushToBlob,
  /*  873 */ Trc_DefContain,
  /*  874 */ BlobAufbereiten,
  /*  875 */ DatenVomBlob,
  /*  876 */ Trc_DefContain2,
  /*  877 */ RemoveFromBlob,
  /*  878 */ ErsteDatenVomBlob,
  /*  879 */ WeitereDatenVomBlob,
  /*  880 */ StatFunc,
  /*  881 */ SetNoAutoScroll,
  /*  882 */ GetLastCommError,
  /*  883 */ TestDllProc,
  /*  884 */ GetResFactor,
  /*  885 */ CommSignalStatus,
  /*  886 */ CommEscape,
  /*  887 */ DenyNormalCursor,
  /*  888 */ GetScriptEntry,
  /*  889 */ lSetUpCallBack,
  /*  890 */ SetOLEDocVar,
  /*  891 */ GetOLEDocVar,
  /*  892 */ OLEPrint,
  /*  893 */ GetTableID,
  /*  894 */ GetMyIUnknown,
  /*  895 */ GetOLEDocProp,
  /*  896 */ OLEUpdateFields,
  /*  897 */ OLERestrictInput,
  /*  898 */ OLESetHostName,
  /*  899 */ MakeDateTime,
  /*  900 */ GetDateFromDateTime,
  /*  901 */ GetTimeFromDateTime,
  /*  902 */ bCmpDateTime,
  /*  903 */ SetPrinterCaption,
  /*  904 */ SetStrAtCaretObj,
  /*  905 */ SetStrAtCaretTool,
  /*  906 */ CreateMemoryFile,
  /*  907 */ ReadMemoryFile,
  /*  908 */ WriteMemoryFile,
  /*  909 */ PostWinMessage,
  /*  910 */ HaltQueue,
  /*  911 */ ResumeQueue,
  /*  912 */ CallDllProcDynamic,
  /*  913 */ PushDataMit,
  /*  914 */ NetListen,
  /*  915 */ NetAccept,
  /*  916 */ NetConnect,
  /*  917 */ NetReceive,
  /*  918 */ NetSend,
  /*  919 */ NetWorkAddressStrToBin,
  /*  920 */ NetWorkAddressBinToStr,
  /*  921 */ NetStatus,
  /*  922 */ NetError,
  /*  923 */ ColorObjSelection,
  /*  924 */ ColorToolSelection,
  /*  925 */ GetObjColor,
  /*  926 */ GetToolColor,
  /*  927 */ ExchangeEscape,
  /*  928 */ ReexchangeEscape,
  /*  929 */ DataWithName,
  /*  930 */ GetSystemPath,
  /*  931 */ SetUserName,
  /*  932 */ WindowsEvent,
  /*  933 */ SetErrorRef,
  /*  934 */ CreateDir,
  /*  935 */ Wait,
  /*  936 */ ShowFormMultiComboInnerList,
  /*  937 */ ShowToolMultiComboInnerList,
  /*  938 */ DBCall_FormComboObjList,
  /*  939 */ DBCall_ToolComboObjList,
  /*  940 */ DBCall_FormMultiComboObjList,
  /*  941 */ DBCall_ToolMultiComboObjList,
  /*  942 */ ShowFormComboInnerListObjList,
  /*  943 */ ShowToolComboInnerObjList,
  /*  944 */ ShowFormMultiComboInnerObjList,
  /*  945 */ ShowToolMultiComboInnerObjList,
  /*  946 */ RefreshDlgList,
  /*  947 */ DenyDlgClose,
  /*  948 */ SetDlgText,
  /*  949 */ CheckBuffer,
  /*  950 */ CloseSpell,
  /*  951 */ SpellSuggestion,
  /*  952 */ SpellAnagram,
  /*  953 */ SpellWildcard,
  /*  954 */ SpellSetOptions,
  /*  955 */ SpellGetOptions,
  /*  956 */ SpellOpenUserDictionary,
  /*  957 */ SpellAddToUserDictionary,
  /*  958 */ SpellDelFromUserDictionary,
  /*  959 */ SpellCloseUserDictionary,
  /*  960 */ SpellAddToRAMCacheList,
  /*  961 */ SpellDelFromRAMCacheList,
  /*  962 */ SpellClearRAMCacheList,
  /*  963 */ HtmlHelpInit,
  /*  964 */ CallHtmlHelp,
  /*  965 */ usqrt,
  /*  966 */ SetDDSCapture,
  /*  967 */ InstallProcedure,
  /*  968 */ FireProcedure,
  /*  969 */ SetDocVeryBestWith,
  /*  970 */ TagesAuslastung,
  /*  971 */ RunAutomacro,
  /*  972 */ GetFrmFieldText,
  /*  973 */ SetSelection,
  /*  974 */ ChangeSelection,
  /*  975 */ WaitForSingleObject,
  /*  976 */ CreateAllTables,
  /*  977 */ SetFeierTag,
  /*  978 */ ClearFeierTage,
  /*  979 */ IsInTransactionProc,
  /*  980 */ ShowPopupMenu,
  /*  981 */ PrintOleObjectFromBlob ,
  /*  982 */ CloseApplicationWord,
  /*  983 */ SaveWordObjectAs,
  /*  984 */ AddBlobToBlob,
  /*  985 */ ExtractDataFromBlob,
  /*  986 */ ExtractBlob,
  /*  987 */ NetSendBlob,
  /*  988 */ bBlobEqual,
  /*  989 */ GetHelpPrefix,
  /*  990 */ SetObjInfo,
  /*  991 */ GetObjInfo,
  /*  992 */ GetObjContext,
  /*  993 */ GetLastErrorText,
  /*  994 */ BlockCopy,
  /*  995 */ ForcePageBreak,
  /*  996 */ MoveBlobData,
  /*  997 */ GetClientWindowHandle,
  /*  998 */ ClientExtWindow,
  /*  999 */ lInnerUpdate,
  /* 1000 */ SetFocusToSubDoc,
  /* 1001 */ MultiComboReset,
  /* 1002 */ Random,
  /* 1003 */ DBCall_Parse,
  /* 1004 */ Ltx,
  /* 1005 */ SetNetWorkSubAddressID,
  /* 1006 */ DirSelector_Box,
  /* 1007 */ ChooseColorDialog,
  /* 1008 */ SetDBLogState,
  /* 1009 */ Code128bc,
  /* 1010 */ Jmethod,                          // VAR_OBJ
  /* 1011 */ Jmethod,                          // VAR_STR    ok
  /* 1012 */ Jmethod,                          // VAR_STRARR ok
  /* 1013 */ Jmethod,                          // VAR_LONG   ok
  /* 1014 */ Jmethod,                          // VAR_FLAG   ok
  /* 1015 */ Jmethod,                          // VAR_DEC    ok
  /* 1016 */ Jmethod,                          // VAR_QLONG  ok
  /* 1017 */ Jmethod,                          // VAR_DATE
  /* 1018 */ Jmethod,                          // VAR_DATETIME
  /* 1019 */ Jstaticmethod,                    // VAR_OBJ
  /* 1020 */ Jstaticmethod,                    // VAR_STR
  /* 1021 */ Jstaticmethod,                    // VAR_STRARR
  /* 1022 */ Jstaticmethod,                    // VAR_LONG
  /* 1023 */ Jstaticmethod,                    // VAR_FLAG
  /* 1024 */ Jstaticmethod,                    // VAR_DEC
  /* 1025 */ Jstaticmethod,                    // VAR_QLONG
  /* 1026 */ Jstaticmethod,                    // VAR_DATE
  /* 1027 */ Jstaticmethod,                    // VAR_DATETIME
  /* 1028 */ Jnew,
  /* 1029 */ Jdelete,
  /* 1030 */ Jnewstring,
  /* 1031 */ Jstartvm,
  /* 1032 */ Jdestroyvm,
  /* 1033 */ Jmethodparallel,                  // VAR_OBJ
  /* 1034 */ Jmethodparallel,                  // VAR_STR    ok
  /* 1035 */ Jmethodparallel,                  // VAR_STRARR ok
  /* 1036 */ Jmethodparallel,                  // VAR_LONG   ok
  /* 1037 */ Jmethodparallel,                  // VAR_FLAG   ok
  /* 1038 */ Jmethodparallel,                  // VAR_DEC    ok
  /* 1039 */ Jmethodparallel,                  // VAR_QLONG  ok
  /* 1040 */ Jmethodparallel,                  // VAR_DATE
  /* 1041 */ Jmethodparallel,                  // VAR_DATETIME
  /* 1042 */ Jcatchexception,
  /* 1043 */ Jlogexception,
  /* 1044 */ Jinstanceof,
  /* 1045 */ Jmethodexists,
  /* 1046 */ Jstaticmethodexists,
  /* 1047 */ Jgetarraylength,
  /* 1048 */ Jgetobjarrayelement,
  /* 1049 */ Jsetreplacemode,
  /* 1050 */ JBmethodexists,
  /* 1051 */ JBstaticmethodexists,
  /* 1052 */ JavaReferencesInc
  };

WORD mTypesForCmd [] = {
  /*   32 */ 0xFFFF,                /* GenericTool       */
  /*   33 */ 0xFFFF,                /* GenericTool       */
  /*   34 */ 0xFFFF,                /* GenericTool       */
  /*   35 */ 0xFFFF,                /* lCallDefSel       */
  /*   36 */ 0xFFFF,                /* lSetFocusFunction */
  /*   37 */ 0xFFFF,                /* bWordEqual        */
  /*   38 */ 0xFFFF,                /* AddIconEleEx      */
  /*   39 */ 0xFFFF,                /* bDateGreater      */
  /*   40 */ 0xFFFF,                /* DefFrmTable       */
  /*   41 */ VAR_POINT,             /* uSetPoint         */
  /*   42 */ VAR_STR,               /* CatMultiString    */
  /*   43 */ VAR_TIME,              /* uTimeNow          */
  /*   44 */ VAR_TIME,              /* uDiffTime         */
  /*   45 */ 0xFFFF,                /* DefFrmTime        */
  /*   46 */ 0xFFFF,                /* GenericTool       */
  /*   47 */ 0xFFFF,                /* ActivateMapElem   */
  /*   48 */ VAR_DEC,               /* uSetVal           */
  /*   49 */ VAR_DEC,               /* uPtDist           */
  /*   50 */ 0xFFFF,                /* GenericTool       */
  /*   51 */ 0xFFFF,                /* GenericTool       */
  /*   52 */ 0xFFFF,                /* GenericTool       */
  /*   53 */ 0xFFFF,                /* bButtonPressed    */
  /*   54 */ VAR_SCALE,             /* uBringToHor       */
  /*   55 */ VAR_POINT,             /* uScPt             */
  /*   56 */ VAR_CONT,              /* uScCont           */
  /*   57 */ 0xFFFF,                /* lSetListMode      */
  /*   58 */ 0xFFFF,                /* GenericTool       */
  /*   59 */ VAR_CONT,              /* uSmoothCont       */
  /*   60 */ 0xFFFF,                /* bPointExist       */
  /*   61 */ VAR_POINT,             /* uCalcRelPt        */
  /*   62 */ VAR_POINT,             /* uLinInt           */
  /*   63 */ VAR_CONT,              /* uCombineCont      */
  /*   64 */ VAR_POINT,             /* uPerpPt           */
  /*   65 */ VAR_POINT,             /* uParPt            */
  /*   66 */ 0xFFFF,                /* PaintFullHeader   */
  /*   67 */ VAR_POINT,             /* uCntCro           */
  /*   68 */ VAR_POINT,             /* uCntMax           */
  /*   69 */ VAR_POINT,             /* uCntMaxAng        */
  /*   70 */ VAR_POINT,             /* uCntNea           */
  /*   71 */ VAR_POINT,             /* uPtPro            */
  /*   72 */ VAR_CONT,              /* uExtSmoothCont    */
  /*   73 */ VAR_POINT,             /* uAddFixVect       */
  /*   74 */ VAR_POINT,             /* uMaxPt            */
  /*   75 */ 0xFFFF,                /* PaintFullBottom   */
  /*   76 */ 0xFFFF,                /* PaintStdBottom    */
  /*   77 */ VAR_DEC,               /* uDiffYears        */
  /*   78 */ VAR_DEC,               /* uMulVal           */
  /*   79 */ VAR_DEC,               /* uAddVal           */
  /*   80 */ VAR_DEC,               /* uDivVal           */
  /*   81 */ VAR_DEC,               /* uSubVal           */
  /*   82 */ VAR_DEC,               /* uPtNDist          */
  /*   83 */ VAR_DEC,               /* uPtPDist          */
  /*   84 */ VAR_DEC,               /* uDiffAng          */
  /*   85 */ 0xFFFF,                /* uValRange         */
  /*   86 */ 0xFFFF,                /* bValGreater       */
  /*   87 */ VAR_TIME,              /* uAddTime          */
  /*   88 */ VAR_TIME,              /* uSetTime          */
  /*   89 */ VAR_DEC,               /* ScaleDateTime     */
  /*   90 */ VAR_CONT,              /* uSmoothCycCont    */
  /*   91 */ VAR_OBJ,               /* GetScaleDateTime  */
  /*   92 */ VAR_TIME,              /* uAddRelTime       */
  /*   93 */ 0xFFFF,                /* LoadInnerList     */
  /*   94 */ 0xFFFF,                /* CallProcOnMode    */
  /*   95 */ VAR_SCALE,             /* uLinTrans         */
  /*   96 */ 0xFFFF,                /* SetOutContext     */
  /*   97 */ 0xFFFF,                /* PushToPackList    */
  /*   98 */ 0xFFFF,                /* SetToolRefHandle  */
  /*   99 */ 0xFFFF,                /* ActivateInInnerList */
  /*  100 */ VAR_FLAG,              /* uSetFlag          */
  /*  101 */ 0xFFFF,                /* DeActivateInInnerList */
  /*  102 */ 0xFFFF,                /* Trc_DefFilledCont */
  /*  103 */ 0xFFFF,                /* RestoreZoom       */
  /*  104 */ 0xFFFF,                /* ActivateZoom      */
  /*  105 */ 0xFFFF,                /* SetContrast       */
  /*  106 */ 0xFFFF,                /* RepeatedCall      */
  /*  107 */ 0xFFFF,                /* ClearSemaphore    */
  /*  108 */ 0xFFFF,                /* SetSemaphore      */
  /*  109 */ 0xFFFF,                /* TestSemaphore     */
  /*  110 */ 0xFFFF,                /* BeginTransaction  */
  /*  111 */ 0xFFFF,                /* uDevInd           */
  /*  112 */ 0xFFFF,                /* uTrcDevInd        */
  /*  113 */ 0xFFFF,                /* EndTransaction    */
  /*  114 */ 0xFFFF,                /* AbortTransaction  */
  /*  115 */ 0xFFFF,                /* CallOptScript     */
  /*  116 */ 0xFFFF,                /* SetObjectColor    */
  /*  117 */ 0xFFFF,                /* bWordIndGreater   */
  /*  118 */ 0xFFFF,                /* GetLineCount      */
  /*  119 */ 0xFFFF,                /* EmptyInnerList    */
  /*  120 */ VAR_CONT,              /* uDivideCont       */
  /*  121 */ VAR_POINT,             /* uSymmetrieLine    */
  /*  122 */ 0xFFFF,                /* uGet33Arr         */
  /*  123 */ 0xFFFF,                /* uGenAgeNorm       */
  /*  124 */ 0xFFFF,                /* GenericTool       */
  /*  125 */ 0xFFFF,                /* BindInnerListToOuterList */
  /*  126 */ 0xFFFF,                /* GetCopy           */
  /*  127 */ 0xFFFF,                /* bIsValInNorm      */
  /*  128 */ 0xFFFF,                /* IsUpdateDone      */
  /*  129 */ 0xFFFF,                /* bIsOverlapped     */
  /*  130 */ 0xFFFF,                /* lSetDblClkCallBack*/
  /*  131 */ 0xFFFF,                /* bImageExist       */
  /*  132 */ VAR_SCALE,             /* uGetImgScale      */
  /*  133 */ VAR_SCALE,             /* uCombineScale     */
  /*  134 */ VAR_SCALE,             /* uGetNegX          */
  /*  135 */ 0xFFFF,                /* uOverlapPoints    */
  /*  136 */ VAR_DEC,               /* uLinInterpol      */
  /*  137 */ 0xFFFF,                /* uVarCall          */
  /*  138 */ 0xFFFF,                /* LockTable         */
  /*  139 */ 0xFFFF,                /* UnlockTable       */
  /*  140 */ 0xFFFF,                /* AvoidInput        */
  /*  141 */ 0xFFFF,                /* CopyFromRecord    */
  /*  142 */ 0xFFFF,                /* CopyToRecord      */
  /*  143 */ 0xFFFF,                /* uArcInt           */
  /*  144 */ 0xFFFF,                /* UseDialogDocumentTellPar */
  /*  145 */ 0xFFFF,                /* ChangeUseDialogDocumentPars */
  /*  146 */ 0xFFFF,                /* uCalcMiddDev      */
  /*  147 */ VAR_DEC,               /* uArcSin           */
  /*  148 */ 0xFFFF,                /* CreateUniqueFile  */
  /*  149 */ 0xFFFF,                /* OpenFileDirect    */
  /*  150 */ 0xFFFF,                /* CloseFile         */
  /*  151 */ 0xFFFF,                /* WriteToFile       */
  /*  152 */ 0xFFFF,                /* ReadLn            */
  /*  153 */ 0xFFFF,                /* ReadBinary        */
  /*  154 */ 0xFFFF,                /* WriteLn           */
  /*  155 */ 0xFFFF,                /* CopyFileTo        */
  /*  156 */ 0xFFFF,                /* ExecProgram       */
  /*  157 */ VAR_CONT,              /* uCopyCont         */
  /*  158 */ VAR_LONG,              /* uSetLong          */
  /*  159 */ 0xFFFF,                /* Trc_DefMark       */
  /*  160 */ 0xFFFF,                /* SetStatText       */
  /*  161 */ VAR_STR,               /* Str_Cpy           */
  /*  162 */ VAR_STR,               /* Str_Cat           */
  /*  163 */ VAR_STR,               /* Str_Printf        */
  /*  164 */ 0xFFFF,                /* AvoidUpdates      */
  /*  165 */ 0xFFFF,                /* Trc_DefCont       */
  /*  166 */ 0xFFFF,                /* uGenVect          */
  /*  167 */ 0xFFFF,                /* uAddVect          */
  /*  168 */ 0xFFFF,                /* Trc_DefPattern    */
  /*  169 */ 0xFFFF,                /* Trc_DefmPattern   */
  /*  170 */ 0xFFFF,                /* uGetDevString     */
  /*  171 */ 0xFFFF,                /* DefFrmField       */
  /*  172 */ 0xFFFF,                /* DefFrmDate        */
  /*  173 */ 0xFFFF,                /* DefFrmDec         */
  /*  174 */ 0xFFFF,                /* DefFrmSLDec       */
  /*  175 */ 0xFFFF,                /* DefFrmStrList     */
  /*  176 */ 0xFFFF,                /* uFrmShowObject    */
  /*  177 */ 0xFFFF,                /* DoWhile           */
  /*  178 */ 0xFFFF,                /* DefFrmLine        */
  /*  179 */ 0xFFFF,                /* DefFrmImage       */
  /*  180 */ 0xFFFF,                /* FrmScanImage      */
  /*  181 */ 0xFFFF,                /* Vto_Init          */
  /*  182 */ 0xFFFF,                /* Vto_DefRotCent    */
  /*  183 */ 0xFFFF,                /* Vto_DefineGroup   */
  /*  184 */ 0xFFFF,                /* Trc_DefLine       */
  /*  185 */ 0xFFFF,                /* DestroyFile       */
  /*  186 */ 0xFFFF,                /* SetFileAttr       */
  /*  187 */ 0xFFFF,                /* bStrExist         */
  /*  188 */ VAR_SCALE,             /* uInvScale         */
  /*  189 */ VAR_SCALE,             /* uScExplicit       */
  /*  190 */ VAR_POINT,             /* uSubVect          */
  /*  191 */ 0xFFFF,                /* bScaleExist       */
  /*  192 */ 0xFFFF,                /* uScSkipOffset     */
  /*  193 */ VAR_DATE,              /* uDateNow          */
  /*  194 */ 0xFFFF,                /* DefFrmSozNr       */
  /*  195 */ VAR_POINT,             /* uPtExplicit       */
  /*  196 */ 0xFFFF,                /* DefFrmDevDec      */
  /*  197 */ 0xFFFF,                /* DefFrmRectImage   */
  /*  198 */ 0xFFFF,                /* DefCheckBox       */
  /*  199 */ VAR_LONG,              /* uAddLong          */
  /*  200 */ VAR_LONG,              /* uMaskLong         */
  /*  201 */ VAR_LONG,              /* uFindLong         */
  /*  202 */ VAR_LONG,              /* uGetLong          */
  /*  203 */ 0xFFFF,                /* bDatExist         */
  /*  204 */ 0xFFFF,                /* DefFrmStrShortList*/
  /*  205 */ 0xFFFF,                /* uMutualExclude    */
  /*  206 */ 0xFFFF,                /* uSetDirKey        */
  /*  207 */ 0xFFFF,                /* bLongEqual        */
  /*  208 */ 0xFFFF,                /* Trc_DefArc        */
  /*  209 */ 0xFFFF,                /* DefSoftEdit       */
  /*  210 */ 0xFFFF,                /* SetDocBestWidth   */
  /*  211 */ 0xFFFF,                /* DefPattern        */
  /*  212 */ VAR_DEC,               /* uGetIndDec        */
  /*  213 */ 0xFFFF,                /* VTOCopy           */
  /*  214 */ 0xFFFF,                /* VTOSetEmptyCont   */
  /*  215 */ 0xFFFF,                /* InstallKeyWord    */
  /*  216 */ 0xFFFF,                /* DefFrmTab         */
  /*  217 */ 0xFFFF,                /* DefFrmTabField    */
  /*  218 */ 0xFFFF,                /* DefTabDecField    */
  /*  219 */ 0xFFFF,                /* DefTabShortStrListField*/
  /*  220 */ 0xFFFF,                /* DefTabFlagField   */
  /*  221 */ 0xFFFF,                /* CalcTabPos        */
  /*  222 */ 0xFFFF,                /* uCntmCro          */
  /*  223 */ 0xFFFF,                /* mShowMessageBox   */
  /*  224 */ 0xFFFF,                /* DefCutEdit        */
  /*  225 */ 0xFFFF,                /* DefCheckField     */
  /*  226 */ 0xFFFF,                /* DefTabCheckField  */
  /*  227 */ 0xFFFF,                /* SetDigCnf         */
  /*  228 */ VAR_STR,               /* eFindSubStr       */
  /*  229 */ 0xFFFF,                /* DoIconEleSelect   */
  /*  230 */ 0xFFFF,                /* DefFrmStrDivList  */
  /*  231 */ 0xFFFF,                /* bCmpShort         */
  /*  232 */ VAR_CONT,              /* uScContPart       */
  /*  233 */ 0xFFFF,                /* bContExist        */
  /*  234 */ 0xFFFF,                /* DefFrmTabDate     */
  /*  235 */ 0xFFFF,                /* bYearGreater      */
  /*  236 */ 0xFFFF,                /* DefTabStrListField*/
  /*  237 */ 0xFFFF,                /* uSetDirKeyUpDown  */
  /*  238 */ 0xFFFF,                /* uSetDirKeyLeftRight*/
  /*  239 */ 0xFFFF,                /* bCmpLong           */
  /*  240 */ 0xFFFF,                /* uEstimateTang      */
  /*  241 */ 0xFFFF,                /* DefTabColDec       */
  /*  242 */ 0xFFFF,                /* bCmpFloat          */
  /*  243 */ 0xFFFF,                /* DefFKurve          */
  /*  244 */ VAR_POINT,             /* GetFieldLeftLower  */
  /*  245 */ VAR_POINT,             /* GetFieldRightLower */
  /*  246 */ 0xFFFF,                /* uOptimize          */
  /*  247 */ VAR_DEC,               /* uContDist          */
  /*  248 */ 0xFFFF,                /* bCmpString         */
  /*  249 */ VAR_DEC,               /* uExpVal            */
  /*  250 */ VAR_DEC,               /* uPowVal            */
  /*  251 */ 0xFFFF,                /* uCubSpl            */
  /*  252 */ 0xFFFF,                /* DefFrmSlantField   */
  /*  253 */ VAR_CONT,              /* uStretchCont       */
  /*  254 */ 0xFFFF,                /* DefFrmSlantDec     */
  /*  255 */ 0xFFFF,                /* DefFrmSlantSLDec   */
  /*  256 */ VAR_CONT,              /* uConnectCont       */
  /*  257 */ 0xFFFF,                /* bCmpDate           */
  /*  258 */ 0xFFFF,                /* bCmpTime           */
  /*  259 */ 0xFFFF,                /* uDelData           */
  /*  260 */ 0xFFFF,                /* uTurningPoint      */
  /*  261 */ 0xFFFF,                /* uMutualExcludeNone */
  /*  262 */ 0xFFFF,                /* DefMovePattern     */
  /*  263 */ 0xFFFF,                /* DefFrmDefDec       */
  /*  264 */ 0xFFFF,                /* DefFrmMultiField   */
  /*  265 */ 0xFFFF,                /* ChangeCubSplPt     */
  /*  266 */ 0xFFFF,                /* Vto_OnMove         */
  /*  267 */ 0xFFFF,                /* Vto_DrawObject     */
  /*  268 */ 0xFFFF,                /* AddSHEnt           */
  /*  269 */ 0xFFFF,                /* bFindInd           */
  /*  270 */ 0xFFFF,                /* WriteCubSpl        */
  /*  271 */ 0xFFFF,                /* uSetMulti          */
  /*  272 */ 0xFFFF,                /* uCopyRefs          */
  /*  273 */ 0xFFFF,                /* uCalcSoftVect      */
  /*  274 */ 0xFFFF,                /* CreateScreen       */
  /*  275 */ 0xFFFF,                /* GenericTool        */
  /*  276 */ 0xFFFF,                /* GenericTool        */
  /*  277 */ 0xFFFF,                /* GenericTool        */
  /*  278 */ 0xFFFF,                /* GenericTool        */
  /*  279 */ 0xFFFF,                /* GenericTool        */
  /*  280 */ 0xFFFF,                /* GenericTool        */
  /*  281 */ 0xFFFF,                /* GenericTool        */
  /*  282 */ 0xFFFF,                /* GenericTool        */
  /*  283 */ 0xFFFF,                /* GenericTool        */
  /*  284 */ 0xFFFF,                /* GenericTool        */
  /*  285 */ 0xFFFF,                /* GenericTool        */
  /*  286 */ 0xFFFF,                /* CallProc           */
  /*  287 */ 0xFFFF,                /* ActivateScreen     */
  /*  288 */ 0xFFFF,                /* SetScale           */
  /*  289 */ 0xFFFF,                /* StoreData          */
  /*  290 */ 0xFFFF,                /* SetDocSide         */
  /*  291 */ 0xFFFF,                /* SetDocBestSize     */
  /*  292 */ 0xFFFF,                /* RemoveFormatInfo   */
  /*  293 */ VAR_STR,               /* GetPascalString    */
  /*  294 */ VAR_STR,               /* GetProfileString   */
  /*  295 */ 0xFFFF,                /* DefTrcImage        */
  /*  296 */ 0xFFFF,                /* RenameFile         */
  /*  297 */ 0xFFFF,                /* WriteToIniFile     */
  /*  298 */ 0xFFFF,                /* GenericTool        */
  /*  299 */ 0xFFFF,                /* GenericTool        */
  /*  300 */ 0xFFFF,                /* GenericTool        */
  /*  301 */ 0xFFFF,                /* WinExit            */
  /*  302 */ VAR_STRARR,            /* GetConnNmbr        */
  /*  303 */ 0xFFFF,                /* DivideIntoFormatStrings */
  /*  304 */ 0xFFFF,                /* AllowAdditionalSel */
  /*  305 */ 0xFFFF,                /* DisableFlapChange  */
  /*  306 */ 0xFFFF,                /* DBCall_Get         */
  /*  307 */ 0xFFFF,                /* GenericTool        */
  /*  308 */ 0xFFFF,                /* lSelect            */
  /*  309 */ 0xFFFF,                /* GenericTool        */
  /*  310 */ 0xFFFF,                /* GenericTool        */
  /*  311 */ 0xFFFF,                /* GenericTool        */
  /*  312 */ 0xFFFF,                /* GenericTool        */
  /*  313 */ 0xFFFF,                /* GenericTool        */
  /*  314 */ 0xFFFF,                /* GenericTool        */
  /*  315 */ 0xFFFF,                /* lPrint             */
  /*  316 */ 0xFFFF,                /* LinkElements       */
  /*  317 */ 0xFFFF,                /* CreatePaintDocument */
  /*  318 */ VAR_STRARR,            /* SetIndIndex        */
  /*  319 */ 0xFFFF,                /* GenericTool        */
  /*  320 */ 0xFFFF,                /* DBCall_Update      */
  /*  321 */ 0xFFFF,                /* DBCall_Insert      */
  /*  322 */ 0xFFFF,                /* DBCall_Excute      */
  /*  323 */ VAR_DEC,               /* LongToFloat        */
  /*  324 */ VAR_DEC,               /* ShortToFloat       */
  /*  325 */ 0xFFFF,                /* DestroyDocument    */
  /*  326 */ 0xFFFF,                /* InitHk             */
  /*  327 */ VAR_LONG,              /* FloatToLong        */
  /*  328 */ VAR_STRARR,            /* FloatToShort       */
  /*  329 */ VAR_STRARR,            /* LongToShort        */
  /*  330 */ VAR_LONG,              /* ShortToLong        */
  /*  331 */ 0xFFFF,                /* CallOnUpdate       */
  /*  332 */ 0xFFFF,                /* lRefreshList       */
  /*  333 */ 0xFFFF,                /* TileDocuments      */
  /*  334 */ 0xFFFF,                /* ArrangeDocuments   */
  /*  335 */ 0xFFFF,                /* SwitchToNextWindow */
  /*  336 */ 0xFFFF,                /* SwitchToPrevWindow */
  /*  337 */ 0xFFFF,                /* ExtractDate        */
  /*  338 */ 0xFFFF,                /* DestroyAllDocuments*/
  /*  339 */ 0xFFFF,                /* GenericTool        */
  /*  340 */ 0xFFFF,                /* SwitchToNextField  */
  /*  341 */ 0xFFFF,                /* SwitchToPrevField  */
  /*  342 */ 0xFFFF,                /* ActivateApp        */
  /*  343 */ 0xFFFF,                /* Str_Scanf          */
  /*  344 */ 0xFFFF,                /* InstallClpObserver */
  /*  345 */ 0xFFFF,                /* WriteClpBoard      */
  /*  346 */ 0xFFFF,                /* AvoidActivation    */
  /*  347 */ 0xFFFF,                /* RemoveObserver     */
  /*  348 */ 0xFFFF,                /* TaskExist          */
  /*  349 */ 0xFFFF,                /* OnTaskDestroy      */
  /*  350 */ 0xFFFF,                /* StartTask          */
  /*  351 */ 0xFFFF,                /* WatchCreation      */
  /*  352 */ VAR_STRARR,            /* lGetSelCount       */
  /*  353 */ 0xFFFF,                /* GetRecCount        */
  /*  354 */ 0xFFFF,                /* ShowToolList       */
  /*  355 */ VAR_STR,               /* GetTextFrom        */
  /*  356 */ 0xFFFF,                /* PrintDocument      */
  /*  357 */ 0xFFFF,                /* mNumSize           */
  /*  358 */ 0xFFFF,                /* DefmNum            */
  /*  359 */ 0xFFFF,                /* GetDataWithCodeData*/
  /*  360 */ 0xFFFF,                /* OnDocumentDestroy  */
  /*  361 */ 0xFFFF,                /* IsInJobList        */
  /*  362 */ 0xFFFF,                /* IsDocOpen          */
  /*  363 */ VAR_STR,               /* PaddString         */
  /*  364 */ VAR_STR,               /* ExtractString      */
  /*  365 */ 0xFFFF,                /* bCompareString     */
  /*  366 */ VAR_DATE,              /* BuildDate          */
  /*  367 */ 0xFFFF,                /* ExtractTime        */
  /*  368 */ VAR_TIME,              /* BuildTime          */
  /*  369 */ 0xFFFF,                /* bLongVarEqual      */
  /*  370 */ VAR_STRARR,            /* uSubInd            */
  /*  371 */ VAR_LONG,              /* uSubLong           */
  /*  372 */ VAR_STR,               /* FormatDate         */
  /*  373 */ VAR_STR,               /* FormatTime         */
  /*  374 */ 0xFFFF,                /* GetLicense         */
  /*  375 */ 0xFFFF,                /* Beeps              */
  /*  376 */ 0xFFFF,                /* DBCall_Delete      */
  /*  377 */ 0xFFFF,                /* DoHotkeyAction     */
  /*  378 */ 0xFFFF,                /* SetCharCallback    */
  /*  379 */ 0xFFFF,                /* GenericTool        */
  /*  380 */ 0xFFFF,                /* PrgExit            */
  /*  381 */ 0xFFFF,                /* SetWndFormat       */
  /*  382 */ 0xFFFF,                /* GetFormatStrings   */
  /*  383 */ 0xFFFF,                /* IsDocOpenName      */
  /*  384 */ 0xFFFF,                /* ActivateDoc        */
  /*  385 */ 0xFFFF,                /* GetDocFName        */
  /*  386 */ 0xFFFF,                /* DefEntParam        */
  /*  387 */ 0xFFFF,                /* DefEnterPoint      */
  /*  388 */ 0xFFFF,                /* DefEnterCont       */
  /*  389 */ 0xFFFF,                /* FrmImportImage     */
  /*  390 */ 0xFFFF,                /* GetFieldFormat     */
  /*  391 */ 0xFFFF,                /* Retired            */
  /*  392 */ 0xFFFF,                /* Retired               */
  /*  393 */ 0xFFFF,                /* FrmStoreImage      */
  /*  394 */ 0xFFFF,                /* SetFocusToDoc      */
  /*  395 */ VAR_DATE,              /* uAddDays           */
  /*  396 */ 0xFFFF,                /* ImgGetOriginal     */
  /*  397 */ 0xFFFF,                /* ImgUserFlt         */
  /*  398 */ 0xFFFF,                /* ImgBestContrast    */
  /*  399 */ 0xFFFF,                /* ImgCrispFlt        */
  /*  400 */ 0xFFFF,                /* ImgMedianFlt       */
  /*  401 */ 0xFFFF,                /* ImgSobelFlt        */
  /*  402 */ 0xFFFF,                /* ImgLocalContrast   */
  /*  403 */ 0xFFFF,                /* Vto_SetMode        */
  /*  404 */ 0xFFFF,                /* Retired               */
  /*  405 */ 0xFFFF,                /* Vto_ApplyCut          */
  /*  406 */ 0xFFFF,                /* SynchorizeUpdate      */
  /*  407 */ 0xFFFF,                /* CloseDocument         */
  /*  408 */ VAR_DEC,               /* uGetx                 */
  /*  409 */ VAR_DEC,               /* uGety                 */
  /*  410 */ 0xFFFF,                /* Retired               */
  /*  411 */ VAR_CONT,              /* uClipCont             */
  /*  412 */ 0xFFFF,                /* Retired               */
  /*  413 */ 0xFFFF,                /* GetCreationData       */
  /*  414 */ 0xFFFF,                /* SetFNrRef             */
  /*  415 */ 0xFFFF,                /* ModifyDocFallNummer   */
  /*  416 */ VAR_STR,               /* GetFullDocumentName   */
  /*  417 */ 0xFFFF,                /* Retired               */
  /*  418 */ 0xFFFF,                /* ShowDocMaximized      */
  /*  419 */ 0xFFFF,                /* ExtractRef            */
  /*  420 */ 0xFFFF,                /* bDataEqual            */
  /*  421 */ 0xFFFF,                /* CallOnDestroy         */
  /*  422 */ 0xFFFF,                /* Retired               */
  /*  423 */ 0xFFFF,                /* Retired               */
  /*  424 */ VAR_STRARR,            /* uAddInd               */
  /*  425 */ VAR_DATE,              /* uSetDate              */
  /*  426 */ 0xFFFF,                /* GenericTool           */
  /*  427 */ 0xFFFF,                /* ToBusy                */
  /*  428 */ 0xFFFF,                /* RemoveControlFromLayer*/
  /*  429 */ 0xFFFF,                /* ActivateScreenLayer   */
  /*  430 */ 0xFFFF,                /* GenericTool           */
  /*  431 */ 0xFFFF,                /* GenericTool           */
  /*  432 */ 0xFFFF,                /* SetFocusToObject      */
  /*  433 */ 0xFFFF,                /* Retired            */
  /*  434 */ 0xFFFF,                /* Retired            */
  /*  435 */ 0xFFFF,                /* GenericTool           */
  /*  436 */ 0xFFFF,                /* CallWindowsHelp       */
  /*  437 */ VAR_DATE,              /* uAddMonths            */
  /*  438 */ VAR_DATE,              /* uAddYears             */
  /*  439 */ 0xFFFF,                /* Retired               */
  /*  440 */ 0xFFFF,                /* SetWindowDimension    */
  /*  441 */ 0xFFFF,                /* Retired               */
  /*  442 */ 0xFFFF,                /* SetWindowTitle        */
  /*  443 */ 0xFFFF,                /* GetDocInstance        */
  /*  444 */ 0xFFFF,                /* DBCall_FormComboList  */
  /*  445 */ 0xFFFF,                /* DBCall_ToolComboList  */
  /*  446 */ VAR_STR,               /* GetScriptProperty     */
  /*  447 */ VAR_STRARR,            /* GetScriptProperty_Int */
  /*  448 */ 0xFFFF,                /* Retired               */
  /*  449 */ 0xFFFF,                /* Retired               */
  /*  450 */ 0xFFFF,                /* Retired               */
  /*  451 */ 0xFFFF,                /* Retired               */
  /*  452 */ 0xFFFF,                /* BringObjectToTail     */
  /*  453 */ 0xFFFF,                /* Retired               */
  /*  454 */ 0xFFFF,                /* Retired               */
  /*  455 */ 0xFFFF,                /* SetObjectSide         */
  /*  456 */ 0xFFFF,                /* DeleteFile            */
  /*  457 */ 0xFFFF,                /* FileSelector_Box      */
  /*  458 */ 0xFFFF,                /* DefPrgIcon            */
  /*  459 */ VAR_STRARR,            /* GetVarSize            */
  /*  460 */ 0xFFFF,                /* DefFrmStaticBitmap    */
  /*  461 */ 0xFFFF,                /* SetEntryHeight        */
  /*  462 */ 0xFFFF,                /* SetEditSize           */
  /*  463 */ 0xFFFF,                /* RestoreRecord         */
  /*  464 */ 0xFFFF,                /* SaveRecord            */
  /*  465 */ VAR_DEC,               /* GetFormatBaseHeight   */
  /*  466 */ 0xFFFF,                /* Retired               */
  /*  467 */ 0xFFFF,                /* Retired               */
  /*  468 */ 0xFFFF,                /* Retired               */
  /*  469 */ 0xFFFF,                /* Retired               */
  /*  470 */ 0xFFFF,                /* Retired               */
  /*  471 */ 0xFFFF,                /* RemoveCRLF            */
  /*  472 */ 0xFFFF,                /* Retired               */
  /*  473 */ 0xFFFF,                /* Retired               */
  /*  474 */ 0xFFFF,                /* OnActivation          */
  /*  475 */ 0xFFFF,                /* ShowmNumHelp          */
  /*  476 */ 0xFFFF,                /* ShowmNumGauss         */
  /*  477 */ 0xFFFF,                /* DefActivationRegion   */
  /*  478 */ 0xFFFF,                /* DefNormObj            */
  /*  479 */ 0xFFFF,                /* DefNormTab            */
  /*  480 */ 0xFFFF,                /* GetNorm               */
  /*  481 */ 0xFFFF,                /* ListCharCallBack      */
  /*  482 */ 0xFFFF,                /* IsFirstCharAlpha      */
  /*  483 */ 0xFFFF,                /* IsFirstCharNumeric    */
  /*  484 */ 0xFFFF,                /* RemoveLastChar        */
  /*  485 */ 0xFFFF,                /* DefFrmBField          */
  /*  486 */ 0xFFFF,                /* GenericTool           */
  /*  487 */ 0xFFFF,                /* GetCapStr             */
  /*  488 */ 0xFFFF,                /* GetDigits             */
  /*  489 */ 0xFFFF,                /* Retired               */
  /*  490 */ 0xFFFF,                /* RemoveSpaces          */
  /*  491 */ VAR_POINT,             /* uGetThirdPt           */
  /*  492 */ VAR_DEC,               /* uGetNAbstPt           */
  /*  493 */ VAR_POINT,             /* uGetRotPt             */
  /*  494 */ VAR_POINT,             /* uCalcNewPt            */
  /*  495 */ VAR_DEC,               /* GetGrowthVal          */
  /*  496 */ VAR_POINT,             /* GetMidPts             */
  /*  497 */ VAR_DEC,               /* uSin                  */
  /*  498 */ VAR_DEC,               /* uCos                  */
  /*  499 */ 0xFFFF,                /* uGetVGrid             */
  /*  500 */ 0xFFFF,                /* DefOutVGrid           */
  /*  501 */ 0xFFFF,                /* SetMouseScale         */
  /*  502 */ 0xFFFF,                /* InitializeData        */
  /*  503 */ 0xFFFF,                /* GetListHeight         */
  /*  504 */ 0xFFFF,                /* OptimizeHeight        */
  /*  505 */ 0xFFFF,                /* Retired            */
  /*  506 */ 0xFFFF,                /* Retired               */
  /*  507 */ 0xFFFF,                /* SetNewPts             */
  /*  508 */ 0xFFFF,                /* GrowPt                */
  /*  509 */ 0xFFFF,                /* GrowCnt               */
  /*  510 */ 0xFFFF,                /* CombineData           */
  /*  511 */ 0xFFFF,                /* uSetOther             */
  /*  512 */ VAR_DATE,              /* uAddYearsDec          */
  /*  513 */ 0xFFFF,                /* SetFrmEditSize        */
  /*  514 */ 0xFFFF,                /* ExtractData           */
  /*  515 */ 0xFFFF,                /* AvoidWrite            */
  /*  516 */ 0xFFFF,                /* GenericTool           */
  /*  517 */ 0xFFFF,                /* Retired            */
  /*  518 */ 0xFFFF,                /* GetPrTextHeight       */
  /*  519 */ 0xFFFF,                /* Retired            */
  /*  520 */ 0xFFFF,                /* Retired            */
  /*  521 */ 0xFFFF,                /* Retired            */
  /*  522 */ 0xFFFF,                /* GetPrinterType        */
  /*  523 */ 0xFFFF,                /* SetPrinter            */
  /*  524 */ 0xFFFF,                /* Retired            */
  /*  525 */ 0xFFFF,                /* Retired            */
  /*  526 */ 0xFFFF,                /* GetDefaultPrinterName */
  /*  527 */ 0xFFFF,                /* SetCaretToEnd         */
  /*  528 */ 0xFFFF,                /* SetEditCaretToEnd     */
  /*  529 */ 0xFFFF,                /* ClearQueue            */
  /*  530 */ 0xFFFF,                /* Vto_CalcAllRotCents   */
  /*  531 */ 0xFFFF,                /* Start_TimeMark        */
  /*  532 */ 0xFFFF,                /* DefMoveField          */
  /*  533 */ 0xFFFF,                /* DefMoveLine           */
  /*  534 */ 0xFFFF,                /* DefHelpLine           */
  /*  535 */ 0xFFFF,                /* SetDblClkProc         */
  /*  536 */ 0xFFFF,                /* CallExternProc        */
  /*  537 */ 0xFFFF,                /* bWordGreater          */
  /*  538 */ 0xFFFF,                /* GetTwainSources       */
  /*  539 */ 0xFFFF,                /* KettenLinienParameter */
  /*  540 */ 0xFFFF,                /* GetKettenLinie        */
  /*  541 */ 0xFFFF,                /* BestPalette           */
  /*  542 */ 0xFFFF,                /* ModifyKettenLinienExt */
  /*  543 */ 0xFFFF,                /* SplitCont             */
  /*  544 */ 0xFFFF,                /* DDSOle                */
  /*  545 */ 0xFFFF,                /* FrmSetImage           */
  /*  546 */ 0xFFFF,                /* FrmWriteBMP           */
  /*  547 */ 0xFFFF,                /* ExtractPath           */
  /*  548 */ 0xFFFF,                /* FrmGetPixPerMeter     */
  /*  549 */ 0xFFFF,                /* FrmSetPixPerMeter     */
  /*  550 */ 0xFFFF,                /* FrmGetImgWidth        */
  /*  551 */ 0xFFFF,                /* FrmDrawContDirect     */
  /*  552 */ 0xFFFF,                /* uGetImgPhysScale      */
  /*  553 */ 0xFFFF,                /* CreateEdgeTable       */
  /*  554 */ 0xFFFF,                /* FillInEdges           */
  /*  555 */ 0xFFFF,                /* FrmMorphImage         */
  /*  556 */ 0xFFFF,                /* Trc_DefRectangle      */
  /*  557 */ VAR_CONT,              /* MakeCont              */
  /*  558 */ VAR_CONT,              /* uMultiDivideCont      */
  /*  559 */ 0xFFFF,                /* SetIndElement         */
  /*  560 */ 0xFFFF,                /* bIndGreater           */
  /*  561 */ 0xFFFF,                /* MakeContFromDec       */
  /*  562 */ 0xFFFF,                /* FrmGetImageScaleFact  */
  /*  563 */ 0xFFFF,                /* SetEditOverwrite      */
  /*  564 */ 0xFFFF,                /* FrmGetImageFileName   */
  /*  565 */ 0xFFFF,                /* UseIntern             */
  /*  566 */ 0xFFFF,                /* Use                   */
  /*  567 */ 0xFFFF,                /* GenericTool           */
  /*  568 */ 0xFFFF,                /* GenericTool           */
  /*  569 */ 0xFFFF,                /* Out                   */
  /*  570 */ 0xFFFF,                /* InOut                 */
  /*  571 */ 0xFFFF,                /* NewRec                */
  /*  572 */ 0xFFFF,                /* ShowDDSList           */
  /*  573 */ 0xFFFF,                /* SetObjCallBack        */
  /*  574 */ 0xFFFF,                /* CreateDialogDocument  */
  /*  575 */ 0xFFFF,                /* ShowToolDDSList       */
  /*  576 */ 0xFFFF,                /* lSetSelCallBack       */
  /*  577 */ 0xFFFF,                /* lChangeSelection      */
  /*  578 */ 0xFFFF,                /* CallOverSelection     */
  /*  579 */ 0xFFFF,                /* Do                    */
  /*  580 */ 0xFFFF,                /* GetNetWorkAddress     */
  /*  581 */ 0xFFFF,                /* PaintStdHeader        */
  /*  582 */ 0xFFFF,                /* EndCreateMappe        */
  /*  583 */ 0xFFFF,                /* AddMappElem           */
  /*  584 */ 0xFFFF,                /* StartCreateMappe      */
  /*  585 */ 0xFFFF,                /* CreateMapScreen       */
  /*  586 */ 0xFFFF,                /* SetMenuText           */
  /*  587 */ 0xFFFF,                /* AddMenuCommand        */
  /*  588 */ 0xFFFF,                /* SetButtons            */
  /*  589 */ 0xFFFF,                /* UseDialogDocument     */
  /*  590 */ 0xFFFF,                /* GetRecordPtr          */
  /*  591 */ 0xFFFF,                /* ReUseRecord           */
  /*  592 */ 0xFFFF,                /* LoadInternList        */
  /*  593 */ 0xFFFF,                /* MoveToolGroup         */
  /*  594 */ 0xFFFF,                /* SetToolExtension      */
  /*  595 */ 0xFFFF,                /* SetPrgCaption         */
  /*  596 */ 0xFFFF,                /* GenericTool           */
  /*  597 */ 0xFFFF,                /* OnSizeChanged         */
  /*  598 */ 0xFFFF,                /* SetDelayedUpdate      */
  /*  599 */ 0xFFFF,                /* SetDestruktor         */
  /*  600 */ 0xFFFF,                /* CallForSelected       */
  /*  601 */ 0xFFFF,                /* LoadList              */
  /*  602 */ 0xFFFF,                /* PackList              */
  /*  603 */ 0xFFFF,                /* lSetSelChangeCallback */
  /*  604 */ 0xFFFF,                /* lSetMaxSelCount       */
  /*  605 */ VAR_BLOB,              /* CopyBlob              */
  /*  606 */ 0xFFFF,                /* CreateInnerList       */
  /*  607 */ 0xFFFF,                /* AddRecToInnerList     */
  /*  608 */ 0xFFFF,                /* bIsSelected           */
  /*  609 */ 0xFFFF,                /* CallOverInnerList     */
  /*  610 */ 0xFFFF,                /* RemoveRecFromInnerList*/
  /*  611 */ 0xFFFF,                /* CallInInnerListFor    */
  /*  612 */ 0xFFFF,                /* KisInit               */
  /*  613 */ 0xFFFF,                /* KisExit               */
  /*  614 */ 0xFFFF,                /* KisSelectionOpen      */
  /*  615 */ 0xFFFF,                /* KisSelectionClose     */
  /*  616 */ 0xFFFF,                /* KisRecordRead         */
  /*  617 */ 0xFFFF,                /* KisRecordWrite        */
  /*  618 */ 0xFFFF,                /* KisRecordCreate       */
  /*  619 */ 0xFFFF,                /* KisRecordFree         */
  /*  620 */ 0xFFFF,                /* KisTableOpen          */
  /*  621 */ 0xFFFF,                /* KisTableClose         */
  /*  622 */ 0xFFFF,                /* KisDataGet            */
  /*  623 */ 0xFFFF,                /* KisDataSet            */
  /*  624 */ VAR_STRARR,            /* InStr                 */
  /*  625 */ VAR_STR,               /* MidStr                */
  /*  626 */ VAR_STRARR,            /* StrLen                */
  /*  627 */ 0xFFFF,                /* DDE_GetLastError      */
  /*  628 */ 0xFFFF,                /* KisConvBcdToMac       */
  /*  629 */ 0xFFFF,                /* KisConvMacToBcd       */
  /*  630 */ VAR_STR,               /* InterpreteHdString    */
  /*  631 */ 0xFFFF,                /* ActivateObject        */
  /*  632 */ 0xFFFF,                /* ConnectToCheckBox     */
  /*  633 */ 0xFFFF,                /* GetScriptParameter    */
  /*  634 */ 0xFFFF,                /* Trc_DefRectImage      */
  /*  635 */ 0xFFFF,                /* DefMoveRect           */
  /*  636 */ 0xFFFF,                /* DefMoveRectImage      */
  /*  637 */ 0xFFFF,                /* ToolLongInt           */
  /*  638 */ 0xFFFF,                /* ToolMoney             */
  /*  639 */ VAR_STRARR,            /* uMulInd               */
  /*  640 */ VAR_STRARR,            /* uDivInd               */
  /*  641 */ VAR_LONG,              /* uMulLong              */
  /*  642 */ VAR_LONG,              /* uDivLong              */
  /*  643 */ 0xFFFF,                /* DefFrmShort           */
  /*  644 */ 0xFFFF,                /* DefFrmLong            */
  /*  645 */ 0xFFFF,                /* DefFrmMoney           */
  /*  646 */ 0xFFFF,                /* IstFeierTag           */
  /*  647 */ 0xFFFF,                /* SetToolPalette        */
  /*  648 */ 0xFFFF,                /* ToolPalette           */
  /*  649 */ 0xFFFF,                /* BitEdit               */
  /*  650 */ 0xFFFF,                /* BitEditMode           */
  /*  651 */ 0xFFFF,                /* MergeBit              */
  /*  652 */ 0xFFFF,                /* PresentBitmap         */
  /*  653 */ 0xFFFF,                /* GetNextFlagInd        */
  /*  654 */ 0xFFFF,                /* SetSetFocusProc       */
  /*  655 */ VAR_STRARR,            /* BitCount              */
  /*  656 */ 0xFFFF,                /* bVektorInProd         */
  /*  657 */ 0xFFFF,                /* UnionVektor           */
  /*  658 */ 0xFFFF,                /* GenerateVector        */
  /*  659 */ 0xFFFF,                /* SetFilterProc         */
  /*  660 */ 0xFFFF,                /* TextMerge             */
  /*  661 */ 0xFFFF,                /* PresentText           */
  /*  662 */ VAR_STR,               /* RemoveChar            */
  /*  663 */ 0xFFFF,                /* ExpandBinary          */
  /*  664 */ 0xFFFF,                /* GetBaseUnit           */
  /*  665 */ 0xFFFF,                /* DefMultiDim           */
  /*  666 */ 0xFFFF,                /* WriteMultiDim         */
  /*  667 */ 0xFFFF,                /* ReadMultiDim          */
  /*  668 */ 0xFFFF,                /* LoadMultiDim          */
  /*  669 */ 0xFFFF,                /* UpdateScreenImmediate */
  /*  670 */ 0xFFFF,                /* TextPushCheckButton   */
  /*  671 */ 0xFFFF,                /* GetVersionInfo        */
  /*  672 */ 0xFFFF,                /* SetFieldMode          */
  /*  673 */ 0xFFFF,                /* SetMapExtent          */
  /*  674 */ 0xFFFF,                /* SetDocumentTitle      */
  /*  675 */ 0xFFFF,                /* SetEditMode           */
  /*  676 */ VAR_STRARR,            /* GetFieldModify        */
  /*  677 */ 0xFFFF,                /* SetFieldModify        */
  /*  678 */ 0xFFFF,                /* SetOnActivate         */
  /*  679 */ 0xFFFF,                /* SetOnDeactivate       */
  /*  680 */ 0xFFFF,                /* SetObjModify          */
  /*  681 */ VAR_STRARR,            /* GetObjModify          */
  /*  682 */ 0xFFFF,                /* SetEditFormatMaps     */
  /*  683 */ 0xFFFF,                /* SetObjFormatMaps      */
  /*  684 */ VAR_STR,               /* StrRemoveFormat       */
  /*  685 */ 0xFFFF,                /* OpenPrinterDirect     */
  /*  686 */ 0xFFFF,                /* PrintDirect           */
  /*  687 */ 0xFFFF,                /* ClosePrinterDirect    */
  /*  688 */ VAR_STR,               /* CRtoCRLF              */
  /*  689 */ 0xFFFF,                /* bVektorTeilmenge      */
  /*  690 */ 0xFFFF,                /* IntersectionVektor    */
  /*  691 */ VAR_STR,               /* GetDBHandler          */
  /*  692 */ 0xFFFF,                /* CreateFormTool        */
  /*  693 */ 0xFFFF,                /* FormToolPictureButton */
  /*  694 */ 0xFFFF,                /* FormToolTextButton    */
  /*  695 */ 0xFFFF,                /* SetToolObjectColor    */
  /*  696 */ VAR_STRARR,            /* GetObjLineHeight      */
  /*  697 */ 0xFFFF,                /* SetObjLineHeight      */
  /*  698 */ 0xFFFF,                /* SetFieldPageBreak     */
  /*  699 */ 0xFFFF,                /* GetFieldLeftLowerSeite*/
  /*  700 */ 0xFFFF,                /* CallDllProcP          */
  /*  701 */ 0xFFFF,                /* CallDllProcC          */
  /*  702 */ 0xFFFF,                /* CallDllBoolProcP      */
  /*  703 */ 0xFFFF,                /* CallDllBoolProcC      */
  /*  704 */ 0xFFFF,                /* FreeExternDll         */
  /*  705 */ 0xFFFF,                /* GenericTool           */
  /*  706 */ 0xFFFF,                /* KisError              */
  /*  707 */ 0xFFFF,                /* FileSeek              */
  /*  708 */ 0xFFFF,                /* SetLineObjects        */
  /*  709 */ 0xFFFF,                /* NonRepeativeObjects   */
  /*  710 */ 0xFFFF,                /* SetExtraModify        */
  /*  711 */ 0xFFFF,                /* GetToolCoordinates    */
  /*  712 */ 0xFFFF,                /* SetDialogPos          */
  /*  713 */ 0xFFFF,                /* SplitPath             */
  /*  714 */ 0xFFFF,                /* lSetHeaderClickCallBack */
  /*  715 */ 0xFFFF,                /* FindFirst             */
  /*  716 */ 0xFFFF,                /* FindNext              */
  /*  717 */ 0xFFFF,                /* WriteScriptLog        */
  /*  718 */ VAR_STR,               /* ExpandRNT             */
  /*  719 */ VAR_STR,               /* MakeRNT               */
  /*  720 */ 0xFFFF,                /* SetRecHash            */
  /*  721 */ 0xFFFF,                /* ClearRecHash          */
  /*  722 */ 0xFFFF,                /* SetToolModify         */
  /*  723 */ VAR_STRARR,            /* GetToolModify         */
  /*  724 */ 0xFFFF,                /* SetCLINICUMEnvironment */
  /*  725 */ 0xFFFF,                /* SndDefObj             */
  /*  726 */ 0xFFFF,                /* SndClear              */
  /*  727 */ 0xFFFF,                /* bSndIsEmpty           */
  /*  728 */ 0xFFFF,                /* SndReadWav            */
  /*  729 */ 0xFFFF,                /* SndWriteWav           */
  /*  730 */ 0xFFFF,                /* SndPlayStart          */
  /*  731 */ 0xFFFF,                /* SndPause              */
  /*  732 */ 0xFFFF,                /* SndRestart            */
  /*  733 */ 0xFFFF,                /* SndPlayStop           */
  /*  734 */ 0xFFFF,                /* SndRecStart           */
  /*  735 */ 0xFFFF,                /* SndRecStop            */
  /*  736 */ 0xFFFF,                /* bSndIsCompatible      */
  /*  737 */ 0xFFFF,                /* ShowFormList          */
  /*  738 */ 0xFFFF,                /* InitializeVoidData    */
  /*  739 */ 0xFFFF,                /* SetArrayData          */
  /*  740 */ 0xFFFF,                /* GetArrayData          */
  /*  741 */ 0xFFFF,                /* LockDataKey           */
  /*  742 */ 0xFFFF,                /* HideScreen            */
  /*  743 */ VAR_QLONG,             /* ShortToQLong          */
  /*  744 */ VAR_QLONG,             /* FloatToQLong          */
  /*  745 */ VAR_QLONG,             /* LongToQLong           */
  /*  746 */ VAR_STRARR,            /* QLongToShort          */
  /*  747 */ VAR_DEC,               /* QLongToFloat          */
  /*  748 */ VAR_LONG,              /* QLongToLong           */
  /*  749 */ VAR_QLONG,             /* uAddQLong             */
  /*  750 */ VAR_QLONG,             /* uSubQLong             */
  /*  751 */ VAR_QLONG,             /* uDivQLong             */
  /*  752 */ VAR_QLONG,             /* uMulQLong             */
  /*  753 */ 0xFFFF,                /* DoDBRep               */
  /*  754 */ 0xFFFF,                /* DoDBRepIn             */
  /*  755 */ 0xFFFF,                /* GetDBToken            */
  /*  756 */ 0xFFFF,                /* UnlockDBToken         */
  /*  757 */ 0xFFFF,                /* ClearMyTokens         */
  /*  758 */ 0xFFFF,                /* MouseMoveProc         */
  /*  759 */ 0xFFFF,                /* MarkUpdateError       */
  /*  760 */ 0xFFFF,                /* SystemUpdate          */
  /*  761 */ 0xFFFF,                /* AlterTable            */
  /*  762 */ 0xFFFF,                /* ActivateList          */
  /*  763 */ 0xFFFF,                /* MarkVarStatic         */
  /*  764 */ 0xFFFF,                /* MarkVarDynamic        */
  /*  765 */ 0xFFFF,                /* OnScreenButtonDown    */
  /*  766 */ 0xFFFF,                /* CreateTable           */
  /*  767 */ 0xFFFF,                /* GetDBPointer          */
  /*  768 */ 0xFFFF,                /* ExeIs32Bit            */
  /*  769 */ 0xFFFF,                /* AddMessageHook        */
  /*  770 */ 0xFFFF,                /* GetFrameWindowHandle  */
  /*  771 */ 0xFFFF,                /* bCmpQLong             */
  /*  772 */ VAR_FLAG,              /* IsKeyPressed          */
  /*  773 */ 0xFFFF,                /* SetScrollProc         */
  /*  774 */ 0xFFFF,                /* PushData              */
  /*  775 */ 0xFFFF,                /* PopData               */
  /*  776 */ 0xFFFF,                /* DenyBusy              */
  /*  777 */ 0xFFFF,                /* AllowBusy             */
  /*  778 */ 0xFFFF,                /* DefineParse           */
  /*  779 */ 0xFFFF,                /* CheckExpression       */
  /*  780 */ 0xFFFF,                /* CreatePaintDocumentFromBlob      */
  /*  781 */ 0xFFFF,                /* CreatePrintDocumentFromBlob      */
  /*  782 */ 0xFFFF,                /* CallWithSignature     */
  /*  783 */ 0xFFFF,                /* InsertStrAtCaretObj   */
  /*  784 */ 0xFFFF,                /* InsertStrAtCaretTool  */
  /*  785 */ VAR_STRARR,            /* WordInStr             */
  /*  786 */ 0xFFFF,                /* DefineRegion          */
  /*  787 */ 0xFFFF,                /* RegioFromPoint        */
  /*  788 */ 0xFFFF,                /* RegioFromRect         */
  /*  789 */ 0xFFFF,                /* BestRegioFromPoint    */
  /*  790 */ VAR_STR,               /* ExchangeStringWithReplaceList */
  /*  791 */ VAR_STR,               /* ReplaceString */
  /*  792 */ VAR_STR,               /* ModifierToString */
  /*  793 */ 0xFFFF,                /* SetCaretTo */
  /*  794 */ 0xFFFF,                /* GetFieldLeftLowerAnzahlSeite */
  /*  795 */ 0xFFFF,                /* AppendContextMenu     */
  /*  796 */ 0xFFFF,                /* GetMDIClienData          */
  /*  797 */ 0xFFFF,                /* SetToolRefHandleExplizit */
  /*  798 */ 0xFFFF,                /* AddStringToBlob */
  /*  799 */ 0xFFFF,                /* AddVoidDataToBlob */
  /*  800 */ 0xFFFF,                /* GenerateScriptFromBlob */
  /*  801 */ 0xFFFF,                /* DelBlob */
  /*  802 */ 0xFFFF,                /* UseDialogDocumentFromBlob */
  /*  803 */ 0xFFFF,                /* BlobToFile */
  /*  804 */ 0xFFFF,                /* ExtBlobDoc */
  /*  805 */ 0xFFFF,                /* SetModifyBlob */
  /*  806 */ VAR_STRARR,            /* GetObjLen */
  /*  807 */ 0xFFFF,                /* AddParseFunction */
  /*  808 */ 0xFFFF,                /* StartParse */
  /*  809 */ 0xFFFF,                /* DeleteActivationPens */
  /*  810 */ 0xFFFF,                /* SetMapFont */
  /*  811 */ 0xFFFF,                /* SetFlapHeight */
  /*  812 */ 0xFFFF,                /* SetMapOffset */
  /*  813 */ 0xFFFF,                /* bToolSelectionInString */
  /*  814 */ VAR_STR,               /* TakeModifyFrom */
  /*  815 */ 0xFFFF,                /* DefTrcGrid */
  /*  816 */ VAR_BLOB,              /* BlobFromFile */
  /*  817 */ 0xFFFF,                /* AddParseConversion */
  /*  818 */ 0xFFFF,                /* WindowScroll */
  /*  819 */ 0xFFFF,                /* MultiComboSet */
  /*  820 */ 0xFFFF,                /* FrmGetImgInfo */
  /*  821 */ 0xFFFF,                /* FrmLoadDIB */
  /*  822 */ 0xFFFF,                /* FrmSaveDIB */
  /*  823 */ 0xFFFF,                /* ParentInst */
  /*  824 */ 0xFFFF,                /* CloseAllFiles */
  /*  825 */ 0xFFFF,                /* NoManipulate */
  /*  826 */ 0xFFFF,                /* DDE_SetTimeOut */
  /*  827 */ VAR_DEC,               /* TwipsToDlg */
  /*  828 */ 0xFFFF,                /* CreateOleObjectFromFile */
  /*  829 */ 0xFFFF,                /* RunOleObjectFromBlob */
  /*  830 */ 0xFFFF,                /* CreateCBDesc */
  /*  831 */ 0xFFFF,                /* DefineBitArray */
  /*  832 */ 0xFFFF,                /* SetBit */
  /*  833 */ 0xFFFF,                /* IsBitSet */
  /*  834 */ 0xFFFF,                /* BitAND */
  /*  835 */ 0xFFFF,                /* BitNOT */
  /*  836 */ 0xFFFF,                /* ShowFormComboInnerList */
  /*  837 */ 0xFFFF,                /* ShowToolComboInnerList */
  /*  838 */ 0xFFFF,                /* AppendFrmContextMenu */
  /*  839 */ 0xFFFF,                /* FrmFreeDIB */
  /*  840 */ VAR_LONG,              /* CRC32 */
  /*  841 */ 0xFFFF,                /* Encrypt32 */
  /*  842 */ 0xFFFF,                /* AddDictNode */
  /*  843 */ 0xFFFF,                /* GetFirstDictNode */
  /*  844 */ 0xFFFF,                /* GetNextDictNode */
  /*  845 */ 0xFFFF,                /* SetContextFunction */
  /*  846 */ 0xFFFF,                /* MakeTimeStamp */
  /*  847 */ 0xFFFF,                /* TextFromStrArray */
  /*  848 */ 0xFFFF,                /* ReallyExtractPath */
  /*  849 */ VAR_FLAG,              /* uPtInCont */
  /*  850 */ 0xFFFF,                /* DataFromPointer */
  /*  851 */ VAR_OBJ,               /* GetMouseObject */
  /*  852 */ 0xFFFF,                /* OpenCommPort */
  /*  853 */ 0xFFFF,                /* CloseCommPort */
  /*  854 */ 0xFFFF,                /* FlushCommPort */
  /*  855 */ 0xFFFF,                /* WriteStrCommPort */
  /*  856 */ 0xFFFF,                /* ReadStrCommPort */
  /*  857 */ 0xFFFF,                /* CommBytesReceived */
  /*  858 */ 0xFFFF,                /* SetListColor */
  /*  859 */ VAR_LONG,              /* GetSysColor */
  /*  860 */ 0xFFFF,                /* SetFrameType */
  /*  861 */ 0xFFFF,                /* DocumentToPrinterFromBlob */
  /*  862 */ 0xFFFF,                /* DIBFromClipboard */
  /*  863 */ 0xFFFF,                /* SetWindowPosition */
  /*  864 */ 0xFFFF,                /* MCICommand */
  /*  865 */ 0xFFFF,                /* StartParameter */
  /*  866 */ VAR_DEC,               /* InterpreteDouble */
  /*  867 */ VAR_DEC,               /* FrmGetImgRatio */
  /*  868 */ VAR_STR,               /* PressedChar */
  /*  869 */ 0xFFFF,                /* Trc_DefEllipse */
  /*  870 */ 0xFFFF,                /* SetListClickProc */
  /*  871 */ 0xFFFF,                /* ProfileOverrideBuffer */
  /*  872 */ 0xFFFF,                /* PushToBlob */
  /*  873 */ 0xFFFF,                /* TrcContainObj */
  /*  874 */ 0xFFFF,                /* BlobAufbereiten */
  /*  875 */ 0xFFFF,                /* DatenVomBlob */
  /*  876 */ 0xFFFF,                /* Trc_DefContain2 */
  /*  877 */ 0xFFFF,                /* RemoveFromBlob */
  /*  878 */ 0xFFFF,                /* ErsteDatenVomBlob */
  /*  879 */ 0xFFFF,                /* WeitereDatenVomBlob */
  /*  880 */ VAR_DEC,               /* StatFunc */
  /*  881 */ 0xFFFF,                /* SetNoAutoScroll */
  /*  882 */ 0xFFFF,                /* GetLastCommError */
  /*  883 */ 0xFFFF,                /* TestDllProc */
  /*  884 */ VAR_DEC,               /* GetResFactor */
  /*  885 */ 0xFFFF,                /* CommSignalStatus */
  /*  886 */ 0xFFFF,                /* CommEscape */
  /*  887 */ 0xFFFF,                /* DenyNormalCursor */
  /*  888 */ 0xFFFF,                /* GetScriptEntry */
  /*  889 */ 0xFFFF,                /* lSetUpCallBack */
  /*  890 */ 0xFFFF,                /* SetOLEDocVar */
  /*  891 */ 0xFFFF,                /* GetOLEDocVar */
  /*  892 */ 0xFFFF,                /* OLEPrint */
  /*  893 */ 0xFFFF,                /* GetTableID */
  /*  894 */ 0xFFFF,                /* GetMyIUnknown */
  /*  895 */ 0xFFFF,                /* GetOLEDocProp */
  /*  896 */ 0xFFFF,                /* OLEUpdateFields */
  /*  897 */ 0xFFFF,                /* OLERestrictInput */
  /*  898 */ 0xFFFF,                /* OLESetHostName */
  /*  899 */ VAR_DATETIME,          /* MakeDateTime */
  /*  900 */ VAR_DATE,              /* GetDateFromDateTime */
  /*  901 */ VAR_TIME,              /* GetTimeFromDateTime */
  /*  902 */ 0xFFFF,                /* bCmpDateTime */
  /*  903 */ 0xFFFF,                /* SetPrinterCaption */
  /*  904 */ 0xFFFF,                /* InsertStrAtCaretObj   */
  /*  905 */ 0xFFFF,                /* InsertStrAtCaretTool  */
  /*  906 */ 0xFFFF,                /* CreateMemoryFile */
  /*  907 */ 0xFFFF,                /* ReadMemoryFile */
  /*  908 */ 0xFFFF,                /* WriteMemoryFile */
  /*  909 */ 0xFFFF,                /* PostWinMessage */
  /*  910 */ 0xFFFF,                /* HaltQueue */
  /*  911 */ 0xFFFF,                /* ResumeQueue */
  /*  912 */ 0xFFFF,                /* CallDllProcDynamic */
  /*  913 */ VAR_OBJ,               /* PushDataMit */
  /*  914 */ 0xFFFF,                /* NetListen */
  /*  915 */ 0xFFFF,                /* NetAccept */
  /*  916 */ 0xFFFF,                /* NetConnect */
  /*  917 */ 0xFFFF,                /* NetReceive */
  /*  918 */ VAR_STRARR,            /* NetSend */
  /*  919 */ 0xFFFF,                /* NetWorkAddressStrToBin */
  /*  920 */ VAR_STR,               /* NetWorkAddressBinToStr */
  /*  921 */ VAR_STRARR,            /* NetStatus */
  /*  922 */ VAR_LONG,              /* NetError */
  /*  923 */ 0xFFFF,                /* ColorObjSelection */
  /*  924 */ 0xFFFF,                /* ColorToolSelection */
  /*  925 */ 0xFFFF,                /* GetObjColor */
  /*  926 */ 0xFFFF,                /* GetToolColor */
  /*  927 */ 0xFFFF,                /* ExchangeEscape  */
  /*  928 */ 0xFFFF,                /* ReexchangeEscape */
  /*  929 */ 0xFFFF,                /* DataWithName */
  /*  930 */ 0xFFFF,                /* GetSystemPath */
  /*  931 */ 0xFFFF,                /* SetUserName */
  /*  932 */ 0xFFFF,                /* WindowsEvent */
  /*  933 */ 0xFFFF,                /* SetErrorref */
  /*  934 */ 0xFFFF,                /* CreateDir */
  /*  935 */ 0xFFFF,                /* Wait */
  /*  936 */ 0xFFFF,                /* ShowFormMultiComboInnerList */
  /*  937 */ 0xFFFF,                /* ShowToolMultiComboInnerList */
  /*  938 */ 0xFFFF,                /* DBCall_FormComboObjList */
  /*  939 */ 0xFFFF,                /* DBCall_ToolComboObjList */
  /*  940 */ 0xFFFF,                /* DBCall_FormMultiComboObjList */
  /*  941 */ 0xFFFF,                /* DBCall_ToolMultiComboObjList */
  /*  942 */ 0xFFFF,                /* ShowFormComboInnerListObjList */
  /*  943 */ 0xFFFF,                /* ShowToolComboInnerObjList */
  /*  944 */ 0xFFFF,                /* ShowFormMultiComboInnerObjList */
  /*  945 */ 0xFFFF,                /* ShowToolMultiComboInnerObjList */
  /*  946 */ 0xFFFF,                /* RefreshDlgList */
  /*  947 */ 0xFFFF,                /* DenyDlgClose */
  /*  948 */ 0xFFFF,                /* SetDlgText */
  /*  949 */ 0xFFFF,                /* CheckBuffer */
  /*  950 */ 0xFFFF,                /* CloseSpell */
  /*  951 */ 0xFFFF,                /* SpellSuggestion */
  /*  952 */ 0xFFFF,                /* SpellAnagramm */
  /*  953 */ 0xFFFF,                /* SpellWidlcard */
  /*  954 */ 0xFFFF,                /* SpellSetOptions */
  /*  955 */ 0xFFFF,                /* SpellGetOptions */
  /*  956 */ 0xFFFF,                /* SpellOpenUserDictionary */
  /*  957 */ 0xFFFF,                /* SpellAddToUserDictionary */
  /*  958 */ 0xFFFF,                /* SpellDelFromUserDictionary */
  /*  959 */ 0xFFFF,                /* SpellCloseUserDictionary */
  /*  960 */ 0xFFFF,                /* SpellAddToRAMCacheList */
  /*  961 */ 0xFFFF,                /* SpellDelFromRAMCacheList */
  /*  962 */ 0xFFFF,                /* SpellClearRAMCacheList */
  /*  963 */ 0xFFFF,                /* HtmlHelpInit */
  /*  964 */ 0xFFFF,                /* CallHtmlHelp */
  /*  965 */ VAR_DEC,               /* usqrt */
  /*  966 */ 0xFFFF,                /* SetDDSCapture */
  /*  967 */ 0xFFFF,                /* InstallProcedure */
  /*  968 */ 0xFFFF,                /* FireProcedure */
  /*  969 */ 0xFFFF,                /* SetDocVeryBestWith */
  /*  970 */ 0xFFFF,                /* TagesAuslastung */
  /*  971 */ 0xFFFF,                /* RunAutomacro */
  /*  972 */ VAR_STR,               /* GetFrmFieldText */
  /*  973 */ 0xFFFF,                /* SetSelection */
  /*  974 */ 0xFFFF,                /* ChangeSelection */
  /*  975 */ 0xFFFF,                /* WaitForSingleObject */
  /*  976 */ 0xFFFF,                /* CreateAllTables */
  /*  977 */ 0xFFFF,                /* SetFeierTag */
  /*  978 */ 0xFFFF,                /* ClearFeierTage */
  /*  979 */ 0xFFFF,                /* IsInTransactionProc */
  /*  980 */ 0xFFFF,                /* ShowPopupMenu */
  /*  981 */ 0xFFFF,                /* PrintOleObjectFromBlob */
  /*  982 */ 0xFFFF,                /* CloseApplicationWord */
  /*  983 */ 0xFFFF,                /* SaveWordObjectAs */
  /*  984 */ 0xFFFF,                /* AddBlobToBlob */
  /*  985 */ 0xFFFF,                /* ExtractDataFromBlob */
  /*  986 */ 0xFFFF,                /* ExtractBlob */
  /*  987 */ 0xFFFF,                /* NetSendBlob */
  /*  988 */ 0xFFFF,                /* bBlobEqual */
  /*  989 */ VAR_LONG,              /* GetHelpPrefix */
  /*  990 */ 0xFFFF,                /* SetObjInfo */
  /*  991 */ VAR_STR,               /* GetObjInfo */
  /*  992 */ VAR_OBJ,               /* GetObjContext */
  /*  993 */ VAR_STR,               /* GetLastErrorText */
  /*  994 */ VAR_OBJ,               /* BlockCopy */
  /*  995 */ 0xFFFF,                /* ForcePageBreak */
  /*  996 */ 0xFFFF,                /* MoveBlobData */
  /*  997 */ VAR_OBJ,               /* GetClientWindowHandle */
  /*  998 */ 0xFFFF,                /* ClientExtWindow */
  /*  999 */ 0xFFFF,                /* lInnerUpdate */
  /* 1000 */ 0xFFFF,                /* SetFocusToSubDoc */
  /* 1001 */ 0xFFFF,                /* MultiComboReset */
  /* 1002 */ 0xFFFF,                /* Random */
  /* 1003 */ 0xFFFF,                /* DBCall_Parse */
  /* 1004 */ 0xFFFF,                /* Ltx */
  /* 1005 */ 0xFFFF,                /* SetNetWorkSubAddressID */
  /* 1006 */ 0xFFFF,                /* DirSelector_Box */
  /* 1007 */ 0xFFFF,                /* ChooseColorDialog */
  /* 1008 */ 0xFFFF,                /* SetDBLogState */
  /* 1009 */ 0xFFFF,                /* Code128bc */
  /* 1010 */ VAR_OBJ,               /* Jmethod VAR_OBJ */
  /* 1011 */ VAR_STR,               /* Jmethod VAR_STR */
  /* 1012 */ VAR_STRARR,            /* Jmethod VAR_STRARR */
  /* 1013 */ VAR_LONG,              /* Jmethod VAR_LONG */
  /* 1014 */ VAR_FLAG,              /* Jmethod VAR_FLAG */
  /* 1015 */ VAR_DEC,               /* Jmethod VAR_DEC */
  /* 1016 */ VAR_QLONG,             /* Jmethod VAR_QLONG */
  /* 1017 */ VAR_DATE,              /* Jmethod VAR_DATE '/
  /* 1018 */ VAR_DATETIME,          /* Jmethod VAR_DATETIME */
  /* 1019 */ VAR_OBJ,               /* Jstaticmethod VAR_OBJ */
  /* 1020 */ VAR_STR,               /* Jstaticmethod VAR_STR */
  /* 1021 */ VAR_STRARR,            /* Jstaticmethod VAR_STRARR */
  /* 1022 */ VAR_LONG,              /* Jstaticmethod VAR_LONG */
  /* 1023 */ VAR_FLAG,              /* Jstaticmethod VAR_FLAG */
  /* 1024 */ VAR_DEC,               /* Jstaticmethod VAR_DEC */
  /* 1025 */ VAR_QLONG,             /* Jstaticmethod VAR_QLONG */
  /* 1026 */ VAR_DATE,              /* Jstaticmethod VAR_DATE */
  /* 1027 */ VAR_DATETIME,          /* Jstaticmethod VAR_DATETIME */
  /* 1028 */ VAR_OBJ,               /* Jnew */
  /* 1029 */ 0xFFFF,                /* Jdelete */
  /* 1030 */ VAR_OBJ,               /* Jnewstring */
  /* 1031 */ 0xFFFF,                /* Jstartvm */
  /* 1032 */ 0xFFFF,                /* Jdestroyvm */
  /* 1033 */ VAR_OBJ,               /* Jmethodparallel VAR_OBJ */
  /* 1034 */ VAR_STR,               /* Jmethodparallel VAR_STR */
  /* 1035 */ VAR_STRARR,            /* Jmethodparallel VAR_STRARR */
  /* 1036 */ VAR_LONG,              /* Jmethodparallel VAR_LONG */
  /* 1037 */ VAR_FLAG,              /* Jmethodparallel VAR_FLAG */
  /* 1038 */ VAR_DEC,               /* Jmethodparallel VAR_DEC */
  /* 1039 */ VAR_QLONG,             /* Jmethodparallel VAR_QLONG */
  /* 1040 */ VAR_DATE,              /* Jmethodparallel VAR_DATE */
  /* 1041 */ VAR_DATETIME,          /* Jmethodparallel VAR_DATETIME */
  /* 1042 */ 0xFFFF,                /* Jcatchexception */
  /* 1043 */ 0xFFFF,                /* Jlogexception */
  /* 1044 */ 0xFFFF,                /* Jinstanceof */
  /* 1045 */ 0xFFFF,                /* Jmethodexists */
  /* 1046 */ 0xFFFF,                /* Jstaticmethodexists */
  /* 1047 */ VAR_LONG,              /* Jgetarraylength */
  /* 1048 */ VAR_OBJ,               /* Jgetobjarrayelement */
  /* 1049 */ 0xFFFF,                /* Jsetreplacemode */
  /* 1050 */ 0xFFFF,                /* JBmethodexists */
  /* 1051 */ 0xFFFF,                /* JBstaticmethodexists */
  /* 1052 */ 0xFFFF                 /* JavaReferencesInc */
  };

#else
extern DDSFUNC ddsfunc[];
extern WORD mTypesForCmd[];
#endif
