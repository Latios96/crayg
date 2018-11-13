#!/usr/bin/env bash
rm -rf build/
mkdir build
cd build
cmake ..
make -j 4
make test

#lcov --directory ./build/ --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
#lcov -e ./code_coverage.info $PWD/crayg/\* > ./code_coverage_clean.info
#genhtml ./code_coverage_clean.info --branch-coverage --output-directory ./code_coverage_report/

./standalone/crayg-standalone -s ../example_scenes/single_sphere.json -o single_sphere.bmp
./standalone/crayg-standalone -s ../example_scenes/three_spheres.json -o three_spheres.bmp

