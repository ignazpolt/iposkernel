COPY ..\..\..\SOURCE\DBBTRV\dbbtrv.l32
COPY ..\..\..\SOURCE\DBBTRV\dbbtrv32.DEF

rc -r -v -dWIN32 -fodbbtrv.res /I..\..\..\SOURCE\DBBTRV /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\DBBTRV\dbbtrv.rc

link /DLL /DEBUG /LIBPATH:..\..\COBJ32 @dbbtrv.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy dbbtrv.dll ..\*.*
copy dbbtrv.lib ..\*.*
copy dbbtrv.exp ..\*.*
copy dbbtrv.dll ..\restool\*.*
