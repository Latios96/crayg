
#include "crayg/foundation/parallel/ThreadCount.h"

#include <catch2/catch.hpp>
#include <thread>

namespace crayg {

TEST_CASE("ThreadCount::getThreadCount") {

    SECTION("should return all available cores") {
        ThreadCount threadCount(0);

        REQUIRE(threadCount.getThreadCount() == std::thread::hardware_concurrency());
    }

    SECTION("should return specified cores") {
        ThreadCount threadCount(42);

        REQUIRE(threadCount.getThreadCount() == 42);
    }

    SECTION("should return available cores minus specified cores") {
        ThreadCount threadCount(-2);

        REQUIRE(threadCount.getThreadCount() == (std::thread::hardware_concurrency() - 2));
    }
}

}