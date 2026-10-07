set(IPOS_DEPLOYED_JAVA_HOME "C:/ipos_host/JavaDeploy/JAVA/32Bit/ojdk1.8.0_201")

set(_ipos_java_home "")
if(DEFINED ENV{IPOS_JAVA_HOME} AND NOT "$ENV{IPOS_JAVA_HOME}" STREQUAL "")
  set(_ipos_java_home "$ENV{IPOS_JAVA_HOME}")
elseif(EXISTS "${IPOS_DEPLOYED_JAVA_HOME}/include/jni.h")
  set(_ipos_java_home "${IPOS_DEPLOYED_JAVA_HOME}")
elseif(DEFINED ENV{JAVA_HOME} AND NOT "$ENV{JAVA_HOME}" STREQUAL "")
  set(_ipos_java_home "$ENV{JAVA_HOME}")
endif()

if(NOT _ipos_java_home STREQUAL "")
  file(TO_CMAKE_PATH "${_ipos_java_home}" _ipos_java_home)

  set(JAVA_HOME "${_ipos_java_home}" CACHE PATH "JNI Java home override" FORCE)
  set(ENV{JAVA_HOME} "${_ipos_java_home}")

  if(EXISTS "${_ipos_java_home}/include/jni.h")
    set(JAVA_INCLUDE_PATH "${_ipos_java_home}/include" CACHE PATH "JNI include path override" FORCE)
  endif()

  if(EXISTS "${_ipos_java_home}/include/win32/jni_md.h")
    set(JAVA_INCLUDE_PATH2 "${_ipos_java_home}/include/win32" CACHE PATH "JNI include path #2 override" FORCE)
  endif()

  set(_ipos_jvm_candidates
    "${_ipos_java_home}/lib/jvm.lib"
    "${_ipos_java_home}/lib/server/jvm.lib"
    "${_ipos_java_home}/jre/lib/i386/server/jvm.lib"
    "${_ipos_java_home}/jre/lib/server/jvm.lib"
  )

  foreach(_ipos_jvm_candidate IN LISTS _ipos_jvm_candidates)
    if(EXISTS "${_ipos_jvm_candidate}")
      set(JAVA_JVM_LIBRARY "${_ipos_jvm_candidate}" CACHE FILEPATH "JNI JVM library override" FORCE)
      break()
    endif()
  endforeach()

  set(_ipos_jawt_candidates
    "${_ipos_java_home}/lib/jawt.lib"
    "${_ipos_java_home}/jre/lib/i386/jawt.lib"
    "${_ipos_java_home}/jre/lib/jawt.lib"
  )

  foreach(_ipos_jawt_candidate IN LISTS _ipos_jawt_candidates)
    if(EXISTS "${_ipos_jawt_candidate}")
      set(JAVA_AWT_LIBRARY "${_ipos_jawt_candidate}" CACHE FILEPATH "JNI AWT library override" FORCE)
      break()
    endif()
  endforeach()

  message(STATUS "JNI Java root: ${_ipos_java_home}")
  if(DEFINED JAVA_JVM_LIBRARY AND NOT JAVA_JVM_LIBRARY STREQUAL "")
    message(STATUS "JNI JVM library: ${JAVA_JVM_LIBRARY}")
  endif()
  if(DEFINED JAVA_AWT_LIBRARY AND NOT JAVA_AWT_LIBRARY STREQUAL "")
    message(STATUS "JNI AWT library: ${JAVA_AWT_LIBRARY}")
  endif()
endif()
