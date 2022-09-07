#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRECTLIGHTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRECTLIGHTWRITER_H_

#include "sceneIO/write/usd/BaseUsdLightWriter.h"
#include <pxr/usd/usdLux/rectLight.h>
#include "scene/lights/RectLight.h"

namespace crayg {

class UsdRectLightWriter : public BaseUsdLightWriter<pxr::UsdLuxRectLight, RectLight> {
 public:
    UsdRectLightWriter(const std::shared_ptr<RectLight> &craygObject);

    pxr::UsdLuxRectLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRECTLIGHTWRITER_H_
