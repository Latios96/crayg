//
// Created by Jan on 19.05.2022.
//
#include <catch2/catch.hpp>
#include "basics/Resolution.h"

namespace crayg {

TEST_CASE("Resolution/parse") {

    SECTION("parse valid") {
        const Resolution resolution = Resolution::parse("800x600");

        REQUIRE(resolution == Resolution(800, 600));
    }

    SECTION("parse invalid") {
        REQUIRE_THROWS_AS(Resolution::parse(""), std::runtime_error);
        REQUIRE_THROWS_AS(Resolution::parse("800"), std::runtime_error);
        REQUIRE_THROWS_AS(Resolution::parse("800x"), std::runtime_error);
        REQUIRE_THROWS_AS(Resolution::parse("x600"), std::runtime_error);

    }
}

}