@echo off
setlocal

set "SOURCE_DIR=%~dp0."
set "BUILD_DIR=%~dp0build"

if exist "%BUILD_DIR%" (
    echo Removing existing build directory: "%BUILD_DIR%"
    rmdir /s /q "%BUILD_DIR%" 2>nul
    if exist "%BUILD_DIR%" (
        echo Could not remove the build directory. Close the GLFromWebGL solution in Visual Studio
        echo and check that no other process is using files under "%BUILD_DIR%".
        exit /b 1
    )
)

echo Configuring the x64 Debug solution with CMake...
cmake -S "%SOURCE_DIR%" -B "%BUILD_DIR%" -A x64
if errorlevel 1 exit /b 1

echo Building the Debug solution...
cmake --build "%BUILD_DIR%" --config Debug
if errorlevel 1 exit /b 1

echo Debug build completed successfully.
exit /b 0
