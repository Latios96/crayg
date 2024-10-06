#pragma once

#include "basics/Resolution.h"
#include "scene/RenderSettings.h"
#include "utils/DtoUtils.h"
#include <optional>

namespace crayg {

CRAYG_DTO_2(IntegratorSettingsOverride, std::string, settingName, IntegratorSettingsValue, value);

struct CliRenderSettingsOverride {
    std::optional<Resolution> resolution;
    std::optional<int> maxSamples;
    std::optional<IntegratorType> integratorType;
    std::optional<IntersectorType> intersectorType;
    std::optional<BucketSequenceType> bucketSequenceType;
    std::optional<BucketSamplerType> bucketSamplerType;
    std::optional<float> adaptiveMaxError;
    std::optional<int> samplesPerAdaptivePass;
    std::optional<bool> useSpectralLensing;
    std::optional<RegionToRender> regionToRender;
    std::vector<IntegratorSettingsOverride> integratorSettingsOverrides;

    RenderSettings resolveOverrides(const RenderSettings &renderSettings) const;

    bool hasAnyOverrides() const;

    std::string reportOverrides() const;
};

}
