COPY ..\..\%ACTVERS%.SRC\DBBTRV\dbbtrv.l32
COPY ..\..\%ACTVERS%.SRC\DBBTRV\dbbtrv32.DEF

rc -r -v -dWIN32 -fodbbtrv.res /I..\..\%ACTVERS%.SRC\DBBTRV /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DBBTRV\dbbtrv.rc

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
