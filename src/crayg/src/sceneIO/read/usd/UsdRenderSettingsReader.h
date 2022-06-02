//
// Created by Jan on 29.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_

#include "sceneIO/CraygUsdBase.h"
#include "BaseUsdReader.h"
#include <pxr/usd/usdRender/settings.h>
#include "scene/RenderSettings.h"

namespace crayg {

class UsdRenderSettingsReader : public BaseUsdReader<pxr::UsdRenderSettings, RenderSettings> {
 public:
    UsdRenderSettingsReader(const pxr::UsdRenderSettings &usdPrim);
    std::shared_ptr<RenderSettings> read() override;
 protected:
    std::string getTranslatedType() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_
