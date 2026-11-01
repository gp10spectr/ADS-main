@echo off
setlocal

:: Переходим в корень проекта (на один уровень выше папки scripts)
cd /d "%~dp0\.."

:: 1. Создаем папку build, если ее нет
if not exist build (
    mkdir build
)

:: 2. Переходим в папку build
cd build

:: 3. Запускаем генерацию и сборку проекта командой cmake
echo [INFO] Configuring CMake...
cmake ..
if %ERRORLEVEL% neq 0 (
    echo [ERROR] CMake configuration failed!
    pause
    exit /b %ERRORLEVEL%
)

echo [INFO] Building project...
cmake --build . --config Debug

:: 4. Если сборка прошла успешно, открываем собранное решение (.slnx или .sln)
if %ERRORLEVEL% equ 0 (
    echo [SUCCESS] Build succeeded! Opening solution...
    if exist DataStructure.slnx (
        start DataStructure.slnx
    ) else if exist DataStructure.sln (
        start DataStructure.sln
    ) else (
        echo [WARNING] Solution file not found!
    )
) else (
    echo [ERROR] Build failed!
)

pause