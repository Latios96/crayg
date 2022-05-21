//
// Created by Jan on 19.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRECTLIGHTTRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRECTLIGHTTRANSLATOR_H_

#include "CraygUsdBase.h"
#include "scene/RectLight.h"
#include <pxr/usd/usdLux/rectLight.h>

namespace crayg {

class UsdRectLightTranslator {
 public:
    UsdRectLightTranslator(const pxr::UsdLuxRectLight &rectLight);
    std::shared_ptr<RectLight> translate();
 private:
    pxr::UsdLuxRectLight rectLight;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRECTLIGHTTRANSLATOR_H_
