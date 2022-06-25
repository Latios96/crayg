#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_

#include "sceneIO/usd/CraygUsdBase.h"
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
 private:
    Resolution readResolution() const;
    int readMaxSamples() const;
    IntegratorType readIntegratorType() const;
};

}

#endif //CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_
