cmake_minimum_required(VERSION 3.20)
project(DmwapiModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    CNTMENU.CPP
    COSHINTE.CPP
    CSPELL.CPP
    CUSTCRTL.CPP
    CWORD.CPP
    CWORD1.CPP
    DMWAPI.CPP
    FINT.CPP
    FLDCOMBO.CPP
    FLIST.CPP
    FONT.CPP
    GETWORD.CPP
    IADVSINK.CPP
    ICLISITE.CPP
    MLIST.CPP
    MULTL.CPP
    OLE.CPP
    OLEOBJ.CPP
    POLINT.CPP
    PRCONFIG.CPP
    PRINTER.CPP
    RECONST.CPP
    SCHIEBE.CPP
    SHOWBEM.CPP
    SINGL.CPP
    VORONOI.CPP
    WORDWIN.CPP
    DMWAPI.RC
)

# 2. Define this project as a shared library (DLL)
add_library(dmwapi SHARED ${MODULE_SOURCES})

# 3. Do not auto-generate a .def from the full object list: the legacy DMWAPI
# export table uses a hand-maintained, toolchain-specific naming scheme that is
# not compatible with the current MSVC linker. Keep the source-level DLLExport
# declarations as the authoritative export mechanism.
set_target_properties(dmwapi PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it.
# If the parent defines ipos_includes, link it; otherwise provide a local
# fallback so this module can still be built standalone.
if (TARGET ipos_includes)
  target_link_libraries(dmwapi PRIVATE ipos_includes)
else()
  target_include_directories(dmwapi PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/..         # expose V200.SRC root (matches /I..\..\%ACTVERS%.SRC)
      ${CMAKE_CURRENT_SOURCE_DIR}/../Include # expose shared Include directory (contains GLOBMEM.H)
  )
endif()

# Ensure the MSVC resource compiler (RC) receives the same /I include flags
# when compiling .rc files in this target.
target_compile_options(dmwapi PRIVATE
  $<$<COMPILE_LANG_AND_ID:RC,MSVC>:/I${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<$<COMPILE_LANG_AND_ID:RC,MSVC>:/I${CMAKE_CURRENT_SOURCE_DIR}/../Include>
)

# 5. Link against necessary libraries
# ddsmem implements helpers like lstrncpy; ensure dmwapi links against it so
# unresolved externals are resolved when building the dmwapi DLL.
target_link_libraries(dmwapi PRIVATE ddsmem Dbghelp)
