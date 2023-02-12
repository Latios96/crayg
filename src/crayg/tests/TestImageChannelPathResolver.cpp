#include <catch2/catch.hpp>
#include "utils/ImageChannelPathResolver.h"

namespace crayg {

TEST_CASE("ImageChannelPathResolver::resolve") {

    SECTION("should resolve path for rgb channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("test.png", "rgb");

        REQUIRE(newPath == "test.png");
    }

    SECTION("should resolve path with # for rgb channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("test.#.png", "rgb");

        REQUIRE(newPath == "test.#.png");
    }

    SECTION("should resolve path with digits for rgb channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("test.0001.png", "rgb");

        REQUIRE(newPath == "test.0001.png");
    }

    SECTION("should resolve path for alpha channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("test.png", "alpha");

        REQUIRE(newPath == "test.alpha.png");
    }

    SECTION("should resolve path with # for alpha channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("test.#.png", "alpha");

        REQUIRE(newPath == "test.alpha.#.png");
    }

    SECTION("should resolve path with digits for alpha channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("test.0001.png", "alpha");

        REQUIRE(newPath == "test.alpha.0001.png");
    }
}

}