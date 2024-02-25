call SetPaths.bat
set BuildMode=Debug
call CMakeBuild.bat
cd %BuildDir%
cmake --build . --clean-first --config %BuildMode%