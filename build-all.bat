@echo off
setlocal enableextensions

if "%ACTVERS%"=="" set "ACTVERS=V200"

set "IPOS_KERNEL_ROOT=%~dp0"
set "TOOLS=%IPOS_KERNEL_ROOT%tools"
set "ROOT=%IPOS_KERNEL_ROOT%%ACTVERS%"
  
if not exist "%TOOLS%\makec.bat" (
  echo ERROR: makec shim not found at "%TOOLS%\makec.bat"
  exit /b 2
)

where cl >NUL 2>&1
if errorlevel 1 call :init_vc

set "PATH=%TOOLS%;%PATH%"

echo Using ACTVERS=%ACTVERS% in %ROOT%
echo Using tools from %TOOLS%

if /I "%~1"=="DBG" goto build_dbg
if /I "%~1"=="OPT" goto build_opt
if /I "%~1"=="ALL" goto build_all
if "%~1"=="" goto build_all

echo Usage: build-all.bat [DBG^|OPT^|ALL]
exit /b 1

:build_all
pushd "%ROOT%" >nul
call :build_tree "%ROOT%\%ACTVERS%_32.DBG" "DBG"
call :build_tree "%ROOT%\%ACTVERS%_32.OPT" "OPT"
popd >nul
goto done

:build_dbg
pushd "%ROOT%" >nul
call :build_tree "%ROOT%\%ACTVERS%_32.DBG" "DBG"
popd >nul
goto done

:build_opt
pushd "%ROOT%" >nul
call :build_tree "%ROOT%\%ACTVERS%_32.OPT" "OPT"
popd >nul
goto done

:build_tree
set "TREE=%~1"
set "TAG=%~2"

echo.
echo ===== Building %TAG% tree at %TREE% =====

call :run_module "%TREE%\COMPILE" "COMPILE.BAT"
call :run_module "%TREE%\DDSMEM" "DDSMEM.BAT"
call :run_module "%TREE%\CTOOL" "CTOOL.BAT"
call :run_module "%TREE%\DMWAPI" "DMWAPI.BAT"
call :run_module "%TREE%\FRMOBJ" "FRMOBJ.BAT"
call :run_module "%TREE%\HOOK" "HOOK.BAT"
call :run_module "%TREE%\IMAGE" "IMAGE.BAT"
call :run_module "%TREE%\DBBTRV" "DBBTRV.BAT"
call :run_module "%TREE%\DBHELP" "DBHELP.BAT"
call :run_module "%TREE%\DBCLEAN" "DBCLEAN.BAT"
call :run_module "%TREE%\STATBAR" "STATBAR.BAT"
call :run_module "%TREE%\RESTOOL" "RESTOOL.BAT"
call :run_module "%TREE%\TOOLBAR" "TOOLBAR.BAT"
call :run_module "%TREE%\DDSODBC" "DDSODBC.BAT"
call :run_module "%TREE%\DDSORA" "DDSORA.BAT"
call :run_module "%TREE%\DDSSEQ" "DDSSEQ.BAT"
call :run_module "%TREE%\DNETIN" "DNETIN.BAT"
call :run_module "%TREE%\DNETNV" "DNETNV.BAT"

pushd "%TREE%" >nul
call CLINICUM.BAT
set "RC=%ERRORLEVEL%"
if exist SUPER32.BAT call SUPER32.BAT
popd >nul

if not "%RC%"=="0" (
  echo ERROR: CLINICUM.BAT failed in %TREE% with code %RC%
  exit /b %RC%
)

:continue_build

echo ===== Completed %TAG% tree =====
exit /b 0

:run_module
set "MDIR=%~1"
set "MBAT=%~2"

echo.
echo --- %MBAT% in %MDIR% ---
pushd "%MDIR%" >nul
call "%MBAT%"
set "RC=%ERRORLEVEL%"
popd >nul
if not "%RC%"=="0" (
  echo ERROR: %MBAT% failed in %MDIR% with code %RC%
  exit /b %RC%
)
exit /b 0

:init_vc
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
  "C:\Program Files\Microsoft Visual Studio\2022\BuildTools"
  "C:\Program Files\Microsoft Visual Studio\2022\Community"
  "C:\Program Files\Microsoft Visual Studio\2022\Professional"
  "C:\Program Files\Microsoft Visual Studio\2022\Enterprise"
  "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools"
  "C:\Program Files (x86)\Microsoft Visual Studio\2022\Community"
  "C:\Program Files (x86)\Microsoft Visual Studio\2022\Professional"
  "C:\Program Files (x86)\Microsoft Visual Studio\2022\Enterprise"
) do (
  if exist "%%~I\Common7\Tools\VsDevCmd.bat" (
    call "%%~I\Common7\Tools\VsDevCmd.bat" -arch=x86
    exit /b 0
  )
)

echo ERROR: Visual Studio C/C++ toolchain not found. Open a VS developer prompt or install MSVC.
exit /b 1

:done
echo.
echo Build finished.
exit /b 0
