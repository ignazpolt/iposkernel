if exist supererr del supererr

echo -------------------- >> supererr
echo **** compile **** >> supererr
cd compile
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\ddsmem **** >> ..\supererr
cd ..\ddsmem
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\ctool **** >> ..\supererr
cd ..\ctool
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\dmwapi **** >> ..\supererr
cd ..\dmwapi
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\frmobj **** >> ..\supererr
cd ..\frmobj
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\hook **** >> ..\supererr
cd ..\hook
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\image **** >> ..\supererr
cd ..\image
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\dbbtrv **** >> ..\supererr
cd ..\dbbtrv
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\dbhelp **** >> ..\supererr
cd ..\dbhelp
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\dbclean **** >> ..\supererr
cd ..\dbclean
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\statbar **** >> ..\supererr
cd ..\statbar
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\restool **** >> ..\supererr
cd ..\restool
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\toolbar **** >> ..\supererr
cd ..\toolbar
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\ddsodbc **** >> ..\supererr
cd ..\ddsodbc
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\ddsora **** >> ..\supererr
cd ..\ddsora
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\ddsseq **** >> ..\supererr
cd ..\ddsseq
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\dnetin **** >> ..\supererr
cd ..\dnetin
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** ..\dnetnv **** >> ..\supererr
cd ..\dnetnv
if exist err type err >> ..\supererr
echo -------------------- >> ..\supererr
echo **** .. **** >> ..\supererr
cd ..
if exist err type err >> supererr
