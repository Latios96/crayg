#include "catch2/catch.hpp"
#include "crayg/foundation/math/geometry/Tile.h"
#include "image/Image.h"
#include "image/ImageAlgorithms.h"

namespace crayg {

TEST_CASE("ImageAlgorithmsTileIsContainedInImage") {
    Image image(100, 100);

    SECTION("tileIsContained") {
        REQUIRE(ImageAlgorithms::tileIsContainedInImage(Tile({0, 0}, 10, 10), image));
        REQUIRE(ImageAlgorithms::tileIsContainedInImage(Tile({0, 0}, 100, 100), image));
        REQUIRE(ImageAlgorithms::tileIsContainedInImage(Tile({20, 30}, 40, 50), image));
        REQUIRE(ImageAlgorithms::tileIsContainedInImage(Tile({99, 99}, 1, 1), image));
    }

    SECTION("tileIsNotContained") {
        REQUIRE_FALSE(ImageAlgorithms::tileIsContainedInImage(Tile({-1, -1}, 10, 10), image));
        REQUIRE_FALSE(ImageAlgorithms::tileIsContainedInImage(Tile({0, 0}, 110, 110), image));
        REQUIRE_FALSE(ImageAlgorithms::tileIsContainedInImage(Tile({90, 80}, 40, 50), image));
        REQUIRE_FALSE(ImageAlgorithms::tileIsContainedInImage(Tile({99, 99}, 10, 10), image));
    }
}

TEST_CASE("ImageAlgorithmsCopyTileImageBufferIntoImage") {
    Image image(10, 10);

    SECTION("shouldNotCopyBecauseNotTileIsNotContained") {
        ImageTile imageTile({0, 0}, 50, 5);

        ImageAlgorithms::copyTileImageBufferIntoImage(imageTile, image);

        REQUIRE(image.getValue({0, 0}) == Color::createBlack());
        REQUIRE(image.getValue({4, 4}) == Color::createBlack());
        REQUIRE(image.getValue({5, 5}) == Color::createBlack());
        REQUIRE(image.getValue({9, 9}) == Color::createBlack());
    }

    SECTION("shouldCopyCorrectly") {
        ImageTile imageTile({0, 0}, 5, 5);
        ImageAlgorithms::fill(imageTile.image, Color::createWhite());

        ImageAlgorithms::copyTileImageBufferIntoImage(imageTile, image);

        REQUIRE(image.getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getValue({4, 4}) == Color::createWhite());
        REQUIRE(image.getValue({5, 5}) == Color::createBlack());
        REQUIRE(image.getValue({9, 9}) == Color::createBlack());
    }

    SECTION("should copy image channels if they exist in target image") {
        ImageTile imageTile({0, 0}, 5, 5);
        auto specImageTile = ImageSpecBuilder({5, 5})
                                 .createGreyFloatChannel("channelExistingInTargetImage")
                                 .createGreyUInt8Channel("channelExistingButInOtherFormat")
                                 .createGreyFloatChannel("channelNotExisting")
                                 .finish();
        imageTile.image.addChannelsFromSpec(specImageTile);
        ImageAlgorithms::fill(imageTile.image, Color::createWhite());
        ImageAlgorithms::fill(*imageTile.image.getChannel("channelExistingInTargetImage"), Color::createWhite());

        ImageAlgorithms::fill(*imageTile.image.getChannel("channelNotExisting"), Color::createWhite());
        auto specImage = ImageSpecBuilder({10, 10})
                             .createGreyFloatChannel("channelExistingInTargetImage")
                             .createGreyFloatChannel("untouchedChannel")
                             .finish();
        image.addChannelsFromSpec(specImage);

        ImageAlgorithms::copyTileImageBufferIntoImage(imageTile, image);

        REQUIRE(image.getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("channelExistingInTargetImage")->getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("untouchedChannel")->getValue({0, 0}) == Color::createBlack());
    }

    SECTION("should copy image channel that are in update list") {
        ImageTile tileImageBuffer({0, 0}, 5, 5);
        auto specImageTile = ImageSpecBuilder({5, 5})
                                 .createGreyFloatChannel("updatedChannel")
                                 .createGreyFloatChannel("untouchedChannel")
                                 .finish();
        tileImageBuffer.image.addChannelsFromSpec(specImageTile);
        ImageAlgorithms::fill(tileImageBuffer.image, Color::createWhite());
        ImageAlgorithms::fill(*tileImageBuffer.image.getChannel("updatedChannel"), Color::createWhite());

        auto specImage = ImageSpecBuilder({10, 10})
                             .createGreyFloatChannel("updatedChannel")
                             .createGreyFloatChannel("untouchedChannel")
                             .finish();
        image.addChannelsFromSpec(specImage);

        ImageAlgorithms::copyTileImageBufferIntoImage(tileImageBuffer, image, {"updatedChannel"});

        REQUIRE(image.getValue({0, 0}) == Color::createBlack());
        REQUIRE(image.getChannel("updatedChannel")->getValue({0, 0}) == Color::createWhite());
        REQUIRE(image.getChannel("untouchedChannel")->getValue({0, 0}) == Color::createBlack());
    }
}

TEST_CASE("ImageAlgorithms::updateChannel") {
    Image imageToUpdate(10, 10);

    SECTION("should not update because channel does not exist") {
        auto pixelBuffer = PixelBuffer::createGreyFloat(imageToUpdate.getResolution());

        ImageAlgorithms::updateChannel(imageToUpdate, "channelToUpdate", pixelBuffer.get());

        REQUIRE(imageToUpdate.getValue({0, 0}) == Color::createBlack());
    }

    SECTION("should update channel") {
        auto pixelBuffer = PixelBuffer::createGreyFloat(imageToUpdate.getResolution());
        ImageAlgorithms::fill(*pixelBuffer, Color::createWhite());
        imageToUpdate.addChannel("channelToUpdate", PixelBuffer::createGreyFloat(imageToUpdate.getResolution()));

        ImageAlgorithms::updateChannel(imageToUpdate, "channelToUpdate", pixelBuffer.get());

        REQUIRE(imageToUpdate.getChannel("channelToUpdate")->getValue({0, 0}) == Color::createWhite());
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

        REQUIRE(minValue == Color::createGrey(0.1f));
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

TEST_CASE("ImageAlgorithms::fill Image Tile") {
    SECTION("should fill tile") {
        Image image(10, 10);
        Tile region({5, 5}, 2, 2);

        ImageAlgorithms::fill(image, Color::createWhite(), region);

        REQUIRE(image.getValue({4, 4}) == Color::createBlack());
        REQUIRE(image.getValue({5, 5}) == Color::createWhite());
        REQUIRE(image.getValue({7, 5}) == Color::createBlack());
    }
}
}