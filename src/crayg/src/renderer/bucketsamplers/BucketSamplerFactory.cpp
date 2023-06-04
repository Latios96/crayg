#include "BucketSamplerFactory.h"
#include "AdaptiveBucketSampler.h"
#include "UniformBucketSampler.h"

namespace crayg {
std::unique_ptr<BucketSampler>
BucketSamplerFactory::createBucketSampler(const RenderSettings &renderSettings,
                                          const std::function<Color(Vector2f)> &renderSample) {
    switch (renderSettings.bucketSamplerType) {
    case BucketSamplerType::UNIFORM:
        return std::make_unique<UniformBucketSampler>(renderSettings.maxSamples, renderSample);
    case BucketSamplerType::ADAPTIVE:
        return std::make_unique<AdaptiveBucketSampler>(renderSettings.maxSamples, renderSample,
                                                       renderSettings.samplesPerAdaptivePass,
                                                       renderSettings.adaptiveMaxError);
        throw std::runtime_error(
            fmt::format(R"(Unsupported BucketSamplerType : "{}")", renderSettings.bucketSamplerType));
    }
}
} // crayg