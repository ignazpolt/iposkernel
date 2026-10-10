del err

call makec ..\..\..\SOURCE\ddsseq\*.cpp *.obj COMPDLL1
if exist ddsseq.dll if %ERRORLEVEL% equ 0 del ddsseq.dll

call makec ..\..\..\SOURCE\ddsseq\*.rc *.res RCCOMP
if exist ddsseq.dll if %ERRORLEVEL% equ 0 del ddsseq.dll

if not exist ddsseq.dll call lnk.bat
