#ifndef CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGESPEC_H_
#define CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGESPEC_H_

#include <vector>
#include "basics/Resolution.h"
#include "PixelFormat.h"
#include "utils/DtoUtils.h"

namespace crayg {

CRAYG_DTO_3(ChannelSpec, std::string, name, PixelFormat, pixelFormat, int, colorChannelCount) ;

CRAYG_DTO_2(ImageSpec, Resolution, resolution, std::vector<ChannelSpec>, channels) ;

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_IMAGE_IMAGESPEC_H_
