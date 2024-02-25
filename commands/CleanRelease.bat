call SetPaths.bat
set BuildMode=Release
call CMakeBuild.bat
cd %BuildDir%
cmake --build . --target clean --config %BuildMode%