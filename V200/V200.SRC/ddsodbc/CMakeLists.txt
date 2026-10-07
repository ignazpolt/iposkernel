cmake_minimum_required(VERSION 3.20)
project(DDSOdbcModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    ALTODBC.CPP
    APPSRC.CPP
    DDSODBC.CPP
    OPODBC.CPP
    DDSODBC.RC
)

# 2. Define this project as a shared library (DLL)
add_library(ddsodbc SHARED ${MODULE_SOURCES})

# 3. Use source-level DLLExport annotations from the legacy codebase and avoid
# CMake's auto-generated export map, which is incompatible with this toolchain.
set_target_properties(ddsodbc PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(ddsodbc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the historical DDSODBC link set.
target_link_libraries(ddsodbc PRIVATE odbc32 ddsmem dmwapi dbhelp)
