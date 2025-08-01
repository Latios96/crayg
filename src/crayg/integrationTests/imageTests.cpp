#include "utils.h"
#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageAlgorithms.h>
#include <image/io/ImageWriters.h>
#include <iostream>

namespace crayg {

void createGradientImage(PixelBuffer &pixelBuffer) {
    for (auto pixel : ImageIterators::lineByLine(pixelBuffer)) {
        float grey = static_cast<float>(pixel.x) / static_cast<float>(pixelBuffer.getWidth());
        pixelBuffer.setValue(pixel, Color::createGrey(grey));
    }
}

void createSplittedImage(PixelBuffer &pixelBuffer) {
    for (auto pixel : ImageIterators::lineByLine(pixelBuffer)) {
        if (pixel.y > pixelBuffer.getHeight() / 2) {
            pixelBuffer.setValue(pixel, Color::createBlack());
        } else {
            pixelBuffer.setValue(pixel, Color::createWhite());
        }
    }
}

TEST_CASE("ImageIO/writeRgbExrImage") {
    Image image(1280, 720);
    createGradientImage(image.rgb);

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "writeRgbExrImage", ".exr"));
}

TEST_CASE("ImageIO/writeRgbazExrImage") {
    Image image(1280, 720);
    image.addAlphaChannel();
    image.addDepthChannel();

    createGradientImage(image.rgb);
    createSplittedImage(*image.getAlphaChannel());
    createGradientImage(*image.getDepthChannel());

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "writeRgbazExrImage", ".exr"));
}

TEST_CASE("ImageIO/writeRgbazCustomChannelExrImage") {
    Image image(1280, 720);
    image.addAlphaChannel();
    image.addDepthChannel();
    image.addChannel("position", PixelBuffer::createRgbUInt8(image.getResolution()));

    createGradientImage(image.rgb);
    createSplittedImage(*image.getAlphaChannel());
    createGradientImage(*image.getDepthChannel());
    createSplittedImage(*image.getChannel("position"));

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "writeRgbazCustomChannelExrImage", ".exr"));
}

TEST_CASE("ImageIO/createRgbFloat") {
    Image image(1280, 720);
    image.replaceChannel("rgb", PixelBuffer::createRgbFloat(image.getResolution()));
    createGradientImage(image.rgb);

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "createRgbFloat", ".exr"));
}

TEST_CASE("ImageIO/createGreyFloat") {
    Image image(1280, 720);
    image.replaceChannel("rgb", PixelBuffer::createGreyFloat(image.getResolution()));
    createGradientImage(image.rgb);

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "createGreyFloat", ".exr"));
}

TEST_CASE("ImageIO/createRgbUInt8") {
    Image image(1280, 720);
    image.replaceChannel("rgb", PixelBuffer::createRgbUInt8(image.getResolution()));
    createGradientImage(image.rgb);

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "createRgbUInt8", ".exr"));
}

TEST_CASE("ImageIO/createGreyUInt8") {
    Image image(1280, 720);
    image.replaceChannel("rgb", PixelBuffer::createGreyUInt8(image.getResolution()));
    createGradientImage(image.rgb);

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "createGreyUInt8", ".exr"));
}

TEST_CASE("ImageIO/createVector3f") {
    Image image(1280, 720);
    image.replaceChannel("rgb", PixelBuffer::createVector3f(image.getResolution()));
    createGradientImage(image.rgb);

    ImageWriters::writeImage(image, getOutputFilename("ImageIO", "createVector3f", ".exr"));
}

}