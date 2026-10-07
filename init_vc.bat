@echo off
setlocal

where cl >NUL 2>&1
if not errorlevel 1 exit /b 0

where vswhere >NUL 2>&1
if not errorlevel 1 (
  for /f "usebackq delims=" %%I in (`vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2^>nul`) do (
    if exist "%%I\Common7\Tools\VsDevCmd.bat" (
      call "%%I\Common7\Tools\VsDevCmd.bat" -arch=x86
      exit /b 0
    )
  )
)

for %%I in (
  "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools"
  "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"
  "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional"
  "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise"
) do (
  if exist "%%~I\Common7\Tools\VsDevCmd.bat" (
    call "%%~I\Common7\Tools\VsDevCmd.bat" -arch=x86
    exit /b 0
  )
)

echo ERROR: Visual Studio C/C++ toolchain not found. Open a VS developer prompt or install MSVC.
exit /b 1
