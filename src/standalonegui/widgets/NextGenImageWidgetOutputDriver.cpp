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
}

void NextGenImageWidgetOutputDriver::updateChannelInBucket(const ImageBucket &imageBucket,
                                                           const std::string &channelName) {
    NextGenOutputDriver::updateChannelInBucket(imageBucket, channelName);
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
    // todo drawBucket(bufferToShow, imageBucket);
    // todo drawRegionToRenderIfNeeded(bufferToShow, regionToRender);
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

void NextGenImageWidgetOutputDriver::updateDisplayBuffer() {
    Resolution filmResolution = film->getResolution();
    updateDisplayBuffer(ImageBucket({0, 0}, filmResolution.getWidth(), filmResolution.getHeight()));
}

void NextGenImageWidgetOutputDriver::updateDisplayBuffer(const ImageBucket &imageBucket) {
    // get current channel
    // copy current channel within display bounds to display buffer, convert colors if needed
    // draw buckets
    // draw regionToRender if needed
    // call update() on NextGenImageWidget
}

}