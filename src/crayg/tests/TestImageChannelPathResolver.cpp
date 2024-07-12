#include "utils/ImageChannelPathResolver.h"
#include <catch2/catch.hpp>
#include <filesystem>

namespace crayg {

std::string normalize(const std::string &p) {
    return (std::filesystem::absolute(std::filesystem::path(p))).string();
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