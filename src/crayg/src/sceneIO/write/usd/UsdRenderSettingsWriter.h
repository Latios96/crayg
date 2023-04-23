#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRENDERSETTINGSWRITER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRENDERSETTINGSWRITER_H_

#include "BaseUsdWriter.h"
#include "scene/RenderSettings.h"
#include <pxr/usd/usdRender/settings.h>

namespace crayg {

class UsdRenderSettingsWriter {
  public:
    UsdRenderSettingsWriter(const RenderSettings &renderSettings);
    pxr::UsdRenderSettings write(pxr::UsdStagePtr stage);

  private:
    RenderSettings renderSettings;
    void writeResolution(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeMaxSamples(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeIntegratorType(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeIntegratorSettings(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeIntersectorType(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeBucketSequenceType(const pxr::UsdRenderSettings &usdRenderSettings) const;
};

} // crayg

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_WRITE_USD_USDRENDERSETTINGSWRITER_H_
