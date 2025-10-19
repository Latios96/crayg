#pragma once
#include "crayg/image/ImageMetadata.h"
#include "crayg/image/film/Film.h"

namespace crayg {

class NextGenOutputDriver {
  public:
    virtual void initialize(const FilmSpec &filmSpec);
    virtual void startTile(const Tile &tile);
    virtual void updateAllChannelsInTile(const Tile &tile);
    virtual void updateChannelInTile(const Tile &tile, const std::string &channelName);
    virtual void finishTile(const Tile &tile);
    virtual void updateAllChannels();
    virtual void updateChannel(const std::string &channelName);
    virtual void updateImageMetadata();

    Film &getFilm();

    virtual ~NextGenOutputDriver() = default;

  protected:
    std::unique_ptr<Film> film;
    ImageMetadata imageMetadata;
};

}
