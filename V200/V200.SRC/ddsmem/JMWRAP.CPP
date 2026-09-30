// JavaModelWrapper.cpp : Defines the entry point for the DLL application.
//

#include <windows.h>
// #include <stdlib.h>
#include "dds32.h"
#include "jni.h"
#include "jmodel.h"
#include "jmwrap.h"

static JavaModel* jm = NULL;

BOOL Start(const TCHAR* vmpath, const ACHAR* classpath, const ACHAR* debug_param, const ACHAR* extra_option) {
  if (!jm) {
    jm = new JavaModel();
  }
 
  if (jm) {
    jm->Start(vmpath, classpath, debug_param, extra_option);
    return TRUE;
  } else {
    return FALSE;
  }
}

BOOL Destroy() {
  if (jm) {
    jm->Stop();
    delete jm;
    jm = NULL;
    return TRUE;
  } else {
    return FALSE;
  }
}

jarray NewArrayNative(const void* nativeArray, const jsize length, const ACHAR* type) {
  if (jm) {
    return jm->NewArrayNative(nativeArray, length, type);
  } else {
    return NULL;
  }
}

const jsize GetArrayLength(const jarray array) {
  if (jm) {
    return jm->GetArrayLength(array);
  } else {
    return -1;
  }
}

BOOL GetArrayNativesEx(const jarray array, const ACHAR* type, void* result, int index) {
  if (jm) {
    return jm->GetArrayNativesEx(array, type, result, index);
  } else {
    return FALSE;
  }
}

BOOL GetArrayNatives(const jarray array, const ACHAR* type, void* result) {
  if (jm) {
    return jm->GetArrayNatives(array, type, result);
  } else {
    return FALSE;
  }
}

jobject GetObjArrayElement(const jarray array, int index) {
  if (jm) {
    return jm->GetObjArrayElement(array, index);
  } else {
    return NULL;
  }
}

const jint GetStringLength(jstring jstr) {
  if (jm) {
    return jm->GetStringLength(jstr);
  } else {
    return -1;
  }
}

BOOL GetStringNativeChars(jstring jstr, TCHAR* rString) {
  if (jm) {
    return jm->GetStringNativeChars(jstr, rString);
  } else {
    return FALSE;
  }
}

jstring NewStringNative(const TCHAR* str, unsigned int len) {
  if (jm) {
    return jm->NewStringNative(str, len);
  } else {
    return NULL;
  }
}

void AttachCurrentThread() {
  if (jm) {
    jm->AttachCurrentThread();
  }
}

void DetachCurrentThread() {
  if (jm) {
    jm->DetachCurrentThread();
  }
}

void GetStaticFieldValue(const ACHAR* classDescriptor, const ACHAR* fieldName, const ACHAR* typeDescriptor, jvalue* result) {
  if (jm) {
    jm->GetStaticFieldValue(classDescriptor, fieldName, typeDescriptor, result);
  }
}


void CallStaticMethodByName(const ACHAR* classDescriptor, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...) {
  va_list marker;
  if (jm) {
    __try {
      va_start(marker, result);
      jm->CallStaticMethodByNameV(NULL, classDescriptor, method, methodDescriptor, result, marker);
    } _finally {
      va_end(marker);
    }
  }
}

void CallStaticMethodByNameEx(jthrowable *ex, const ACHAR* classDescriptor, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...) {
  va_list marker;
  if (jm) {
    __try {
      va_start(marker, result);
      jm->CallStaticMethodByNameV(ex, classDescriptor, method, methodDescriptor, result, marker);
    } _finally {
      va_end(marker);
    }
  }
}

void CallMethodByName(const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...) {
  va_list marker;
  if (jm) {
    __try {
      va_start(marker, result);
      jm->CallMethodByNameV(NULL, handl, method, methodDescriptor, result, marker);
    } _finally {
      va_end(marker);
    }
  }
}

void CallMethodByNameEx(jthrowable *ex, const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...) {
  va_list marker;
  if (jm) {
    __try {
      va_start(marker, result);
      jm->CallMethodByNameV(ex, handl, method, methodDescriptor, result, marker);
    } _finally {
      va_end(marker);
    }
  }
}

void CallMethodByNameParallel(const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...) {
  va_list marker;
  if (jm) {
    __try {
      va_start(marker, result);
      jm->CallMethodByNameParallelV(NULL, handl, method, methodDescriptor, result, marker);
    } _finally {
      va_end(marker);
    }
  }
}

void CallMethodByNameParallelEx(jthrowable *ex, const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...) {
  va_list marker;
  if (jm) {
    __try {
      va_start(marker, result);
      jm->CallMethodByNameParallelV(ex, handl, method, methodDescriptor, result, marker);
    } _finally {
      va_end(marker);
    }
  }
}

jobject CallConstructor(const ACHAR* classDescriptor, const ACHAR* methodDescriptor, ...) {
  va_list marker;
  jobject rc = NULL;
  if (jm) {
    __try {
      va_start(marker, methodDescriptor);
      rc = jm->CallConstructorV(NULL, classDescriptor, methodDescriptor, marker);
    } _finally {
      va_end(marker);
    }
  }
  return rc;
}

jobject CallConstructorEx(jthrowable *ex, const ACHAR* classDescriptor, const ACHAR* methodDescriptor, ...) {
  va_list marker;
  jobject rc = NULL;
  if (jm) {
    __try {
      va_start(marker, methodDescriptor);
      rc = jm->CallConstructorV(ex, classDescriptor, methodDescriptor, marker);
    } _finally {
      va_end(marker);
    }
  }
  return rc;
}

void Delete(jobject ref) {
  if (jm) {
    jm->Delete(ref);
  }
}

BOOL CheckStaticMethod(const ACHAR* classDescriptor, const ACHAR* method, const ACHAR* methodDescriptor) {
  BOOL res = FALSE;
  if (jm) {
    res = jm->CheckStaticMethod(classDescriptor, method, methodDescriptor);
  }
  return res;
}

BOOL CheckMethod(const jobject objhndl, const ACHAR* method, const ACHAR* methodDescriptor) {
  BOOL res = FALSE;
  if (jm) {
    res = jm->CheckMethod(objhndl, method, methodDescriptor);
  }
  return res;
}

BOOL Instanceof(const jobject objhndl, const ACHAR* classDescriptor) {
  BOOL res = FALSE;
  if (jm) {
    res = jm->Instanceof(objhndl, classDescriptor);
  }
  return res;
}

static JMLCALLBACK jml;
void SetJavaMessageLoopCallback (JMLCALLBACK jmlcb)
  {
  jml = jmlcb;
  }

static void *myPrivData;  // vorerst statisch
void CallJavaMessageLoop(BOOL withMouseAndKeyboard, void *privData)
  {
  myPrivData = privData;
  (*jml)(withMouseAndKeyboard);
  myPrivData = NULL;
  }

BOOL JavaThreadIsRunning()
  {
  return ThreadIsRunning(myPrivData);
  }

extern BOOL CatchNextException;
extern LPTSTR LastJavaExceptionText;
extern GLOBALHANDLE LastJavaExceptionCallStack;
extern jobject LastExceptionObject;

BOOL GetCatchNextException()
  {
  return CatchNextException;
  }

LPTSTR GetLastJavaExceptionText()
  {
  return LastJavaExceptionText;
  }

GLOBALHANDLE GetLastJavaExceptionCallStack()
  {
  return LastJavaExceptionCallStack;
  }

jobject GetLastExceptionObject()
  {
  return LastExceptionObject;
  }

void SetCatchNextException(BOOL val)
  {
  CatchNextException = val;
  }

void SetLastJavaExceptionText(LPTSTR val)
  {
  LastJavaExceptionText = val;
  }

void SetLastJavaExceptionCallStack(GLOBALHANDLE val)
  {
  LastJavaExceptionCallStack = val;
  }

void SetLastExceptionObject(jobject val)
  {
  LastExceptionObject = val;
  }

GLOBALHANDLE GetJavaExceptionInfo(jthrowable ex,TCHAR *str)
  {
  GLOBALHANDLE res = NULL;
  if (jm) {
    res = jm->GetJavaExceptionInfo(ex, str);
    }
  return res;
  }
