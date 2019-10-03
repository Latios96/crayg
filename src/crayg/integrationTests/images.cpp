//
// Created by jan on 03/10/2019.
//

#include <image/Image.h>
#include <image/ImageIterators.h>
#include <image/ImageWriters.h>
#include "KnipserApp.h"
#include <KnipserAssertions.h>

void createGradientImage(Image &image){
    for(auto pixel : ImageIterators::lineByLine(image)){
        float grey = static_cast<float>(pixel.x) / static_cast<float>(image.getWidth());
        image.setValue(pixel.x, pixel.y, Color::createGrey(grey));
    }
}

void writeAndCheckTestImage(TestContext &context, std::string imageOutputName) {
    context.setImageOutputName(imageOutputName);
    Image image(1280,720);
    createGradientImage(image);

    ImageWriters::writeImage(image, context.getOutputFilename());

    ASSERT_IMAGES_ARE_EQUAL(context);
};

KNIPSER_REGISTER_TEST(writeBmpImage, [](TestContext &context){
    writeAndCheckTestImage(context, "bmpTestImage.bmp");
})


void writeAndCheckTestImage();
KNIPSER_REGISTER_TEST(writePngImage, [](TestContext &context){
    writeAndCheckTestImage(context, "pngTestImage.png");
});