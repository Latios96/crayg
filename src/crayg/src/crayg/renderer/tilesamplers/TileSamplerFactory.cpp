#include "TileSamplerFactory.h"
#include "AdaptiveTileSampler.h"
#include "UniformTileSampler.h"
#include "crayg/foundation/exceptions/Exceptions.h"

namespace crayg {

std::unique_ptr<TileSampler> TileSamplerFactory::createTileSampler(const RenderSettings &renderSettings,
                                                                   const std::function<Color(Vector2f)> &renderSample) {
    switch (renderSettings.tileSamplerType) {
    case TileSamplerType::UNIFORM:
        return std::make_unique<UniformTileSampler>(renderSettings.maxSamples, renderSample);
    case TileSamplerType::ADAPTIVE:
        return std::make_unique<AdaptiveTileSampler>(renderSettings.maxSamples, renderSample,
                                                     renderSettings.samplesPerAdaptivePass,
                                                     renderSettings.adaptiveMaxError);
    default:
        CRAYG_LOG_AND_THROW_RUNTIME_ERROR(R"(Unsupported TileSamplerType : "{}")", renderSettings.tileSamplerType);
    }
}
}