//
// Created by Jan on 23.11.2020.
//
#include <catch2/catch.hpp>
#include <ImagePathResolver.h>
#include <boost/regex.hpp>
#include <iostream>

// TODO File Fixture
// TODO File Fixture

TEST_CASE("ImagePathResolver should replace #") {
    ImagePathResolver imagePathResolver;
    std::string result = imagePathResolver.resolve("test.#.png");

    REQUIRE(result == "test.0001.png");
}

TEST_CASE("ImagePathResolver shouldParseImageNumber") {
    ImagePathResolver imagePathResolver;

    SECTION("1001") {
        int frameNumber = imagePathResolver.parseImageNumber("test.1001.png");
        REQUIRE(frameNumber == 1001);
    }

    SECTION("0001") {
        int frameNumber = imagePathResolver.parseImageNumber("test.0001.png");
        REQUIRE(frameNumber == 0001);
    }

    SECTION("0000") {
        int frameNumber = imagePathResolver.parseImageNumber("test.0000.png");
        REQUIRE(frameNumber == 0000);
    }

    SECTION("-1") {
        int frameNumber = imagePathResolver.parseImageNumber("test.png");
        REQUIRE(frameNumber == -1);
    }

}
