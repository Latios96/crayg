#pragma once
#include "image/ImageMetadata.h"
#include "image/film/Film.h"

namespace crayg {

class NextGenOutputDriver {
  public:
    void initialize(const FilmSpec &filmSpec);
    void startBucket(const ImageBucket &imageBucket);
    void updateAllChannelsInBucket(const ImageBucket &imageBucket);
    void updateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName);
    void finishBucket(const ImageBucket &imageBucket);
    void updateAllChannels();
    void updateChannel(const std::string &channelName);
    void writeImageMetadata(const ImageMetadata &imageMetadata_);
    Film &getFilm();

    virtual void onInitialize();
    virtual void onStartBucket(const ImageBucket &imageBucket);
    virtual void onUpdateAllChannelsInBucket(const ImageBucket &imageBucket);
    virtual void onUpdateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName);
    virtual void onFinishBucket();
    virtual void onUpdateAllChannels();
    virtual void onUpdateChannel(const std::string &channelName);
    virtual void onWriteImageMetadata();

    virtual ~NextGenOutputDriver() = default;

  private:
    std::unique_ptr<Film> film;
    ImageMetadata imageMetadata;
};

}
