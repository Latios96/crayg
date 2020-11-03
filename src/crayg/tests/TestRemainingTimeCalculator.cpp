//
// Created by jan on 27.12.18.
//

#include <catch2/catch.hpp>
#include <utils/RemainingTimeCalculator.h>

TEST_CASE("RemainingTimeCalculator") {
    RemainingTimeCalculator remainingTimeCalculator(std::chrono::steady_clock::now());

    SECTION("progressOfZeroShouldReturn-1") {
        REQUIRE(remainingTimeCalculator.getRemainingTimeByProgress(0) == -1);
    }

    SECTION("progressOf100ShouldReturn0") {
        REQUIRE(remainingTimeCalculator.getRemainingTimeByProgress(100) == 0);
    }SECTION("progressOf1ShouldReturnElapsedTime*100") {
        RemainingTimeCalculator remainingTimeCalculator(std::chrono::steady_clock::now() - std::chrono::seconds(5));
        REQUIRE(remainingTimeCalculator.getRemainingTimeByProgress(2) == 245);
    }
}