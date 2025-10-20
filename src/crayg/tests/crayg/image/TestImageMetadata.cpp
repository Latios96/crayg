#include "crayg/image/ImageMetadata.h"
#include <catch2/catch.hpp>

namespace crayg {

TEST_CASE("ImageMetadata::read/write") {

    SECTION("should read and write int correctly") {
        ImageMetadata imageMetadata;

        imageMetadata.write("int", 1);

        REQUIRE(imageMetadata.read<int>("int") == 1);
    }

    SECTION("should read and write float correctly") {
        ImageMetadata imageMetadata;

        imageMetadata.write("float", 1.0f);

        REQUIRE(imageMetadata.read<float>("float") == 1.0f);
    }

    SECTION("should read and write seconds correctly") {
        ImageMetadata imageMetadata;

        imageMetadata.write("seconds", std::chrono::seconds(1));

        REQUIRE(imageMetadata.read<std::chrono::seconds>("seconds") == std::chrono::seconds(1));
    }

    SECTION("should overwrite correctly") {
        ImageMetadata imageMetadata;

        imageMetadata.write("int", 1);
        imageMetadata.write("int", 2);

        REQUIRE(imageMetadata.read<int>("int") == 2);
    }
}

TEST_CASE("ImageMetadata::has") {

    SECTION("existing key should return true") {
        ImageMetadata imageMetadata;
        imageMetadata.write("int", 1);

        REQUIRE(imageMetadata.has("int"));
    }

    SECTION("not existing key should return false") {
        ImageMetadata imageMetadata;
        imageMetadata.write("int", 1);

        REQUIRE_FALSE(imageMetadata.has("not existing"));
    }
}

TEST_CASE("ImageMetadata::iterate") {

    SECTION("should correctly iterate empty image metadata") {
        ImageMetadata imageMetadata;

        bool visited = false;
        for (auto &m : imageMetadata) {
            visited = true;
        }

        REQUIRE_FALSE(visited);
    }

    SECTION("should correctly iterate image metadata correctly") {
        ImageMetadata imageMetadata;
        imageMetadata.write("int", 1);
        imageMetadata.write("float", 1.0f);
        imageMetadata.write("seconds", std::chrono::seconds(1));

        int count = 0;
        for (auto &m : imageMetadata) {
            count += 1;
        }

        REQUIRE(count == 3);
    }
}

}