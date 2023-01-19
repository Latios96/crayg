#ifndef CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_
#define CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_

#include <image/OutputDriver.h>
#include "ImageWidget.h"

namespace crayg {

class ImageMetadataChanger: public QObject{
    Q_OBJECT
 public:
    explicit ImageMetadataChanger(QObject *parent= nullptr) : QObject(parent) {}
 public:
    void change(const ImageMetadata &imageMetadata){
        emit changed(imageMetadata);
    }
 signals:
    void changed(ImageMetadata imageMetadata);
};

class ImageWidgetOutputDriver : public OutputDriver {
 public:
    explicit ImageWidgetOutputDriver(ImageWidget &imageWidget);
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;
    ImageMetadataChanger imageMetadataChanger;
 private:
    ImageWidget &imageWidget;
};

}

#endif //CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_
