@echo off
echo Running Part A Tests...
echo ======================

echo Test 0: Simple Test
eel.exe A test_cases/t1a-0.txt

echo. & echo Test 1: Loop Exit Test
eel.exe A test_cases/t1a-1.txt

echo. & echo Test 2: Efficiency Test (Complete Graph)
eel.exe A test_cases/t1a-2.txt

echo. & echo Test 3: Max Food Impact Test
eel.exe A test_cases/t1a-3.txt

echo. & echo Tests 4-6: Time Boundary Tests
eel.exe A test_cases/t1a-4.txt
eel.exe A test_cases/t1a-5.txt
eel.exe A test_cases/t1a-6.txt

echo. & echo Test 7: Lake Predators Impact Test
eel.exe A test_cases/t1a-7.txt

echo. & echo Test 8: Broken Lake System
eel.exe A test_cases/t1a-8.txt

echo. & echo Test 9: Upstream Only Impact Test
eel.exe A test_cases/t1a-9.txt

echo. & echo Test 10: Negative Loop Impact Test
eel.exe A test_cases/t1a-10.txt

echo. & echo. & echo Running Part B Tests...
echo ======================

echo Test 0: Simple Test
eel.exe B test_cases/t1b-0.txt

echo. & echo Test 1: Loop Exit Test
eel.exe B test_cases/t1b-1.txt

echo. & echo Test 2: Efficiency Test (Complete Graph)
eel.exe B test_cases/t1b-2.txt

echo. & echo Test 3: Max Food Impact Test
eel.exe B test_cases/t1b-3.txt

echo. & echo Tests 4-6: Time Boundary Tests
eel.exe B test_cases/t1b-4.txt
eel.exe B test_cases/t1b-5.txt
eel.exe B test_cases/t1b-6.txt

echo. & echo Test 7: Lake Predators Impact Test
eel.exe B test_cases/t1b-7.txt

echo. & echo Test 8: Broken Lake System
eel.exe B test_cases/t1b-8.txt

echo. & echo Test 9: Upstream Only Impact Test
eel.exe B test_cases/t1b-9.txt

echo. & echo Test 10: Negative Loop Impact Test
eel.exe B test_cases/t1b-10.txt

pause
