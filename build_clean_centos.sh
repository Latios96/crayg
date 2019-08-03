#!/usr/bin/env bash
export CC=/opt/rh/devtoolset-7/root/usr/bin/gcc
export CXX=/opt/rh/devtoolset-7/root/usr/bin/g++

rm -rf build/
mkdir build
cd build
conan install .. --s compiler.version=7.3 --build missing
cmake ..
make -j 4
./bin/tests
./bin/crayg-standalone-tests

./bin/crayg-standalone -s ../example_scenes/single_sphere.json -o single_sphere.bmp
./bin/crayg-standalone -s ../example_scenes/three_spheres.json -o three_spheres.bmp
./bin/crayg-standalone -s ../example_scenes/poly_cube.json -o poly_cube.bmp