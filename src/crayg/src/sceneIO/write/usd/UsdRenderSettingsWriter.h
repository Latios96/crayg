//
// Created by Jan on 02.06.2022.
//

#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRENDERSETTINGSWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRENDERSETTINGSWRITER_H_

#include "BaseUsdWriter.h"
#include <pxr/usd/usdRender/settings.h>
#include "scene/RenderSettings.h"

namespace crayg {

class UsdRenderSettingsWriter {
 public:
    UsdRenderSettingsWriter(const RenderSettings &renderSettings);
    pxr::UsdRenderSettings write(pxr::UsdStagePtr stage);
 private:
    RenderSettings renderSettings;
};

} // crayg

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRENDERSETTINGSWRITER_H_
