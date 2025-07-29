#pragma once

#include "image/BucketImageBuffer.h"
#include "image/ImageBucket.h"
#include "utils/TaskReporter.h"
#include <QMetaType>
#include <image/ImageMetadata.h>
#include <image/ImageSpec.h>

Q_DECLARE_METATYPE(crayg::ImageMetadata);
Q_DECLARE_METATYPE(crayg::ImageBucket);
Q_DECLARE_METATYPE(crayg::BucketImageBuffer);
Q_DECLARE_METATYPE(std::shared_ptr<crayg::BucketImageBuffer>);
Q_DECLARE_METATYPE(crayg::ImageSpec);
Q_DECLARE_METATYPE(crayg::BaseTaskReporter::Task);
Q_DECLARE_METATYPE(std::string);

void registerQMetaTypes() {
    qRegisterMetaType<crayg::ImageMetadata>("ImageMetadata");
    qRegisterMetaType<crayg::ImageBucket>("ImageBucket");
    qRegisterMetaType<crayg::BucketImageBuffer>();
    qRegisterMetaType<std::shared_ptr<crayg::BucketImageBuffer>>("std::shared_ptr<BucketImageBuffer>");
    qRegisterMetaType<crayg::ImageSpec>("ImageSpec");
    qRegisterMetaType<crayg::BaseTaskReporter::Task>("BaseTaskReporter::Task");
    qRegisterMetaType<std::string>("std::string");
}
