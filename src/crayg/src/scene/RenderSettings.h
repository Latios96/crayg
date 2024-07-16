#pragma once

#include "basics/Bound2d.h"
#include "image/imageiterators/buckets/BucketSequenceType.h"
#include "integrators/IntegratorSettings.h"
#include "integrators/IntegratorType.h"
#include "intersectors/IntersectorType.h"
#include "renderer/bucketsamplers/BucketSamplerType.h"
#include <basics/Resolution.h>
#include <fmt/ostream.h>
#include <optional>

namespace crayg {

Bounds2di parseRegionFromString(const std::string &str);

class RenderSettings {
  public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType,
                            IntegratorSettings integratorSettings, IntersectorType intersectorType,
                            BucketSequenceType bucketSequenceType, BucketSamplerType bucketSamplerType, float maxError,
                            int samplesPerAdaptivePass, bool useSpectralLensing,
                            const std::optional<Bounds2di> &regionToRender);

    static RenderSettings createDefault();

    bool operator==(const RenderSettings &rhs) const;
    bool operator!=(const RenderSettings &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const RenderSettings &renderSettings);

    Resolution resolution;
    int maxSamples;
    IntegratorType integratorType = IntegratorType::RAYTRACING;
    IntegratorSettings integratorSettings;
    IntersectorType intersectorType = IntersectorType::EMBREE;
    BucketSequenceType bucketSequenceType = BucketSequenceType::MORTON;
    BucketSamplerType bucketSamplerType = BucketSamplerType::ADAPTIVE;
    float adaptiveMaxError = 0.007f;
    int samplesPerAdaptivePass = 8;
    bool useSpectralLensing = false;
    std::optional<Bounds2di> regionToRender;
};

}

template <> struct fmt::formatter<crayg::RenderSettings> : ostream_formatter {};
