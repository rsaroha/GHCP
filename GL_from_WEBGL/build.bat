@echo off
setlocal

set "SOURCE_DIR=%~dp0"
set "BUILD_DIR=%~dp0build"

if exist "%BUILD_DIR%\.vs\" (
    echo Close the GLFromWebGL solution in Visual Studio before running this clean build.
    echo Visual Studio may lock files inside the generated build directory.
    exit /b 1
)

if exist "%BUILD_DIR%" (
    echo Removing existing build directory: "%BUILD_DIR%"
    rmdir /s /q "%BUILD_DIR%"
    if exist "%BUILD_DIR%" (
        echo Failed to remove the existing build directory.
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
