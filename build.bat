@echo off
setlocal enableextensions enabledelayedexpansion

set "ROOT=%~dp0"
set "TOOLS=%ROOT%tools"
set "BUILD_FAILED=0"
  
if not exist "%TOOLS%\makec.bat" (
  echo ERROR: makec shim not found at "%TOOLS%\makec.bat"
  exit /b 2
)

where cl >NUL 2>&1
if errorlevel 1 call "%~dp0init_vc.bat"
if errorlevel 1 exit /b %ERRORLEVEL%

set "PATH=%TOOLS%;%PATH%"

if /I "%~1"=="DBG" (
  if "%~2"=="" goto build_dbg
  call :build_selected "DBG" "%~2 %~3 %~4 %~5 %~6 %~7 %~8 %~9"
  if errorlevel 1 set "BUILD_FAILED=1"
  goto done
)
if /I "%~1"=="OPT" (
  if "%~2"=="" goto build_opt
  call :build_selected "OPT" "%~2 %~3 %~4 %~5 %~6 %~7 %~8 %~9"
  if errorlevel 1 set "BUILD_FAILED=1"
  goto done
)
if /I "%~1"=="ALL" (
  if "%~2"=="" goto build_all
  call :build_selected "ALL" "%~2 %~3 %~4 %~5 %~6 %~7 %~8 %~9"
  if errorlevel 1 set "BUILD_FAILED=1"
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
call :build_tree "%ROOT%TARGET\DBG" "DBG"
if errorlevel 1 set "BUILD_FAILED=1"
call :build_tree "%ROOT%TARGET\OPT" "OPT"
if errorlevel 1 set "BUILD_FAILED=1"
popd >nul
goto done

:build_dbg
pushd "%ROOT%" >nul
call :build_tree "%ROOT%TARGET\DBG" "DBG"
if errorlevel 1 set "BUILD_FAILED=1"
popd >nul
goto done

:build_opt
pushd "%ROOT%" >nul
call :build_tree "%ROOT%TARGET\OPT" "OPT"
if errorlevel 1 set "BUILD_FAILED=1"
popd >nul
goto done

:build_selected
set "PROFILE=%~1"
set "REQUESTED=%~2"
set "REQUESTED=%REQUESTED:,= %"
set "SELECTED="
set "ROOT_REQ=0"
set "UNKNOWN="
set "SELECT_FAILED=0"

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

for %%R in (%REQUESTED%) do (
  set "KNOWN=0"
  if /I "%%~R"=="DDS" set "KNOWN=1"
  for %%M in (DDSMEM DMWAPI DBHELP COMPILE CTOOL IMAGE FRMOBJ HOOK DBCLEAN STATBAR TOOLBAR DBBTRV DDSODBC DDSSEQ DNETIN DNETNV RESTOOL) do (
    if /I "%%~R"=="%%M" set "KNOWN=1"
  )
  if "!KNOWN!"=="0" (
    if not "!UNKNOWN!"=="" set "UNKNOWN=!UNKNOWN!,"
    set "UNKNOWN=!UNKNOWN!%%~R"
  )
)

if not "!UNKNOWN!"=="" (
  echo ERROR: unknown module name^(s^): !UNKNOWN!
  echo Known modules: DDSMEM,DMWAPI,DBHELP,COMPILE,CTOOL,IMAGE,FRMOBJ,HOOK,DBCLEAN,STATBAR,TOOLBAR,DBBTRV,DDSODBC,DDSSEQ,DNETIN,DNETNV,RESTOOL,DDS
  exit /b 1
)

if "%SELECTED%"=="" if "%ROOT_REQ%"=="0" (
  echo ERROR: no matching module names found for: %REQUESTED%
  exit /b 1
)

if /I "%PROFILE%"=="ALL" (
  call :build_tree_selected "%ROOT%TARGET\DBG" "DBG" "%SELECTED%" "%ROOT_REQ%"
  if errorlevel 1 set "SELECT_FAILED=1"
  call :build_tree_selected "%ROOT%TARGET\OPT" "OPT" "%SELECTED%" "%ROOT_REQ%"
  if errorlevel 1 set "SELECT_FAILED=1"
  if "!SELECT_FAILED!"=="1" exit /b 1
  goto :eof
)
if /I "%PROFILE%"=="DBG" (
  call :build_tree_selected "%ROOT%TARGET\DBG" "DBG" "%SELECTED%" "%ROOT_REQ%"
  if errorlevel 1 exit /b 1
  goto :eof
)
if /I "%PROFILE%"=="OPT" (
  call :build_tree_selected "%ROOT%TARGET\OPT" "OPT" "%SELECTED%" "%ROOT_REQ%"
  if errorlevel 1 exit /b 1
  goto :eof
)

echo ERROR: unsupported profile %PROFILE%
exit /b 1

:build_tree_selected
set "TREE=%~1"
set "TAG=%~2"
set "SELECTED=%~3"
set "ROOT_REQ=%~4"
set "TREE_FAILED=0"

echo.
echo ===== Building %TAG% tree at %TREE% =====
if not "%SELECTED%"=="" (
  echo Selected modules: %SELECTED%
  for %%M in (%SELECTED%) do (
    call :run_module "%TREE%\%%M" "%%M.BAT"
    if errorlevel 1 set "TREE_FAILED=1"
  )
)
if "%ROOT_REQ%"=="1" (
  pushd "%TREE%" >nul
  call BUILD_DDS.BAT
  set "RC=%ERRORLEVEL%"
  if exist SUPER32.BAT call SUPER32.BAT
  popd >nul

  if not "%RC%"=="0" (
    echo ERROR: BUILD_DDS.BAT failed in %TREE% with code %RC%
    set "TREE_FAILED=1"
  )
)

if "%TREE_FAILED%"=="1" (
  echo ===== Completed %TAG% tree with errors =====
  exit /b 1
)
echo ===== Completed %TAG% tree =====
exit /b 0

:build_tree
set "TREE=%~1"
set "TAG=%~2"
set "TREE_FAILED=0"

echo.
echo ===== Building %TAG% tree at %TREE% =====
call :run_module "%TREE%\DDSMEM" "DDSMEM.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DMWAPI" "DMWAPI.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DBHELP" "DBHELP.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\COMPILE" "COMPILE.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\CTOOL" "CTOOL.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\IMAGE" "IMAGE.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\FRMOBJ" "FRMOBJ.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\HOOK" "HOOK.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DBCLEAN" "DBCLEAN.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\STATBAR" "STATBAR.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\TOOLBAR" "TOOLBAR.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DBBTRV" "DBBTRV.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DDSODBC" "DDSODBC.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DDSSEQ" "DDSSEQ.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DNETIN" "DNETIN.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\DNETNV" "DNETNV.BAT"
if errorlevel 1 set "TREE_FAILED=1"
call :run_module "%TREE%\RESTOOL" "RESTOOL.BAT"
if errorlevel 1 set "TREE_FAILED=1"

pushd "%TREE%" >nul
call BUILD_DDS.BAT
set "RC=%ERRORLEVEL%"
if exist SUPER32.BAT call SUPER32.BAT
popd >nul

if not "%RC%"=="0" (
  echo ERROR: BUILD_DDS.BAT failed in %TREE% with code %RC%
  set "TREE_FAILED=1"
)

:continue_build

if "%TREE_FAILED%"=="1" (
  echo ===== Completed %TAG% tree with errors =====
  exit /b 1
)
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

:done
echo.
if "%BUILD_FAILED%"=="1" (
  echo Build finished with errors.
  exit /b 1
)
echo Build finished successfully.
exit /b 0
