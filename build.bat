@echo off
setlocal enabledelayedexpansion
set DIRECTORY=%cd%
set INCL=-I%DIRECTORY%\src\code -I%DIRECTORY%\src -I%DIRECTORY%\src\base -I%DIRECTORY%\libraries\glfw\include  -I%DIRECTORY%\libraries
set OPTIONS=-FC -GR- -EHa- -nologo -Zi -FS /analyze /W3 /WX
set LIBS=user32.lib gdi32.lib kernel32.lib  vulkan-1.lib
set BUILD_DIR=build
set SOURCE_DIR=src
set TARGET=%BUILD_DIR%\program.exe

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
echo Building %TARGET%...
cl %INCL% %OPTIONS% %SOURCE_DIR%\code\program.cpp /Fe%TARGET% %LIBS%