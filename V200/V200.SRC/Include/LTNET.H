/*
   LTNET.H - internet module header file
   Copyright (c) 1991-1998 by LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTNET_H_
#define _LTNET_H_

#include "ltkrn.h"

#define _HEADER_ENTRY_
#include "ltpck.h"   

#ifndef WIN32
#include <compobj.h>
#endif

#include "ltcap.h"

typedef L_UINT  L_COMP;     // handle to a connected computer

/************************************************************************************
 *                                                                                  *
 *                  Internet Messages                                               *
 *                                                                                  *
 ************************************************************************************/

#define INET_CONNECT          0  /* connected to remote computer                    */
#define INET_DATA_READY       1  /* data ready to be read                           */
#define INET_CLOSE            2  /* connection has been terminated                  */
#define INET_CONNECT_REQUEST  3  /* remote computer is requesting a connections     */
#define INET_DATA_SENT        4  /* data has been completely send to remote         */
#define INET_DATA_SENDING     5  /* lets user know that queued data has been sent   */
#define INET_DATA_START       6  /* about to start receiving data                   */
#define INET_DATA_RECEIVING   7  /* receiving data from a remote connection         */
#define INET_IMAGE_RECEIVED   8  /* an image has been received                      */
#define INET_MMEDIA_RECEIVED  9  /* a multimedia object has been received           */
#define INET_SOUND_RECEIVED   10 /* sound data has been received                    */
#define INET_USER1_RECEIVED   11 /* user data has been received                     */
#define INET_USER2_RECEIVED   12 /* user data has been received                     */
#define INET_USER3_RECEIVED   13 /* user data has been received                     */
#define INET_USER4_RECEIVED   14 /* user data has been received                     */

/************************************************************************************
 *                                                                                  *
 *                  Internet Data types                                             *
 *                                                                                  *
 ************************************************************************************/

#define IDATA_IMAGE  0  /* image data           */
#define IDATA_MMEDIA 1  /* multimedia object    */
#define IDATA_SOUND  2  /* multimedia object    */
#define IDATA_USER1  3  /* user data            */
#define IDATA_USER2  4  /* user data            */
#define IDATA_USER3  5  /* user data            */
#define IDATA_USER4  6  /* user data            */
#define IDATA_LAST   7  /* first invalid value  */

/************************************************************************************
 *                                                                                  *
 *                  Internet Address Types                                          *
 *                                                                                  *
 ************************************************************************************/

#define  HOST_NAME_DESCRP  0
#define  HOST_NAME_IP      1


/************************************************************************************
 *                                                                                  *
 *                        Predefined Queue sizes                                    *
 *                                                                                  *
 ************************************************************************************/

#define  QUEUE_NO_DATA     0xFFFFFFFF     /* Queue has only data required for auto processing */

/************************************************************************************
 *                                                                                  *
 *                  Callback Functions                                              *
 *                                                                                  *
 ************************************************************************************/

typedef L_INT (pEXT_CALLBACK INETCALLBACK)
(
   L_COMP hComputer,
   L_INT nMessage,
   L_INT nError,
   L_CHAR L_FAR *pBuffer,
   L_UINT32 lSize,
   L_VOID L_FAR *pUserData
);


/************************************************************************************
 *                                                                                  *
 *                  Internet Functions                                              *
 *                                                                                  *
 ************************************************************************************/

L_INT EXT_FUNCTION L_InetConnect(L_CHAR L_FAR *pszAddress,
                                 L_INT nPort,
                                 L_COMP L_FAR *phComputer,
                                 INETCALLBACK pfnCallback,
                                 L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetServerInit(L_INT nPort,
                                    L_COMP L_FAR *phComputer,
                                    INETCALLBACK pfnCallback,
                                    L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetClose(L_COMP hComputer, L_BOOL bGraceful);

L_INT EXT_FUNCTION L_InetSendData(L_COMP hComputer, 
                                  L_CHAR L_FAR *pBuffer, 
                                  L_UINT32 L_FAR *pulBufferLength,
                                  L_UINT uDataType);

L_INT EXT_FUNCTION L_InetSendMMData(L_COMP hComputer, 
                                    L_CHAR L_FAR *pBuffer, 
                                    L_UINT32 L_FAR*pulBufferLength);

L_INT EXT_FUNCTION L_InetReadData(L_COMP hComputer, 
                                  L_CHAR L_FAR *pBuffer, 
                                  L_UINT32 L_FAR *pulBufferLength);


L_INT EXT_FUNCTION L_InetGetHostName(L_COMP hHost,
                                     L_CHAR L_FAR *pszName,
                                     L_INT nType,
                                     L_UINT32 L_FAR *pulBufferLength);

L_INT EXT_FUNCTION L_InetAcceptConnect(L_COMP hHost, 
                                       L_COMP L_FAR *phRemote,
                                       INETCALLBACK pfnCallback,
                                       L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_InetSendBitmap(L_COMP hComputer, 
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nFormat, 
                                    L_INT nBitsPerPixel, 
                                    L_INT nQFactor,
                                    L_UINT32 L_FAR*pulImageLength);

L_INT EXT_FUNCTION L_InetAutoProcess(L_COMP hComputer,
                                     L_BOOL bProcess);

L_INT EXT_FUNCTION L_InetSendRawData(L_COMP hComputer, 
                                     L_CHAR L_FAR *pBuffer,
                                     L_UINT32 L_FAR *pulBufferLength);

L_INT EXT_FUNCTION L_InetGetQueueSize(L_COMP hComputer, 
                                      L_UINT32 L_FAR *pulLength);

L_INT EXT_FUNCTION L_InetClearQueue(L_COMP hComputer);

L_INT EXT_FUNCTION L_InetStartUp(void);

L_INT EXT_FUNCTION L_InetShutDown(void);

L_INT EXT_FUNCTION L_InetSendSound(L_COMP hComputer, 
                                   LPWAVEFORMATDATA pWaveFormatData, 
                                   LPWAVEDATA pWaveData, 
                                   L_UINT32 L_FAR *pdwDataSize);

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif  /*_LTNET_H_ */
