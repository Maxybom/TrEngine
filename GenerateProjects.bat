@echo off
echo Pulizia dei file e delle cartelle...

REM Cancella file specifici
del /Q /F "Sandbox\Sandbox.vcxproj"
del /Q /F "Sandbox\Sandbox.vcxproj.user"
del /Q /F "TrEngine\TrEngine.vcxproj"
del /Q /F "TrEngine\TrEngine.vcxproj.user"
del /Q /F "TrEngine\TrEngine.vcxproj.filters"

REM Cancella una directory e tutto il suo contenuto
rmdir /S /Q "bin"
rmdir /S /Q "bin-int"

echo Pulizia completata.
echo Esecuzione del comando premake...

REM Esegui il comando premake
call vendor\bin\premake\premake5.exe vs2022

PAUSE
