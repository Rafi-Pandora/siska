@echo off

if not exist build (
    echo Folder build tidak ditemukan!
    echo Jalankan build.bat terlebih dahulu.
    pause
    exit /b 1
)

cd build


if not exist RailwayMLL.exe (
    echo Executable RailwayMLL.exe tidak ditemukan!
    echo Pastikan build berhasil.
    pause
    exit /b 1
)

echo.
echo Menjalankan RailwayMLL...
RailwayMLL.exe

echo.
echo   Program selesai
pause
