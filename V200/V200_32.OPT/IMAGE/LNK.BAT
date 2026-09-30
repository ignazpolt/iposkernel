COPY ..\..\%ACTVERS%.SRC\IMAGE\tiff.L32

rc -r -v -dWIN32 -fotiffimg.res /I..\..\%ACTVERS%.SRC\IMAGE /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\IMAGE\tiffimg.rc

link /DLL /DEBUG /LIBPATH:..\..\COBJ32 @tiff.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy tiffimg.dll ..\*.*
copy tiffimg.lib ..\*.*
copy tiffimg.exp ..\*.*
copy tiffimg.dll ..\restool\*.*
