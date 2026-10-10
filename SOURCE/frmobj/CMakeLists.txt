cmake_minimum_required(VERSION 3.20)
project(FrmObjModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    CUBSPL.CPP
    CUTEDIT.CPP
    DIGCNF.CPP
    FRMOBJ.CPP
    FRMOBJ1.CPP
    FRMOBJ2.CPP
    FRMOBJ3.CPP
    FRMOBJ4.CPP
    FRMOBJ5.CPP
    FRMOBJ6.CPP
    FRMTABLE.CPP
    METAPLAY.CPP
    MOVEOBJ.CPP
    NAMFLD.CPP
    PAINT.CPP
    ROTCENT.CPP
    SC2D.CPP
    SDOC.CPP
    TRCOBJ.CPP
    WMFCACHE.CPP
    FRMOBJ.RC
)

# 2. Define this project as a shared library (DLL)
add_library(frmobj SHARED ${MODULE_SOURCES})

# 3. Use source-level DLLExport annotations from the legacy codebase and avoid
# CMake's auto-generated export map, which is incompatible with this toolchain.
set_target_properties(frmobj PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(frmobj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the historical FRMOBJ link set:
#    - ctool, dmwapi, ddsmem, dbhelp, image provide shared APIs used here
#    - LeadTools libs provide L_* imaging symbols used by tracing/image objects
target_link_directories(frmobj PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../COBJ32
)
target_link_libraries(frmobj PRIVATE
    ctool
    dmwapi
    ddsmem
    dbhelp
    image
    ltkrn_n
    ltfil_n
)

# LeadTools import libraries in COBJ32 are built without SAFESEH metadata.
if(MSVC)
  target_link_options(frmobj PRIVATE /SAFESEH:NO)
endif()
