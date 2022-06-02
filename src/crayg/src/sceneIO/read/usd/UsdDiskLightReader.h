//
// Created by Jan on 21.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDDISKLIGHTREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDDISKLIGHTREADER_H_

#include "sceneIO/usd/CraygUsdBase.h"
#include "BaseUsdLightReader.h"
#include "scene/DiskLight.h"
#include <pxr/usd/usdLux/diskLight.h>

namespace crayg {

class UsdDiskLightReader : public BaseUsdLightReader<pxr::UsdLuxDiskLight, DiskLight> {
 public:
    UsdDiskLightReader(const pxr::UsdLuxDiskLight &diskLight);
    std::shared_ptr<DiskLight> read() override;
 protected:
    std::string getTranslatedType() override;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDDISKLIGHTREADER_H_
