//
// Created by Jan on 29.10.2020.
//

#include "BucketImageBuffer.h"

namespace crayg {

BucketImageBuffer::BucketImageBuffer(int x, int y, int width, int height) : image(Image(width, height)),
                                                                            imageBucket(ImageBucket(x,
                                                                                                    y,
                                                                                                    width,
                                                                                                    height)) {}
BucketImageBuffer::BucketImageBuffer(const ImageBucket &imageBucket)
    : imageBucket(imageBucket), image(Image(imageBucket.getWidth(), imageBucket.getHeight())) {

}

}
