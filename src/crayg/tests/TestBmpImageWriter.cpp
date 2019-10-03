//
// Created by Jan Honsbrok on 01.11.18.
//

#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/BmpImageWriter.h>

#include <fstream>
#include <iostream>

static const char *const TEST_IMAGE_NAME = "testImageWrite.bmp";

// helper to check if file exists
bool fexists(const char *filename) {
    std::ifstream ifile(filename);
    return (bool) ifile;
}

TEST_CASE("BmpImageWriter") {
    // setup
    Image image(20, 10);
    BmpImageWriter writer;

    if (fexists(TEST_IMAGE_NAME)) {
        REQUIRE(remove(TEST_IMAGE_NAME) == 0);
    }

    SECTION("fileShouldExistAfterWrite") {
        writer.writeImage(image, TEST_IMAGE_NAME);
        REQUIRE(fexists(TEST_IMAGE_NAME));
    }

    // tear down
    if (fexists(TEST_IMAGE_NAME)) {
        REQUIRE(remove(TEST_IMAGE_NAME) == 0);
    }
}