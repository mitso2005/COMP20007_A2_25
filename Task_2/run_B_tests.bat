@echo off
echo Compiling birds.c and CBF dependencies...
gcc -Wall -o birds birds.c cbf.c bf_stub.c dbf_stub.c hash.c bit.c utils.c -lm -g

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo Running Part B (Counting Bloom Filter) tests...
echo ============================================

REM Test case 1: Basic functionality
echo Test 1: Basic functionality
birds C datafiles/t2b_data_1.txt test_cases/t2_1.txt delete_cases/t2_delete_1.txt

echo.
echo Test 2: Multiple birds
birds C datafiles/t2b_data_10.txt test_cases/t2_1.txt delete_cases/t2_delete_10.txt

echo.
echo Test 3: Near capacity
birds C datafiles/t2b_data_11.txt test_cases/t2_1.txt delete_cases/t2_delete_10.txt

echo.
echo Test 4: Overflow test
birds C datafiles/t2b_data_22.txt test_cases/t2_1.txt delete_cases/t2_delete_10.txt

echo.
echo All Part B tests complete.
pause
