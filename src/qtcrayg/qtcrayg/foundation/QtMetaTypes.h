#pragma once

#include "crayg/foundation/math/geometry/Tile.h"
#include "image/ImageTile.h"
#include "utils/TaskReporter.h"
#include <QMetaType>
#include <image/ImageMetadata.h>
#include <image/ImageSpec.h>

Q_DECLARE_METATYPE(crayg::ImageMetadata);
Q_DECLARE_METATYPE(crayg::Tile);
Q_DECLARE_METATYPE(crayg::ImageTile);
Q_DECLARE_METATYPE(std::shared_ptr<crayg::ImageTile>);
Q_DECLARE_METATYPE(crayg::ImageSpec);
Q_DECLARE_METATYPE(crayg::BaseTaskReporter::Task);
Q_DECLARE_METATYPE(std::string);

void registerQMetaTypes() {
    qRegisterMetaType<crayg::ImageMetadata>("ImageMetadata");
    qRegisterMetaType<crayg::Tile>("Tile");
    qRegisterMetaType<crayg::ImageTile>();
    qRegisterMetaType<std::shared_ptr<crayg::ImageTile>>("std::shared_ptr<ImageTile>");
    qRegisterMetaType<crayg::ImageSpec>("ImageSpec");
    qRegisterMetaType<crayg::BaseTaskReporter::Task>("BaseTaskReporter::Task");
    qRegisterMetaType<std::string>("std::string");
}
