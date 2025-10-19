#pragma once

#include "crayg/foundation/areaiterators/tiles/TileSequenceType.h"
#include "crayg/foundation/math/geometry/Resolution.h"
#include "image/io/imageformatwriters/ImageFormatWriteOptions.h"
#include "renderer/integrators/IntegratorSettings.h"
#include "renderer/integrators/IntegratorType.h"
#include "renderer/intersectors/IntersectorType.h"
#include "renderer/tilesamplers/TileSamplerType.h"
#include "scene/RegionToRender.h"
#include <fmt/ostream.h>
#include <optional>

namespace crayg {

class RenderSettings {
  public:
    RenderSettings();
    RenderSettings(const RenderSettings &renderSettings);
    explicit RenderSettings(const Resolution &resolution, int maxSamples, IntegratorType integratorType,
                            IntegratorSettings integratorSettings, IntersectorType intersectorType,
                            TileSequenceType tileSequenceType, TileSamplerType tileSamplerType, float maxError,
                            int samplesPerAdaptivePass, bool useSpectralLensing,
                            const std::optional<RegionToRender> &regionToRender,
                            const ImageFormatWriteOptions &imageFormatWriteOptions);

    static RenderSettings createDefault();

    bool operator==(const RenderSettings &rhs) const;
    bool operator!=(const RenderSettings &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const RenderSettings &renderSettings);

    Resolution resolution;
    int maxSamples;
    IntegratorType integratorType = IntegratorType::RAYTRACING;
    IntegratorSettings integratorSettings;
    IntersectorType intersectorType = IntersectorType::EMBREE;
    TileSequenceType tileSequenceType = TileSequenceType::MORTON;
    TileSamplerType tileSamplerType = TileSamplerType::ADAPTIVE;
    float adaptiveMaxError = 0.007f;
    int samplesPerAdaptivePass = 8;
    bool useSpectralLensing = false;
    std::optional<RegionToRender> regionToRender;
    ImageFormatWriteOptions imageFormatWriteOptions;
};

}

template <> struct fmt::formatter<crayg::RenderSettings> : ostream_formatter {};
