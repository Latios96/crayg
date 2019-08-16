//
// Created by Jan Honsbrok on 2019-08-10.
//
#include <catch2/catch.hpp>
#include <TestRunner.h>
#include "TestRegistry.h"


TEST_CASE("passing test should generate passing result") {
    TestRegistry testRegistry;
    RunConfig runConfig("demo", "demoReference");
    const KnipserTest passingTest = KnipserTest(std::string("passing test"), [](const TestContext &context) {});
    testRegistry.registerTest(passingTest);

    TestRunner testRunner(testRegistry, runConfig);
    const std::vector<TestResult> testResults = testRunner.execute();

    REQUIRE(testResults.size() == 1);
    REQUIRE(testResults[0].test == passingTest);
    REQUIRE(testResults[0].passed);
    REQUIRE(testResults[0].message.empty());
}

TEST_CASE("failing test should generate failing result with message") {
    TestRegistry testRegistry;
    RunConfig runConfig("demo", "demoReference");
    const KnipserTest failingTest = KnipserTest(std::string("failing test"), [](const TestContext &context) {
        throw std::exception();
    });
    testRegistry.registerTest(failingTest);

    TestRunner testRunner(testRegistry, runConfig);
    const std::vector<TestResult> testResults = testRunner.execute();

    REQUIRE(testResults.size() == 1);
    REQUIRE(testResults[0].test == failingTest);
    REQUIRE_FALSE(testResults[0].passed);
    REQUIRE(testResults[0].message == "std::exception");
}



