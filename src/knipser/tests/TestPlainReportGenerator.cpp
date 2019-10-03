//
// Created by Jan Honsbrok on 2019-08-10.
//
#include <catch2/catch.hpp>
#include <PlainReportGenerator.h>
#include <sstream>
#include <fmt/format.h>

TEST_CASE("PlainReportGenerator") {
    const KnipserTest myTest = KnipserTest(std::string("my test"), [](const TestContext &context) {});

    std::vector<TestResult> results;

    SECTION("should report passed test") {
        results.push_back(TestResult::createPassed(myTest, TestContext("demo", "reference")));
        PlainReportGenerator plainReportGenerator(results);

        std::stringstream ss;
        plainReportGenerator.generateReport(ss);
        std::string s = ss.str();

        REQUIRE(ss.str().find("my test") != -1);
        REQUIRE(ss.str().find("OK") != -1);
    }

    SECTION("should report failed test") {

    }

}