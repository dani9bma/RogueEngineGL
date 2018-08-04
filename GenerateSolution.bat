@Echo off
setlocal
cd Sharpmake
call Sharpmake.Application.exe /sources(@"main.sharpmake.cs")
pause