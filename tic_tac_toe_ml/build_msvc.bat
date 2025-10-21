@echo off
echo Building Tic-Tac-Toe ML with MSVC...
echo ====================================

:: Try to find Visual Studio
where cl.exe >nul 2>&1
if errorlevel 1 (
    echo Searching for Visual Studio...
    
    :: Try to call vcvarsall.bat to set up environment
    if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" (
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    ) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" (
        call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    ) else (
        echo Error: Visual Studio compiler not found!
        echo Please install Visual Studio or use build.bat with MinGW
        pause
        exit /b 1
    )
)

:: Compile with MSVC
echo Compiling with MSVC...
cl /EHsc /std:c++17 /O2 main.cpp TicTacToe.cpp QLearningAgent.cpp /Fe:tic_tac_toe_ml.exe

if errorlevel 1 (
    echo Compilation failed!
    pause
    exit /b 1
)

echo.
echo ✅ Build successful with MSVC!
echo 🎮 Run 'tic_tac_toe_ml.exe' to start playing!
echo.
pause
