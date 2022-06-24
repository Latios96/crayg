#include <catch2/catch.hpp>
#include "ExecuteTestPredicate.h"

namespace knipser {

TEST_CASE("ExecuteTestPredicate should return true", "[ExecuteTestPredicate]") {
    KnipserTest test("myAwesomeTest", nullptr);

    ExecuteTestPredicate predicate((std::vector<TestPattern>()));
    REQUIRE(predicate.shouldExecute(test));

    ExecuteTestPredicate predicate2((std::vector<TestPattern>({TestPattern("myAwesomeTest")})));
    REQUIRE(predicate.shouldExecute(test));
}

TEST_CASE("ExecuteTestPredicate should return false", "[ExecuteTestPredicate]") {
    KnipserTest test("myAwesomeTest", nullptr);

    ExecuteTestPredicate predicate((std::vector<TestPattern>({TestPattern("Dieter")})));
    REQUIRE_FALSE(predicate.shouldExecute(test));
}

}