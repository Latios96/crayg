#pragma once

#include "scene/lights/DiskLight.h"
#include "sceneIO/write/usd/base/BaseUsdLightWriter.h"
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

class UsdDiskLightWriter : public BaseUsdLightWriter<pxr::UsdLuxDiskLight, DiskLight> {
  public:
    UsdDiskLightWriter(DiskLight &craygObject);
    pxr::UsdLuxDiskLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

} // crayg
