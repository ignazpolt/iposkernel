del err

call makec ..\..\%ACTVERS%.SRC\frmobj\*.cpp *.obj COMPDLL1
if exist frmobj.dll if %ERRORLEVEL% equ 0 del frmobj.dll

call makec ..\..\%ACTVERS%.SRC\frmobj\*.rc *.res RCCOMP
if exist frmobj.dll if %ERRORLEVEL% equ 0 del frmobj.dll

if not exist frmobj.dll call lnk.bat
