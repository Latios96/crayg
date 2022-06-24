#include <catch2/catch.hpp>
#include <utils/Preconditions.h>

#ifdef ENFORCE_CHECKS

namespace crayg {

TEST_CASE("check argument with expression", "[Preconditions]") {
    SECTION("pass") {
        Preconditions::checkArgument(1 == 1, FAILURE_INFORMATION);
    }

    SECTION("fail") {
        REQUIRE_THROWS_AS(Preconditions::checkArgument(1 == 2, FAILURE_INFORMATION), std::invalid_argument);
    }
}

TEST_CASE("check argument with expression and message", "[Preconditions]") {
    SECTION("pass") {
        Preconditions::checkArgument(1 == 1, "This is my message", FAILURE_INFORMATION);
    }

    SECTION("fail") {
        REQUIRE_THROWS_AS(Preconditions::checkArgument(1 == 2, "This is my message", FAILURE_INFORMATION),
                          std::invalid_argument);
        try {
            Preconditions::checkArgument(1 == 2, "This is my message", FAILURE_INFORMATION);
        }
        catch (std::invalid_argument &e) {
            REQUIRE(std::string(e.what()).rfind("This is my message", 0) == 0);
        }
    }
}

TEST_CASE("check unit vector", "[Preconditions]") {
    SECTION("pass") {
        Preconditions::checkIsUnitVector(Vector3f(1, 0, 0), FAILURE_INFORMATION);
    }

    SECTION("fail") {
        REQUIRE_THROWS_AS(Preconditions::checkIsUnitVector(Vector3f(1, 2, 3), FAILURE_INFORMATION),
                          std::invalid_argument);
    }
}

}
#endif
