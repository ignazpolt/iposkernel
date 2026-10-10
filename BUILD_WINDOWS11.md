# Legacy DDS Build On Windows 11

This repository now includes a local `makec` compatibility shim so the existing build trees can run without the original `makec` tool.

## Added Files

- `tools/makec.bat`
- `tools/makec.ps1`
- `build-all.bat`

## What It Does

- Preserves the original module batch flow in:
  - `TARGET.DBG/*/*.BAT`
  - `TARGET.OPT/*/*.BAT`
- Uses a shim to compile `.cpp/.c` with `cl.exe` and `.rc` with `rc.exe`.
- Keeps original linker steps (`lnk.bat`) unchanged.
- Runs `SUPER32.BAT` after tree build to aggregate module `err` files.

## Preconditions

1. Start from an **x86 Visual Studio Developer Command Prompt**.
2. Ensure `cl.exe`, `link.exe`, and `rc.exe` are available in PATH.
3. Ensure required third-party/import libs exist for your target modules.
4. Ensure resource path expectations are satisfied (`C:\ipos_kernel\PICTURES`), or adapt your environment accordingly.

## Build Commands

From `c:\ipos_kernel`:

```bat
build.bat DBG
build.bat OPT
build.bat ALL
```

## Notes

- The shim currently applies debug-friendly compile flags for all profiles (`MAKEC1`, `COMPDLL`, `COMPDLL1`, default).
- Java JNI headers and CMake JNI link resolution (`jvm.lib`) are pinned first to `C:\ipos_host\JavaDeploy\JAVA\32Bit\ojdk1.8.0_201` (override with `IPOS_JAVA_HOME`, then `JAVA_HOME`).
- If a module needs profile-specific flags, adjust mapping in `tools/makec.ps1`.
- On compile/link failure, check per-module `err` files and `supererr` in the corresponding tree root.
