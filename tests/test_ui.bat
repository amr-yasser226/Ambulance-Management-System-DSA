@echo off
REM Change to the script directory
cd /d "%~dp0"

REM Change to src directory
cd ..\src

REM Clean previous build
nmake -f ui-Makefile clean

REM Build
nmake -f ui-Makefile

REM Check if build was successful
if %ERRORLEVEL% EQU 0 (
    cd bin
    test_ui.exe
) else (
    echo Build failed
)