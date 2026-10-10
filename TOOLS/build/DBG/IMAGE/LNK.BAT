COPY ..\..\..\SOURCE\IMAGE\tiff.L32

rc -r -v -dWIN32 -fotiffimg.res /I..\..\..\SOURCE\IMAGE /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\IMAGE\tiffimg.rc

link /DLL /DEBUG /LIBPATH:..\..\..\COBJ32 @tiff.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy tiffimg.dll ..\*.*
copy tiffimg.lib ..\*.*
copy tiffimg.exp ..\*.*
copy tiffimg.dll ..\restool\*.*
