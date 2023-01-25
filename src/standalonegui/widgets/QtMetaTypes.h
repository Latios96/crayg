#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_QTMETATYPES_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_QTMETATYPES_H_

#include <QMetaType>
#include <image/ImageMetadata.h>

Q_DECLARE_METATYPE(crayg::ImageMetadata);
Q_DECLARE_METATYPE(crayg::ImageBucket);
Q_DECLARE_METATYPE(crayg::BucketImageBuffer);
Q_DECLARE_METATYPE(std::shared_ptr<crayg::BucketImageBuffer>);

void registerQMetaTypes(){
    qRegisterMetaType<crayg::ImageMetadata>("ImageMetadata");
    qRegisterMetaType<crayg::ImageBucket>("ImageBucket");
    qRegisterMetaType<crayg::BucketImageBuffer>();
    qRegisterMetaType<std::shared_ptr<crayg::BucketImageBuffer>>("std::shared_ptr<BucketImageBuffer>");
}

#endif //CRAYG_SRC_STANDALONEGUI_WIDGETS_QTMETATYPES_H_
