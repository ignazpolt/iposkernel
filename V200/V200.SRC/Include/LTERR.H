/*
   LTERR.H - global error codes
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTERR_H_
#define _LTERR_H_

#include "ltsys.h"

#define SUCCESS_ABORT                    2   /** Function successful. You can quit now. **/
#define SUCCESS                          1   /** Function successful        **/
#define FAILURE                          0   /** Function not successful    **/

#define ERROR_NO_MEMORY                 -1   /** Not enough memory available**/
#define ERROR_NO_BITMAP                 -2   /** Invalid bitmap handle      **/
#define ERROR_MEMORY_TOO_LOW            -3   /** Not enough memory available**/
#define ERROR_FILE_LSEEK                -4   /** Error seeking to position  **/
#define ERROR_FILE_WRITE                -5   /** Error writing file         **/
#define ERROR_FILE_GONE                 -6   /** File not present - abort   **/
#define ERROR_FILE_READ                 -7   /** Error reading file         **/
#define ERROR_INV_FILENAME              -8   /** Invalid filename specified **/
#define ERROR_FILE_FORMAT               -9   /** Invalid file format        **/
#define ERROR_FILENOTFOUND              -10  /** File not found             **/
#define ERROR_INV_RANGE                 -11  /** Invalid width/height       **/
#define ERROR_IMAGE_TYPE                -12  /** Image format recognized,   **/
                                             /** but sub-type not supported **/
#define ERROR_INV_PARAMETER             -13  /** Invalid parmameter passed  **/
#define ERROR_FILE_OPEN                 -14  /** Not able to open file      **/
#define ERROR_UNKNOWN_COMP              -15  /** Unknown compression format **/
#define ERROR_FEATURE_NOT_SUPPORTED     -16  /** Feature not supported      **/
#define ERROR_NOT_256_COLOR             -17  /** VGA card only supports 256 **/
                                             /** colors (8 bit)             **/
#define ERROR_PRINTER                   -18  /** Printer error              **/
#define ERROR_CRC_CHECK                 -19  /** Data CRC check error       **/
#define ERROR_QFACTOR                   -21  /** Invalid QFactor specified  **/
#define ERROR_TARGAINSTALL              -22  /** TARGA not installed        **/
#define ERROR_OUTPUTTYPE                -23  /** Invalid compression format **/
#define ERROR_XORIGIN                   -24  /** X origin specified invalid **/
#define ERROR_YORIGIN                   -25  /** Y origin specified invalid **/
#define ERROR_VIDEOTYPE                 -26  /** Invalid video mode         **/
#define ERROR_BITPERPIXEL               -27  /** Invalid bits/pixel         **/
#define ERROR_WINDOWSIZE                -28  /** Invalid window size        **/
#define ERROR_NORMAL_ABORT              -29  /** Escape key pressed         **/
#define ERROR_NOT_INITIALIZED           -30  /** Internal error - call LEAD **/
#define ERROR_CU_BUSY                   -31  /** Internal error - call LEAD **/
#define ERROR_INVALID_TABLE_TYPE        -32  /** Internal error - call LEAD **/
#define ERROR_UNEQUAL_TABLES            -33  /** Internal error - call LEAD **/
#define ERROR_INVALID_BUFFER            -34  /** Internal error - call LEAD **/
#define ERROR_MISSING_TILE_DATA         -35  /** Internal error - call LEAD **/
#define ERROR_INVALID_QVALUE            -36  /** Internal error - call LEAD **/
#define ERROR_INVALIDDATA               -37  /** Internal error - call LEAD **/
#define ERROR_INVALID_COMPRESSED_TYPE   -38  /** Internal error - call LEAD **/
#define ERROR_INVALID_COMPONENT_NUM     -39  /** Internal error - call LEAD **/
#define ERROR_INVALID_PIXEL_TYPE        -40  /** Internal error - call LEAD **/
#define ERROR_INVALID_PIXEL_SAMPLING    -41  /** Internal error - call LEAD **/
#define ERROR_INVALID_SOURCE_FILE       -42  /** Internal error - call LEAD **/
#define ERROR_INVALID_TARGET_FILE       -43  /** Internal error - call LEAD **/
#define ERROR_INVALID_IMAGE_DIMS        -44  /** Internal error - call LEAD **/
#define ERROR_INVALID_TILE_DIMS         -45  /** Internal error - call LEAD **/
#define ERROR_INVALID_PIX_BUFF_DIMS     -46  /** Internal error - call LEAD **/
#define ERROR_SEGMENT_OVERFLOW          -47  /** Internal error - call LEAD **/
#define ERROR_INVALID_SUBSAMPLING       -48  /** Internal error - call LEAD **/
#define ERROR_INVALID_Q_VIS_TABLE       -49  /** Internal error - call LEAD **/
#define ERROR_INVALID_DC_CODE_TABLE     -50  /** Internal error - call LEAD **/
#define ERROR_INVALID_AC_CODE_TABLE     -51  /** Internal error - call LEAD **/
#define ERROR_INSUFFICIENT_DATA         -52  /** Internal error - call LEAD **/
#define ERROR_MISSING_FUNC_POINTER      -53  /** Internal error - call LEAD **/
#define ERROR_TOO_MANY_DC_CODE_TABLES   -54  /** Internal error - call LEAD **/
#define ERROR_TOO_MANY_AC_CODE_TABLES   -55  /** Internal error - call LEAD **/
#define ERROR_INVALID_SUBIMAGE          -56  /** Internal error - call LEAD **/
#define ERROR_INVALID_ABORTION          -57  /** Internal error - call LEAD **/
#define ERROR_CU_NO_SUPPORT             -58  /** Internal error - call LEAD **/
#define ERROR_CU_FAILURE                -59  /** Internal error - call LEAD **/
#define ERROR_BAD_POINTER               -60  /** Internal error - call LEAD **/
#define ERROR_HEADER_DATA_FAILURE       -61  /** Internal error - call LEAD **/
#define ERROR_COMPRESSED_DATA_FAILURE   -62  /** Internal error - call LEAD **/

#define ERROR_FIXEDPAL_DATA             -63  /** fixed palette data not found **/
#define ERROR_LOADFONT_DATA             -64  /** fixed palette data not found **/
#define ERROR_NO_STAMP                  -65  /** stamp not found **/
#define ERROR_G3CODE_INVALID            -70  /** invalid group 3 dat **/
#define ERROR_G3CODE_EOF                -71  /** group3 code end of file **/
#define ERROR_G3CODE_EOL                -72  /** group3 code end of code **/
#define ERROR_PREMATURE_EOF             -73  /** premature EOF at scanline **/
#define ERROR_PREMATURE_EOL             -74  /** premature end-of-line code **/
#define ERROR_UNCOMP_EOF                -75  /** premature end-of-line code **/
#define ERROR_ACT_INCOMP                -76  /** premature end-of-line code **/
#define ERROR_BAD_DECODE_STATE          -77  /** premature end-of-line code **/
#define ERROR_VERSION_NUMBER            -78  /** bad version number **/
#define ERROR_TWAIN_NODSM               -79  /** source manager not found **/
#define ERROR_TWAIN_BUMMER              -80  /** Failure due to unknown causes **/
#define ERROR_TWAIN_LOWMEMORY           -81  /** Not enough memory to perform operation **/
#define ERROR_TWAIN_NODS                -82  /** No Data Source **/
#define ERROR_TWAIN_MAXCONNECTIONS      -83  /** DS is connected to max possible apps **/
#define ERROR_TWAIN_OPERATIONERROR      -84  /** DS or DSM reported error, app shouldn't **/
#define ERROR_TWAIN_BADCAP              -85  /** Unknown capability **/
#define ERROR_TWAIN_BADPROTOCOL         -86  /** Unrecognized MSG DG DAT combination **/
#define ERROR_TWAIN_BADVALUE            -87  /** Data parameter out of range **/
#define ERROR_TWAIN_SEQERROR            -88  /** DG DAT MSG out of expected sequence **/
#define ERROR_TWAIN_BADDEST             -89  /** Unknown destination App/Src in DSM_Entry **/
#define ERROR_TWAIN_CANCEL              -90  /** Operation was cancelled **/
#define ERROR_PANWINDOW_NOT_CREATED     -91  /** PanWindow was not created **/

#define ERROR_USER_ABORT               -100  /** User has aborted operation **/

#define ERROR_FPX_INVALID_FORMAT_ERROR       -101  /** FlashPix errors */
#define ERROR_FPX_FILE_WRITE_ERROR           -102
#define ERROR_FPX_FILE_READ_ERROR            -103
#define ERROR_FPX_FILE_NOT_FOUND             -104
#define ERROR_FPX_COLOR_CONVERSION_ERROR     -105
#define ERROR_FPX_SEVER_INIT_ERROR           -106
#define ERROR_FPX_LOW_MEMORY_ERROR           -107
#define ERROR_FPX_IMAGE_TOO_BIG_ERROR        -108
#define ERROR_FPX_INVALID_COMPRESSION_ERROR  -109
#define ERROR_FPX_INVALID_RESOLUTION         -110
#define ERROR_FPX_INVALID_FPX_HANDLE         -111
#define ERROR_FPX_TOO_MANY_LINES             -112
#define ERROR_FPX_BAD_COORDINATES            -113
#define ERROR_FPX_FILE_SYSTEM_FULL           -114
#define ERROR_FPX_MISSING_TABLE              -115
#define ERROR_FPX_RETURN_PARAMETER_TOO_LARGE -116
#define ERROR_FPX_NOT_A_VIEW                 -117
#define ERROR_FPX_VIEW_IS_TRANFORMLESS       -118
#define ERROR_FPX_ERROR                      -119
#define ERROR_FPX_UNIMPLEMENTED_FUNCTION     -120
#define ERROR_FPX_INVALID_IMAGE_DESC         -121
#define ERROR_FPX_INVALID_JPEG_TABLE         -122
#define ERROR_FPX_ILLEGAL_JPEG_ID            -123
#define ERROR_FPX_MEMORY_ALLOCATION_FAILED   -124
#define ERROR_FPX_NO_MEMORY_MANAGEMENT       -125
#define ERROR_FPX_OBJECT_CREATION_FAILED     -126
#define ERROR_FPX_EXTENSION_FAILED           -127
#define ERROR_FPX_FREE_NULL_PTR              -128
#define ERROR_FPX_INVALID_TILE               -129
#define ERROR_FPX_FILE_IN_USE                -130
#define ERROR_FPX_FILE_CREATE_ERROR          -131
#define ERROR_FPX_FILE_NOT_OPEN_ERROR        -132
#define ERROR_FPX_USER_ABORT                 -133
#define ERROR_FPX_OLE_FILE_ERROR             -134

#define ERROR_BAD_TAG                        -140 /* Bad TIFF tag */
#define ERROR_INVALID_STAMP_SIZE             -141 /* stamp size is too big or invalid bits/pixel, etc */
#define ERROR_BAD_STAMP                      -142 /* Stamp is present but data is corrupted  */
#define ERROR_EXPRESS_NOT_ENABLED            -143 /* Document Express capability is required to use this function */
#define ERROR_IMAGE_EMPTY                    -144 /* Image is empty */
#define ERROR_NO_CHANGE                      -145 /* The image hasn't changed */
#define ERROR_LZW_LOCKED                     -146 /* LZW is locked */
#define ERROR_FPXEXTENSIONS_LOCKED           -147 /* FPX Extensions is locked */
#define ERROR_ANN_LOCKED                     -148 /* the annotation object is locked */
#define ERROR_EXCEPTION                      -149 /* an unspecified exception occured - could be memory access violations */

#define ERROR_DLG_CANCELED                   -150 /* common dialog was canceled by user */
#define ERROR_DLG_FAILED                     -151 /* an error occured during creation of the common dialog */

#define ERROR_ISIS_NOCURSCANNER              -160   /* No ISIS Scanner selected */
#define ERROR_ISIS_SCANDRIVER_NOT_LOADED     -161   /* ISIS Scanner driver failed to load */
#define ERROR_ISIS_CANCEL                    -162   /* ISIS operation canceled */
#define ERROR_ISIS_BAD_TAG_OR_VALUE          -163   /* Bad ISIS Tag or Bad Tag Value */
#define ERROR_ISIS_NOT_READY                 -164   /* ISIS Scanner not ready */
#define ERROR_ISIS_NO_PAGE                   -165   /* No page in the ISIS Scanner */
#define ERROR_ISIS_JAM                       -166   /* ISIS Scanner Jam error */
#define ERROR_ISIS_SCANNER_ERROR             -167   /* ISIS Scanner driver rror */
#define ERROR_ISIS_BUSY                      -168   /* ISIS Scanner is busy */
#define ERROR_ISIS_FILE_ERROR                -169   /* ISIS File driver error */
#define ERROR_ISIS_NETWORK_ERROR             -170   /* ISIS Network error */
#define ERROR_ISIS_NOT_INSTALLED             -171   /* ISIS is not installed */

#define ERROR_DOC_NOT_INITIALIZED            -180
#define ERROR_DOC_HANDLE                     -181
#define ERROR_DOC_EMPTY                      -182
#define ERROR_DOC_INVALID_FONT               -183
#define ERROR_DOC_INVALID_PAGE               -184
#define ERROR_DOC_INVALID_RULE               -185
#define ERROR_DOC_INVALID_ZONE               -186
#define ERROR_DOC_TYPE_ZONE                  -187
#define ERROR_DOC_INVALID_COLUMN             -188
#define ERROR_DOC_INVALID_LINE               -189
#define ERROR_DOC_INVALID_WORD               -190
#define ERROR_OCR_LOCKED                     -191  /* OCR is locked */
#define ERROR_OCR_NOT_INITIALIZED            -192
#define ERROR_OCR_MAX_REGIONS                -193
#define ERROR_OCR_OPTION                     -194
#define ERROR_OCR_CONVERT_DIB                -195
#define ERROR_OCR_CANCELED                   -196
#define ERROR_OCR_INVALID_OUTPUT             -197
#define ERROR_OCR_BLOCKED                    -198
#define ERROR_OCR_RPCMEM                     -199  /* These errors are used internally only by API code */
#define ERROR_OCR_FATAL                      -200  /* Fatal condition detected call technical support */
#define ERROR_OCR_BADTAG                     -201  /* Bad tag in tag value set */
#define ERROR_OCR_BADVAL                     -202  /* Value bad or out of range */
#define ERROR_OCR_BADTYPE                    -203  /* Wrong type used to make IO_TOKEN_T */
#define ERROR_OCR_NOFILE                     -204  /* Cannot access specified file */
#define ERROR_OCR_BADTOK                     -205  /* invalid IO_TOKEN_T */
#define ERROR_OCR_BADFMT                     -206  /* Invalid input format */
#define ERROR_OCR_BADMATCH                   -207  /* Image incompatible with IO_TOKEN_T */
#define ERROR_OCR_NOSUPPORT                  -208  /* Param combination not supported or file format legal but not supported */
#define ERROR_OCR_BADID                      -209  /* Invalid index for language/lexicon */
#define ERROR_OCR_NOLANG                     -210  /* Language not loaded/installed */
#define ERROR_OCR_LANGOVFL                   -211  /* Too many langauge packs, remove one */
#define ERROR_OCR_NOISRC                     -212  /* No image source declared */
#define ERROR_OCR_NOTIDL                     -213  /* ICR must be idle to make this call */
#define ERROR_OCR_NOVER                      -214  /* ICR not blocked on verification */
#define ERROR_OCR_NODRAW                     -215  /* ICR not blocked on  progress draw */
#define ERROR_OCR_MEMERR                     -216  /* ICR process memory error */
#define ERROR_OCR_BADRGN                     -217  /* Region index error */
#define ERROR_OCR_NOICR                      -218  /* Server not found or down */
#define ERROR_OCR_NOACTV                     -219  /* There are no active io_tokens in API */
#define ERROR_OCR_NOMORE                     -220  /* Nothing (more) to read */
#define ERROR_OCR_NOTWAIT                    -221  /* ICR must be waiting to make this call */
#define ERROR_OCR_LEXOVFL                    -222  /* Too many lexicons, remove one */
#define ERROR_OCR_PREPROC                    -223  /* Bitmap preprocessing failed */
#define ERROR_OCR_BADFILE                    -224  /* Bad file or file content associated with the passed IO_TOKEN_T */
#define ERROR_OCR_BADSCAN                    -225  /* Scanner failure */
#define ERROR_OCR_NOIMG                      -226  /* Preprocessing, Recognition, or region retrieval with no image */
#define ERROR_OCR_NOLICN                     -227  /* Licensed version of API could not acquire a license from server */
#define ERROR_OCR_NOLCSRV                    -228  /* Licensed version of API could not find license server */
#define ERROR_OCR_LMEMERR                    -229  /* Local (API library) memory error */
#define ERROR_OCR_RESCHNG                    -230  /* Image resolution change within a document too many times */
#define ERROR_OCR_BADPLGN                    -231  /* Bad Polygon used to define region extents; probably beyond the dimensions of the source image or bad vertices. */
#define ERROR_OCR_NOSINK                     -232  /* no sink token available for use with regions et. al. */
#define ERROR_OCR_NOSRC                      -233  /* no source token available for use with user defined input et. al. */
#define ERROR_OCR_NOTOK                      -234  /* unable to specify token to unblock ICR - user managed I/O "_APP" */
#define ERROR_OCR_IMBUFOVFL                  -235  /* image buffer full/overflow */
#define ERROR_OCR_TMOUT                      -236  /* timeout error on IPC to server */
#define ERROR_OCR_BADVRS                     -237  /* Server is for wrong version */
#define ERROR_OCR_TAGNNW                     -238  /* Tag cannot have value changed at this time */
#define ERROR_OCR_SRVCAN                     -239  /* Server cancelled processing on its initiative - page may be too complex for selected mode */
#define ERROR_OCR_WRFAIL                     -240  /* I/O write failed (no space) */
#define ERROR_OCR_SCNCAN                     -241  /* Scan canceled by user at scanner (using button or Scanner UI) */
#define ERROR_OCR_RGOCCLD                    -242  /* Region is totally occluded */
#define ERROR_OCR_NOTORNT                    -243  /* Could not orient text */
#define ERROR_OCR_ACCDEN                     -244  /* Access denied to this feature see your sales rep. */
#define ERROR_OCR_BADUOR                     -245  /* Invalid UOR passed to the server */

#define ERROR_RECORDING                      -250  /* wave device is currently recording */
#define ERROR_COMPRESSOR                     -251  /* invalid compressor */
#define ERROR_SOUND_DEVICE                   -252  /* problem with sound card */
#define ERROR_DEVICE_INUSE                   -253  /* the sound card is currently in use */
#define ERROR_INV_TRACKTYPE                  -254  /* invalid track for operation */
#define ERROR_NO_SOUNDCARD                   -255  /* no sound card is presend */
#define ERROR_NOT_RECORDING                  -256  /* not currently recording */
#define ERROR_INV_MODE                       -257  /* invalid open mode for operation */
#define ERROR_NO_VIDEO_MODULE                -258  /* no video module present on machine */
#define ERROR_QUEUE_FULL                     -259  /* the buffer queue is full */

#define ERROR_HOST_RESOLVE                   -270
#define ERROR_CANT_INITIALIZE                -271
#define ERROR_NO_CONNECTION                  -272
#define ERROR_HOST_NOT_FOUND                 -273
#define ERROR_NOT_SERVER                     -274
#define ERROR_NO_CONNECTIONS                 -275
#define ERROR_CONNECT_REFUSED                -276
#define ERROR_IS_CONNECTED                   -277  /* computer is already connected */
#define ERROR_NET_UNREACH                    -278  /* network is unreachable from host */
#define ERROR_TIME_OUT                       -279  /* connect attempt time out without connecting */
#define ERROR_NET_DOWN                       -280  /* network subsystem is down */
#define ERROR_NO_BUFFERS                     -281  /* no buffer space is available, to many connections*/
#define ERROR_NO_FILE_DESCR                  -282  /* no more file handle available */
#define ERROR_DATA_QUEUED                    -283  /* data has been queued to send later */
#define ERROR_UNKNOWN                        -284  /* unkown network error has occured */
#define ERROR_CONNECT_RESET                  -285  /* connection was reset - socket might be unusable */
#define ERROR_TRANSFER_ABORTED               -286  /* transfer was aborted */

#define ERROR_DSHOW_FAILURE                  -287  /* DirectShow isn't installed correctly */

#define ERROR_REGISTRY_READ                  -288  /* Error reading from the registry */
#define ERROR_WAVE_FORMAT                    -289  /* The wave format is not supported */
#define ERROR_INSUFICIENT_BUFFER             -290  /* The buffer size is too small */
#define ERROR_WAVE_CONVERT                   -291  /* Error converting the wave format */
#define ERROR_VIDEO_LOCKED                   -292  /* Video capabilities not unlocked */

#define ERROR_CAP_CONNECT                    -293  /* error connecting to capture device */
#define ERROR_CAP_DISCONNECT                 -294  /* error disconnecting capture device */
#define ERROR_DISK_ISFULL                    -295  /* not enough disk space */
#define ERROR_CAP_OVERLAY                    -296  /* error setting capture overlay */
#define ERROR_CAP_PREVIEW                    -297  /* error setting capture preview */
#define ERROR_CAP_COPY                       -298  /* error copying to clipboard */
#define ERROR_CAP_WINDOW                     -299  /* error with capture window */
#define ERROR_CAP_ISCAPTURING                -300  /* operation invalid during capture */
#define ERROR_NO_STREAMS                     -301  /* no streams to play */
#define ERROR_CREATE_STREAM                  -302  /* error creating streams */
#define ERROR_FRAME_DELETE                   -303  /* error deleting frames */

#define ERROR_PAGE_NOT_FOUND                 -310  /* Page not found */
#define ERROR_DELETE_LAST_PAGE               -311  /* You cannot delete a page from a file containing only one page */
#define ERROR_NO_HOTKEY                      -312  /* There is no hotkey */
#define ERROR_CANNOT_CREATE_HOTKEY_WINDOW    -313  /* Error creating the hotkey window */
#define ERROR_MEDICAL_NOT_ENABLED            -314  /* Medical Express capability is required to use this function */

#define ERROR_CAPTURE_STILL_IN_PROCESS          -320
#define ERROR_INVALID_DELAY                     -321  /* the user passed an invalid delay value */
#define ERROR_INVALID_COUNT                     -322  /* the user passed an invalid capture count */
#define ERROR_INVALID_INTERVAL                  -323  /* the user passed an invalid interval value */
#define ERROR_HOTKEY_CONFILCTS_WITH_CANCELKEY   -324  /* the user specified the hotkey to be the same as the cancel key */
#define ERROR_CAPTURE_INVALID_AREA_TYPE         -325  /* wrong area type passed to L_CaptureArea() */
#define ERROR_CAPTURE_NO_OPTION_STRUCTURE       -326  /* invalid options structure pointer */
#define ERROR_CAPTURE_INVALID_FILL_PATTERN      -327  /* invalid fill pattern */
#define ERROR_CAPTURE_INVALID_LINE_STYLE        -328
#define ERROR_CAPTURE_INVALID_INFOWND_POS       -329
#define ERROR_CAPTURE_INVALID_INFOWND_SIZE      -330
#define ERROR_CAPTURE_ZERO_AREA_SIZE            -331
#define ERROR_CAPTURE_FILE_ACCESS_FAILED        -332  /* The specified filename couldn't be read */
#define ERROR_CAPTURE_INVALID_32BIT_EXE_OR_DLL  -333  /* The specified filename is not a valid 32bit EXE/DLL */
#define ERROR_CAPTURE_INVALID_RESOURCE_TYPE     -334  /* The specified resource type is not supported */
#define ERROR_CAPTURE_INVALID_RESOURCE_INDEX    -335  /* The index resource is out of range */
#define ERROR_CAPTURE_NO_ACTIVE_WINDOW          -336
#define ERROR_CAPTURE_CANNOT_CAPTURE_WINDOW     -337
#define ERROR_CAPTURE_STRING_ID_NOT_DEFINED     -338
#define ERROR_CAPTURE_DELAY_LESS_THAN_ZERO      -339
#define ERROR_CAPTURE_NO_MENU                   -340

#endif                          /* _LTERR_H_ */
