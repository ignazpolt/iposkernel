cmake_minimum_required(VERSION 3.20)
project(DBBtrvModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    ALTBTRV.CPP
    BTRVSQL.CPP
    CMBTRV.CPP
    CVBTRV.CPP
    DBBTRV.CPP
    DCBTRV.CPP
    JOINBTRV.CPP
    OPBTRV.CPP
    OPBTRV1.CPP
    RSBTRV.CPP
    DBBTRV.RC
)

# 2. Define this project as a shared library (DLL)
add_library(dbbtrv SHARED ${MODULE_SOURCES})

# 3. Use source-level DLLExport annotations from the legacy codebase and avoid
# CMake's auto-generated export map, which is incompatible with this toolchain.
set_target_properties(dbbtrv PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(dbbtrv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the historical DBBTRV link set.
target_link_directories(dbbtrv PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../COBJ32
)
target_link_libraries(dbbtrv PRIVATE
    user32
    wbtrv32
    ddsmem
    dmwapi
    dbhelp
    compile
)

# wbtrv32 import library is built without SAFESEH metadata.
if(MSVC)
  target_link_options(dbbtrv PRIVATE /SAFESEH:NO)
endif()
