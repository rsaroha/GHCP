@echo off
setlocal

:: Adjust these if needed
set BUILD_DIR=build
set VCPKG_TOOLCHAIN=C:\vcpkg\scripts\buildsystems\vcpkg.cmake

cmake -B %BUILD_DIR% -G "Visual Studio 18 2026" -A x64 -DCMAKE_TOOLCHAIN_FILE="%VCPKG_TOOLCHAIN%"
cmake --build %BUILD_DIR% --config Debug

echo.
echo Run with:  %BUILD_DIR%\Debug\triangle.exe
endlocal
