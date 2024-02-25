call SetPaths.bat
call CreateDirectories.bat
cd %BuildDir%

if not "%BuildMode%"=="" (
    cmake -G"MinGW Makefiles" -H%ProjectsDir% -B%BuildDir% -DCMAKE_BUILD_TYPE=%BuildMode%
    goto :Exit
) else (
    echo . [X] Build mode is empty.
    goto :FatalError
)

:FatalError
echo . [X] An fatal error occurred during the process, operation of the batch file terminated unexpectedly.
exit /B 1

:Exit
exit /B 0