#pragma once

#include "crayg/scene/io/read/usd/base/BaseUsdLightReader.h"
#include "crayg/scene/lights/DiskLight.h"
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
