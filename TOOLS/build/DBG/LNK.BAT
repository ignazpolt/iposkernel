copy ..\..\SOURCE\dds.l32

rc -r -v -dWIN32 -fodds.res /I..\..\SOURCE\include /I..\..\SOURCE ..\..\SOURCE\dds.rc

link /DEBUG /LIBPATH:..\..\COBJ32 @dds.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue
