#include "ImageOutputDriver.h"
#include "ImageAlgorithms.h"
#include "ImageMetadata.h"

namespace crayg {

void ImageOutputDriver::initialize(const ImageSpec &imageSpec) {
    const ImageSpec specOfProvidedImage = image.getImageSpec();
    if (specOfProvidedImage != imageSpec) {
        throw std::runtime_error(fmt::format("Image spec does not match! Required was {}, provided was {}", imageSpec,
                                             specOfProvidedImage));
    }
}

void ImageOutputDriver::prepareBucket(const ImageBucket &imageBucket) {

}
void ImageOutputDriver::writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) {
    ImageAlgorithms::copyBucketImageBufferIntoImage(bucketImageBuffer, image);
}
ImageOutputDriver::ImageOutputDriver(Image &image) : image(image) {}

void ImageOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata) {
    image.metadata = imageMetadata;
}
ImageOutputDriver::~ImageOutputDriver() = default;

}