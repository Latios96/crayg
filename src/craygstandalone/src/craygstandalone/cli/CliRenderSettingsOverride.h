#pragma once

#include "crayg/foundation/math/geometry/Resolution.h"
#include "crayg/foundation/objects/DtoUtils.h"
#include "crayg/scene/RenderSettings.h"
#include <fmt/std.h>
#include <optional>

namespace crayg {

CRAYG_DTO_2(IntegratorSettingsOverride, std::string, settingName, IntegratorSettingsValue, value);

struct CliRenderSettingsOverride {
    std::optional<Resolution> resolution;
    std::optional<int> maxSamples;
    std::optional<IntegratorType> integratorType;
    std::optional<IntegratorSettings> integratorSettings;
    std::optional<IntersectorType> intersectorType;
    std::optional<TileSequenceType> tileSequenceType;
    std::optional<TileSamplerType> tileSamplerType;
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
