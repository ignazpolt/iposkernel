# Development

## Legacy DDS Build On Windows 11

### Getting started

Open a "Developer PowerShell 2019"

```PS
**********************************************************************
** Visual Studio 2019 Developer PowerShell v16.11.42
** Copyright (c) 2021 Microsoft Corporation
**********************************************************************
PS C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools>
```

Execute vcvars32

```PS
PS C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools> .\VC\Auxiliary\Build\vcvars32.bat

**********************************************************************
** Visual Studio 2019 Developer Command Prompt v16.11.42
** Copyright (c) 2021 Microsoft Corporation
**********************************************************************
[vcvarsall.bat] Environment initialized for: 'x86'
```

Change into the project folder and start code

```PS
PS C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools> cd C:\ipos_kernel\
PS C:\ipos_kernel> code .
```

This repository now includes a local `makec` compatibility shim so the existing build trees can run without the original `makec` tool.

### Added Files

- `tools/makec.bat`
- `tools/makec.ps1`
- `build.bat`
- `clean.bat`

### What It Does

- Preserves the original module batch flow in:
  - `V200_32.DBG/*/*.BAT`
  - `V200_32.OPT/*/*.BAT`
- Uses a shim to compile `.cpp/.c` with `cl.exe` and `.rc` with `rc.exe`.
- Keeps original linker steps (`lnk.bat`) unchanged.
- Runs `SUPER32.BAT` after tree build to aggregate module `err` files.

### Build Commands

From `c:\ipos_kernel`:

```bat
build.bat DBG
build.bat OPT
build.bat ALL
```

`ACTVERS` defaults to `V200` if not set.

### Notes

- The shim currently applies debug-friendly compile flags for all profiles (`MAKEC1`, `COMPDLL`, `COMPDLL1`, default).
- Java JNI headers and CMake JNI link resolution (`jvm.lib`) are pinned first to `C:\ipos_host\JavaDeploy\JAVA\32Bit\ojdk1.8.0_201` (override with `IPOS_JAVA_HOME`, then `JAVA_HOME`).
- If a module needs profile-specific flags, adjust mapping in `tools/makec.ps1`.
- On compile/link failure, check per-module `err` files and `supererr` in the corresponding tree root.

## CMake transition

Open and Launch
1. Launch Visual Studio 2026.
2. Click Open a local folder and select C:\ipos_kernel\V200\V200.SRC.
3. In the top toolbar configuration dropdown, select either VS 2019 Toolset (32-bit x86) or VS 2019 Toolset (64-bit x64) depending on your project type.
4. CMake will generate the cache and populate the compilation output inside C:\ipos_kernel\V200\TARGET\bin\DDSMain.exe along with all 14 companion DLLs.
To verify our setup matches your environment completely:
• Is your legacy application compiled as a 32-bit (x86) or 64-bit (x64) executable?
• Once you save the CMakeLists.txt and CMakePresets.json files and open the folder in Visual Studio, do you see a "CMake generation finished" message in your Output window, or are any file target names throwing a syntax error?
