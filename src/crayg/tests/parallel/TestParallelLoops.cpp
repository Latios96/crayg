#include "basics/Resolution.h"
#include "parallel/ParallelLoops.h"
#include <catch2/catch.hpp>
#include <set>
#include <tbb/concurrent_set.h>

namespace crayg {

bool compareSet(tbb::concurrent_set<Index2d> &s1, std::set<Index2d> &s2) {
    std::set<Index2d> s1_;

    for (auto &value : s1) {
        s1_.insert(value);
    }

    return s1_ == s2;
}

TEST_CASE("ParallelLoops::parallelFor2d") {

    SECTION("should iterate correctly based on dimensions") {
        tbb::concurrent_set<Index2d> visitedIndices;

        parallelFor2d(5, 3, [&visitedIndices](const Index2d &index) { visitedIndices.insert(index); });

        std::set<Index2d> expectedIndices({Index2d(0, 0), Index2d(1, 0), Index2d(2, 0), Index2d(3, 0), Index2d(4, 0),
                                           Index2d(0, 1), Index2d(1, 1), Index2d(2, 1), Index2d(3, 1), Index2d(4, 1),
                                           Index2d(0, 2), Index2d(1, 2), Index2d(2, 2), Index2d(3, 2), Index2d(4, 2)});

        REQUIRE(compareSet(visitedIndices, expectedIndices));
    }

    SECTION("should iterate correctly based on resolution") {
        tbb::concurrent_set<Index2d> visitedIndices;

        parallelFor2d(Resolution(5, 3), [&visitedIndices](const Index2d &index) { visitedIndices.insert(index); });

        std::set<Index2d> expectedIndices({Index2d(0, 0), Index2d(1, 0), Index2d(2, 0), Index2d(3, 0), Index2d(4, 0),
                                           Index2d(0, 1), Index2d(1, 1), Index2d(2, 1), Index2d(3, 1), Index2d(4, 1),
                                           Index2d(0, 2), Index2d(1, 2), Index2d(2, 2), Index2d(3, 2), Index2d(4, 2)});
        REQUIRE(compareSet(visitedIndices, expectedIndices));
    }
}

}