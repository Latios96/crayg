#include <boost/filesystem.hpp>
#include <catch2/catch.hpp>
#include <fstream>
#include <image/Image.h>
#include <image/ImageWriters.h>

namespace crayg {

static const char *const TEST_IMAGE_EXR = "ImageWriters_exr.exr";
static const char *const TEST_IMAGE_PNG = "ImageWriters_png.png";
static const char *const TEST_IMAGE_UNKNOWN = "ImageWriters_unknown.unknown";

TEST_CASE("ImageWriters/ImageWriterType") {
    Image image(20, 10);

    SECTION("PNG") {
        if (boost::filesystem::exists(TEST_IMAGE_PNG)) {
            REQUIRE(remove(TEST_IMAGE_PNG) == 0);
        }

        REQUIRE(ImageWriters::writeImage(image, TEST_IMAGE_PNG));
        REQUIRE(boost::filesystem::exists(TEST_IMAGE_PNG));

        if (boost::filesystem::exists(TEST_IMAGE_PNG)) {
            REQUIRE(remove(TEST_IMAGE_PNG) == 0);
        }
    }

    SECTION("EXR") {
        if (boost::filesystem::exists(TEST_IMAGE_EXR)) {
            REQUIRE(remove(TEST_IMAGE_EXR) == 0);
        }

        REQUIRE(ImageWriters::writeImage(image, TEST_IMAGE_EXR));
        REQUIRE(boost::filesystem::exists(TEST_IMAGE_EXR));

        if (boost::filesystem::exists(TEST_IMAGE_EXR)) {
            REQUIRE(remove(TEST_IMAGE_EXR) == 0);
        }
    }

    SECTION("unknown") {
        REQUIRE_THROWS_AS(ImageWriters::writeImage(image, TEST_IMAGE_UNKNOWN), std::runtime_error);
        REQUIRE_FALSE(boost::filesystem::exists(TEST_IMAGE_UNKNOWN));
    }
}

}
