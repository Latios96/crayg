//
// Created by Jan Honsbrok on 2019-08-10.
//
#include <catch2/catch.hpp>

#include <KnipserTest.h>
#include <TestResult.h>


TEST_CASE("TestResult"){
    const KnipserTest myTest = KnipserTest(std::string("my test"), [](const TestContext &context) {});

    SECTION("should create passed test"){
        TestResult passedTestResult = TestResult::createPassed(myTest);

        REQUIRE(passedTestResult.test == myTest);
        REQUIRE(passedTestResult.passed);
        REQUIRE(passedTestResult.message.empty());
    }

    SECTION("should create failed test"){
        TestResult passedTestResult = TestResult::createFailed(myTest, "my message");

        REQUIRE(passedTestResult.test == myTest);
        REQUIRE_FALSE(passedTestResult.passed);
        REQUIRE(passedTestResult.message == "my message");
    }
}