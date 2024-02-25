@echo off

set BaseDirectory=%~dp0
set WorkspaceDir=%BaseDirectory%..

set ProjectsDir=%WorkspaceDir%\\projects
set CommandsDir=%WorkspaceDir%\\commands

set BuildDir=%WorkspaceDir%\\outputs\\build
set BinDir=%WorkspaceDir%\\outputs\\bin

set BinDebugDir=%BinDir%\\Debug
set BinReleaseDir=%BinDir%\\Release

set Path=C:\\msys64\\mingw64\\bin;
set CC=C:\\msys64\\mingw64\\bin\\x86_64-w64-mingw32-gcc.exe;
set CXX=C:\\msys64\\mingw64\\bin\\x86_64-w64-mingw32-c++.exe;
