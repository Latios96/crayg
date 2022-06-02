//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDDISKLIGHTTRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDDISKLIGHTTRANSLATOR_H_

#include "sceneIO/CraygUsdBase.h"
#include "BaseUsdLightTranslator.h"
#include "scene/DiskLight.h"
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

class UsdDiskLightTranslator : public BaseUsdLightTranslator<pxr::UsdLuxDiskLight, DiskLight> {
 public:
    UsdDiskLightTranslator(const pxr::UsdLuxDiskLight &diskLight);
    std::shared_ptr<DiskLight> translate() override;
 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDDISKLIGHTTRANSLATOR_H_
