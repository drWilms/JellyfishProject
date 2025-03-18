@echo off
echo === GitHub Push Script ===
cd /d "%~dp0"

:: Check if Git is installed
git --version >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ❌ Git is not installed or not in PATH. Exiting.
    pause
    exit /b
)

:: Check if this is a Git repository
git rev-parse --is-inside-work-tree >nul 2>&1
if %ERRORLEVEL% neq 0 (
    echo ❌ This is not a Git repository. Run 'git init' first.
    pause
    exit /b
)

echo Adding all changes...
git add .

echo Committing changes...
git commit -m "JF_RTOS with LED, RGB-fade, WiFi, date/time"

:: Ensure branch is correct
for /f %%B in ('git branch --show-current') do set current_branch=%%B
if not "%current_branch%"=="JF_RTOS" (
    echo Switching to JF_RTOS branch...
    git checkout -B JF_RTOS
)

echo Pushing to GitHub...
git push -u origin JF_RTOS

echo.
echo ✅ Push completed! Check: https://github.com/drWilms/JellyfishProject/tree/JF_RTOS
pause
