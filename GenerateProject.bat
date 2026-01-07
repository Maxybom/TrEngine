@echo off
echo === CLEAN START ===

del /Q *.sln

if exist "bin" rmdir /S /Q "bin"
if exist "bin-int" rmdir /S /Q "bin-int"

if exist ".vs" rmdir /S /Q ".vs"

echo Deleting project files...
del /S /Q *.vcxproj
del /S /Q *.vcxproj.user
del /S /Q *.vcxproj.filters

echo === CLEAN COMPLETE ===
echo === PREMAKE EXECUTION ===

call vendor\bin\premake\Windows\premake5.exe vs2022

PAUSE