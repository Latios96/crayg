#!/usr/bin/env bash
lcov --directory ./build/ --capture --output-file ./code_coverage.info -rc lcov_branch_coverage=1
lcov -e ./code_coverage.info $PWD/crayg/\* > ./code_coverage_clean.info
genhtml ./code_coverage_clean.info --branch-coverage --output-directory ./code_coverage_report/