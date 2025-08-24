#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageAlgorithms.h>
#include <outputdrivers/ImageOutputDriver.h>

namespace crayg {

TEST_CASE("ImageOutputDriver") {
    Image image(200, 200);
    ImageOutputDriver imageOutputDriver(image);

    SECTION("shouldWriteTile") {
        TileImageBuffer tileImageBuffer({0, 0}, 30, 30);
        ImageAlgorithms::fill(tileImageBuffer.image, Color::createWhite());

        imageOutputDriver.prepareTile(tileImageBuffer.imageTile);
        imageOutputDriver.writeTileImageBuffer(tileImageBuffer);

        REQUIRE(image.getValue({10, 10}) == Color::createWhite());
    }

    SECTION("should write metadata") {
        ImageMetadata imageMetadata;
        imageMetadata.write("testValue", 42);

        imageOutputDriver.writeImageMetadata(imageMetadata);

        REQUIRE(image.metadata == imageMetadata);
    }
}

}