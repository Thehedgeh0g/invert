@echo off
setlocal enabledelayedexpansion

set "inputFolder=TestComms"
set "outputFolder=."
set "outputFile=%outputFolder%\output.txt"

if not exist "%outputFolder%" mkdir "%outputFolder%"

type nul > "!outputFile!"

chcp 65001 > nul

for %%F in ("%inputFolder%\*.in") do (
    for /f "tokens=*" %%A in (%%F) do (
        echo Running: %%A
        echo Running: %%A >> "!outputFile!"
        echo ------------------Result----------------- >> "!outputFile!"
        %%A >> "!outputFile!" 2>&1
        echo ========================================= >> "!outputFile!"
    )
)

chcp > nul

echo Done.
pause
