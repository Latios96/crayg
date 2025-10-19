#include "crayg/image/film/buffers/FilmBufferVariants.h"
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

TEST_CASE("FilmBufferVariants::getAsValueBufferVariantPtr") {

    SECTION("should return accumulation buffer ptr") {
        const auto &testData =
            GENERATE(table<FilmBufferVariantPtr>({new FloatValueBuffer(10, 5), new Color3fValueBuffer(10, 5)}));

        const auto buffer = std::get<0>(testData);

        REQUIRE(FilmBufferVariants::getAsValueBufferVariantPtr(buffer).has_value());

        FilmBufferVariants::freeFilmBufferVariantPtr(buffer);
    }

    SECTION("should return empty optional for non-accumulation buffer") {
        const auto &testData = GENERATE(
            table<FilmBufferVariantPtr>({new FloatAccumulationBuffer(10, 5), new Color3fAccumulationBuffer(10, 5)}));

        const auto buffer = std::get<0>(testData);

        REQUIRE_FALSE(FilmBufferVariants::getAsValueBufferVariantPtr(buffer).has_value());

        FilmBufferVariants::freeFilmBufferVariantPtr(buffer);
    }
}

TEST_CASE("FilmBufferVariants::getAsSumBufferVariantPtr") {

    SECTION("should return accumulation buffer ptr") {
        const auto &testData =
            GENERATE(table<FilmBufferVariantPtr>({new FloatSumBuffer(10, 5), new IntSumBuffer(10, 5),
                                                  new Color3fSumBuffer(10, 5), new Color3iSumBuffer(10, 5)}));

        const auto buffer = std::get<0>(testData);

        REQUIRE(FilmBufferVariants::getAsSumBufferVariantPtr(buffer).has_value());

        FilmBufferVariants::freeFilmBufferVariantPtr(buffer);
    }

    SECTION("should return empty optional for non-accumulation buffer") {
        const auto &testData =
            GENERATE(table<FilmBufferVariantPtr>({new FloatAccumulationBuffer(10, 5), new FloatValueBuffer(10, 5)}));

        const auto buffer = std::get<0>(testData);

        REQUIRE_FALSE(FilmBufferVariants::getAsSumBufferVariantPtr(buffer).has_value());

        FilmBufferVariants::freeFilmBufferVariantPtr(buffer);
    }
}

TEST_CASE("FilmBufferVariants::getPixelFormat") {

    SECTION("should return pixel format correctly for float") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getPixelFormat(ptr) == PixelFormat::FLOAT32);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }

    SECTION("should return pixel format correctly for int") {
        FilmBufferVariantPtr ptr = new IntValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getPixelFormat(ptr) == PixelFormat::UINT8);

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

TEST_CASE("FilmBufferVariants::getDataPtr") {

    SECTION("should return data ptr correctly for ValueBuffer") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getDataPtr(ptr) != nullptr);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }

    SECTION("should return data ptr correctly for AccumulationBuffer") {
        FilmBufferVariantPtr ptr = new Color3fAccumulationBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getDataPtr(ptr) != nullptr);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }
}

TEST_CASE("FilmBufferVariants::getWidth") {

    SECTION("should return width") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getWidth(ptr) == 10);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }
}

TEST_CASE("FilmBufferVariants::getHeight") {

    SECTION("should return height") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getHeight(ptr) == 5);

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }
}

TEST_CASE("FilmBufferVariants::getResolution") {

    SECTION("should return resolution") {
        FilmBufferVariantPtr ptr = new FloatValueBuffer(10, 5);

        REQUIRE(FilmBufferVariants::getResolution(ptr) == Resolution(10, 5));

        FilmBufferVariants::freeFilmBufferVariantPtr(ptr);
    }
}

}