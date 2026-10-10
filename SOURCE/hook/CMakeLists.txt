cmake_minimum_required(VERSION 3.20)
project(HookModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    HOOKSDLL.CPP
    DMWHOOK.RC
)

# 2. Define this project as a shared library (DLL)
# We name the target 'hook' to stay consistent with the folder name
add_library(hook SHARED ${MODULE_SOURCES})

# 3. Legacy .DEF files were generated for a different toolchain and do not
# match the symbols emitted by the current MSVC linker. Export symbols via
# dllexport instead of forcing an incompatible module definition.
set_target_properties(hook PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON
    OUTPUT_NAME dmwhook
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(hook PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
