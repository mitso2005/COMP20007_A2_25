@echo off
setlocal EnableDelayedExpansion

REM Create temp directory for actual outputs
if not exist "actual_output" mkdir actual_output

echo Comparing Part A outputs...
echo ========================

REM Run tests and capture outputs
for %%i in (0,1,2,3,4,5,6,7,8,9,10) do (
    eel.exe A test_cases/t1a-%%i.txt > actual_output\t1a-%%i.out
    fc /W actual_output\t1a-%%i.out expected_output\t1a-%%i.out > nul
    if !errorlevel! == 0 (
        echo Test A%%i: PASSED
    ) else (
        echo Test A%%i: FAILED
        echo Expected:
        type expected_output\t1a-%%i.out
        echo Got:
        type actual_output\t1a-%%i.out
        echo.
    )
)

echo.
echo Comparing Part B outputs...
echo ========================

REM Run tests and capture outputs
for %%i in (0,1,2,3,4,5,6,7,8,9,10) do (
    eel.exe B test_cases/t1b-%%i.txt > actual_output\t1b-%%i.out
    fc /W actual_output\t1b-%%i.out expected_output\t1b-%%i.out > nul
    if !errorlevel! == 0 (
        echo Test B%%i: PASSED
    ) else (
        echo Test B%%i: FAILED
        echo Expected:
        type expected_output\t1b-%%i.out
        echo Got:
        type actual_output\t1b-%%i.out
        echo.
    )
)

pause
