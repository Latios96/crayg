#include "NextGenOutputDriver.h"

namespace crayg {
void NextGenOutputDriver::initialize(const FilmSpec &filmSpec) {
    film = std::make_unique<Film>(filmSpec.resolution);
    film->addChannelsFromSpec(filmSpec);
    onInitialize();
}

void NextGenOutputDriver::startBucket(const ImageBucket &imageBucket) {
    onStartBucket(imageBucket);
}

void NextGenOutputDriver::updateAllChannelsInBucket(const ImageBucket &imageBucket) {
    film->updateAveragesInBucket(imageBucket);
    onUpdateAllChannelsInBucket(imageBucket);
}

void NextGenOutputDriver::updateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName) {
    film->updateAveragesForChannelInBucket(imageBucket, channelName);
    onUpdateChannelInBucket(imageBucket, channelName);
}

void NextGenOutputDriver::finishBucket(const ImageBucket &imageBucket) {
    film->updateAveragesInBucket(imageBucket);
    onFinishBucket();
}

void NextGenOutputDriver::updateAllChannels() {
    film->updateAverages();
    onUpdateAllChannels();
}

void NextGenOutputDriver::updateChannel(const std::string &channelName) {
    film->updateAveragesForChannel(channelName);
    onUpdateChannel(channelName);
}

void NextGenOutputDriver::writeImageMetadata(const ImageMetadata &imageMetadata_) {
    this->imageMetadata = imageMetadata_;
    onWriteImageMetadata();
}

Film &NextGenOutputDriver::getFilm() {
    return *film;
}

void NextGenOutputDriver::onInitialize() {
}

void NextGenOutputDriver::onStartBucket(const ImageBucket &imageBucket) {
}

void NextGenOutputDriver::onUpdateAllChannelsInBucket(const ImageBucket &imageBucket) {
}

void NextGenOutputDriver::onUpdateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName) {
}

void NextGenOutputDriver::onFinishBucket() {
}

void NextGenOutputDriver::onUpdateAllChannels() {
}

void NextGenOutputDriver::onUpdateChannel(const std::string &channelName) {
}

void NextGenOutputDriver::onWriteImageMetadata() {
}
}