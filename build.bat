@echo off
call GenerateSolution.bat
msbuild Engine\Skel.vcxproj
cd binaries
start skel.exe