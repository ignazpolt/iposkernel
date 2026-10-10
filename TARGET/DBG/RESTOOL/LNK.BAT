copy ..\..\..\SOURCE\RESTOOL\restool.l32

rc -r -v -dWIN32 -forestool.res /I..\..\..\SOURCE\RESTOOL /I..\..\..\SOURCE\Include /I..\..\..\SOURCE ..\..\..\SOURCE\RESTOOL\restool.rc

link /DEBUG @restool.l32
if errorlevel 1 goto error
goto continue
:error
pause
:continue
if exist restool.exe copy /Y restool.exe ..\restool.exe
