COPY ..\..\%ACTVERS%.SRC\FRMOBJ\frmobj.L32

rc -r -v -dWIN32 -fofrmobj.res /I..\..\%ACTVERS%.SRC\FRMOBJ /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\FRMOBJ\frmobj.rc

link /DLL /DEBUG /LIBPATH:..\..\COBJ32 @frmobj.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue

copy frmobj.dll ..\*.*
copy frmobj.lib ..\*.*
copy frmobj.exp ..\*.*
copy frmobj.dll ..\restool\*.*
