mkdir build
cd build
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
C:\cmake\bin\cmake -G "Ninja" .. -DCMAKE_BUILD_TYPE=Release
C:\cmake\bin\cmake --build . --config Release
ctest -C Release -V
C:\cmake\bin\cmake --build . --config Release --target createDistribution