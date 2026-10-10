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

for /r "%TREE%" %%F in (*.obj *.dll *.lib *.exp *.res *.map *.exe *.pdb *.ilk *.idb *.sbr *.pch *.manifest *.log *.tmp *.err *.fts *.gid *.hlp *.rsp *.tlog *.lastbuildstate *.l32 *.def err supererr) do (
  call :delete_if_safe "%%~F"
)

for %%F in ("err" "supererr") do (
  if exist "%TREE%\%%~F" del /q /f "%TREE%\%%~F"
)

echo ===== Cleaned %TAG% tree =====
exit /b 0

:delete_if_safe
set "FILE=%~1"
set "EXT=%~x1"

if /I "%EXT%"==".bat" exit /b 0
if /I "%EXT%"==".lin" exit /b 0
if /I "%EXT%"==".inc" exit /b 0
if /I "%EXT%"==".rc" exit /b 0
if /I "%EXT%"==".c" exit /b 0
if /I "%EXT%"==".cpp" exit /b 0
if /I "%EXT%"==".h" exit /b 0
if /I "%EXT%"==".hpp" exit /b 0
if /I "%EXT%"==".lnk" exit /b 0
if /I "%EXT%"==".mak" exit /b 0
if /I "%EXT%"==".txt" exit /b 0
if /I "%EXT%"==".md" exit /b 0

if exist "%FILE%" del /q /f "%FILE%"
exit /b 0

:done
echo.
echo Cleanup finished.
exit /b 0
