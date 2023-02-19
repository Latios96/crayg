#ifndef CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_
#define CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_

#include <QPainter>
#include <QtWidgets/qwidget.h>
#include <basics/Resolution.h>
#include "image/ImageBucket.h"
#include "image/ImageMetadata.h"
#include "image/BucketImageBuffer.h"
#include "image/ImageOutputDriver.h"

namespace crayg {

class ImageWidget : public QWidget {
 Q_OBJECT
    friend class ImageWidgetOutputDriver;
 public:
    explicit ImageWidget(Image &image, QWidget *parent = nullptr);
 protected:
    void paintEvent(QPaintEvent *event) override;
 public slots:
    void initialize(ImageSpec imageSpec);
    void writeMetadata(ImageMetadata imageMetadata);
    void prepareBucket(const ImageBucket imageBucket);
    void writeBucketImageBuffer(std::shared_ptr<BucketImageBuffer> bucketImageBuffer);
    void changeChannel(std::string newChannel);
 private:
    void updateBufferToShow(const ImageBucket &imageBucket);
    std::string currentChannel = "rgb";
    QImage bufferToShow;
    Image &image;
};

}


#endif //CRAYG_SRC_STANDALONEGUI_IMAGEWIDGET_H_
