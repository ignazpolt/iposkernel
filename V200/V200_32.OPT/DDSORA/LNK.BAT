COPY ..\..\%ACTVERS%.SRC\DDSORA\ddsora.L32
COPY ..\..\%ACTVERS%.SRC\DDSORA\ddsora32.def

rc -r -v -dWIN32 -foddsora.res /I..\..\%ACTVERS%.SRC\DDSORA /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\DDSORA\ddsora.rc

link /DLL /DEBUG /LIBPATH:..\..\COBJ32 @ddsora.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy ddsora.dll ..
copy ddsora.lib ..
copy ddsora.exp ..
copy ddsora.dll ..\restool\*.*
