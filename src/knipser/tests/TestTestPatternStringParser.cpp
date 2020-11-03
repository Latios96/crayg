#include <catch2/catch.hpp>
#include <TestPatternStringParser.h>

TEST_CASE("TestTestPatternStringParser") {

    SECTION("parse") {
        REQUIRE(TestPatternStringParser("").parse() == std::vector<TestPattern>());

        REQUIRE(TestPatternStringParser("myAwesomeTest").parse()
                    == std::vector<TestPattern> {TestPattern("myAwesomeTest")});

        REQUIRE(TestPatternStringParser("myAwesomeTest,myAwesomeTest2").parse()
                    == std::vector<TestPattern> {TestPattern("myAwesomeTest"), TestPattern("myAwesomeTest2")});

        REQUIRE(TestPatternStringParser("myAwesomeTest,,myAwesomeTest2").parse()
                    == std::vector<TestPattern> {TestPattern("myAwesomeTest"), TestPattern("myAwesomeTest2")});

        REQUIRE(TestPatternStringParser("myAwesomeTest , , myAwesomeTest2").parse()
                    == std::vector<TestPattern> {TestPattern("myAwesomeTest"), TestPattern("myAwesomeTest2")});

        REQUIRE(TestPatternStringParser("myAwesomeTest,, myAwesomeTest2").parse()
                    == std::vector<TestPattern> {TestPattern("myAwesomeTest"), TestPattern("myAwesomeTest2")});
    }

}

