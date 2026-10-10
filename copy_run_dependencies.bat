@echo off
setlocal enableextensions enabledelayedexpansion

set "MODE=%~1"
if /I "%MODE%"=="DBG" goto mode_ok
if /I "%MODE%"=="OPT" goto mode_ok

echo ERROR: copy_run_dependencies.bat requires mode DBG or OPT.
exit /b 1

:mode_ok
set "ROOT=%~dp0"
set "LIB_DIR=%ROOT%LIB32"
set "SOURCE_SEQ_DIR=%ROOT%SEQ"
set "TARGET_ROOT=%ROOT%TARGET"
set "TARGET_DIR=%TARGET_ROOT%\%MODE%"
set "TARGET_SEQ_DIR=%TARGET_ROOT%\SEQ"

if not exist "%LIB_DIR%\" (
  echo ERROR: run dependencies folder not found: "%LIB_DIR%"
  exit /b 1
)
if not exist "%SOURCE_SEQ_DIR%\" (
  echo ERROR: source SEQ folder not found: "%SOURCE_SEQ_DIR%"
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

if not exist "%LIB_DIR%\*.dll" (
  echo ERROR: no DLL files found in "%LIB_DIR%"
  exit /b 1
)

copy /Y "%LIB_DIR%\*.dll" "%TARGET_DIR%\" >nul
set "COPY_RC=%ERRORLEVEL%"
if not "%COPY_RC%"=="0" (
  echo ERROR: failed to copy DLL dependencies to "%TARGET_DIR%" ^(copy code %COPY_RC%^)
  exit /b %COPY_RC%
)

if exist "%LIB_DIR%\*.jar" (
  copy /Y "%LIB_DIR%\*.jar" "%TARGET_DIR%\" >nul
  set "COPY_RC=%ERRORLEVEL%"
  if not "%COPY_RC%"=="0" (
    echo ERROR: failed to copy JAR dependencies to "%TARGET_DIR%" ^(copy code %COPY_RC%^)
    exit /b %COPY_RC%
  )
)

set "SOURCE_SEQ_COUNT=0"
for %%F in ("%SOURCE_SEQ_DIR%\*.seq") do (
  if exist "%%~fF" set /a SOURCE_SEQ_COUNT+=1
)
if not "%SOURCE_SEQ_COUNT%"=="5" (
  echo ERROR: expected 5 source SEQ files in "%SOURCE_SEQ_DIR%", found %SOURCE_SEQ_COUNT%
  exit /b 1
)

set "TARGET_SEQ_COUNT=0"
if exist "%TARGET_SEQ_DIR%\" (
  for %%F in ("%TARGET_SEQ_DIR%\*.seq") do (
    if exist "%%~fF" set /a TARGET_SEQ_COUNT+=1
  )
)

set "MISSING_SEQ=0"
for %%F in ("%SOURCE_SEQ_DIR%\*.seq") do (
  if not exist "%TARGET_SEQ_DIR%\%%~nxF" set "MISSING_SEQ=1"
)

if "%TARGET_SEQ_COUNT%"=="5" if "%MISSING_SEQ%"=="0" goto done

if not exist "%TARGET_SEQ_DIR%\" (
  mkdir "%TARGET_SEQ_DIR%"
  if errorlevel 1 (
    echo ERROR: failed to create "%TARGET_SEQ_DIR%"
    exit /b 1
  )
)

if "%MISSING_SEQ%"=="1" (
  copy /Y "%SOURCE_SEQ_DIR%\*.seq" "%TARGET_SEQ_DIR%\" >nul
  set "COPY_RC=%ERRORLEVEL%"
  if not "%COPY_RC%"=="0" (
    echo ERROR: failed to copy SEQ files to "%TARGET_SEQ_DIR%" ^(copy code %COPY_RC%^)
    exit /b %COPY_RC%
  )
)

:done
exit /b 0
