@echo off
setlocal enabledelayedexpansion

if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" (
    set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
) else (
    if exist "%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe" (
        set "VSWHERE=%ProgramFiles%\Microsoft Visual Studio\Installer\vswhere.exe"
    ) else (
        echo [ERROR] vswhere.exe not found. Is Visual Studio installed?
        exit /b 1
    )
)

for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    set "MSBUILD_PATH=%%i"
)

if not defined MSBUILD_PATH (
    echo [ERROR] MSBuild not found! Ensure the C++ workload is installed.
    exit /b 1
)

echo [INFO] Found MSBuild at: "!MSBUILD_PATH!"

"%MSBUILD_PATH%" %*