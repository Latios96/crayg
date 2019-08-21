//
// Created by Jan Honsbrok on 2019-08-10.
//
#include <catch2/catch.hpp>

#include <KnipserTest.h>
#include <TestResult.h>


TEST_CASE("TestResult"){
    const KnipserTest myTest = KnipserTest(std::string("my test"), [](const TestContext &context) {});

    TestContext testContext("demo", "reference");

    SECTION("should create passed test"){
        TestResult passedTestResult = TestResult::createPassed(myTest, testContext);

        REQUIRE(passedTestResult.test == myTest);
        REQUIRE(passedTestResult.passed);
        REQUIRE(passedTestResult.message.empty());
        REQUIRE(passedTestResult.testContext == testContext);
    }

    SECTION("should create failed test"){
        TestResult failedTestResult = TestResult::createFailed(myTest, "my message", testContext);

        REQUIRE(failedTestResult.test == myTest);
        REQUIRE_FALSE(failedTestResult.passed);
        REQUIRE(failedTestResult.message == "my message");
        REQUIRE(failedTestResult.testContext == testContext);
    }

}