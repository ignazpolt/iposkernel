#define _EXPORTING

#ifdef _EXPORTING
  #define DECLSPEC    __declspec(dllexport)
#else
  #define DECLSPEC    __declspec(dllimport)
#endif

extern "C" {
       
//#include "dds32.h"       

  /*
   * Call this function to start the java virtual machine.
   * The following error are thrown:
   * LIBRARY_NOT_FOUND:
   * OUT_OF_MEMORY:
   * ILLEGAL_ACCESS_ERROR:
   * VM_CREATION_FAILED:
   * CLASS_NOT_FOUND:
   * METHOD_ID_NOT_FOUND:
   * The method return true on success, otherwise false.
   *
   * Parameters: 
   * vmpath: specifies where to locate the dynamic link 
   * library of the java virtual machine. Supply empty string, if 
   * default library on path or registry should be loaded.
   * classpath: userclasspath is added to environments default 
   * classpath.
   * 
   */
  DECLSPEC BOOL Start(const TCHAR* vmpath, const ACHAR* classpath, const ACHAR* debug_param, const ACHAR* extra_option);

  
  /*
   * Call this function to stop the java virtual machine and 
   * free all allocated resources.
   *
   */
  DECLSPEC BOOL Destroy();

  /*
   * Call this function to convert a native array to a java
   * array. A native array can be either an array of primitive
   * types like jint, jdouble, jboolean etc. or an array of jobjects.
   * The result will be NULL if any error occurs. The following errors are
   * thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   *
   * Parameters:
   * nativeArray: Array of either primitive values or jobjects.
   * length: the length of the nativeArray.
   * type: the type of the values contained in the primitive array. 
   * Here the jni notion must be supplied, i.e. 
   * I for integer, Z for boolean etc. and for reference types and L followed
   * by the fully qualified classname where packages are separated by '/'.
   * Note: Do not add a semicolon to the end!
   * Note: The resulting array will occupy memory until it is freed by 
   * calling Delete on it.
   *
   */
  DECLSPEC jarray NewArrayNative(const void* nativeArray, const jsize length, const ACHAR* type);

  /*
   * Returns the number of elements in the array.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   *
   * Parameters:
   * array: a Java array object. 
   * Returns the length of the array or -1 in case of error. 
   *
   */
  DECLSPEC const jsize GetArrayLength(const jarray array);

  /*
   * A function that copies the element at the given index of a Java array object into 
   * an array buffer. 
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * JAVA_EXCEPTION:
   * The function return true if no other error occurs otherwise false.
   *
   * Parameter:
   * array: a Java array object of either primitive or reference type.
   * type: type in jni notation of the elements in the Java array 
   * object, e.g. J for long, Z for boolean or for reference types L 
   * followed by the fully  qualified classname where packages are separated 
   * by '/'.
   * Note: Do not add a semicolon in case of a reference type.
   * result: buffer where the element is copied to. Should have sufficient 
   * space for one element.
   *
   */
  DECLSPEC BOOL GetArrayNativesEx(const jarray array, const ACHAR* type, void* result, int index);

  /*
   * A function that copies the elements of a Java array object into 
   * an array buffer. 
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * JAVA_EXCEPTION:
   * The function return true if no other error occurs otherwise false.
   *
   * Parameter:
   * array: a Java array object of either primitive or reference type.
   * type: type in jni notation of the elements in the Java array 
   * object, e.g. J for long, Z for boolean or for reference types L 
   * followed by the fully  qualified classname where packages are separated 
   * by '/'.
   * Note: Do not add a semicolon in case of a reference type.
   * result: buffer where the elements are copied to. Should have sufficient 
   * space.
   *
   */
  DECLSPEC BOOL GetArrayNatives(const jarray array, const ACHAR* type, void* result);

  /*
   * A function that returns the object with the given index.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * ARRAY_INDEX_OUT_OF_BOUNDS: if the given index is less than zero or greater than or equal to the
   * length of the array.
   * JAVA_EXCEPTION:
   * The function return true if no other error occurs otherwise false.
   *
   * Parameter:
   * array: a Java array object of either primitive or reference type.
   * index: array index of object to be returned
   * result: the desired object.
   *
   */
  DECLSPEC jobject GetObjArrayElement(const jarray array, int index);

  /*
   * Returns the length of a Java string object.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * The function returns the length excluding the string terminator if 
   * no other error occurs otherwise -1.
   * 
   * Parameters:
   * jstr: A Java string object.
   *
   */
  DECLSPEC const jint GetStringLength(jstring jstr);

  /*
   * Turns a Java string object into its native representation and 
   * copies it into the buffer.
   * Does NOT add zero termination!
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible. 
   * The function returns true if no other error occurs, otherwise false.
   *
   * Parameter: 
   * jstr: a Java string object.
   * rString: buffer where the native representation is copied into.
   * Should provide sufficient space.
   *
   */
  DECLSPEC BOOL GetStringNativeChars(jstring jstr, TCHAR* rString);

  /*
   * Turns a native array of characters into a Java string object.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible. 
   * The function returns a Java string object if no other error occurs, 
   * otherwise NULL.
   * Note: The returned object will occupy memory util it is released by 
   * calling Delete on it.
   *
   * Parameter: 
   * str: buffer containing native string.
   * len: the length of the string (excluding zero termination!)
   * 
   */
  DECLSPEC jstring NewStringNative(const TCHAR* str, unsigned int len);

  /*
   * Attaches the current thread to a Java VM. Trying to 
   * attach a thread that is already attached is a no-op. 
   * A native thread cannot be attached simultaneously to 
   * two Java VMs. 
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * ATTACH_CURRENT_THREAD_FAILED
   * 
   */
  DECLSPEC void AttachCurrentThread();

  /*
   * Detaches the current thread from a Java VM. All Java monitors 
   * held by this thread are released. All Java threads waiting for 
   * this thread to die are notified. The main thread, which is the 
   * thread that created the Java VM, cannot be detached from the VM. 
   * Instead, the main thread must call Destroy() to unload the entire VM. 
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * DETACH_CURRENT_THREAD_FAILED
   * 
   */
  DECLSPEC void DetachCurrentThread();

  /*
   * This accessor routine returns the value of a static field of an object.
   * The class is specified by its signature in jni notation.
   * The field is specified by its name and signature in jni notation.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * OUT_OF_MEMORY:
   * CLASS_NOT_FOUND:
   * FIELD_ID_NOT_FOUND:
   * JAVA_EXCEPTION:
   *
   * Parameter:
   * classDescriptor: signature of the Java class object.
   * fieldName: name of the field.
   * typeDescriptor: signature of the field.
   * result: pointer to a union that contains the value.
   *
   */
  DECLSPEC void GetStaticFieldValue(const ACHAR* classDescriptor, const ACHAR* fieldName, const ACHAR* typeDescriptor, jvalue* result);

  /*
   * This routine calls a static method on the specified Java class
   * object. The class object is specified by its signature in jni
   * notation. The method is specified by its name and its signature
   * in jni notation.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * OUT_OF_MEMORY:
   * CLASS_NOT_FOUND:
   * METHOD_ID_NOT_FOUND:
   * JAVA_EXCEPTION: 
   * ILLEGAL_ARGUMENT:
   *
   * Parameter:
   * classDescriptor: signature of the Java class object.
   * method: name of the Java method.
   * methodDescriptor: signature of the method in jni notation.
   * result: to store the result. Can be NULL for void or if ther
   * is no interest in the result.
   * Note: objects cotained in the result will occupy memory until they
   * are freed by passing them to the Delete function.
   * ... parameters for the Java method.
   * 
   */
  DECLSPEC void CallStaticMethodByName(const ACHAR* classDescriptor, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...);
  DECLSPEC void CallStaticMethodByNameEx(jthrowable *ex, const ACHAR* classDescriptor, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...);

  /*
   * This routine calls a method on the specified Java object
   * The object is specified by its reference. 
   * The method is specified by its name and its signature
   * in jni notation.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * OUT_OF_MEMORY:
   * CLASS_NOT_FOUND:
   * METHOD_ID_NOT_FOUND:
   * JAVA_EXCEPTION: 
   * ILLEGAL_ARGUMENT:
   *
   * Parameter:
   * handl: Java object.
   * method: name of the Java method.
   * methodDescriptor: signature of the method in jni notation.
   * result: to store the result. Can be NULL for void or if there
   * is no interest in result.
   * Note: objects cotained in the result will occupy memory until they
   * are freed by passing them to the Delete function.
   * ... parameters for the Java method.
   * 
   */
  DECLSPEC void CallMethodByName(const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...);
  DECLSPEC void CallMethodByNameEx(jthrowable *ex, const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...);
  DECLSPEC void CallMethodByNameParallel(const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...);
  DECLSPEC void CallMethodByNameParallelEx(jthrowable *ex, const jobject handl, const ACHAR* method, const ACHAR* methodDescriptor, jvalue* result, ...);

  /*
   * This routine calls a constructor on the specified Java object class.
   * The class object is specified by its class signature in jni notation. 
   * The constructor is specified by its signature in jni notation.
   * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   * OUT_OF_MEMORY:
   * CLASS_NOT_FOUND:
   * METHOD_ID_NOT_FOUND:
   * JAVA_EXCEPTION: 
   * This method creates and returns a new Java object.
   * Note: returned objects will occupy memory until they
   * are freed by passing them to the Delete function.
   *
   * Parameter:
   * classDescriptor: Java class object signature in jni notation.
   * methodDescriptor: signature of the constructor in jni notation.
   * ... parameters to the constructor.
   * 
   */
  DECLSPEC jobject CallConstructor(const ACHAR* classDescriptor, const ACHAR* methodDescriptor, ...);
  DECLSPEC jobject CallConstructorEx(jthrowable *ex, const ACHAR* classDescriptor, const ACHAR* methodDescriptor, ...);

  /*
   * The function deletes the global reference to the specified Java
   * object, thus it loses its validity and should not be used anymore.
   * * The following error are thrown:
   * VM_NOT_STARTED: if the virtual machine was not started when calling 
   * this function.
   * GET_ENVIRONMENT_FAILED: if access to the environment pointer was not
   * possible.
   *
   * Parameter:
   * ref: valid Java object
   */
  DECLSPEC void Delete(jobject ref);

  DECLSPEC BOOL CheckStaticMethod(const ACHAR* classDescriptor, const ACHAR* method, const ACHAR* methodDescriptor);

  DECLSPEC BOOL CheckMethod(const jobject objhndl, const ACHAR* method, const ACHAR* methodDescriptor);

  DECLSPEC BOOL Instanceof(const jobject objhndl, const ACHAR* classDescriptor);

  typedef void (__stdcall *JMLCALLBACK)(BOOL);
  DECLSPEC void SetJavaMessageLoopCallback (JMLCALLBACK jmlcb);
  DECLSPEC BOOL JavaThreadIsRunning();

  DECLSPEC BOOL GetCatchNextException();
  DECLSPEC LPTSTR GetLastJavaExceptionText();
  DECLSPEC GLOBALHANDLE GetLastJavaExceptionCallStack();
  DECLSPEC jobject GetLastExceptionObject();

  DECLSPEC void SetCatchNextException(BOOL val);
  DECLSPEC void SetLastJavaExceptionText(LPTSTR val);
  DECLSPEC void SetLastJavaExceptionCallStack(GLOBALHANDLE val);
  DECLSPEC void SetLastExceptionObject(jobject val);

  DECLSPEC GLOBALHANDLE GetJavaExceptionInfo(jthrowable ex,TCHAR *str);

}

