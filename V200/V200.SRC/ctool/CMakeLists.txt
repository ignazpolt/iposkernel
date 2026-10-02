cmake_minimum_required(VERSION 3.20)
project(CToolModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    BARELEM.CPP
    BARELEM1.CPP
    BARELEM2.CPP
    BITLIST.CPP
    BUBBLES.CPP
    BUTTONS.CPP
    DDSLIST.CPP
    DLG3D.CPP
    HOTKEY.CPP
    ICONTOOL.CPP
    MAPPE.CPP
    MERGETXT.CPP
    MYLINE.CPP
    PEDIT.CPP
    TOOLBAR.CPP
    TOOLBAR.RC
    TRBIT.CPP
)

# 2. Define this project as a shared library (DLL)
add_library(ctool SHARED ${MODULE_SOURCES})

# 3. Use source-level DLLExport annotations from the legacy codebase and avoid
# CMake's auto-generated export map, which is incompatible with this toolchain.
set_target_properties(ctool PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(ctool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the original legacy link set from CTOOL.L32: ctool depends on the
# shared helper/runtime APIs provided by ddsmem, dmwapi, and dbhelp.
target_link_libraries(ctool PRIVATE ddsmem dmwapi dbhelp comctl32)
