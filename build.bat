@echo off
setlocal enableextensions enabledelayedexpansion

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

if /I "%~1"=="DBG" (
  if "%~2"=="" goto build_dbg
  call :build_selected "DBG" "%~2"
  goto done
)
if /I "%~1"=="OPT" (
  if "%~2"=="" goto build_opt
  call :build_selected "OPT" "%~2"
  goto done
)
if /I "%~1"=="ALL" (
  if "%~2"=="" goto build_all
  call :build_selected "ALL" "%~2"
  goto done
)
if "%~1"=="" goto build_all

echo Usage: build.bat [DBG^|OPT^|ALL] [module[,module...]]
echo Examples:
  echo   build.bat DBG ddsmem
  echo   build.bat OPT ddsseq
  echo   build.bat ALL ddsmem,ddsseq,dds
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

:build_selected
set "PROFILE=%~1"
set "REQUESTED=%~2"
set "REQUESTED=%REQUESTED:,= %"
set "SELECTED="
set "ROOT_REQ=0"

for %%R in (%REQUESTED%) do (
  if /I "%%~R"=="DDS" set "ROOT_REQ=1"
)

for %%M in (DDSMEM DMWAPI DBHELP COMPILE CTOOL IMAGE FRMOBJ HOOK DBCLEAN STATBAR TOOLBAR DBBTRV DDSODBC DDSSEQ DNETIN DNETNV RESTOOL) do (
  set "MATCH=0"
  for %%R in (%REQUESTED%) do (
    if /I "%%~R"=="%%M" set "MATCH=1"
  )
  if "!MATCH!"=="1" (
    if not "!SELECTED!"=="" set "SELECTED=!SELECTED! "
    set "SELECTED=!SELECTED!%%M"
  )
)

if "%SELECTED%"=="" if "%ROOT_REQ%"=="0" (
  echo ERROR: no matching module names found for: %REQUESTED%
  exit /b 1
)

if /I "%PROFILE%"=="ALL" (
  call :build_tree_selected "%ROOT%\%ACTVERS%_32.DBG" "DBG" "%SELECTED%" "%ROOT_REQ%"
  call :build_tree_selected "%ROOT%\%ACTVERS%_32.OPT" "OPT" "%SELECTED%" "%ROOT_REQ%"
  goto :eof
)
if /I "%PROFILE%"=="DBG" (
  call :build_tree_selected "%ROOT%\%ACTVERS%_32.DBG" "DBG" "%SELECTED%" "%ROOT_REQ%"
  goto :eof
)
if /I "%PROFILE%"=="OPT" (
  call :build_tree_selected "%ROOT%\%ACTVERS%_32.OPT" "OPT" "%SELECTED%" "%ROOT_REQ%"
  goto :eof
)

echo ERROR: unsupported profile %PROFILE%
exit /b 1

:build_tree_selected
set "TREE=%~1"
set "TAG=%~2"
set "SELECTED=%~3"
set "ROOT_REQ=%~4"

echo.
echo ===== Building %TAG% tree at %TREE% =====
if not "%SELECTED%"=="" (
  echo Selected modules: %SELECTED%
  for %%M in (%SELECTED%) do call :run_module "%TREE%\%%M" "%%M.BAT"
)
if "%ROOT_REQ%"=="1" (
  pushd "%TREE%" >nul
  call BUILD_DDS.BAT
  set "RC=%ERRORLEVEL%"
  if exist SUPER32.BAT call SUPER32.BAT
  popd >nul

  if not "%RC%"=="0" (
    echo ERROR: BUILD_DDS.BAT failed in %TREE% with code %RC%
    exit /b %RC%
  )
)

echo ===== Completed %TAG% tree =====
exit /b 0

:build_tree
set "TREE=%~1"
set "TAG=%~2"

echo.
echo ===== Building %TAG% tree at %TREE% =====
call :run_module "%TREE%\DDSMEM" "DDSMEM.BAT"
call :run_module "%TREE%\DMWAPI" "DMWAPI.BAT"
call :run_module "%TREE%\DBHELP" "DBHELP.BAT"
call :run_module "%TREE%\COMPILE" "COMPILE.BAT"
call :run_module "%TREE%\CTOOL" "CTOOL.BAT"
call :run_module "%TREE%\IMAGE" "IMAGE.BAT"
call :run_module "%TREE%\FRMOBJ" "FRMOBJ.BAT"
call :run_module "%TREE%\HOOK" "HOOK.BAT"
call :run_module "%TREE%\DBCLEAN" "DBCLEAN.BAT"
call :run_module "%TREE%\STATBAR" "STATBAR.BAT"
call :run_module "%TREE%\TOOLBAR" "TOOLBAR.BAT"
call :run_module "%TREE%\DBBTRV" "DBBTRV.BAT"
call :run_module "%TREE%\DDSODBC" "DDSODBC.BAT"
call :run_module "%TREE%\DDSSEQ" "DDSSEQ.BAT"
call :run_module "%TREE%\DNETIN" "DNETIN.BAT"
call :run_module "%TREE%\DNETNV" "DNETNV.BAT"
call :run_module "%TREE%\RESTOOL" "RESTOOL.BAT"

pushd "%TREE%" >nul
call BUILD_DDS.BAT
set "RC=%ERRORLEVEL%"
if exist SUPER32.BAT call SUPER32.BAT
popd >nul

if not "%RC%"=="0" (
  echo ERROR: BUILD_DDS.BAT failed in %TREE% with code %RC%
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
