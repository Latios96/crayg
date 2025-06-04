#include "image/film/buffers/FilmBufferFactory.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("FilmBufferFactory::createValueBuffer") {

    SECTION("should create FloatValueBuffer") {
        auto bufferVariant = FilmBufferFactory::createValueBuffer({10, 5}, FilmPixelDepth::FLOAT32, 1);

        REQUIRE(std::holds_alternative<FloatValueBuffer *>(bufferVariant));

        FilmBufferVariants::freeFilmBufferVariantPtr(bufferVariant);
    }

    SECTION("should create IntValueBuffer") {
        auto bufferVariant = FilmBufferFactory::createValueBuffer({10, 5}, FilmPixelDepth::UINT8, 1);

        REQUIRE(std::holds_alternative<IntValueBuffer *>(bufferVariant));

        FilmBufferVariants::freeFilmBufferVariantPtr(bufferVariant);
    }

    SECTION("should create Color3fValueBuffer") {
        auto bufferVariant = FilmBufferFactory::createValueBuffer({10, 5}, FilmPixelDepth::FLOAT32, 3);

        REQUIRE(std::holds_alternative<Color3fValueBuffer *>(bufferVariant));

        FilmBufferVariants::freeFilmBufferVariantPtr(bufferVariant);
    }

    SECTION("should create Color3iValueBuffer") {
        auto bufferVariant = FilmBufferFactory::createValueBuffer({10, 5}, FilmPixelDepth::UINT8, 3);

        REQUIRE(std::holds_alternative<Color3iValueBuffer *>(bufferVariant));

        FilmBufferVariants::freeFilmBufferVariantPtr(bufferVariant);
    }

    SECTION("should throw for unsupported") {
        REQUIRE_THROWS(FilmBufferFactory::createValueBuffer({10, 5}, FilmPixelDepth::UINT8, 2));
    }
}

TEST_CASE("FilmBufferFactory::createAccumulationBuffer") {

    SECTION("should create FloatValueBuffer") {
        auto bufferVariant = FilmBufferFactory::createAccumulationBuffer({10, 5}, FilmPixelDepth::FLOAT32, 1);

        REQUIRE(std::holds_alternative<FloatAccumulationBuffer *>(bufferVariant));

        FilmBufferVariants::freeFilmBufferVariantPtr(bufferVariant);
    }

    SECTION("should create Color3fValueBuffer") {
        auto bufferVariant = FilmBufferFactory::createAccumulationBuffer({10, 5}, FilmPixelDepth::FLOAT32, 3);

        REQUIRE(std::holds_alternative<Color3fAccumulationBuffer *>(bufferVariant));

        FilmBufferVariants::freeFilmBufferVariantPtr(bufferVariant);
    }

    SECTION("should throw for unsupported") {
        REQUIRE_THROWS(FilmBufferFactory::createAccumulationBuffer({10, 5}, FilmPixelDepth::UINT8, 2));
    }
}

}