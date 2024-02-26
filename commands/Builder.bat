@echo off

set "BaseDir=%~dp0"
if "%BaseDir:~-1%"=="\" set "BaseDir=%BaseDir:~0,-1%"

set WorkspaceDir=%BaseDir%\\..
set OutputsDir=%WorkspaceDir%\\outputs\\build\\Windows

set "ProjectName=%~1"
if "%ProjectName%"=="" (
    echo [X] First parameter is empty. Must be specify base-name of the current project's executable file.
    goto :FatalError
)

set "Operation=%~2"
if /I not "%Operation%"=="Run" if /I not "%Operation%"=="Build" if /I not "%Operation%"=="Clean" if /I not "%Operation%"=="Rebuild" (
    echo [X] Invalid second parameter. Must be specify an operation.
    echo [^] Parameter: %Operation%
    echo [^] Operations: Run, Build, Clean Rebuild
    goto :FatalError
)

set "Compiler=%~3"
if /I not "%Compiler%"=="GCC" if /I not "%Compiler%"=="Clang" (
    echo [X] Invalid third parameter. Must be specify a compiler.
    echo [^] Parameter: %Compiler%
    echo [^] Compilers: GCC, Clang
    goto :FatalError
)

set "BuildMode=%~4"
if /I not "%BuildMode%"=="Debug" if /I not "%BuildMode%"=="Release" (
    echo [X] Invalid fourth parameter. Must be specify a build mode.
    echo [^] Parameter: %BuildMode%
    echo [^] Modes: Debug, Release
    goto :FatalError
)

if /I "%Compiler%"=="GCC" (
    set Compiler=gcc
    set "Path=%Path%;C:\\msys64\\mingw64\\bin"
    set CC=C:\\msys64\\mingw64\\bin\\x86_64-w64-mingw32-gcc.exe
    set CXX=C:\\msys64\\mingw64\\bin\\x86_64-w64-mingw32-c++.exe
)
if /I "%Compiler%"=="Clang" (
    set Compiler=clang
    set "Path=%Path%;C:\\msys64\\clang64\\bin"
    set CC=C:\\msys64\\clang64\\bin\\x86_64-w64-mingw32-clang.exe
    set CXX=C:\\msys64\\clang64\\bin\\x86_64-w64-mingw32-c++.exe
)

if /I "%BuildMode%"=="Debug" (
    set BuildMode=Debug
    set Jobs=""
)
if /I "%BuildMode%"=="Release" (
    set BuildMode=Release
    set "Jobs=--parallel 8"
)

set BuildDir=%OutputsDir%\\mingw\\%Compiler%\\%BuildMode%
set BinDir=%OutputsDir%\\mingw\\%Compiler%\\bin\\%BuildMode%

if /I "%Operation%"=="Run" (
    goto :Run
) else (
    goto :Build
)

:Build

cmake -G "MinGW Makefiles" -S %WorkspaceDir% -B %BuildDir% -D CMAKE_BUILD_TYPE=%BuildMode%

if /I "%Operation%"=="Build" (
    cmake --build %BuildDir% --target install %Jobs% --config %BuildMode%
)
if /I "%Operation%"=="Clean" (
    cmake --build %BuildDir% --target clean --config %BuildMode%
)
if /I "%Operation%"=="Rebuild" (
    cmake --build %BuildDir% --clean-first %Jobs% --config %BuildMode%
)

goto :ExitTerminal

:Run

set "Exec=%~5"
if /I not "%Exec%"=="Project" if /I not "%Exec%"=="CMakeGUI" (
    echo [X] Invalid fifth parameter. Must be specify an executable program.
    echo [^] Parameter: %Exec%
    echo [^] Executables: Project, CMakeGUI
    goto :FatalError
)

if /I "%Exec%"=="Project" (
    %BinDir%\\%ProjectName%.exe
)
if /I "%Exec%"=="CMakeGUI" (
    cd %BuildDir%
    cmake-gui %WorkspaceDir%
)

goto :ExitTerminal

:ExitTerminal
exit /B 0

:FatalError
echo [FATAL] An fatal error occurred during the process, operation of the batch file terminated unexpectedly.
exit /B 1
