#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDDISKLIGHTWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDDISKLIGHTWRITER_H_

#include "scene/lights/DiskLight.h"
#include "BaseUsdLightWriter.h"
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

class UsdDiskLightWriter : public BaseUsdLightWriter<pxr::UsdLuxDiskLight, DiskLight> {
 public:
    UsdDiskLightWriter(DiskLight &craygObject);
    pxr::UsdLuxDiskLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDDISKLIGHTWRITER_H_
