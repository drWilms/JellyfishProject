@echo off
setlocal enabledelayedexpansion

for %%F in (*.bak) do (
    set "original=%%F"
    set "newname=%%~nF"
    
    if exist "!newname!" del "!newname!"
    ren "!original!" "!newname!"
)

echo All .bak files have been renamed.
pause
