//
// Created by jan on 03/10/2019.
//

#include <image/Image.h>
#include <image/ImageWriters.h>
#include "KnipserApp.h"
#include <KnipserAssertions.h>
#include <image/ImageOutputDriver.h>
#include <image/ImageAlgorithms.h>

void createGradientImage(Image &image) {
    for (auto pixel : ImageIterators::lineByLine(image)) {
        float grey = static_cast<float>(pixel.x) / static_cast<float>(image.getWidth());
        image.setValue(pixel.x, pixel.y, Color::createGrey(grey));
    }
}

void writeAndCheckTestImage(TestContext &context, std::string imageOutputName) {
    context.setImageOutputName(imageOutputName);
    Image image(1280, 720);
    createGradientImage(image);

    ImageWriters::writeImage(image, context.getOutputFilename());

    ASSERT_IMAGES_ARE_EQUAL(context);
};

KNIPSER_REGISTER_TEST(writeBmpImage, [](TestContext &context) {
    writeAndCheckTestImage(context, "bmpTestImage.bmp");
})

void writeAndCheckTestImage();
KNIPSER_REGISTER_TEST(writePngImage, [](TestContext &context) {
    writeAndCheckTestImage(context, "pngTestImage.png");
});

KNIPSER_REGISTER_TEST(writeToImageOutputDriver, [](TestContext &context) {
    context.setImageOutputName("writeToImageOutputDriver.png");

    Image image(1000, 500);
    ImageOutputDriver imageOutputDriver(image);

    for (int x = 0; x < 1000; x += 50) {
        for (int y = 0; y < 500; y += 50) {
            BucketImageBuffer bucketImageBuffer(x, y, 25, 25);
            ImageAlgorithms::fill(bucketImageBuffer.image, Color::createGrey(x));

            imageOutputDriver.prepareBucket(bucketImageBuffer.imageBucket);
            imageOutputDriver.writeBucketImageBuffer(bucketImageBuffer);
        }
    }

    ImageWriters::writeImage(image, context.getOutputFilename());

    ASSERT_IMAGES_ARE_EQUAL(context);
})

