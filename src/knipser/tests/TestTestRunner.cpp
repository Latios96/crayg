//
// Created by Jan Honsbrok on 2019-08-10.
//
#include <catch2/catch.hpp>
#include <TestRunner.h>
#include "TestRegistry.h"

TEST_CASE("passing test should generate passing result", "[TestRunner]") {
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
    REQUIRE(testResults[0].testContext == TestContext("demo/passing test", "demoReference/passing test"));
}

TEST_CASE("failing test should generate failing result with message", "[TestRunner]") {
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
    REQUIRE(testResults[0].testContext == TestContext("demo/failing test", "demoReference/failing test"));
}

TEST_CASE("TestRunner should execute test based on predicate", "[TestRunner]") {
    TestRegistry testRegistry;
    RunConfig runConfig("demo", "demoReference", std::vector<TestPattern>({TestPattern("passing test")}));
    const KnipserTest passingTest = KnipserTest(std::string("passing test"), [](const TestContext &context) {});
    testRegistry.registerTest(passingTest);

    TestRunner testRunner(testRegistry, runConfig);
    const std::vector<TestResult> testResults = testRunner.execute();

    REQUIRE(testResults.size() == 1);
}

TEST_CASE("TestRunner should not execute test based on predicate", "[TestRunner]") {
    TestRegistry testRegistry;
    RunConfig runConfig("demo", "demoReference", std::vector<TestPattern>({TestPattern("not_passing_test")}));
    const KnipserTest passingTest = KnipserTest(std::string("passing test"), [](const TestContext &context) {});
    testRegistry.registerTest(passingTest);

    TestRunner testRunner(testRegistry, runConfig);
    const std::vector<TestResult> testResults = testRunner.execute();

    REQUIRE(testResults.empty());
}



