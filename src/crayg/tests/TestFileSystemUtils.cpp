#include <catch2/catch.hpp>
#include "utils/FileSystemUtils.h"

namespace crayg {

TEST_CASE("FileSystemUtils::swapFileExtension") {

    SECTION("should replace extension") {
        const auto pathWithNewExtension = FileSystemUtils::swapFileExtension("myImage.png", "txt");

        REQUIRE(pathWithNewExtension == "myImage.txt");
    }

    SECTION("should add extension") {
        const auto pathWithNewExtension = FileSystemUtils::swapFileExtension("myImage", "txt");

        REQUIRE(pathWithNewExtension == "myImage.txt");
    }

    SECTION("should not add two dots") {
        const auto pathWithNewExtension = FileSystemUtils::swapFileExtension("myImage.png", ".txt");

        REQUIRE(pathWithNewExtension == "myImage.txt");
    }
}

}