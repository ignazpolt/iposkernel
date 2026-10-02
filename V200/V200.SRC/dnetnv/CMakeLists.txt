cmake_minimum_required(VERSION 3.20)
project(DNetNvModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    DNETNV.CPP
    NNETAPI.CPP
    DNETNV.RC
)

# 2. Define this project as a shared library (DLL)
add_library(dnetnv SHARED ${MODULE_SOURCES})

# 3. Use source-level DLLExport annotations from the legacy codebase and avoid
# CMake's auto-generated export map, which is incompatible with this toolchain.
set_target_properties(dnetnv PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(dnetnv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the historical DNETNV link set.
target_link_libraries(dnetnv PRIVATE ddsmem wsock32 ws2_32)
