copy ..\..\%ACTVERS%.SRC\RESTOOL\restool.l32

rc -r -v -dWIN32 -forestool.res /I..\..\%ACTVERS%.SRC\RESTOOL /I..\..\%ACTVERS%.SRC\Include /I..\..\%ACTVERS%.SRC ..\..\%ACTVERS%.SRC\RESTOOL\restool.rc

link /DEBUG @restool.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue
if exist restool.exe copy /Y restool.exe ..\restool.exe
