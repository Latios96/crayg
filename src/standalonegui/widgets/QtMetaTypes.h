#ifndef CRAYG_SRC_STANDALONEGUI_WIDGETS_QTMETATYPES_H_
#define CRAYG_SRC_STANDALONEGUI_WIDGETS_QTMETATYPES_H_

#include <QMetaType>
#include <image/ImageMetadata.h>

Q_DECLARE_METATYPE(crayg::ImageMetadata);

void registerQMetaTypes(){
    qRegisterMetaType<crayg::ImageMetadata>("ImageMetadata");
}

#endif //CRAYG_SRC_STANDALONEGUI_WIDGETS_QTMETATYPES_H_
