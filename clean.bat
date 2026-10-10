@echo off
setlocal enableextensions

set "ROOT=%~dp0"

if /I "%~1"=="DBG" goto clean_dbg
if /I "%~1"=="OPT" goto clean_opt
if /I "%~1"=="ALL" goto clean_all
if "%~1"=="" goto clean_all

echo Usage: clean.bat [DBG^|OPT^|ALL]
exit /b 1

:clean_all
call :clean_tree "%ROOT%\TARGET\DBG" "DBG"
call :clean_tree "%ROOT%\TARGET\OPT" "OPT"
goto done

:clean_dbg
call :clean_tree "%ROOT%\TARGET\DBG" "DBG"
goto done

:clean_opt
call :clean_tree "%ROOT%\TARGET\OPT" "OPT"
goto done

:clean_tree
set "TREE=%~1"
set "TAG=%~2"

if not exist "%TREE%" (
  echo Skipping missing %TAG% tree at %TREE%
  exit /b 0
)

echo.
echo ===== Cleaning %TAG% tree at %TREE% =====

rd /s /q "%TREE%"
if errorlevel 1 (
  echo ERROR: failed to remove %TAG% tree at %TREE%
  exit /b 1
)

mkdir "%TREE%"
if errorlevel 1 (
  echo ERROR: failed to recreate %TAG% tree at %TREE%
  exit /b 1
)

echo ===== Cleaned %TAG% tree =====
exit /b 0

:done
echo.
echo Cleanup finished.
exit /b 0
