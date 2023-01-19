#ifndef CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_
#define CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_

#include <image/OutputDriver.h>
#include "ImageWidget.h"

namespace crayg {

class ImageWidgetOutputDriver : public OutputDriver {
 public:
    explicit ImageWidgetOutputDriver(ImageWidget &imageWidget);
    void prepareBucket(const ImageBucket &imageBucket) override;
    void writeBucketImageBuffer(const BucketImageBuffer &bucketImageBuffer) override;
    void writeImageMetadata(const ImageMetadata &imageMetadata) override;
 private:
    ImageWidget &imageWidget;
};

}

#endif //CRAYG_SRC_STANDALONEGUI_IMAGEWIDGETOUTPUTDRIVER_H_
