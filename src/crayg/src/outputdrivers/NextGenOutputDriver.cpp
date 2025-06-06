#include "NextGenOutputDriver.h"

namespace crayg {
void NextGenOutputDriver::initialize(const FilmSpec &filmSpec) {
    film = std::make_unique<Film>(filmSpec.resolution);
    film->addChannelsFromSpec(filmSpec);
}

void NextGenOutputDriver::startBucket(const ImageBucket &imageBucket) {
}

void NextGenOutputDriver::updateAllChannelsInBucket(const ImageBucket &imageBucket) {
    film->updateAveragesInBucket(imageBucket);
}

void NextGenOutputDriver::updateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName) {
    film->updateAveragesForChannelInBucket(imageBucket, channelName);
}

void NextGenOutputDriver::finishBucket(const ImageBucket &imageBucket) {
    film->updateAveragesInBucket(imageBucket);
}

void NextGenOutputDriver::updateAllChannels() {
    film->updateAverages();
}

void NextGenOutputDriver::updateChannel(const std::string &channelName) {
    film->updateAveragesForChannel(channelName);
}

void NextGenOutputDriver::updateImageMetadata() {
}

Film &NextGenOutputDriver::getFilm() {
    return *film;
}

}