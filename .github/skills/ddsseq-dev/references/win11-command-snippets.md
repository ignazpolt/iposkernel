# Win11 Command Snippets for DDSSEQ

Use these commands during DDSSEQ build and linker triage on Windows 11.

## Preferred Shell Policy

- Use PowerShell for MSVC tools and response-file linking.
- Use cmd for legacy batch flows requiring environment variables.
- Use Git Bash mainly for file and text search.

## 1) Compile only OPSEQ

PowerShell:

    Set-Location C:\ipos_kernel\V200\V200_32.DBG\DDSSEQ
    powershell -NoProfile -ExecutionPolicy Bypass -File C:\ipos_kernel\TOOLS\makec.ps1 ../../V200.SRC/ddsseq/OPSEQ.CPP OPSEQ.obj COMPDLL1

## 2) Inspect emitted DataRes symbols in OPSEQ.obj

Git Bash or PowerShell:

    cd /c/ipos_kernel
    MSYS2_ARG_CONV_EXCL='*' dumpbin /symbols V200/V200_32.DBG/DDSSEQ/OPSEQ.obj | grep -i "DataRes_"

If grep is unavailable in PowerShell, use:

    dumpbin /symbols C:\ipos_kernel\V200\V200_32.DBG\DDSSEQ\OPSEQ.obj | findstr /I DataRes_

## 3) Rebuild DDSSEQ resources and relink from module folder

PowerShell:

    Set-Location C:\ipos_kernel\V200\V200_32.DBG\DDSSEQ
    Copy-Item ..\..\V200.SRC\DDSSEQ\ddsseq.L32 . -Force
    Copy-Item ..\..\V200.SRC\DDSSEQ\ddsseq32.def . -Force
    rc.exe -r -v -dWIN32 -foddsseq.res /I..\..\V200.SRC\DDSSEQ /I..\..\V200.SRC\Include /I..\..\V200.SRC ..\..\V200.SRC\DDSSEQ\ddsseq.rc
    & "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Tools\MSVC\14.29.30133\bin\Hostx86\x86\link.exe" /DLL /DEBUG @ddsseq.l32

## 4) Verify output artifacts

PowerShell:

    Get-Item C:\ipos_kernel\V200\V200_32.DBG\DDSSEQ\ddsseq.dll, C:\ipos_kernel\V200\V200_32.DBG\DDSSEQ\ddsseq.lib, C:\ipos_kernel\V200\V200_32.DBG\DDSSEQ\ddsseq.exp

## 5) Full DBG build from repository root

cmd:

    cd /d C:\ipos_kernel
    build-all.bat DBG

## Common Pitfalls

- Running link in Git Bash may call GNU link instead of MSVC link.
- Missing ACTVERS in cmd batch context can make module scripts no-op.
- If linker reports DataRes unresolved symbols, first confirm OPSEQ.obj was rebuilt from the current source.
