@echo off
setlocal

set "TEST_ROOT=%~dp0"
set "TEST_MODE=%~1"
if "%TEST_MODE%"=="" set "TEST_MODE=all"

call "%~dp0..\..\..\init_vc.bat"
if errorlevel 1 exit /b %ERRORLEVEL%
call "%~dp0..\test_env.bat"
if errorlevel 1 exit /b %ERRORLEVEL%

set "SEQ_SOURCE=%V200_ROOT%\SEQ"
set "SEQ_TARGET=%V200_TEST_ROOT%SEQ"
set "INI_SOURCE=%TEST_ROOT%DMW.INI"
set "INI_RUNTIME=%TEST_ROOT%DMW.INI"

if not exist "%INI_SOURCE%" (
  echo ERROR: Missing %INI_SOURCE%
  exit /b 1
)

if not exist "%SEQ_SOURCE%" (
  echo ERROR: Missing %SEQ_SOURCE%
  exit /b 1
)

if not exist "%SEQ_TARGET%" mkdir "%SEQ_TARGET%"
robocopy "%SEQ_SOURCE%" "%SEQ_TARGET%" *.* /E /NFL /NDL /NJH /NJS /NC /NS /NP >nul
if errorlevel 8 (
  echo ERROR: Failed to copy SEQ files from %SEQ_SOURCE% to %SEQ_TARGET%.
  exit /b 1
)

powershell -NoProfile -ExecutionPolicy Bypass -Command ^
  "$src = $env:INI_SOURCE; $dst = $env:INI_RUNTIME; $seq = $env:SEQ_TARGET;" ^
  "$seq = $seq.TrimEnd('\') + '\';" ^
  "$txt = Get-Content -LiteralPath $src;" ^
  "$txt = $txt -replace '^ResourceDLL=.*$', 'ResourceDLL=MV3';" ^
  "$txt = $txt -replace '^SeqPath=.*$', ('SeqPath=' + $seq);" ^
  "Set-Content -LiteralPath $dst -Value $txt -Encoding ascii;"
if errorlevel 1 (
  echo ERROR: Failed to create runtime INI %INI_RUNTIME%.
  exit /b 1
)

call "%TEST_ROOT%build_test.bat"
if errorlevel 1 exit /b %ERRORLEVEL%

set "PATH=C:\ipos_kernel\LIB32;%TEST_DLL_ROOT%;%PATH%"
cd /d "%TEST_ROOT%"

echo Running DDSSEQ harness mode %TEST_MODE% ...
"%TEST_ROOT%ddsseq_harness.exe" %TEST_MODE% --ini "DMW.INI"
set "RUN_RC=%ERRORLEVEL%"

if not "%RUN_RC%"=="0" (
  echo.
  echo DDSSEQ harness failed with exit code %RUN_RC%.
  exit /b %RUN_RC%
)

echo.
echo DDSSEQ harness succeeded.
exit /b 0
