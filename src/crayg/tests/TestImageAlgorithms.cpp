#include "catch2/catch.hpp"
#include <image/Image.h>
#include <image/ImageAlgorithms.h>
#include <image/ImageBucket.h>

namespace crayg {

TEST_CASE("ImageAlgorithmsBucketIsContainedInImage") {
    Image image(100, 100);

    SECTION("bucketIsContained") {
        REQUIRE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({0, 0}, 10, 10), image));
        REQUIRE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({0, 0}, 100, 100), image));
        REQUIRE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({20, 30}, 40, 50), image));
        REQUIRE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({99, 99}, 1, 1), image));
    }

    SECTION("bucketIsNotContained") {
        REQUIRE_FALSE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({-1, -1}, 10, 10), image));
        REQUIRE_FALSE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({0, 0}, 110, 110), image));
        REQUIRE_FALSE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({90, 80}, 40, 50), image));
        REQUIRE_FALSE(ImageAlgorithms::bucketIsContainedInImage(ImageBucket({99, 99}, 10, 10), image));
    }
}

TEST_CASE("ImageAlgorithmsCopyBucketImageBufferIntoImage") {
    Image image(10, 10);

    SECTION("shouldNotCopyBecauseNotBucketIsNotContained") {
        BucketImageBuffer bucketImageBuffer({0, 0}, 50, 5);

        ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);

        REQUIRE(image.getValue({0, 0}) == Color::createBlack());
        REQUIRE(image.getValue({4, 4}) == Color::createBlack());
        REQUIRE(image.getValue({5, 5}) == Color::createBlack());
        REQUIRE(image.getValue({9, 9}) == Color::createBlack());
    }

    SECTION("shouldCopyCorrectly") {
        BucketImageBuffer bucketImageBuffer({0, 0}, 5, 5);
        ImageAlgorithms::fill(bucketImageBuffer.image, Color::createWhite());

        ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);

        REQUIRE(image.getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getValue({4, 4}) == Color::createWhite());
        REQUIRE(image.getValue({5, 5}) == Color::createBlack());
        REQUIRE(image.getValue({9, 9}) == Color::createBlack());
    }

    SECTION("should copy image channels if they exist in target image") {
        BucketImageBuffer bucketImageBuffer({0, 0}, 5, 5);
        auto specImageBucket = ImageSpecBuilder({5, 5})
                                   .createGreyFloatChannel("channelExistingInTargetImage")
                                   .createGreyUInt8Channel("channelExistingButInOtherFormat")
                                   .createGreyFloatChannel("channelNotExisting")
                                   .finish();
        bucketImageBuffer.image.addChannelsFromSpec(specImageBucket);
        ImageAlgorithms::fill(bucketImageBuffer.image, Color::createWhite());
        ImageAlgorithms::fill(**bucketImageBuffer.image.getChannel("channelExistingInTargetImage"),
                              Color::createWhite());

        ImageAlgorithms::fill(**bucketImageBuffer.image.getChannel("channelNotExisting"), Color::createWhite());
        auto specImage = ImageSpecBuilder({10, 10})
                             .createGreyFloatChannel("channelExistingInTargetImage")
                             .createGreyFloatChannel("untouchedChannel")
                             .finish();
        image.addChannelsFromSpec(specImage);

        ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);

        REQUIRE(image.getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("channelExistingInTargetImage").value()->getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("untouchedChannel").value()->getValue({0, 0}) == Color::createBlack());
    }
}

}