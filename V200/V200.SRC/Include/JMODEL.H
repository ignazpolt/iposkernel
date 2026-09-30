#ifndef javamodel_h
#define javamodel_h

#pragma warning(disable:4786)

//#include "dds32.h"

// Fehlercodes

#define VM_NOT_STARTED				 0L
#define GET_ENVIRONMENT_FAILED		 1L
#define ATTACH_CURRENT_THREAD_FAILED 2L
#define DETACH_CURRENT_THREAD_FAILED 3L
#define LIBRARY_NOT_FOUND			 4L
#define ILLEGAL_ACCESS_ERROR		 5L
#define VM_CREATION_FAILED			 6L
#define CLASS_NOT_FOUND				 7L
#define METHOD_ID_NOT_FOUND			 8L
#define ILLEGAL_ARGUMENT			 9L
#define JAVA_EXCEPTION			    10L
#define OUT_OF_MEMORY				11L
#define FIELD_ID_NOT_FOUND	        12L


// JNI Methodenname für den Konstruktor
#define JAVA_JNI_CONSTRUCTOR "<init>"

#define STRING_TERMINATOR '\x0'

// JNI Referenztypen enden immer mit diesem Zeichen
#define JAVA_JNI_END_OBJECT ';'

// JNI primitiver Typ void
#define JAVA_JNI_VOID 'V'

// JNI primitiver Typ boolean
#define JAVA_JNI_BOOLEAN 'Z'

// JNI primitiver Typ char
#define JAVA_JNI_CHAR 'C'

// JNI primitver Typ byte
#define JAVA_JNI_BYTE 'B'

// JNI primitver Typ short
#define JAVA_JNI_SHORT 'S'

// JNI primitver Typ int 
#define JAVA_JNI_INT 'I'

// JNI primitver Typ long 
#define JAVA_JNI_LONG 'J'

// JNI primitver Typ float 
#define JAVA_JNI_FLOAT 'F'

// JNI primitver Typ double
#define JAVA_JNI_DOUBLE 'D'

// JNI Referenztypen beginnen immer mit diesem Zeichen 
#define JAVA_JNI_OBJECT 'L'

// JNI Typ Feld beginnt immer mit diesem Zeichen
#define JAVA_JNI_ARRAY '['

// JNI Argument Beschreibung endet mit diesem Zeichen
#define JAVA_JNI_END_ARGS ')'

// JNI Bezeichnung der String Klasse im Java Core API 
#define JAVA_API_STRING "java/lang/String"

// JNI Bezeichnung der Object Klasse im Java Core API
#define JAVA_API_OBJECT "java/lang/Object"

// Konstanten für den JNI Descriptor eines String aus dem Java Core API
#define JAVA_API_STRING_DESC_PARAM "L"JAVA_API_STRING
#define JAVA_API_STRING_DESC_RETURN JAVA_API_STRING_DESC_PARAM";"


// Zugriff auf Registry zum finden der Java Virtual Machine dll
#define	JAVA_REGISTRY_STRING_1 _T("SOFTWARE\\JavaSoft\\Java Runtime Environment\\1.2")
#define	JAVA_REGISTRY_STRING_2 _T("SOFTWARE\\JavaSoft\\Java Plug-in\\1.2")
#define	JAVA_REGISTRY_STRING_3 _T("SOFTWARE\\JavaSoft\\Java Runtime Environment\\1.3")
#define	JAVA_REGISTRY_STRING_4 _T("SOFTWARE\\JavaSoft\\Java Plug-in\\1.3")

// Name der Java Virtual Machine dll
#define JAVA_VM_DLL _T("jvm.dll")


/*
 * Pointers to the needed JNI invocation API, initialized by LoadJavaVM.
 */
typedef struct 
{
    jint (JNICALL *CreateJavaVM) (JavaVM **pvm, void **env, void *args);
    jint (JNICALL *GetDefaultJavaVMInitArgs) (void *args);
} InvocationFunctions;


class JavaModel
{
public:
	/* Konstruktor */
	JavaModel()
	{
		// Handle auf die DLL der Java Virtual Machine
		hVM                = NULL; 
		// Zeiger auf die Java Virtual Machine
		vm                 = NULL; 
		// Anzahl der Verbundenen Threads mit der VM
		countAttachedThreads = 0;
		lstrcpy(jvmdll, _T(""));		

#ifdef START_ON_LOAD
		// Wird auf true gesetzt, wenn Java Virtual Machine gestartet wurde
		try {
			Start("");
		} catch (long /* error */) 
		{

		}
#endif
	}
	
	/* Destruktor */
	inline ~JavaModel()
	{
		Stop();
		
		if (hVM != NULL) {
			FreeLibrary(hVM);
		}
	}

  jarray NewArrayNative(const void* nativeArray, 
                        const jsize length,
                        const ACHAR* type);

  const jsize GetArrayLength(const jarray array);

  BOOL GetArrayNativesEx(const jarray array,
                         const ACHAR* type,
                         void* result,
                         int index);

  BOOL GetArrayNatives(const jarray array,
                       const ACHAR* type,
                       void* result);

  jobject GetObjArrayElement(const jarray array, int index);

  const jint GetStringLength(const jstring jstr);

  BOOL GetStringNativeChars (const jstring jstr, TCHAR* rString);
  
  jstring NewStringNative(const TCHAR* str, unsigned int len);
    
	void AttachCurrentThread();

	void DetachCurrentThread();

	void GetStaticFieldValue(const ACHAR* classDescriptor,
	                         const ACHAR* fieldName,
	                         const ACHAR* typeDescriptor,
                           jvalue* result);
	
	void CallStaticMethodByNameV(jthrowable *ex,
                               const ACHAR* classDescriptor, 
                               const ACHAR* method,
                               const ACHAR* methodDescriptor,
                               jvalue* result,
                               va_list argList);
	
	void CallMethodByNameV(jthrowable *ex,
                         const jobject hndl, 
                         const ACHAR* method,
                         const ACHAR* methodDescriptor,
                         jvalue* result,
                         va_list argList);
	
	void CallMethodByNameParallelV(jthrowable *ex,
                                 const jobject hndl, 
                                 const ACHAR* method,
                                 const ACHAR* methodDescriptor,
                                 jvalue* result,
                                 va_list argList);
	
	jobject CallConstructorV(jthrowable *ex,
                           const ACHAR* classDescriptor,  
                           const ACHAR* methodDescriptor,
                           va_list argList);
	 
	void Delete(jobject ref);

  BOOL CheckStaticMethod(const ACHAR* classDescriptor,
                         const ACHAR* method,
                         const ACHAR* methodDescriptor);

  BOOL CheckMethod(const jobject objhndl,
                   const ACHAR* method,
                   const ACHAR* methodDescriptor);

  BOOL Instanceof(const jobject objhndl,
                  const ACHAR* classDescriptor);

  GLOBALHANDLE GetJavaExceptionInfo(jthrowable ex,TCHAR *str);

	void Start(const TCHAR* vmpath, const ACHAR* classpath, const ACHAR* debug_param, const ACHAR* extra_option);

	BOOL Stop();

  void SetJVMDLL(const TCHAR* filename) {
    if (filename) {
      lstrcpy(jvmdll, filename);
		}
	}

private:
	TCHAR jvmdll[MAX_PATH]; // complete path+filename of VM-DLL
	/**
	 * Zählt, wieviele Threads momentan mit der VM verbunden sind.
	 */
	int countAttachedThreads;
	JavaVM*   vm;
	HINSTANCE hVM;

	jmethodID MID_StringBuffer_append_S;
	jmethodID MID_StringBuffer_append_J;

	jclass Class_java_lang_String;
	jmethodID MID_String_init;
	jmethodID MID_String_getBytes;
		
	BOOL FindLibrary();
};

extern BOOL ThreadIsRunning(void *privData);
extern void CallJavaMessageLoop(BOOL withMouseAndKeyboard, void *privData);

#endif

