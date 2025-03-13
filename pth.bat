@echo off
echo === pth.bat ==  GitHub Push Script ===
cd /d "%~dp0"

echo Checking if repository is initialized...
git rev-parse --is-inside-work-tree >nul 2>nul
if errorlevel 1 (
    echo ERROR: This is not a Git repository!
    pause
    exit /b
)

echo Adding all changes...
git add .

echo Committing changes...
git commit -m "Half werkende audio plus LEDs"

echo Checking remote repository...
git remote -v | findstr /C:"origin" >nul
if errorlevel 1 (
    echo No remote 'origin' found. Adding it now...
    git remote add origin https://github.com/drWilms/JellyfishProject.git
)

echo Setting default branch...
git branch --show-current > current_branch.txt
set /p BRANCH=<current_branch.txt
del current_branch.txt

if "%BRANCH%"=="" (
    echo No branch detected. Creating and setting 'main' as default...
    git branch -M main
    set BRANCH=main
)

echo Pushing to GitHub on branch %BRANCH%...
git push -u origin %BRANCH%

echo.
echo ✅ Push completed! Check: https://github.com/drWilms/JellyfishProject
pause
