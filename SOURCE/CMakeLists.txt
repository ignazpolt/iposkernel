cmake_minimum_required(VERSION 3.20)
project(DDSApplication LANGUAGES CXX RC)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ResolvePinnedJava.cmake)
find_package(JNI REQUIRED)

# 1. Enforce the Visual Studio 2019 Toolset (v142) under VS 2026
set(CMAKE_GENERATOR_TOOLSET "v142" CACHE STRING "MSVC 2019 Toolset" FORCE)

# Enforce C++ Standard (adjust to 14 or 20 if your legacy project requires it)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Restore legacy MSVC for-loop scoping to support many legacy source files that
# rely on loop variables remaining available after the for(...) header.
# This is equivalent to the MSVC compiler option: /Zc:forScope-
if(MSVC)
  # Match legacy makec Debug behavior: disable CMake's default /RTC1 in Debug.
  foreach(_flag_var CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG)
    if(DEFINED ${_flag_var})
      string(REPLACE "/RTC1" "" ${_flag_var} "${${_flag_var}}")
      string(REPLACE "/RTCs" "" ${_flag_var} "${${_flag_var}}")
      string(REPLACE "/RTCu" "" ${_flag_var} "${${_flag_var}}")
      set(${_flag_var} "${${_flag_var}}" CACHE STRING "" FORCE)
    endif()
  endforeach()

  add_compile_options(
    $<$<C_COMPILER_ID:MSVC>:/Zc:forScope->
    $<$<CXX_COMPILER_ID:MSVC>:/Zc:forScope->
  )

  # Legacy makec parity for Debug builds across all modules:
  # - explicit DEBUG define
  # - disable MSVC runtime-init checks (/RTC*) that are not used by makec
  # - match warning/debug/optimization profile
  add_compile_definitions(
    WIN32
    _WINDOWS
    _CRT_SECURE_NO_WARNINGS
    $<$<CONFIG:Debug>:DEBUG>
  )
  add_compile_options(
    $<$<CONFIG:Debug>:/W3>
    $<$<CONFIG:Debug>:/Zi>
    $<$<CONFIG:Debug>:/Od>
  )
endif()

# 2. Collect all main executable C++ source and resource files
set(EXE_SOURCES
    ABOUT.CPP
    CONTCALC.CPP
    CYCSPL.CPP
    DBUPD.CPP
    DDS.CPP
    DDS.RC
    DDSDDE.CPP
    DDSDEB.CPP
    DDSOLE.CPP
    DDSSPELL.CPP
    DDSTOOL.CPP
    DIAGRAM.CPP
    DICT.CPP
    DLLCHILD.CPP
    DOCUMENT.CPP
    DSWTCH.CPP
    EXPR.CPP
    EXTCHILD.CPP
    EXTDLL.CPP
    FILEPROC.CPP
    FORM.CPP
    FORMAT.CPP
    FORMTOOL.CPP
    FUNC0.CPP
    FUNC1.CPP
    FUNC2.CPP
    FUNC3.CPP
    HEADTXT.CPP
    HLPFUNC.CPP
    INTERPR.CPP
    KISQUERY.CPP
    LIST.CPP
    LIST1.CPP
    LOCKHAND.CPP
    MAINDIGI.CPP
    MAINIMG.CPP
    MAINOBJ.CPP
    MAINSC2D.CPP
    MAINSND.CPP
    MDICHILD.CPP
    MDICLIEN.CPP
    MEMCHK.CPP
    MISC.CPP
    MOVETOOL.CPP
    MULTIDIM.CPP
    MULTIPRO.CPP
    NICNFLD.CPP
    NORMCALC.CPP
    ONESHOT.CPP
    OPTI.CPP
    POST_IT.CPP
    REGIO.CPP
    SERIAL.CPP
    SMOOTH.CPP
    SOCKET.CPP
    StdAfx.cpp
    STDDDE.CPP
    STRFNC.CPP
    TRACING.CPP
    TRACKWND.CPP
    USE.CPP
    VARCALL.CPP
    VERSION.CPP
    VTO.CPP
    VTOOBJ.CPP
    WBASE.CPP
)

# 3. Define the main executable target.
# The legacy build produces a Windows GUI binary (dds.exe), so configure
# DDSMain as a WIN32 executable and keep the historical output name.
add_executable(DDSMain WIN32 ${EXE_SOURCES})
target_include_directories(DDSMain PRIVATE ${JNI_INCLUDE_DIRS})
set_target_properties(DDSMain PROPERTIES
  OUTPUT_NAME dds
)

# 4. Legacy .DEF files were generated for a different toolchain and do not
# match the symbols emitted by the current MSVC linker. Keep the modern
# dllexport-based export model instead.

# 5. Global Include directory (Propagates automatically down to ALL submodules)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Include")

# Modern CMake: provide an INTERFACE target that exposes the same include paths
# so submodules can link against it when the whole tree is built from the parent.
add_library(ipos_includes INTERFACE)
target_include_directories(ipos_includes INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# 6. Include your submodule project trees
add_subdirectory(ddsmem)
add_subdirectory(dmwapi)
add_subdirectory(dbhelp)
add_subdirectory(compile)
add_subdirectory(ctool)
add_subdirectory(image)
add_subdirectory(frmobj)
add_subdirectory(hook)
add_subdirectory(dbclean)
add_subdirectory(statbar)
add_subdirectory(toolbar)
add_subdirectory(dbbtrv)
add_subdirectory(ddsodbc)
add_subdirectory(ddsseq)
add_subdirectory(dnetin)
add_subdirectory(dnetnv)
add_subdirectory(restool)

# 7. Link all submodule DLLs directly into your main EXE
target_link_libraries(DDSMain PRIVATE
    user32
    gdi32
    ole32
    version
    comdlg32
    winmm
    wsock32
    ws2_32
    ltfil_n
    ltkrn_n
    lttwn_n
    ltdis_n
    ddsmem
    hook
    dmwapi
    dbhelp
    compile
    ctool
    image
    frmobj
    hook
    dbclean
    statbar
    toolbar
    dbbtrv
    ddsodbc
    ddsseq
    dnetin
    dnetnv
)

# LeadTools import libraries are stored in COBJ32 and are built without SAFESEH
# metadata, so allow linking them into the legacy DDS executable.
target_link_directories(DDSMain PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../COBJ32
)
if(MSVC)
  target_link_options(DDSMain PRIVATE /INCREMENTAL:NO /SAFESEH:NO)
endif()

# 8. Force all output binaries (.exe and .dlls) into a unified bin directory for debugging
set_target_properties(DDSMain PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
foreach(SUB_MOD ddsmem dmwapi dbhelp compile ctool image frmobj hook dbclean statbar toolbar dbbtrv ddsodbc ddsseq dnetin dnetnv)
    set_target_properties(${SUB_MOD} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endforeach()
set_target_properties(restool PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
