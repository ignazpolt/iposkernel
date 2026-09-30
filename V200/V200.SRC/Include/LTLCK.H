/*
   LTLCK.H - support unlock key defines
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTLCK_H_
#define _LTLCK_H_

#define L_KEY_EXPRESS ""
#define L_KEY_GIFLZW  ""
#define L_KEY_TIFLZW  ""
#define L_KEY_FPXEXTENSIONS  ""
#define L_KEY_OCR            ""
#define L_KEY_VIDEO   ""
#define L_KEY_MEDICAL ""

#define UNLOCKSUPPORT() \
{ \
   L_UnlockSupport(L_SUPPORT_EXPRESS, L_KEY_EXPRESS); \
   L_UnlockSupport(L_SUPPORT_GIFLZW, L_KEY_GIFLZW); \
   L_UnlockSupport(L_SUPPORT_TIFLZW, L_KEY_TIFLZW); \
   L_UnlockSupport(L_SUPPORT_FPXEXTENSIONS, L_KEY_FPXEXTENSIONS); \
   L_UnlockSupport(L_SUPPORT_OCR, L_KEY_OCR); \
   L_UnlockSupport(L_SUPPORT_VIDEO,L_KEY_VIDEO); \
   L_UnlockSupport(L_SUPPORT_MEDICAL,L_KEY_MEDICAL); \
}

#endif                          /* _LTLCK_H_ */
