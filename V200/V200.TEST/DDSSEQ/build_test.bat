@echo off
setlocal

set "TEST_ROOT=%~dp0"

call "%~dp0..\..\..\init_vc.bat"
if errorlevel 1 exit /b %ERRORLEVEL%
call "%~dp0..\test_env.bat"
if errorlevel 1 exit /b %ERRORLEVEL%

cd /d "%TEST_ROOT%"

set "LIB=%TEST_LIB_ROOT%;%LIB%"
set "PATH=%TEST_DLL_ROOT%;%PATH%"

cl /nologo /EHsc /DWIN32 /I"%TEST_INCLUDE_ROOT%" /I"%TEST_SRC_ROOT%" ddsseq_harness.cpp /link /OUT:ddsseq_harness.exe /LIBPATH:"%TEST_LIB_ROOT%" dbhelp.lib ddsseq.lib ddsmem.lib dmwapi.lib compile.lib user32.lib kernel32.lib advapi32.lib

if errorlevel 1 (
  echo.
  echo ERROR: build failed.
  exit /b %ERRORLEVEL%
)

echo.
echo DDSSEQ harness build succeeded.
echo Executable: ddsseq_harness.exe
echo Active TEST_PROFILE=%TEST_PROFILE%
echo TEST_LIB_ROOT=%TEST_LIB_ROOT%
echo TEST_DLL_ROOT=%TEST_DLL_ROOT%
endlocal
