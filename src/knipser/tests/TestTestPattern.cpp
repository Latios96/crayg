#include <catch2/catch.hpp>
#include <TestPattern.h>

namespace knipser {

TEST_CASE("TestTestPattern") {
    std::string testName = "myAwesomeTest";

    SECTION("should match string") {
        REQUIRE(TestPattern("myAwesomeTest").matches(testName));
        REQUIRE(TestPattern("myawesometest").matches(testName));
        REQUIRE(TestPattern("MyaWesometEst").matches(testName));
    }

    SECTION("should match with wildcard") {
        REQUIRE(TestPattern("myAwesome.*").matches(testName));
        REQUIRE(TestPattern("myawesome.*").matches(testName));
        REQUIRE(TestPattern("MyaWesome.*").matches(testName));
    }

    SECTION("should not match string") {
        REQUIRE_FALSE(TestPattern("myAwesome").matches(testName));
        REQUIRE_FALSE(TestPattern("myawesmetest").matches(testName));
        REQUIRE_FALSE(TestPattern("MyaWesometEt").matches(testName));
    }

    SECTION("should match with wildcard") {
        REQUIRE_FALSE(TestPattern("myAwesme.*").matches(testName));

    }
}

}

