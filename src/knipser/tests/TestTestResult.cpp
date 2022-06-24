#include <catch2/catch.hpp>

#include <KnipserTest.h>
#include <TestResult.h>

namespace knipser {

TEST_CASE("TestResult") {
    const KnipserTest myTest = KnipserTest(std::string("my test"), [](const TestContext &context) {});

    TestContext testContext("demo", "reference");

    SECTION("should create passed test") {
        TestResult passedTestResult = TestResult::createPassed(myTest, testContext);

        REQUIRE(passedTestResult.test == myTest);
        REQUIRE(passedTestResult.isPassed());
        REQUIRE(passedTestResult.message.empty());
        REQUIRE(passedTestResult.testContext == testContext);
    }

    SECTION("should create failed test") {
        TestResult failedTestResult = TestResult::createFailed(myTest, "my message", testContext);

        REQUIRE(failedTestResult.test == myTest);
        REQUIRE(failedTestResult.isFailed());
        REQUIRE(failedTestResult.message == "my message");
        REQUIRE(failedTestResult.testContext == testContext);
    }

}

}