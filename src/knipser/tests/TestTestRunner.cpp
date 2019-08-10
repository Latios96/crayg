//
// Created by Jan Honsbrok on 2019-08-10.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <TestRunner.h>
#include "TestRegistry.h"

TEST_CASE("TestResult"){
    const KnipserTest myTest = KnipserTest(std::string("my test"), [](const TestContext &context) {});

    SECTION("should create passed test"){
        TestResult passedTestResult = TestResult::createPassed(myTest);

        REQUIRE(passedTestResult.test == myTest);
        REQUIRE(passedTestResult.passed);
        REQUIRE(passedTestResult.message == "");
    }

    SECTION("should create failed test"){
        TestResult passedTestResult = TestResult::createFailed(myTest, "my message");

        REQUIRE(passedTestResult.test == myTest);
        REQUIRE_FALSE(passedTestResult.passed);
        REQUIRE(passedTestResult.message == "my message");
    }
}

TEST_CASE("passing test should generate passing result"){
    TestRegistry testRegistry;
    const KnipserTest passingTest = KnipserTest(std::string("passing test"), [](const TestContext &context) {});
    testRegistry.registerTest(passingTest);
    
    TestRunner testRunner(testRegistry);
    const std::vector<TestResult> testResults = testRunner.execute();

    REQUIRE(testResults.size() == 1);
    REQUIRE(testResults[0].test == passingTest);
    REQUIRE(testResults[0].passed);
    REQUIRE(testResults[0].message == "");
}

TEST_CASE("failing test should generate failing result with message"){
    TestRegistry testRegistry;
    const KnipserTest failingTest = KnipserTest(std::string("failing test"), [](const TestContext &context) {
        throw std::exception();
    });
    testRegistry.registerTest(failingTest);

    TestRunner testRunner(testRegistry);
    const std::vector<TestResult> testResults = testRunner.execute();

    REQUIRE(testResults.size() == 1);
    REQUIRE(testResults[0].test == failingTest);
    REQUIRE_FALSE(testResults[0].passed);
    REQUIRE(testResults[0].message == "std::exception");
}


