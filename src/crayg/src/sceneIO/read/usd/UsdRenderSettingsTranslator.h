//
// Created by Jan on 29.05.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSTRANSLATOR_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSTRANSLATOR_H_

#include "sceneIO/CraygUsdBase.h"
#include "BaseUsdTranslator.h"
#include <pxr/usd/usdRender/settings.h>
#include "scene/RenderSettings.h"

namespace crayg {

class UsdRenderSettingsTranslator : public BaseUsdTranslator<pxr::UsdRenderSettings, RenderSettings> {
 public:
    UsdRenderSettingsTranslator(const pxr::UsdRenderSettings &usdPrim);
    std::shared_ptr<RenderSettings> translate() override;
 protected:
    std::string getTranslatedType() override;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSTRANSLATOR_H_
