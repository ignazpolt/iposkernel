cmake_minimum_required(VERSION 3.20)
project(DDSMemModule LANGUAGES CXX RC)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/ResolvePinnedJava.cmake)
find_package(JNI REQUIRED)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    DDSDEB_C.CPP
    DDSMEM.CPP
    GLOBMEM.CPP
    HASH.CPP
    JMODEL.CPP
    JMWRAP.CPP
    WAITWIN.CPP
    DDSMEM.RC
)

# 2. Define this project as a shared library (DLL)
add_library(ddsmem SHARED ${MODULE_SOURCES})

# 3. The legacy codebase exports symbols through explicit DLLExport/_export
# declarations in the source code. Auto-generating a .def from every symbol can
# pull in invalid operator names from the old C++ sources, so do not force the
# export-all fallback here.
set_target_properties(ddsmem PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(ddsmem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Link against necessary libraries
# JNI include dirs and libraries (FindJNI provides JNI_INCLUDE_DIRS and JNI_LIBRARIES)
target_include_directories(ddsmem PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(ddsmem PRIVATE ${JNI_LIBRARIES} Dbghelp)
