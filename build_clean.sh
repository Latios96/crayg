#!/usr/bin/env bash
rm -rf build/
mkdir build
cd build
cmake ..
make -j 4
#lcov --directory ./build/ --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
make test
#genhtml ./code_coverage.info --branch-coverage --output-directory ./code_coverage_report/

