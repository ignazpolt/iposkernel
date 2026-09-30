/*
   LTSYS.H - operating system definition
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTSYS_H_
#define _LTSYS_H_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined (_ALPHA_)
   #ifndef FOR_WIN32
      #define FOR_WIN32
   #endif                          /* FOR_WIN32 */
#else
   #ifndef FOR_WIN
      #define FOR_WIN
   #endif                          /* FOR_WIN */
#endif                          /* defined(WIN32) || defined(_WIN32) */

#endif                          /* _LTSYS_H_ */
