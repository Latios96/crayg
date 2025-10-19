#pragma once

#include "scene/io/write/usd/base/BaseUsdLightWriter.h"
#include "scene/lights/DiskLight.h"
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

class UsdDiskLightWriter : public BaseUsdLightWriter<pxr::UsdLuxDiskLight, DiskLight> {
  public:
    UsdDiskLightWriter(DiskLight &craygObject);
    pxr::UsdLuxDiskLight write(pxr::UsdStagePtr stage, UsdPathFactory &usdPathFactory) override;
};

}
