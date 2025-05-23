@echo off
echo Compiling eel.c...
gcc -Wall -g -o eel.exe eel.c utils.c

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo Compilation successful!
echo.
echo Running tests...
call compare_outputs.bat
