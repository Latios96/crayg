#pragma once
#include "image/ImageMetadata.h"
#include "image/film/Film.h"

namespace crayg {

class NextGenOutputDriver {
  public:
    virtual void initialize(const FilmSpec &filmSpec);
    virtual void startBucket(const ImageBucket &imageBucket);
    virtual void updateAllChannelsInBucket(const ImageBucket &imageBucket);
    virtual void updateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName);
    virtual void finishBucket(const ImageBucket &imageBucket);
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
