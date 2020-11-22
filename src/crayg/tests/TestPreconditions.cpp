//
// Created by Jan on 22.11.2020.
//
#include <catch2/catch.hpp>
#include <Preconditions.h>

TEST_CASE("check argument with expression", "[Preconditions]") {
    SECTION("pass") {
        Preconditions::checkArgument(1 == 1);
    }

    SECTION("fail") {
        REQUIRE_THROWS_AS(Preconditions::checkArgument(1 == 2), std::invalid_argument);
    }
}

TEST_CASE("check argument with expression and message", "[Preconditions]") {
    SECTION("pass") {
        Preconditions::checkArgument(1 == 1, "This is my message");
    }

    SECTION("fail") {
        REQUIRE_THROWS_AS(Preconditions::checkArgument(1 == 2, "This is my message"), std::invalid_argument);
        try {
            Preconditions::checkArgument(1 == 2, "This is my message");
        }
        catch (std::invalid_argument &e) {
            REQUIRE(e.what() == std::string("This is my message"));
        }
    }
}

TEST_CASE("check unit vector", "[Preconditions]") {
    SECTION("pass") {
        Preconditions::checkIsUnitVector(Vector3f(1, 0, 0));
    }

    SECTION("fail") {
        REQUIRE_THROWS_AS(Preconditions::checkIsUnitVector(Vector3f(1, 2, 3)), std::invalid_argument);
    }
}
