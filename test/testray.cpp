//
// Created by Jan Honsbrok on 06.11.18.
//
#include <catch.hpp>
#include "foundation/Ray.h"

TEST_CASE("Ray/shouldCreateInvalid", "[Ray]"){
    Ray invalid = Ray::createInvalid();
    REQUIRE_FALSE(invalid.startPoint.isValid());
    REQUIRE_FALSE(invalid.direction.isValid());
    REQUIRE(invalid.length == std::numeric_limits<float>::max());
}

TEST_CASE("Ray/shouldBeInvalid", "[Ray]"){
    Ray invalid = Ray::createInvalid();
    REQUIRE_FALSE(invalid.isValid());
}

