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
        testContext.setImageOutputName("test.exr");
        REQUIRE(testContext.getOutputFilename() == "demo/test.exr");
    }

    SECTION("canNotSetImageOutputNameSecondTime"){
        testContext.setImageOutputName("test.exr");
        REQUIRE_THROWS_AS(testContext.setImageOutputName("test.exr"), std::logic_error);
    }
}

