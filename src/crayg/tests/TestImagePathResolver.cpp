#include "fixtures/TemporaryDirectory.h"

#include <boost/regex.hpp>
#include <catch2/catch.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utils/ImagePathResolver.h>

namespace crayg {

TEST_CASE("ImagePathResolver should replace #") {

    SECTION("no # should not change") {
        TemporaryDirectory temporaryDirectory;
        const auto path = temporaryDirectory.writeToFile("1203e5c176ab4e7fbe124ae4258131b4.1000.png", "");

        const std::filesystem::path result = ImagePathResolver::resolve(path);

        REQUIRE(result == temporaryDirectory.getPath() / "1203e5c176ab4e7fbe124ae4258131b4.1000.png");
    }

    SECTION("not existing before") {
        const std::filesystem::path result = ImagePathResolver::resolve("1203e5c176ab4e7fbe124ae4258131b4.#.png");

        REQUIRE(result == "1203e5c176ab4e7fbe124ae4258131b4.0001.png");
    }

    SECTION("existing file") {
        TemporaryDirectory temporaryDirectory;
        const auto path = temporaryDirectory.writeToFile("1203e5c176ab4e7fbe124ae4258131b4.0001.png", "");

        const std::filesystem::path result =
            ImagePathResolver::resolve(temporaryDirectory.getPath() / "1203e5c176ab4e7fbe124ae4258131b4.#.png");

        REQUIRE(result == temporaryDirectory.getPath() / "1203e5c176ab4e7fbe124ae4258131b4.0002.png");
    }
}

TEST_CASE("ImagePathResolver::parseImageNumber") {

    SECTION("should parse '1001'") {
        const std::optional<int> frameNumber =
            ImagePathResolver::parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.1001.png");
        REQUIRE(*frameNumber == 1001);
    }

    SECTION("should parse '0001'") {
        const std::optional<int> frameNumber =
            ImagePathResolver::parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.0001.png");
        REQUIRE(*frameNumber == 0001);
    }

    SECTION("should parse '0000'") {
        const std::optional<int> frameNumber =
            ImagePathResolver::parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.0000.png");
        REQUIRE(*frameNumber == 0000);
    }

    SECTION("should parse '-1'") {
        const std::optional<int> frameNumber =
            ImagePathResolver::parseImageNumber("1203e5c176ab4e7fbe124ae4258131b4.png");
        REQUIRE_FALSE(frameNumber.has_value());
    }
}

TEST_CASE("ImagePathResolver::matchesTemplate") {

    REQUIRE(ImagePathResolver::matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.#.png",
                                               "1203e5c176ab4e7fbe124ae4258131b4.1.png"));
    REQUIRE(ImagePathResolver::matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.#.png",
                                               "1203e5c176ab4e7fbe124ae4258131b4.1000.png"));
    REQUIRE(ImagePathResolver::matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.#.png",
                                               "1203e5c176ab4e7fbe124ae4258131b4.0001.png"));
    REQUIRE_FALSE(ImagePathResolver::matchesTemplate("1203e5c176ab4e7fbe124ae4258131b4.1000.png",
                                                     "1203e5c176ab4e7fbe124ae4258131b4.0001.png"));
    REQUIRE_FALSE(ImagePathResolver::matchesTemplate("tt.png", "1203e5c176ab4e7fbe124ae4258131b4.0001.png"));
}

}
