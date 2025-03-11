@echo off
setlocal enabledelayedexpansion

REM Define paths
set "PROJECT_ROOT=%CD%"
set "INPUT_FILE=GPT.txt"
set "CURRENT_FILE="

REM Check if GPT.txt exists
if not exist "%INPUT_FILE%" (
    echo ERROR: GPT.txt not found!
    pause
    exit /b
)

echo Updating files from %INPUT_FILE%...

REM Read GPT.txt line by line
for /f "tokens=*" %%A in (%INPUT_FILE%) do (
    set "line=%%A"

    REM Skip lines that start with "=========="
    echo !line! | findstr /B "===========" >nul
    if not errorlevel 1 (
        REM Skip this line and continue to the next one
        REM No action, just skip the line
    ) else (
        REM Detect file header line
        echo !line! | findstr /B "File: " >nul
        if not errorlevel 1 (
            REM Extract file path
            set "CURRENT_FILE=%PROJECT_ROOT%\!line:File: =!"
            REM Replace forward slashes with backslashes
            set "CURRENT_FILE=!CURRENT_FILE:/=\!"
            echo Processing: !CURRENT_FILE!

            REM Create a backup of the existing file if it exists
            if exist "!CURRENT_FILE!" copy /Y "!CURRENT_FILE!" "!CURRENT_FILE!.bak" >nul

            REM Clear the target file
            echo. > "!CURRENT_FILE!"
        ) else (
            REM Append lines to the last detected file
            if defined CURRENT_FILE (
                echo !line! >> "!CURRENT_FILE!"
            )
        )
    )
)

echo Update completed!
pause
