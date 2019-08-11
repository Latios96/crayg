//
// Created by Jan Honsbrok on 2019-08-11.
//
#include <catch2/catch.hpp>
#include <TestContext.h>

TEST_CASE("TestTestContext"){
    TestContext testContext("demo");

    SECTION("shouldReturnCorrectOutputFolder"){
        REQUIRE(testContext.getOutputFolder() == "demo");
    }

    SECTION("shouldReturnCorrectOutputName"){
        REQUIRE(testContext.getOutputFilename("test.exr") == "demo/test.exr");
    }
}

