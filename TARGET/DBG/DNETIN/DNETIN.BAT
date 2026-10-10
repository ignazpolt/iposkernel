del err

call makec ..\..\..\SOURCE\dnetin\*.cpp *.obj COMPDLL
if exist dnetin.dll if %ERRORLEVEL% equ 0 del dnetin.dll

call makec ..\..\..\SOURCE\dnetin\*.rc *.res RCCOMP
if exist dnetin.dll if %ERRORLEVEL% equ 0 del dnetin.dll

if not exist dnetin.dll call lnk.bat
