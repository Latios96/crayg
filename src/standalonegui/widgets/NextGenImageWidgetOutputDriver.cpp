#include "NextGenImageWidgetOutputDriver.h"

namespace crayg {

void NextGenImageWidgetOutputDriver::initialize(const FilmSpec &filmSpec) {
    NextGenOutputDriver::initialize(filmSpec);
    emit initialized();
}

void NextGenImageWidgetOutputDriver::startBucket(const ImageBucket &imageBucket) {
    NextGenOutputDriver::startBucket(imageBucket);
    emit bucketStarted(imageBucket);
}

void NextGenImageWidgetOutputDriver::updateAllChannelsInBucket(const ImageBucket &imageBucket) {
    NextGenOutputDriver::updateAllChannelsInBucket(imageBucket);
    emit allChannelsInBucketUpdated(imageBucket);
}

void NextGenImageWidgetOutputDriver::updateChannelInBucket(const ImageBucket &imageBucket,
                                                           const std::string &channelName) {
    NextGenOutputDriver::updateChannelInBucket(imageBucket, channelName);
    emit channelInBucketUpdated(imageBucket, channelName);
}

void NextGenImageWidgetOutputDriver::finishBucket(const ImageBucket &imageBucket) {
    NextGenOutputDriver::finishBucket(imageBucket);
    emit bucketFinished(imageBucket);
}

void NextGenImageWidgetOutputDriver::updateAllChannels() {
    NextGenOutputDriver::updateAllChannels();
    emit allChannelsUpdated();
}

void NextGenImageWidgetOutputDriver::updateChannel(const std::string &channelName) {
    NextGenOutputDriver::updateChannel(channelName);
    emit channelUpdated(channelName);
}

void NextGenImageWidgetOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata_) {
    NextGenOutputDriver::writeImageMetadata(imageMetadata_);
    emit imageMetadataWritten();
}

void NextGenImageWidgetOutputDriver::processInitialize() {
    nextGenImageWidget.initBuffer(film->getResolution());
}

void NextGenImageWidgetOutputDriver::processBucketStarted(ImageBucket imageBucket) {
    activeBuckets.insert(imageBucket);
    FrameBufferDrawUtils::drawBucket(nextGenImageWidget.displayBuffer, imageBucket);
    FrameBufferDrawUtils::drawRegionToRenderIfNeeded(nextGenImageWidget.displayBuffer, film->getRegionToRender());
    nextGenImageWidget.update();
}

void NextGenImageWidgetOutputDriver::processAllChannelsInBucketUpdated(ImageBucket imageBucket) {
    updateDisplayBuffer(imageBucket);
}

void NextGenImageWidgetOutputDriver::processChannelInBucketUpdated(ImageBucket imageBucket, std::string channelName) {
    if (channelName != currentChannel) {
        return;
    }
    updateDisplayBuffer(imageBucket);
}

void NextGenImageWidgetOutputDriver::processBucketFinished(ImageBucket imageBucket) {
    activeBuckets.erase(imageBucket);
    updateDisplayBuffer(imageBucket);
}

void NextGenImageWidgetOutputDriver::processAllChannelsUpdated() {
    updateDisplayBuffer();
}

void NextGenImageWidgetOutputDriver::processChannelUpdated(std::string channelName) {
    if (channelName != currentChannel) {
        return;
    }
    updateDisplayBuffer();
}

inline void NextGenImageWidgetOutputDriver::processCurrentChannelChanged(std::string newChannel) {
    currentChannel = newChannel;
    updateDisplayBuffer();
}

void NextGenImageWidgetOutputDriver::updateDisplayBuffer() {
    Resolution filmResolution = film->getResolution();
    updateDisplayBuffer(ImageBucket({0, 0}, filmResolution.getWidth(), filmResolution.getHeight()));
}

void NextGenImageWidgetOutputDriver::updateDisplayBuffer(const ImageBucket &imageBucket) {
    auto bufferVariantPtr = film->getBufferVariantPtrByName(currentChannel);
    if (!bufferVariantPtr) {
        return;
    }

    for (auto pixel : ImageIterators::lineByLine(imageBucket)) {
        const Vector2i globalPosition = pixel + imageBucket.getPosition();
        Color color =
            std::visit([&globalPosition](auto buf) { return buf->getColor(globalPosition); }, *bufferVariantPtr);
        if (ColorConversion::channelNeedsLinearToSRgbConversion(currentChannel)) {
            color = ColorConversion::linearToSRGB(color);
        }
        const auto rgbValues = color.getRgbValues();
        nextGenImageWidget.displayBuffer.setPixelColor(
            globalPosition.x, globalPosition.y,
            QColor::fromRgb(std::get<0>(rgbValues), std::get<1>(rgbValues), std::get<2>(rgbValues)));
    }

    for (auto &bucket : activeBuckets) {
        FrameBufferDrawUtils::drawBucket(nextGenImageWidget.displayBuffer, bucket);
    }
    FrameBufferDrawUtils::drawRegionToRenderIfNeeded(nextGenImageWidget.displayBuffer, film->getRegionToRender());
    nextGenImageWidget.update();
}

}