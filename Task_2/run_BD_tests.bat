@echo off
echo Compiling birds.c and dependencies...
gcc -Wall -o birds birds.c cbf.c dbf.c hash.c bit.c utils.c bf_stub.c -lm -g

if %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo Running Part B (Counting Bloom Filter) basic test...
echo =============================================
birds C datafiles/t2b_data_1.txt test_cases/t2_1.txt delete_cases/t2_delete_1.txt

echo.
echo Running Part D (Dynamic Bloom Filter) basic test...
echo =============================================
birds D datafiles/t2d_data_5.txt test_cases/t2_1.txt delete_cases/t2_delete_1.txt

echo.
echo Tests complete.

REM Create output files
echo Creating test outputs...
birds C datafiles/t2b_data_1.txt test_cases/t2_1.txt delete_cases/t2_delete_1.txt > output/test_b.txt
birds D datafiles/t2d_data_5.txt test_cases/t2_1.txt delete_cases/t2_delete_1.txt > output/test_d.txt

echo.
echo Output files created in output/test_b.txt and output/test_d.txt
pause
