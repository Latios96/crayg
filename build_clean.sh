#!/usr/bin/env bash
rm -rf build/
mkdir build
cd build
conan install .. --build missing
cmake ..
make -j 4
./bin/tests

./bin/crayg-standalone -s ../example_scenes/single_sphere.json -o single_sphere.bmp
./bin/crayg-standalone -s ../example_scenes/three_spheres.json -o three_spheres.bmp
./bin/crayg-standalone -s ../example_scenes/poly_cube.json -o poly_cube.bmp

