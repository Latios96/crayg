//
// Created by jan on 03/10/2019.
//


#include <catch2/catch.hpp>
#include <fstream>
#include <image/Image.h>
#include <image/ImageWriters.h>
#include <boost/filesystem.hpp>

static const char *const TEST_IMAGE_BMP = "ImageWriters_bmp.bmp";
static const char *const TEST_IMAGE_PNG = "ImageWriters_png.png";
static const char *const TEST_IMAGE_UNKNOWN = "ImageWriters_unknown.unknown";

TEST_CASE("ImageWriters") {
    Image image(20, 10);

    SECTION("BMP") {
        if (boost::filesystem::exists(TEST_IMAGE_BMP)) {
            REQUIRE(remove(TEST_IMAGE_BMP) == 0);
        }

        REQUIRE(ImageWriters::writeImage(image, TEST_IMAGE_BMP));
        REQUIRE(boost::filesystem::exists(TEST_IMAGE_BMP));

        if (boost::filesystem::exists(TEST_IMAGE_BMP)) {
            REQUIRE(remove(TEST_IMAGE_BMP) == 0);
        }
    }

    SECTION("unknown") {
        REQUIRE_FALSE(ImageWriters::writeImage(image, TEST_IMAGE_UNKNOWN));
        REQUIRE_FALSE(boost::filesystem::exists(TEST_IMAGE_UNKNOWN));
    }
}