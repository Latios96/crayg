#include "utils/ProgressReporter.h"
#include <catch2/catch.hpp>
#include <fakeit.hpp>

namespace crayg {

void _report(int progress, float elapsed, float timeRemaining) {
}

int callCount = 0;

void _storeCallCount(int progress, float elapsed, float timeRemaining) {
    callCount++;
}

bool finishedCalled = false;

void _storeFinishCalled(std::chrono::seconds seconds) {
    finishedCalled = true;
}

TEST_CASE("ProgressReporter") {
    ProgressReporter reporter(100, &_report, &_storeFinishCalled);

    SECTION("iterationsDoneShouldBeZero") {
        REQUIRE(reporter.iterationsDone == 0);
    }

    SECTION("iterationsDoneShouldBeIncreasedByOne") {
        reporter.iterationDone();
        REQUIRE(reporter.iterationsDone == 1);
    }

    SECTION("progressCallbackShouldBeCalledEvery1") {
        ProgressReporter reporter(200, &_storeCallCount, &_storeFinishCalled);

        REQUIRE(callCount == 0);

        reporter.iterationDone();
        REQUIRE(callCount == 0);

        reporter.iterationDone();
        REQUIRE(callCount == 1);
    }

    SECTION("finished callback should be called") {
        ProgressReporter reporter(100, &_storeCallCount, &_storeFinishCalled);

        reporter.finish();

        REQUIRE(finishedCalled);
    }
}

}
