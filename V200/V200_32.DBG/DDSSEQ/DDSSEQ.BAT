del err

call makec ..\..\%ACTVERS%.SRC\ddsseq\*.cpp *.obj COMPDLL1
if exist ddsseq.dll if %ERRORLEVEL% equ 0 del ddsseq.dll

call makec ..\..\%ACTVERS%.SRC\ddsseq\*.rc *.res RCCOMP
if exist ddsseq.dll if %ERRORLEVEL% equ 0 del ddsseq.dll

if not exist ddsseq.dll call lnk.bat
