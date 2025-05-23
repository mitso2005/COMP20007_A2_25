@echo off
gcc -Wall -g -o eel.exe eel.c utils.c
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful
) else (
    echo Compilation failed
)
