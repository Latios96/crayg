#include "image/film/buffers/FilmBufferVariants.h"
#include <catch2/catch.hpp>

namespace crayg {
TEST_CASE("FilmBufferVariants::getAsAccumulationBufferVariantPtr") {

    SECTION("should return accumulation buffer ptr") {
        const auto &testData = GENERATE(
            table<FilmBufferVariantPtr>({new FloatAccumulationBuffer(10, 5), new Color3fAccumulationBuffer(10, 5)}));

        const auto buffer = std::get<0>(testData);

        REQUIRE(FilmBufferVariants::getAsAccumulationBufferVariantPtr(buffer).has_value());

        FilmBufferVariants::freeFilmBufferVariantPtr(buffer);
    }

    SECTION("should return empty optional for non-accumulation buffer") {
        const auto &testData =
            GENERATE(table<FilmBufferVariantPtr>({new FloatValueBuffer(10, 5), new IntValueBuffer(10, 5),
                                                  new Color3fValueBuffer(10, 5), new Color3iValueBuffer(10, 5)}));

        const auto buffer = std::get<0>(testData);

        REQUIRE_FALSE(FilmBufferVariants::getAsAccumulationBufferVariantPtr(buffer).has_value());

        FilmBufferVariants::freeFilmBufferVariantPtr(buffer);
    }
}

TEST_CASE("FilmBufferVariants::getPixelDepth") {

    SECTION("should return pixel depth correctly for float") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getPixelDepth(ptr) == FilmPixelDepth::FLOAT32);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }

    SECTION("should return pixel depth correctly for int") {
        FilmBufferVariantPtr ptr = new IntValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getPixelDepth(ptr) == FilmPixelDepth::UINT8);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }
}

TEST_CASE("FilmBufferVariants::getChannelCount") {

    SECTION("should return channel count correctly for float") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getChannelCount(ptr) == 1);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }

    SECTION("should return channel count correctly for Color3f") {
        FilmBufferVariantPtr ptr = new Color3fValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getChannelCount(ptr) == 3);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }
}

}