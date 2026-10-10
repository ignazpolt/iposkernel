cmake_minimum_required(VERSION 3.20)
project(ImageModule LANGUAGES CXX RC)

# 1. Collect all the C++ source files and resource files
set(MODULE_SOURCES
    DIBMAN.CPP
    IMGCOMPR.CPP
    MIMAGE.CPP
    MORPHING.CPP
    ROTIMG.CPP
    SOUND.CPP
    TIFFIMG.CPP
    TIFFIMG.RC
)

# 2. Define this project as a shared library (DLL)
add_library(image SHARED ${MODULE_SOURCES})

# 3. Use source-level DLLExport annotations from the legacy codebase and avoid
# CMake's auto-generated export map, which is incompatible with this toolchain.
set_target_properties(image PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS OFF
    OUTPUT_NAME tiffimg
)

# 4. Expose this directory's headers to any project that links against it
target_include_directories(image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 5. Match the historical IMAGE/TIFF link set:
#    - ddsmem/dmwapi provide shared helper APIs used across this module
#    - winmm provides wave/mmio APIs used by SOUND.CPP
#    - LeadTools libs provide L_* imaging functions used by DIBMAN/MIMAGE
target_link_directories(image PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../COBJ32
)
target_link_libraries(image PRIVATE
    ddsmem
    dmwapi
    winmm
    ltkrn_n
    ltfil_n
    lttwn_n
)

# LeadTools import libraries in COBJ32 are built without SAFESEH metadata.
# Allow linking this legacy dependency set on modern MSVC.
if(MSVC)
  target_link_options(image PRIVATE /SAFESEH:NO)
endif()
