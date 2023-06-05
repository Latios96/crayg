#ifndef CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
#define CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_

#include "image/imageiterators/buckets/BucketSequenceType.h"
#include "integrators/IntegratorSettings.h"
#include "integrators/IntegratorType.h"
#include "intersectors/IntersectorType.h"
#include "renderer/bucketsamplers/BucketSamplerType.h"
#include "spdlog/fmt/ostr.h"
#include <basics/Resolution.h>
#include <utils/ToStringHelper.h>

namespace crayg {

class RenderSettings {
  public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType,
                            IntegratorSettings integratorSettings, IntersectorType intersectorType,
                            BucketSequenceType bucketSequenceType, BucketSamplerType bucketSamplerType, float maxError,
                            int samplesPerAdaptivePass);

    static RenderSettings createDefault();

    bool operator==(const RenderSettings &rhs) const;
    bool operator!=(const RenderSettings &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const RenderSettings &renderSettings) {
        os << ToStringHelper("RenderSettings")
                  .addMember("resolution", renderSettings.resolution)
                  .addMember("maxSamples", renderSettings.maxSamples)
                  .addMember("integratorType", renderSettings.integratorType)
                  .addMember("integratorSettings", renderSettings.integratorSettings)
                  .addMember("intersectorType", renderSettings.intersectorType)
                  .addMember("bucketSequenceType", renderSettings.bucketSequenceType)
                  .addMember("bucketSamplerType", renderSettings.bucketSamplerType)
                  .addMember("adaptiveMaxError", renderSettings.adaptiveMaxError)
                  .addMember("samplesPerAdaptivePass", renderSettings.samplesPerAdaptivePass)
                  .finish();
        return os;
    }

    Resolution resolution;
    int maxSamples;
    IntegratorType integratorType = IntegratorType::RAYTRACING;
    IntegratorSettings integratorSettings;
    IntersectorType intersectorType = IntersectorType::EMBREE;
    BucketSequenceType bucketSequenceType = BucketSequenceType::SPIRAL;
    BucketSamplerType bucketSamplerType = BucketSamplerType::ADAPTIVE;
    float adaptiveMaxError = 0.007f;
    int samplesPerAdaptivePass = 8;
};

}

#endif // CRAYG_SRC_CRAYG_SRC_SCENE_RENDERSETTINGS_H_
