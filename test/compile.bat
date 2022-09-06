:: Alvajoy "Alvajoy123" Asante
:: Last updated: 9/5/2022
:: This compiles the API into a folder and uses it to detect bugs of any sort.

@echo off
title Testing: Notify
:start
echo Copying the lastest version of Notify into testing folder...

:: Makes a folder named hydra and copies all the source code into the hyra folder
mkdir .\src\notify
xcopy /y/s/i "..\notify" .\src\notify

:: Clears the screen of any infomations displayed whiles create folder.
cls

:: Compiles all the program in order to test for errors and bugs
make
PAUSE 

:: Once the bug has been fixed then cleans via dev then the screen is cleared. 
cls
goto start