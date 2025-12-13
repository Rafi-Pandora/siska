
if not exist build (
    echo Membuat folder build...
    mkdir build
)

cd build

echo.
echo Menjalankan CMake...
cmake ..

if errorlevel 1 (
    echo.
    echo [ERROR] CMake gagal.
    pause
    exit /b 1
)

echo.
echo Melakukan build...
cmake --build .

if errorlevel 1 (
    echo.
    echo [ERROR] Build gagal.
    pause
    exit /b 1
)

echo.
echo   BUILD BERHASIL
pause
