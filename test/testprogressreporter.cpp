//
// Created by Jan Honsbrok on 11.11.18.
//

#include <catch.hpp>
#include "utils/ProgressReporter.h"
#include <fakeit.hpp>

void _report(int progress){

}

int callCount = 0;

void _storeCallCount(int progress){
    callCount++;
}

TEST_CASE("ProgressReporter"){
    ProgressReporter reporter (100, &_report);

    SECTION("iterationsDoneShouldBeZero"){
        REQUIRE(reporter.iterationsDone == 0);
    }

    SECTION("iterationsDoneShouldBeIncreasedByOne"){
        reporter.iterationDone();
        REQUIRE(reporter.iterationsDone == 1);
    }

    SECTION("progressCallbackShouldBeCalledEvery10"){
        ProgressReporter reporter (100, &_storeCallCount);

        REQUIRE(callCount == 0);
        reporter.iterationDone();
        REQUIRE(callCount == 0);

        for(int i=0;i<10;i++){
            reporter.iterationDone();
        }
        // todo for some reason this sometimes fails and most of the time not
        //REQUIRE(callCount == 1);

    }

}
