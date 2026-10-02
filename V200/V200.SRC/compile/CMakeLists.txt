cmake_minimum_required(VERSION 3.20)
project(CompileModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    CODEGEN.CPP
    COMPILE.CPP
    FNCPROT.CPP
    LEXSCAN.CPP
    PARSE.CPP
    PARSE1.CPP
    PRGICON.CPP
    TBVAR.CPP
    TWODIM.CPP
    WONSCHD.CPP
    COMPILE.RC
)

# 2. Define this project as a shared library (DLL)
add_library(compile SHARED ${MODULE_SOURCES})

# 3. The legacy code uses source-level DLLExport annotations rather than a
# generated export map, so keep the modern dllexport-based path and avoid the
# stale .def generation that is incompatible with this toolchain.
set_target_properties(compile PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(compile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the original legacy link set: compile depends on ddsmem and dbhelp for
# the shared helper APIs used throughout this module.
target_link_libraries(compile PRIVATE ddsmem dbhelp)
