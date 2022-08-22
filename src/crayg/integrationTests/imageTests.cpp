#include "utils.h"
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <catch2/catch.hpp>
#include <image/Image.h>
#include <image/ImageAlgorithms.h>
#include <image/ImageOutputDriver.h>
#include <image/ImageWriters.h>
#include <iostream>

namespace crayg {

void createGradientImage(Image &image) {
  for (auto pixel : ImageIterators::lineByLine(image)) {
    float grey =
        static_cast<float>(pixel.x) / static_cast<float>(image.getWidth());
    image.setValue(pixel.x, pixel.y, Color::createGrey(grey));
  }
}

TEST_CASE("ImageIO/writeBmpImage") {
  Image image(1280, 720);
  createGradientImage(image);

  ImageWriters::writeImage(image,
                           getOutputFilename("ImageIO", "writeBmpImage"));
}
TEST_CASE("ImageIO/writeExrImage") {
  Image image(1280, 720);
  createGradientImage(image);

  std::cout << "write to "
            << getOutputFilename("ImageIO", "writeExrImage", ".exr")
            << std::endl;
  ImageWriters::writeImage(
      image, getOutputFilename("ImageIO", "writeExrImage", ".exr"));
}

TEST_CASE("ImageIO/writeToImageOutputDriver") {
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

  ImageWriters::writeImage(
      image, getOutputFilename("ImageIO", "writeToImageOutputDriver", ".exr"));
}

}