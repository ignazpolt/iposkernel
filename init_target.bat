@echo off
setlocal enableextensions

set "MODE=%~1"
if /I "%MODE%"=="DBG" goto mode_ok
if /I "%MODE%"=="OPT" goto mode_ok

echo ERROR: init_target.bat requires mode DBG or OPT.
exit /b 1

:mode_ok
set "ROOT=%~dp0"
set "TOOLS_BUILD=%ROOT%TOOLS\build"
set "TARGET_ROOT=%ROOT%TARGET"
set "SOURCE_DIR=%TOOLS_BUILD%\%MODE%"
set "TARGET_DIR=%TARGET_ROOT%\%MODE%"

if not exist "%SOURCE_DIR%\" (
  echo ERROR: source build folder not found: "%SOURCE_DIR%"
  exit /b 1
)

if not exist "%TARGET_ROOT%\" (
  mkdir "%TARGET_ROOT%"
  if errorlevel 1 (
    echo ERROR: failed to create "%TARGET_ROOT%"
    exit /b 1
  )
)

if not exist "%TARGET_DIR%\" (
  mkdir "%TARGET_DIR%"
  if errorlevel 1 (
    echo ERROR: failed to create "%TARGET_DIR%"
    exit /b 1
  )
)

xcopy "%SOURCE_DIR%\*" "%TARGET_DIR%\" /E /I /Y >nul
set "COPY_RC=%ERRORLEVEL%"
if "%COPY_RC%"=="0" exit /b 0
if "%COPY_RC%"=="1" exit /b 0

echo ERROR: failed to synchronize "%SOURCE_DIR%" to "%TARGET_DIR%" ^(xcopy code %COPY_RC%^)
exit /b %COPY_RC%
