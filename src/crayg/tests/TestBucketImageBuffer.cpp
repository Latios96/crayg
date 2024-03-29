#include "catch2/catch.hpp"
#include <image/BucketImageBuffer.h>

namespace crayg {

struct ImageWrapper {
    Image image;
};

TEST_CASE("BucketImageBuffer") {

    SECTION("shouldConstructCorrectly") {
        BucketImageBuffer bucketImageBuffer({0, 1}, 20, 30);

        REQUIRE(bucketImageBuffer.imageBucket.getPosition() == Vector2i(0, 1));
        REQUIRE(bucketImageBuffer.imageBucket.getWidth() == 20);
        REQUIRE(bucketImageBuffer.imageBucket.getHeight() == 30);
        REQUIRE(bucketImageBuffer.image.getWidth() == 20);
        REQUIRE(bucketImageBuffer.image.getHeight() == 30);
    }
}

}
