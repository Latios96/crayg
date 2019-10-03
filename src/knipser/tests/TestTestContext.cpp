//
// Created by Jan Honsbrok on 2019-08-11.
//
#include <catch2/catch.hpp>
#include <TestContext.h>

TEST_CASE("TestTestContext") {
    TestContext testContext("demo", "demoReference");

    SECTION("shouldReturnCorrectOutputFolder") {
        REQUIRE(testContext.getOutputFolder() == "demo");
    }

    SECTION("shouldReturnCorrectOutputName") {
        testContext.setImageOutputName("test.exr");
        REQUIRE(testContext.getOutputFilename() == "demo/test.exr");
    }

    SECTION("canNotSetImageOutputNameSecondTime") {
        testContext.setImageOutputName("test.exr");
        REQUIRE_THROWS_AS(testContext.setImageOutputName("test.exr"), std::logic_error);
    }

    SECTION("imageOutputIsSetIsFalse") {
        REQUIRE_FALSE(testContext.imageOutputIsSet());
    }

    SECTION("imageOutputIsSetIsTrue") {
        testContext.setImageOutputName("test");
        REQUIRE(testContext.imageOutputIsSet());
    }

    SECTION("shouldReturnCorrectReferenceFolder") {
        REQUIRE(testContext.getReferenceFolder() == "demoReference");
    }

    SECTION("shouldReturnCorrectReferenceName") {
        testContext.setImageOutputName("test.exr");
        REQUIRE(testContext.getReferenceFilename() == "demoReference/test.exr");
    }
}

