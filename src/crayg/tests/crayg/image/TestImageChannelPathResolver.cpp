#include "crayg/image/ImageChannelPathResolver.h"
#include <catch2/catch.hpp>
#include <filesystem>

namespace crayg {

std::filesystem::path normalize(const std::filesystem::path &p) {
    return std::filesystem::absolute(std::filesystem::path(p));
}

TEST_CASE("ImageChannelPathResolver::resolve") {

    SECTION("should resolve path for rgb channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.png", "rgb");

        REQUIRE(newPath == "some/path/test.png");
    }

    SECTION("should resolve path with # for rgb channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.#.png", "rgb");

        REQUIRE(newPath == "some/path/test.#.png");
    }

    SECTION("should resolve path with digits for rgb channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.0001.png", "rgb");

        REQUIRE(newPath == "some/path/test.0001.png");
    }

    SECTION("should resolve path for color channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.png", "color");

        REQUIRE(newPath == "some/path/test.png");
    }

    SECTION("should resolve path with # for color channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.#.png", "color");

        REQUIRE(newPath == "some/path/test.#.png");
    }

    SECTION("should resolve path with digits for color channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.0001.png", "color");

        REQUIRE(newPath == "some/path/test.0001.png");
    }

    SECTION("should resolve path for alpha channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.png", "alpha");

        REQUIRE(normalize(newPath) == normalize(("some/path/test.alpha.png")));
    }

    SECTION("should resolve path with # for alpha channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.#.png", "alpha");

        REQUIRE(normalize(newPath) == normalize("some/path/test.alpha.#.png"));
    }

    SECTION("should resolve path with digits for alpha channel to unchanged path") {
        ImageChannelPathResolver imageChannelPathResolver;

        const auto newPath = imageChannelPathResolver.resolve("some/path/test.0001.png", "alpha");

        REQUIRE(normalize(newPath) == normalize("some/path/test.alpha.0001.png"));
    }
}

}