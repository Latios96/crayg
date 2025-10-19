#include "NextGenOutputDriver.h"

namespace crayg {
void NextGenOutputDriver::initialize(const FilmSpec &filmSpec) {
    film = std::make_unique<Film>(filmSpec.resolution);
    film->addChannelsFromSpec(filmSpec);
}

void NextGenOutputDriver::startTile(const Tile &tile) {
}

void NextGenOutputDriver::updateAllChannelsInTile(const Tile &tile) {
    film->updateAveragesInTile(tile);
}

void NextGenOutputDriver::updateChannelInTile(const Tile &tile, const std::string &channelName) {
    film->updateAveragesForChannelInTile(tile, channelName);
}

void NextGenOutputDriver::finishTile(const Tile &tile) {
    film->updateAveragesInTile(tile);
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