//-------------------------------------------------------
// JNI Model
//-------------------------------------------------------
//
// $Header:   P:/marille/clinicum/ddsmem/rev/jmodel.cpv   1.31   12 May 2009 20:29:40   Martin  $
// $Log:   P:/marille/clinicum/ddsmem/rev/jmodel.cpv  $
// 
//    Rev 1.31   12 May 2009 20:29:40   Martin
// exception handling...
// 
//    Rev 1.30   07 Nov 2008 11:44:24   Wolfgang
// 1.) Compute javaReferences here instead of EXTDLL.
// 2.) New function DoJavaReferencesInc.
// 
//    Rev 1.29   08 Oct 2008 18:56:24   Martin
// besseres Exception-Handling
// 
//    Rev 1.28   16 Jun 2008 00:06:02   Martin
// JAVA nach ddsmem verschoben
// 
//    Rev 1.27   28 Feb 2008 17:22:00   Katharina
// Unicode, Speicherverwaltung
// 
//    Rev 1.26   26 Jul 2007 14:15:46   Martin
// Thread handling korrigiert! Wie waers mit Doku lesen?
// 
//    Rev 1.25   19 Jul 2007 19:08:36   Martin
// vernuenftige Meldung bei CallMethod auf NULL Objekt
// 
//    Rev 1.24   10 Jul 2007 14:34:56   Martin
// Sleep bei JAVA-Popup verbessert
// 
//    Rev 1.23   23 Apr 2007 12:15:20   Martin
// describe raus (produzierte unnietige stderr redirect LOGs)
// 
//    Rev 1.22   26 Mar 2007 17:02:44   Martin
// jetzt auch hoffentlich wirklich bei Exception Klassennamen ausgeben
// 
//    Rev 1.21   21 Dec 2006 10:42:34   Martin
// Sleep(100) entschaerft
// 
//    Rev 1.20   06 Oct 2006 19:46:58   Martin
// hoffentlich jetzt wirklich Kartendaten-Problem geloest
// 
//    Rev 1.19   10 May 2006 19:51:36   Martin
// Loesungsversuch fuer Kartendaten-Aufnahme-Problematik
// 
//    Rev 1.18   28 Apr 2006 17:57:48   Martin
// Logging...
// 
//    Rev 1.17   06 Apr 2006 19:13:06   Martin
// bei Exception Klassennamen ausgeben
// 
//    Rev 1.16   13 Mar 2006 17:30:46   Martin
// eventuelle Gaensefuesschen im Classpath entfernen
// 
//    Rev 1.15   09 Feb 2006 14:40:40   Martin
// String <-> blob
// 
//    Rev 1.14   15 Jul 2005 20:05:50   Martin
// bei + vorm Methodennamen auch Maus- und Tastaturnachrichten durchlassen
// 
//    Rev 1.13   13 May 2005 18:49:22   Martin
// primitive arrays...
// 
//    Rev 1.12   22 Apr 2005 18:47:44   Martin
// arrays...
// 
//    Rev 1.11   17 Dec 2004 19:52:34   Martin
// Maus- und Tastaturnachrichten doch NICHT abarbeiten...
// 
//    Rev 1.10   11 Nov 2004 12:28:24   Martin
// Jmethodparallel arbeitet alle Nachrichten ab (ausser WMU_CALLCOMMAND)
// 
//    Rev 1.9   13 Oct 2004 18:51:20   Martin
// Jcatchexception usw.
// 
//    Rev 1.8   08 Sep 2004 21:24:18   Martin
// bool -> BOOL (wegen 4er compiler)
// 
//    Rev 1.7   08 Sep 2004 21:12:20   Martin
// Jmethodparallel
// 
//    Rev 1.6   29 Apr 2004 11:01:30   Gerhold
// SetJavaExceptionText ... __declspec (dllexport)
// 
//    Rev 1.5   04 Mar 2004 18:38:42   Wolfgang
// 1.) Auch Short eingebaut.
//

#include <windows.h>
#include <stdlib.h>
#include "jni.h"
#include "dds32.h"
#include "jmodel.h"
#include "globmem.h"
#include "ddsmsg.h"
#include "dds.hpp"

#include <dde.h>
#include <process.h>

#define MODULENUM 196

extern __declspec( dllexport ) void WINAPI dbwin_ass_failed_text (int modnum, int line, LPTSTR text);
#define JAVA_ERROR(text) { dbwin_ass_failed_text(MODULENUM, __LINE__, text); }

LONG javaReferences = 0L;
static TCHAR gLastLoadedJvmPath[1024] = _T("");
static TCHAR gLastJavaClassPath[4096] = _T("");

BOOL CatchNextException = FALSE;
LPTSTR LastJavaExceptionText = NULL;
GLOBALHANDLE LastJavaExceptionCallStack = NULL;
jobject LastExceptionObject = NULL;

void AppendTextLimited(TCHAR* target, size_t targetCount, const TCHAR* text) {
    if (!target || targetCount == 0 || !text) {
        return;
    }

    size_t currentLen = (size_t)lstrlen(target);
    if (currentLen >= targetCount - 1) {
        return;
    }

    TCHAR* dst = target + currentLen;
    const TCHAR* src = text;
    size_t remaining = targetCount - currentLen - 1;
    while (remaining > 0 && *src) {
        *dst++ = *src++;
        remaining--;
    }
    *dst = _T('\0');
}

void RememberLoadedJvmPath(const TCHAR* path) {
    if (!path) {
        gLastLoadedJvmPath[0] = _T('\0');
        return;
    }
    lstrcpyn(gLastLoadedJvmPath, path, _countof(gLastLoadedJvmPath));
}

void RememberJavaClassPath(const TCHAR* classPathOption) {
    if (!classPathOption) {
        gLastJavaClassPath[0] = _T('\0');
        return;
    }
    lstrcpyn(gLastJavaClassPath, classPathOption, _countof(gLastJavaClassPath));
}

void ReportClassNotFoundWithContext(int line, const ACHAR* classDescriptor) {
    TCHAR msg[4608];
#ifdef UNICODE
    LPCPLSTR uniClass = classDescriptor ? AnsiToBomStr((LPASTR)classDescriptor) : NULL;
    LPCTSTR classText = uniClass ? TO_LPTSTR(uniClass) : _T("<null>");
#else
    LPCTSTR classText = classDescriptor ? classDescriptor : _T("<null>");
#endif
    _stprintf(msg,
              _T("CLASS_NOT_FOUND (class %s), JVM=%s, classpath=%s"),
              classText,
              gLastLoadedJvmPath[0] ? gLastLoadedJvmPath : _T("<unknown>"),
              gLastJavaClassPath[0] ? gLastJavaClassPath : _T("<none>"));
    dbwin_ass_failed_text(MODULENUM, line, msg);
#ifdef UNICODE
    if (uniClass) {
        FreeGlobMem(uniClass);
    }
#endif
}

BOOL TryFindInsensitiveSubPath(const TCHAR* path, const TCHAR* token, int* indexOut) {
    if (!path || !token || !indexOut) {
        return FALSE;
    }

    int pathLen = lstrlen(path);
    int tokenLen = lstrlen(token);
    if (tokenLen <= 0 || tokenLen > 127 || pathLen < tokenLen) {
        return FALSE;
    }

    TCHAR probe[128];
    for (int i = 0; i <= pathLen - tokenLen; i++) {
        lstrcpyn(probe, path + i, tokenLen + 1);
        if (lstrcmpi(probe, token) == 0) {
            *indexOut = i;
            return TRUE;
        }
    }

    return FALSE;
}

BOOL AppendJarFilesFromDir(const ACHAR* dirPath, ACHAR* classPathOut, size_t classPathOutCount) {
    if (!dirPath || !*dirPath || !classPathOut || classPathOutCount == 0) {
        return FALSE;
    }

    ACHAR searchPattern[MAX_PATH];
    if (dirPath[strlen(dirPath) - 1] == '\\' || dirPath[strlen(dirPath) - 1] == '/') {
        sprintf(searchPattern, "%s*.jar", dirPath);
    } else {
        sprintf(searchPattern, "%s\\*.jar", dirPath);
    }

    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPattern, &fd);
    if (hFind == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    BOOL appended = FALSE;
    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue;
        }

        ACHAR fullJarPath[MAX_PATH];
        if (dirPath[strlen(dirPath) - 1] == '\\' || dirPath[strlen(dirPath) - 1] == '/') {
            sprintf(fullJarPath, "%s%s", dirPath, fd.cFileName);
        } else {
            sprintf(fullJarPath, "%s\\%s", dirPath, fd.cFileName);
        }

        if (classPathOut[0] != '\0') {
            AppendTextLimited(classPathOut, classPathOutCount, ";");
        }
        AppendTextLimited(classPathOut, classPathOutCount, fullJarPath);
        appended = TRUE;
    } while (FindNextFileA(hFind, &fd));

    FindClose(hFind);
    return appended;
}

BOOL BuildClassPathFromExeLocation(ACHAR* classPathOut, size_t classPathOutCount) {
    if (!classPathOut || classPathOutCount == 0) {
        return FALSE;
    }
    classPathOut[0] = '\0';

    ACHAR exePath[MAX_PATH];
    DWORD n = GetModuleFileNameA(NULL, exePath, _countof(exePath));
    if (n == 0 || n >= _countof(exePath)) {
        return FALSE;
    }

    ACHAR exeDir[MAX_PATH];
    strcpy(exeDir, exePath);
    for (int i = (int)strlen(exeDir) - 1; i >= 0; --i) {
        if (exeDir[i] == '\\' || exeDir[i] == '/') {
            exeDir[i] = '\0';
            break;
        }
    }

    BOOL foundAny = FALSE;
    if (AppendJarFilesFromDir(exeDir, classPathOut, classPathOutCount)) {
        foundAny = TRUE;
    }

    ACHAR libDir[MAX_PATH];
    sprintf(libDir, "%s\\lib", exeDir);
    if (AppendJarFilesFromDir(libDir, classPathOut, classPathOutCount)) {
        foundAny = TRUE;
    }

    return foundAny;
}

void GetPathDirectory(const TCHAR* path, TCHAR* outDir, size_t outDirCount) {
    if (!outDir || outDirCount == 0) {
        return;
    }
    outDir[0] = _T('\0');
    if (!path || !*path) {
        return;
    }

    lstrcpyn(outDir, path, (int)outDirCount);
    int len = lstrlen(outDir);
    for (int i = len - 1; i >= 0; i--) {
        if (outDir[i] == _T('\\') || outDir[i] == _T('/')) {
            outDir[i] = _T('\0');
            return;
        }
    }

    outDir[0] = _T('\0');
}

void ResolveJvmDependencyDir(const TCHAR* jvmPath, TCHAR* outDir, size_t outDirCount) {
    if (!outDir || outDirCount == 0) {
        return;
    }
    outDir[0] = _T('\0');
    if (!jvmPath || !*jvmPath) {
        return;
    }

    int idx = -1;
    if (TryFindInsensitiveSubPath(jvmPath, _T("\\bin\\client\\jvm.dll"), &idx) ||
        TryFindInsensitiveSubPath(jvmPath, _T("\\bin\\server\\jvm.dll"), &idx)) {
        int keepLen = idx + 4; // "\bin"
        if (keepLen > 0) {
            lstrcpyn(outDir, jvmPath, keepLen + 1);
            return;
        }
    }

    if (TryFindInsensitiveSubPath(jvmPath, _T("\\jre\\bin\\server\\jvm.dll"), &idx) ||
        TryFindInsensitiveSubPath(jvmPath, _T("\\jre\\bin\\client\\jvm.dll"), &idx)) {
        int keepLen = idx + 8; // "\jre\bin"
        if (keepLen > 0) {
            lstrcpyn(outDir, jvmPath, keepLen + 1);
            return;
        }
    }

    GetPathDirectory(jvmPath, outDir, outDirCount);
}

HMODULE LoadJvmLibraryCandidate(const TCHAR* candidatePath, DWORD* lastErrorOut) {
    if (lastErrorOut) {
        *lastErrorOut = 0;
    }

    if (!candidatePath || !*candidatePath) {
        if (lastErrorOut) {
            *lastErrorOut = ERROR_INVALID_PARAMETER;
        }
        return NULL;
    }

    TCHAR depDir[MAX_PATH];
    depDir[0] = _T('\0');
    ResolveJvmDependencyDir(candidatePath, depDir, _countof(depDir));

    HMODULE h = NULL;
    BOOL hasCustomDllDir = (depDir[0] != _T('\0'));
    if (hasCustomDllDir) {
        SetDllDirectory(depDir);
        h = LoadLibraryEx(candidatePath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (!h && lastErrorOut) {
            *lastErrorOut = GetLastError();
        }
        SetDllDirectory(NULL);
    } else {
        h = LoadLibraryEx(candidatePath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
        if (!h && lastErrorOut) {
            *lastErrorOut = GetLastError();
        }
    }

    if (!h) {
        h = LoadLibrary(candidatePath);
        if (!h && lastErrorOut) {
            *lastErrorOut = GetLastError();
        }
    }

    return h;
}

const TCHAR* GetProcessBitnessText() {
#if defined(_WIN64)
    return _T("64-bit");
#else
    return _T("32-bit");
#endif
}

void AppendLoadAttempt(TCHAR* target, size_t targetCount, const TCHAR* candidatePath, const TCHAR* depDir, DWORD loadError, BOOL* sawBadExeFormat) {
    TCHAR row[1024];

    if (sawBadExeFormat && loadError == ERROR_BAD_EXE_FORMAT) {
        *sawBadExeFormat = TRUE;
    }

    _stprintf(row,
              _T("%s [dep=%s] (err=%lu); "),
              (candidatePath && *candidatePath) ? candidatePath : _T("<empty>"),
              (depDir && *depDir) ? depDir : _T("<default>"),
              loadError);
    AppendTextLimited(target, targetCount, row);
}

#ifdef DEBUG
// #define LOG_JAVAREFS 1
#endif

#ifdef LOG_JAVAREFS
void LogReference(LPVOID jref, BOOL isNew)
  {
//  if (IsLogTypeEnabled(LOG_TYPE_MTS)) { // Does not work for unknown reasons. Probably too early.
    TCHAR msg[128];
    wsprintf(msg, _T("Java-Reference: 0x%08lx - %s"), jref, (isNew ? "New" : "Delete"));
    WriteLogFile(LOG_TYPE_CPL, msg);
//    }
  }
#endif

DLLExport void _export WINAPI DoJavaReferencesInc (LPVOID jref)
  {
#ifdef LOG_JAVAREFS
  LogReference(jref, TRUE);
#endif
  if (jref != NULL) javaReferences++;
  }

GLOBALHANDLE GetJavaExceptionInfoInt(jthrowable t,JNIEnv* env, TCHAR *str) {
    jclass c = env->FindClass ("java/lang/Throwable");
    if (c == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot find class 'java/lang/Throwable'"));
        return NULL;
    }
    jclass pwc = env->FindClass ("java/io/PrintWriter");
    if (pwc == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot find class 'java/io/PrintWriter'"));
        return NULL;
    }
    jclass swc = env->FindClass ("java/io/StringWriter");
    if (swc == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot find class 'java/io/StringWriter'"));
        return NULL;
    }
    jmethodID pwcm = env->GetMethodID (pwc,JAVA_JNI_CONSTRUCTOR, "(Ljava/io/Writer;)V");
    if (pwcm == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot get constructor for 'java/io/PrintWriter'"));
        return NULL;
    }
    jmethodID swcm = env->GetMethodID (swc,JAVA_JNI_CONSTRUCTOR, "()V");
    if (swcm == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot get constructor for 'java/io/StringWriter'"));
        return NULL;
    }
    jmethodID swtsm = env->GetMethodID (swc,"toString", "()Ljava/lang/String;");
    if (swtsm == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot get method ID for 'toString'"));
        return NULL;
    }
    jmethodID m = env->GetMethodID (c,"getMessage", "()Ljava/lang/String;");
    if (m == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot get method ID for 'getMessage'"));
        return NULL;
    }
    jmethodID pm = env->GetMethodID (c,"printStackTrace", "(Ljava/io/PrintWriter;)V");
    if (pm == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot get method ID for 'printStackTrace'"));
        return NULL;
    }
    jclass clazz = env->FindClass ("java/lang/Class");
    if (clazz == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot find class 'java/lang/Class'"));
        return NULL;
    }
    jmethodID cgn = env->GetMethodID (clazz,"getName", "()Ljava/lang/String;");
    if (cgn == NULL) {
        JAVA_ERROR(_T("JNI Error - cannot get method ID for 'getName'"));
        return NULL;
    }
    const TCHAR* ps;
    jstring ss = (jstring) env->CallObjectMethod (t, m);
    if (ss == NULL) {
        ps = _T("(no message)");
    } else {
#ifdef UNICODE          
        ps = (LPTSTR)env->GetStringChars (ss, NULL);
#else
        ps = (LPTSTR)env->GetStringUTFChars (ss, NULL);
#endif                                    
        if (ps == NULL) {
            JAVA_ERROR(_T("JNI Error - 'GetStringUTFChars' returned NULL"));
            return NULL;
        }
    }
    jobject sw = env->NewObject (swc, swcm);
    if (sw == NULL) {
        JAVA_ERROR(_T("JNI Error - constructor of StringWriter failed"));
        return NULL;
    }
    jobject pw = env->NewObject (pwc, pwcm, sw);
    if (pw == NULL) {
        JAVA_ERROR(_T("JNI Error - constructor of PrintWriter failed"));
        return NULL;
    }
    env->CallObjectMethod (t, pm, pw);
    jstring st = (jstring) env->CallObjectMethod (sw, swtsm);
    if (st == NULL) {
        JAVA_ERROR(_T("JNI Error - 'printStackTrace' returned NULL"));
        return NULL;
    }
    const TCHAR* pst;
#ifdef UNICODE          
    pst = (LPTSTR)env->GetStringChars (st, NULL);
#else
    pst = (LPTSTR)env->GetStringUTFChars (st, NULL);
#endif                                    
    if (pst == NULL) {
        JAVA_ERROR(_T("JNI Error - 'GetStringUTFChars' returned NULL"));
        return NULL;
    }
    jclass ec = env->GetObjectClass(t);
    const TCHAR* cn;
    jstring jcn = (jstring) env->CallObjectMethod (ec, cgn);
    if (jcn == NULL) {
        cn = _T("(no class name)");
    } else {
#ifdef UNICODE          
        cn = (LPTSTR)env->GetStringChars (jcn, NULL);
#else
        cn = (LPTSTR)env->GetStringUTFChars (jcn, NULL);
#endif                                                
        if (cn == NULL) {
            JAVA_ERROR(_T("JNI Error - 'GetStringUTFChars' returned NULL"));
            return NULL;
        }
    }
  
    GLOBALHANDLE hjet = GlobalAlloc(GHND, (lstrlen(pst) + 1)*sizeof(TCHAR));
    LPTSTR jet = (LPTSTR)GlobalLock(hjet);
    lstrcpy(jet, pst);
    GlobalUnlock(hjet);
    _stprintf(str, _T("JAVA Exception %s: %.256s\r\n"), cn, ps);
#ifdef UNICODE            
    if (ss != NULL)
        env->ReleaseStringChars (ss, (jchar*)ps);
    env->ReleaseStringChars (st, (jchar*)pst);
    if (jcn != NULL)
        env->ReleaseStringChars (jcn, (jchar*)cn);
#else
    if (ss != NULL)
        env->ReleaseStringUTFChars (ss, ps);
    env->ReleaseStringUTFChars (st, pst);
    if (jcn != NULL)
        env->ReleaseStringUTFChars (jcn, cn);
#endif            
    env->DeleteLocalRef(ss);
    env->DeleteLocalRef(st);
    env->DeleteLocalRef(jcn);
  
    return hjet;
}

BOOL CheckJavaException(jthrowable *ex, JNIEnv* env, int line, LPASTR FileName) {
    jthrowable t = env->ExceptionOccurred ();
    if (t != NULL) {
        // env->ExceptionDescribe();
        javaReferences++;
        t = jthrowable(env->NewGlobalRef(t));
#ifdef LOG_JAVAREFS
        LogReference(t, TRUE);
#endif
        env->ExceptionClear();
        if (ex != NULL) {
          *ex = t;
          return TRUE;          
          }
        TCHAR *str = (TCHAR *)GetGlobMem(3000*sizeof(TCHAR));
        GLOBALHANDLE hjet = GetJavaExceptionInfoInt(t, env, str);
        if (CatchNextException) {
            if (LastJavaExceptionCallStack != NULL) {
                GlobalFree(LastJavaExceptionCallStack);
                }
            if (LastJavaExceptionText != NULL) {
                FreeGlobMem(LastJavaExceptionText);
                }
            LastJavaExceptionCallStack = hjet;
            LastJavaExceptionText = str;
            LastExceptionObject = t;
            }
        else {
            SetJavaExceptionText(hjet);
            dbwin_ass_failed_text(MODULENUM, line, str); //FileName as 3rd parameter
            FreeGlobMem(str);
#ifdef LOG_JAVAREFS
            LogReference(t, FALSE);
#endif
            env->DeleteGlobalRef(t);
            javaReferences--;
            }
        return TRUE;
    }
    return FALSE;
}


#define CHECK_EXCEPTION(ex) CheckJavaException(ex, env, __LINE__, __FILE__)

void JavaError(int line, LPASTR FileName, const TCHAR *text, const TCHAR *param) {
    TCHAR str[1024];
    _stprintf(str,text,param);
    dbwin_ass_failed_text(MODULENUM, line, str); //FileName as 3rd parameter
}

void JavaError2(int line, LPASTR FileName, const TCHAR *text, const TCHAR *param1, const TCHAR *param2) {
    TCHAR str[1024];
    _stprintf(str,text,param1,param2);
    dbwin_ass_failed_text(MODULENUM, line, str); //FileName as 3rd parameter
}

void JavaError3(int line, LPASTR FileName, const TCHAR *text, const TCHAR *param1, const TCHAR *param2, const TCHAR *param3) {
    TCHAR str[1024];
    _stprintf(str,text,param1,param2,param3);
    dbwin_ass_failed_text(MODULENUM, line, str); //FileName as 3rd parameter
}

#define JAVA_ERROR_PARAM(text,param) { JavaError(__LINE__, __FILE__, text, param); }
#define JAVA_ERROR_PARAM2(text,param1,param2) { JavaError2(__LINE__, __FILE__, text, param1, param2); }
#define JAVA_ERROR_PARAM3(text,param1,param2,param3) { JavaError3(__LINE__, __FILE__, text, param1, param2, param3); }


jarray JavaModel::NewArrayNative(const void* nativeArray, 
                                 const jsize length, 
                                 const ACHAR* type) {

    jarray rc     = NULL;
    jarray result = NULL;
    JNIEnv* env   = NULL;
        
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    switch(*type) {
    case JAVA_JNI_BOOLEAN:
        result = env->NewBooleanArray(length);
        env->SetBooleanArrayRegion((jbooleanArray) result, 
                                   0, 
                                   length, 
                                   (jboolean*) nativeArray);
        break;
    case JAVA_JNI_CHAR:
        result = env->NewCharArray(length);
        env->SetCharArrayRegion((jcharArray) result, 
                                0, 
                                length, 
                                (jchar*) nativeArray);
        break;
    case JAVA_JNI_BYTE:
        result = env->NewByteArray(length);
        env->SetByteArrayRegion((jbyteArray) result,
                                0, 
                                length, 
                                (jbyte*) nativeArray);
        break;
    case JAVA_JNI_SHORT:
        result = env->NewShortArray(length);
        env->SetShortArrayRegion((jshortArray) result, 
                                 0, 
                                 length, 
                                 (jshort*) nativeArray);
        break;
    case JAVA_JNI_INT:
        result = env->NewIntArray(length);
        env->SetIntArrayRegion((jintArray) result, 
                               0, 
                               length, 
                               (jint*) nativeArray);
        break;
    case JAVA_JNI_LONG:
        result = env->NewLongArray(length);
        env->SetLongArrayRegion((jlongArray) result, 
                                0, 
                                length, 
                                (jlong*) nativeArray);
        break;
    case JAVA_JNI_FLOAT:
        result = env->NewFloatArray(length);
        env->SetFloatArrayRegion((jfloatArray) result, 
                                 0, 
                                 length, 
                                 (jfloat*) nativeArray);
        break;
    case JAVA_JNI_DOUBLE:
        result = env->NewDoubleArray(length);
        env->SetDoubleArrayRegion((jdoubleArray) result, 
                                  0, 
                                  length, 
                                  (jdouble*) nativeArray);
        break;
    case JAVA_JNI_OBJECT:
        {
            type++;
            jclass cls = env->FindClass(type);
            result = env->NewObjectArray(length, cls, NULL);
            
            for (int i = 0; i < length; i++) {
                jobject obj = ((jobject*) nativeArray)[i];

                env->SetObjectArrayElement((jobjectArray) result, 
                                           i, 
                                           obj);
            }
            break;
        }
    }

    if (CHECK_EXCEPTION(NULL)) {
        if (result) {
            env->DeleteLocalRef(result);
        }
    } else if (result) {
        javaReferences++;
        rc = (jarray) env->NewGlobalRef(result);    
#ifdef LOG_JAVAREFS
        LogReference(rc, TRUE);
#endif
        env->DeleteLocalRef(result);
    } 

    return rc;
}

const jsize JavaModel::GetArrayLength(const jarray array) {
    JNIEnv* env = NULL;
    jsize rc    = -1;     
    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    rc = env->GetArrayLength(array);

    CHECK_EXCEPTION(NULL);
    
    return rc;
}

BOOL JavaModel::GetArrayNativesEx(const jarray array,
                                  const ACHAR* type,
                                  void* result,
                                  int index) {
    JNIEnv* env = NULL;
    BOOL rc     = TRUE;
        
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    int fromIndex;
    jsize length;
    if (index == -1) {
        fromIndex = 0;
        length = env->GetArrayLength(array);
    } else {
        fromIndex = index;
        length = 1;
    }

    switch(*type) {
    case JAVA_JNI_BOOLEAN:
        env->GetBooleanArrayRegion((jbooleanArray) array, 
                                   fromIndex, 
                                   length, 
                                   (jboolean*) result);
        break;
    case JAVA_JNI_CHAR:
        env->GetCharArrayRegion((jcharArray) array, 
                                fromIndex, 
                                length, 
                                (jchar*) result);
        break;
    case JAVA_JNI_BYTE:
        env->GetByteArrayRegion((jbyteArray) array,
                                fromIndex, 
                                length, 
                                (jbyte*) result);
        break;
    case JAVA_JNI_SHORT:
        env->GetShortArrayRegion((jshortArray) array, 
                                 fromIndex, 
                                 length, 
                                 (jshort*) result);
        break;
    case JAVA_JNI_INT:
        env->GetIntArrayRegion((jintArray) array, 
                               fromIndex, 
                               length, 
                               (jint*) result);
        break;
    case JAVA_JNI_LONG:
        env->GetLongArrayRegion((jlongArray) array, 
                                fromIndex, 
                                length, 
                                (jlong*) result);
        break;
    case JAVA_JNI_FLOAT:
        env->GetFloatArrayRegion((jfloatArray) array, 
                                 fromIndex, 
                                 length, 
                                 (jfloat*) result);
        break;
    case JAVA_JNI_DOUBLE:
        env->GetDoubleArrayRegion((jdoubleArray) array, 
                                  fromIndex, 
                                  length, 
                                  (jdouble*) result);
        break;
    case JAVA_JNI_OBJECT:
        if (index == -1) {
            for (int i = 0; i < length; i++) {
                jobject obj = env->GetObjectArrayElement((jobjectArray) array, i);
                CHECK_EXCEPTION(NULL);
                ((jobject*) result)[i] = obj;
            }
        } else {
            ((jobject*) result)[0] = env->GetObjectArrayElement((jobjectArray) array, index);
        }
    }

    if (CHECK_EXCEPTION(NULL)) {
        rc = FALSE;
    } 

    return rc;
}

BOOL JavaModel::GetArrayNatives(const jarray array,
                                const ACHAR* type,
                                void* result) {
    return GetArrayNativesEx(array, type, result, -1);
}

jobject JavaModel::GetObjArrayElement(const jarray array, int index) {
    JNIEnv* env = NULL;
        
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    jsize length = env->GetArrayLength(array);

    if ((index < 0) || (index >= length)) {
        JAVA_ERROR(_T("ARRAY_INDEX_OUT_OF_BOUNDS"));
    }
    jobject obj = env->GetObjectArrayElement((jobjectArray) array, index);
    CHECK_EXCEPTION(NULL);
    return obj;
}

jstring JavaModel::NewStringNative(const TCHAR* str, unsigned int len) {

    jstring result   = NULL;
    JNIEnv* env      = NULL;
        
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }
    
#ifdef UNICODE        
    result = env->NewString((jchar*)str, len); 
#else
    jbyteArray bytes = env->NewByteArray(len);

    if (bytes) {
        env->SetByteArrayRegion(bytes, 0, len, (jbyte*) str);
        javaReferences++;
        result = (jstring) env->NewGlobalRef(
                    env->NewObject(Class_java_lang_String, MID_String_init, bytes));
#ifdef LOG_JAVAREFS
        LogReference(result, TRUE);
#endif
        env->DeleteLocalRef(bytes);        
    }
#endif    
/*
    if (UnicodeString != NULL) {
        delete UnicodeString;
    }
*/        
    return result;
}

const jint JavaModel::GetStringLength(const jstring jstr) {
    JNIEnv *env = NULL;
    jint len    = -1;

    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

#ifdef UNICODE        
    len = env->GetStringLength(jstr); 
#else
    jbyteArray bytes = (jbyteArray) env->CallObjectMethod(jstr, 
                                                          MID_String_getBytes);
    
    if(!CHECK_EXCEPTION(NULL)) {
        len = env->GetArrayLength(bytes);
    }

    env->DeleteLocalRef(bytes);
#endif
    return len;    
}


BOOL JavaModel::GetStringNativeChars (const jstring jstr, TCHAR* rString) {
    
    JNIEnv *env = NULL;
    BOOL rc     = TRUE;
    
    if (rString != NULL) {
        if(!vm) {
            JAVA_ERROR(_T("VM_NOT_STARTED"));
        }

        if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
            JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
        }

#ifdef UNICODE        
        const jchar* myString = env->GetStringChars(jstr, NULL); 
        lstrcpy (rString, (LPTSTR)myString);
        env->ReleaseStringChars(jstr, myString);
#else
        jbyteArray bytes = (jbyteArray) env->CallObjectMethod(jstr, 
                                                              MID_String_getBytes);
        
        jint len = env->GetArrayLength(bytes);
        
        env->GetByteArrayRegion(bytes, 0, len, (jbyte*) rString);

        env->DeleteLocalRef(bytes);
#endif        
    }

    if (CHECK_EXCEPTION(NULL)) {
        rc = FALSE;
    } 

    return rc;
}


void JavaModel::AttachCurrentThread() {
    JNIEnv *env  = NULL;

    JavaVMAttachArgs args;
    args.version = JNI_VERSION_1_2; 
    args.name    = NULL;
    args.group   = NULL;

    if (!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if(vm->AttachCurrentThread( (void **)&env, &args ) < 0) {
        JAVA_ERROR(_T("ATTACH_CURRENT_THREAD_FAILED"));
    }
    countAttachedThreads++;
}

void JavaModel::DetachCurrentThread() {
    if (!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->DetachCurrentThread() < 0) {
        JAVA_ERROR(_T("DETACH_CURRENT_THREAD_FAILED"));
    }
    countAttachedThreads--;
}

/*
 * Erzeuge und starte Java Virtual Machine.
 * Im Fehlerfall wird eine Fehlerkennung vom Typ long geworfen.
 */
void JavaModel::Start(const TCHAR* vmpath, const ACHAR* classpath, const ACHAR* debug_param, const ACHAR* extra_option) {
    JNIEnv *env               = NULL;
    InvocationFunctions  *ifn = NULL; 
    
    SetJVMDLL(vmpath);
    // Java Virtual Machine ist bereits gestartet
    if(vm) {
        return;
    }

    __try {
        // wirft Exception, wenn Bibliothek nicht gefunden wird
        if(!FindLibrary()) {
            JAVA_ERROR(_T("LIBRARY_NOT_FOUND"));
        }

        if(!(ifn = new InvocationFunctions())) {
            JAVA_ERROR(_T("OUT_OF_MEMORY"));
        }

        ifn->CreateJavaVM = 
                (jint (JNICALL *) (JavaVM **pvm, void **env, void *args)) 
                        GetProcAddress(hVM, "JNI_CreateJavaVM");
        
        if(!ifn->CreateJavaVM) {
            JAVA_ERROR(_T("ILLEGAL_ACCESS_ERROR"));
        }
    
        JavaVMInitArgs vm_args;    
        JavaVMOption options[50];

#ifdef UEBERLEGT
        ACHAR buffer[256];

        ACHAR* cpPtr = getenv("CLASSPATH");
    
        int t = cpPtr 
                ? sprintf(buffer, "-Djava.class.path=%s", cpPtr)
                : 0;     
        
        if (classpath) {
            if (t > 0) {
                t = sprintf(buffer + t, ";%s", classpath);    
            } else {
                t = sprintf(buffer, "-Djava.class.path=%s", classpath);
            }
        }    

        if (t > 0) {
            options[0].optionString = buffer;
            options[0].extraInfo = NULL;
            vm_args.nOptions = 1;
        } else {
            vm_args.nOptions = 0;
        }
#endif

        ACHAR buffer[65535];
        ACHAR autoClasspath[65535];
        const ACHAR* effectiveClasspath = classpath;
        ACHAR* envClasspath = getenv("CLASSPATH");
        RememberJavaClassPath(NULL);
        autoClasspath[0] = '\0';

        if ((!effectiveClasspath || effectiveClasspath[0] == '\0') &&
            envClasspath && envClasspath[0] != '\0') {
            effectiveClasspath = envClasspath;
        }

        if ((!effectiveClasspath || effectiveClasspath[0] == '\0') &&
            BuildClassPathFromExeLocation(autoClasspath, _countof(autoClasspath))) {
            effectiveClasspath = autoClasspath;
            dbwin_ass_failed_text(MODULENUM, __LINE__, _T("JAVA classpath fallback: auto-built from executable location"));
        }

        if (effectiveClasspath && effectiveClasspath[0] != '\0') {
            if (effectiveClasspath[0] == '"') {
              size_t cpLen = strlen(effectiveClasspath);
              if (cpLen >= 2 && effectiveClasspath[cpLen - 1] == '"') {
                  ACHAR classpathUnquoted[65535];
                  size_t copyLen = cpLen - 2;
                  if (copyLen >= _countof(classpathUnquoted)) {
                      copyLen = _countof(classpathUnquoted) - 1;
                  }
                  strncpy(classpathUnquoted, effectiveClasspath + 1, copyLen);
                  classpathUnquoted[copyLen] = '\0';
                  sprintf(buffer, "-Djava.class.path=%s", classpathUnquoted);
              } else {
                  sprintf(buffer, "-Djava.class.path=%s", effectiveClasspath + 1);
              }
            }
            else {
              sprintf(buffer, "-Djava.class.path=%s", effectiveClasspath);
            }
            options[0].optionString = buffer;
            options[0].extraInfo = NULL;
            vm_args.nOptions = 1;
            RememberJavaClassPath(buffer);
        } else {
            vm_args.nOptions = 0;
            RememberJavaClassPath(_T("<none>"));
        }

        if (debug_param) {
            options[vm_args.nOptions].optionString = "-Xdebug";
            options[vm_args.nOptions++].extraInfo = NULL;
            options[vm_args.nOptions].optionString = "-Xnoagent";
            options[vm_args.nOptions++].extraInfo = NULL;
            options[vm_args.nOptions].optionString = "-Djava.compiler=NONE";
            options[vm_args.nOptions++].extraInfo = NULL;
            static ACHAR params[256];
            sprintf(params,"-Xrunjdwp:%s",debug_param);
            options[vm_args.nOptions].optionString = params;
            options[vm_args.nOptions++].extraInfo = NULL;
            }
    
        if (extra_option) {
            ACHAR *option_begin = (ACHAR *)extra_option;
            while (*option_begin != '\0') {
                ACHAR *next_option = option_begin;
                while ((*next_option != ' ') && (*next_option != '\0')) next_option++;
                if (*next_option == ' ')
                    *next_option++ = '\0';
                options[vm_args.nOptions].optionString = option_begin;
                options[vm_args.nOptions++].extraInfo = NULL;
                option_begin = next_option;
            }
        }
    
        if (vm_args.nOptions > 0)
            vm_args.options = options;
        else
            vm_args.options = NULL;
        
        vm_args.version = JNI_VERSION_1_2;
        vm_args.ignoreUnrecognized = JNI_TRUE;

        /* Note that in JDK 1.2, there is no longer any need to call 
         * JNI_GetDefaultJavaVMInitArgs. 
         */
        
        if (ifn->CreateJavaVM(&vm, (void **)&env, &vm_args) != JNI_OK) {
            JAVA_ERROR(_T("VM_CREATION_FAILED"));
        }

        Class_java_lang_String = (jclass) env->NewWeakGlobalRef(
                env->FindClass(JAVA_API_STRING));

        if (Class_java_lang_String == NULL) {
#ifdef UNICODE
            LPCPLSTR uniClass = AnsiToBomStr (JAVA_API_STRING);
            JAVA_ERROR_PARAM(_T("CLASS_NOT_FOUND (class %s)"),TO_LPTSTR(uniClass));
            FreeGlobMem (uniClass);
#else
            JAVA_ERROR_PARAM(_T("CLASS_NOT_FOUND (class %s)"),JAVA_API_STRING);
#endif            
        }
    
        MID_String_init = env->GetMethodID(Class_java_lang_String, 
                                           JAVA_JNI_CONSTRUCTOR, 
                                           "([B)V");
        if (!MID_String_init) {
#ifdef UNICODE
            LPCPLSTR uniClass = AnsiToBomStr (JAVA_API_STRING);
            LPCPLSTR uniConstr = AnsiToBomStr (JAVA_JNI_CONSTRUCTOR);
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),TO_LPTSTR(uniClass),TO_LPTSTR(uniConstr),_T("([B)V"));
            FreeGlobMem (uniClass);
            FreeGlobMem (uniConstr);
#else           
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),JAVA_API_STRING,JAVA_JNI_CONSTRUCTOR,_T("([B)V"));
#endif
        }

        MID_String_getBytes = env->GetMethodID(Class_java_lang_String, 
                                              "getBytes", 
                                              "()[B");
        
        if (!MID_String_getBytes) {
#ifdef UNICODE
            LPCPLSTR uniClass = AnsiToBomStr (JAVA_API_STRING);
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),TO_LPTSTR(uniClass),_T("getBytes"),_T("()[B"));
            FreeGlobMem (uniClass);
#else           
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),JAVA_API_STRING,_T("getBytes"),_T("()[B"));
#endif
        }

        jclass cls = env->FindClass("java/lang/StringBuffer");
        
        if (!cls) {
            JAVA_ERROR_PARAM(_T("CLASS_NOT_FOUND (class %s)"),_T("java/lang/StringBuffer"));
        }
        
        MID_StringBuffer_append_S = env->GetMethodID(cls, 
                                                    "append", 
                                                    "(Ljava/lang/String;)Ljava/lang/StringBuffer;");

        if (!MID_StringBuffer_append_S) {
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),_T("java/lang/StringBuffer"),_T("append"),_T("(Ljava/lang/String;)Ljava/lang/StringBuffer;"));
        }

        MID_StringBuffer_append_J = env->GetMethodID(cls, 
                                                    "append", 
                                                    "(J)Ljava/lang/StringBuffer;");

        if (!MID_StringBuffer_append_J) {
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),_T("java/lang/StringBuffer"),_T("append"),_T("(J)Ljava/lang/StringBuffer;"));
        }

        if (ifn) { 
            delete(ifn);
            ifn = NULL;
        }
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        CHECK_EXCEPTION(NULL);
        
        if (ifn) {
            delete(ifn);
            ifn = NULL;
        }

        JAVA_ERROR(_T("error starting JVM"));
    }
}

unsigned __stdcall  tryToStop(void* vm) {
    ((JavaVM*) vm)->DestroyJavaVM();
    _endthreadex(0);
    return 0;
}


/*
 * Beendet die Java Virtual Machine.
 */
BOOL JavaModel::Stop() {
    if (vm) {
        unsigned ThreadId;
        HANDLE hstop = (HANDLE)_beginthreadex(NULL, 0, tryToStop, vm, 0, &ThreadId);
        DWORD exitCode;
        int tries = 0;
        while (GetExitCodeThread(hstop, &exitCode) 
               && exitCode == STILL_ACTIVE 
               && tries < 5) {
            Sleep(100);
            tries++;
        }

        if (exitCode == STILL_ACTIVE) {
            TerminateThread(hstop, 0);
        }
        CloseHandle(hstop);

        vm = NULL;
    }
    return TRUE;
}

void JavaModel::GetStaticFieldValue(const ACHAR* classDescriptor,
                                    const ACHAR* fieldName,
                                    const ACHAR* typeDescriptor,
                                    jvalue* result) {
    jclass cls       = NULL;
    jfieldID fid   = NULL;
    JNIEnv *env    = NULL;

    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }
    
    __try {
        if (!(cls = env->FindClass(classDescriptor))) {
#ifdef UNICODE
            LPCPLSTR uniClass = AnsiToBomStr ((LPASTR)classDescriptor);
            JAVA_ERROR_PARAM(_T("CLASS_NOT_FOUND (class %s)"),TO_LPTSTR(uniClass));
            FreeGlobMem (uniClass);
#else           
            ReportClassNotFoundWithContext(__LINE__, classDescriptor);
#endif            
        }

        if (!(fid = env->GetStaticFieldID(cls, fieldName, typeDescriptor))) {
#ifdef UNICODE
            LPCPLSTR uniClass = AnsiToBomStr ((LPASTR)classDescriptor);
            LPCPLSTR uniField = AnsiToBomStr ((LPASTR)fieldName);
            LPCPLSTR uniType = AnsiToBomStr ((LPASTR)typeDescriptor);
            JAVA_ERROR_PARAM3(_T("FIELD_ID_NOT_FOUND (class %s, field %s %s)"),TO_LPTSTR(uniClass),TO_LPTSTR(uniField),TO_LPTSTR(uniType));
            FreeGlobMem (uniClass);
            FreeGlobMem (uniField);
            FreeGlobMem (uniType);
#else           
            JAVA_ERROR_PARAM3(_T("FIELD_ID_NOT_FOUND (class %s, field %s %s)"),classDescriptor,fieldName,typeDescriptor);
#endif            
        }
        
        switch (*typeDescriptor) {
        case JAVA_JNI_BOOLEAN:
            result->z = env->GetStaticBooleanField(cls, fid);
            break;
        case JAVA_JNI_CHAR:
            result->c = env->GetStaticCharField(cls, fid);
            break;
        case JAVA_JNI_BYTE:
            result->b = env->GetStaticByteField(cls, fid);
            break;
        case JAVA_JNI_SHORT:
            result->s = env->GetStaticShortField(cls, fid);
            break;
        case JAVA_JNI_INT:
            result->i = env->GetStaticIntField(cls, fid);
            break;
        case JAVA_JNI_LONG:
            result->j = env->GetStaticLongField(cls, fid);
            break;
        case JAVA_JNI_FLOAT:
            result->f = env->GetStaticFloatField(cls, fid);
            break;
        case JAVA_JNI_DOUBLE:
            result->d = env->GetStaticDoubleField(cls, fid);
            break;
        case JAVA_JNI_OBJECT:
        case JAVA_JNI_ARRAY:
            jobject val = env->GetStaticObjectField(cls, fid);
            if (val != NULL) javaReferences++;
            result->l = env->NewGlobalRef(val);
#ifdef LOG_JAVAREFS
            LogReference(result->l, TRUE);
#endif
            break;
        }

        CHECK_EXCEPTION(NULL);

        env->PopLocalFrame(NULL);
        
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);
        
        env->PopLocalFrame(NULL);
        
        JAVA_ERROR(_T("error in GetStaticFieldValue"));
    }
}
    
void JavaModel::CallStaticMethodByNameV(jthrowable *ex,
                                        const ACHAR* classDescriptor, 
                                        const ACHAR* method, 
                                        const ACHAR* methodDescriptor,
                                        jvalue* result,
                                        va_list argList) {
    if (ex != NULL)
      *ex = NULL;
    // Referenz auf Klasse
    jclass     cls   = NULL;
    // Kennung der Methode
    jmethodID  mid  = NULL;
    JNIEnv     *env = NULL;
    ACHAR      *p   = (ACHAR*) methodDescriptor;
    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }        
    
    __try {
#ifdef UNICODE          
        if (!(cls = env->FindClass(classDescriptor))) {
            LPCPLSTR uniClass = AnsiToBomStr ((LPASTR)classDescriptor);
            JAVA_ERROR_PARAM(_T("CLASS_NOT_FOUND (class %s)"),TO_LPTSTR(uniClass));
            FreeGlobMem (uniClass);
        }

        if (!(mid = env->GetStaticMethodID(cls, method, methodDescriptor))) {
            LPCPLSTR uniClass = AnsiToBomStr ((LPASTR)classDescriptor);
            LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
            LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),TO_LPTSTR(uniClass),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc));
            FreeGlobMem (uniClass);
            FreeGlobMem (uniMethod);
            FreeGlobMem (uniMethodDesc);
        }
#else
        if (!(cls = env->FindClass(classDescriptor))) {
            ReportClassNotFoundWithContext(__LINE__, classDescriptor);
        }

        if (!(mid = env->GetStaticMethodID(cls, method, methodDescriptor))) {
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),classDescriptor,method,methodDescriptor);
        }
#endif

        // bewege zeiger zum R�ckgabetyp
        for (;*p != JAVA_JNI_END_ARGS && *p != STRING_TERMINATOR; p++);
        
        if(*p == STRING_TERMINATOR) {
            JAVA_ERROR(_T("ILLEGAL_ARGUMENT"));
        }

        p++;
        // if result == NULL, result is not of interest
        switch (*p) {
        case JAVA_JNI_VOID:
            env->CallStaticVoidMethodV(cls, mid, argList);
            break;
        case JAVA_JNI_BOOLEAN:
            if (result != NULL) {
                result->z = env->CallStaticBooleanMethodV(cls, mid, argList);
            } else {
                env->CallStaticBooleanMethodV(cls, mid, argList);    
            }
            break;
        case JAVA_JNI_CHAR:
            if (result != NULL) {
                result->c = env->CallStaticCharMethodV(cls, mid, argList);
            } else {
                env->CallStaticCharMethodV(cls, mid, argList);    
            }
            break;
        case JAVA_JNI_BYTE:
            if (result != NULL) {
                result->b = env->CallStaticByteMethodV(cls, mid, argList);
            } else {
                env->CallStaticByteMethodV(cls, mid, argList);
            }
            break;
        case JAVA_JNI_SHORT:
            if (result != NULL) {
                result->s = env->CallStaticShortMethodV(cls, mid, argList);
            } else {
                env->CallStaticShortMethodV(cls, mid, argList);
            }
            break;
        case JAVA_JNI_INT:
            if (result != NULL) {
                result->i = env->CallStaticIntMethodV(cls, mid, argList);
            } else {
                env->CallStaticIntMethodV(cls, mid, argList);
            }
            break;
        case JAVA_JNI_LONG:
            if (result != NULL) {
                result->j = env->CallStaticLongMethodV(cls, mid, argList);
            } else {
                env->CallStaticLongMethodV(cls, mid, argList);
            }
            break;
        case JAVA_JNI_FLOAT:
            if (result != NULL) {
                result->f = env->CallStaticFloatMethodV(cls, mid, argList);
            } else {
                env->CallStaticFloatMethodV(cls, mid, argList);
            }
            break;
        case JAVA_JNI_DOUBLE:
            if (result != NULL) {
                result->d = env->CallStaticDoubleMethodV(cls, mid, argList);
            } else {
                env->CallStaticDoubleMethodV(cls, mid, argList);
            }
            break;
        case JAVA_JNI_ARRAY:
        case JAVA_JNI_OBJECT:
            if (result != NULL) {
                jobject val = env->CallStaticObjectMethodV(cls, mid, argList);
                if (val != NULL) javaReferences++;
                result->l = env->NewGlobalRef(val);
#ifdef LOG_JAVAREFS
                LogReference(result->l, TRUE);
#endif
            } else {
                env->CallStaticObjectMethodV(cls, mid, argList);
            }
            break;        

        }

        CHECK_EXCEPTION(ex);

        env->PopLocalFrame(NULL);
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);
        
        env->PopLocalFrame(NULL);
        
        JAVA_ERROR(_T("error in CallStaticMethodByNameV"));
    }
}


jobject JavaModel :: CallConstructorV(jthrowable *ex,
                                      const ACHAR* classDescriptor,  
                                      const ACHAR* methodDescriptor,
                                      va_list argList) {
    if (ex != NULL)
      *ex = NULL;
    // Referenz auf Klasse
    jclass      cls  = NULL;
    // Kennung der Methode
    jmethodID cid  = NULL;    
    JNIEnv *env    = NULL;
    jobject result = NULL;

    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }

    __try {
#ifdef UNICODE          
        if (!(cls = env->FindClass(classDescriptor))) {
            LPCPLSTR uniClass = AnsiToBomStr ((LPASTR)classDescriptor);
            JAVA_ERROR_PARAM(_T("CLASS_NOT_FOUND (class %s)"),TO_LPTSTR(uniClass));
            FreeGlobMem (uniClass);
        }

        if (!(cid = env->GetMethodID(cls, JAVA_JNI_CONSTRUCTOR, methodDescriptor))) {
            LPCPLSTR uniClass = AnsiToBomStr ((LPASTR)classDescriptor);
            LPCPLSTR uniConstr = AnsiToBomStr (JAVA_JNI_CONSTRUCTOR);
            LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),TO_LPTSTR(uniClass),TO_LPTSTR(uniConstr),TO_LPTSTR(uniMethodDesc));
            FreeGlobMem (uniClass);
            FreeGlobMem (uniConstr);
            FreeGlobMem (uniMethodDesc);
        }
#else          
        if (!(cls = env->FindClass(classDescriptor))) {
            ReportClassNotFoundWithContext(__LINE__, classDescriptor);
        }
        if (!(cid = env->GetMethodID(cls, JAVA_JNI_CONSTRUCTOR, methodDescriptor))) {
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (class %s, method %s%s)"),classDescriptor,JAVA_JNI_CONSTRUCTOR,methodDescriptor);
        }
#endif

        jobject rc = env->NewObjectV(cls, cid, argList);
        if (rc != NULL) javaReferences++;
        result = env->NewGlobalRef(rc);
#ifdef LOG_JAVAREFS
        LogReference(result, TRUE);
#endif

        CHECK_EXCEPTION(ex);
        env->PopLocalFrame(NULL);

        return result;
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        CHECK_EXCEPTION(NULL);
        env->PopLocalFrame(NULL);
        JAVA_ERROR(_T("error in CallConstructorV"));
        return  NULL;
    }
}


struct ThreadPrivData {
  HANDLE mThread;
  JavaModel* jm;
  jthrowable *t_ex;
  jobject t_objhndl;
  ACHAR *t_method;
  ACHAR *t_methodDescriptor;
  jvalue *t_result;
  va_list t_marker;
  BOOL errorOccured;
};

BOOL ThreadIsRunning(void *privData) {
 DWORD dwExitCode;

 if (((ThreadPrivData *)privData)->mThread && GetExitCodeThread(((ThreadPrivData *)privData)->mThread, &dwExitCode) != 0) {
  return dwExitCode == STILL_ACTIVE;
 } else {
  return FALSE;
 }
}

unsigned __stdcall ThreadExecute(void* request) {
  ThreadPrivData *tpd = (ThreadPrivData *)request;
  tpd->errorOccured = FALSE;
  __try {
    tpd->jm->AttachCurrentThread();
    tpd->jm->CallMethodByNameV(tpd->t_ex, tpd->t_objhndl,
           tpd->t_method,
           tpd->t_methodDescriptor,
           tpd->t_result,
           tpd->t_marker);
    tpd->jm->DetachCurrentThread();
  } _except (EXCEPTION_EXECUTE_HANDLER) {
    tpd->errorOccured = TRUE;
  }
  _endthreadex(0);
  return 0;
}

void JavaModel::CallMethodByNameParallelV(jthrowable *ex,
                                          const jobject objhndl,
                                          const ACHAR* method,
                                          const ACHAR* methodDescriptor,
                                          jvalue* result,
                                          va_list argList) {

  if (ex != NULL)
    *ex = NULL;
  if (objhndl != NULL) {

    ThreadPrivData tpd;
    tpd.jm = this;
    tpd.t_ex = ex;
    tpd.t_objhndl = objhndl;
    BOOL withMouseAndKeyboard = FALSE;
    if (*method == '+') {
      withMouseAndKeyboard = TRUE;
      tpd.t_method = (ACHAR *)(method + 1);
      }
    else
      tpd.t_method = (ACHAR *)method;
    tpd.t_methodDescriptor = (ACHAR *)methodDescriptor;
    tpd.t_result = result;
    tpd.t_marker = argList;
    unsigned ThreadId;
    tpd.mThread = (HANDLE)_beginthreadex(NULL, 0, ThreadExecute, &tpd, 0, &ThreadId);

    CallJavaMessageLoop(withMouseAndKeyboard, &tpd);

    CloseHandle(tpd.mThread);
    tpd.mThread = NULL;

    if (tpd.errorOccured) {
#ifdef UNICODE
      LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
      LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
      JAVA_ERROR_PARAM2(_T("error in CallMethodByNameParallelV: error within ThreadExecute (method %s%s)"),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc));
      FreeGlobMem (uniMethod);
      FreeGlobMem (uniMethodDesc);    
#else    
      JAVA_ERROR_PARAM2(_T("error in CallMethodByNameParallelV: error within ThreadExecute (method %s%s)"),method,methodDescriptor);
#endif    
    }
  } else {
#ifdef UNICODE
    LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
    LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
    JAVA_ERROR_PARAM2(_T("error in CallMethodByNameParallelV: object reference is null (method %s%s)"),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc));
    FreeGlobMem (uniMethod);
    FreeGlobMem (uniMethodDesc);    
#else    
    JAVA_ERROR_PARAM2(_T("error in CallMethodByNameParallelV: object reference is null (method %s%s)"),method,methodDescriptor);
#endif    
  }
}

void JavaModel::CallMethodByNameV(jthrowable *ex,
                                  const jobject objhndl, 
                                  const ACHAR* method, 
                                  const ACHAR* methodDescriptor,
                                  jvalue* result,
                                  va_list argList) {

  if (ex != NULL)
    *ex = NULL;
  if (objhndl != NULL) {

    // Referenz auf Klasse
    jclass cls        = NULL;
    // Kennung der Methode
    jmethodID mid     = NULL;
    JNIEnv   *env     = NULL;
    ACHAR* p = (ACHAR*) methodDescriptor;

    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }

    __try {
        cls = env->GetObjectClass(objhndl);

        if (!(mid = env->GetMethodID(cls, method, methodDescriptor))) {
            TCHAR* pst = NULL;
            TCHAR* cause = NULL;
            jstring st = NULL;
            jmethodID getClass = env->GetMethodID(cls,"getClass","()Ljava/lang/Class;");
            if (getClass != NULL) {
                jobject class_object = env->CallObjectMethod(objhndl,getClass);
                if (class_object != NULL) {
                    jclass clscls = env->GetObjectClass(class_object);
                    if (clscls != NULL) {
                        jmethodID getName = env->GetMethodID (clscls,"getName", "()Ljava/lang/String;");
                        if (getName != NULL) {
                            st = (jstring) env->CallObjectMethod (class_object, getName);
                            if (st != NULL) {
#ifdef UNICODE          
                                pst = (LPTSTR)env->GetStringChars (st, NULL);
#else
                                pst = (LPTSTR)env->GetStringUTFChars (st, NULL);
#endif                                    
                                cause = _T("<pst == NULL>");
                            } else {
                                cause = _T("<getName returns NULL>");
                            }
                        } else {
                            cause = _T("<methodID getName == NULL>");
                        }
                    } else {
                        cause = _T("<clscls == NULL>");
                    }
                } else {
                    cause = _T("<class_object == NULL>");
                }
            } else {
                cause = _T("<methodID getClass == NULL>");
            }
#ifdef UNICODE
            LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
            LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (method %s%s, object %s)"),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc),pst != NULL ? pst : cause);
            FreeGlobMem (uniMethod);
            FreeGlobMem (uniMethodDesc);    
#else               
            JAVA_ERROR_PARAM3(_T("METHOD_ID_NOT_FOUND (method %s%s, object %s)"),method,methodDescriptor,pst != NULL ? pst : cause);
#endif            
            if (pst != NULL) {
#ifdef UNICODE
                env->ReleaseStringChars (st, (jchar*)pst);
#else               
                env->ReleaseStringUTFChars (st, pst);
#endif            
            }
            if (st != NULL) {
                env->DeleteLocalRef(st);
            }
        }

        // setze zeiger auf R�ckgabetyp
        for(; *p != JAVA_JNI_END_ARGS && *p != STRING_TERMINATOR; p++);
        if(*p == STRING_TERMINATOR) {
            JAVA_ERROR(_T("ILLEGAL_ARGUMENT"));
        }
        p++;

        switch(*p) {
        case JAVA_JNI_VOID: // void
            env->CallVoidMethodV(objhndl, mid, argList);
            break;
        case JAVA_JNI_BOOLEAN:
            if (result != NULL) {
                result->z = env->CallBooleanMethodV(objhndl, mid, argList);
            } else {
                env->CallBooleanMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_CHAR:
            if (result != NULL) {
                result->c = env->CallCharMethodV(objhndl, mid, argList);
            } else {
                env->CallCharMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_BYTE:
            if (result != NULL) {
                result->b = env->CallByteMethodV(objhndl, mid, argList);
            } else {
                env->CallByteMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_SHORT:
            if (result != NULL) {
                result->s = env->CallShortMethodV(objhndl, mid, argList);
            } else {
                env->CallShortMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_INT:
            if (result != NULL) {
                result->i = env->CallIntMethodV(objhndl, mid, argList);
            } else {
                env->CallIntMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_LONG:
            if (result != NULL) {
                result->j = env->CallLongMethodV(objhndl, mid, argList);
            } else {
                env->CallLongMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_FLOAT:
            if (result != NULL) {
                result->f = env->CallFloatMethodV(objhndl, mid, argList);
            } else {
                env->CallFloatMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_DOUBLE:
            if (result != NULL) {
                result->d = env->CallDoubleMethodV(objhndl, mid, argList);
            } else {
                env->CallDoubleMethodV(objhndl, mid, argList);
            }
            break;
        case JAVA_JNI_OBJECT:
        case JAVA_JNI_ARRAY:
            if (result != NULL) {
                jobject val = env->CallObjectMethodV(objhndl, mid, argList);
                if (val != NULL) javaReferences++;
                result->l = env->NewGlobalRef(val);
#ifdef LOG_JAVAREFS
                LogReference(result->l, TRUE);
#endif
            } else {
                env->CallObjectMethodV(objhndl, mid, argList);
            }
            break;
        }
        
        env->PopLocalFrame(NULL);

        CHECK_EXCEPTION(ex);

    } _except (EXCEPTION_EXECUTE_HANDLER) {
    // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);

        env->PopLocalFrame(NULL);

#ifdef UNICODE
        LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
        LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
        JAVA_ERROR_PARAM2(_T("error in CallMethodByNameV: error in execution (method %s%s)"),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc));
        FreeGlobMem (uniMethod);
        FreeGlobMem (uniMethodDesc);    
#else                   
        JAVA_ERROR_PARAM2(_T("error in CallMethodByNameV: object reference is null (method %s%s)"),method,methodDescriptor);
#endif    
    }
  } else {
#ifdef UNICODE
    LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
    LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
    JAVA_ERROR_PARAM2(_T("error in CallMethodByNameV: object reference is null (method %s%s)"),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc));
    FreeGlobMem (uniMethod);
    FreeGlobMem (uniMethodDesc);    
#else                   
    JAVA_ERROR_PARAM2(_T("error in CallMethodByNameV: object reference is null (method %s%s)"),method,methodDescriptor);
#endif    
  }

}

/**
 * Diese Methode l�scht das Objekt mit dem Schl�ssel ref
 * aus dem Objekt cache und die Referenz darauf,
 * damit garbage collection es beseitigen kann.
 * Im Fehlerfall wird eine Fehlerkennung vom Typ long geworfen.
 */
void JavaModel::Delete(jobject ref) {
    JNIEnv* env = NULL;

    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

#ifdef LOG_JAVAREFS
    LogReference(ref, FALSE);
#endif
    env->DeleteGlobalRef(ref);
    if (ref != NULL) javaReferences--;
}

/**
 * Diese Methode sucht und l�dt die angegebene dynamic link library. Dabei ist die Suchreihenfolge 1. Pfad, 2. Registry.
 * Die Registry wird nach global definierten Schl�sseln befragt. Bei Erfolg hat die Membervariable hVM eine
 * Referenz auf die Bibliothek und es wird true zur�ck gegeben. 
 * Sonst false;
 */
BOOL JavaModel::FindLibrary() {
//    ACHAR buffer[MAX_PATH];
//    ACHAR jvmdll[MAX_PATH];
    // BOOL localjava;

    // hVM = LoadLibrary(jvmdll);
/*
    if (!hVM) {
        Nameserver *ns = (Nameserver*)owp->GetFocus(TID_Nameserver);
        localjava = ns->GetVar("LOCALJAVA", buffer) && !stricmp(buffer, "true");
        if (localjava) {
            if (ns->GetVar("orbis32_home", buffer)) {
                sprintf(jvmdll, "%s%sjava\\bin\\hotspot\\jvm.dll", 
                    buffer, (buffer[strlen(buffer) - 1] != '\\') ? "\\" : "");
            }
        }
        else {
            if (ns->GetVar("orbis32_modul_home", buffer)) {
                sprintf(jvmdll, "%s%sjava\\bin\\hotspot\\jvm.dll", 
                    buffer, (buffer[strlen(buffer) - 1] != '\\') ? "\\" : "");
            }
        }
        hVM = LoadLibrary(jvmdll);
    }

    if (hVM) {
        ShowInfo(owp, jvmdll, "JAVA Virtual Machine");
    }
*/

    HKEY  hKey;
    DWORD dwBufSize;
    DWORD dwType;
    TCHAR vmDllRegistry[1024];
    TCHAR depDir[1024];
    DWORD loadErr;
    TCHAR loadAttempts[4096];
    BOOL sawBadExeFormat = FALSE;
    BOOL hasExplicitJvmPath = (jvmdll[0] != _T('\0'));
    loadAttempts[0] = _T('\0');
    RememberLoadedJvmPath(NULL);

    // suche zuerst im Pfad
    ResolveJvmDependencyDir(jvmdll, depDir, _countof(depDir));
    hVM = LoadJvmLibraryCandidate(jvmdll, &loadErr);
    if (hVM) {
        RememberLoadedJvmPath(jvmdll);
        return TRUE;
    }
    AppendLoadAttempt(loadAttempts, _countof(loadAttempts), jvmdll, depDir, loadErr, &sawBadExeFormat);
    if (hasExplicitJvmPath) {
        if (loadAttempts[0]) {
            TCHAR logMsg[4608];
            _stprintf(logMsg, _T("LIBRARY_NOT_FOUND details: searched %s"), loadAttempts);
            dbwin_ass_failed_text(MODULENUM, __LINE__, logMsg);
        }
        return FALSE;
    }

    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                    JAVA_REGISTRY_STRING_3, 
                    0, 
                    KEY_READ, 
                    &hKey) == ERROR_SUCCESS) {

        dwBufSize = sizeof(vmDllRegistry);
        vmDllRegistry[0] = _T('\0');
        if(RegQueryValueEx(hKey, 
                           _T("RuntimeLib"), 
                           NULL, 
                           &dwType, 
                           (LPBYTE) vmDllRegistry, 
                           &dwBufSize) == ERROR_SUCCESS) {
            ResolveJvmDependencyDir(vmDllRegistry, depDir, _countof(depDir));
            hVM = LoadJvmLibraryCandidate(vmDllRegistry, &loadErr);
            if (hVM) {
                RememberLoadedJvmPath(vmDllRegistry);
                RegCloseKey(hKey);
                return TRUE;
            }
            AppendLoadAttempt(loadAttempts, _countof(loadAttempts), vmDllRegistry, depDir, loadErr, &sawBadExeFormat);
        }

        RegCloseKey(hKey);
    }
    
    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                    JAVA_REGISTRY_STRING_4, 
                    0, 
                    KEY_READ, 
                    &hKey) == ERROR_SUCCESS) {

        dwBufSize = sizeof(vmDllRegistry);
        vmDllRegistry[0] = _T('\0');
        if(RegQueryValueEx(hKey, 
                           _T("RuntimeLib"), 
                           NULL, 
                           &dwType, 
                           (LPBYTE) vmDllRegistry, 
                           &dwBufSize) == ERROR_SUCCESS) {
            ResolveJvmDependencyDir(vmDllRegistry, depDir, _countof(depDir));
            hVM = LoadJvmLibraryCandidate(vmDllRegistry, &loadErr);
            if (hVM) {
                RememberLoadedJvmPath(vmDllRegistry);
                RegCloseKey(hKey);
                return TRUE;
            }
            AppendLoadAttempt(loadAttempts, _countof(loadAttempts), vmDllRegistry, depDir, loadErr, &sawBadExeFormat);
        }
        
        RegCloseKey(hKey);
    }

    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                    JAVA_REGISTRY_STRING_1, 
                    0, 
                    KEY_READ, 
                    &hKey) == ERROR_SUCCESS) {
        
        dwBufSize = sizeof(vmDllRegistry);
        vmDllRegistry[0] = _T('\0');
        if(RegQueryValueEx(hKey, 
                           _T("RuntimeLib"), 
                           NULL, 
                           &dwType, 
                           (LPBYTE) vmDllRegistry, 
                           &dwBufSize) == ERROR_SUCCESS) {
            ResolveJvmDependencyDir(vmDllRegistry, depDir, _countof(depDir));
            hVM = LoadJvmLibraryCandidate(vmDllRegistry, &loadErr);
            if (hVM) {
                RememberLoadedJvmPath(vmDllRegistry);
                RegCloseKey(hKey);
                return TRUE;
            }
            AppendLoadAttempt(loadAttempts, _countof(loadAttempts), vmDllRegistry, depDir, loadErr, &sawBadExeFormat);
        }
        
        RegCloseKey(hKey);
    }

    if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, 
                    JAVA_REGISTRY_STRING_2, 
                    0, 
                    KEY_READ, 
                    &hKey) == ERROR_SUCCESS) {
        
        dwBufSize = sizeof(vmDllRegistry);
        vmDllRegistry[0] = _T('\0');
        if(RegQueryValueEx(hKey, 
                           _T("RuntimeLib"), 
                           NULL, 
                           &dwType, 
                           (LPBYTE) vmDllRegistry, 
                           &dwBufSize) == ERROR_SUCCESS) {

            ResolveJvmDependencyDir(vmDllRegistry, depDir, _countof(depDir));
            hVM = LoadJvmLibraryCandidate(vmDllRegistry, &loadErr);
            if (hVM) {
                RememberLoadedJvmPath(vmDllRegistry);
                RegCloseKey(hKey);
                return TRUE;
            }
            AppendLoadAttempt(loadAttempts, _countof(loadAttempts), vmDllRegistry, depDir, loadErr, &sawBadExeFormat);
        }
        
        RegCloseKey(hKey);
    }

    if (loadAttempts[0]) {
        TCHAR logMsg[4608];
        _stprintf(logMsg, _T("LIBRARY_NOT_FOUND details: searched %s"), loadAttempts);
        dbwin_ass_failed_text(MODULENUM, __LINE__, logMsg);

        if (sawBadExeFormat) {
            TCHAR hintMsg[512];
            _stprintf(hintMsg,
                      _T("LIBRARY_NOT_FOUND hint: err=193 (ERROR_BAD_EXE_FORMAT), process=%s. Likely x86/x64 mismatch between DDS and jvm.dll."),
                      GetProcessBitnessText());
            dbwin_ass_failed_text(MODULENUM, __LINE__, hintMsg);
        }
    }

    return FALSE;
}


BOOL JavaModel::CheckStaticMethod(const ACHAR* classDescriptor, 
                                  const ACHAR* method, 
                                  const ACHAR* methodDescriptor) {
    // Referenz auf Klasse
    jclass        cls       = NULL;
    JNIEnv *env           = NULL;
    BOOL res = FALSE;
    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }
    
    __try {          
        if (cls = env->FindClass(classDescriptor)) {
            if (strcmp(method, JAVA_JNI_CONSTRUCTOR)) {
                if (env->GetStaticMethodID(cls, method, methodDescriptor))
                    res = TRUE;
            } else {
                if (env->GetMethodID(cls, JAVA_JNI_CONSTRUCTOR, methodDescriptor))
                    res = TRUE;
            }
        }

        // CHECK_EXCEPTION(NULL);
        jthrowable t = env->ExceptionOccurred ();
        if (t != NULL) {
            // env->ExceptionDescribe();
            env->ExceptionClear();
            }

        env->PopLocalFrame(NULL);
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);

        env->PopLocalFrame(NULL);

        JAVA_ERROR(_T("error in CheckStaticMethod"));
    }
    return res;
}


BOOL JavaModel::CheckMethod(const jobject objhndl,
                            const ACHAR* method,
                            const ACHAR* methodDescriptor) {

  BOOL res = FALSE;

  if (objhndl != NULL) {

    // Referenz auf Klasse
    jclass cls  = NULL;
    JNIEnv *env = NULL;
    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }
    
    __try {
        cls = env->GetObjectClass(objhndl);

        if (env->GetMethodID(cls, method, methodDescriptor))
            res = TRUE;

        // CHECK_EXCEPTION(NULL);
        jthrowable t = env->ExceptionOccurred ();
        if (t != NULL) {
            // env->ExceptionDescribe();
            env->ExceptionClear();
            }

        env->PopLocalFrame(NULL);
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);

        env->PopLocalFrame(NULL);

        JAVA_ERROR(_T("error in CheckMethod"));
    }
  } else {
#ifdef UNICODE
    LPCPLSTR uniMethod = AnsiToBomStr ((LPASTR)method);
    LPCPLSTR uniMethodDesc = AnsiToBomStr ((LPASTR)methodDescriptor);
    JAVA_ERROR_PARAM2(_T("error in CheckMethod: object reference is null (method %s%s)"),TO_LPTSTR(uniMethod),TO_LPTSTR(uniMethodDesc));
    FreeGlobMem (uniMethod);
    FreeGlobMem (uniMethodDesc);    
#else                       
    JAVA_ERROR_PARAM2(_T("error in CheckMethod: object reference is null (method %s%s)"),method,methodDescriptor);
#endif    
  }

  return res;
}


BOOL JavaModel::Instanceof(const jobject objhndl, 
                           const ACHAR* classDescriptor) {

  BOOL res = FALSE;

  if (objhndl != NULL) {

    // Referenz auf Klasse
    jclass cls  = NULL;
    JNIEnv *env = NULL;
    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }
    
    __try {
        if (cls = env->FindClass(classDescriptor)) {
            if (env->IsInstanceOf(objhndl, cls))
                res = TRUE;
        }

        // CHECK_EXCEPTION(NULL);
        jthrowable t = env->ExceptionOccurred ();
        if (t != NULL) {
            // env->ExceptionDescribe();
            env->ExceptionClear();
            }

        env->PopLocalFrame(NULL);
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);

        env->PopLocalFrame(NULL);

        JAVA_ERROR(_T("error in Instanceof"));
    }
  }
  return res;
}


GLOBALHANDLE JavaModel::GetJavaExceptionInfo(jthrowable ex,TCHAR *str) {

    GLOBALHANDLE res = NULL;

    JNIEnv *env = NULL;
    
    if(!vm) {
        JAVA_ERROR(_T("VM_NOT_STARTED"));
    }

    if (vm->GetEnv((void **)&env, JNI_VERSION_1_2) != JNI_OK) {
        JAVA_ERROR(_T("GET_ENVIRONMENT_FAILED"));
    }

    if (env->PushLocalFrame(10) < 0) {
        JAVA_ERROR(_T("OUT_OF_MEMORY"));
    }
    
    __try {
        res = GetJavaExceptionInfoInt(ex, env, str);

        env->PopLocalFrame(NULL);
    } _except (EXCEPTION_EXECUTE_HANDLER) {
        // etwas ist schief gegangen
        CHECK_EXCEPTION(NULL);

        env->PopLocalFrame(NULL);

        JAVA_ERROR(_T("error in GetJavaExceptionInfo"));
    }
    return res;
}
