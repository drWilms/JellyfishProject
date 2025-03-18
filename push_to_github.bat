@echo off
echo === GitHub Push Script ===
cd /d "%~dp0"

echo Adding all changes...
git add .

echo Committing changes...
git commit -m restored "JF_RTOS with fragment audio playing in setup , SD, led, rgb-fade, wifi, date/time w/o DST"

echo Setting branch to JF_RTOS...
git branch -M JF_RTOS

echo Pushing to GitHub...
git push -u origin JF_RTOS

echo.
echo ✅ Push completed! Check: https://github.com/drWilms/JellyfishProject/tree/JF_RTOS
pause
