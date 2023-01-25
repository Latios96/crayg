#ifndef CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_
#define CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_

#include <image/OutputDriver.h>
#include "ImageWidget.h"

namespace crayg {

class QtSignalAdapter: public QObject{
    Q_OBJECT
 public:
    explicit QtSignalAdapter(QObject *parent= nullptr) : QObject(parent) {}
 public:
    void writeImageMetadata(const ImageMetadata &imageMetadata){
        emit metadataWritten(imageMetadata);
    }
    void prepareBucket(const ImageBucket &imageBucket){
        emit bucketPrepared(imageBucket);
    }
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer){
        auto buf = std::make_shared<BucketImageBuffer>(bucketImageBuffer);
        emit bucketImageBufferWritten(buf);
    }
 signals:
    void metadataWritten(ImageMetadata imageMetadata);
    void bucketPrepared(const ImageBucket imageBucket);
    void bucketImageBufferWritten(std::shared_ptr<BucketImageBuffer> bucketImageBuffer);
};

class ImageWidgetOutputDriver : public OutputDriver {
 public:
    explicit ImageWidgetOutputDriver(ImageWidget &imageWidget);
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;
    QtSignalAdapter qtSignalAdapter;
 private:
    ImageWidget &imageWidget;
};

}

#endif //CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_
