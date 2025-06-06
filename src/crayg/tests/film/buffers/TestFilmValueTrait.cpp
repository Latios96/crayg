#include "image/film/buffers/FilmValueTrait.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ValueTrait<float>") {

    SECTION("should convert correctly to float") {
        REQUIRE(FilmValueTrait<float>::toFloat(42) == 42);
    }

    SECTION("should convert correctly from float") {
        REQUIRE(FilmValueTrait<float>::fromFloat(42) == 42);
    }

    SECTION("should have correct name") {
        REQUIRE(FilmValueTrait<float>::name == "f32");
    }
}

TEST_CASE("ValueTrait<uint8>") {

    SECTION("should convert correctly to float") {
        REQUIRE(FilmValueTrait<uint8_t>::toFloat(0) == 0);
        REQUIRE(FilmValueTrait<uint8_t>::toFloat(128) == Catch::Detail::Approx(0.50196f));
        REQUIRE(FilmValueTrait<uint8_t>::toFloat(255) == 1.f);
    }

    SECTION("should convert correctly from float") {
        REQUIRE(FilmValueTrait<uint8_t>::fromFloat(-1) == 0);
        REQUIRE(FilmValueTrait<uint8_t>::fromFloat(0) == 0);
        REQUIRE(FilmValueTrait<uint8_t>::fromFloat(0.5f) == 127);
        REQUIRE(FilmValueTrait<uint8_t>::fromFloat(1) == 255);
        REQUIRE(FilmValueTrait<uint8_t>::fromFloat(1.1) == 255);
    }

    SECTION("should have correct name") {
        REQUIRE(FilmValueTrait<uint8_t>::name == "uint8");
    }
}

}