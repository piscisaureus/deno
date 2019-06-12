@echo off
pushd %~dp0
rmdir /s/q %~dp0build
mkdir build
cd build
cmake.exe .. -G "Visual Studio 15 2017" -A x64 -T host=x64 %*
popd