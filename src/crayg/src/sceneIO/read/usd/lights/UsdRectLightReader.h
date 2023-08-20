#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRECTLIGHTREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRECTLIGHTREADER_H_

#include "scene/lights/RectLight.h"
#include "sceneIO/read/usd/base/BaseUsdLightReader.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdLux/rectLight.h>

namespace crayg {

class UsdRectLightReader : public BaseUsdLightReader<pxr::UsdLuxRectLight, RectLight> {
  public:
    UsdRectLightReader(const pxr::UsdLuxRectLight &rectLight);
    std::shared_ptr<RectLight> read() override;

  protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRECTLIGHTREADER_H_
