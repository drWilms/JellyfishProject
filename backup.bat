@echo off
setlocal enabledelayedexpansion

:: Get date and time for filename
for /f "tokens=2 delims==" %%I in ('"wmic os get localdatetime /value"') do set datetime=%%I
set datetime=%datetime:~0,4%-%datetime:~4,2%-%datetime:~6,2%_%datetime:~8,2%-%datetime:~10,2%
set backupfile="Backup_%datetime%.txt"

:: Start writing to the backup file
echo Merged JellyfishProject Code (Generated on %datetime%) > %backupfile%
echo ===================================================== >> %backupfile%

:: Backup main.cpp
if exist src\main.cpp (
    echo ======================================= >> %backupfile%
    echo File: src\main.cpp >> %backupfile%
    echo ======================================= >> %backupfile%
    type src\main.cpp >> %backupfile%
    echo. >> %backupfile%
) else (
    echo WARNING: src\main.cpp not found! Skipping... >> %backupfile%
)

:: Loop through libraries listed in libs_list.txt
for /f "delims=" %%L in (libs_list.txt) do (
    if exist lib\%%L (
        echo ======================================= >> %backupfile%
        echo Library: lib\%%L >> %backupfile%
        echo ======================================= >> %backupfile%

        :: Loop through files in each library directory
        for %%F in (lib\%%L\*.h lib\%%L\*.cpp lib\%%L\*.txt) do (
            echo ======================================= >> %backupfile%
            echo File: %%F >> %backupfile%
            echo ======================================= >> %backupfile%
            type "%%F" >> %backupfile%
            echo. >> %backupfile%
        )
    ) else (
        echo WARNING: lib\%%L not found! Skipping... >> %backupfile%
    )
)


:: Completion message
echo Backup completed! File saved as %backupfile%
pause
