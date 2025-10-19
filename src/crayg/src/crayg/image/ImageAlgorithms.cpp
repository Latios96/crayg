#include "ImageAlgorithms.h"

namespace crayg {

void ImageAlgorithms::copyTileImageBufferIntoImage(const ImageTile &imageTile, Image &image) {
    copyTileImageBufferIntoImage(imageTile, image, imageTile.image.channelNames());
}

void ImageAlgorithms::copyTileImageBufferIntoImage(const ImageTile &imageTile, Image &image,
                                                   const std::vector<std::string> &channelsToUpdate) {
    const bool isContained = tileIsContainedInImage(imageTile.tile, image);

    if (!isContained) {
        return;
    }
    for (const auto &channelName : channelsToUpdate) {
        if (!image.hasChannel(channelName)) {
            continue;
        }
        auto imageChannel = image.getChannel(channelName);
        auto tileImageBufferChannel = imageTile.image.getChannel(channelName);
        for (auto pixel : AreaIterators::scanlines(*tileImageBufferChannel)) {
            imageChannel->setValue(pixel + imageTile.tile.getPosition(), tileImageBufferChannel->getValue(pixel));
        }
    }
}

void ImageAlgorithms::updateChannel(Image &image, const std::string &channelName, PixelBuffer *pixelBuffer) {
    if (!image.hasChannel(channelName)) {
        return;
    }

    auto imageChannel = image.getChannel(channelName);

    for (auto pixel : AreaIterators::scanlines(*pixelBuffer)) {
        imageChannel->setValue(pixel, pixelBuffer->getValue(pixel));
    }
}

}
