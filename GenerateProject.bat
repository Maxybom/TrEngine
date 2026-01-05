@echo off
echo Clean start

REM Delete specific files
del /Q /F "Sandbox\Sandbox.vcxproj"
del /Q /F "Sandbox\Sandbox.vcxproj.user"
del /Q /F "TrEngine\TrEngine.vcxproj"
del /Q /F "TrEngine\TrEngine.vcxproj.user"
del /Q /F "TrEngine\TrEngine.vcxproj.filters"

rmdir /S /Q "bin"
rmdir /S /Q "bin-int"

echo Clean complete
echo premake execution

call vendor\bin\premake\Windows\premake5.exe vs2022

PAUSE
