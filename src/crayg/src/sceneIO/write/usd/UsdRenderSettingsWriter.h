#pragma once

#include "scene/RenderSettings.h"
#include "sceneIO/write/usd/base/BaseUsdWriter.h"
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
    void writeBucketSamplerType(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeAdaptiveMaxError(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeSamplesPerAdaptivePass(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeUseSpectralLensing(const pxr::UsdRenderSettings &usdRenderSettings) const;
    void writeRegionToRender(const pxr::UsdRenderSettings &usdRenderSettings) const;
};

}
