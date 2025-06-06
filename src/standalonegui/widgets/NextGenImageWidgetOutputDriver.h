#pragma once
#include "NextGenImageWidget.h"
#include "outputdrivers/NextGenOutputDriver.h"

namespace crayg {

class NextGenImageWidgetOutputDriver : public QObject, public NextGenOutputDriver {
    Q_OBJECT
  public:
    explicit NextGenImageWidgetOutputDriver(NextGenImageWidget &nextGenImageWidget)
        : nextGenImageWidget(nextGenImageWidget) {
        connect(this, &NextGenImageWidgetOutputDriver::initialized, this,
                &NextGenImageWidgetOutputDriver::processInitialize);
        connect(this, &NextGenImageWidgetOutputDriver::bucketStarted, this,
                &NextGenImageWidgetOutputDriver::processBucketStarted);
        connect(this, &NextGenImageWidgetOutputDriver::allChannelsInBucketUpdated, this,
                &NextGenImageWidgetOutputDriver::processAllChannelsInBucketUpdated);
        connect(this, &NextGenImageWidgetOutputDriver::channelInBucketUpdated, this,
                &NextGenImageWidgetOutputDriver::processChannelInBucketUpdated);
        connect(this, &NextGenImageWidgetOutputDriver::bucketFinished, this,
                &NextGenImageWidgetOutputDriver::processBucketFinished);
        connect(this, &NextGenImageWidgetOutputDriver::allChannelsUpdated, this,
                &NextGenImageWidgetOutputDriver::processAllChannelsUpdated);
        connect(this, &NextGenImageWidgetOutputDriver::channelUpdated, this,
                &NextGenImageWidgetOutputDriver::processChannelUpdated);
    }

    void initialize(const FilmSpec &filmSpec) override;
    void startBucket(const ImageBucket &imageBucket) override;
    void updateAllChannelsInBucket(const ImageBucket &imageBucket) override;
    void updateChannelInBucket(const ImageBucket &imageBucket, const std::string &channelName) override;
    void finishBucket(const ImageBucket &imageBucket) override;
    void updateAllChannels() override;
    void updateChannel(const std::string &channelName) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata_) override;

  signals:
    void initialized();
    void bucketStarted(ImageBucket imageBucket);
    void allChannelsInBucketUpdated(ImageBucket imageBucket);
    void channelInBucketUpdated(ImageBucket imageBucket, std::string channelName);
    void bucketFinished(ImageBucket imageBucket);
    void allChannelsUpdated();
    void channelUpdated(std::string channelName);
    void imageMetadataWritten();

  public slots:
    void processInitialize();
    void processBucketStarted(ImageBucket imageBucket);
    void processAllChannelsInBucketUpdated(ImageBucket imageBucket);
    void processChannelInBucketUpdated(ImageBucket imageBucket, std::string channelName);
    void processBucketFinished(ImageBucket imageBucket);
    void processAllChannelsUpdated();
    void processChannelUpdated(std::string channelName);
    void processCurrentChannelChanged(std::string newChannel);

  private:
    std::string currentChannel = "rgb";
    void updateDisplayBuffer();
    void updateDisplayBuffer(const ImageBucket &imageBucket);
    NextGenImageWidget &nextGenImageWidget;
    std::unordered_set<ImageBucket> activeBuckets;
};

}