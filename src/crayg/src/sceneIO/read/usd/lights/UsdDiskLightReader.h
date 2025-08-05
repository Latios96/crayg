#pragma once

#include "scene/lights/DiskLight.h"
#include "sceneIO/read/usd/base/BaseUsdLightReader.h"
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

class UsdDiskLightReader : public BaseUsdLightReader<pxr::UsdLuxDiskLight, DiskLight> {
  public:
    UsdDiskLightReader(const pxr::UsdLuxDiskLight &diskLight);
    std::shared_ptr<DiskLight> read() override;

  protected:
    std::string getTranslatedType() override;
};

}
