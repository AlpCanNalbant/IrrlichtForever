call SetPaths.bat
set BuildMode=Release
call CMakeBuild.bat
cd %BuildDir%
cmake --build . --target install --parallel 8 --config %BuildMode%
