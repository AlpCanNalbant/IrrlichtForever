call SetPaths.bat
set BuildMode=Debug
call CMakeBuild.bat
cd %BuildDir%
cmake --build . --target clean --config %BuildMode%