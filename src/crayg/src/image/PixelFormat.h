#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELFORMAT_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELFORMAT_H_

#include "utils/EnumUtils.h"

namespace crayg {

enum class PixelFormat { FLOAT, UINT8 };

}

CRAYG_FMT_ENUM_FORMATTER(crayg::PixelFormat);

#endif // CRAYG_SRC_CRAYG_SRC_IMAGE_PIXELFORMAT_H_
