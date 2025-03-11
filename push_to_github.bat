@echo off
echo === GitHub Push Script ===
cd /d "%~dp0"

echo Removing existing remote (if any)...
git remote remove origin 2>nul

echo Adding new remote...
git remote add origin https://github.com/drWilms/JellyfishProject.git

echo Verifying remote...
git remote -v

echo Adding all changes...
git add .

echo Committing changes...
git commit -m "Updated JellyfishProject files"

echo Setting branch to main...
git branch -M main

echo Pushing to GitHub...
git push -u origin main

echo.
echo ✅ Push completed! Check: https://github.com/drWilms/JellyfishProject
pause
