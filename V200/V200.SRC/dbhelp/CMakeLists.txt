cmake_minimum_required(VERSION 3.20)
project(DBHelpModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    CMDFIFO.CPP
    CMDSORT.CPP
    DATE.CPP
    DBHELP.CPP
    DBLIST.CPP
    DBRECORD.CPP
    DBREQ.CPP
    DLLADMIN.CPP
    DLLNAME.CPP
    INTTABLE.CPP
    NETWORK.CPP
    REP.CPP
    RESADMIN.CPP
    RESSQL.CPP
    SCRIPTHD.CPP
    SHOWDATA.CPP
    SQLCONN.CPP
    TBDEF.CPP
    TBDIFF.CPP
    TIME.CPP
    DBHELP.RC
)

# 2. Define this project as a shared library (DLL)
add_library(dbhelp SHARED ${MODULE_SOURCES})

# 3. The project exports via source annotations rather than a generated .def
# file; the CMake auto-def path is incompatible with these legacy names.
set_target_properties(dbhelp PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(dbhelp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Link against the legacy support libraries that provide the helper APIs used
# by dbhelp (memory handling, ini access, Win32 wrappers, and shared DLL helpers).
target_link_libraries(dbhelp PRIVATE ddsmem dmwapi)
