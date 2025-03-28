@echo off
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

mkdir build
cd build 

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON .. 

ninja 

ctest --output-on-failure 

cd ..
