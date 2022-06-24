mkdir build
cd build
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
ctest -C Release -V
cmake --build . --config Release --target createDistribution