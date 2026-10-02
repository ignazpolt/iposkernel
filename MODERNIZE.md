# MODERNIZE

## makec

`makec` is the legacy compile helper used by module batch files (for example `RESTOOL.BAT`) to compile sources, resources, and selected translation units.

### Steps for makec

1. Ensure MSVC tools are available (`cl.exe`), and initialize the VS developer environment if needed.
2. Resolve source patterns passed to `makec` (single file or wildcard).
3. Apply legacy extension fallback behavior:
   - if a requested `.cpp` file is missing, try the corresponding `.cpx`.
4. Compile sources with the selected profile (for example `MAKEC1`) and write object outputs.
5. Compile resource files (`.rc`) where requested (for example via `RCCOMP` profile).
6. Link only when all required object/resource outputs are available and the module link script requests it.

### TODO

| text | status | date |
|---|---|---|
| Delete `GENDICT.CPX` and remove remaining legacy references once no longer required by batch-based flows. | open | 2026-10-06 |

## CMake

This repository now uses a top-level CMake project with module-level subdirectories that mirror the legacy build order and dependency graph.

### Structure overview (main module and submodules)

- **Main module (application root):**
  - `V200.SRC/CMakeLists.txt`
  - Defines the primary executable target (`DDSMain`).
  - Registers shared include paths and adds all module subdirectories.
- **Submodules (DLLs and tools):**
  - Each module folder has its own `CMakeLists.txt`.
  - Most module targets are `SHARED` libraries (DLLs), while `restool` is a `WIN32` executable target.

### Main blocks in the top-level CMakeLists

1. **Project/toolchain baseline**
   - `cmake_minimum_required`, `project(...)`.
   - Toolset/compiler behavior (for example legacy `/Zc:forScope-` compatibility).
2. **Main executable source collection**
   - The full source list for `DDSMain`.
3. **Executable target creation**
   - `add_executable(DDSMain ...)`.
4. **Global include propagation**
   - shared include root and interface include target for submodules.
5. **Submodule registration**
   - `add_subdirectory(...)` for each module.
6. **Main executable linkage**
   - `target_link_libraries(DDSMain PRIVATE ...)` with all required module targets.
7. **Output layout**
   - Unified runtime output folder (`TARGET/bin`) for EXE/DLL outputs.

### Common pattern across submodule CMakeLists

Most submodule files follow the same template:

1. `cmake_minimum_required(...)` and `project(...)`
2. `set(MODULE_SOURCES ...)`
3. `add_library(<module> SHARED ${MODULE_SOURCES})` (or `add_executable` for tool modules)
4. `set_target_properties(... WINDOWS_EXPORT_ALL_SYMBOLS OFF)` to avoid incompatible auto-generated export maps with this legacy codebase
5. `target_include_directories(...)`
6. `target_link_libraries(...)` with module-specific internal/external dependencies
7. Optional target-specific linker options for legacy binary compatibility (for example `/SAFESEH:NO` when required by old third-party libs)

### Linker-critical points

- **Do not rely on auto-generated exports for these legacy modules.**
  - Source-level `DLLExport`/legacy export annotations are authoritative.
- **Respect legacy link sets from module `.L32`/`.LNK` metadata.**
  - Missing internal module links cause large unresolved symbol cascades.
- **Preserve required system/SDK libs per module.**
  - Example classes: `odbc32`, `winmm`, `comctl32`, `wsock32`, `ws2_32`, `advapi32`.
- **Account for legacy third-party libs and linker flags.**
  - Example: LeadTools libs from `COBJ32` plus `/SAFESEH:NO` where needed.

### Submodule dependencies and CMake representation

Dependencies are represented explicitly in each module via `target_link_libraries`.

- **Internal module dependencies**
  - Example pattern:
    - `dbhelp` depends on `ddsmem`, `dmwapi`
    - `compile` depends on `ddsmem`, `dbhelp`
    - `frmobj` depends on `ctool`, `dmwapi`, `ddsmem`, `dbhelp`, `image`
    - `ddsseq` depends on `ddsmem`, `compile`, `dmwapi`, `dbhelp`
- **Tool module dependencies**
  - `restool` links against multiple submodules because it orchestrates resource and script tooling for the main system.
- **External dependencies**
  - Added directly to the target that needs them via `target_link_libraries`.
  - Additional search paths are added via `target_link_directories` when legacy binary locations must be preserved.

In short: the modern CMake model reflects the legacy build graph by making every dependency explicit at target level, instead of relying on implicit linker behavior from old batch/link scripts.
