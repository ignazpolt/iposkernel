/*
   LTPCK.H - pack header file
   Copyright (c) 1990-1998 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifdef _HEADER_ENTRY_

   #ifdef __cplusplus
      extern "C"
      {
   #endif

   #if !defined(__BORLANDC__) || (defined(__BORLANDC__) && defined(FOR_WIN32))
      #ifndef RC_INVOKED
         #pragma warning(disable: 4103)
         #pragma pack(1)
      #endif                          /* RC_INVOKED */
   #else
      #pragma option -a1

   #endif                          /* __BORLANDC__ */

#else

   #if !defined(__BORLANDC__) || (defined(__BORLANDC__) && defined(FOR_WIN32))
      #ifndef RC_INVOKED
         #pragma pack()
      #endif                          /* RC_INVOKED */
   #else
      #pragma option -a.
   #endif                          /* __BORLANDC__ */

   #ifdef __cplusplus
      } // extern "C"
   #endif

#endif



