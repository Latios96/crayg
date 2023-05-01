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
        ImageAlgorithms::fill(*bucketImageBuffer.image.getChannel("channelExistingInTargetImage"),
                              Color::createWhite());

        ImageAlgorithms::fill(*bucketImageBuffer.image.getChannel("channelNotExisting"), Color::createWhite());
        auto specImage = ImageSpecBuilder({10, 10})
                             .createGreyFloatChannel("channelExistingInTargetImage")
                             .createGreyFloatChannel("untouchedChannel")
                             .finish();
        image.addChannelsFromSpec(specImage);

        ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);

        REQUIRE(image.getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("channelExistingInTargetImage")->getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("untouchedChannel")->getValue({0, 0}) == Color::createBlack());
    }
}

TEST_CASE("ImageAlgorithms::minValue") {
    SECTION("should find black as min color") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createBlack());
        image.setValue({1, 0}, Color::createGrey(0.2f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createWhite());

        auto minValue = ImageAlgorithms::minValue(image);

        REQUIRE(minValue == Color::createBlack());
    }

    SECTION("should find black as min color") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createGrey(0.1f));
        image.setValue({1, 0}, Color::createGrey(0.2f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createWhite());

        auto minValue = ImageAlgorithms::minValue(image);

        REQUIRE(minValue == Color::createGrey(0.1));
    }
}

TEST_CASE("ImageAlgorithms::maxValue") {
    SECTION("should find white as max color") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createBlack());
        image.setValue({1, 0}, Color::createGrey(0.2f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createWhite());

        auto minValue = ImageAlgorithms::maxValue(image);

        REQUIRE(minValue == Color::createWhite());
    }

    SECTION("should find 0.6 as max color") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createBlack());
        image.setValue({1, 0}, Color::createGrey(0.2f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createGrey(0.3f));

        auto minValue = ImageAlgorithms::maxValue(image);

        REQUIRE(minValue == Color::createGrey(0.6f));
    }
}

TEST_CASE("ImageAlgorithms::fillWithRelativeGradient") {
    SECTION("should fill with relative gradient in range 0-1") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createBlack());
        image.setValue({1, 0}, Color::createGrey(0.2f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createGrey(0.3f));
        Gradient<Color> gradient({Color::createBlack(), Color::createGrey(0.5f)});

        ImageAlgorithms::fillWithRelativeGradient(image, image, gradient, Color::createBlack(), Color::createWhite());

        REQUIRE(image.getValue({0, 0}) == Color::createGrey(0.0f));
        REQUIRE(image.getValue({1, 0}) == Color::createGrey(0.1f));
        REQUIRE(image.getValue({0, 1}) == Color::createGrey(0.3f));
        REQUIRE(image.getValue({1, 1}) == Color::createGrey(0.15f));
    }

    SECTION("should fill with relative gradient in range 0-0.5") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createBlack());
        image.setValue({1, 0}, Color::createGrey(0.1f));
        image.setValue({0, 1}, Color::createGrey(0.3f));
        image.setValue({1, 1}, Color::createGrey(0.15f));
        Gradient<Color> gradient({Color::createBlack(), Color::createGrey(0.5f)});

        ImageAlgorithms::fillWithRelativeGradient(image, image, gradient, Color::createBlack(),
                                                  Color::createGrey(0.5f));

        REQUIRE(image.getValue({0, 0}) == Color::createGrey(0.0f));
        REQUIRE(image.getValue({1, 0}) == Color::createGrey(0.1f));
        REQUIRE(image.getValue({0, 1}) == Color::createGrey(0.3f));
        REQUIRE(image.getValue({1, 1}) == Color::createGrey(0.15f));
    }

    SECTION("should fill with relative gradient in range 0.1-0.9") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createGrey(0.1f));
        image.setValue({1, 0}, Color::createGrey(0.3f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createGrey(0.9f));
        Gradient<Color> gradient({Color::createBlack(), Color::createGrey(1)});

        ImageAlgorithms::fillWithRelativeGradient(image, image, gradient, Color::createGrey(0.1f),
                                                  Color::createGrey(0.9f));

        REQUIRE(image.getValue({0, 0}) == Color::createBlack());
        REQUIRE(image.getValue({1, 0}) == Color::createGrey(0.25000003f));
        REQUIRE(image.getValue({0, 1}) == Color::createGrey(0.62500006f));
        REQUIRE(image.getValue({1, 1}) == Color::createWhite());
    }

    SECTION("should fill with relative gradient in range 0.1-0.9, clamping required") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createGrey(0.0f));
        image.setValue({1, 0}, Color::createGrey(0.3f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createGrey(0.9f));
        Gradient<Color> gradient({Color::createBlack(), Color::createGrey(1)});

        ImageAlgorithms::fillWithRelativeGradient(image, image, gradient, Color::createGrey(0.1f),
                                                  Color::createGrey(0.9f));

        REQUIRE(image.getValue({0, 0}) == Color::createBlack());
        REQUIRE(image.getValue({1, 0}) == Color::createGrey(0.25000003f));
        REQUIRE(image.getValue({0, 1}) == Color::createGrey(0.62500006f));
        REQUIRE(image.getValue({1, 1}) == Color::createWhite());
    }

    SECTION("should fill with relative gradient with min/max found in image") {
        Image image(2, 2);
        image.setValue({0, 0}, Color::createGrey(0.3f));
        image.setValue({1, 0}, Color::createGrey(0.3f));
        image.setValue({0, 1}, Color::createGrey(0.6f));
        image.setValue({1, 1}, Color::createGrey(0.6f));
        Gradient<Color> gradient({Color::createBlack(), Color::createGrey(1)});

        ImageAlgorithms::fillWithRelativeGradient(image, image, gradient);

        REQUIRE(image.getValue({0, 0}) == Color::createBlack());
        REQUIRE(image.getValue({1, 0}) == Color::createBlack());
        REQUIRE(image.getValue({0, 1}) == Color::createWhite());
        REQUIRE(image.getValue({1, 1}) == Color::createWhite());
    }
}

}