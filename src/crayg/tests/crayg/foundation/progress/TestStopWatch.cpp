#include "crayg/foundation/progress/StopWatch.h"
#include "crayg/foundation/progress/StopWatchHelperMacros.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("StopWatchHelperMacros Smoke Tests") {

    SECTION("seconds") {
        CRAYG_SCOPED_STOP_WATCH_S;
    }

    SECTION("milliseconds") {
        CRAYG_SCOPED_STOP_WATCH_MS;
    }

    SECTION("human") {
        CRAYG_SCOPED_STOP_WATCH_HUMAN;
    }
}

}