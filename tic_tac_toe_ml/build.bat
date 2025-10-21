@echo off
echo Building Tic-Tac-Toe ML with C++...
echo =====================================

:: Check if g++ is available
g++ --version >nul 2>&1
if errorlevel 1 (
    echo Error: g++ compiler not found!
    echo Please install MinGW-w64 or Visual Studio Build Tools
    echo Download from: https://www.mingw-w64.org/downloads/
    pause
    exit /b 1
)

:: Compile the program
echo Compiling...
g++ -std=c++17 -Wall -Wextra -O2 main.cpp TicTacToe.cpp QLearningAgent.cpp -o tic_tac_toe_ml.exe

if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo ✅ Build successful! 
echo 🎮 Run 'tic_tac_toe_ml.exe' to start playing!
echo.
pause
