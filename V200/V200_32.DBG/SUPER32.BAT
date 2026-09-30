@echo off

if exist supererr del supererr

call :collect_err "ddsmem"
call :collect_err "dmwapi"
call :collect_err "dbhelp"
call :collect_err "compile"
call :collect_err "ctool"
call :collect_err "image"
call :collect_err "frmobj"
call :collect_err "hook"
call :collect_err "dbbtrv"
call :collect_err "dbclean"
call :collect_err "statbar"
call :collect_err "toolbar"
call :collect_err "ddsodbc"
call :collect_err "ddsora"
call :collect_err "ddsseq"
call :collect_err "dnetin"
call :collect_err "dnetnv"
call :collect_err "restool"
call :collect_root

goto :eof

:collect_err
cd /d "%~1"
echo -------------------- >> ..\supererr
echo **** %~1 **** >> ..\supererr
if exist err type err >> ..\supererr
cd /d ..
goto :eof

:collect_root
echo -------------------- >> supererr
echo **** dds **** >> supererr
if exist err type err >> supererr
goto :eof
