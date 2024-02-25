call SetPaths.bat
set BuildMode=Release
call CMakeBuild.bat
cd %BuildDir%
cmake --build . --clean-first --parallel 8 --config %BuildMode%