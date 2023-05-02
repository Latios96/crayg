#ifndef CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_
#define CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_

#include "BaseUsdReader.h"
#include "scene/RenderSettings.h"
#include "sceneIO/usd/CraygUsdBase.h"
#include <pxr/usd/usdRender/settings.h>

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
    IntegratorSettings readIntegratorSettings() const;
    bool isIntegratorSettingsAttribute(const pxr::UsdAttribute &attribute) const;
    IntegratorSettingsValue readIntegratorSettingsValue(const pxr::UsdAttribute &attribute) const;
    IntersectorType readIntersectorType() const;
    BucketSequenceType readBucketSequenceType() const;
    BucketSamplerType readBucketSamplerType();
    float readAdaptiveMaxError();
    int readSamplesPerAdaptivePass();
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENEIO_READ_USD_USDRENDERSETTINGSREADER_H_
