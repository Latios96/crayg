#include <catch2/catch.hpp>
#include <ImageComparator.h>

static const char *const TEST_IMAGE_WHITE = "test_image_white.png";
static const char *const TEST_IMAGE_BLACK = "test_image_black.png";

namespace knipser {

TEST_CASE("ImageComparator") {

    SECTION("Result should be OK") {
        OpenImageIoImageComparator comparator(TEST_IMAGE_WHITE, TEST_IMAGE_WHITE);
        REQUIRE(comparator.compareImages().isOk());
    }

    SECTION("Result should be ERROR") {
        OpenImageIoImageComparator comparator(TEST_IMAGE_WHITE, TEST_IMAGE_BLACK);
        REQUIRE(comparator.compareImages().isError());
    }
}

}